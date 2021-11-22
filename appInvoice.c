#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <curses.h>
#include "appInvoice.h"
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include <dirent.h>
#include<locale.h>

#define esc 27
#define enter 13


void contentDisplay()
{
	setlocale(LC_ALL, "Turkish");
	int i = 1;
    DIR *di;
    struct dirent *dir;
    di = opendir("."); //specify the directory name
    if (di)
    {
         int a = strlen(dir->d_name); // file name+extension
        while ((dir = readdir(di)) != NULL)
        {
            if(a >= 4)
            {
                if (dir->d_name[a-1] == 'v' && dir->d_name[a-2] == 'n' && dir->d_name[a-3] == 'i' && dir->d_name[a-4] == '.')
                {
                    printf("%d - ",i);
                    int j;
                    for (j = 0; j < a-4; j++)
                    {
                        printf("%c",dir->d_name[j]);
                    }
                    printf("\n");
                    i++;
                }
            }
        }
        closedir(di);
        printf("...\n...\nPress ESC to return main menu\n");
    }
    setlocale (LC_ALL, "C");


}

 int filePrint(char *fileName)
 {
	int firstByteFlag = 0, secondByteFlag = 0,thirdByteFlag = 0;
	int c;
    FILE *infile = fopen(fileName, "r");
    while((c = getc(infile)) != EOF)
    {

	if(c == 195 || c == 196 || c == 197)
	{
		switch(c){
			case 195:
				firstByteFlag = 1;
				break;
			case 196:
				secondByteFlag = 1;
				break;
			case 197:
				thirdByteFlag = 1;
				break;
	}
    }
	else if(firstByteFlag == 1)
	{
		switch(c){
			case 135:
				printf("%c",128);
				break;
			case 150:
				printf("%c",153);
				break;
			case 156:
				printf("%c",154);
				break;
			case 167:
				printf("%c",135);
				break;
			case 182:
				printf("%c",148);
				break;
			case 188:
				printf("%c",129);
				break;
			}
				firstByteFlag = 0;
	}
	else if(secondByteFlag == 1)
	{
		switch(c){
			case 158:
				printf("%c",158);
				break;
			case 150:
				printf("%c",153);
				break;
			case 159:
				printf("%c",167);
				break;
			case 176:
				printf("%c",152);
				break;
			case 177:
				printf("%c",141);
				break;
			}
			secondByteFlag = 0;
	}
	else if(thirdByteFlag == 1)
	{
		switch(c){
			case 158:
				printf("%c",158);
				break;
			case 159:
				printf("%c",159);
				break;
			}
			thirdByteFlag = 0;
	}
	else{
		printf("%c",c);
   	}

	}
    fclose(infile);
    return 0;
 }


int customerSize()
{
	int i;
    DIR *di;
    struct dirent *dir;
    di = opendir("."); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
           int a = strlen(dir->d_name); // file name+extension
            if(a >= 4)
            {
                if (dir->d_name[a-1] == 'v' && dir->d_name[a-2] == 'n' && dir->d_name[a-3] == 'i' && dir->d_name[a-4] == '.')
                {
                   i++;
                }
            }
        }
        closedir(di);
        return i;
    }
    return 0;
}

void showInvoice(int list)
{
    setlocale (LC_ALL, "C");

	int i = 1;
    DIR *di;
    struct dirent *dir;
    di = opendir("."); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
             int a = strlen(dir->d_name); // file name+extension
            if(a >= 4)
            {
                if (dir->d_name[a-1] == 'v' && dir->d_name[a-2] == 'n' && dir->d_name[a-3] == 'i' && dir->d_name[a-4] == '.')
                {
                    if(list == i)
                    {
                    	closedir(di);
                        filePrint(dir->d_name);
                        return;
                    }
                    i++;
                }
            }
        }
        closedir(di);
    }
    return;

}




void showInvoiceList()
{
    int fileNu;
    char *input = (char*)calloc(100,sizeof(char));
     if (input == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    contentDisplay();

    int exitflag = 0;
    char ch;
    do{
        ch = getch();
        switch(ch)
        {
        case esc:
            printf("esc ye basildi\n");
            exitflag = 1;
            break;
        case enter:

            printf("\n");
            fileNu = atoi(input);
            if(fileNu  <= customerSize() && fileNu > 0)
            {
                showInvoice(fileNu);
                Sleep(4000);
            }
            else{
                printf("record not found\n");
                Sleep(2000);
            }
            memset(input, 0, strlen(input));
            system("cls");
            contentDisplay();
            break;
        default:
            strncat(input,&ch,1);
            system("cls");
            printf("%s",input);
        }
    }while(exitflag != 1);


    system("cls");
    //printf("break on");
}
