<?php


$ago_sql_code = <<<HDOCX
DROP FUNCTION getAgo;
CREATE FUNCTION getAgo(diffU INT) RETURNS VARCHAR(128) NOT DETERMINISTIC NO SQL SQL SECURITY DEFINER BEGIN
    DECLARE ago_string varchar(128);
    DECLARE years INT;
    DECLARE months INT;
    DECLARE weeks INT;
    DECLARE days INT;
    DECLARE hours INT;
    DECLARE minutes INT;
    DECLARE seconds INT;
    SET ago_string = '';
    SET years = FLOOR(diffU / 31536000);
    IF years = 1 THEN
        SET ago_string = CONCAT(ago_string, years, ' year, ');
    END IF;
    IF years > 1 THEN
        SET ago_string = CONCAT(ago_string, years, ' years, ');
    END IF;
    SET months = FLOOR((diffU % 31536000) / 2592000);
    IF months = 1 THEN
        SET ago_string = CONCAT(ago_string, months, ' month, ');
    END IF;
    IF months > 1 THEN
        SET ago_string = CONCAT(ago_string, months, ' months, ');
    END IF;
    SET weeks = FLOOR((diffU % 2592000) / 604800);
    IF weeks = 1 THEN
        SET ago_string = CONCAT(ago_string, weeks, ' week, ');
    END IF;
    IF weeks > 1 THEN
        SET ago_string = CONCAT(ago_string, weeks, ' weeks, ');
    END IF;
    SET days = FLOOR((diffU % 604800) / 86400);
    IF days = 1 THEN
        SET ago_string = CONCAT(ago_string, days, ' day, ');
    END IF;
    IF days > 1 THEN
        SET ago_string = CONCAT(ago_string, days, ' days, ');
    END IF;
    SET hours = FLOOR((diffU % 86400) / 3600);
    IF hours = 1 THEN
        SET ago_string = CONCAT(ago_string, hours, ' hour, ');
    END IF;
    IF hours > 1 THEN
        SET ago_string = CONCAT(ago_string, hours, ' hours, ');
    END IF;
    SET minutes = FLOOR((diffU % 3600) / 60);
    IF minutes > 0 THEN
        SET ago_string = CONCAT(ago_string, minutes, ' min, ');
    END IF;
    SET seconds = diffU % 60;
    IF seconds > 0 THEN
        SET ago_string = CONCAT(ago_string, seconds, ' sec');
    END IF;
    RETURN ago_string;
END;
HDOCX;
