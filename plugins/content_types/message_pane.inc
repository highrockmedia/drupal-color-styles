<?php

$plugin = array(
  'single' => TRUE,
  // Just do this one, it is needed.
  'title' => t('Message Pane'),
  'description' => t('Custom message pane with color settings.'),
  'category' => t('Custom profile'),
  'edit form' => 'color_styles_message_pane_edit_form',
  'render callback' => 'color_styles_message_pane_render',
  // Array of defaults for the settings form.
  'defaults' => array(
    'text' => '',
    'markup_tag' => '',
    'override_title' => FALSE,
    'override_title_text' => '<no title>',
  ),
  'all contexts' => TRUE,
  // This is NEEDED to be able to use substitution strings in your pane.
);

/**
 * An edit form for the pane's settings.
 */
function color_styles_message_pane_edit_form($form, &$form_state) {

  // Hide the pane title  / override, we don't want it and it's not a required field.
  $form['override_title_text'] = array(
    '#type' => '',
  );

  $form['override_title'] = array(
    '#type' => '',
  );

  $form['override_title_markup'] = array(
    '#markup' => t(''),
  );

  return $form;

}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function color_styles_message_pane_render($subtype, $conf, $args, $contexts) {
  // Pull the message title from our settings page
  $message_title = variable_get('color_styles_message_title');
  $title_color = variable_get('color_styles_title_color');
  $title_bg = variable_get('color_styles_title_bg');
  $message_text = variable_get('color_styles_message_text');

  // Define the output array.
  $output = array();

  // Render the title text if there's a value.
  if (isset($message_title)) {
    $output[] = '<h2 style="color: #' . $title_color . ' ; background-color: #' . $title_bg . ' " class="help-text-wrapper"> ';
    $output[] = $message_title;
    $output[] = '</h2>';
  }

  // Render the message text if there's a value
  if (isset($message_text['value'])) {
    $output[] = '<span class="message-text-wrapper"> ';
    $output[] = $message_text['value'];
    $output[] = '</span>';
  }

  // Render the final output.
  $block = new stdClass();
  $block->title = '';
  $block->content = implode('', $output);

  return $block;
}