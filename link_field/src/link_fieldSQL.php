<?php

class link_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
        $this->render_column_array = array('url');
    }

    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new link_fieldSQL($field_config_ob);
        return $return_field_object;
    }

    public function unpack_by_field_id() {
        parent::unpack_by_field_id();
        // $this->field_column_name = $this->field_name . '_url';
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
