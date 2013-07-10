<?php

/**
 * @file
 * Theme function used by Social Count.
 */

/**
 * Build a single link.
 */
function theme_social_count_link($variables) {
  $type = $variables['type'];
  $url = $variables['url'];
  $show_icon = $variables['show_icon'];
  $facebook_recommend = isset($variables['facebook_recommend']) ? $variables['facebook_recommend'] : FALSE;

  $texte = array(
    SocialCountBase::FACEBOOK => ($facebook_recommend) ? t('Recommend') : t('Like'),
    SocialCountBase::TWITTER => t('Tweet'),
    SocialCountBase::GOOGLEPLUS => t('+1'),
  );
  $title = array(
    SocialCountBase::FACEBOOK => t('Share on Facebook'),
    SocialCountBase::TWITTER => t('Share on Twitter'),
    SocialCountBase::GOOGLEPLUS => t('Share on Google Plus'),
  );
  $bt_url = array(
    SocialCountBase::FACEBOOK => 'https://www.facebook.com/sharer/sharer.php?u=' . $url,
    SocialCountBase::TWITTER => 'https://twitter.com/intent/tweet?text=' . urlencode($url),
    SocialCountBase::GOOGLEPLUS => 'https://plusone.google.com/_/+1/confirm?url=' . $url,
  );

  $icon_markup = '';
  if ($show_icon) {
    $icon_markup = '<span class="social-icon icon-' . $type . '"></span>';
  }

  return array(
    'class' => array($type),
    'data' => l($icon_markup . '<span class="count">' . $texte[$type] . '</span>', $bt_url[$type], array(
      'html' => TRUE,
      'attributes' => array(
        'title' => $title[$type],
      ),
    )),
  );
}

/**
 * Build the list of social links.
 */
function theme_social_count_link_list($variables) {
  $url = $variables['url'];
  $items = $variables['items'];
  $size = $variables['size'];
  $show_count = $variables['show_count'];
  $facebook_recommend = isset($variables['facebook_recommend']) ? $variables['facebook_recommend'] : FALSE;

  $items_array = array();
  foreach ($items as $key => $value) {
    $items_array[] = theme_social_count_link($value);
  }

  $attributes = array(
    'class' => 'socialcount',
    'data-url' => $url,
  );

  if ($show_count) {
    $attributes['data-counts'] = "true";
  }
  if ($facebook_recommend) {
    $attributes['data-facebook-action'] = "recommend";
  }
  if ($size === "0") {
    $attributes['class'] .= ' socialcount-small';
  }
  if ($size === "2") {
    $attributes['class'] .= ' socialcount-large';
  }

  return theme_item_list(array(
    'title' => NULL,
    'items' => $items_array,
    'type' => 'ul',
    'attributes' => $attributes,
  ));
}
