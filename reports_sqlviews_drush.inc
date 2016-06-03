<?php

function _do_reports_sqlviews_drush(){
  $print = drush_get_option('context', 0);
  $print = $print == 1 ? TRUE : FALSE;
  // $print = TRUE;
  $context = _render_drush_context_sqlviews($print);

  $dev = drush_get_option('dev', 0);
  $dev = $dev == 1 ? TRUE : FALSE;

  $abort_string = 'sqlViews Report Mechanism Cancelled!';//at least as default
  $argument_report = $context['drush']['arguments'][0];
  $argument_report = empty($argument_report) ? 'ZXZ' : $argument_report;

  $supported_report_array = array(
        'fieldObjectAsColumnParameter_DEV',
        'field_object_array',
        'field_info_field_by_id_DEV',
        'nodeTypeSQL_DEV',
        'schema_DEV',
        'FieldBundleSettings_DEV',
        'field_config_instance_array__db_select',

    );
  $prompt_for_bundle_report_array = array(
        'field_object_array',
        'field_config_instance_array__db_select',
    );

  if ($argument_report == 'ZXZ' || $argument_report == 'which') {
    $arguments = array_combine($supported_report_array, $supported_report_array);
    $argument_report = drush_choice($arguments, dt("Which Report would you like to run? \r\n('DEV' indicates unformated vardump at this time)"));
    if ($argument_report == '0') {
        drush_user_abort($abort_string);
        die();
    }
    }
  if (!in_array($argument_report, $supported_report_array)) {
      $report_key = $argument_report;
      if (ctype_digit($report_key)) {
        $report_key--;//for CANCEL offset
          $argument_report = $supported_report_array[$report_key];
          $report = empty($argument_report) ? 'ZXZXZXZ' : 'ZXZXZ';
      }else{
        $report = 'ZXZ';
      }
  }
  if (in_array($argument_report, $supported_report_array)) {
      $report = $argument_report;
  }else{
    return drush_set_error(dt('"@argument_report" is not a supported sqlViews Report. ',
      array('@argument_report' => $argument_report)));
  }
    // $argument_bundle = $context['drush']['arguments'][1];
    // $argument_bundle = empty($argument_bundle) ? 'ZXZ' : $argument_bundle;
    if (in_array($report, $prompt_for_bundle_report_array)) {
      $supported_bundle_array = _which_nodetype_arguments();
      #\_ use custom function to encapsulate
      $argument_bundle = drush_choice($supported_bundle_array, dt('Which Bundle (Content Type) would you like to Report on?'));
      if ($argument_bundle == '0') {
        drush_user_abort($abort_string);
        die();
      }
    $bundle = $argument_bundle;
    $bundle_string = $supported_bundle_array[$bundle];
   } //END if (in_array($report, $prompt_for_bundle_report_array))

  // $dev_param = $dev ? ', dev' : ''

  $dev_param = $dev ? " \r\n[as DEV expression]" : '';
  $dev_param = substr($report, -4) == '_DEV' ? " \r\n[as DEV expression]" : $dev_param;
  $report_string = ucwords(str_replace('_', ' ', str_replace('_DEV', '', $report)));
  $bundle_header_string = strlen($bundle) > 0 ? "' on Bundle: '" . $bundle_string . "'" : '';
  // $header = 'Result of ' . __FUNCTION__ . '(' . $report . $dev_param . ')';
  $header = "Report: '" . $report_string . $bundle_header_string;
  $header_len = strlen($header);
  $header .= $dev_param;
  $header .= "\r\n";
  for ($i=0; $i < $header_len; $i++) {
    $header .= '=';
  }
  $header .= "\r\n";

  if ($report == 'fieldObjectAsColumnParameter_DEV') {
    // drush_print($header);
    // drush_print('$report: ' . $report . '; $bundle: ' . $argument_bundle . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
    // return;

    $label_option_default = 'machine_abbrv';//moot?
    $label_option = drush_get_option('label', $label_option_default);
    require_once 'src/nodeTypeSQL.php';
    $node_type_sql = new nodeTypeSQL($bundle);
    $node_type_sql->label_option = $label_option;

    $node_type_sql->database = $databases['default']['default']['database'];
    $node_type_sql->gatherFieldsArrayToNodeType();
    $result_array = array();
    $field_object_array = $node_type_sql->field_object_array;
    foreach ($field_object_array as $index => $field_object_this) {
      $column_instantiation_array_array[$index] =
        $field_object_this->prepareColumnArrayForColumnInstantiation();
      // $column_instantiation_array_array[$index] =
      //   $field_object_this->gatherColumnArrayToField();

    } //END foreach ($field_object_array as $index => $column_array)
    $result_array = $column_instantiation_array_array;
    if (count($result_array) == 0) {
      $header .= "\r\nWhy Aren't These fieldSQL Objects:\r\n";
      $result_array = $field_object_array;
    }
    $result = $header . print_r($result_array, TRUE);
    // $result = $header . $output;
    drush_print($result);
    return;
  } //END if ($report == 'fieldObjectAsColumnParameter_DEV')




  if ($report == 'field_info_field_by_id_DEV') {
      drush_print($header);
      drush_print('$report: ' . $report . '; $bundle: ' . $argument_bundle . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
      return;

      $field_id_array = array(5,14);
      foreach ($field_id_array as $index => $field_id) {
        $result_array[] = field_info_field_by_id($field_id);
      }
      $result = $header . print_r($result_array, TRUE);
      drush_print($result);
      return;
  } //END if ($report == 'field_info_field_by_id_DEV')


  if ($report == 'nodeTypeSQL_DEV') {
    drush_print($header);
    drush_print('$r1eport: ' . $report . '; $bundle: ' . $argument_bundle . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
    return;

    $label_option_default = 'machine_abbrv';//moot?
    $label_option = drush_get_option('label', $label_option_default);
    require_once 'src/nodeTypeSQL.php';
    $node_type_sql = new nodeTypeSQL($type_machine_name);
    $node_type_sql->label_option = $label_option;

    $node_type_sql->database = $databases['default']['default']['database'];
    $node_type_sql->gatherFieldsArrayToNodeType();
    $result_array = $node_type_sql;
    // $field_object_array = $node_type_sql->field_object_array;
    // foreach ($field_object_array as $index => $field_object_this) {
    //   // $column_instantiation_array_array[$index] =
    //     // $field_object_this->prepareColumnArrayForColumnInstantiation();
    //   $column_instantiation_array_array[$index] =
    //     $field_object_this->gatherColumnArrayToField();

    // } //END foreach ($field_object_array as $index => $column_array)
    // $result_array = $column_instantiation_array_array;
    // if (count($result_array) == 0) {
    //   $header .= "\r\nWhy Aren't These fieldSQL Objects:\r\n";
    //   $result_array = $field_object_array;
    // }
    $result = $header . print_r($result_array, TRUE);
    // $result = $header . $output;
    drush_print($result);
    return;
  } //END if ($report == 'nodeTypeSQL_DEV')


  if ($report == 'schema_DEV') {
    drush_print($header);
    drush_print('$report: ' . $report . '; $bundle: ' . $argument_bundle . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
    return;

    require_once 'src/nodeTypeSQL.php';

    // $table_name = 'feather_marcy_chester_marais';
    // $result_array = table_alias_from_table_name($table_name);
    // $schema = drupal_get_schema();
    // $schema_tablenames = array_keys($schema);
    // $result_array = array_combine($schema_tablenames, $schema_tablenames);
    $result_array = best_table_alias_array();
    $result = $header . print_r($result_array, TRUE);
    drush_print($result);
    return;
  } //END if ($report == 'schema_DEV')


  if ($report == 'FieldBundleSettings_DEV') {
    drush_print($header);
    drush_print('$report: ' . $report . '; $bundle: ' . $argument_bundle . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
    return;

    require_once 'src/nodeTypeSQL.php';

    $node_type = new nodeTypeSQL($type_machine_name);
    $node_type->label_option = $label_option;
    $node_type->gatherFieldBundleSettings();
    $field_bundle_settings = $node_type->field_bundle_settings;
    $result = $header . print_r($field_bundle_settings, TRUE);
    drush_print($result);
    return;

    $field_array = array();
    foreach ($field_bundle_settings as $key => $object_this) {
      $use = $object_this->field->active == 1 ? TRUE : FALSE;
      $use = $object_this->field->deleted == 0 ? $use : FALSE;
      if ($use === TRUE) {
        $field_array[$key]['field_name'] = $object_this->field->field_name;
        $field_array[$key]['module'] = $object_this->field->module;
        $field_array[$key]['cardinality'] = $object_this->field->cardinality;
        // $field_array[$key]['active'] = $object_this->field->active;
        // $field_array[$key]['deleted'] = $object_this->field->deleted;
      }
    }

    $result = $header . print_r($field_array, TRUE);
    drush_print($result);
    return;
  } //END if ($report == 'FieldBundleSettings')




  // $path = 'reports/' . $report . '_report.inc';
  $path_info = __FILE__;
  $basename = basename(__FILE__);
  // $path_info = str_replace($basename, '', $path_info);
  $path_info = dirname(__FILE__);
  // $path = $path_info . 'README.md';
  $path = $path_info . '/reports/' . $report . '_report.inc';
  $file_exists = file_exists($path);
  $unsupported_path = '';
  if ($file_exists) {
    require $path;
    #\_ $output is ALWAYS the result, do any print_r() in the include
    $result = $header . $output;
    drush_print($result);
    return;
  }else{
    $unsupported_path = "; \$UNsupported_path: {$path}";
    // $path_info = dirname(__FILE__);
    // drush_print($path_info);
  }






  drush_print($header);
  drush_print("Unsupported Report!\r\n");
  drush_print('$report: ' . $report . '; $bundle: ' . $argument_bundle . $unsupported_path . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
  return;

}
