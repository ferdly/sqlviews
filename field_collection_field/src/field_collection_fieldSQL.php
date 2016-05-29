<?php

class field_collection_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
    }
    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new field_collection_fieldSQL($field_config_ob);

        $field_collection_ob = new stdClass();
        $field_collection_ob->entity = 'field_collection_item';
        $field_collection_ob->bundle = $field_config_ob->field_name;

        $return_field_object->field_field_object_array = fieldSQL::instantiate_fieldsFromEntityBundle($field_collection_ob);

        return $return_field_object;
    }
    public function zunpack_by_field_id() {
        $field_id = $this->id;
        $this->active = 1;
        $this->field_join_string = "\r\nUNPACKED_JOIN_STRING_FOR_" . $this->field_name;
    }

    function instantiateColumnObjects($field_array_this = array()) {
        $bundle = $field_array_this['field_name'];
        $field_config_instance_array =
        db_query('SELECT id, field_id, field_name, data, deleted FROM {field_config_instance} WHERE bundle = :bundle',
            array(':bundle' =>
            $this->type))->fetchAll();

        foreach ($field_config_instance_array as $index => $row) {
            $row->data = (object) unserialize($row->data);
            $field_config_this =
                db_query('SELECT * FROM {field_config} WHERE id = :field_id',
                    array(':field_id' =>
                    $row->field_id))->fetchObject();
            $field_config_this->data = (object) unserialize($field_config_this->data);
            $fields[$row->field_name]['instance'] = $row;
            $fields[$row->field_name]['field'] = $field_config_this;
            // $columns_this = gather_field_table_data($row->field_name);
            // $fields[$row->field_name]['columns'] = $columns_this;
            $fields[$row->field_name] = (object) $fields[$row->field_name];
        }
        $column_loop_array_overload = $fields;

        $column_loop_array_overloadz = array(
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

} //END class field_collection_fieldSQL extends fieldSQL
