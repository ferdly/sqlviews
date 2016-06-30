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
    switch ($limit_by_bundle_segment) {
        case 'INCEXP':
            self::$limit_byinclusion_field_tablename_array = array('field_data_field_app_orgexpense','field_data_field_app_projectexpense','field_data_field_app_projectincome_year1','field_data_field_app_projectincome_year2','field_data_field_app_orgincome_year1','field_data_field_app_orgincome_year2','field_data_field_app_projectincome','field_data_field_app_orgincome');
            break;
        case 'RMN':
            self::$limit_byinclusion_field_tablename_array = array('field_data_field_app_supp_narrative','field_data_field_app_fin_a','field_data_field_app_fin_b','field_data_field_confirm','field_data_field_app_fin_e','field_data_field_app_evaluation_a','field_data_field_app_evaluation_b','field_data_field_app_diversity_a','field_data_field_app_diversity_b','field_data_field_app_selpr_e','field_data_field_app_selpr_g','field_data_field_app_selpr_c','field_data_field_app_selpr_b','field_data_field_app_selpr_h','field_data_field_app_selpr_a','field_data_field_app_selpr_f','field_data_field_app_selpr_i','field_data_field_app_selpr_j','field_data_field_app_board_meetings','field_data_field_app_board_attendance');
            break;
        case 'ORG':
            self::$limit_byinclusion_field_tablename_array = array('field_data_field_app_org_name','field_data_field_app_org_name_aka','field_data_field_app_org_street','field_data_field_app_org_street2','field_data_field_app_org_city','field_data_field_app_org_state','field_data_field_app_org_zip','field_data_field_app_org_county','field_data_field_app_org_borough','field_data_field_app_org_legal','field_data_field_app_org_phone','field_data_field_app_org_fax','field_data_field_app_org_website','field_data_field_app_org_ein','field_data_field_app_org_founded','field_data_field_app_org_exempt','field_data_field_app_org_mission_history','field_data_field_app_org_mission_mission','field_data_field_app_org_mission_goals','field_data_field_app_org_mission_accomplish','field_data_field_app_org_activity_a','field_data_field_app_org_mission_supphist');
            break;
        case 'ART':
            self::$limit_byinclusion_field_tablename_array = array('field_data_field_app_art_title','field_data_field_app_art_aka','field_data_field_app_art_street','field_data_field_app_art_street2','field_data_field_app_art_city','field_data_field_app_art_state','field_data_field_app_art_zip','field_data_field_app_art_county','field_data_field_app_art_borough','field_data_field_app_art_legal','field_data_field_app_art_phone','field_data_field_app_art_fax','field_data_field_app_art_website','field_data_field_app_art_email','field_data_field_art_mission_a','field_data_field_art_mission_b','field_data_field_art_mission_c','field_data_field_art_mission_d','field_data_field_art_mission_e');
            break;
        case 'PROJ':
            self::$limit_byinclusion_field_tablename_array = array('field_data_field_application_type','field_data_field_app_project_title','field_data_field_app_proj_summary','field_data_field_app_proj_duration','field_data_field_app_proj_start','field_data_field_app_proj_end','field_data_field_app_proj_amt','field_data_field_app_proj_description','field_data_field_app_proj_keydates');
            break;
        case 'SPN':
            self::$limit_byinclusion_field_tablename_array = array('field_data_field_app_org_sponsor','field_data_field_app_org_sponsor_aka','field_data_field_app_spn_street','field_data_field_app_spn_street2','field_data_field_app_spn_city','field_data_field_app_spn_state','field_data_field_app_spn_zip','field_data_field_app_spn_county','field_data_field_app_spn_borough','field_data_field_app_spn_legal','field_data_field_app_spn_phone','field_data_field_app_spn_email','field_data_field_app_spn_fax','field_data_field_app_spn_website','field_data_field_app_spn_ein','field_data_field_app_spn_founded','field_data_field_app_spn_exempt','field_data_field_spn_mission_a','field_data_field_spn_mission_b','field_data_field_spn_mission_c','field_data_field_spn_mission_d');
            break;
        case 'SPN_C':
            self::$limit_byinclusion_column_tablename_array = array('field_data_field_contact_type','field_data_field_contact_name','field_data_field_phone','field_data_field_title','field_data_field_email');
            break;
        case 'SPN3':
            self::$limit_byinclusion_field_tablename_array = array('field_data_field_app_spn_city','field_data_field_app_spn_state','field_data_field_app_spn_zip');
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
