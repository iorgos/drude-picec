<?php

/**
 * Implements hook_preprocess_node().
 */
function compra_preprocess_node(&$variables) {
  $view_mode = $variables['elements']['#view_mode'];
  $node_type = $variables['type'];
  if($view_mode == "teaser" && $node_type == "product_display"){
    unset($variables['content']['links']['node']['#links']['node-readmore']);
    unset($variables['elements']['links']['node']['#links']['node-readmore']);
  }
}
