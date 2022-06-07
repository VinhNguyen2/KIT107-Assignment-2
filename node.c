// KIT107 Assignment 2: Node
/*
* Implementation for Node
* Author Julian Dermoudy and Vinh Nguyen (student #470821)
* Version 27/4/2018
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"


struct node_int {
	void *data;
	cluster next;
};


/*
* 'Initialiser' for node
*/
void init_node(cluster *np, void *o)
{
	*np = (cluster)malloc(sizeof(struct node_int));
	(*np)->data = o;
	(*np)->next = NULL;
}

/*
* Getter for data
* Return data field
*/
void *getData(cluster n)
{
	return n->data;
}

/*
* Getter for next
* Return next field
*/
cluster getNext(cluster n)
{
 	return n->next;
}

/*
* Setter for data
* Param o value to be placed into the node's data field
*/
void setData(cluster n, void *o)
{
	n->next = o;
}

/*
* Setter for next
* Param o value to be placed into the node's next field
*/
void setNext(cluster v, cluster n)
{
	v->next = n;
}


