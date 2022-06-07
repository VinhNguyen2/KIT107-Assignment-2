// KIT107 Assignment 2
/*
* Implementation for Server
* Author Julian Dermoudy
* Version 28/3/19
*
* THIS FILE IS OMPLETE
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "assig_two119.h"
#include "node.h"

/*
* Definition of server type
*/
struct server_int {
	char name[50];
	cluster sessions;
};


/*
* 'Constructor' for server
*/
void init_server(server *sp, char *who)
{
	*sp = (server)malloc(sizeof(struct server_int));
	sprintf((*sp)->name, who);
	(*sp)->sessions = NULL;
}

/*
* Getter for name
* Return name field
*/
char *get_name(server s)
{
	return (s->name);
}

/*
* Getter for sessions
* Return sessions field
*/
cluster get_sessions(server s)
{
	return (s->sessions);
}

/*
* Setter for name
* Param who value to be placed into the servers's name field
*/
void set_name(server s, char *who)
{
	sprintf(s->name, who);
}

/*
* Setter for sessions
* Param c value to be placed into the server's sessions field
*/
void set_sessions(server s, cluster c)
{
	s->sessions = c;
}