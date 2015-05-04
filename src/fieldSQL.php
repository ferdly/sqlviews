<?php
class fieldSQL /* WILL SOON extend something*/ {
	/* <drupal/sql direct> */
	#\_ some may be vestigial ($index), but keep until no longer needed
	public $index;
	public $weight;
	public $field_name;
	public $table_name;
	public $label; 
	public $field_config_instance_id; 
	public $field_config_id;
	public $field_config_instance_deleted; 
	public $field_config_deleted;
	public $type;
	public $module;
	public $active;
	public $locked;
	public $cardinality;
	public $columns = array(); //Pre-Object Array
	/* </drupal/sql direct> */
	/* <to be UnPacked> */
	public $column_object_array = array();
	public $table_alias;
	public $field_select_list_string;
	public $field_join_string;
	/* </to be UnPacked> */

	function __construct($field_array) {
		if (is_array($field_array)) {
			foreach ($field_array as $key => $value) {
				# -> Some Way to limit to listed attributes (but should not be an issue)
				$this->$key = $value;
			}
		}
	}

	function un_pack($node_data_array) {
		$this->table_alias = 'ta' . $this->index;
		$space_string = ' ';
		$crlf_string = "\r\n"; //figure out globally
		$field_data_array = array();
		$field_data_array['country'] = $node_data_array['country'];
		$field_data_array['field_name'] = $this->field_name;
		$field_data_array['label'] = $this->label;
		$field_data_array['table_alias'] = $this->table_alias;
		$field_data_array['cardinality'] = $this->cardinality;
		$field_data_array['type'] = $this->type;
		$this->field_join_string = 'JOIN' . $space_string . $this->table_name . $space_string . $this->table_alias;
		$join_right_string = $node_data_array['entity_table_alias'] . '.' . $node_data_array['entity_table_foriegnkey'];
		$this->field_join_string .= $space_string . $crlf_string . 'ON' . $space_string . $join_right_string . ' = ' . $this->table_alias . '.' . 'entity_id';
		$column_select_string_array = array();
		$column_keys_to_skip_array = array('format','summary'); //believed to be reserved for body
		foreach ($this->column_object_array as $index => $column_object_this) {
			if (in_array($column_object_this->column_key, $column_keys_to_skip_array) !== true) {
				$this->column_object_array[$index]->un_pack($field_data_array);
				if (!empty($this->column_object_array[$index]->column_select_string)) {
					$column_select_string_array[] = $this->column_object_array[$index]->column_select_string;
				}
			}
		}
		$this->field_select_list_string = implode("\r\n,", $column_select_string_array);
	} //END function un_pack()

}