<?php

class columnSQL {

	/* <drupal/sql direct> */
	public $column_key;
	public $column_name;
	public $label;
	public $label_option;
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
	/* </to be UnPacked> */

	function __construct($column_array) {
		if (is_array($column_array)) {
			foreach ($column_array as $key => $value) {
				# -> Some Way to limit to listed attributes (but should not be an issue)
				$this->$key = $value;
			}
		}
	}

	function un_pack($field_data_array) {
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

	function un_pack_label(&$field_data_array) {
		$double_quote = '"';
		$label = trim($field_data_array['label']);
		$label_option = $this->label_option;
		switch ($label_option) {
			case 'label':
				$label_append = $field_data_array['cardinality'] + 0 < 0?' [#!]':'';
				$label_append = $field_data_array['cardinality'] + 0 > 1?' [#' . $field_data_array['cardinality'] . ']':$label_append;
				$label .= $label_append;
				$label .= $this->column_key == 'value'?'':'-' . ucwords(str_replace('_', ' ', $this->column_key));
				$label = isset($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', "'", $label);
				$label = $double_quote . $label . $double_quote;
				break;
			case 'label_machine':
				$label_append = $field_data_array['cardinality'] + 0 < 0?'_iE':'';
				$label_append = $field_data_array['cardinality'] + 0 > 1?'_i' . $field_data_array['cardinality']:$label_append;
				$label .= $label_append;
				$label .= $this->column_key == 'value'?'':'_' . ucwords(str_replace('_', ' ', $this->column_key));
				$label = isset($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
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
				// $label = isset($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
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
				// $label = isset($field_data_array['label_overload'])?$field_data_array['label_overload']:$label;
				$label = str_replace('"', '', $label);
				$label = str_replace("'", '', $label);
				$label = strtolower(str_replace(' ', '_', str_replace('-', '_', $label)));
				break;

			default:
				$holder = 'no default code, default checking logic above should kick-in';
				break;
		}
		$label = simple_sanatize_label($label);
		$this->label = $label;
	}

	function overloadLogic (&$field_data_array) {
		$type = $field_data_array['type'];
		$supported_type_array = array(
			'addressfield', '
			body',
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

			default:
				$holder = 'do nothing at this time (probably forever)';
				break;
		}
		return;
	}

	function overloadLogic_Body (&$field_data_array) {
		//'LEFT(' . $z . ', 25)'
		return;
	}
	function overloadLogic_AddressField (&$field_data_array) {
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

	}

}