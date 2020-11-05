SELECT JOB_ID,
	CASE DEPARTMENT_ID WHEN 20 THEN SALARY END AS 'Dept 20',
	CASE DEPARTMENT_ID WHEN 50 THEN SALARY END AS 'Dept 50',
	CASE DEPARTMENT_ID WHEN 80 THEN SALARY END AS 'Dept 80',
	CASE DEPARTMENT_ID WHEN 90 THEN SALARY END AS 'Dept 90',
FROM employees
GROUP 	BY JOB_ID;