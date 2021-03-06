<?php

function Z_do_reports_sqlviews_drush(){
  $print = drush_get_option('context', 0);
  $print = $print == 1 ? TRUE : FALSE;
  // $print = TRUE;
  $context = _render_drush_context_sqlviews($print);

  $dev = drush_get_option('dev', 0);
  $dev = $dev == 1 ? TRUE : FALSE;

  $argument_report = $context['drush']['arguments'][0];
  $argument_report = empty($argument_report) ? 'ZXZ' : $argument_report;

  $supported_report_array = array(
        'fieldObjectAsColumnParameter_DEV',
        'field_object_array_DEV',
        'field_info_field_by_id_DEV',
        'nodeTypeSQL_DEV',
        'schema_DEV',
        'FieldBundleSettings_DEV',

    );
  if ($argument_report == 'ZXZ' || $argument_report == 'which') {
    $arguments = array_combine($supported_report_array, $supported_report_array);
    $argument_report = drush_choice($arguments, dt("Which Report would you like to run? \r\n('DEV' indicates unformated vardump at this time)"));
    if ($argument_report == '0') {
        drush_user_abort('sqlViews Report Mechanism Cancelled!');
        return;
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
    $argument_bundle = $context['drush']['arguments'][1];
    $argument_bundle = empty($argument_bundle) ? 'ZXZ' : $argument_bundle;
    $supported_bundle_array = _which_nodetype_arguments(); //use custom function to encapsulate
    if ($argument_bundle == 'ZXZ') {
        $argument_bundle = drush_choice($supported_bundle_array, dt('Which Bundle (Content Type) would you like to Report on?'));
    }

  $correct_args = array_keys($supported_bundle_array);
  if (!in_array($argument_bundle, $correct_args)) {
    if ($argument_bundle == '0') {
      drush_user_abort('sqlViews Report Mechanism Cancelled!');
      return;
    }
    $string = _which_nodetype_arguments('string');
    return drush_set_error(dt('"@bundle" is not a valid Bundle (Content Type). ',
      array('@bundle' => $argument_bundle)) . $string);
  }
  $bundle = $argument_bundle;
  $bundle_string = $supported_bundle_array[$bundle];

  // $dev_param = $dev ? ', dev' : ''

  $dev_param = $dev ? " \r\n[as DEV expression]" : '';
  $dev_param = substr($report, -4) == '_DEV' ? " \r\n[as DEV expression]" : $dev_param;
  $report_string = ucwords(str_replace('_', ' ', str_replace('_DEV', '', $report)));
  // $header = 'Result of ' . __FUNCTION__ . '(' . $report . $dev_param . ')';
  $header = "Report: '" . $report_string . "' on Bundle: '" . $bundle_string . "'";
  $header_len = strlen($header);
  $header .= $dev_param;
  $header .= "\r\n";
  for ($i=0; $i < $header_len; $i++) {
    $header .= '=';
  }
  $header .= "\r\n";



  if ($report == 'field_object_array_DEV'){
    drush_print($header);
    drush_print('$report: ' . $report . '; $bundle: ' . $argument_bundle . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
    return;

    $header = _render_header(__FUNCTION__, $type_machine_name, __LINE__);
    $label_option_default = 'machine_abbrv';//moot?
    $label_option = drush_get_option('label', $label_option_default);
    require_once 'src/nodeTypeSQL.php';
    $node_type_sql = new nodeTypeSQL($type_machine_name);
    $node_type_sql->label_option = $label_option;

    $node_type_sql->database = $databases['default']['default']['database'];
    $node_type_sql->gatherFieldsArrayToNodeType();
    // $node_type_sql->gatherWeightedFieldArray();

    $pre_output = $node_type_sql->field_object_array;
    $output_fieldname_array = array();
    // $output_fieldname_array = array('body');
    // $output_fieldname_array = array('field_reference_prof');
    $output = array();
    foreach ($pre_output as $index => $field_object_this) {
      if (count($output_fieldname_array) == 0) {
        $output[$index] = $field_object_this;
      }
      elseif (in_array($field_object_this->field_name, $output_fieldname_array)) {
        $output[$index] = $field_object_this;
      }
    }

    $result = $header . print_r($output, TRUE);
    // $result = $header . $output;
    drush_print($result);  return;
  } //END if ($report == 'field_object_array_DEV')


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
  } //END if ($which == 'FieldBundleSettings')


if ($which == 'composeSQL_Query_DEV') {
  $label_option_default = 'machine_abbrv';//moot?
  $label_option = drush_get_option('label', $label_option_default);
  require_once 'src/nodeTypeSQL.php';
  $node_type_sql = new nodeTypeSQL($type_machine_name);
  $node_type_sql->label_option = $label_option;
  nodeTypeSQL::$static_label_option = $label_option;
  $output = $node_type_sql->composeSQL_Query();
  // $output = nodeTypeSQL::$static_label_option;
  $result = $header . $output;
  drush_print($result);
  return;
} //END if ($which == 'composeSQL_Query_DEV')

if ($which == 'composeSQL_View_DEV') {
  $label_option_default = 'machine_abbrv';//moot?
  $label_option = drush_get_option('label', $label_option_default);
  require_once 'src/nodeTypeSQL.php';
  $node_type_sql = new nodeTypeSQL($type_machine_name);
  $node_type_sql->label_option = $label_option;
  nodeTypeSQL::$static_label_option = $label_option;
  $output = $node_type_sql->composeSQL_View();
  // $output = nodeTypeSQL::$static_label_option;
  $result = $header . $output;
  drush_print($result);
  return;
} //END if ($which == 'composeSQL_Query_DEV')

if ($which == 'new_select_join_array_collection_DEV') {
  $test = FALSE;
  if ($test) {
    $result_array = array('feather','marcy','chester','marais');
    $result_other = array('feather','marcy',);
    // $result_array['cats'] = array('petunia');
    // $result_other['dogs'] = array('feather','marcy',);
    // $result_other['cats'] = array('petunia','algonquin','chester');
    // // array_push($result_array, $result_other);
    $result_one = print_r($result_array);
    $result_two = print_r($result_other);
    $result_array = array_merge($result_array, $result_other);
    // $result_array['dogs'] = array_merge($result_array['dogs'], $result_other['dogs']);
    // $result_array['cats'] = array_merge($result_array['cats'], $result_other['cats']);
    $result_three = print_r($result_array);
    // // $result = $header . print_r($result_array, TRUE);
    $result = $header . $result_one . $result_two . $result_three;
    // // $result = $header . $output;
    drush_print($result);
    return;
  }
  $label_option_default = 'machine_abbrv';//moot?
  $label_option = drush_get_option('label', $label_option_default);
  require_once 'src/nodeTypeSQL.php';
  $node_type_sql = new nodeTypeSQL($type_machine_name);
  $node_type_sql->label_option = $label_option;

  $node_type_sql->database = $databases['default']['default']['database'];
  $node_type_sql->gatherFieldsArrayToNodeType();

  $field_object_array = $node_type_sql->field_object_array;
  // $select_array = array('chester');
  $select_array = array();
  $join_array = array();
  $i = 0;
  foreach ($field_object_array as $index => $field_object_this) {

    $select_result_array = $field_object_this->gatherSelect_this();
    $select_array = array_merge($select_array,$select_result_array);
    $join_result_array = $field_object_this->gatherJoin_this();
    $join_array = array_merge($join_array,$join_result_array);
    if ($i == -1) {
       break;
     }
     $i++;
  }
  $select_string = "\r\n, " . implode("\r\n, ", $select_array);
  $join_string = implode("\r\n", $join_array);
  // $result = $header . print_r($select_array, TRUE) . print_r($join_array, TRUE);
  $result = $header . $select_string . "\r\n\r\n" . $join_string;
  // $result = $header . $output;
  drush_print($result);
  return;
} //END if ($which == 'new_select_join_array_collection_DEV';) {

  if ($which == 'field_reference_prof') {
    $bundle = 'job_application';
    // $field_config_instance_array =
    // db_query('SELECT field_id FROM {field_config_instance} WHERE bundle = :bundle AND deleted = :deleted',
    //     array(
    //       ':bundle' =>$bundle,
    //       ':deleted' => 0,
    //     ))->fetchAll();
$field_config_instance_object_array = db_select('field_config_instance','fci')
    ->fields('fci',array('field_id'))
    ->condition('bundle',$bundle)
    ->execute()
    ->fetchAll();
    $field_id_array = array_map(
      create_function('$o', 'return $o->field_id;'),
      $field_config_instance_object_array);
    $result_array = $field_id_array;
    // foreach ($field_config_instance_array as $index => $row) {
      // $row->data = (object) unserialize($row->data);
      // $field_config_this =
          // db_query('SELECT * FROM {field_config} WHERE id = :field_id',
              // array(':field_id' =>
              // $row->field_id))->fetchObject();
      // $field_config_this->data = (object) unserialize($field_config_this->data);
      // unset($field_config_this->data);
      // $fields[$row->field_name]['instance'] = $row;
      // $fields[$row->field_name]['field'] = $field_config_this;
      // $columns_this = gather_field_table_data($row->field_name);
      // $fields[$row->field_name]['columns'] = $columns_this;
      // $fields[$row->field_name] = (object) $fields[$row->field_name];
    // }

    // $result = $header . print_r($field_config_instance_array, TRUE);
    // $result = $header . print_r($result_array, TRUE);
    $result = $header . print_r($result_array, TRUE);
    drush_print($result);
    return;
  }

  if ($which == 'FieldPreOb') {

    $node_type = new nodeTypeSQL($type_machine_name);
    $node_type->label_option = $label_option;
    $node_type->gatherObjectReadyFieldArray();
    $field_preobject_array = $node_type->field_preobject_array;
    $output_full = $field_preobject_array;

    $field_name_array = array('field_app_references');
    foreach ($field_preobject_array as $key => $field_array) {
      if (in_array($key, $field_name_array)) {
        $output[$key] = $field_array;
      }
    }
    $output_abbrv = $field_array;

    $result = $header;
    // $result .= "output_abbrv:\r\n=============\r\n" . print_r($output_abbrv, TRUE);
    $result .= "output_full:\r\n============\r\n" . print_r($output_full, TRUE);
    drush_print($result);
    return;
  } //END if ($which == 'FieldPreOb')

  if ($which == 'FieldObjectArray') {

    $node_type = new nodeTypeSQL($type_machine_name);
    $node_type->label_option = $label_option;
    $node_type->instantiateFieldObjects();
    $output_full = $node_type->field_object_array;
    // $output_full = $node_type->field_object_array->column_object_array;

    $output_abbrv = array();
    foreach ($node_type->field_object_array as $index => $field_object_this) {
      if ($field_object_this->field_name != 'body') {
        $field_join_string = empty($field_object_this->field_join_string) ? 'EEMPTY' : $field_object_this->field_join_string;
        $output_abbrv[$field_object_this->field_name]['field_join_string'] = $field_join_string;
        $output_abbrv[$field_object_this->field_name]['column_object_array'] = $field_object_this->column_object_array;
      }
    }

    $result = $header;
    // $result .= "output_abbrv:\r\n=============\r\n" . print_r($output_abbrv, TRUE);
    $result .= "output_full:\r\n============\r\n" . print_r($output_full, TRUE);
    drush_print($result);
    return;
  } //END if ($which == 'FieldObjectArray')

  if ($which == 'reference_prof') {
    drush_print('$which: ' . $which . ' [' . __LINE__ . ']');
    return;
    $bundle = 'field_reference_prof';//$field_array_this['field_name'];
    $field_config_instance_array =
        db_query('SELECT id, field_id, field_name, data, deleted FROM {field_config_instance
          WHERE bundle = :bundle',
            array(':bundle' =>
            $bundle))->fetchAll();
    $output = $field_config_instance_array;
    $result = $header . print_r($output, TRUE);
    drush_print($result);
    return;

  } //END if ($which == 'reference_prof')

  if ($which == 'LEFTOVER') {
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
    $node_type->label_option = $label_option;

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
  } //END if ($which == 'LEFTOVER')

  drush_print($header);
  drush_print("Unsupported Report!\r\n");
  drush_print('$report: ' . $report . '; $bundle: ' . $argument_bundle . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
  return;

}
