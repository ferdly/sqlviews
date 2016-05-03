<?php

function generate_result_form($sql) {
    $buffer = '';
    // $crlf = '<br><hr><br>';
    $crlf = "\r\n";
    $buffer .= $sql;
    $buffer .= $crlf;
    $buffer .= __FUNCTION__ . '<br>';
    $buffer .= $crlf;
    return $buffer;
}

function generate_sql_switch($query_name, $ago = FALSE, $options_array = array()) {
    $buffer = '';
    // $crlf = '<br><hr><br>';
    $crlf = "\r\n";
    if ($ago) {
        $buffer .= gather_sql_ago();
        $buffer .= $crlf;
    }
    $which = $query_name;
    $which .= $ago ? '_ago': '';
    switch ($which) {
        case 'users':
            $buffer .= gather_sql_users();
            break;
        case 'users_roles':
            $buffer .= gather_sql_users_roles();
            break;
        case 'users_ago':
            $buffer .= gather_sql_users_ago();
            break;
        case 'users_roles_ago':
            $buffer .= gather_sql_users_roles_ago();
            break;

        default:
            $buffer = "Unsupported Option: $which";
            break;
    }
    $buffer .= $crlf;
    // $buffer = generate_result_form($buffer);
    return $buffer;
}

function gather_sql_ago() {
    $sql = 'sql_ago code block (as include)';
    return $sql;
}
function gather_sql_users() {
    $sql = 'sql_users code block (as include)';
    return $sql;
}
function gather_sql_users_ago() {
    $sql = 'sql_users_ago code block (as include)';
    return $sql;
}
function gather_sql_users_roles() {
    $sql = 'sql_users_roles code block (as include)';
    return $sql;
}
function gather_sql_users_roles_ago() {
    $sql = 'sql_users_roles_ago code block (as include)';
    return $sql;
}
