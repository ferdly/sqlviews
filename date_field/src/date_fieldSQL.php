<?php

class date_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
        $this->field_select_is_hidden = 1;
    }


    /**
     * Most Current OO from Local Static Method
     *
     *
     */
    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new fieldSQL($field_config_ob);
        $value_one = fieldSQL::instantiateFieldAndReturn($field_config_ob);
        // $value_one = fieldSQL::instantiate_fieldsFromEntityBundle($field_config_ob);
        $field_config_ob->field_name .= '2';
        $value_two = fieldSQL::instantiateFieldAndReturn($field_config_ob);
        // $value_two = fieldSQL::instantiate_fieldsFromEntityBundle($field_config_ob);
        $return_field_object->field_field_object_array[] = $value_one;
        $return_field_object->field_field_object_array[] = $value_two;
        return $return_field_object;
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
