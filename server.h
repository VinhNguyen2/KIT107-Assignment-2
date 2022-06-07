// KIT107 Assignment 2
/*
* Specification for the Server ADT
* Author Julian Dermoudy
* Version 30/3/19
*
* THIS FILE IS COMPLETE
*/

#ifndef SERVER_H
#define SERVER_H

#include "node.h"
struct server_int;
typedef struct server_int *server;

void init_server(server *sp, char *who);
char *get_name(server s);
cluster get_sessions(server s);
void set_name(server s, char *who);
void set_sessions(server s, cluster c);

#endif