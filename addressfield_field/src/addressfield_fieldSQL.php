<?php

class addressfield_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
        $this->render_column_array = array('value','YIKES');
    }

    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new addressfield_fieldSQL($field_config_ob);
        return $return_field_object;
    }

    public function instantiateColumnObjects($field_array_this = array()) {
        $column_loop_array_overload = array(
            'first_name' => 1,
            'last_name' => 2,
            'name_line' => 3,
            'organisation_name' => 4,
            'thoroughfare' => 5,
            'premise' => 6,
            'locality' => 7,
            'administrative_area' => 8,
            'postal_code' => 9,
            'country' => 10,
            'sub_administrative_area' => 11,
            'dependent_locality' => 12,
            'sub_premise' => 13,
            'data' => 14,
         );
        $column_object_array = parent::instantiateColumnObjects($field_array_this, $column_loop_array_overload);
        return $column_object_array;
    } //END METHOD function instantiateColumnObjects($field_array_this = array())

} //END class addressfield_fieldSQL extends fieldSQL

