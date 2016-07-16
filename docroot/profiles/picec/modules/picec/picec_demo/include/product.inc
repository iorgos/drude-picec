<?php
/**
 * @file This class migrates products to the site using Migrate.
 *
 * Any modification to the structure of products must be reflected not just here
 * but also (in some cases) in the XML file where the product data is fetched.
 */

/**
 * Drupal does not have this constant, so we added one here.
 */
if ( ! defined('DRUPAL_ADMIN_ROOT_UID')) {
  define('DRUPAL_ADMIN_ROOT_UID', 1);
}

class ProductXMLMigration extends XMLMigration {

  protected $categoryMap;

  /**
   * Constructor
   */
  public function __construct($arguments = array()) {
    $mig = new CategoryXMLMigration();
    $this->categoryMap = $mig->getMap();

    $arguments['group_name'] = 'picec_demo';
    parent::__construct($arguments);

    /* Migrate common initiaization for XML migration */
    $this->setDescription(t('XML file of multiple products'));
    $this->dependencies = array("CategoryXML");


    /* Description of xml fields */
    $fields = array(
      'name' => t('Product name'),
      'description' => t('Product description'),
      'currency' => t('Currency'),
      'price' => t('Price'),
      'sku' => t('SKU code'),
    );

    /* maps the Migration by SKU */
    $this->map = new MigrateSQLMap($this->machineName,
      array(
      'sku' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      )
      ), MigrateDestinationCommerceProduct::getKeySchema('commerce_product')
    );

    /* Gets the XML source file absolute path */
    $picec_demo_path = drupal_get_path('module', 'picec_demo');
    $xml_folder = DRUPAL_ROOT . '/' . $picec_demo_path . '/data';
    $items_url = $xml_folder . '/products.xml';

    /* xpath for the item to Migrate (product) and the key (sku) */
    $item_xpath = '/products/product';
    $item_ID_xpath = 'sku';

    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);

    /* sets the source for this migration */
    $source = new MigrateSourceMultiItems($items_class, $fields);

    $this->setSource($source);

    $des = new MigrateDestinationCommerceProduct('commerce_product', 'product');
    $this->setDestination($des);


    /* Values that takes a default value such as uid */
    $this->addDefaults();

    /* price, sku and such */
    $this->addCommonProductValues();

    /* migrated images */
    $this->addImages();

    /* Destination that will not have any value */
    $this->addUnmigratedDestinations($this->getUnmigratedDestinations());
  }



  /**
   * Add common values for commerce product.
   *
   * Values are: price, currency, sku and name.
   *
   */
  protected function addCommonProductValues() {
    $this->addFieldMapping('commerce_price', 'price')->xpath('price');
    $this->addFieldMapping('commerce_price:currency_code', 'currency')
      ->xpath('currency');
    $this->addFieldMapping('sku', 'sku')->xpath('sku');
    $this->addFieldMapping('title', 'name')->xpath('name');
  }



  /**
   * Adds values for the product image.
   *
   */
  protected function addImages() {
    $this->addFieldMapping('field_product_images', 'img_name')
      ->xpath('img/filename');

    /* In case of multilingual, this must to be changed. */
    $this->addFieldMapping('field_product_images:language')
      ->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_product_images:source_dir')
      ->defaultValue(drupal_get_path('module', 'picec_demo') . '/data/images');

    $this->addFieldMapping('field_product_images:alt', 'img_alt')
      ->xpath('img/alt');

    $this->addFieldMapping('field_product_images:title', 'img_alt')
      ->xpath('img/alt');
  }



  /**
   * Values that does not come from the XML but from fixed values.
   */
  protected function addDefaults() {
    $this->addFieldMapping('uid')->defaultValue(DRUPAL_ADMIN_ROOT_UID);
    $this->addFieldMapping('status')->defaultValue(NODE_PUBLISHED);
    /**
     * In case of multilingual, this must to be changed.
     */
    $this->addFieldMapping('language')->defaultValue(LANGUAGE_NONE);
  }


  /**
   * Gets all field names that will not be migrated.
   *
   * @return array
   *  - an array of field names and/or field properties names.
   */
  protected function getUnmigratedDestinations() {
    return array(
      'created',
      'changed',
      'commerce_price:tax_rate',
      'field_product_images:file_class',
      'field_product_images:destination_dir',
      'field_product_images:destination_file',
      'field_product_images:file_replace',
      'field_product_images:preserve_files',
    );
  }



  /**
   * Each time a product migration is complete, a node is created.
   *
   * @param mixed $product
   * @param mixed $row
   */
  public function complete($product, $row) {
    /* values to create a new node */
    $values = array(
      'type'     => 'product_display',
      'uid'      => 1,
      'status'   => 1,
      'comment'  => 1,
      'promote'  => 0,
      'language' => 'en',
      'title'    => $row->name
    );

    $entity = entity_create('node', $values);

    /* In case of multilingual, this must to be changed. */
    $entity->title_field['und'][0]['value'] = $row->name;
    $entity->body['und'][0]['value'] = (string) $row->xml->description;

    $product_id = $product->product_id;
    $entity->field_product['und'][0]['product_id'] = $product_id;

    $this->entitySetCategories($entity, $row);

    entity_save('node', $entity);
  }



  /**
   * Sets categories to product_display entity.
   *
   * @param mixed $entity
   * @param mixed $row
   */
  public function entitySetCategories(&$entity, $row) {
    $cat = (array)$row->xml->categories;
    $categories = array();

    if(isset($cat['category_id'])) {

      if(!is_array($cat['category_id'])) {
        $categories = array($cat['category_id']);
      }
      else{
        $categories = $cat['category_id'];
      }

      $i = 0;
      foreach($categories as $category_id){
        $map = $this->categoryMap->getRowBySource(array($category_id));
        $tid = (int)$map['destid1'];
        if(!is_numeric($tid) || $tid === 0) continue;

        /* In case of multilingual, this must to be changed. */
        $entity->field_product_categories['und'][$i++]['tid'] = $tid;
      }
    }
  }



  /**
   * Deletes all migrated content.
   *
   * Migrate does not delete all commerce content. It needs to be done with this
   * helper.
   */
  public function preRollback() {
    //parent::preRollback();
    $products = $this->getAllMigratedProducts();
    $nids = $this->getAllMigratedNids($products);

    entity_delete_multiple('node', $nids);

    foreach ($products as $product) {
      commerce_product_delete($product->product_id);
    }
  }



  /**
   * Get all products from the xml.
   *
   * @return array
   *  - an array of commerce module products.
   */
  public function getAllMigratedProducts() {
    $module_path = drupal_get_path('module', 'picec_demo');
    $data = file_get_contents($module_path . '/data/products.xml');
    $iterator = new SimpleXMLIterator($data);
    $products = array();
    for ($iterator->rewind(); $iterator->valid(); $iterator->next()) {
      $sku = (string) $iterator->current()->sku;
      $product = commerce_product_load_by_sku($sku);
      if ($product) {
        $products[] = $product;
      }
    }

    return $products;
  }



  /**
   * For a list of products, returns all the associated nodes.
   *
   * @param mixed $products
   * @return array
   *  - array of nid for the associated nodes.
   */
  public function getAllMigratedNids($products) {
    /**
     * @todo improve poor performance of this solution.
     */
    $nids = array();

    foreach ($products as $product) {
      $query = new EntityFieldQuery;
      $result = $query
        ->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'product_display')
        ->fieldCondition('field_product', 'product_id',
          $product->product_id, '=')
        ->execute();

      if ( ! empty($result['node'])) {
        $keys = array_keys($result['node']);
        $nid = array_shift($keys);
        $nids[$nid] = $nid;
      }
    }

    return $nids;
  }
}