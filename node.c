//
// Created by prxvvy on 10/04/2022
//

#include "node.h"

#include <stdlib.h>
#include <string.h>

node_t *create_node(void *p_value, unsigned int is_string) {
  node_t *p_self = calloc(1, sizeof(struct node));
  p_self->p_next = NULL;
  p_self->p_previous = NULL;
  if (is_string == 1) {
    p_self->p_value = calloc(strlen(p_value) + 1, sizeof(char));
    strcpy(p_self->p_value, p_value);
    p_self->is_containing_string = 1;
  } else {
    p_self->p_value = p_value;
    p_self->is_containing_string = 0;
  }
  return p_self;
}

int destroy_node(node_t *p_node) {
  if (p_node->is_containing_string == 1) free(p_node->p_value);
  free(p_node);
  return 1;
}
