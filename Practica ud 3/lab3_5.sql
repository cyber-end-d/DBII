SELECT CONCAT(UPPER(SUBSTR(LAST_NAME,1,1)),LOWER(SUBSTR(LAST_NAME,2))) AS 'LAST_NAME', LENGTH(LAST_NAME) AS 'Length'
FROM employees
WHERE SUBSTR(LAST_NAME,1,1) LIKE 'J' OR 'A' OR 'M'
ORDER BY LAST_NAME;