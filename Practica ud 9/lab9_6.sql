CREATE TABLE EMPLOYEES2
    ID mediumint(9) NOT NULL,
    FIRST_NAME varchar(20) NOT NULL,
    LAST_NAME varchar(25) NOT NULL,
    SALARY decimal(8,2) NOT NULL
    DEPARTMENT_ID smallint(6) DEFAULT NULL
AS
    SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, SALARY, DEPARTMENT_ID
    FROM employees;
