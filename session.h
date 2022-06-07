// KIT107 Assignment 2
/*
* Specification for the Session ADT
* Author Julian Dermoudy
* Version 30/3/19
*
* THIS FILE IS COMPLETE
*/

#ifndef SESSION_H
#define SESSION_H

struct session_int;
typedef struct session_int *session;

void init_session(session *sp, char *when, char *from, char *to);
char *get_date(session s);
char *get_source_IP(session s);
char *get_destination(session s);
void set_date(session s, char *when);
void set_source_IP(session s, char *from);
void set_destination(session s, char *to);
char *to_string(session s);

#endif