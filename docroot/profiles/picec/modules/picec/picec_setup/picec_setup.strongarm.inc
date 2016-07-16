<?php
/**
 * @file
 * picec_setup.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function picec_setup_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_billing_addressbook';
  $strongarm->value = 1;
  $export['commerce_customer_profile_billing_addressbook'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_billing_field';
  $strongarm->value = 'commerce_customer_billing';
  $export['commerce_customer_profile_billing_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_shipping_addressbook';
  $strongarm->value = 1;
  $export['commerce_customer_profile_shipping_addressbook'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_shipping_field';
  $strongarm->value = 'commerce_customer_shipping';
  $export['commerce_customer_profile_shipping_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_shipping_profile_copy';
  $strongarm->value = 1;
  $export['commerce_customer_profile_shipping_profile_copy'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_shipping_profile_copy_default';
  $strongarm->value = 1;
  $export['commerce_customer_profile_shipping_profile_copy_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_shipping_profile_copy_source';
  $strongarm->value = 'billing';
  $export['commerce_customer_profile_shipping_profile_copy_source'] = $strongarm;

  return $export;
}
