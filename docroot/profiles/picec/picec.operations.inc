<?php


/**
 * @TODO: documentar
 */

/**
 * Install the picec_demo module.
 */
function _picec_install_demo_modules_dependencies($module, $module_name, &$context) {
  module_enable(array($module), FALSE);

  $context['message'] = st('Installed %module module.', array('%module' => $module_name));
  $context['results'][] = $module;
}

/**
 * Finish modules.
 */
function _picec_install_demo_flush_cache($success, $results, $operations) {
  drupal_flush_all_caches();
}


/**
 * Import the products.
 */
function _picec_install_demo_import($machine_name, &$context) {
  $migration = Migration::getInstance($machine_name);
  $migration->processImport();

  $context['message'] = t('Importing categories and products');
}
