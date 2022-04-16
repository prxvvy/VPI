#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "list.h"
#include "util.h"

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
char *__str_plugin__(plugin_t *p_plugin);
char *assemble_path_installation(plugin_t *p_plugin);
char *git_installation_cmd(char *p_path, char *p_githubURL, int b_special);
int init_start_dirs();
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

char *__str_plugin__(plugin_t *p_plugin) {
  // https://github.com/author/pluginName.git
  char *p_githubURL = "https://github.com";
  size_t githubURLLen = strlen(p_githubURL);
  size_t authorLen = strlen(p_plugin->p_author);
  size_t nameLen = strlen(p_plugin->p_name);
  size_t slashLen = strlen("/");
  size_t dotGitLen = strlen(".git");
  size_t totalLen =
      githubURLLen + slashLen + authorLen + slashLen + nameLen + dotGitLen + 1;
  char *p_gitRepoURL = calloc(totalLen, sizeof(char));
  sprintf(p_gitRepoURL, "%s/%s/%s.git", p_githubURL, p_plugin->p_author,
          p_plugin->p_name);
  return p_gitRepoURL;
}

char *assemble_path_installation(plugin_t *p_plugin) {
  char *p_pathInstallation =
      calloc((is_equal_to(p_plugin->p_category, "ide") == 1
                  ? strlen(idepluginspath)
                  : strlen(appearancepluginspath)) +
                 strlen("/") + strlen(p_plugin->p_name) + 1,
             sizeof(char));
  if (is_equal_to(p_plugin->p_category, "ide") == 1) {
    sprintf(p_pathInstallation, "%s/%s", idepluginspath, p_plugin->p_name);
  } else if (is_equal_to(p_plugin->p_category, "appearance") == 1) {
    sprintf(p_pathInstallation, "%s/%s", appearancepluginspath,
            p_plugin->p_name);
  } else if (is_equal_to(p_plugin->p_category, "appearance") == 1) {
  } else {
    printf("Invalid category.\n");
    exit(0);
  }
  return p_pathInstallation;
}

char *git_installation_cmd(char *p_path, char *p_githubURL, int b_special) {
  char *p_git_clone =
      b_special == 1 ? "git clone --branch release " : "git clone ";

  size_t totalSize =
      b_special == 1 ? strlen(p_git_clone) + strlen(p_githubURL) + strlen(" ") +
                           strlen(p_path) + strlen(" --depth=1") + 1
                     : strlen(p_git_clone) + strlen(p_githubURL) + strlen(" ") +
                           strlen(p_path) + 1;
  char *p_cmd = calloc(totalSize, sizeof(char));
  if (b_special == 1) {
    sprintf(p_cmd, "%s%s %s --depth=1", p_git_clone, p_githubURL, p_path);
  } else {
    sprintf(p_cmd, "%s%s %s", p_git_clone, p_githubURL, p_path);
  }

  return p_cmd;
}

int init_start_dirs() {
  int rmCode, mkdirCode;

  printf("Removing existing plugins for a fresh installation...\n");

  rmCode = rmrf((char *)idepluginspath);
  if (rmCode == -1) {
    printf("Something went wrong removing \"%s\". Exit code: %d\n",
           idepluginspath, rmCode);
    return 0;
  }
  printf("Successfully removed existing autocompletion plugins.\n");

  rmCode = rmrf((char *)appearancepluginspath);
  if (rmCode == -1) {
    printf("Something went wrong removing \"%s\". Exit code: %d\n",
           appearancepluginspath, rmCode);
    return 0;
  }

  printf("Successfully removed existing theme plugins.\n\n\n");

  printf("Creating new start directories for plugins...\n");

  mkdirCode = mkdir(idepluginspath, 0700);

  if (mkdirCode == -1) {
    printf("Something went wrong trying to create \"%s\". Exit code: %d\n",
           idepluginspath, mkdirCode);
    return 0;
  }

  printf("Successfully created new start directory for ide plugins.\n");

  mkdirCode = mkdir(appearancepluginspath, 0700);

  if (mkdirCode == -1) {
    printf("Something went wrong trying to create \"%s\". Exit code: %d\n",
           appearancepluginspath, mkdirCode);
    return 0;
  }

  printf("Successfully created new start directory for appearance plugins.\n");

  return 1;
}

int install_plugins() {
  init_start_dirs();
  list_t *p_plugins = assemble_plugins(parse_plugins_from_arr());
  for (unsigned int i = 0; i < get_len(p_plugins); ++i) {
    char *p_plugin_name =
        ((plugin_t *)get_node_at(p_plugins, i)->p_value)->p_name;
    char *p_plugin_category =
        ((plugin_t *)get_node_at(p_plugins, i)->p_value)->p_category;
    char *p_gitRepoURL =
        __str_plugin__((plugin_t *)get_node_at(p_plugins, i)->p_value);
    char *p_path =
        assemble_path_installation(get_node_at(p_plugins, i)->p_value);
    if (is_equal_to(p_plugin_name, "coc.nvim") == 1) {
      char *p_git_clone = git_installation_cmd(p_path, p_gitRepoURL, 1);
      printf("Adding special plugin \"%s\" to %s category directory...\n",
             p_plugin_name, p_plugin_category);
      system(p_git_clone);
      printf("Added special plugin \"%s\" to %s category directory.\n",
             p_plugin_name, p_plugin_category);

      free(p_git_clone);
    }

    if (is_equal_to(p_plugin_category, "ide") == 1) {
      char *p_git_clone = git_installation_cmd(p_path, p_gitRepoURL, 0);
      printf("Adding plugin \"%s\" to %s category directory...\n",
             p_plugin_name, p_plugin_category);
      system(p_git_clone);
      printf("Added plugin \"%s\" to %s category directory.\n", p_plugin_name,
             p_plugin_category);

      free(p_git_clone);
    } else if (is_equal_to(p_plugin_category, "appearance") == 1) {
      char *p_git_clone = git_installation_cmd(p_path, p_gitRepoURL, 0);
      printf("Adding plugin \"%s\" to %s category directory...\n",
             p_plugin_name, p_plugin_category);
      system(p_git_clone);
      printf("Added plugin \"%s\" to %s category directory.\n", p_plugin_name,
             p_plugin_category);

      free(p_git_clone);

    } else {
      printf("Didn't install because of invalid category.\n");
      exit(0);
    }
    free(p_path);
    free(p_gitRepoURL);
  }

  destroy_plugins(p_plugins);

  return 1;
}

int main() {
  install_plugins();
  return 0;
}
