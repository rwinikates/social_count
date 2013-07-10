<?php

/**
 * @file
 * Field related hook implementations for the Social Count module.
 */

/**
 * Implements hook_field_info().
 */
function social_count_field_info() {
  return array(
    'social_count' => array(
      'label' => t('Social Count'),
      'description' => t('Social Count buttons.'),
      'default_widget' => 'social_count_widget',
      'default_formatter' => 'social_count_buttons',
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function social_count_field_formatter_info() {
  return array(
    'social_count_buttons' => array(
      'label' => t('Social Count buttons'),
      'field types' => array('social_count'),
      'settings' => array(
        'size' => 1,
        'facebook_recommend' => 0,
        'show_count' => FALSE,
        'show_icon' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_field_prepare_view().
 *
 * Adds a dummy value in SocialCount field to make rendering possible.
 */
function social_count_field_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items) {
  foreach ($items as $key => $item) {
    if (!isset($item[0]['value'])) {
      $items[$key][0]['value'] = 'Dummy value';
    }
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function social_count_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  _social_count_add_library();

  $settings = $display['settings'];
  $element = array();

  // Get entity url.
  $uri = entity_uri($entity_type, $entity);
  $uri['options'] += array(
    'absolute' => TRUE,
  );
  $url = url($uri['path'], $uri['options']);

  // Create the render array.
  $element[] = array(
    '#theme' => 'social_count_link_list',
    '#url' => $url,
    '#size' => $settings['size'],
    '#show_count' => $settings['show_count'],
    '#facebook_recommend' => $settings['facebook_recommend'],
    '#items' => array(
      SocialCountBase::FACEBOOK => array(
        'type' => SocialCountBase::FACEBOOK,
        'url' => $url,
        'show_icon' => $settings['show_icon'],
        'facebook_recommend' => $settings['facebook_recommend'],
      ),
      SocialCountBase::TWITTER => array(
        'type' => SocialCountBase::TWITTER,
        'url' => $url,
        'show_icon' => $settings['show_icon'],
      ),
      SocialCountBase::GOOGLEPLUS => array(
        'type' => SocialCountBase::GOOGLEPLUS,
        'url' => $url,
        'show_icon' => $settings['show_icon'],
      ),
    ),
  );

  return $element;
}

/**
 * Implements hook_field_is_empty().
 */
function social_count_field_is_empty($item, $field) {
  return FALSE;
}

/**
 * Implements hook_field_widget_info().
 */
function social_count_field_widget_info() {
  return array(
    'social_count_widget' => array(
      'label' => t('Social count widget'),
      'field types' => array('social_count'),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function social_count_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element['size'] = array(
    '#type' => 'select',
    '#title' => t('Buttons size'),
    '#options' => SocialCountBase::getButtonsSizes(),
    '#default_value' => $settings['size'],
  );
  $element['facebook_recommend'] = array(
    '#type' => 'radios',
    '#title' => t('Facebook'),
    '#options' => array(
      0 => t('Like'),
      1 => t('Recommend'),
    ),
    '#default_value' => $settings['facebook_recommend'],
  );
  $element['show_count'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fetch Share Counts'),
    '#default_value' => $settings['show_count'],
  );
  $element['show_icon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include Icons'),
    '#default_value' => $settings['show_icon'],
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function social_count_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();

  $sizes = SocialCountBase::getButtonsSizes();
  $summary[] = t('Button size: !size', array('!size' => $sizes[$settings['size']]));
  $summary[] = ($settings['facebook_recommend'] != 0) ? t('Facebook: Recommend') : t('Facebook: Like');
  $summary[] = ($settings['show_count'] != 0) ? t('Fetch count: True') : t('Fetch count: False');
  $summary[] = ($settings['show_icon'] != 0) ? t('Show icons: True') : t('Show icons: False');

  return implode('<br />', $summary);
}
