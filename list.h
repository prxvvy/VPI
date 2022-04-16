//
// Created by prxvvy on 10/04/2022
//

#ifndef LIST_H
#define LIST_H

#include "node.h"

typedef struct list {
  struct node *p_head;
  struct node *p_tail;
  unsigned int size;
} list_t;

list_t *create_list();

unsigned int get_len(list_t *p_list);

int insert_at_beginning(list_t *p_list, void *p_value, unsigned int is_string);

int insert_at_end(list_t *p_list, void *p_value, unsigned int is_string);

int remove_at_beginning(list_t *p_list);

int remove_at_end(list_t *p_list);

int first_entry(list_t *p_list, node_t *p_node);

int destroy_list(list_t *p_list);

int destroy_each_node(list_t *p_list);

int destroy_nested_lists(list_t *p_parent_list);

node_t *get_node_at(list_t *p_list, unsigned int index);

int unlink_node(list_t *p_list, node_t *p_node);

int insert_at(list_t *p_list, void *p_value, size_t value_size,
              unsigned int index);

#endif  // LIST_H
