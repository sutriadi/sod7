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
  $form[$_p . '_image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Picture'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form[$_p . '_image'][$_p . '_image_detail_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Image Detail Size'),
    '#default_value' => $slims_conf['image_detail_size'],
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Size of image on detail page'),
  );
  $form[$_p . '_image'][$_p . '_image_thumb_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Image Thumb Size'),
    '#default_value' => $slims_conf['image_thumb_size'],
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Size of image on thumb page'),
  );
  return system_settings_form($form);
}
