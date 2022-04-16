//
// Created by prxvvy on 10/04/2022
//

#ifndef NODE_H
#define NODE_H

#include <stddef.h>

typedef struct node {
  void *p_value;
  struct node *p_next;
  struct node *p_previous;
  unsigned int is_containing_string;
} node_t;

node_t *create_node(void *p_value, unsigned int is_string);

int destroy_node(node_t *p_node);

#endif  // NODE_H
