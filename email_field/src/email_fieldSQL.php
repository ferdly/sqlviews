<?php

class email_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
    }

    public function unpack_by_field_id() {
        parent::unpack_by_field_id();
        $this->field_column_name = $this->field_name . '_email';
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
