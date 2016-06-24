<?php

/**
 * Implements hook_drush_command().
 */
function sqlviews_drush_command() {
/**
 * Essential to the function of the Drush Command
 */
  $items['field-report'] = array(
    'aliases' => array(
      'f-rpt',
      ),
    'arguments' => array(
      'which' => 'is argument',
    ),
    'options' => array(
      'bundle-segment' => 'is_option',
      'headers' => 'is option',
      'context' => 'is option',
      'count' => 'is option',
      'dev' => 'is option',
    ),
  );
  $items['custom_config-report'] = array(
    'aliases' => array(
      'cc-rpt',
      ),
    'arguments' => array(
      'which' => 'is argument',
    ),
    'options' => array(
      'bundle-segment' => 'is_option',
      'headers' => 'is option',
      'context' => 'is option',
      'dev' => 'is option',
    ),
  );
  $items['developer-vardump'] = array(
    'aliases' => array(
      'devv',
      ),
    'arguments' => array(
      'which' => 'is argument',
    ),
    'options' => array(
      'context' => 'is option',
      'dev' => 'is option',
    ),
  );
  $items['sql-view-code'] = array(
    'aliases' => array(
      'sqlv',
      ),
    'options' => array(
      'label' => 'is option',
      'view-name' => 'is option',
    ),
  );
  $items['sql-view-reports'] = array(
    'aliases' => array(
      'sqlv-rpt',
      'sqlv-rpts',
      ),
    'arguments' => array(
      'report' => 'is argument',
      'bundle' => 'is argument',
    ),
    'options' => array(
      'context' => 'is option',
      'dev' => 'is option',
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
  require_once 'drush_do_developer_vardump.inc';
  _do_developer_vardump();
} //END function drush_node_tablelist($which_list = FALSE)

function drush_sqlviews_field_report($which_type = FALSE) {
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
  _do_field_report($which_type);
} //END function drush_sqlviews_field_report($which_type = FALSE)

function drush_sqlviews_custom_config_report($which_type = FALSE) {
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
  _do_custom_config_report($which_type);
} //END function drush_sqlviews_custom_config_report($which_type = FALSE)

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

function drush_sqlviews_sql_view_reports() {
  require_once 'reports_sqlviews_drush.inc';
  _do_reports_sqlviews_drush();
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
        $string = $non_zero . $grammar . $list . '. (Or supply none and select from prompted values.)';
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

function _render_drush_context_sqlviews($print = FALSE) {
  $file_line = '[File: ' . basename(__FILE__) . '; Line: ' . __LINE . ';]';
  $print = $print !== TRUE ? FALSE : TRUE;

  $context = drush_get_context();
  $command = $context['command'];

  $argument_values = $command['arguments'];
  $argument_keys = array_keys($command['argument-description']);
  $count_argument_values = count($argument_values);
  $count_argument_keys = count($argument_keys);
  if ($count_argument_keys > $count_argument_values) {
    foreach ($argument_keys as $index => $key) {
      if (empty($argument_values[$index])) {
        $argument_values[$index] = "missing_argument";
      }
    }
  }
  if ($count_argument_values > $count_argument_keys) {
    foreach ($argument_values as $index => $value) {
      if (empty($argument_keys[$index])) {
        $argument_keys[$index] = "extra_arg_{$index}";
      }
    }
  }
  $option_keys = $command['options'];
  $option_values = $context['cli'];
  foreach ($option_keys as $key => $descr) {
    $option_array[$key] = empty($option_values[$key]) ? 'not_provided' : $option_values[$key];
  }


  $developer_friedly_array = array();
  $dfa = array();
  $dfa_drush = array();
  $dfa_drush['command'] = $command['command'];
  $dfa_drush['argument-description'] = $command['argument-description'];
  $dfa_drush['arguments'] = $command['arguments'];
  $dfa_drush['options'] = $command['options'];
  $dfa_drush['cli'] = $context['cli'];
  $dfa_drush['aliases'] = $command['aliases'];
  $dfa_custom = array();
  $hook = 'drush_' . $command['commandfile'] . '_';
  $hook .= str_replace('-', '_', $command['command-hook']) . '()';
  $dfa_custom['command_hook_function'] = $hook;
  $dfa_custom['arguments'] = array_combine($argument_keys, $argument_values);
  $dfa_custom['options'] = $option_array;
  $developer_friedly_array['drush'] = $dfa_drush;
  $developer_friedly_array['custom'] = $dfa_custom;
  if ($print) {

    $header = "Output from '" . __FUNCTION__ . "()':\r\n" . $file_line . "\r\n======================================\r\n";
    $output = print_r($developer_friedly_array, TRUE);
    drush_print($header . $output);
  }
  return $developer_friedly_array;
} //END function _render_drush_context_gr($print = FALSE)

function _render_header($function, $parameter_string = '', $line = 0) {
  $file_line = '[File: ' . basename(__FILE__) . '; Line: ' . $line . ';]' . "\r\n";
  $file_line = $line > 0 ? $file_line : '';
  $header = 'Result of ' . $function . '(' . $parameter_string . ")";
  // $header = 'Output from ' . $function . '(' . $parameter_string . ")"; //ALT
  $header_length = strlen($header);
  $underscore = '';
  $i = 0;
  while ($i < $header_length) {
    $underscore .= '=';
    $i++;
  }
  return $header . "\r\n" . $underscore . "\r\n" . $file_line;
}

function _do_field_report($type_machine_name){
  $print = drush_get_option('context', 0);
  $print = $print == 1 ? TRUE : FALSE;
  // $print = TRUE;
  $context = _render_drush_context_sqlviews($print);
  $headers = drush_get_option('headers', 0);
  $headers = $headers == 1 ? TRUE : FALSE;
  $dev = drush_get_option('dev', 0);
  $dev = $dev == 1 ? TRUE : FALSE;
  $bundle_segment = drush_get_option('bundle-segment', FALSE);
  $bundle_segment = $bundle_segment === TRUE ? '1' : $bundle_segment;

  $dev = drush_get_option('dev', 0);
  $dev = $dev == 1 ? TRUE : FALSE;

  $line = 0; //__LINE__;
  $header = _render_header(__FUNCTION__, $type_machine_name, $line);
  $label_option_default = 'machine_abbrv';//moot?
  require_once 'src/nodeTypeSQL.php';
  $limit_by_bundle_segment = $bundle_segment !== FALSE ? $bundle_segment : NULL;
  $node_type_sql = new nodeTypeSQL($type_machine_name, $limit_by_bundle_segment);
  if ($dev) {
    nodeTypeSQL::$devv = $dev;
  }
  $node_type_sql->label_option = $label_option;
  drush_print("Bundle-Segment: " . $bundle_segment);
  drush_print("THIS->Bundle-Segment: " . $node_type_sql->limit_by_bundle_segment);

  $node_type_sql->database = $databases['default']['default']['database'];
  $node_type_sql->composeFieldReport();

  $error_string = $node_type_sql->renderErrorArray($dev);
  if ($error_string !== FALSE) {
    $output = $error_string;
  }else{
    $headers_string = $headers ? "entity,bundle,table_name,field_name,cardinality\r\n" : '';;
    $output = $node_type_sql->view_string;
    $output = $headers_string . $output;
  }

  $result = $header . $output;
  drush_print($result);
}

function _do_custom_config_report($type_machine_name, $option_array = array()){
  $print = drush_get_option('context', 0);
  $print = $print == 1 ? TRUE : FALSE;
  // $print = TRUE;
  $context = _render_drush_context_sqlviews($print);
  $bundle_segment = drush_get_option('bundle-segment', FALSE);
  $bundle_segment = $bundle_segment === TRUE ? '1' : $bundle_segment;
  // $headers = $headers == 1 ? TRUE : FALSE;

  $dev = drush_get_option('dev', 0);
  $dev = $dev == 1 ? TRUE : FALSE;

  $line = 0; //__LINE__;
  $header = _render_header(__FUNCTION__, $type_machine_name, $line);
  $label_option_default = 'machine_abbrv';//moot?
  require_once 'src/nodeTypeSQL.php';
  $limit_by_bundle_segment = $bundle_segment !== FALSE ? $bundle_segment : NULL;
  $node_type_sql = new nodeTypeSQL($type_machine_name, $limit_by_bundle_segment);
  // drush_print("Bundle-Segment: " . $bundle_segment);
  drush_print("THIS->Bundle-Segment: " . $node_type_sql->limit_by_bundle_segment);
  $node_type_sql->label_option = $label_option;

  $node_type_sql->database = $databases['default']['default']['database'];
  // $node_type_sql->composeFieldReport();
  $report_string = '';
  /*<Just Brute Force> (for now) */
  $is_null_string = 'NNULL';
  $is_empty_array_string = 'EEMPTY_AARRAY';
  /*<NEXT> First*/
  $kind = 'field_tablename';
  $by = 'by_inclusion';
  $this_static_array = nodeTypeSQL::$limit_byinclusion_field_tablename_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<NEXT> Second*/
  $kind = 'field_tablename';
  $by = 'by_exclusion';
  $this_static_array = nodeTypeSQL::$limit_byexclusion_field_tablename_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<NEXT>*/
  $kind = 'field_fieldname';
  $by = 'by_inclusion';
  $this_static_array = nodeTypeSQL::$limit_byinclusion_field_fieldname_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<NEXT>*/
  $kind = 'field_fieldname';
  $by = 'by_exclusion';
  $this_static_array = nodeTypeSQL::$limit_byexclusion_field_fieldname_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<NEXT>*/
  $kind = 'column_tablename';
  $by = 'by_inclusion';
  $this_static_array = nodeTypeSQL::$limit_byinclusion_column_tablename_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<NEXT>*/
  $kind = 'column_tablename';
  $by = 'by_exclusion';
  $this_static_array = nodeTypeSQL::$limit_byexclusion_column_tablename_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<NEXT>*/
  $kind = 'column_columnname';
  $by = 'by_inclusion';
  $this_static_array = nodeTypeSQL::$limit_byinclusion_column_columnname_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<NEXT>*/
  $kind = 'column_columnname';
  $by = 'by_exclusion';
  $this_static_array = nodeTypeSQL::$limit_byexclusion_column_columnname_array;
  $isset = isset($this_static_array);
  $is_array = is_array($this_static_array);
  $count = count($this_static_array);
  $is_null = !$is_array && !$isset;
  $is_empty_array = $is_array && $count == 0;
  if ($is_array) {
      $list = implode(',', $this_static_array);
  }else{
    $list = '';
  }
  $final = $list;
  $final = $is_empty_array ? $is_empty_array_string : $final;
  $final = $is_null ? $is_null_string : $final;
  $limit[$kind][$by] = $final;
  /*<Just Brute Force> (for now) */
  foreach ($limit as $kind => $by_array) {
    foreach ($by_array as $by_key => $limit_list) {
      $report_string .= 'Limit ' . str_replace('_', ' ', $kind . ' ' . $by_key) . ": \r\n";
      $report_string .= $limit_list . "\r\n\r\n";
    }
  }

  $error_string = FALSE;//$node_type_sql->renderErrorArray($dev);
  if ($error_string !== FALSE) {
    $output = $error_string;
  }else{
    $output = $report_string;
    // $output = $headers_string . $output;
  }

  $result = $header . $output;
  drush_print($result);
}

function _do_sql_view_code($type_machine_name){
  $label_option_default = 'label';
  // $label_option_default = 'label_machine';
  // $label_option_default = 'machine';
  // $label_option_default = 'machine_abbrv';
  $label_option = drush_get_option('label', $label_option_default);
  $view_name_option = drush_get_option('view-name', '');
  $header = 'Result of ' . __FUNCTION__ . '(' . $type_machine_name . ")\r\n==========\r\n";
  require_once 'src/nodeTypeSQL.php';
  // $node_type = new nodeTypeSQL($type_machine_name);
  $node_type_sql = new nodeTypeSQL($type_machine_name);
  $node_type_sql->label_option = $label_option;
  if (strlen($view_name_option) > 0) {
    $node_type_sql->view_name = $view_name_option;
  }

  $node_type_sql->database = $databases['default']['default']['database'];
  // $node_type_sql->composeViewString();
  $node_type_sql->composeSQL_View();

  $output = $node_type_sql->view_string;

  $result = $header . print_r($output, TRUE);
  drush_print($result);
}
