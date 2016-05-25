<?php

class field_collection_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
        $this->field_join_string = "\r\nJOIN_STRING_FOR_" . $this->field_name;
    }
}

