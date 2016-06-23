<?php

function _do_developer_vardump(){
  $print = drush_get_option('context', 0);
  $print = $print == 1 ? TRUE : FALSE;
  // $print = TRUE;
  $context = _render_drush_context_sqlviews($print);
  $options = $context['custom']['options'];
  $argument_which = $context['drush']['arguments'][0];
  $argument_which = empty($argument_which) ? 'ZXZ' : $argument_which;
  // $which = $argument_which;
  // drush_print('$which: ' . $which . ' [' . __LINE__ . ']');
  // return;

  /*<Preset $type_machine_name> of course, can overload, but why?*/
  $type_machine_name = 'job_application';
  // $type_machine_name = 'property';
  /*</Preset $type_machine_name>*/
  /*<Preset $label_option> of course, can overload, but why?*/
  $label_option = 'machine_abbrv';
  /*</Preset $label_option>*/
  $supported_which_array = array(
        'cleared out see reports for archived devv too',
    );
  if ($argument_which == 'which') {
    $arguments = array_combine($supported_which_array, $supported_which_array);
    $argument_which = drush_choice($arguments, dt('Which Object-Attribute would you like to \'Developer-Vardump\'?'));
    if ($argument_which == '0') {
        drush_user_abort('Buh-Bye! Developer-Vardump Which-Which!');
        return;
    }
    }
  if (!in_array($argument_which, $supported_which_array)) {
      $which_key = $argument_which;
      if (ctype_digit($which_key)) {
        $which_key--;
          $argument_which = $supported_which_array[$which_key];
          $which = empty($argument_which) ? 'ZXZXZXZ' : 'ZXZXZ';
      }else{
        $which = 'ZXZ';
      }
  }
  if (in_array($argument_which, $supported_which_array)) {
      $which = $argument_which;
  }else{
      // $which = 'cleared out see reports for archived devv too';
      /* \_ Un-Comment one above for default $which */
  }
  $which = 'project_app_gp';
  $header = 'Result of ' . __FUNCTION__ . '(' . $which . ')';
  $header_len = strlen($header);
  $header .= "\r\n";
  for ($i=0; $i < $header_len; $i++) {
    $header .= '=';
  }
  $header .= "\r\n";

  $bundle = $which;
  $path = dirname(__FILE__);
  require_once $path . '/src/nodeTypeSQL.php';
  $node_type_sql = new nodeTypeSQL($bundle);
  $node_type_sql->label_option = $label_option;

  $node_type_sql->database = $databases['default']['default']['database'];
  $node_type_sql->composeFieldReport();

  $now_array = getdate();
  drush_print('Seconds: ' . print_r($now_array[seconds], TRUE));
  $index =$now_array[seconds] % 10;//1,3,4,5,7,9

  $field_this = $node_type_sql->field_object_array[$index];
  drush_print('$field_this: ' . print_r($field_this, TRUE));
  // $field_column_name = 'field_app_org_sponsor_value';
  $field_column_name = $field_this->field_column_name;
  // $table_name = 'field_data_field_app_org_sponsor';
  $table_name = $field_this->table_name;
  $is_limited_orig = $field_this->field_custom_config_is_limited;
  $is_limited_orig_string = $is_limited_orig ? '$is_limited_orig: TTRUE' : '$is_limited_orig: FFALSE';

  $is_limited_direct = $field_this->unpack_field_is_limited();
  /**
   * is_limited Method fieldSQL.php
   */
        $tables_included = nodeTypeSQL::$limit_byinclusion_field_tablename_array;
        $tables_excluded = nodeTypeSQL::$limit_byexclusion_field_tablename_array;
        $fields_included = nodeTypeSQL::$limit_byinclusion_field_fieldname_array;
        $fields_excluded = nodeTypeSQL::$limit_byexclusion_field_fieldname_array;
        $table_is_excluded = in_array($table_name, $tables_excluded);
        $table_is_included = count($tables_included) == 0 ? TRUE : FALSE;
        $any_is_included = count($tables_included) + count($fields_included) == 0 ? TRUE : FALSE;
        $table_is_included = in_array($table_name, $tables_included) ? TRUE : $any_is_included;
        // $field_is_excluded = in_array($this->field_name, $fields_excluded);
        $field_is_excluded = in_array($field_column_name, $fields_excluded);
        $field_is_included = count($fields_included) == 0 ? TRUE : FALSE;
        // $field_is_included = in_array($this->field_name, $fields_included) ? TRUE : $any_is_included;
        $field_is_included = in_array($field_column_name, $fields_included) ? TRUE : $any_is_included;

        $is_limited = 1;
        $is_limited = $table_is_included ? 0 : $is_limited;
        $is_limited = $field_is_included ? 0 : $is_limited;
        $is_limited = $table_is_excluded ? 1 : $is_limited;
        $is_limited = $field_is_excluded ? 1 : $is_limited;
        $any_is_included_string = $any_is_included ? '$any_is_included: TTRUE' : '$any_is_included: FFALSE';
        $table_is_included_string = $table_is_included ? '$table_is_included: TTRUE' : '$table_is_included: FFALSE';
        $field_is_included_string = $field_is_included ? '$field_is_included: TTRUE' : '$field_is_included: FFALSE';
        $table_is_excluded_string = $table_is_excluded ? '$table_is_excluded: TTRUE' : '$table_is_excluded: FFALSE';
        $field_is_excluded_string = $field_is_excluded ? '$field_is_excluded: TTRUE' : '$field_is_excluded: FFALSE';
        $is_limited_string = $is_limited !== 0 ? '$is_limited: TTRUE' : '$is_limited: FFALSE';
        $is_limited_direct_string = $is_limited_direct !== 0 ? '$is_limited_direct: TTRUE' : '$is_limited_direct: FFALSE';
        // $is_limited = $field_is_included ? 0 : 1;
        // $is_limited = 0;
  /**
   * is_limited Method fieldSQL.php
   */


  $output = 'limit_byinclusion_field_fieldname_array: ' . print_r($fields_included, TRUE);


  $result = $header . $output;
  drush_print($result);
  drush_print('$index: ' . $index . ' [FFALSE for: 1,3,4,5,7,9]');
  drush_print('$table_name: ' . $table_name);
  drush_print('$field_column_name: ' . $field_column_name);
  drush_print($any_is_included_string);
  drush_print($table_is_included_string);
  drush_print($field_is_included_string);
  drush_print($table_is_excluded_string);
  drush_print($field_is_excluded_string);
  drush_print($is_limited_string . '[' . $is_limited . ']');
  drush_print($is_limited_orig_string . '[' . $is_limited_orig . ']');
  drush_print($is_limited_direct_string . '[' . $is_limited_direct . ']');
  return;


  drush_print($header);
  drush_print("Unsupported Developer-Vardump \$which!\r\n");
  drush_print('$which: ' . $which . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
  return;
}
