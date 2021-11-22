#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <curses.h>
#include "sqlite3.h"
#include "appUser.h"
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>

int validadation(char *id,char *Password,char *name)
 {
    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;

    int rc = sqlite3_open("upload_system.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = (char*)malloc(sizeof(char)*100);
    sprintf(sql, "SELECT NameSurname FROM users WHERE Id = %s AND Password = \"%s\"",id,Password);




    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

    sqlite3_bind_int(res, 1, 3);
    } else {

    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);



    if (step == SQLITE_ROW) {
        printf("Login Succeeded\n");
        Sleep(2000);
        system("cls");

        strcpy(name,(char *)sqlite3_column_text(res, 0));

        sprintf(sql, "INSERT INTO audit(UserId,LoginTime) VALUES (%s,datetime('now'));",id);

        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);


        if (rc != SQLITE_OK ) {

            fprintf(stderr, "SQL error: %s\n", err_msg);

            sqlite3_free(err_msg);
            sqlite3_close(db);

             return 1;
          }



         sqlite3_finalize(res);  // The database is closed when logged out.
         sqlite3_close(db);
         return 3;
    }
    else{
        printf("Login Failed\n");
        Sleep(2000);
        system("cls");
        return 2;       // User not found
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
 }

 int setLogoutTime()
{

     sqlite3 *db;
     char *err_msg = 0;

    int rc = sqlite3_open("upload_system.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        printf("Cannot open database\n");
    }

         char *sql = "UPDATE audit SET LogoutTime = datetime('now') WHERE OID = (SELECT MAX(OID) FROM audit);";

           rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

        if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
        }

        sqlite3_close(db);


        return 0; // Logout
}




