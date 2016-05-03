<?php


$users_roles_view_sql_code = <<<HDOCX
CREATE OR REPLACE VIEW users_roles_view AS
SELECT ur.uid
, ur.rid
, u.name
, r.name AS role
, u.mail
, FROM_UNIXTIME(u.created,'%b %e, %Y %l:%i:%s %p') AS created
, FROM_UNIXTIME(u.access,'%b %e, %Y %l:%i:%s %p') AS last_access
, FROM_UNIXTIME(u.login,'%b %e, %Y %l:%i:%s %p') AS last_login
FROM users_roles ur
LEFT JOIN users u
ON ur.uid = u.uid
LEFT JOIN role r
ON r.rid = ur.rid
;
HDOCX;
