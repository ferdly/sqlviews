<?php

class markup_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
        $this->field_join_is_hidden = 1;
        $this->field_select_is_hidden = 1;
    }

    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new markup_fieldSQL($field_config_ob);
        return $return_field_object;
    }
    /**
     * Most Current OO from Local Static Method
     *
     *
     */


    /**
     * END Most Current OO from Local Static Method
     */
} //END class markup_fieldSQL extends fieldSQL
