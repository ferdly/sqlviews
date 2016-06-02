<?php

class field_collection_fieldSQL extends fieldSQL {

    public function __construct($field_array) {
        parent::__construct($field_array);
    }


    /**
     * Most Current OO from Local Static Method
     *
     *
     */

    public function instantiateFieldAndReturn($field_config_ob) {
        $return_field_object = new field_collection_fieldSQL($field_config_ob);

        $field_info_array = field_info_field_by_id($field_config_ob->field_id);
        $cardinality = $field_info_array['cardinality'];
        $field_collection_ob = new stdClass();
        $field_collection_ob->entity = 'field_collection_item';
        $field_collection_ob->bundle = $field_config_ob->field_name;
        $field_collection_ob->label_option = $field_config_ob->label_option;
        $field_collection_ob->foriegn_key_table = 'field_data_'.$field_config_ob->field_name;
        $field_collection_ob->entity_table_foriegnkey = $field_config_ob->field_name . '_value';
        $field_collection_ob->of_cardinality = $field_config_ob->of_cardinality * $cardinality;

        $return_field_object->field_field_object_array = fieldSQL::instantiate_fieldsFromEntityBundle($field_collection_ob);
        $return_field_object->field_select_is_hidden = 1;

        return $return_field_object;
    }

    // public function zunpack_join_string(){
    //     $join = 'LEFT JOIN ' . $this->table_name . ' ' . $this->table_alias;
    //     $on = 'ON ' . nodeTypeSQL::$all_table_alias_array[$this->of_entity] . '.' . $this->of_bundle . '_value' . ' = ' . $this->table_alias . '.entity_id';
    //     $this->field_join_string = $join . "\r\n" . $on;
    // }

    /**
     * END Most Current OO from Local Static Method
     */


    // public function zunpack_by_field_id() {
    //     $field_id = $this->id;
    //     $this->active = 1;
    //     $this->field_join_string = "\r\nUNPACKED_JOIN_STRING_FOR_" . $this->field_name;
    // }

    function Z_instantiateColumnObjects($field_array_this = array()) {
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
