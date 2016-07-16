<?php

if ( ! defined('PICEC_DEFAULT_LANGUAGE')) {
  define('PICEC_DEFAULT_LANGUAGE', 'es');
}


class CategoryXMLMigration extends XMLMigration {
    public function __construct($arguments = array()) {
      $arguments['group_name'] = 'picec_demo';
      parent::__construct($arguments);
      $this->description = t('XML file of multiple products');

      $termSchema = array(
        'tid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'description' => 'ID of destination term',
        ),
      );

      $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
          )
        ),
        $termSchema
      );

      $fields = array();


      /* Gets the XML source file absolute path */
      $picec_demo_path = drupal_get_path('module', 'picec_demo');
      $xml_folder = DRUPAL_ROOT . '/' . $picec_demo_path . '/data';
      $items_url = $xml_folder . '/categories.xml';

      /* xpath for the item to Migrate (product) and the key (sku) */
      $item_xpath = '/categories/category';
      $item_ID_xpath = 'id';

      $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);

      /* sets the source for this migration */
      $this->source = new MigrateSourceMultiItems($items_class, $fields);
      $this->destination = new MigrateDestinationTerm('product_category');

      $this->addFieldMapping('name', 'name')
        ->xpath('content/' . PICEC_DEFAULT_LANGUAGE . '/name');

      $this->addFieldMapping('description', 'description')
        ->xpath('content/' . PICEC_DEFAULT_LANGUAGE . '/description');

    }
}