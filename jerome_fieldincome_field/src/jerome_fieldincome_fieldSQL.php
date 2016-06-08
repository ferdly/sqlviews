<?php

class jerome_fieldincome_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
        $this->render_column_array = array('jerome_fieldincome');
    }

    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new jerome_fieldincome_fieldSQL($field_config_ob);
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
