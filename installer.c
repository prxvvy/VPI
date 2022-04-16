#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "list.h"

typedef struct plugin {
  char *p_author;
  char *p_name;
  char *p_category;
} plugin_t;

/* function declarations */
list_t *parse_plugins_from_arr();
list_t *assemble_plugins();
plugin_t *create_plugin(char *p_author, char *p_name, char *p_category);
int destroy_plugin(plugin_t *p_plugin);
int destroy_nested_lists(list_t *p_parent_list);
int destroy_plugins(list_t *p_plugins_list);
int install_plugins();
/* variables */
static const int arrpluginslen = sizeof(plugins) / sizeof(plugins[0]);
/* function implementations */
int destroy_nested_lists(list_t *p_parent_list) {
  if (get_len(p_parent_list) == 0) return 0;
  for (unsigned int i = 0; i < get_len(p_parent_list); ++i) {
    destroy_each_node(get_node_at(p_parent_list, i)->p_value);
    destroy_list(get_node_at(p_parent_list, i)->p_value);
  }
  destroy_each_node(p_parent_list);
  destroy_list(p_parent_list);
  return 1;
}

list_t *parse_plugins_from_arr() {
  list_t *p_plugins_list = create_list();
  char *p_token;
  for (int i = 0; i < arrpluginslen; ++i) {
    char *p_plugin = calloc(strlen(plugins[0]) + 1, sizeof(char));
    strcpy(p_plugin, plugins[0]);
    list_t *p_plugin_components = create_list();
    insert_at_end(p_plugins_list, p_plugin_components, 0);
    p_token = strtok(p_plugin, separator);
    while (p_token) {
      insert_at_end(p_plugin_components, p_token, 1);
      p_token = strtok(NULL, separator);
    }
    free(p_plugin);
  }
  return p_plugins_list;
}

list_t *assemble_plugins(list_t *p_plugins_list) {
  list_t *p_plugins = create_list();
  for (unsigned int i = 0; i < get_len(p_plugins_list); ++i) {
    char *p_author =
        get_node_at(get_node_at(p_plugins_list, i)->p_value, 0)->p_value;
    char *p_name =
        get_node_at(get_node_at(p_plugins_list, i)->p_value, 1)->p_value;
    char *p_category =
        get_node_at(get_node_at(p_plugins_list, i)->p_value, 2)->p_value;
    plugin_t *p_plugin = create_plugin(p_author, p_name, p_category);
    insert_at_end(p_plugins, p_plugin, 0);
  }

  destroy_nested_lists(p_plugins_list);

  return p_plugins;
}

plugin_t *create_plugin(char *p_author, char *p_name, char *p_category) {
  plugin_t *p_self = calloc(1, sizeof(struct plugin));
  p_self->p_author = calloc(strlen(p_author) + 1, sizeof(char));
  strcpy(p_self->p_author, p_author);
  p_self->p_name = calloc(strlen(p_name) + 1, sizeof(char));
  strcpy(p_self->p_name, p_name);
  p_self->p_category = calloc(strlen(p_category) + 1, sizeof(char));
  strcpy(p_self->p_category, p_category);
  return p_self;
}

int destroy_plugin(plugin_t *p_plugin) {
  free(p_plugin->p_author);
  free(p_plugin->p_name);
  free(p_plugin->p_category);
  free(p_plugin);
  return 1;
}

int destroy_plugins(list_t *p_plugins_list) {
  if (get_len(p_plugins_list) == 0) return 0;
  for (unsigned int i = 0; i < get_len(p_plugins_list); ++i) {
    destroy_plugin(get_node_at(p_plugins_list, i)->p_value);
  }
  destroy_each_node(p_plugins_list);
  destroy_list(p_plugins_list);
  return 1;
}

int install_plugins() {
  list_t *p_plugins = assemble_plugins(parse_plugins_from_arr());
  for (unsigned int i = 0; i < get_len(p_plugins); ++i) {
    printf("%s\n", ((plugin_t *)get_node_at(p_plugins, i)->p_value)->p_author);
  }

  destroy_plugins(p_plugins);

  return 1;
}

int main() {
  install_plugins();
  return 0;
}
