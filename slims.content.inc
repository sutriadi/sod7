<?php

function slims_search($key = '') {
  $slims_conf = slims_conf();
  
  $page = isset($_GET['page']) ? $_GET['page'] : 0;
  
  $params = array(
    'title' => isset($_GET['title']) ? $_GET['title'] : '',
    'author' => isset($_GET['author']) ? $_GET['author'] : '',
    'subject' => isset($_GET['subject']) ? $_GET['subject'] : '',
    'isbn' => isset($_GET['isbn']) ? $_GET['isbn'] : '',
  );
  
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
    
  $render_array['slims_markup'] = array(
    '#markup' => '<h3>' . $slims_conf['server_subtitle'] . '</h3>'
  );
  
  $data = _slims_receiver_items($page, $key, $params);
  
  if ($data['total'] != 0 AND $data['nums'] != 0)
  {
    $page = pager_default_initialize($data['total'], $data['nums']);
  
    $offset = ($page) * $data['nums'];
    $last = ($offset + $data['nums'] < $data['total'])? $offset + $data['nums'] : $data['total'];
  }
  else {
    $render_array['slims_empty_search'] = array(
      '#markup' => '<h3>' . t('Search result with keywords: !key has empty', array('!key' => "<em>$key</em>")) . '</h3>'
    );
  }
  
  $items = array();
  foreach ($data['items'] as $item) {
    $items[] = array(
      'data' => array(
        '#theme' => 'slims_single_item',
        '#items' => $item,
      ),
      'class' => array('item-' . $item['id']),
    );
  }
  
  if (!empty($items)) {
    $render_array['slims_list'] = array(
      '#theme' => 'slims_div_items',
      '#items' => $items,
      '#title' => !empty($key) ? t('Search result with keywords: !key', array('!key' => "<em>$key</em>")) : NULL,
      '#pre_render' => array('slims_item_list_child_render'),
    );
  }

  $render_array['slims_pager'] = array(
    '#theme' => 'pager',
  );

  if (empty($key))
    $breadcrumb[] = l(variable_get('slims_server_title', 'Senayan'), 'slims/search');
  else {
    $breadcrumb[] = l(t('Search result(s)'), 'slims/search');
    $breadcrumb[] = l($key, current_path());
  }

  drupal_set_breadcrumb($breadcrumb);

  drupal_add_css(drupal_get_path('module', 'slims') .'/slims.css');
  return $render_array;
}

function slims_item_details($id = '') {
  $slims_conf = slims_conf();

  $button['back'] = array(
    '#type' => 'button',
    '#button_type' => 'button',
    '#value' => t('Back'),
    '#attributes' => array('onclick' => "history.back()"),
  );

  $render_array['slims_back_button'] = array(
    '#markup' => drupal_render($button),
  );
  
  if (!is_numeric($id)) {
    $render_array['slims_empty_id'] = array(
      '#markup' => '<p>' . t('ID is invalid!') . '</p>',
    );
  }
  else {

    $data = _slims_receiver_details($id);
    
    $title_page = t('@title | Record Detail', array('@title' => $data['items']['title']['val']));
    drupal_set_title($title_page, CHECK_PLAIN);
    
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), '<front>');
    $breadcrumb[] = l(variable_get('slims_server_title', 'Senayan'), 'slims/search');
    $breadcrumb[] = l($data['items']['title']['val'], 'slims/detail/' . $id);

	drupal_set_breadcrumb($breadcrumb);
    
    if (count($data['items']) > 0) {
      $header = array(
        array('data' => ''),
        array('data' => ''),
      );
      
      $rows = array();
      foreach ($data['items'] as $prerow => $row) {
	    $rows[$prerow] = array(
	      array('data' => $row['key']),
	      array('data' => $row['val'])
	    );
	  }
      $render_array['slims_detail_table'] = array(
        '#theme' => 'table',
        //~ '#header' => $header,
        '#rows' => $rows,
        '#pre_render' => array('slims_row_detail'),
      );
    }
    
  }
  
  return $render_array;
}
