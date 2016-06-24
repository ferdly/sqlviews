<?php

class columnSQL {

	/* <drupal/sql direct> */
	public $column_key;
	public $column_name;
	public $label;
	public $label_option;
	public $label_override;
	public $type;
	public $length;//number?
	public $size;//string?
	public $description;
	public $serialize = 0;
	// public $value; //just and instance of $column_key
	// public $format; //just and instance of $column_key
	/* </drupal/sql direct> */
	/* <to be UnPacked> */
	public $common_type;
	public $mask_open;
	public $mask_close;
	public $column_select_string;
	public $column_join_string;
	/* </to be UnPacked> */
	public $column_join_is_hidden = 1;
	public $column_select_is_hidden = 0;
	public $column_custom_config_is_limited = 0;

	function __construct($column_array) {
		if (is_array($column_array)) {
			foreach ($column_array as $key => $value) {
				# -> Some Way to limit to listed attributes (but should not be an issue)
				$this->$key = $value;
			}
		}
	}
/**
 * Most Current OO from Local Static Method
 *
 *
 */
public function instantiate_columnsFromField($field_object) {
	if (count($field_object->field_field_object_array) > 0) {
		// return array('columnSQL: Not Indicated for this Field (it _has_ fields)');
		return array();
	}
	$columns = $field_object->columns;
	// $supported_columns_key_array = array('value');
	$supported_columns_key_array = $field_object->render_column_array;
	$column_object_array = array();
	foreach ($columns as $column_key => $column_array) {
		if (in_array($column_key, $supported_columns_key_array)) {
			if ($field_object->field_column_name != $field_object->field_name . '_' . $column_key) {
				/**
				 * @circleback maybe remove the IF, just rewrite regardless
				 */
				$field_object->field_column_name = $field_object->field_name . '_' . $column_key;
			}
			$column_array = $field_object->prepareColumnArrayForColumnInstantiation();
			$column_array['column_key'] = $column_key;
			$column_object_this = new columnSQL($column_array);
			$column_object_this->unpack_label();
			$column_object_this->unpack_select_string();
			$column_object_this->unpack_column_is_limited();
			$column_object_array[] = $column_object_this;
		}
	}
	return $column_object_array;
}

	public function unpack_label($label_overload = '') {
		$double_quote = '"';
		$label = trim($this->label);
		$label = !empty($label_overload) ? $label_overload : $label;
		$label_option = $this->label_option;
		// $label_option = nodeTypeSQL::$static_label_option;
		// $label = nodeTypeSQL::$static_label_option;
		// $label = nodeTypeSQL::$static_label_option;
		switch ($label_option) {
			case 'label':
				$label_append = $this->cardinality + 0 < 0?' [#!]':'';
				$label_append = $this->cardinality + 0 > 1?' [#' . $this->cardinality . ']':$label_append;
				$label .= $label_append;
				$label .= $this->column_key == 'value'?'':'-' . ucwords(str_replace('_', ' ', $this->column_key));
				$label = !empty($label_overload)?$label_overload:$label;
				$label = str_replace('"', "'", $label);
				$label = $double_quote . $label . $double_quote;
				break;
			case 'label_machine':
				$label_append = $this->cardinality + 0 < 0?'_iE':'';
				$label_append = $this->cardinality + 0 > 1?'_i' . $field_data_array['cardinality']:$label_append;
				$label .= $label_append;
				$label .= $this->column_key == 'value'?'':'_' . ucwords(str_replace('_', ' ', $this->column_key));
				$label = !empty($label_overload)?$label_overload:$label;
				$label = str_replace('"', '', $label);
				$label = str_replace("'", '', $label);
				$label = strtolower(str_replace(' ', '_', str_replace('-', '_', $label)));
				break;
			case 'machine':
				$label = trim($this->column_name);// overloads above SWITCH
				$label_append = $this->cardinality + 0 < 0?'_iE':'';
				$label_append = $this->cardinality + 0 > 1?'_i' . $this->cardinality:$label_append;
				$label .= $label_append;
				// $label .= $this->column_key == 'value'?'':'_' . ucwords(str_replace('_', ' ', $this->column_key));
				// $label = !empty($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', '', $label);
				$label = str_replace("'", '', $label);
				$label = strtolower(str_replace(' ', '_', str_replace('-', '_', $label)));
				break;
			case 'machine_abbrv':
				$label = trim($this->column_name);// overloads above SWITCH
				$label_array = explode('_', $label);
				if ($label_array[0] == 'field') {
					$field = array_shift($label_array);
				}
				$last_index = count($label_array) - 1;
				if ($label_array[$last_index] == 'value') {
					$value = array_pop($label_array);
				}
				$label = implode('_', $label_array);
				$label_append = $this->cardinality + 0 < 0?'_iE':'';
				$label_append = $this->cardinality + 0 > 1?'_i' . $this->cardinality:$label_append;
				$label .= $label_append;
				// $label .= $this->column_key == 'value'?'':'_' . ucwords(str_replace('_', ' ', $this->column_key));
				// $label = !empty($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', '', $label);
				$label = str_replace("'", '', $label);
				$label = strtolower(str_replace(' ', '_', str_replace('-', '_', $label)));
 				break;

			default:
				$holder = 'no default code, default checking logic above should kick-in';
				break;
		}
		// $label = simple_sanatize_label($label);
		$this->label = $label;

	} //END function unpack_label()

	public function unpack_select_string() {
		$column_select_string = $this->table_alias . '.' . $this->column_name;
		$column_select_string .= ' AS ' . $this->label;
		$this->column_select_string = $column_select_string;
	}
    public function unpack_column_is_limited(){
        // No attempt to Reconcile Conflicts
        $tables_included = nodeTypeSQL::$limit_byinclusion_column_tablename_array;
        $tables_excluded = nodeTypeSQL::$limit_byexclusion_column_tablename_array;
        $columns_included = nodeTypeSQL::$limit_byinclusion_column_columnname_array;
        $columns_excluded = nodeTypeSQL::$limit_byexclusion_column_columnname_array;
        $table_is_excluded = in_array($this->table_name, $tables_excluded);
        $table_is_included = count($tables_included) == 0 ? TRUE : FALSE;
        $any_is_included = count($tables_included) + count($columns_included) == 0 ? TRUE : FALSE;
        $table_is_included = in_array($this->table_name, $tables_included) ? TRUE : $any_is_included;
        $column_is_excluded = in_array($this->column_name, $columns_excluded);
        $column_is_included = count($columns_included) == 0 ? TRUE : FALSE;
        $column_is_included = in_array($this->column_name, $columns_included) ? TRUE : $any_is_included;

        $is_limited = 1;
        $is_limited = $table_is_included ? 0 : $is_limited;
        $is_limited = $column_is_included ? 0 : $is_limited;
        $is_limited = $table_is_excluded ? 1 : $is_limited;
        $is_limited = $column_is_excluded ? 1 : $is_limited;
        // $is_limited = 0;
    	$this->column_custom_config_is_limited = $is_limited;
        return $this->column_custom_config_is_limited;
    }

	public function field_report_singleton($column_singleton_first_three_columns = 'defualt_entity,default_bundle,default_tablename,') {
		if ($this->column_select_is_hidden == 1) {
			return "/*Column Select Is Hidden*/\r\n";
		}
		if ($this->column_join_is_hidden == 0) {
			return "/*Column Join Is Not Hidden*/\r\n";
		}
		$field_report_singleton_result = $column_singleton_first_three_columns;
		// $field_report_singleton_result .= "Holder for {$this->column_name} Field Report Single Row";
		$field_report_singleton_result .= "{$this->column_name},";
		$field_report_singleton_result .= "{$this->total_cardinality}";
		$limited = "/*COLUMN LIMITED: " .$field_report_singleton_result . "*/\r\n";
        $limited = nodeTypeSQL::$devv === TRUE ? $limited : '';
		$field_report_singleton_result .= "\r\n";
		$field_report_singleton_result = $this->column_custom_config_is_limited == 1 ? $limited : $field_report_singleton_result;

		return $field_report_singleton_result;
	}

/**
 * END Most Current OO from Local Static Method
 */
	function Z_un_pack($field_data_array) {
		$double_quote = '"';
		$field_data_array = is_array($field_data_array)?$field_data_array:array();
		$this->overloadLogic($field_data_array);
		if (@$field_data_array['skip'] == 'TTRUE') {
			return;
		}
		$column_select_string = $field_data_array['table_alias'] . '.' . $this->column_name;
		// $column_select_string = $field_data_array['cardinality'] + 0 != 1?'group_concat(' . $column_select_string . ')':$column_select_string;
		// $column_select_string = $field_data_array['cardinality'] + 0 != 1?"CONCAT(IFNULL(" . $column_select_string . ", ''), ' [', CASE WHEN COUNT(" . $column_select_string . ") > 0 THEN CONCAT('+', CAST((COUNT(" . $column_select_string . ") - 1) AS CHAR)) ELSE '0' END, ']')":$column_select_string;
		// $label = $field_data_array['label'];
		// $label_append = $field_data_array['cardinality'] + 0 < 0?' [#!]':'';
		// $label_append = $field_data_array['cardinality'] + 0 > 1?' [#' . $field_data_array['cardinality'] . ']':$label_append;
		// $label .= $label_append;
		// $label .= $this->column_key == 'value'?'':'-' . ucwords(str_replace('_', ' ', $this->column_key));
		// $label = isset($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
		// $label = $double_quote . $label . $double_quote;

		// $this->label = $label;
		$this->un_pack_label($field_data_array);
		$label = $this->label;

		$column_select_string .= ' AS ' . $label;
		$this->column_select_string = $column_select_string;


	} //END function un_pack()

	function Z_un_pack_label(&$field_data_array) {
		// $label_overload = $field_data_array['label_overload'];
		$double_quote = '"';
		$label = trim($field_data_array['label']);
		// $label = !empty($label_overload) ? $label_overload : $label;
		$label_option = $this->label_option;
		switch ($label_option) {
			case 'label':
				$label_append = $field_data_array['cardinality'] + 0 < 0?' [#!]':'';
				$label_append = $field_data_array['cardinality'] + 0 > 1?' [#' . $field_data_array['cardinality'] . ']':$label_append;
				$label .= $label_append;
				$label .= $this->column_key == 'value'?'':'-' . ucwords(str_replace('_', ' ', $this->column_key));
				$label = !empty($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', "'", $label);
				$label = $double_quote . $label . $double_quote;
				break;
			case 'label_machine':
				$label_append = $field_data_array['cardinality'] + 0 < 0?'_iE':'';
				$label_append = $field_data_array['cardinality'] + 0 > 1?'_i' . $field_data_array['cardinality']:$label_append;
				$label .= $label_append;
				$label .= $this->column_key == 'value'?'':'_' . ucwords(str_replace('_', ' ', $this->column_key));
				$label = !empty($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', '', $label);
				$label = str_replace("'", '', $label);
				$label = strtolower(str_replace(' ', '_', str_replace('-', '_', $label)));
				break;
			case 'machine':
				$label = trim($this->column_name);// overloads above SWITCH
				$label_append = $field_data_array['cardinality'] + 0 < 0?'_iE':'';
				$label_append = $field_data_array['cardinality'] + 0 > 1?'_i' . $field_data_array['cardinality']:$label_append;
				$label .= $label_append;
				// $label .= $this->column_key == 'value'?'':'_' . ucwords(str_replace('_', ' ', $this->column_key));
				// $label = !empty($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', '', $label);
				$label = str_replace("'", '', $label);
				$label = strtolower(str_replace(' ', '_', str_replace('-', '_', $label)));
				break;
			case 'machine_abbrv':
				$label = trim($this->column_name);// overloads above SWITCH
				$label_array = explode('_', $label);
				if ($label_array[0] == 'field') {
					$field = array_shift($label_array);
				}
				$last_index = count($label_array) - 1;
				if ($label_array[$last_index] == 'value') {
					$value = array_pop($label_array);
				}
				$label = implode('_', $label_array);
				$label_append = $field_data_array['cardinality'] + 0 < 0?'_iE':'';
				$label_append = $field_data_array['cardinality'] + 0 > 1?'_i' . $field_data_array['cardinality']:$label_append;
				$label .= $label_append;
				// $label .= $this->column_key == 'value'?'':'_' . ucwords(str_replace('_', ' ', $this->column_key));
				// $label = !empty($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', '', $label);
				$label = str_replace("'", '', $label);
				$label = strtolower(str_replace(' ', '_', str_replace('-', '_', $label)));
				break;

			default:
				$holder = 'no default code, default checking logic above should kick-in';
				break;
		}
		// $label = simple_sanatize_label($label);
		$this->label = $label;
	}

	function Z_overloadLogic (&$field_data_array) {
		$type = $field_data_array['type'];
		$supported_type_array = array(
			'addressfield',
			'body',
			'field_collection',
			);
		if (in_array($type, $supported_type_array) === false) {
			return;
		}
		switch ($type) {
			case 'addressfield':
				$this->overloadLogic_AddressField($field_data_array);
				break;
			case 'body':
				$this->overloadLogic_Body($field_data_array);
				break;
			case 'field_collection':
				$this->overloadLogic_FieldCollection($field_data_array);
				break;

			default:
				$holder = 'do nothing at this time (probably forever)';
				break;
		}
		return;
	}

	function Z_overloadLogic_Body (&$field_data_array) {
		//'LEFT(' . $z . ', 25)'
		return;
	}

	function Z_overloadLogic_AddressField (&$field_data_array) {
		$toskip_column_key_array = array('country','sub_administrative_area','dependent_locality','sub_premise','name_line','data',);
		#\_ This MUST become aware of Settings and Country
		if (in_array($this->column_key, $toskip_column_key_array) === true) {
			$field_data_array['skip'] = 'TTRUE';
			return;
		}
		// ABOVE -- Quick Exit if To-Skip
		// BELOW -- Will do nothing if $column_key not in Switch (so above is not required)

		switch ($this->column_key) {
			case 'administrative_area':
				$field_data_array['label_overload'] = 'State';
				break;
			case 'locality':
				$field_data_array['label_overload'] = 'City';
				break;
			case 'postal_code':
				$field_data_array['label_overload'] = 'Zip';
				break;
			case 'thoroughfare':
				$field_data_array['label_overload'] = 'Address 1';
				break;
			case 'premise':
				$field_data_array['label_overload'] = 'Address 2';
				break;
			case 'organisation_name':
				$field_data_array['label_overload'] = 'Organization';
				break;
			case 'first_name':
				$field_data_array['label_overload'] = 'First';
				break;
			case 'last_name':
				$field_data_array['label_overload'] = 'Last';
				break;

			default:
				$holder = 'do nothing at this time (probably forever)';
				break;
		}

	} //END function overloadLogic_AddressField (&$field_data_array)

	function Z_overloadLogic_FieldCollection (&$field_data_array) {
		$field_data_array['label'] .= '_fcz';
		return;
	}

}