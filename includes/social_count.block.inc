<?php

/**
 * @file
 * Block related hook implementations for the Social Count module.
 */

/**
 * Implements hook_block_info().
 */
function social_count_block_info() {
  $blocks['social_count_block'] = array(
    'info' => t('Social Count'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  );
  return $blocks;
}

/**
 * Implements hook_block_configure().
 */
function social_count_block_configure($delta = '') {
  $form = array();
  if ($delta == 'social_count_block') {
    $form['social_count_block_type'] = array(
      '#type' => 'select',
      '#title' => t('Buttons size'),
      '#options' => SocialCountBase::getButtonsSizes(),
      '#default_value' => variable_get('social_count_block_type', 1),
    );
    $form['social_count_block_facebook'] = array(
      '#type' => 'radios',
      '#title' => t('Facebook'),
      '#options' => array(
        0 => t('Like'),
        1 => t('Recommend'),
      ),
      '#default_value' => variable_get('social_count_block_facebook', 0),
    );
    $form['social_count_block_fetch_counts'] = array(
      '#type' => 'checkbox',
      '#title' => t('Fetch Share Counts'),
      '#default_value' => variable_get('social_count_block_fetch_counts', 0),
    );
    $form['social_count_block_icons'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include Icons'),
      '#default_value' => variable_get('social_count_block_icons', 1),
    );
  }
  return $form;
}

/**
 * Implements hook_block_save().
 */
function social_count_block_save($delta = '', $edit = array()) {
  if ($delta == 'social_count_block') {
    variable_set('social_count_block_type', $edit['social_count_block_type']);
    variable_set('social_count_block_facebook', $edit['social_count_block_facebook']);
    variable_set('social_count_block_fetch_counts', $edit['social_count_block_fetch_counts']);
    variable_set('social_count_block_icons', $edit['social_count_block_icons']);
  }
  return;
}

/**
 * Implements hook_block_view().
 */
function social_count_block_view($delta = '') {
  $node = menu_get_object('node');
  if ($node) {
    return;
  }

  switch ($delta) {
    case 'social_count_block':
      $block['subject'] = t('Share this');
      $block['content'] = social_count_block_content();
      break;
  }
  return $block;
}

/**
 * Social count block content.
 */
function social_count_block_content() {
  _social_count_add_library();

  $url = _social_count_get_url();
  $social_count_block_type = variable_get('social_count_block_type', 1);
  $social_count_block_facebook = variable_get('social_count_block_facebook', 0);
  $social_count_block_fetch_counts = variable_get('social_count_block_fetch_counts', FALSE);
  $social_count_block_icons = variable_get('social_count_block_icons', TRUE);

  $element = array(
    '#theme' => 'social_count_link_list',
    '#url' => $url,
    '#size' => $social_count_block_type,
    '#show_count' => $social_count_block_fetch_counts,
    '#facebook_recommend' => $social_count_block_facebook,
    '#items' => array(
      SocialCountBase::FACEBOOK => array(
        'type' => SocialCountBase::FACEBOOK,
        'url' => $url,
        'show_icon' => $social_count_block_icons,
        'facebook_recommend' => $social_count_block_facebook,
      ),
      SocialCountBase::TWITTER => array(
        'type' => SocialCountBase::TWITTER,
        'url' => $url,
        'show_icon' => $social_count_block_icons,
      ),
      SocialCountBase::GOOGLEPLUS => array(
        'type' => SocialCountBase::GOOGLEPLUS,
        'url' => $url,
        'show_icon' => $social_count_block_icons,
      ),
    ),
  );
  return render($element);
}

/**
 * Helper function to return the page path for non-node.
 */
function _social_count_get_url() {
  if (drupal_is_front_page()) {
    $url = url('<front>', array('absolute' => TRUE));
  }
  else {
    $url = url($_GET['q'], array('absolute' => TRUE));
  }

  return $url;
}
