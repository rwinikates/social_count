<?php
/**
 * @file
 * An SocialCount helper class.
 */

class SocialCountBase {
  const FACEBOOK = 'facebook';
  const TWITTER = 'twitter';
  const GOOGLEPLUS = 'googleplus';

  /**
   * Helper function to get the available size options.
   */
  public static function getButtonsSizes() {
    return array(
      0 => t('Small'),
      1 => t('Medium'),
      2 => t('Large'),
    );
  }
}
