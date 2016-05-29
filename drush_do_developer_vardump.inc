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
        'instantiate_field_array_DEV',
        'field_info_field_by_id_DEV',
        'schema_DEV',
        'FieldBundleSettings',
        'FieldPreOb',
        'FieldObjectArray',
        'reference_prof',
        'SQL',
        'field_reference_prof',
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
      // $which = 'FieldBundleSettings';
      // $which = 'FieldPreOb';
      // $which = 'FieldObjectArray';
      // $which = 'reference_prof';
      // $which = 'SQL';
      // $which = 'field_reference_prof';
      $which = 'instantiate_field_array_DEV';
      // $which = 'field_info_field_by_id_DEV';
      // $which = 'schema_DEV';
      /* \_ Un-Comment one above for default $which */
  }

  $header = 'Result of ' . __FUNCTION__ . '(' . $which . ')';
  $header_len = strlen($header);
  $header .= "\r\n";
  for ($i=0; $i < $header_len; $i++) {
    $header .= '=';
  }
  $header .= "\r\n";

if ($which == 'schema_DEV') {
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
}

if ($which == 'field_info_field_by_id_DEV') {
    $field_id_array = array(5,14);
    foreach ($field_id_array as $index => $field_id) {
      $result_array[] = field_info_field_by_id($field_id);
    }
    $result = $header . print_r($result_array, TRUE);
    drush_print($result);
    return;
}
if ($which == 'instantiate_field_array_DEV') {
      require_once 'src/nodeTypeSQL.php';
    $node_type = new nodeTypeSQL($type_machine_name);
    $node_type->label_option = $label_option;

    $node_type->gatherFieldsArrayToNodeType();
    $result_array = $node_type->field_object_array;
    $result = $header . print_r($result_array, TRUE);
    drush_print($result);
    return;
}


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

  if ($which == 'FieldBundleSettings') {

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
  // gatherFieldBundleSettings()

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
}
