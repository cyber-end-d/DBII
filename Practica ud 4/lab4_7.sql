SELECT E.LAST_NAME AS 'EMPLOYEE', E.EMPLOYEE_ID AS 'EMP#', M.LAST_NAME AS 'MANAGER', M.EMPLOYEE_ID AS 'MGR#'
FROM E.employees
RIGHT OUTER JOIN M.employees
ON (E.MANAGER_ID = M.EMPLOYEE_ID);
