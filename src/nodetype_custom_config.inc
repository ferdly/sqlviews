<?php


self::$limit_byinclusion_field_tablename_array = array();
self::$limit_byexclusion_field_tablename_array = array();
self::$limit_byinclusion_field_fieldname_array = array();
self::$limit_byexclusion_field_fieldname_array = array();
self::$limit_byinclusion_column_tablename_array = array();
self::$limit_byexclusion_column_tablename_array = array();
self::$limit_byinclusion_column_columnname_array = array();
self::$limit_byexclusion_column_columnname_array = array();

$type = $this->type;
$limit_by_bundle_segment = trim($this->limit_by_bundle_segment);

if ($this->type == 'project_app_gp') {
    self::$limit_byinclusion_field_fieldname_array = array('field_app_org_sponsor_value','field_app_spn_street_value','field_app_spn_street2_value','field_app_spn_city_value','field_app_spn_state_value','field_app_spn_zip_value');
    switch ($limit_by_bundle_segment) {
        case 'TST1':
            self::$limit_byinclusion_field_fieldname_array = array('field_app_org_sponsor_value','field_app_spn_street_value','field_app_spn_street2_value','field_app_spn_city_value','field_app_spn_state_value','field_app_spn_zip_value');
            break;
        default:
            $holder = 'no action';
            break;
    }
}

if ($this->type == 'founder_film') {
    // self::$limit_byinclusion_field_tablename_array = array('field_data_field_film_media_info');
    self::$limit_byexclusion_field_tablename_array = array('field_data_field_film_media_info');
    // self::$limit_byinclusion_field_fieldname_array = array('field_film_media_info');
    // self::$limit_byexclusion_field_fieldname_array = array('field_film_media_info');
    // self::$limit_byinclusion_column_tablename_array = array('field_data_field_film_media_info');
    // self::$limit_byexclusion_column_tablename_array = array('field_data_field_film_media_info');
    // self::$limit_byinclusion_column_columnname_array = array('field_film_media_info_value');
    // self::$limit_byexclusion_column_columnname_array = array('field_film_media_info_value');
    switch ($limit_by_bundle_segment) {
        case 'ff':
                self::$limit_byinclusion_field_tablename_array = array(
                    'field_data_field_film_media_info',
                    );

            break;

        default:
                self::$limit_byexclusion_column_columnname_array = array('field_film_media_info_value');

            break;
    }
}
