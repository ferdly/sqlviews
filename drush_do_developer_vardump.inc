<?php

function _do_developer_vardump(){
  $print = drush_get_option('context', 0);
  $print = $print == 1 ? TRUE : FALSE;
  // $print = TRUE;
  $context = _render_drush_context_sqlviews($print);
  $options = $context['custom']['options'];
  $argument_which = $context['drush']['arguments'][0];
  $argument_which = empty($argument_which) ? 'ZXZ' : $argument_which;
  // $which = $argument_which;
  // drush_print('$which: ' . $which . ' [' . __LINE__ . ']');
  // return;

  /*<Preset $type_machine_name> of course, can overload, but why?*/
  $type_machine_name = 'job_application';
  // $type_machine_name = 'property';
  /*</Preset $type_machine_name>*/
  /*<Preset $label_option> of course, can overload, but why?*/
  $label_option = 'machine_abbrv';
  /*</Preset $label_option>*/
  $supported_which_array = array(
        'cleared out see reports for archived devv too',
    );
  if ($argument_which == 'which') {
    $arguments = array_combine($supported_which_array, $supported_which_array);
    $argument_which = drush_choice($arguments, dt('Which Object-Attribute would you like to \'Developer-Vardump\'?'));
    if ($argument_which == '0') {
        drush_user_abort('Buh-Bye! Developer-Vardump Which-Which!');
        return;
    }
    }
  if (!in_array($argument_which, $supported_which_array)) {
      $which_key = $argument_which;
      if (ctype_digit($which_key)) {
        $which_key--;
          $argument_which = $supported_which_array[$which_key];
          $which = empty($argument_which) ? 'ZXZXZXZ' : 'ZXZXZ';
      }else{
        $which = 'ZXZ';
      }
  }
  if (in_array($argument_which, $supported_which_array)) {
      $which = $argument_which;
  }else{
      // $which = 'cleared out see reports for archived devv too';
      /* \_ Un-Comment one above for default $which */
  }

  $header = 'Result of ' . __FUNCTION__ . '(' . $which . ')';
  $header_len = strlen($header);
  $header .= "\r\n";
  for ($i=0; $i < $header_len; $i++) {
    $header .= '=';
  }
  $header .= "\r\n";
  $result = $header . $output;


  drush_print($header);
  drush_print("Unsupported Developer-Vardump \$which!\r\n");
  drush_print('$which: ' . $which . "; \r\n[Line: " . __LINE__ . '; File: ' . basename(__FILE__) . ";]\r\n");
  return;
}
