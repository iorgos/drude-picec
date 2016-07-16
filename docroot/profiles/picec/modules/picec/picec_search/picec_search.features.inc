<?php
/**
 * @file
 * picec_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function picec_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "current_search" && $api == "current_search") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function picec_search_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function picec_search_default_search_api_index() {
  $items = array();
  $items['product_display'] = entity_import('search_api_index', '{
    "name" : "Product Display",
    "machine_name" : "product_display",
    "description" : "An index of the products displays.",
    "server" : "catalog",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "body:summary" : { "type" : "text" },
        "body:value" : { "type" : "text" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "field_product" : { "type" : "integer", "entity_type" : "commerce_product" },
        "field_product:commerce_price:amount_decimal" : { "type" : "decimal" },
        "field_product_categories" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_product_categories:name" : { "type" : "list\\u003Ctext\\u003E" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title_field" : { "type" : "text" },
        "type" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_ranges_alter" : {
          "status" : 1,
          "weight" : "-50",
          "settings" : { "fields" : { "field_product:commerce_price:amount_decimal" : "field_product:commerce_price:amount_decimal" } }
        },
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : { "product_display" : "product_display" } }
        },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "search_api_aggregation_1" : {
                "name" : "Title (Fulltext)",
                "type" : "fulltext",
                "fields" : [ "title_field" ],
                "description" : "A Fulltext aggregation of the following fields: Title."
              },
              "search_api_aggregation_2" : {
                "name" : "Category Name",
                "type" : "fulltext",
                "fields" : [ "field_product_categories:name" ],
                "description" : "A Fulltext aggregation of the following fields: Categories \\u00bb Name."
              }
            }
          }
        },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } }
      },
      "processors" : {
        "search_api_case_ignore" : { "status" : 1, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : [],
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_transliteration" : {
          "status" : 1,
          "weight" : "15",
          "settings" : { "fields" : {
              "title_field" : true,
              "body:value" : true,
              "body:summary" : true,
              "field_product_categories:name" : true
            }
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : { "fields" : [], "spaces" : "[^[:alnum:]]", "ignorable" : "[\\u0027]" }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : [],
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      },
      "additional fields" : { "field_product:commerce_price:data" : "field_product:commerce_price:data" }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function picec_search_default_search_api_server() {
  $items = array();
  $items['catalog'] = entity_import('search_api_server', '{
    "name" : "Catalog",
    "machine_name" : "catalog",
    "description" : "For products",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "3",
      "partial_matches" : 0,
      "indexes" : { "product_display" : {
          "nid" : {
            "table" : "search_api_db_product_display",
            "column" : "nid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "type" : {
            "table" : "search_api_db_product_display",
            "column" : "type",
            "type" : "string",
            "boost" : "1.0"
          },
          "status" : {
            "table" : "search_api_db_product_display",
            "column" : "status",
            "type" : "integer",
            "boost" : "1.0"
          },
          "created" : {
            "table" : "search_api_db_product_display",
            "column" : "created",
            "type" : "date",
            "boost" : "1.0"
          },
          "changed" : {
            "table" : "search_api_db_product_display",
            "column" : "changed",
            "type" : "date",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_product_display",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "title_field" : {
            "table" : "search_api_db_product_display_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "body:value" : {
            "table" : "search_api_db_product_display_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "body:summary" : {
            "table" : "search_api_db_product_display_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_product_categories" : {
            "table" : "search_api_db_product_display_field_product_categories",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_product_categories:name" : {
            "table" : "search_api_db_product_display_text",
            "type" : "list\\u003Ctext\\u003E",
            "boost" : "1.0"
          },
          "field_product" : {
            "table" : "search_api_db_product_display",
            "column" : "field_product",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_product:commerce_price:amount_decimal" : {
            "table" : "search_api_db_product_display",
            "column" : "field_product_commerce_price_amount_decimal",
            "type" : "decimal",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1"
  }');
  return $items;
}
