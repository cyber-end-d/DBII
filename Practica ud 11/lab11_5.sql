CREATE VIEW DEPT50
AS
    SELECT EMPLOYEE_ID AS 'EMPNO', LAST_NAME AS 'EMPLOYEE', DEPARTMENT_ID AS 'DEPTNO'
    FROM employees
    WHERE DEPARTMENT_ID = 50
    WITH READ ONLY;
