<?php


$users_ago_view_sql_code = <<<HDOCX
CREATE OR REPLACE VIEW users_ago_view AS
SELECT u.uid
, u.name
, u.mail
, FROM_UNIXTIME(u.access,'%b %e, %Y %l:%i:%s %p') AS last_access
, getAgo((u.access - u.login)) AS login_ago
, getAgo((u.access - u.created)) AS created_ago
FROM  users u
;
HDOCX;
