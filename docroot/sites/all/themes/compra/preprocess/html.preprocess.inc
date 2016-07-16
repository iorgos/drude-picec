<?php


function compra_preprocess_html(&$variables) {
    $sidebar_first = true;
    $sidebar_second = true;
    if(!isset($variables['page']['sidebar_first']) || empty($variables['page']['sidebar_first'])){
        $variables['attributes_array']['class'][] = "no-sidebar-first";
        $sidebar_first = false;
    }


    if(!isset($variables['page']['sidebar_second']) || empty($variables['page']['sidebar_second'])){
        $variables['attributes_array']['class'][] = "no-sidebar-second";
        $sidebar_second = false;
    }

    $both_sidebars = $sidebar_first && $sidebar_second;
    $no_sidebars   = !($sidebar_first || $sidebar_second);

    $both_sidebars ? $variables['attributes_array']['class'][] = "both-sidebars" : "";
    $no_sidebars   ? $variables['attributes_array']['class'][] = "no-sidebars"   : "";
}