// KIT107 Assignment 2
/*
* assignment_two119.c
* Implementation for driver
*
* Uncommented sample solution
*
* A program analyse which web sites students visit when
*
* they’re using their laptops on campus in 24-hour.
* Author Julian Dermoudy and Vinh Nguyen (student #470821)
* Version 2019.04.30
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "assig_two119.h"
#include "session.h"
#include "server.h"
#include "node.h"

// Global constant definitions
const int NUM_SESSIONS = 50000;	// reduce to 20 when developing
const bool DEVELOPING = true;	// set to false for truly random data
const int NUM_HOURS = 24;		// number of hours in a day

// Global type definitions are in Header file

/* Global variable declarations */
collection archive; // declaration archive 

int sessions_per_hours[24]; // The array store numbers of sessions of each hours
int sessions_per_server[7]; // the array store number of session of each server

// Function definitions
/*
* Initialise the empty archive
*/
void initialise_archive()
{
	int i; // The index of array archiver.

	for (i = 0; i < 7; i++)
	{
		archive[i] = (server)malloc(sizeof(server)); // allocate memory for archive
		archive[i] = NULL; // initializes the array archive to NULL
	}
}

/*
* Add session to a non-empty cluster in chronological order
* Param s an existing server with non-empty cluster
* Param one_session a session to be added to the cluster
*/
void add_existing(server s, session one_session)
{

	cluster new_node; // the node to insert into clusters
	cluster current_node; // point to cluster node currently being visisted 

	/* Create nodes for the one_session */
	init_node(&new_node, one_session);

	/* Begin traversing at the beginning of the clusters */
	current_node = get_sessions(s);

	/* Traverse the nodes until  the end of the clusters is reached */
	while (getNext(current_node) != NULL)
	{
		current_node = getNext(current_node);
	}
	setNext(current_node, new_node);
}

/*
* Add session to the archive (which may be empty), might be first for a server, might be second etc.
* Param one_session the session to add
*/
void add_session(session one_session)
{

	server s_temp; // server holder name one_session
	cluster new_node; // the node to insert into clusters

	int i = 0; // the index of array archiver.
	int i_hour; // the index of array "sessions_per_hours" 
	char str_time[20]; // the variable store date and time of sessions
	char delim[] = " :"; // declaration of delimiter

	/* Create nodes for the one_session */
	init_node(&new_node, one_session);

	/* Create new server holder name one_session */
	init_server(&s_temp, get_destination(one_session));

	if (archive[0] == NULL)
	{
		archive[0] = s_temp; // set element archive index 0 point to the server
			
		set_sessions(s_temp, new_node); // set new_node value to be placed into the server sessions field
	}
	else
	{
		while (i <6 && archive[i] != NULL && strcmp(get_name(archive[i]), get_destination(one_session)) != 0)
		{
			i++;
			if (archive[i] == NULL)
			{
				archive[i] = s_temp;
				set_sessions(s_temp, new_node); // set new_node value to be placed into the server's sessions field
			}
		}
	}

	/* treversing the array archive and add session to non_empty cluster*/
	for (i = 0; i < 7; i++)
	{
		if (archive[i] != NULL && strcmp(get_name(archive[i]), get_destination(one_session)) == 0)
		{

			add_existing(archive[i], one_session);
			sessions_per_server[i]++;
		}
	}

	strcpy(str_time, get_date(one_session)); // copy the date of session into character array 
	char *ptr = strtok(str_time, delim); // use of strtok to get first token 

	ptr = strtok(NULL, delim); // use of strtok to get first token 
	
	/* convert hour in type string to interger and increate number of sessions in that hour */
	i_hour = atoi(ptr);
	sessions_per_hours[i_hour] ++;
}

/*
* Generate the data and fill the archive
*/
void generate_data()
{
	const char *TARGETS[] = { "www.facebook.com", "www.whitehouse.gov",
		"www.abs.gov.au/census", "www.youtube.com", "www.snapchat.com",
		"www.google.com.au", "https://icanhas.cheezburger.com/lolcats" };
	const int NUM_TARGETS = 7;	// the number of target servers

	char *when;	// date of session
	char *from; // source of session
	char *to;	// destination for session
	session one_session; // session constructed from generated fields
	int count = 0;	// for debugging

	printf("loading");
	if (DEVELOPING)
	{
		srand(0);	// ensure predictable data
	}
	else
	{
		srand((unsigned int)time(NULL));	// randomise data
	}

	// generate the required amount of data
	for (count = 1; count <= NUM_SESSIONS; count++)
	{
		printf("...");
		// generate session components
		when = (char *)malloc(20 * sizeof(char));
		sprintf(when, "2019/03/28 %02d:%02d:%02d", rand() % 24, rand() % 60, rand() % 60);
		from = (char *)malloc(16 * sizeof(char));
		sprintf(from, "010.100.%03d.%03d", rand() % (256 - 224) + 224, rand() % 256);
		to = (char *)malloc(50 * sizeof(char));
		sprintf(to, "%s", TARGETS[rand() % NUM_TARGETS]);

		// make a session with the generated components
		init_session(&one_session, when, from, to);

		printf("\b\b\b");
//printf("%s\n", to_string(one_session));/*DEBUG*/

											   // add session to collection
//printf("calling add_session\n");/*DEBUG*/
		add_session(one_session);
//printf("add_session concluded\n");/*DEBUG*/
	}
//rintf("...data generation complete!\n\n");/*DEBUG*/
	printf("\b\b\b\b\b\b\b");
}

/*
* Calculate and show the summary of the archive grouped by servers
*/
void show_servers()
{
	int i_ser; // index of array sessions_per_server
	int max_server = 0; // Initialize maximum element in array sessions_per_server

	printf("\n");
	printf("Total session per server:\n");
	printf("-------------------------\n");

	char *name_server; // variable store current server name is holder largest sessions in array

	/* allocate enough memory to store the name of servers */
	name_server = (char*)malloc(50 * sizeof(char));


	/* Traverse and display number of sessions store in groups server.
	* Also, compare every array elements with current max  */
	for (i_ser = 0; i_ser < 7; i_ser++)
	{
		/* display numbers of sessions store in groups server */
		printf("%s: %d\n", get_name(archive[i_ser]), sessions_per_server[i_ser]);

		if (sessions_per_server[i_ser]> max_server) 
		{
			max_server = sessions_per_server[i_ser];
			name_server = get_name(archive[i_ser]);
		}
	}
	/* display the server is holder largest sessions */
	printf("\n");
	printf("Most popular: %s (%d sessions of %d)\n", name_server, max_server, NUM_SESSIONS);
	printf("\n");

}

/*
* Calculate and show the summary of the archive grouped by hours
*/
void show_times()
{
	printf("Total session per hour:\n");
	printf("-----------------------\n");
	int i; // index of array session_per_hours
	int max = 0; // Initialize maximum element 

	/* Traverse and display numbers of sessions store in group hours */
	for (i = 0; i < NUM_HOURS; i++)
	{
		if (i % 2 == 1)
		{
			printf("%02d: %2d\n", i, sessions_per_hours[i]);
		}
		else
		{
			printf("%02d: %2d%16s", i, sessions_per_hours[i], "");
		}
	}
	int i_max; // the current index of the array holder the largest sessions in the array.

	/* Traverse array elements and compare every element with the current max */
	for (i = 0; i < NUM_HOURS; i++)
	{
		
		if (sessions_per_hours[i] > max) // if current element large than max 
		{
			max = sessions_per_hours[i]; // set max for that element
			i_max = i; 
		}
	}
	/* display the time(hour) is holder largest of sessions in 24 hours */
	printf("\n");
	printf("Most popular: %02d hours (%d sessions of %d)\n", i_max, max, NUM_SESSIONS);
	printf("\n");
}

/*
* Convert the given text to lower-case and return it
* Param text the string to be converted
* Return char * lower-case version of text
*/
char *to_lower(char *text)
{
	char *r; // result
	int i;	 // loop counter

			 // create enough space for copy of text
	r = (char *)malloc((strlen(text) + 1) * sizeof(char));

	// copy (to lower-case) each character of text
	for (i = 0; i < strlen(text); i++)
	{
		r[i] = tolower(text[i]);
	}
	// terminate copy string
	r[i] = '\0';

	// return result
	return r;
}

/*
* Find and display sessions in the archive containing case-insensitive text in
*	either date, source_IP, or destination field
* Param text the string to be located
*/


void show_selection(char *text)
{

	int i; // index of array archive
	i = 0;
	printf("Showing all sessions containing \"%s\"\n", text);
	printf("--------------------------------------\n");

	cluster temp_node; // point to the current node as the list is traversed
	
	/* treversing the array archive until the end of the array */
	for (i = 0; i < 7; i++)
	{
		temp_node = get_sessions(archive[i]);
		temp_node = getNext(temp_node);

		/* Traverse the nodes until the end of cluster is reached */
		while (temp_node != NULL)
		{
			/* Checks if given text can be found in session, if so print that session */
			if (strstr(to_string(getData(temp_node)), text) != NULL)
			{
				printf("%s\n", to_string(getData(temp_node)));
			}			
			temp_node = getNext(temp_node);
		}
	}
	printf("\n");
}


/*
* Menu function to drive user's choice
*/
void menu()
{
	const int QUIT = 4;	// value to end the execution

	int choice;	// user's selection
	char text[300];	// text of choice

					// show title
	printf("On-campus Wifi Activity\n");
	printf("=======================\n\n");

	do
	{
		// show options and get choice
		printf("1. Show summary by server\n");
		printf("2. Show summary by hour\n");
		printf("3. Show sessions containing specified text\n");
		printf("4. Exit (default)\n");
		printf("\nChoice #");
		scanf("%d", &choice);

		// process choice
		switch (choice)
		{
		case 1:	// show summary by server
			show_servers();
			break;
		case 2:	// show summary by hour
			show_times();
			break;
		case 3:	// search
				// get text
			printf("\nEnter text: ");
			scanf("%s", text);
			// product output
			show_selection(text);
			break;
		default:// exit desired
			choice = QUIT;
			break;
		}
	} while (choice != QUIT);
}

/*
* Entry point
* Param argc the argument count
* Param argv the  argument vector
* Return int error code
*/
int main(int argc, char *argv[])
{
	initialise_archive();
	generate_data();
	menu();

	return 0;
}