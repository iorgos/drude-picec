<?php
/**
 * @file
 * Enables modules and site configuration for a picec site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function picec_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#title'] = 'Nombre de la Tienda';
  $form['site_information']['site_mail']['#title'] = 'Mail de la Tienda';
  $form['site_information']['site_name']['#default_value'] = 'Mi tienda';

  // This profile was designed to Chile.
  $form['server_settings']['site_default_country']['#default_value'] = 'CL';
}