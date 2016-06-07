<?php
  $header_string = "Custom Report Title for '" . $report_string . "'";
  $header_sub = "Sphinx of black quartz, judge my vow. Sphinx of black quartz, judge my vow. Sphinx of black quartz, judge my vow. Sphinx of black quartz, judge my vow. Sphinx of black quartz, judge my vow. Sphinx of black quartz, judge my vow. Sphinx of black quartz, judge my vow. Sphinx of black quartz, judge my vow. ";
  /**
   * No Output Optons at this time
   *
   *
   */
    // $ouptut_query_option_array = array(3=>'Output Abbrviated Results',2=>'Output Full Results',1=>'Output Query',4=>'CSV Field Report');
    // $ouptut_query_option = drush_choice($ouptut_query_option_array, dt('ZWhich Bundle (Content Type) would you like to Report on?'));
    // if ($ouptut_query_option == '0') {
    //   $output = drush_user_abort($abort_string);
    //   die();
    // }
    // $output_query = $ouptut_query_option == 1 ? TRUE : FALSE;
    // $output_full = $ouptut_query_option == 2 ? TRUE : FALSE;
    // $output_abbrv = $ouptut_query_option == 3 ? TRUE : FALSE;
    // $output_csv = $ouptut_query_option == 4 ? TRUE : FALSE;
  /**
   * END No Output Optons at this time
   */

    $entity = 'node';
    // $bundle = 'project_app_gp';
    // $bundle = 'project_app_ts';
    // $bundle = 'project_app_fv';
    // $bundle = 'project_app_fs';


    $label_option_default = 'machine_abbrv';//moot?
    $label_option = drush_get_option('label', $label_option_default);
    $path = dirname(dirname(__FILE__));
    require_once $path . '/src/nodeTypeSQL.php';
    // require_once 'src/nodeTypeSQL.php';
    $node_type_sql = new nodeTypeSQL($bundle);
    $node_type_sql->label_option = $label_option;

    $node_type_sql->database = $databases['default']['default']['database'];
    $node_type_sql->gatherFieldsArrayToNodeType();
    $result_array = $node_type_sql;

    $output = print_r($result_array, TRUE);