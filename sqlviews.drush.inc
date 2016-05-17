<?php

/**
 * Implements hook_drush_command().
 */
function sqlviews_drush_command() {
/**
 * Essential to the function of the Drush Command
 */
  $items['developer-vardump'] = array(
    'aliases' => array(
      'devv',
      ),
  );
  $items['gather-node-type'] = array(
    'aliases' => array(
      'gnode',
      ),
    'arguments' => array(
      'list' => 'is argument',
      'groupby' => 'is argument',
      'cube' => 'is argument',
    ),
    'options' => array(
      'lab' => 'is option',
      'orderby_desc' => 'is option',
      'dev' => 'is option',
      'content_types' => 'is option',
    ),
  );
  $items['instantiate-node-type'] = array(
    'aliases' => array(
      'inode',
      ),
    'arguments' => array(
      'list' => 'is argument',
      'groupby' => 'is argument',
      'cube' => 'is argument',
    ),
    'options' => array(
      'orderby' => 'is option',
      'orderby_desc' => 'is option',
      'dev' => 'is option',
      'content_types' => 'is option',
    ),
  );
  $items['instantiate-node-fields'] = array(
    'aliases' => array(
      'inodef',
      ),
    'arguments' => array(
      'list' => 'is argument',
      'groupby' => 'is argument',
      'cube' => 'is argument',
    ),
    'options' => array(
      'orderby' => 'is option',
      'orderby_desc' => 'is option',
      'dev' => 'is option',
      'content_types' => 'is option',
    ),
  );
  $items['instantiate-field-objects'] = array(
    'aliases' => array(
      'ifield',
      ),
    'arguments' => array(
      'list' => 'is argument',
      'groupby' => 'is argument',
      'cube' => 'is argument',
    ),
    'options' => array(
      'label' => 'is option',
      'dev' => 'is option',
    ),
  );
  $items['sql-view-code'] = array(
    'aliases' => array(
      'sqlv',
      ),
    'arguments' => array(
      'list' => 'is argument',
      'groupby' => 'is argument',
      'cube' => 'is argument',
    ),
    'options' => array(
      'label' => 'is option',
    ),
  );

/**
  * $items Append & Overload below
  * description ONLY here
  * examples ONLY here
  * aliases isn't associative so NEVER here
  * others fleshed out for HELP command
  */


return $items;
}

/**
 * Callback for the drush-demo-command command
 */
function drush_sqlviews_developer_vardump() {

  _do_developer_vardump();
} //END function drush_node_tablelist($which_list = FALSE)

function drush_sqlviews_gather_node_type($which_type = FALSE) {
//drush_mymodule_custom_save_node
  // Check for existence of argument
    $arguments = _which_nodetype_arguments(); //use custom function to encapsulate
    if (!$which_type) {
        $which_type = drush_choice($arguments, dt('Which Example would you like to interact with using \'PHP-Coder\'?'));
    }

  // Check for correct argument
  $correct_args = array_keys($arguments);
  if (!in_array($which_type, $correct_args)) {
    if ($which_type == '0') {
      drush_user_abort('Buh-Bye! sqlViews Gather Node!');
      return;
    }
    $string = _which_type_arguments('string');
    return drush_set_error(dt('"@type" is not a valid example. ',
      array('@type' => $example)) . $string);
  }

  // drush_print($which_type);
  // return;
  _do_gather_node_type($which_type);
} //END function drush_node_tablelist($which_list = FALSE)

function drush_sqlviews_instantiate_node_type($which_type = FALSE) {
//drush_mymodule_custom_save_node
  // Check for existence of argument
    $arguments = _which_nodetype_arguments(); //use custom function to encapsulate
    if (!$which_type) {
        $which_type = drush_choice($arguments, dt('Which Example would you like to interact with using \'PHP-Coder\'?'));
    }

  // Check for correct argument
  $correct_args = array_keys($arguments);
  if (!in_array($which_type, $correct_args)) {
    if ($which_type == '0') {
      drush_user_abort('Buh-Bye! sqlViews Gather Node!');
      return;
    }
    $string = _which_type_arguments('string');
    return drush_set_error(dt('"@type" is not a valid example. ',
      array('@type' => $example)) . $string);
  }

  // drush_print($which_type);
  // return;
  _do_instantiate_node_type($which_type);
} //END function drush_node_tablelist($which_list = FALSE)

function drush_sqlviews_instantiate_node_fields($which_type = FALSE) {
//drush_mymodule_custom_save_node
  // Check for existence of argument
    $arguments = _which_nodetype_arguments(); //use custom function to encapsulate
    if (!$which_type) {
        $which_type = drush_choice($arguments, dt('Which Example would you like to interact with using \'PHP-Coder\'?'));
    }

  // Check for correct argument
  $correct_args = array_keys($arguments);
  if (!in_array($which_type, $correct_args)) {
    if ($which_type == '0') {
      drush_user_abort('Buh-Bye! sqlViews Gather Node!');
      return;
    }
    $string = _which_type_arguments('string');
    return drush_set_error(dt('"@type" is not a valid example. ',
      array('@type' => $example)) . $string);
  }

  // drush_print($which_type);
  // return;
  _do_instantiate_node_fields($which_type);
} //END function drush_node_tablelist($which_list = FALSE)

function drush_sqlviews_instantiate_field_objects($which_type = FALSE) {
//drush_mymodule_custom_save_node
  // Check for existence of argument
    $arguments = _which_nodetype_arguments(); //use custom function to encapsulate
    if (!$which_type) {
        $which_type = drush_choice($arguments, dt('Which Example would you like to interact with using \'PHP-Coder\'?'));
    }

  // Check for correct argument
  $correct_args = array_keys($arguments);
  if (!in_array($which_type, $correct_args)) {
    if ($which_type == '0') {
      drush_user_abort('Buh-Bye! sqlViews Gather Node!');
      return;
    }
    $string = _which_type_arguments('string');
    return drush_set_error(dt('"@type" is not a valid example. ',
      array('@type' => $example)) . $string);
  }

  // drush_print($which_type);
  // return;
  _do_instantiate_field_objects($which_type);
} //END function drush_node_tablelist($which_list = FALSE)

function drush_sqlviews_sql_view_code($which_type = FALSE) {
//drush_mymodule_custom_save_node
  // Check for existence of argument
    $arguments = _which_nodetype_arguments(); //use custom function to encapsulate
    if (!$which_type) {
        $which_type = drush_choice($arguments, dt('Which Example would you like to interact with using \'PHP-Coder\'?'));
    }

  // Check for correct argument
  $correct_args = array_keys($arguments);
  if (!in_array($which_type, $correct_args)) {
    if ($which_type == '0') {
      drush_user_abort('Buh-Bye! sqlViews Gather Node!');
      return;
    }
    $string = _which_type_arguments('string');
    return drush_set_error(dt('"@type" is not a valid example. ',
      array('@type' => $example)) . $string);
  }

  // drush_print($which_type);
  // return;
  _do_sql_view_code($which_type);
} //END function drush_node_tablelist($which_list = FALSE)

function _which_nodetype_arguments($which = 'array'){
  $which_arguments = array();
  $node_types_array = node_type_get_types();
  foreach ($node_types_array as $key => $attribute_array) {
    $which_arguments[$key] = $attribute_array->name;
  }
  // $which_arguments['list'] = "Help Choice for Node Table List 'List' argument.";
  // $which_arguments['groupby'] = "Help Choice for Node Table List 'GroupBy' argument.";
  // $which_arguments['cube'] = "Help Choice for Node Table List 'Cube' argument.";

  switch ($which) {
    case 'array':
      return $which_arguments;
      break;
    case 'string':
      $correct_args = array_keys($which_arguments);
      $correct_args_count = count($correct_args);
      $first_args = $correct_args;
      $last_arg = '"' .  array_pop($first_args) . '"';
      $first_args_list = implode(",", $first_args);
      $first_args_list = '"' . str_replace(",", '", "', $first_args_list) . '"';
      $zero = 'Please ask for assistance, there are currently no php_coder examples in use';
      $non_zero = 'Please select';
      $grammar = $correct_args_count > 2?' among ':': ';
      $grammar = $correct_args_count == 2?' between ':$grammar;
      $list = '';
      $list = $correct_args_count == 1?$last_arg:$list;
      $list = $correct_args_count > 1?$first_args_list. ' and ' . $last_arg:$list;
      if ($correct_args_count == 0) {
        $string = $zero;
      }else{
        $string = $non_zero . $grammar . $list . '. (Or supply no example and select from prompted values.)';
      }
      return $string;
      break;

    default:
      return $which_arguments;
      #\_ OOAAOC notwithstanding default $which, this is its raison detre
      break;
  }
  return; //OOAAOC
}

/**
 * NOT in Module (see if it works)
 */

function _do_developer_vardump(){
  $header = 'Result of ' . __FUNCTION__ . '(' . ")\r\n==========\r\n";

  $which = 'FieldPreOb';
  // $which = 'SQL';

  if ($which == 'FieldPreOb') {
    $type_machine_name = 'project_app_gp';
    $node_type = new nodeTypeSQL($type_machine_name);
    $node_type->label_option = 'machine_abbrv';
    $node_type->gatherObjectReadyFieldArray();
    $field_preobject_array = $node_type->field_preobject_array;

    $field_name_array = array('field_app_references');
    foreach ($field_preobject_array as $key => $field_array) {
      if (in_array($key, $field_name_array)) {
        $output[$key] = $field_array;
      }
    }
    $result = $header . print_r($output, TRUE);
    drush_print($result);
    return;
  }




  $before = <<<CODEREH
SELECT
n.title AS title
,
CODEREH;
  $between = <<<CODEREH

,n.nid as nid
,n.vid as vid
,FROM_UNIXTIME(n.created,'%b %e, %Y %l:%i:%s %p') as created
,FROM_UNIXTIME(n.changed,'%b %e, %Y %l:%i:%s %p') as changed
,u.name AS author

FROM node n
JOIN users u
ON u.uid = n.uid

CODEREH;
  $after = <<<CODEREH

WHERE n.type = 'project_app_gp'
GROUP BY n.nid
;
CODEREH;

  require_once 'src/nodeTypeSQL.php';

  $type_machine_name = 'project_app_gp';
  $node_type = new nodeTypeSQL($type_machine_name);
  $node_type->label_option = 'machine_abbrv';

  // $node_type->gatherFieldBundleSettings();
  // $output = $node_type->field_bundle_settings;

  // $node_type->gatherWeightedFieldArray();
  // $output = $node_type->weighted_field_array;

  // $node_type->gatherObjectReadyFieldArray();
  $node_type->composeSelectStringFields_JoinStringFields();
  // $instances = $node_type->field_bundle_settings;
  // // $output = $node_type->field_bundle_settings;
  // $weighted_field_array = $node_type->weighted_field_array;
  // // $output = $node_type->weighted_field_array;

  // foreach ($weighted_field_array as $fieldname_this => $weighted_field_this){
  //     $instance_this = $instances[$fieldname_this];
  //     if ($instance_this->field->active == 1) {
  //       $output[$fieldname_this] = $instance_this;
  //     }
  // }
  // $result = $header . print_r($output, TRUE);
  // drush_print($result);
  // return;

  $field_name_array = array('field_app_references');
  // $output = $node_type->field_object_array;//[$field_name];

    foreach ($node_type->field_object_array as $index => $field_object_this) {
      if (1 == 2 && $field_object_this->field_name == $field_name) {
        $column_object_array_count = count($field_object_this->column_object_array) + 0;
        $columns_count = is_array($field_object_this->columns)?count($field_object_this->columns) + 0:7;
      }
      // if ($columns_count + $column_object_array_count != 0) {
      if (in_array($field_object_this->field_name, $field_name_array)) {
        $field_select_string_array[] = $field_object_this->field_select_list_string;
        $field_join_string_array[] = $field_object_this->field_join_string;
      }
    }
    $select_string_fields = implode("\r\n,", $field_select_string_array);
    $join_string_fields = implode("\r\n", $field_join_string_array);
    $output = $before . $select_string_fields . $between . $join_string_fields . $after;
  // $result = $header . print_r($select_string_fields, TRUE) . "\r\n\r\n" . print_r($join_string_fields, TRUE);
  $result = $header . $output;
  drush_print($result);
}

function _do_gather_node_type($type_machine_name){
  $header = 'Result of ' . __FUNCTION__ . '(' . $type_machine_name . ")\r\n==========\r\n";
  $node_types_array = node_type_get_types();
  $result = $header . print_r($node_types_array[$type_machine_name], TRUE);
  drush_print($result);
}

function _do_instantiate_node_type($type_machine_name){
  $header = 'Result of ' . __FUNCTION__ . '(' . $type_machine_name . ")\r\n==========\r\n";
  require_once 'src/nodeTypeSQL.php';
  $node_type = new nodeTypeSQL($type_machine_name);
  // $node_type->gatherNodeData();
  $node_type->gatherNodeTypeData();

  $result = $header . print_r($node_type, TRUE);
  drush_print($result);
}

function _do_instantiate_node_fields($type_machine_name){
  $header = 'Result of ' . __FUNCTION__ . '(' . $type_machine_name . ")\r\n==========\r\n";
  require_once 'src/nodeTypeSQL.php';
  $node_type = new nodeTypeSQL($type_machine_name);

  // $node_type->gatherFieldBundleSettings();
  // $output = $node_type->field_bundle_settings;

  // $node_type->gatherWeightedFieldArray();
  // $output = $node_type->weighted_field_array;

  $node_type->gatherObjectReadyFieldArray();
  $output = $node_type->field_preobject_array;

  $result = $header . print_r($output, TRUE);
  drush_print($result);
}

function _do_instantiate_field_objects($type_machine_name){

  $header = 'Result of ' . 'drush_get_option(dev' . ")\r\n==========\r\n";
  $dev_option = drush_get_option('dev', FALSE);
  // drush_print($header . print_r($dev_option, TRUE));
  // return;
  $label_option_default = 'label';
  $label_option = drush_get_option('label', $label_option_default);
  $header = 'Result of ' . __FUNCTION__ . '(' . $type_machine_name . ")\r\n==========\r\n";
  require_once 'src/nodeTypeSQL.php';
  $node_type = new nodeTypeSQL($type_machine_name);
  $node_type->label_option = $label_option;

  // $node_type->gatherFieldBundleSettings();
  // $output = $node_type->field_bundle_settings;

  // $node_type->gatherWeightedFieldArray();
  // $output = $node_type->weighted_field_array;

  // $node_type->instantiateFieldObjects();

  $node_type->composeSelectStringFields_JoinStringFields();
  $dev_result = '';
  if ($dev_option) {
    $dev_header = "\r\n\r\nDEVELOPER Result of " . __FUNCTION__ . '(' . $type_machine_name . ")\r\n==========\r\n";
    $dev_output = $node_type->field_object_array;
    $dev_result = $dev_header . print_r($dev_output, TRUE);
  }
  $output = $node_type->select_string_fields;
//select_string_fields
  $result = $header . print_r($output, TRUE);
  drush_print($result . $dev_result);
}


function _do_sql_view_code($type_machine_name){
  $label_option_default = 'label';
  // $label_option_default = 'label_machine';
  // $label_option_default = 'machine';
  // $label_option_default = 'machine_abbrv';
  $label_option = drush_get_option('label', $label_option_default);
  $header = 'Result of ' . __FUNCTION__ . '(' . $type_machine_name . ")\r\n==========\r\n";
  require_once 'src/nodeTypeSQL.php';
  // $node_type = new nodeTypeSQL($type_machine_name);
  $node_type_sql = new nodeTypeSQL($type_machine_name);
  $node_type_sql->label_option = $label_option;

  $node_type_sql->database = $databases['default']['default']['database'];
  $node_type_sql->composeViewString();

  $output = $node_type_sql->view_string;

  $result = $header . print_r($output, TRUE);
  drush_print($result);
}
