<?php


$users_view_sql_code = <<<HDOCX
CREATE OR REPLACE VIEW users_view AS
SELECT u.uid
, u.name
, u.mail
, FROM_UNIXTIME(u.created,'%b %e, %Y %l:%i:%s %p') AS created
, FROM_UNIXTIME(u.access,'%b %e, %Y %l:%i:%s %p') AS last_access
, FROM_UNIXTIME(u.login,'%b %e, %Y %l:%i:%s %p') AS last_login
FROM  users u
;
HDOCX;
