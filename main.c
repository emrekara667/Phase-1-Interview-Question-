#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "appInvoice.h"
#include "appUser.h"

int main(void) {

    char *Password = (char*)malloc(sizeof(char)*100);
    char *id = (char*)malloc(sizeof(char)*100);
    char *UserName = (char*)malloc(sizeof(char)*100);
    int Flag = 0,logOutFlag = 0;
    int select = 0;


    while(1)
    {
        system("cls");
        printf("Enter User id:\n");
        scanf("%s",id);
        printf("Enter Password:\n");
        scanf("%s",Password);

        Flag = validadation(id,Password,UserName);
        if(Flag == 3)
        {
         do
          {
            printf("User : [%s]\nSelect Operation\n1 - Invoice List\n2 - Logout\n ",UserName);
            scanf("%d",&select);
            system("cls");
            if(select == 1)
            {
                showInvoiceList();
                printf("\n");

            }
            else if(select == 2){
                printf("Logged out\n");
                system("cls");
                logOutFlag = setLogoutTime();
                if(logOutFlag == 1)
                {
                    printf("setLogoutTime function failed!\n");
                }
            }
            else
            {
                printf("A valid number must be entered\n");
            }
          }while(select != 2);
        }

    }
    return 0;

}
