#ifndef APPUSER_H_INCLUDED
#define APPUSER_H_INCLUDED
/*
This function checks if username and id match.
And If the user logs in, it will stamp the login time.
Parameters:password, id number  ,username
Return the username parameter from the database and copies the value.
Return value: Is the ID and number correct?
*/
int validadation(char *,char*,char*);

/*
This function stamps the output time.
*/
int setLogoutTime();

#endif

