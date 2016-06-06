<?php

class date_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
        // $this->field_select_is_hidden = 1;
        $this->render_column_array = array('value','value2');
    }


    /**
     * Most Current OO from Local Static Method
     *
     *
     */
    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new date_fieldSQL($field_config_ob);
        // $return_field_object->field_config_data = $return_field_object->data;
        // $return_field_object->data = NULL;
        // // $value_one = fieldSQL::instantiateFieldAndReturn($field_config_ob);
        // $value_one = new date_fieldSQL($field_config_ob);
        // $value_one->field_select_is_hidden = 0;
        // $value_one->field_join_is_hidden = 1;
        // // $value_one = fieldSQL::instantiate_fieldsFromEntityBundle($field_config_ob);
        // $field_config_ob->field_column_name .= '2';
        // // $value_two = fieldSQL::instantiateFieldAndReturn($field_config_ob);
        // $value_two = new date_fieldSQL($field_config_ob);
        // $value_two->field_select_is_hidden = 0;
        // $value_two->field_join_is_hidden = 1;
        // // $value_two = fieldSQL::instantiate_fieldsFromEntityBundle($field_config_ob);
        // $return_field_object->field_field_object_array[] = $value_one;
        // $return_field_object->field_field_object_array[] = $value_two;
        return $return_field_object;
    }

    public function Z_unpack_by_field_id() {
        $field_config_data = unserialize($this->field_config_data);
        $todate = $field_config_data['settings']['todate'];
        $todate = isset($todate) ? $todate : 'nnull';
        $this->todate = $todate;
        if ($todate == 'nnull') {
            $this->render_column_array = array('value');
        }
        parent::unpack_by_field_id();
    }

    public function Z_instantiateColumnObjects($field_array_this = array()) {
        $column_loop_array_overload = array(
            'value' => 1,
            'value2' => 2,
            // 'first_name' => 1,
            // 'last_name' => 2,
            // 'name_line' => 3,
            // 'organisation_name' => 4,
            // 'thoroughfare' => 5,
            // 'premise' => 6,
            // 'locality' => 7,
            // 'administrative_area' => 8,
            // 'postal_code' => 9,
            // 'country' => 10,
            // 'sub_administrative_area' => 11,
            // 'dependent_locality' => 12,
            // 'sub_premise' => 13,
            // 'data' => 14,
         );
        $column_object_array = parent::instantiateColumnObjects($field_array_this, $column_loop_array_overload);
        return $column_object_array;
    } //END METHOD function instantiateColumnObjects($field_array_this = array())
    /**
     * END Most Current OO from Local Static Method
     */
} //END class markup_fieldSQL extends fieldSQL
