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

  $header = 'Result of ' . __FUNCTION__ . '(' . ")\r\n==========\r\n";

    // $require_base_path = __FILE__;
    // $result = $header . print_r($require_base_path, TRUE);
    // drush_print($result);
    // $require_base_path = str_replace(DRUPAL_ROOT, '', $require_base_path) ;
    // $result = $header . print_r($require_base_path, TRUE);
    // drush_print($result);
    // $require_base_path = str_replace(basename(__FILE__), '', $require_base_path) ;
    // // $require_base_path_array = explode('/', $require_base_path_array);
    // $result = $header . print_r($require_base_path, TRUE);
    // drush_print($result);
    // return;

  /*<Preset $type_machine_name> of course, can overload, but why?*/
  $type_machine_name = 'job_application';
  /*</Preset $type_machine_name>*/

  $supported_which_array = array(
        'FieldBundleSettings',
        'FieldPreOb',
        'FieldObjectArray',
        'reference_prof',
        'SQL',
    );
  if ($argument_which == 'which') {
    $arguments = array_combine($supported_which_array, $supported_which_array);
    $argument_which = drush_choice($arguments, dt('Which Example would you like to interact with using \'PHP-Coder\'?'));
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
      // $which = 'FieldBundleSettings';
      // $which = 'FieldPreOb';
      $which = 'FieldObjectArray';
      // $which = 'reference_prof';
      // $which = 'SQL';
  }

  if ($which == 'FieldBundleSettings') {
    drush_print('$which: ' . $which . ' [' . __LINE__ . ']');
    return;
    // $field_info_array = field_info_fields();
    // $result = $header . print_r($field_info_array, TRUE);
    // drush_print($result);
    // return;
    // $field_info = _field_info_field_cache();
    // $field_info = field_info_instance($entity_type, $field_name, $bundle_name)
    // $field_info = array();
    // foreach ($field_info_array as $key => $field_info_info_array) {
    //   $field_info[$key]['field_name'] = $field_info_info_array['field_name'];
    //   $field_info[$key]['type'] = $field_info_info_array['type'];
    //   $field_info[$key]['module'] = $field_info_info_array['module'];
    //   $field_info[$key]['columns'] = $field_info_info_array['columns'];
    //   $field_info[$key]['cardinality'] = $field_info_info_array['cardinality'];
    //   $field_info[$key]['active'] = $field_info_info_array['active'];
    //   $field_info[$key]['deleted'] = $field_info_info_array['deleted'];
    // }
            // [id] => 2
            // [field_name] => body
            // [type] => text_with_summary
            // [module] => text
            // [active] => 1
            // [locked] => 0
            // [cardinality] => 1
            // [deleted] => 0
            // [columns] => Array
    // $result = $header . print_r($field_info, TRUE);
    // drush_print($result);
    // return;

    require_once 'src/nodeTypeSQL.php';

    $node_type = new nodeTypeSQL($type_machine_name);
    $node_type->label_option = 'machine_abbrv';
    $node_type->gatherFieldBundleSettings();
    $field_bundle_settings = $node_type->field_bundle_settings;
    $result = $header . print_r($field_bundle_settings, TRUE);
    drush_print($result);
    return;

    $field_array = array();
    foreach ($field_bundle_settings as $key => $object_this) {
      $use = $object_this->field->active == 1 ? TRUE : FALSE;
      $use = $$object_this->field->deleted == 0 ? $use : FALSE;
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
  // gatherFieldBundleSettings()

  if ($which == 'FieldPreOb') {
    drush_print('$which: ' . $which . ' [' . __LINE__ . ']');
    return;
    // $type_machine_name = 'job_application';
    $type_machine_name = 'property';
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
    $output = $field_preobject_array;
    $result = $header . print_r($output, TRUE);
    drush_print($result);
    return;
  } //END if ($which == 'FieldPreOb')

  if ($which == 'FieldObjectArray') {
    drush_print('$which: ' . $which . ' [' . __LINE__ . ']');
    return;
    $type_machine_name = 'job_application';
    // $type_machine_name = 'property';
    $node_type = new nodeTypeSQL($type_machine_name);
    // $node_type->label_option = 'machine_abbrv';
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

  }
    drush_print('$which: ' . $which . ' [' . __LINE__ . ']');
    return;


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
