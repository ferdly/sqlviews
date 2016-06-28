<?php

class nodeTypeSQL /* WILL SOON extends entityTypeSQL */ {
	/* <from Tables> */
	/* <Ooops!> NOT part of SQL */
	// var int $nid; //node table
	// var int $vid; //node table
	// var int $created; //node table
	// var int $changed; //node table
	/* </Ooops!> */
	/**
		BIG QUESTIONS: Instantiate Here or in Appropriate Method?

	*/
	public $database;
	public $entity = 'node';
	public $entity_table_name = 'node';
	public $entity_table_alias;
	public $entity_table_foriegnkey = 'nid';
	public $entity_type_table_name = 'node_type';
	public $type; //node table -- machine name
	public $title; //node table
	public $has_title; //node_type table
	public $title_label; //node_type table
	public $label_option;
	public static $static_label_option;
	public $type_name; //node_type table -- human readable name
	/* </from Tables> */
	/* <from Serialized Data> */
	public $field_bundle_settings = array(); //Table: variables; variables::name: field_bundle_settings_node__{node_type}
	/* </from Serialized Data> */
	/* <Loaded (or 'Unpackd') Data> */
	public $weighted_field_array = array();
	public $field_preobject_array = array();
	public $field_object_array = array(); // Array of Field Objects
	public $field_object_array_count = -99999;
	/* </Loaded (or 'Unpackd') Data> */
	/* <Code Only Data> */
	public $country = 'US';
	public $select_string_order = array();
	public $select_string_node;
	public $select_string_ids;
	public $select_string_stamps;
	public $select_string_user;
	public $select_string_fields;
	public $select_string;
	public $join_string_fields;
	public $join_string; //for users
	public $query_string;
	public $error_array = array();
	/* <Utility Code> */
	public $of_cardinality = 1;//for instantiation of cardinality in fields
	public static $drupal_core_field_type_module_array = null;
	public static $all_table_alias_array = null;
	public static $limit_byinclusion_field_tablename_array = null;
	public static $limit_byexclusion_field_tablename_array = null;
	public static $limit_byinclusion_field_fieldname_array = null;
	public static $limit_byexclusion_field_fieldname_array = null;
	public static $limit_byinclusion_column_tablename_array = null;
	public static $limit_byexclusion_column_tablename_array = null;
	public static $limit_byinclusion_column_columnname_array = null;
	public static $limit_byexclusion_column_columnname_array = null;
	public static $limit_by_bundle_segment;
	public static $count = FALSE;
	public static $devv = FALSE;
	/* </Utility Code> */

	/* <Return Code/Data> */
	public $view_name;
	public $view_string;
	/* </Return Code/Data> */

	public function __construct($type_machine_name, $limit_by_bundle_segment = NULL) {
		$this->type = $type_machine_name;
		$this->limit_by_bundle_segment = $limit_by_bundle_segment;
	    if (is_null(self::$all_table_alias_array)) {
        	self::$all_table_alias_array = best_table_alias_array();
    	}
	    if (is_null(self::$drupal_core_field_type_module_array)) {
        	self::$drupal_core_field_type_module_array = array(
	        'number',
	        'text',
	        'list',
	        'taxonomy',
	        'image',
	        'file',
	    	);
    	}
    	require_once 'nodetype_custom_config.inc';
	}

	public function gatherNodeData() {
		$label_option_supported_array = array(
			'label',
			'label_machine',
			'machine',
			'machine_abbrv',
			);
		// $label_option_default = 'label';
		// $label_option_default = 'label_machine';
		$label_option_default = 'machine';
		// $label_option_default = 'machine_abbrv';
		// dpm($this->label_option, 'form_label_option');
		$label_option = $this->label_option;
		self::$static_label_option = $this->label_option;
		$label_option = empty($label_option) ? $label_option_default : $label_option;
		$label_option = in_array($label_option, $label_option_supported_array) ? $label_option : $label_option_default;
		$this->label_option = $label_option;
		// dpm($this->label_option, 'managed_label_option');
		$nid_string = $this->label_option == 'label' ? '"NodeID"' : 'nid';
		$nid_string = $this->label_option == 'label_machine' ? 'node_id' : $nid_string;
		$vid_string = $this->label_option == 'label' ? '"RevisionID"' : 'vid';
		$vid_string = $this->label_option == 'label_machine' ? 'revision_id' : $vid_string;
		$this->select_string_ids = "n.nid as {$nid_string}\r\n,n.vid as $vid_string";
		$created_string = $this->label_option == 'label' ? '"Created"' : 'created';
		$changed_string = $this->label_option == 'label' ? '"Changed"' : 'changed';
		$this->select_string_stamps = "FROM_UNIXTIME(n.created,'%b %e, %Y %l:%i:%s %p') as {$created_string}\r\n,FROM_UNIXTIME(n.changed,'%b %e, %Y %l:%i:%s %p') as {$changed_string}";
		$author_string = $this->label_option == 'label' ? '"Author"' : 'author';
		$author_string = $this->label_option == 'machine' ? 'name' : $author_string;
		$this->select_string_user = 'u.name AS ' . $author_string;//constant user data (name, email, both, more?... eventually maybe a preference)
		$this->join_string = "JOIN users u \r\nON u.uid = n.uid\r\n"; // write it here if there is any non-field related Joins WITH TRAILING SPACE
		$field_config_instance_array = db_query('SELECT id, field_id, field_name, data FROM {field_config_instance} WHERE bundle = :bundle', array(':bundle' =>
		'many_fields'))->fetchAll();
		}
	public function gatherNodeTypeData() {
		if (empty($this->select_string_node)) {
			$this->gatherNodeData();
		}
		$node_type = db_query('SELECT * FROM {node_type} WHERE type = :type',
			array(':type' =>
			$this->type))->fetchObject();
		$this->has_title = $node_type->has_title;
		$title_label = trim($node_type->title_label);
		$machine_title_label = strtolower(str_replace(' ', '_', str_replace('-', '_', $title_label)));
		$title_label = $this->label_option == 'label' ? '"' . $title_label. '"' : $machine_title_label;
		$title_label = $this->label_option == 'machine' ? 'title' : $title_label;
		$title_label = $this->label_option == 'machine_abbrv' ? 'title' : $title_label;
		$title_label = simple_sanatize_label($title_label);
		$this->title_label = $title_label;


		// $sql = 'SELECT * FROM node_type WHERE type = ' . "'{$this->type}'";
		// $result['has_title'] = 1; // OF COURSE: will be dynamic from database
		// $result['title_label'] = 'Title Label Overload'; // OF COURSE: will be dynamic from database
		// $this->has_title = $result['has_title'];
		// $this->title_label = $result['title_label'];
		$this->entity_table_alias = substr($this->entity_table_name, 0, 1);
		$this->entity_table_foriegnkey = 'nid';
		$select_string_node = $this->has_title == 1?$this->entity_table_alias . ".title AS {$this->title_label}":'';
		$this->select_string_node = $select_string_node;
	} //END function gatherNodeTypeData()

	public function gatherFieldConfigInstanceData() {
		#\_ Will Replace gatherFieldBundleSettings()
		$sql = 'SELECT * FROM field_config_instance WHERE bundle = '. "'{$this->type}'";
	} //END function gatherFieldConfigInstanceData()

	public function gatherFieldData() {
		#\_ Will Replace gatherFieldBundleSettings()
		$sql = 'SELECT * FROM field_config_instance WHERE bundle = '. "'{$this->type}'";
	} //END function gatherFieldConfigInstanceData()

	public function gatherFieldBundleSettings(){
		if (isset($this->has_title) === false) {
			$this->gatherNodeTypeData();
		}
		$field_config_instance_array =
		db_query('SELECT id, field_id, field_name, data, deleted FROM {field_config_instance} WHERE bundle = :bundle AND deleted = :not_deleted',
			array(':bundle' =>
			$this->type,
			':not_deleted' =>
			0))->fetchAll();
			// 'many_fields'))->fetchAll();
		foreach ($field_config_instance_array as $index => $row) {
			$row->data = (object) unserialize($row->data);
				$field_config_this =
				db_query('SELECT * FROM {field_config} WHERE id = :field_id AND deleted = :not_deleted',
					array(':field_id' =>
					$row->field_id,
					':not_deleted' =>
					0))->fetchObject();
				$field_config_this->data = (object) unserialize($field_config_this->data);
				$fields[$row->field_name]['instance'] = $row;
				$fields[$row->field_name]['field'] = $field_config_this;
				// $columns_this = gather_field_table_data($row->field_name);
				// $fields[$row->field_name]['columns'] = $columns_this;
				$fields[$row->field_name] = (object) $fields[$row->field_name];
		}
		$this->field_bundle_settings = $fields;
		$this->validateFieldCodeRequire();
	}
	/**
	 * Most Current OO from Local Static Method
	 *
	 *
	 */

	public function validateFieldCodeRequire() {

		$field_bundle_settings = $this->field_bundle_settings;

	    $field_array = array();
	    $sqlviews_unsupported_module_array = array();
	    foreach ($field_bundle_settings as $key => $object_this) {
	      $used = $object_this->field->active == 1 ? TRUE : FALSE;
	      $used = $$object_this->field->deleted == 0 ? $used : FALSE;
	      $module = $object_this->field->module;
	      $supported = in_array($module, self::$drupal_core_field_type_module_array);
	      // $supported = in_array($module, $sqlviews_unsupported_module_array) ?
	      				TRUE : $supported;
	      if (!$supported) {
	      	$sqlviews_unsupported_module_array[$key] = $module;
	      }
	      if ($used === TRUE) {
	        $field_array[$key]['field_name'] = $object_this->field->field_name;
	        $field_array[$key]['module'] = $module;
	        $field_array[$key]['cardinality'] = $object_this->field->cardinality;
	        // $field_array[$key]['active'] = $object_this->field->active;
	        // $field_array[$key]['deleted'] = $object_this->field->deleted;
	      }
	    } //END foreach()
	    $require_base_path = __FILE__;
	    $require_base_path = str_replace(DRUPAL_ROOT, '', $require_base_path) ;
	    $require_base_path_array = explode('/', $require_base_path) ;
	    array_pop($require_base_path_array) ;
	    array_pop($require_base_path_array) ;
	    // $require_base_path = str_replace(basename(__FILE__), '', $require_base_path) ;
	    $require_base_path = implode('/',$require_base_path_array) . '/';
	    $i = 0;
	    foreach ($sqlviews_unsupported_module_array as $key => $module_name) {
	    	$file_name = $module_name . '_fieldSQL.php';
	    	$path = $module_name . '_field/src/';
	    	$full_path = DRUPAL_ROOT . $require_base_path . $path . $file_name;
	    	$module_exists = file_exists($full_path);
	    	if ($module_exists) {
	    		$this->field_bundle_settings[$key]->module_path = $full_path;
	    		require_once $full_path;
	    	}else{
	    		$this->error_array['field_module'][$i]['error_string_dev'] = "The code to manage the field, '{$key}', could not be included.[" . $require_base_path . $path . $file_name . ']';
	    		$this->error_array['field_module'][$i]['error_string'] = "The code to manage the field, '{$key}', could not be included.";
	    		$i++;
	    	}
	    }
	}

	public function gatherFieldsArrayToNodeType() {
		if(count($this->field_bundle_settings) == 0) {
			$this->gatherFieldBundleSettings();
		}
		if(count($this->error_array) > 0) {
			$this->view_string = print_r($this->error_array, TRUE);
			return;
		}
		// require_once 'fieldSQL.php';
		fieldSQL::$used_table_alias_array = array();
		$this->field_object_array = fieldSQL::instantiate_fieldsFromEntityBundle($this);
	}

	public function composeFieldReport($option_array = array()){
		if (count($this->field_object_array) == 0) {
			$this->gatherFieldsArrayToNodeType();
		}

	    $field_object_array = $this->field_object_array;
	    $field_report_buffer = '';
	    $crlf = "\r\n";// could become an option
	    $delimiter = ',';// coule become an option
	    // $double_quotes = '"';
	    // \_MOOT because no values have spaces, let along apostrophes
	    foreach ($field_object_array as $index => $field_object_this) {
	      $field_report_buffer .= $field_object_this->field_report_singleton();
	    }

	    // $result_array = $node_type->field_object_array;
	    // $result = $header . print_r($result_array, TRUE);
	    $this->view_string = $field_report_buffer;

	    return $this->view_string;
	}

	public function composeSQL_SelectAndJoin() {
		if (count($this->field_object_array) == 0) {
			$this->gatherFieldsArrayToNodeType();
		}
		$field_object_array = $this->field_object_array;
		$select_array = array();
		$join_array = array();
		$i = 0;
		foreach ($field_object_array as $index => $field_object_this) {
			$select_result_array = $field_object_this->gatherSelect_this();
			$select_array = array_merge($select_array,$select_result_array);
			$select_array = array_filter($select_array, function($v){return trim($v) !== '';});
			$select_array_unique = array_unique($select_array);
			if ($select_array !== $select_array_unique ) {
				$this->select_string = print_r($field_object_this, TRUE);
				return;
			}
			$join_result_array = $field_object_this->gatherJoin_this();
			$join_array = array_merge($join_array,$join_result_array);
		}
		$select_array = array_filter($select_array, function($v){return trim($v) !== '';});
		$this->select_string = "\r\n," . implode("\r\n,", $select_array);
		$join_array = array_filter($join_array, function($v){return trim($v) !== '';});
		$join_string = implode("\r\n", $join_array);
		// $join_string = $b = array_filter($a, function($v){return $v !== 0;});
		$this->join_string = $join_string;

	} //END public function composeSQL_Query()

	public function composeSQL_Query() {
		if (strlen($this->select_string) == 0) {
			$this->composeSQL_SelectAndJoin();
		}
		if (strlen($this->join_string) == 0) {
			#\_ should be moot, either both or neither
			$this->composeSQL_SelectAndJoin();
		}

		$space_string = ' ';
		$crlf_string = "\r\n"; // figure this out globally
		$query_string = '';
		$query_string .= 'SELECT' . $space_string . $crlf_string;
		$query_string .= 'n.title AS ' . $this->title_label;
		$query_string .= $this->select_string;
		// $query_string .= $crlf_string
  		$between = <<<CODEREH

,n.nid as nid
,n.vid as vid
,FROM_UNIXTIME(n.created,'%b %e, %Y %l:%i:%s %p') as created
,FROM_UNIXTIME(n.changed,'%b %e, %Y %l:%i:%s %p') as changed
,u.name AS author

FROM node n
JOIN users u
ON u.uid = n.uid

CODEREH;

		$query_string .= $between;
		$query_string .= $this->join_string;

	  $after = <<<CODEREH


WHERE n.type = '{$this->type}'
GROUP BY n.nid
;
CODEREH;

		$query_string .= $after;
		$query_string .= ''; // no ORDER BY
		$this->query_string = $query_string;

		return $this->query_string;
	} //END public function composeSQL_Query()

	public function composeSQL_View() {
		if (strlen($this->query_string) == 0) {
			$this->composeSQL_Query();
		}

		if (strlen($this->view_name) == 0) {
			$view_name = $this->type . '_' . strtoupper($this->entity) . '_VIEW';
			$view_name = 'sqlVIEW_' . $this->type . '_' . strtoupper($this->entity);
			$this->view_name = $view_name;
		}
		$space_string = ' ';
		$crlf_string = "\r\n"; // figure this out globally
		$view_string = '';
		$view_string .= $crlf_string . 'CREATE OR REPLACE VIEW' . $space_string;
		$view_string .= $this->view_name . $space_string . 'AS';
		$view_string .= $space_string . $crlf_string . $crlf_string . $this->query_string;
		$view_string .= $space_string . $crlf_string;// . ';';
		$view_string .= $space_string . $crlf_string . "/*END {$this->view_name} */";

		$this->view_string = $view_string;


		return $this->view_string;
	} //END public function composeSQL_View()

	public function renderErrorArray($dev = FALSE) {
		$dev = $dev === TRUE ? TRUE : FALSE;
		if (count($this->error_array) > 0) {
			// $output = 'There was an error ' . __FUNCTION__;
			// return $output;
			$output = 'The following errors were encountered:';
			// $output .= print_r($this->error_array, TRUE);
			foreach ($this->error_array as $key => $error_type_array) {
				if ($dev) {
					# code...
				}else{

				}
			$output .= "\r\n - $key";
				foreach ($error_type_array as $type => $error_string_array) {
					if ($dev) {
						$output .= "\r\n  -- {$error_string_array['error_string_dev']}";
					}else{
						$output .= "\r\n  -- {$error_string_array['error_string']}";
					}
				}
			}
			return $output;
		}else{
			return FALSE;
		}
	}

	/**
	 * END Most Current OO from Local Static Method
	 */

	public function Z_gatherWeightedFieldArray() {
		if(count($this->field_bundle_settings) == 0) {
			$this->gatherFieldBundleSettings();
		}
		if(count($this->error_array) > 0) {
			$this->view_string = print_r($this->error_array, TRUE);
			return;
	}
		$instances = $this->field_bundle_settings;
		foreach ($instances as $fieldname_this => $instance_this) {
			// $instance_weights[$fieldname_this] = $instance_this['display']['default']['weight']; //NOT widget-weight, pretty sure
			$instance_weights[$fieldname_this] = $instance_this->instance->data->display['default']['weight'] + 0;
			// $show = $instance_this->instance->data->display->default;
			// $show = $instance_this->instance->data->display['default']['weight'];
			// dpm($show, '$show');
			// die();
		}
		asort($instance_weights);
		/* </Loop through $instaces to get Weights where fieldname is key> */

		/* <Loop through $fields to get fieldnames> */
		// foreach ($fields as $index => $field_array) {
		// 	$field_name = $field_array['field_name'];
		// 	$field_index_array[$field_name] = $index;
		// }
		/* </Loop through $fields to get fieldnames> */
		/* <Loop through $instance_weights to Construct final Element> */
		$i = 0;
		foreach ($instance_weights as $fieldname_this => $weight_this) {
			$weighted_field_array[$fieldname_this]['index'] = $i;
			$weighted_field_array[$fieldname_this]['weight'] = $weight_this;
			$i++;
		}
		/* </Loop through $instance_weights to Construct final Element> */
		$this->weighted_field_array = $weighted_field_array;
		$this->field_object_array_count = count($weighted_field_array);
	} //END function gatherWeightedFieldArray()

	public function Z_gatherObjectReadyFieldArray() {
		if ($this->field_object_array_count < 0) {
			$this->gatherWeightedFieldArray();
		}
		if(count($this->error_array) > 0) {
			return;
		}
		$instances = $this->field_bundle_settings;
		// $fields = $this->field_bundle_settings['fields'];
		$weighted_field_array = $this->weighted_field_array;
		/* <Loop through $instaces to get Weights where fieldname is key> */
		foreach ($weighted_field_array as $fieldname_this => $weighted_field_this) {
			$instance_this = $instances[$fieldname_this];
			if ($instance_this->field->active == 1) {
				// $instance_this = empty($instance_this)?'EEMPTY':$instance_this;
				// dpm($instance_this, '$instance_this');

				$table_name = '';
				if (is_array($instance_this->field->data->storage['details']['sql']['FIELD_LOAD_CURRENT'])) {
					$table_name = key($instance_this->field->data->storage['details']['sql']['FIELD_LOAD_CURRENT']);
				}
				$table_data = array();
				$columns = array();
				if (!empty($table_name)) {
				$table_data = $instance_this->field->data->storage['details']['sql']['FIELD_LOAD_CURRENT'][$table_name];
					foreach ($table_data as $key => $value) {
						$columns[$key]['column_key'] = $key;
						$columns[$key]['column_name'] = $value;
					}
				}
				// $test_this = $instance_this->field->data->storage['details']['sql']['FIELD_LOAD_CURRENT'][$table_name];
				// dpm($test_this, '$test_this');
				$index = $weighted_field_array[$fieldname_this]['index'];
				$field_preobject_array[$fieldname_this]['index'] = $index;
				$field_preobject_array[$fieldname_this]['weight'] = $weighted_field_array[$fieldname_this]['weight'];
				$field_preobject_array[$fieldname_this]['field_name'] = $fieldname_this;
				$field_preobject_array[$fieldname_this]['label'] = $instance_this->instance->data->label;
				$field_preobject_array[$fieldname_this]['field_config_instance_id'] = $instance_this->instance->id;
				$field_preobject_array[$fieldname_this]['field_config_id'] = $instance_this->field->id;
				$field_preobject_array[$fieldname_this]['field_config_instance_deleted'] = $instance_this->instance->deleted;
				$field_preobject_array[$fieldname_this]['type'] = $instance_this->field->type;
				$field_preobject_array[$fieldname_this]['module'] = $instance_this->field->module;
				$field_preobject_array[$fieldname_this]['active'] = $instance_this->field->active;
				$field_preobject_array[$fieldname_this]['locked'] = $instance_this->field->locked;
				$field_preobject_array[$fieldname_this]['cardinality'] = $instance_this->field->cardinality;
				$field_preobject_array[$fieldname_this]['field_config_deleted'] = $instance_this->field->deleted;
				// $tablename = key($fields[$index]['storage']['details']['sql']['FIELD_LOAD_CURRENT']);
				$field_preobject_array[$fieldname_this]['table_name'] = $table_name; //$instance_this->field->data->storage['details']['sql']['FIELD_LOAD_CURRENT'][$table_name];
				// $table_data = $test_this;
				// // $table_data = $fields[$index]['storage']['details']['sql']['FIELD_LOAD_CURRENT'][$tablename];
				// $columns = $fields[$index]['columns'];
				// $columns_orig = $test_this;
				// foreach ($columns_orig as $column_key => $column_array) {
				//  	$columns[$column_key]['column_key'] = $column_key;
				//  	$columns[$column_key]['column_name'] = $columns[$column_key];
				//  }
				$field_preobject_array[$fieldname_this]['columns'] = $columns;
				//#$instance_this['description'] = 'AS COLUMN COMMENT';
				//#$instance_this['bundle'] must match $this->type -- but that is the point! -- too foundational to test;
			} //END if ($instance_this->field->active == 1)
		}
		$this->field_preobject_array = $field_preobject_array;
		#\_ FAUX for Testing this public functions REAL purpose is to explode the array and load into fieldSQL objects
	} //END function gatherObjectReadyFieldArray()

	public function Z_instantiateFieldObjects() {
		#\_ both __construct() and un_pack()
		if ($this->field_object_array_count != count($this->field_preobject_array)) {
			$this->gatherObjectReadyFieldArray();
		}
		if(count($this->error_array) > 0) {
			return;
		}
		require_once('fieldSQL.php');
		require_once('columnSQL.php');
		$node_data_array = array();
		$node_data_array['entity_table_alias'] = $this->entity_table_alias;
		$node_data_array['entity_table_foriegnkey'] = $this->entity_table_foriegnkey;
		$node_data_array['country'] = $this->country;
		$field_array = $this->field_preobject_array;
		foreach ($field_array as $fieldname_this => $field_array_this) {
			$is_core = in_array($field_array_this['module'], self::$drupal_core_field_type_module_array);
			if ($is_core) {
				$field_object_this = new fieldSQL($field_array_this);
			}else{
				$class_name = $field_array_this['module'] . '_fieldSQL';
				$field_object_this = new $class_name($field_array_this);
			}
			$field_object_this->label_option = $this->label_option;
			$field_object_this->column_object_array = $field_object_this->instantiateColumnObjects($field_array_this);
			$field_object_this->columns = 'NNULL';
		// 	$column_array = $field_object_this->columns;
		// 	if ($field_array_this['type'] == 'addressfield') {
		// 		$column_loop_array = array( 'first_name' => 1, 'last_name' => 2, 'name_line' => 3, 'organisation_name' => 4, 'thoroughfare' => 5, 'premise' => 6, 'locality' => 7, 'administrative_area' => 8, 'postal_code' => 9, 'country' => 10, 'sub_administrative_area' => 11, 'dependent_locality' => 12, 'sub_premise' => 13, 'data' => 14,);
		// 	}else{
		// 		$column_loop_array = $column_array;
		// 	}
		// 	foreach ($column_loop_array as $column_key => $column_array_this) {
		// 		$column_object_this = new columnSQL($column_array[$column_key]);
		// 		$column_object_this->label_option = $field_object_this->label_option;
		// 		$field_object_this->column_object_array[] = $column_object_this;
		// 		$field_object_this->columns = 'NNULL';
		// 	}
			$field_object_this->un_pack($node_data_array);
			$this->field_object_array[] = $field_object_this;
			// $this->field_preobject_array[$fieldname_this] = 'NNULL';
		} //END foreach ($field_array as $fieldname_this => $field_array_this)

	} //END function instantiateFieldObjects()

	public function Z_composeSelectStringFields_JoinStringFields() {
		if ($this->field_object_array_count != count($this->field_object_array)) {
			$this->instantiateFieldObjects();
		}
		if(count($this->error_array) > 0) {
			return;
		}
		if ($this->field_object_array_count == 0) {
			$this->select_string_fields = 'EEMPTY';
			$this->join_string_fields = 'EEMPTY';
		}
		/** Try New (more sophistacted construction) after Looping is Working
		$a = array_map(function($obj) { return $obj->foo; },
 			array(1=>$obj1 , 2=>$obj2 , 3=>$obj3));

		$a = implode(", ", $a);
		*/
		$field_select_string_array = array();
		$field_join_string_array = array();
		foreach ($this->field_object_array as $index => $field_object_this) {
			$column_object_array_count = count($field_object_this->column_object_array) + 0;
			$columns_count = is_array($field_object_this->columns)?count($field_object_this->columns) + 0:7;
			if ($columns_count + $column_object_array_count != 0) {
				$field_select_string_array[] = $field_object_this->field_select_list_string;
				$field_join_string_array[] = $field_object_this->field_join_string;
			}
		}
		$this->select_string_fields = implode("\r\n,", $field_select_string_array);
		$this->join_string_fields = implode("\r\n", $field_join_string_array);
	} //END function gatherSelectStringFields()

	public function Z_composeJoinString() {
		if (empty($this->join_string_fields)) {
			$this->composeSelectStringFields_JoinStringFields();
		}
		if(count($this->error_array) > 0) {
			return;
		}
		$join_string = $this->join_string;
		$join_string .= $this->join_string_fields == 'EEMPTY'?'':$this->join_string_fields;
		$this->join_string = $join_string;
		$this->join_string_fields = 'NNULL';
	} //END function composeJoinString()
	public function Z_composeSelectString() {
		if (empty($this->select_string_fields)) {
			$this->composeSelectStringFields_JoinStringFields();
		}
		if(count($this->error_array) > 0) {
			return;
		}

		// $select_string_node = ''; //"n.title as \"{$title_label}\"";
		// $select_string_ids = "n.nid as \"NodeID\"\r\n,n.vid as \"RevisionID\"";
		// $select_string_stamps = "FROM_UNIXTIME(n.created,'%b %e, %Y %l:%i:%s %p') as \"created\"\r\n,FROM_UNIXTIME(n.changed,'%b %e, %Y %l:%i:%s %p') as \"changed\"";
		// $select_string_user = 'u.name AS "Author"';//constant user data (name, email, both, more?... eventually maybe a preference)

		$default = array('node','fields','ids', 'stamps', 'user',);
		$select_string_order = is_array($this->select_string_order)?$this->select_string_order:array();
		$select_string_order = array_intersect($select_string_order, $default);// remove any stray values
		$append = array_diff($default, $select_string_order); // gather any unused default values
		$select_string_order = array_merge($select_string_order,$append);
		$buffer = print_r($select_string_order, true);
		// die($buffer);
		$this->select_string_order = $select_string_order;
		$select_string = '';
		$error = array();
		foreach ($select_string_order as $key => $value) {
			$comma = empty($select_string)?'':"\r\n,";
			switch ($value) {
				case 'node':
					$select_string .= $comma . $this->select_string_node;
					break;
				case 'fields':
					$select_string_fields = $this->select_string_fields == 'EEMPTY'?'':$this->select_string_fields;
					$select_string .= $comma . $select_string_fields;
					break;
				case 'ids':
					$select_string .= $comma . $this->select_string_ids;
					break;
				case 'stamps':
					$select_string .= $comma . $this->select_string_stamps;
					break;
				case 'user':
					$select_string .= $comma . $this->select_string_user;
					break;

				default:
					$error[] = $value; // SHOULD BE IMPOSSIBLE, so not Thrown (or Caught) at this time
					break;
			}
		}
		$this->select_string = $select_string;

	} //END function composeSelectString()

	public function Z_composeQueryString() {
		if (empty($this->select_string)) {
			$this->composeSelectString();
		}
		if ($this->join_string_fields != 'NNULL') {
			$this->composeJoinString();
		}
		if(count($this->error_array) > 0) {
			return;
		}
		$space_string = ' ';
		$crlf_string = "\r\n"; // figure this out globally
		$query_string = '';
		$query_string .= 'SELECT' . $space_string . $crlf_string . $this->select_string;
		$query_string .= $space_string . $crlf_string . $crlf_string . 'FROM' . $space_string . $this->entity_table_name . $space_string . $this->entity_table_alias;
		$query_string .= $space_string . $crlf_string . $this->join_string;
		$query_string .= $space_string . $crlf_string . $crlf_string . "WHERE n.type = '" . trim($this->type) . "'";
		$query_string .= $space_string . $crlf_string . 'GROUP BY n.nid';
		$query_string .= ''; // no ORDER BY
		$this->query_string = $query_string;
		$this->select_string_node = 'NNULL';
		$this->select_string_fields = 'NNULL';
		$this->select_string_ids = 'NNULL';
		$this->select_string_stamps = 'NNULL';
		$this->select_string = 'NNULL';
		$this->join_string = 'NNULL';
	} //END function composeQueryString()

	public function Z_composeViewString() {
		if (empty($this->query_string)) {
			$this->composeQueryString();
		}
		if(count($this->error_array) > 0) {
			return;
		}
		$view_name = $this->type . '_' . strtoupper($this->entity) . '_VIEW';
		$view_name = 'sqlVIEW_' . $this->type . '_' . strtoupper($this->entity);
		$space_string = ' ';
		$crlf_string = "\r\n"; // figure this out globally
		$view_string = '';
		$view_string .= $crlf_string . 'CREATE OR REPLACE VIEW' . $space_string . $view_name . $space_string . 'AS';
		$view_string .= $space_string . $crlf_string . $crlf_string . $this->query_string;
		$view_string .= $space_string . $crlf_string . ';';
		$view_string .= $space_string . $crlf_string . "/*END $view_name */";

		$this->view_string =$view_string;
		$this->query_string = 'NNULL';


	} //END function composeViewString()

	public function instantiateView() {
		if (empty($this->view_string)) {
			$this->composeViewString();
		}

		echo 'Use PDO to execute the "CREATE OR REPLACE VIEW" code.';

	} //END function instantiateView()


} //END Class

function Z_gather_field_table_data($field_name, $prefix = 'field_data_', $site = 'doggydaycare') {
	if (empty($field_name)) {
		return false;
	}
	$table_name = $prefix . $field_name;
	// return $table_name;
	$table_query = db_query(
	'SELECT *
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_NAME= :table_name AND TABLE_SCHEMA = :site',
array(':table_name'=>$table_name,
	':site'=>$site))->fetchAll();
	// return $table_query;
	foreach ($table_query as $index => $row) {
		$table_query_result[$row->COLUMN_NAME] = $row;
	}
	return (object) $table_query_result;
}


/**
 * NON-Method Utility Functions
 * * perhaps these should be in an external library, but for now...
 *
 */
function simple_sanatize_label($label) {
	$double_quotes = TRUE;
	$double_quotes = substr($label, 0 , 1) != '"' ? FALSE : $double_quotes;
	$double_quotes = substr($label, -1) != '"' ? FALSE : $double_quotes;
	/*< Special Characters > append as they occur */
	$label = str_replace('é', 'e', $label);
	/*</ Special Characters >*/
	$char_array = array('~','`','!','@','#','$','%','^','&','*','(',')','-','+','=','{',
		'[','}',']','}','|','\\',':',';','"',"'",'<',',','>','.','?','/');
	foreach ($char_array as $index => $char_this) {
		$label = str_replace($char_this, '', $label);
	}
	while(strpos($label, '__') !== FALSE) {
		$label = str_replace('__', '_', $label);
	}
	while(strpos($label, '  ') !== FALSE) {
		$label = str_replace('  ', ' ', $label);
	}
	if ($double_quotes) {
		$label = '"' . $label . '"';
	}
	return $label;
}

function best_table_alias_array() {
	#\_ keyed, by table name, array_flip() if you like
	$best_table_alias_array = array();
	$schema = drupal_get_schema();
	$schema_tablenames = array_keys($schema);
	$table_names_assoc = array_combine($schema_tablenames, $schema_tablenames);
	// $table_names_assoc['north_carolina_state'] = 'north_carolina_state';
	// $table_names_assoc['next_clash_song'] = 'next_clash_song';
	/**
	 * Because 'field_' prefixed tables propegate so quickly
	 */
	$hard_coded_alaises = array(
		'field_collection_item' => 'fcli',
		'field_collection_item_revision' => 'fclir',
		#\_ append if a field is important enough not to have an 'indexed alias'
		);
	$pass_array = array('field','remaining');
	foreach ($pass_array as $index => $pass) {
		foreach ($table_names_assoc as $table_name_key => $table_name_value) {
			$does_pass_field = substr($table_name_key, 0, 6) == 'field_' ? TRUE : FALSE;
			$does_pass_remaining = isset($best_table_alias_array[$table_name_key]) ? FALSE : TRUE;
			$does_pass_this = FALSE;
			$does_pass_this = $pass == 'field'  ? $does_pass_field : $does_pass_this;
			$does_pass_this = $pass == 'remaining'  ? $does_pass_remaining : $does_pass_this;
			// if (!isset($best_table_alias_array[$table_name_key])) {
			if ($does_pass_this) {
				if (in_array($table_name_key, array_flip($hard_coded_alaises))) {
					$alias = $hard_coded_alaises[$table_name_key];
				}else{
					$alias = table_alias_from_table_name($table_name_value);
				}
				if (in_array($alias, $best_table_alias_array)) {
					$i = 0;
					$alias_indexed = $alias;
					while (in_array($alias_indexed, $best_table_alias_array)) {
					$i++;
					$alias_indexed = $alias . '_' .  $i;
					}
					$alias = $alias_indexed;
				}
				$best_table_alias_array[$table_name_key] = $alias;
			} //END if ($does_pass_this)
		} //END foreach ($table_names_assoc as $table_name_key => $table_name_value)
	} //END foreach ($pass_array as $index => $pass)

	// $best_table_alias_array = $table_names_assoc;
	return $best_table_alias_array;
}

function table_alias_from_table_name($table_name) {
	// $table_alias = 'z_' . $table_name;
	// return $table_alias;
	$table_name_word_array = explode('_',$table_name);
	// $table_alias= $table_name_word_array;
	// $field_id_array = array_map(
	// 		create_function('$o', 'return $o->field_id;'),
	// 		$field_config_instance_array);
	$table_alias_array= array_map(
			create_function('$e', 'return substr($e, 0, 1);'),
			$table_name_word_array);
	$table_alias = implode('', $table_alias_array);
	return $table_alias;
}

/**
 * END NON-Method Utility Functions
 */
