<?php

/**
 * Implements hook_drush_command().
 */
function sqlviews_drush_command() {
/**
 * Essential to the function of the Drush Command
 */
  $items['step-this'] = array(
    'aliases' => array(
      'step',
      ),
    'arguments' => array(
      'list' => 'is argument',
      'groupby' => 'is argument',
      'cube' => 'is argument',
    ),
    'options' => array(
      'orderby' => 'is option',
      'orderby_desc' => 'is option',
      'count' => 'is option',
      'content_types' => 'is option',
    ),
  );

/**
  * $items Append & Overload below
  * description ONLY here
  * examples ONLY here
  * aliases isn't associative so NEVER here
  * others fleshed out for HELP command
  */
$items['node-tablelist']['description'] = "Description php_coder: \r\nComposes SQL Code to apply Auto-Entry Label Titles to current titles. Useful when there is lots of data already entered before AEL implemented, or when the configuration of EAL is tweaked.";

$items['node-tablelist']['arguments']['list'] = "Longer description of Argument 'List'";
$items['node-tablelist']['arguments']['groupby'] = "Longer description of Argument 'GroupBy'";
$items['node-tablelist']['arguments']['cube'] = "Longer description of Argument 'Cube'";

$items['node-tablelist']['options']['orderby'] = "Longer description of Option 'OrderBy'";
$items['node-tablelist']['options']['orderby_desc'] = "Longer description of Option 'OrderBy DESC'";
$items['node-tablelist']['options']['count'] = "Longer description of Option 'Count'";
$items['node-tablelist']['options']['content_types'] = "Longer description of Option 'Content Types'";

$items['node-tablelist']['examples']['drush node-tablelist'] = 'Simply returns a listing of the nodes.';
$items['node-tablelist']['examples']['drush ntl'] = 'Using the alias, returns a listing of the nodes.';
$items['node-tablelist']['examples']['drush notable'] = 'Using the alias, returns a listing of the nodes.';


return $items;
}

/**
 * Callback for the drush-demo-command command
 */
function drush_sqlviews_step_this($which_list = FALSE) {
//drush_mymodule_custom_save_node
  // Check for existence of argument
    $arguments = _which_list_arguments(); //use custom function to encapsulate
    if (!$which_list) {
        $which_list = drush_choice($arguments, dt('Which Example would you like to interact with using \'PHP-Coder\'?'));
    }

  // Check for correct argument
  $correct_args = array_keys($arguments);
  if (!in_array($which_list, $correct_args)) {
    if ($which_list == '0') {
      drush_user_abort('Buh-Bye! Node Table List!');
      return;
    }
    $string = _which_list_arguments('string');
    return drush_set_error(dt('"@type" is not a valid example. ',
      array('@type' => $example)) . $string);
  }

  drush_print($which_list);
  return;
  // _drush_execute_node_tablelist($which_list);
} //END function drush_node_tablelist($which_list = FALSE)

function _which_list_arguments($which = 'array'){
  $which_arguments = array();
  $which_arguments['list'] = "Help Choice for Node Table List 'List' argument.";
  $which_arguments['groupby'] = "Help Choice for Node Table List 'GroupBy' argument.";
  $which_arguments['cube'] = "Help Choice for Node Table List 'Cube' argument.";

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
