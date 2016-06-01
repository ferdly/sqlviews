<?php

class fieldSQL /* WILL SOON extend something*/ {
	/* <drupal/sql direct> */
	#\_ some may be vestigial ($index), but keep until no longer needed
	public $index;
	public $weight;
	public $field_name;
	public $field_column_name;
	public $table_name;
	public $label;
	public $label_option;
    public $table_alias;
    public $field_select_list_string;
    public $field_join_string;
	public $field_config_instance_id;
	public $field_config_id;
	public $field_config_instance_deleted;
	public $field_config_deleted;
	public $field_config_instance_data;
	public $field_config_data;
	public $of_entity;
    public $of_bundle;
    public $of_foriegn_key_table;
	public $of_foriegn_key;
	public $of_cardinality;
	public $type;
	public $module;
	public $active;
	public $locked;
	public $cardinality;
	public $total_cardinality;
	public $columns = array(); //Pre-Object Array
	/* </drupal/sql direct> */
	/* <to be UnPacked> */
	public $field_field_object_array = array();
	public $column_object_array = array();
	// public $table_alias;
	// public $field_select_list_string;
	// public $field_join_string;
	public $field_join_is_hidden = 0;
	public $field_select_is_hidden = 0;
	/* </to be UnPacked> */
	/* <Utility Code> */
	/* </Utility Code> */

	public function __construct($field_array) {
		if (is_array($field_array) || is_object($field_array)) {
			foreach ($field_array as $key => $value) {
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

	public function instantiateFieldAndReturn($field_config_ob) {
		$return_field_object = new fieldSQL($field_config_ob);
		return $return_field_object;
	}

	public function unpack_by_field_id() {
		$field_id = $this->id;
		$field_info_array = field_info_field_by_id($field_id);
		if ($this->field_name != $field_info_array['field_name']) {
			$this->error[] = 'FieldName MisMatch [File: ' . basename(__FILE__) . '; Line: ' . __LINE__ .';]';
		}
	// $weight;
	// $this->field_name = $field_info_array['field_name'];
	$this->field_column_name = $this->field_name . '_value';
	$table_array = $field_info_array['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
	$table_name = key($table_array);
    $this->table_name = $table_name;
	$this->of_foriegn_key_table = strlen($this->of_foriegn_key_table) == 0 ?
        $this->of_entity : $this->of_foriegn_key_table;
	$this->table_alias = nodeTypeSQL::$all_table_alias_array[$this->table_name];
	// $this->label = $field_info_array[''];
	// $this->label_option = $field_info_array[''];
	$this->field_config_instance_id = 'moot?';//$field_info_array[''];
	$this->field_config_id = 'moot?';//$field_info_array[''];
	$this->field_config_instance_deleted = 'moot?';//$field_info_array[''];
	$this->field_config_deleted = 'moot?';//$field_info_array[''];
	$this->type = $field_info_array['type'];
	$this->module = $field_info_array['module'];
	$this->active = $field_info_array['active'];
	$this->locked = $field_info_array['locked'];
	$this->cardinality = $field_info_array['cardinality'];
	$this->total_cardinality = $this->of_cardinality * $this->cardinality;
	$this->columns = $field_info_array['columns'];
	$data_unserialized = unserialize($this->field_config_instance_data);
	$this->label = $data_unserialized['label'];
	$this->weight = $data_unserialized['widget']['weight'];
	$this->field_config_instance_data = 'EMPTIED after UnPack in ' . basename(__FILE__) . ' on line ' . __LINE__;
	}

	public function unpack_join_string(){
        // $join = 'LEFT JOIN ' . $this->table_name . ' ' . $this->table_alias;
		$join = 'LEFT JOIN ' . $this->table_name . ' ' . $this->table_alias;
        // $on = 'ON ' . nodeTypeSQL::$all_table_alias_array[$this->of_entity] . '.' . $this->of_foriegn_key . ' = ' . $this->table_alias . '.entity_id';
		$on = 'ON ' . nodeTypeSQL::$all_table_alias_array[$this->of_foriegn_key_table] . '.' . $this->of_foriegn_key . ' = ' . $this->table_alias . '.entity_id';
		$this->field_join_string = $join . "\r\n" . $on;
	}

    public function gatherSelect_this($i = 0) {
        $select_array_this = array();
        if (count($this->column_object_array) == 0) {
            $select = "/* NNULL */";
            $select_array_this[$i] = $select;
            foreach ($this->field_field_object_array as $index => $field_object_this) {
                $result_array = $field_object_this->gatherSelect_this();
                $select_array_this = array_merge($select_array_this,$result_array);
            }
        }else{
            foreach ($this->column_object_array as $index => $column_this) {
                $select = $column_this->column_select_string;
                $select_array_this[$i] = $select;
                $i++;
            }
        }
        return $select_array_this;
    } //END public function gatherSelect_this($i = 0)

    public function gatherJoin_this($i = 0) {
        $join_array_this = array();
        if (count($this->column_object_array) == 0) {
            $join = $this->field_join_string;
            $join_array_this[$i] = $join;
            foreach ($this->field_field_object_array as $index => $field_object_this) {
                $result_array = $field_object_this->gatherJoin_this();
                $join_array_this = array_merge($join_array_this,$result_array);
            }
        }else{
            foreach ($this->column_object_array as $index => $column_this) {
                $join = $column_this->column_join_string;
                $join_array_this[$i] = $join;
                $i++;
            }
        }
        return $join_array_this;
    } //END public function gatherSelect_this($i = 0)

	public function field_report_singleton() {
		$crlf = "|\r\n";
		$delimiter = ",";
		$field_field_report_buffer = '';
		if (count($this->field_field_object_array) > 0) {
			$field_field_object_array = $this->field_field_object_array;
			foreach ($field_field_object_array as $index => $field_field_object_this) {
				$field_field_report_buffer .= $field_field_object_this
				->field_report_singleton();
			}
		}
		$field_report_singleton_result = '';
		if ($this->field_select_is_hidden == 0) {
			$field_report_singleton_result .= "{$this->of_entity},";
			$field_report_singleton_result .= "{$this->of_bundle},";
			$field_report_singleton_result .= "{$this->table_name},";
			$field_report_singleton_result .= "{$this->field_column_name},";
			$field_report_singleton_result .= "{$this->total_cardinality}";
			$field_report_singleton_result .= "\r\n";
		}
		// $field_report_singleton_result = "entity,type,table_name,{$this->field_name}|\r\n";
		$field_report_singleton_result .= $field_field_report_buffer;
		return $field_report_singleton_result;
	}
	public function prepareColumnArrayForColumnInstantiation() {
		$column_to_field_mapper_array = array();
		foreach ($this as $field_key => $field_attribute) {
		  $render = FALSE;
          $render = isset($field_attribute) ? TRUE : $render;
          $render = $field_attribute === 0 ? TRUE : $render;
          $render = is_array($field_attribute) && count($field_attribute) == 0 ? FALSE : $render;
          $render = $field_attribute == 'moot?' ? FALSE : $render;
          $do_render_array = array('index');
          $render = in_array($field_key, $do_render_array) ? TRUE : $render;
          $do_not_render_array = array('columns','field_field_object_array','field_config_instance_data','column_object_array');
          $render = in_array($field_key, $do_not_render_array) ? FALSE : $render;
          if ($render) {
            $field_prefix = substr($field_key, 0, 6) == 'field_' ? TRUE : FALSE;
            if ($field_prefix) {
              $column_key = 'column_' . substr($field_key, 6);
              if (substr($column_key, 0, 13) == 'column_column') {
                $column_key = substr($column_key, 7);
              }
            }else{
              $column_key = $field_key;
            } //END if ($field_prefix)
            $column_to_field_mapper_array[$column_key] = $field_key;
          } //END if ($render)
      } //END foreach ($column_array as $field_key => $field_attribute)
      $column_array_for_column_instantiation = array();
      foreach ($column_to_field_mapper_array as $column_key => $field_key) {
      	$column_array_for_column_instantiation[$column_key] = $this->$field_key;
      }
      return $column_array_for_column_instantiation;
	}
    public function gatherColumnArrayToField() {
        $this->column_object_array =
        	columnSQL::instantiate_columnsFromField($this);
        return $this->column_object_array;
    }

    public function instantiate_fieldsFromEntityBundle($entity_bundle_object){
        $entity = $entity_bundle_object->entity;
        $foriegn_key_table = $entity_bundle_object->foriegn_key_table;//save for 'somthing?'
        // $foriegn_key_table = strlen($foriegn_key_table) == 0 ? $entity_bundle_object->table_name : $foriegn_key_table;
        $bundle = $entity_bundle_object->bundle;
        $foriegn_key = $entity_bundle_object->entity_table_foriegnkey;
        $cardinality = $entity_bundle_object->of_cardinality + 0;
        // $cardinality = $cardinality == 0 ? 1 : $cardinality;
        $type = $entity_bundle_object->type; //backward compatible for node
        $bundle = empty($bundle) ? $type : $bundle;//backward compatible for node
        $core = nodeTypeSQL::$drupal_core_field_type_module_array;
        $label_option = $entity_bundle_object->label_option;
        $field_config_instance_array= db_select('field_config_instance','fci')
            ->fields('fci',array('field_id','data'))
            // ->addField('fci', 'field_id')
            // ->addField('fci', 'data', 'fci_data')
            ->condition('entity_type', $entity)
            ->condition('bundle', $bundle)
            ->condition('deleted', 0)
            ->execute()
            ->fetchAll();

        $field_id_array = array_map(
            create_function('$o', 'return $o->field_id;'),
            $field_config_instance_array);
        /* <Critical>  to '$field_config_ob->field_config_instance_data' below*/
        foreach ($field_config_instance_array as $index => $fci_this) {
            $fci_array[$fci_this->field_id]['field_id'] = $fci_this->field_id;
            $fci_array[$fci_this->field_id]['field_name'] = $fci_this->field_name;
            $fci_array[$fci_this->field_id]['fci_data'] = $fci_this->data;
        }
        /* </Critical>*/

        $field_config_array= db_select('field_config','fc')
            ->fields('fc',array('id','field_name','type','module'))
            ->condition('id', $field_id_array,'IN')
            ->condition('active', 1)
            ->condition('deleted', 0)
            ->execute()
            ->fetchAll();
        $i = 0;
        foreach ($field_config_array as $key => $field_config) {
            $this_field_id = $field_config->id;
            $field_config->field_id = $field_config->id;
            $field_config->of_entity = $entity;
            $field_config->of_bundle = $bundle;
            $field_config->of_foriegn_key_table = $foriegn_key_table;
            $field_config->of_foriegn_key = $foriegn_key;
            $field_config->of_cardinality = $cardinality;
            $field_config->label_option = $label_option;
            $field_config->index = $i;
            if (in_array($field_config->module, $core)) {
                $field_config_ob = fieldSQL::instantiateFieldAndReturn($field_config);
                // $field_config_ob->unpack_by_field_id();
                // $return_field_object_array[$field_config->field_name] = $field_config_ob;
            }else{
                // $return_field_object_array[$field_config->field_name]['action'] = $field_config->module . '_fieldSQL';
                $class_name = $field_config->module . '_fieldSQL';
                $field_config_ob = $class_name::instantiateFieldAndReturn($field_config);
                // $field_config_ob->unpack_by_field_id();
            // $return_field_object_array[$field_config->field_name] = $field_config_ob;
            }
            $field_config_ob->field_config_instance_data = $fci_array[$this_field_id]['fci_data'];
            $i++;
            $field_config_ob->unpack_by_field_id();
            $field_config_ob->unpack_join_string();
            $field_config_ob->gatherColumnArrayToField();
            $return_field_object_array[$field_config->field_name] = $field_config_ob;

        }

        $result_array = $return_field_object_array;
            usort($result_array, function($a, $b)
            {
                // return strcmp($a->weight, $b->weight);
                return $a->weight > $b->weight;
            });

        return $result_array;
    } //END function instantiate_fieldsFromEntityBundle($entity_bundle_object)


/**
 * END Most Current OO from Local Static Method
 */


	public function instantiateColumnObjects($field_array_this = array(), $column_loop_array_overload = array()) {
			// $column_array = $this->columns;
			if (count($column_loop_array_overload) == 0) {
				$column_loop_array = $this->columns;
				// $label_overload = '';
			}else{
				$column_loop_array = $column_loop_array_overload;
				// $label_overload = !empty($column_loop_array['label_overload']) ? $column_loop_array['label_overload'] : '';
			}
			// if ($field_array_this['type'] == 'addressfield') {
			// 	$column_loop_array = array( 'first_name' => 1, 'last_name' => 2, 'name_line' => 3, 'organisation_name' => 4, 'thoroughfare' => 5, 'premise' => 6, 'locality' => 7, 'administrative_area' => 8, 'postal_code' => 9, 'country' => 10, 'sub_administrative_area' => 11, 'dependent_locality' => 12, 'sub_premise' => 13, 'data' => 14,);
			// }else{
			// 	$column_loop_array = $column_array;
			// }
			foreach ($column_loop_array as $column_key => $value) {
				// $label_overload = !empty($value['label_overload']) ? $value['label_overload'] : '';
				$column_array_this = $this->columns[$column_key];
				// $column_object_this = new columnSQL($column_array[$column_key]);
				$column_object_this = new columnSQL($column_array_this);
				$column_object_this->label_option = $this->label_option;
				// $column_object_this->label_overload = $label_overload;
				// $column_object_array[] = $column_object_this;
				$column_object_array[$column_key] = $column_object_this;
				// $field_object_this->column_object_array[] = $column_object_this;
				// $field_object_this->columns = 'NNULL';
			}
			return $column_object_array;
		// switch ($this->type) {
		// 	case 'addressfield':
		// 		$column_loop_array = $this->gatherColumnLoopArray_AddressField();
		// 		$this->instantiateColumnObjects_loop($column_loop_array);
		// 		break;

		// 	default:
		// 		$column_loop_array = $this->columns;
		// 		$this->instantiateColumnObjects_loop($column_loop_array);
		// 		break;
		// }

	}

	public function gatherColumnLoopArray_AddressField(){
	$column_loop_array = array(
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
	return $column_loop_array;
	}


	public function gatherColumnLoopArray_FieldCollection(){
		$column_loop_array = $this->columns;
		return $column_loop_array;
	}

	public function instantiateColumnObjects_loop($column_loop_array){
		$column_array = $this->columns;
		foreach ($column_loop_array as $column_key => $column_array_this) {
			$column_object_this = new columnSQL($column_array[$column_key]);
			$column_object_this->label_option = $this->label_option;
			$this->column_object_array[] = $column_object_this;
			$this->columns = 'NNULL';
		}
	}

	public function un_pack($node_data_array) {
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
		// $field_data_array['label_overload'] = '';
		$fc = $field_data_array['type'] == 'field_collection' ? '_zfc' : '';

		// $this->un_pack_JoinString($field_data_array, $node_data_array);
		#\_ NOW BELOW! for Column Join-String implementation
		// $this->field_join_string = 'LEFT JOIN' . $space_string . $this->table_name . $space_string . $this->table_alias;
		// $join_right_string = $node_data_array['entity_table_alias'] . '.' . $node_data_array['entity_table_foriegnkey'];
		// $this->field_join_string .= $space_string . $crlf_string . 'ON' . $space_string . $join_right_string . ' = ' . $this->table_alias . '.' . 'entity_id';
		$column_select_string_array = array();
		$column_keys_to_skip_array = array('format','summary'); //believed to be reserved for body
		foreach ($this->column_object_array as $index => $column_object_this) {
			if (in_array($column_object_this->column_key, $column_keys_to_skip_array) !== true) {
				$field_data_array['label_overload'] = !empty($column_object_this->label_overload) ? $column_object_this->label_overload : '';
				$this->column_object_array[$index]->un_pack($field_data_array);
				if (!empty($this->column_object_array[$index]->column_select_string)) {
					$column_select_string_array[] = $this->column_object_array[$index]->column_select_string . $fc;
				}
			}
		}
		$this->un_pack_JoinString($field_data_array, $node_data_array);
		$this->field_select_list_string = implode("\r\n,", $column_select_string_array);
	} //END function un_pack()

	public function un_pack_JoinString(&$field_data_array,&$node_data_array ) {
		$space_string = ' ';
		$crlf_string = "\r\n"; //figure out globally
		$field_join_string_scrap = $this->field_join_string;
		// if (!empty($field_join_string_scrap)) {
		// 	return;
		// }
		$this->field_join_string = 'LEFT JOIN' . $space_string . $this->table_name . $space_string . $this->table_alias;
		$join_right_string = $node_data_array['entity_table_alias'] . '.' . $node_data_array['entity_table_foriegnkey'];
		$this->field_join_string .= $space_string . $crlf_string . 'ON' . $space_string . $join_right_string . ' = ' . $this->table_alias . '.' . 'entity_id';
		// foreach ($this->column_object_array as $index => $column_object_this) {
		// 	if (!empty($column_object_this->column_join_string)) {
		// 		$this->field_join_string .= $crlf_string . $column_object_this->column_join_string;
		// 	}
		// }
		$this->field_join_string .= $field_join_string_scrap;
	}

}