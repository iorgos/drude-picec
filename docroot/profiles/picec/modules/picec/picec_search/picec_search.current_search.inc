<?php
/**
 * @file
 * picec_search.current_search.inc
 */

/**
 * Implements hook_current_search_default_items().
 */
function picec_search_current_search_default_items() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'picec_search';
  $item->label = 'Search Result';
  $item->settings = array(
    'items' => array(
      'results' => array(
        'id' => 'text',
        'label' => 'Results',
        'text' => 'Search found <span class="result-count">[facetapi_results:result-count]</span> item',
        'plural' => 1,
        'text_plural' => 'Search found <span class="result-count">[facetapi_results:result-count]</span> items',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 1,
        'element' => 'h3',
        'css' => 0,
        'classes' => '',
        'weight' => '-50',
      ),
      'active_items' => array(
        'id' => 'active',
        'label' => 'Active items',
        'pattern' => '[facetapi_active:active-value]',
        'keys' => 1,
        'css' => 0,
        'classes' => '',
        'nofollow' => 1,
        'weight' => '-49',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '3',
    ),
  );
  $export['picec_search'] = $item;

  return $export;
}
