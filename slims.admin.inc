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
  return system_settings_form($form);
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
