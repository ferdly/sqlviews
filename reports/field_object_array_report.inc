<?php


    $header_string = "Custom Report Title for '" . $report_string . "'";
    $header_sub = "Puzzel me this, Bat Man: Joker quietly faced six eyed villian gawker! Puzzel me this, Bat Man: Joker quietly faced six eyed villian gawker! Puzzel me this, Bat Man: Joker quietly faced six eyed villian gawker! Puzzel me this, Bat Man: Joker quietly faced six eyed villian gawker! Puzzel me this, Bat Man: Joker quietly faced six eyed villian gawker! ";

    $output_option_array = array(3=>'Output Abbrviated Results',2=>'Output Full Results',1=>'CSV Field Report');
    $output_option = drush_choice($output_option_array, dt('Which Output Option would you like rendered?'));
    if ($output_option == '0') {
      $output = drush_user_abort($abort_string);
      die();
    }
    $output_csv = $output_option == 1 ? TRUE : FALSE;
    $output_abbrv = $output_option == 3 ? TRUE : FALSE;

    $label_option_default = 'machine_abbrv';//moot?
    $label_option = drush_get_option('label', $label_option_default);
    $path = dirname(dirname(__FILE__));
    require_once $path . '/src/nodeTypeSQL.php';
    $node_type_sql = new nodeTypeSQL($bundle);
    $node_type_sql->label_option = $label_option;

    $node_type_sql->database = $databases['default']['default']['database'];
    $node_type_sql->gatherFieldsArrayToNodeType();
    // $node_type_sql->gatherWeightedFieldArray();


    // $pre_output = $node_type_sql->field_object_array;

    $pre_output = fieldSQL::gatherFieldObjectArrayRecursively($node_type_sql->field_object_array);
    // $result = $header . print_r($pre_output, TRUE);
    // // $result = $header . $output;
    // drush_print($result);
    // return;


    $output_fieldname_array = array();
    // $output_fieldname_array = array('body');
    // $output_fieldname_array = array('field_reference_prof');
    $output_attribute_array = array();
    // $output_attribute_array = array('weight');
    $output_limit_attribute_array = array(
      // 'field_name',
      // 'field_id',
      'id',
      // 'index',
      // 'weight',
      // 'field_column_name',
      // 'table_name',
      // 'label',
      // 'label_option',
      // 'table_alias',
      'field_select_list_string',
      // 'field_join_string',
      'field_config_instance_id',
      'field_config_id',
      'field_config_instance_deleted',
      'field_config_deleted',
      'field_config_instance_data',
      'field_config_data',
      // 'of_entity',
      // 'of_bundle',
      // 'of_foriegn_key_table',
      // 'of_foriegn_key',
      // 'of_cardinality',
      // 'type',
      // 'module',
      'active',
      'locked',
      // 'cardinality',
      // 'total_cardinality',
      'columns',
      'field_field_object_array',
      'column_object_array',
      'field_join_is_hidden',
      'field_select_is_hidden',
      ); #\_ ALL Above, uncomment to remove
    $output_limit_attribute_array = $output_abbrv ? $output_limit_attribute_array : array();
    $output_array = array();
    foreach ($pre_output as $index => $field_object_this) {
      $limit = FALSE;
      if (count($output_fieldname_array) == 0) {
        // $output_array[$index] = $field_object_this;
        $limit = TRUE;
      }
      elseif (in_array($field_object_this->field_name, $output_fieldname_array)) {
        // $output_array[$index] = $field_object_this;
        $limit = TRUE;
      }
      if ($limit) {
        $field_object_this->field_join_string = str_replace("\r\n", '|', $field_object_this->field_join_string);
        if (count($output_attribute_array) + count($output_limit_attribute_array) > 0) {
          foreach ($field_object_this as $key => $attribute) {
            if (count($output_attribute_array) > 0) {
              if ($key != 'field_name' && !in_array($key, $output_attribute_array)) {
                unset($field_object_this->$key);
              }
            }
            if (count($output_limit_attribute_array) > 0) {
              if ($key != 'field_name' && in_array($key, $output_limit_attribute_array)) {
                unset($field_object_this->$key);
              }
            }
          }
        }
        $output_array[$index] = $field_object_this;
      }
    }

  if ($output_csv) {
    $eol = "\r\n";
    $delim = ',';
    $csv_string = '';
    $csv_row = 'entity,bundle,table_name,field_column_name,cardinality';
    $csv_string .= $csv_row . $eol;
    foreach ($output_array as $key => $value) {
      $csv_row = '';
      $csv_row .= $value->of_entity . $delim;
      $csv_row .= $value->of_bundle . $delim;
      $csv_row .= $value->table_name . $delim;
      $csv_row .= $value->field_column_name . $delim;
      $csv_row .= $value->cardinality;// . $delim;
      $csv_string .= $csv_row . $eol;
    }
    $output = $csv_string;
  }else{
    $output = print_r($output_array, TRUE);
  }
