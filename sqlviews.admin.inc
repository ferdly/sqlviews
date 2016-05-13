<?php

function sqlviews_overview() {
    return 'Hello SQL-Views Overview!';
}

function sqlviews_page($which_form) {
    // drupal_set_message(__FUNCTION__);
  // $build = array(
  //   'header_text' => array(
  //     '#type' => 'markup',
  //     '#markup' => '<p>' . t("Simple Test Page to Render the sqlVIEW of Node Type '{$node_type}'.") . '</p><p>' . t(" That is, &mdash; displayed below &mdash; the SQL Code to render a result set of a stored query on the Node Type data, which the database users can see (and query) just as if it were a persistent database table. It is purposely composed to be as 'Human Readable' as is possibe.") . '</p>',
  //   ),
  // );
  // return $build;
  switch ($which_form) {
      case 'content_types':
        return drupal_get_form('sqlviews_node_form');
        break;
      case 'users':
        return drupal_get_form('sqlviews_user_form');
        break;

      default:
          drupal_goto('unsupported_form_option');
          break;
  }

}

function sqlviews_node_form() {
  global $databases;
  $database = $databases['default']['default']['database'];
  $node_type_result = node_type_get_names();
  $disabled_type_overload_array = array('article', 'page');
  foreach ($node_type_result as $key => $value) {
    if (in_array($key, $disabled_type_overload_array)) {
      $node_type_result[$key] = $value . ' [disabled]';
    }
  }
  $form_key = 'label_option';
  $form[$form_key]['#required'] = true;
  $form[$form_key]['#type'] = 'radios';
  $form[$form_key]['#title'] = t('Select which Label-Option you would like to execute');
  $form[$form_key]['#default_value'] = 'label';
  $form[$form_key]['#options'] = array(
    'label'=>'Column Names will match assigned Label',
    'label_machine'=>'Column Names will match assigned Label rendered as a \'machine_name\'',
    'machine'=>'Column Names will match internal Drupal \'machine_name\'',
    'machine_abbrv'=>"Column Names will match internal Drupal 'machine_name' less 'field' at the beginning and/or 'value at the end.",
    );

  $form_key = 'node_type_chex';
  $form[$form_key]['#required'] = true;
  $form[$form_key]['#type'] = 'radios';
  $form[$form_key]['#title'] = t('Select the Node-Types for which you would like to create a view');
  $form[$form_key]['#options'] = $node_type_result;
  $form[$form_key]['article']['#disabled'] = TRUE;
  $form[$form_key]['page']['#disabled'] = TRUE;

  $form_key = 'output_options';
  $form[$form_key]['#required'] = true;
  $form[$form_key]['#type'] = 'radios';
  $form[$form_key]['#title'] = t('Select which Outputs you would like to execute');
  $form[$form_key]['#default_value'] = 'code';
  $form[$form_key]['#options'] = array(
    'code'=>'Render the SQL \'VIEW\' code',
    /**
     * @circleback = Execute may never be in the cards for this module
     * * \_ I wouldn't trust it if I wasn't an SQL guy
     * *     and _as_ an SQL guy I would just run the generated code
    'execute'=>'Execute the SQL \'VIEW\' code to Create (or Replace) the \'database VIEW\' for \'' . $database . '\'',
     */
   );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Execute',
    );
  return $form;
}

function sqlviews_user_form() {

  $form_key = 'output_options';
  $form[$form_key]['#required'] = true;
  $form[$form_key]['#type'] = 'radios';
  $form[$form_key]['#title'] = t('Select which Outputs you would like to execute');
  $form[$form_key]['#options'] = array(
     'users'=>'Render the SQL code for \'users_view\'',
     'users_roles'=>'Render the SQL code for \'users_roles_view\'',
     'users_ago'=>'Render the SQL code for \'users_view\' using the getAgo() function',
     'users_roles_ago'=>'Render the SQL code for \'users_roles_view\' using the getAgo() function',
   );
  $form[$form_key]['code']['#description'] = '<ul><li>The Output Options below are universal Drupal User Views not connected to a particular Node-Type or Label-Option</li></ul>';
  $form[$form_key]['#field_suffix'] =
    t("<ul>NOTES:
        <li>'users_view' is a Drupal Universal user-friendly view of the Users'</li>
        <li>'users_roles_view' is a Drupal Universal user-friendly view of the Users-Roles<br>that is, one row
        for each user-role combinations'</li>
        <li>the 'ago' versions includes a MySQL User-Defined-Function getAgo()</li>
        <li>by 'Universal' it means that this code should be useable for any Drupal Site's database of the same major version using MySQL</li>
    </ul>");
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Execute',
    );
  return $form;
}

function sqlviews_node_form_submit($form, &$form_state) {
  $admin_config_dev_sqlviews_path = 'admin/config/development/sqlviews';
  // drupal_set_message(t('The form has been submitted.'));

 if (is_string($form_state['values']['node_type_chex'])) {
    $string = $form_state['values']['node_type_chex'];
    $options['query'][$string] = $string;
 }elseif(is_array($form_state['values']['node_type_chex'])){
    $string = 'array_unsupported';
    $options['query'][$string] = $string;
 }

 if (is_string($form_state['values']['output_options'])) {
    $string = $form_state['values']['output_options'];
    $options['query'][$string] = $string;
 }elseif(is_array($form_state['values']['output_options'])){
    $option_array = $form_state['values']['output_options'];
    foreach ($option_array as $key => $value) {
        if ($key === $value) {
            $options['query'][$key] = $value;
        }
    }
 }
 $options['query']['label_option'] = $_POST['label_option'];
 $form_state['redirect'] = array($admin_config_dev_sqlviews_path . '/result', $options);
}
function sqlviews_user_form_submit($form, &$form_state) {
  $admin_config_dev_sqlviews_path = 'admin/config/development/sqlviews';
  // drupal_set_message(t('The form has been submitted.'));

 if (is_string($form_state['values']['node_type_chex'])) {
    $string = $form_state['values']['node_type_chex'];
    $options['query'][$string] = $string;
 }elseif(is_array($form_state['values']['node_type_chex'])){
    $string = 'array_unsupported';
    $options['query'][$string] = $string;
 }

 if (is_string($form_state['values']['output_options'])) {
    $string = $form_state['values']['output_options'];
    $options['query'][$string] = $string;
 }elseif(is_array($form_state['values']['output_options'])){
    $option_array = $form_state['values']['output_options'];
    foreach ($option_array as $key => $value) {
        if ($key === $value) {
            $options['query'][$key] = $value;
        }
    }
 }
 $options['query']['label_option'] = $_POST['label_option'];
  $form_state['redirect'] = array($admin_config_dev_sqlviews_path . '/result', $options);
}

/**
 * Page demonstrating embedding a form on a page.
 * This should be MOOT at this juncture, but seems like a more extensible way to work
 */
function sqlviews_result() {
    global $databases;

    $database = $databases['default']['default']['database'];
    $label_option = $_GET['label_option'];
    $node_type_result = node_type_get_names();
    $node_keys = array_keys($node_type_result);
    $option_keys = array(
        'code',
        'execute',
        'users',
        'users_roles',
        'users_ago',
        'users_roles_ago',
        );

    $node_type_array = array();
    $option_array = array();
    foreach ($_GET as $key => $value) {
        if (in_array($key, $node_keys)) {
            $node_type_array[] = $value;
        }
        if (in_array($key, $option_keys)) {
            $key_words = explode('_', $key);
            if ($key_words[0] == 'users') {
                $users_key = in_array('roles', $key_words) ? 'roles' : 'users';
                $ago = in_array('ago', $key_words);
                $$users_key = $users_key;
            }else{
                $$key = $value;
                $ago = FALSE;
            }
        }
        $option_array = array();
    }
    $node_type = count($node_type_array) == 1?$node_type_array[0]:'ERROR: count='. count($node_type_array);
    $option_code = empty($code)?'NNULL':$code;
    $option_execute = empty($execute)?'NNULL':$execute;
    $option_users = empty($users)?'NNULL':$users;
    $option_roles = empty($roles)?'NNULL':$roles;

    if ($option_execute != 'NNULL' || $option_code != 'NNULL') {
        $node_type_sql = new nodeTypeSQL($node_type);
        $node_type_sql->label_option = $label_option;
     }else{
        $query_name = '';
        $query_name .= $option_users != 'NNULL' ? $option_users : '';
        $query_name .= $option_roles != 'NNULL' ?  'users_' . $option_roles : '';
        require_once 'src/utilityUsersSQL.php';
        $users_utility_string = generate_sql_switch($query_name, $ago);
        $text_area = '<br><hr>
            <textarea name="message" rows="60" cols="90">
            ' . $users_utility_string . '
            </textarea>
            <br><hr><br>';
          $build = array(
            'header_text' => array(
              '#type' => 'markup',
              '#markup' => '<p>' . t("Simple Test Page to Render the sqlVIEW of Node Type '{$node_type}'.") . '</p><p>' . t(" That is, &mdash; displayed below &mdash; the SQL Code to render a result set of a stored query on the Node Type data, which the database users can see (and query) just as if it were a persistent database table. It is purposely composed to be as 'Human Readable' as is possibe.") . '</p>' . $text_area,
            ),
          );
        return $build;
     }

    $node_type_sql->database = $databases['default']['default']['database'];
    $node_type_sql->composeViewString();
    $node_type_sql_simple = array();
    $simple_attribute_array = array(
        'database',
        'type',
        'title_label',
        );
    foreach ($simple_attribute_array as $key) {
        $node_type_sql_simple[$key] = $node_type_sql->$key;
    }
    $text_area = '<br><hr>
        <textarea name="message" rows="60" cols="90">
        ' . $node_type_sql->view_string . '
        </textarea>
        <br><hr><br>';
  $build = array(
    'header_text' => array(
      '#type' => 'markup',
      '#markup' => '<p>' . t("Simple Test Page to Render the sqlVIEW of Node Type '{$node_type}'.") . '</p><p>' . t(" That is, &mdash; displayed below &mdash; the SQL Code to render a result set of a stored query on the Node Type data, which the database users can see (and query) just as if it were a persistent database table. It is purposely composed to be as 'Human Readable' as is possibe.") . '</p>' . $text_area,
    ),
  );
  return $build;
}
