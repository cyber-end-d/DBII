SELECT E.LAST_NAME, E.HIRE_DATE
FROM employees E
JOIN employees D
ON (D.LAST_NAME LIKE 'Davis')
WHERE E.HIRE_DATE > D.HIRE_DATE;
