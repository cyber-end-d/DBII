SELECT LAST_NAME,  LPAD(TRUNCATE(SALARY,0),15,'$') AS 'SALARY'
FROM employees;