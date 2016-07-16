<?php
/**
 * @file file to declarate hook_migrate_api().
 *
 * Like any module based on migrate, this file implements this hook and the
 * intelligence is somewhere else, where the clases are defined. In this case
 * the classes are defined in "include" folder.
 */

/* Implementation of hook_migrate_api(). */
function picec_demo_migrate_api() {
  /**
   * @todo another content should be added as such as orders.
   * 
   * Te potential of this profile would not be fully apreciated through just
   * products. Another content may be created to do so.
   */
  $api = array(
    'api' => 2,
    'migrations' => array(
      'CategoryXML' => array('class_name' => 'CategoryXMLMigration'),
      'ProductXML'  => array('class_name' => 'ProductXMLMigration'),
    ),
  );

  return $api;
}