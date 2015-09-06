<?php
/**
 * @file
 * Các hook block c?a module Kaya - Recommend.
 */

/**
 * Implements hook_block_info().
 */
function kaya_recommend_block_info() {
  $blocks['recommended_counts'] = [
    'info' => t('Recommended Count'),
    'region' => 'sidebar_second',
    'status' => TRUE,
    'weight' => 0,
    'visibility' => 0,
  ];

  return $blocks;
}

/**
 * Implements hook_block_configure().
 */
function kaya_recommend_block_configure($delta) {
  switch ($delta) {
    case 'recommended_counts':
      break;
  }
}

/**
 * Implements hook_block_save().
 */
function kaya_recommend_block_save($delta = '', $edit = array()) {
  switch ($delta) {
    case 'recommended_counts':
      break;
  }
}

/**
 * Implements hook_block_view().
 */
function kaya_recommend_block_view($delta = '') {
  /**
   * Quy ??c ??t tên hàm content c?a block.
   * _KAYA_blocks_content_{block name}
   */
  switch ($delta) {
    case 'recommended_counts':
      return [
        'subject' => t('Recommended Count'),
        'content' => _KAYA_blocks_content_recommended_counts(),
      ];
      break;
  }
}

/**
 * Tr? v? content c?a block 'Recommend counts'
 */
function _KAYA_blocks_content_recommended_counts() {
  global $user;

  $query = db_select('recommend', 'r')
    ->fields('r', ['site'])
    ->groupBy('r.site');
  $query->addExpression('count(r.entity_id)', 'ncount');

  $results = $query->condition('r.user_email', $user->mail)
    ->execute();

  $items = [];
  while ($recommend = $results->fetchAssoc()) {
    $items[] = [
      'class' => array('list-group-item'),
      'data' => '<span class="badge">' . $recommend['ncount'] . '</span>' . $recommend['site']
    ];
  }

  return [
    '#theme' => 'item_list',
    '#type' => 'ul',
    '#attributes' => array('class' => 'list-group'),
    '#items' => $items,
  ];
}
