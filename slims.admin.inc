<?php
// $Id$

/**
 * @file
 * Admin functions for slims
 */

/**
 * Settings for SLiMS server parameters
 */
function slims_server_settings() {
  $slims_conf = slims_conf();
  $_p = 'slims';
  $form[$_p . '_server_description'] = array(
    '#markup' => '<p>' . t('Configure SLiMS Server.') . '</p>',
  );
  $form[$_p . '_server_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => $slims_conf['server_url'],
    '#description' => t('Complete URL of SLiMS server.'),
  );
  $form[$_p . '_server_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $slims_conf['server_title'],
    '#description' => t('Title of SLiMS server.'),
  );
  $form[$_p . '_server_subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Subtitle'),
    '#default_value' => $slims_conf['server_subtitle'],
    '#description' => t('Subtitle of SLiMS server.'),
  );
  return system_settings_form($form);
}

/**
 * Settings for picture
 */
function slims_picture_settings() {
  $slims_conf = slims_conf();
  $_p = 'slims';
  $form['pic_size'] = array(
    '#type' => 'fieldset',
    '#title' => t('Picture Size'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['pic_size'][$_p . '_image_detail_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Image Detail Size'),
    '#default_value' => $slims_conf['image_detail_size'],
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Size of image on detail page'),
  );
  $form['pic_size'][$_p . '_image_thumb_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Image Thumb Size'),
    '#default_value' => $slims_conf['image_thumb_size'],
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Size of image on thumb page'),
  );
  $form['pic_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Displaying Picture'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $image_opts = array(
    0 => t('Display picture direct from SLiMS server'),
    1 => t('Display picture from SLiMS server with base64 encoded'),
    2 => t('Display picture that stored in SLiMS module'),
  );
  $form['pic_display'][$_p . '_image_opt'] = array(
    '#type' => 'radios',
    '#title' => t('How to handle picture'),
    '#default_value' => $slims_conf['image_opt'],
    '#options' => $image_opts,
    '#description' => t('Select an option how to handle to display picture of an item'),
  );
  $image_empty_opts = array(
    0 => t('Do not display anything'),
    1 => t('Display default picture direct from SLiMS server'),
    2 => t('Display default picture from SLiMS server with base64 encoded'),
    3 => t('Display default picture from SLiMS module'),
  );
  $form['pic_display'][$_p . '_image_empty_opt'] = array(
    '#type' => 'radios',
    '#title' => t('How to handle empty picture'),
    '#default_value' => $slims_conf['image_empty_opt'],
    '#options' => $image_empty_opts,
    '#description' => t('Select an option how to handle when picture of an item is empty'),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Form submission handle for slims_picture_settings()
 */
function slims_picture_settings_submit($form, &$form_state) {
  $_p = 'slims';
  
  $slims_thumb = image_style_load('slims-thumb');
  $x = 0;
  foreach ($slims_thumb['effects'] as $effect) {
    $x++;
    if ($x == 1) {
      $effect['data'] = array(
        'width' => $form_state['values'][$_p . '_image_thumb_size'],
        'height' => $form_state['values'][$_p . '_image_thumb_size'],
        'upscale' => TRUE,
      );
      $effects = array($effect['ieid'] => $effect);
      image_effect_save($effects[$effect['ieid']]);
    }
    else {
      image_effect_delete($effect);
    }
  }
  $path = drupal_get_path('module', 'slims') . '/default/empty.png';
  $picpath = image_style_path('slims-thumb', $path);
  image_style_create_derivative(image_style_load('slims-thumb'), $path, $picpath);

  $slims_thumb = image_style_load('slims-detail');
  $x = 0;
  foreach ($slims_thumb['effects'] as $effect) {
    $x++;
    if ($x == 1) {
      $effect['data'] = array(
        'width' => $form_state['values'][$_p . '_image_detail_size'],
        'height' => $form_state['values'][$_p . '_image_detail_size'],
        'upscale' => TRUE,
      );
      $effects = array($effect['ieid'] => $effect);
      image_effect_save($effects[$effect['ieid']]);
    }
    else {
      image_effect_delete($effect);
    }
  }
  $path = drupal_get_path('module', 'slims') . '/default/empty.png';
  $picpath = image_style_path('slims-detail', $path);
  image_style_create_derivative(image_style_load('slims-detail'), $path, $picpath);
  
  system_settings_form_submit($form, $form_state);
}

/**
 * Pictures import tool
 */
function slims_pictures_tool() {
  $slims_conf = slims_conf();
  $_p = 'slims';
  $form['import'] = array(
    '#type' => 'item',
    '#title' => t('Underconstruction'),
    '#markup' => t('Please wait for some moment...'),
  );
  return $form;
}

/**
 * Settings for widget
 */
function slims_widget_settings() {
  $slims_conf = slims_conf();
  $_p = 'slims';
  $form['search'] = array(
    '#type' => 'fieldset',
    '#title' => t('SLiMS Simple Search'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['search'][$_p . '_search_input_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Search input size'),
    '#default_value' => $slims_conf['search_input_size'],
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Width (in characters) of the search input textfield. Leave empty for automatic.'),
  );
  $form['list'] = array(
    '#type' => 'fieldset',
    '#title' => t('SLiMS Items'),
    '#weight' => 1,
    '#collapsible' =>  TRUE,
    '#collapsed' => FALSE,
  );
  $form['list'][$_p . '_list_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Page number'),
    '#default_value' => $slims_conf['list_page'],
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Page number to be displayed. Page 1 if empty.'),
  );
  $form['list'][$_p . '_list_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Keywords'),
    '#default_value' => $slims_conf['list_key'],
    '#description' => t('Keywords to filter the list.'),
  );
  $form['list'][$_p . '_list_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Limit'),
    '#size' => 2,
    '#maxlength' => 2,
    '#default_value' => $slims_conf['list_limit'],
    '#description' => t('Limit of items to be displayed. Its max number depending of configuration from SLiMS server.'),
  );
  $form['list'][$_p . '_list_more_key'] = array(
    '#type' => 'radios',
    '#title' => t('More link with key'),
    '#default_value' => $slims_conf['list_more_key'],
    '#options' => array(0 => t('No.'), 1 => t('Yes.')),
    '#description' => t('Option when more link clicked. Yes will continue to search result that specified with keywords.'),
  );
  return system_settings_form($form);
}
