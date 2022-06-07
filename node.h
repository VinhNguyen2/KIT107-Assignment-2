// KIT107 Assignmet 2: Node
/*
* Specification for the Node ADT
* Author Julian Dermoudy and Vinh Nguyen (student #470821)
* Version 27/4/18
*/

#include <stdbool.h>

#ifndef NODE_H
#define NODE_H

struct node_int;
typedef struct node_int *cluster;

void init_node(cluster *vp, void *o);
void setData(cluster v, void *o);
void setNext(cluster v, cluster n);
void *getData(cluster v);
cluster getNext(cluster v);

#endif