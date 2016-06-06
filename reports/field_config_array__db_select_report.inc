<?php
  $header_string = "Custom Report Title for '" . $report_string . "'";
  $header_sub = "The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. The five boxing wizards jump quickly. ";
    $ouptut_query_option_array = array(3=>'Output Abbrviated Results',2=>'Output Full Results',1=>'Output Query',4=>'CSV Field Report');
    $ouptut_query_option = drush_choice($ouptut_query_option_array, dt('ZWhich Bundle (Content Type) would you like to Report on?'));
    if ($ouptut_query_option == '0') {
      $output = drush_user_abort($abort_string);
      die();
    }
    $output_query = $ouptut_query_option == 1 ? TRUE : FALSE;
    $output_full = $ouptut_query_option == 2 ? TRUE : FALSE;
    $output_abbrv = $ouptut_query_option == 3 ? TRUE : FALSE;
    $output_csv = $ouptut_query_option == 4 ? TRUE : FALSE;
    $entity = 'node';
    // $bundle = 'project_app_gp';
    // $bundle = 'project_app_ts';
    // $bundle = 'project_app_fv';
    // $bundle = 'project_app_fs';

    $instance_query = db_select('field_config_instance','fci')
            ->fields('fci',array('field_id','data'))
            // ->addField('fci', 'field_id')
            // ->addField('fci', 'data', 'fci_data')
            ->condition('entity_type', $entity)
            ->condition('bundle', $bundle)
            ->condition('deleted', 0);
    $field_config_instance_array = $instance_query->execute()
            ->fetchAll();

    /* <Critical>  to '$field_config_ob->field_config_instance_data' below*/
    foreach ($field_config_instance_array as $index => $fci_this) {
        $fci_array[$fci_this->field_id]['field_id'] = $fci_this->field_id;
        $fci_array[$fci_this->field_id]['field_name'] = $fci_this->field_name;
        $fci_array[$fci_this->field_id]['fci_data'] = $fci_this->data;
    }
    /* </Critical>*/

    $field_id_array = array_map(
      create_function('$o', 'return $o->field_id;'),
      $field_config_instance_array);

    // $output = print_r($field_config_instance_array, TRUE);
    $query = db_select('field_config','fc')
      ->fields('fc',array('id','field_name','type','module','cardinality','data'))
      ->condition('id', $field_id_array,'IN')
      ->condition('active', 1)
      ->condition('deleted', 0);
    $field_config_array = $query->execute()
      ->fetchAll();

    // $output = print_r($field_config_array, TRUE);
    // return;


    if ($output_query) {
      $output = strtr((string) $query, $query->arguments());
      /**
       * @todo investigate better way to remove table_name braces
       * @todo investigate better way to encapsulate strings in single quotes
       * * - dpq() was insufficient for both
       */
      $output = str_replace($entity, "'" . $entity . "'", $output);
      $output = str_replace($bundle, "'" . $bundle . "'", $output);

      $output = str_replace('}', '', str_replace('{', '', $output)) ."\r\n;";
      return;
    }

    $field_config_array = $query->execute()
            ->fetchAll();
    $i = 0;
    $output_array = array();
    foreach ($field_config_array as $index => $config_this) {
      $data =  unserialize($config_this->data);
      // $fci_data =  unserialize($fci_array[$config_this->id]['fci_data']);
      if (!$output_full) {
        #\_ entity,bundle,table_name,column_name(was field_name),cardinality
        $table_array = $data['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
        $table_name = is_array($table_array) ? key($table_array) : '';
        $column_name = @$table_array[$table_name]['value'];
        $output_array[$i]['field_name'] = $config_this->field_name;
        $output_array[$i]['entity'] = $entity;
        $output_array[$i]['bundle'] = $bundle;
        $output_array[$i]['table_name'] = $table_name;
        $output_array[$i]['column_name'] = $column_name;
        $output_array[$i]['cardinality'] = $config_this->cardinality;
      }else{
        $config_this->entity =  $entity;
        $config_this->bundle =  $bundle;
        $config_this->fci_data =  $fci_data;
        $config_this->data =  $data;
      }
      $i++;
    } //END foreach ($field_config_array as $index => $config_this)

    if ($output_full) {
        $output_array = $field_config_array;
      }

if ($output_csv) {
    $eol = "\r\n";
    $delim = ',';
    $csv_string = '';
    $csv_row = 'entity,bundle,table_name,field_column_name,cardinality';
    $csv_string .= $csv_row . $eol;
    foreach ($output_array as $index => $value) {
      $csv_row = '';
      $field_name = $value['field_name'];
      $csv_row .= $value['entity'] . $delim;
      $csv_row .= $value['bundle'] . $delim;
      $table_name = strlen($value['table_name']) == 0 ? 'UNKNOWN_TABLE_'. $field_name : $value['table_name'];
      $csv_row .= $table_name . $delim;
      $column_name = strlen($value['column_name']) == 0 ? 'UNKNOWN_COLUMN_' . $field_name : $value['column_name'];
      $csv_row .= $column_name . $delim;
      $csv_row .= $value['cardinality'];// . $delim;
      $csv_string .= $csv_row . $eol;
    }
    $output = $csv_string;
  // $output = 'CSV Output is Pending.';
  // $output = print_r($output_array, TRUE);
}else{
  $output = print_r($output_array, TRUE);
}
