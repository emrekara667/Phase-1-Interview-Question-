#ifndef APPINVOICE_H_INCLUDED
#define APPINVOICE_H_INCLUDED

void contentDisplay();         //Prints files with .inv extension in the directory.
int filePrint(char *fileName); //File content is shown without encoding issues
int customerSize();            //Returns the number of files with the extension .inv in the directory
void showInvoice(int list);    //Prints the file contents with the specified number.
void showInvoiceList();        //Manages transactions in the invoice menu


#endif
