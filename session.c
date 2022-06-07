// KIT107 Assignment 2
/*
* Implementation for Session
* Author Julian Dermoudy
* Version 28/3/19
*
* THIS FILE IS COMPLETE
*/

#include <stdio.h>
#include <stdlib.h>
#include "session.h"

/*
* Definition of session type
*/
struct session_int {
	char date[20];
	char source_IP[16];
	char destination[50];
};

/*
* 'Constructor' for session
*/
void init_session(session *sp, char *when, char *from, char *to)
{
	*sp = (session)malloc(sizeof(struct session_int));
	sprintf((*sp)->date, when);
	sprintf((*sp)->source_IP, from);
	sprintf((*sp)->destination, to);
}

/*
* Getter for date
* Return date field
*/
char *get_date(session s)
{
	return (s->date);
}

/*
* Getter for source_IP
* Return source_IP field
*/
char *get_source_IP(session s)
{
	return (s->source_IP);
}

/*
* Getter for destination
* Return destination field
*/
char *get_destination(session s)
{
	return (s->destination);
}

/*
* Setter for date
* Param when value to be placed into the session's date field
*/
void set_date(session s, char *when)
{
	sprintf(s->date, when);
}

/*
* Setter for source_IP
* Param from value to be placed into the session's source_IP field
*/
void set_source_IP(session s, char *from)
{
	sprintf(s->source_IP, from);
}

/*
* Setter for destination
* Param to value to be placed into the session's source field
*/
void set_destination(session s, char *to)
{
	sprintf(s->destination, to);
}

/*
* to_string
* Return string version of session
*/
char *to_string(session s)
{
	char *r = (char *)malloc(150 * sizeof(char));

	sprintf(r, "At %s, session initiated from: %s to %s", s->date, s->source_IP, s->destination);

	return r;
}
