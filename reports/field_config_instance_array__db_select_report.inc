<?php
    $ouptut_query_option_array = array(2=>'Output Results',1=>'Output Query');
    $ouptut_query_option = drush_choice($ouptut_query_option_array, dt('ZWhich Bundle (Content Type) would you like to Report on?'));
    if ($ouptut_query_option == '0') {
      $output = drush_user_abort($abort_string);
      die();
    }
    $output_query = $ouptut_query_option == 1 ? TRUE : FALSE;
    $entity = 'node';
    // $bundle = 'project_app_gp';
    // $bundle = 'project_app_ts';
    // $bundle = 'project_app_fv';
    // $bundle = 'project_app_fs';

    $query = db_select('field_config_instance','fci')
            ->fields('fci',array('field_id','data'))
            // ->addField('fci', 'field_id')
            // ->addField('fci', 'data', 'fci_data')
            ->condition('entity_type', $entity)
            ->condition('bundle', $bundle)
            ->condition('deleted', 0);
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

    $field_config_instance_array = $query->execute()
            ->fetchAll();

    foreach ($field_config_instance_array as $index => $config_instance_this) {
      $config_instance_this->data =  unserialize($config_instance_this->data);
    }


  $output = print_r($field_config_instance_array, TRUE);
