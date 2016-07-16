<?php
/**
 * @file
 * picec_product.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function picec_product_taxonomy_default_vocabularies() {
  return array(
    'product_category' => array(
      'name' => 'product category',
      'machine_name' => 'product_category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
