#pragma once
#include "../submodules/b64.c/b64.h"
#include "../submodules/c_timer/include/c_timer.h"
#include "../submodules/chan/src/chan.h"
#include "../submodules/ctable/src/string_util.h"
#include "../submodules/ctable/src/table.h"
#include "../submodules/list/src/list.h"
#include "../submodules/reproc/reproc/include/reproc/export.h"
#include "../submodules/reproc/reproc/include/reproc/reproc.h"
#include "../submodules/rhash_md5.c/md5.h"
#include "../submodules/tiny-regex-c/re.h"
#include "../submodules/which/src/which.h"
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "cargs/include/cargs.h"
#include "parson.h"
#include "pthread.h"
#include "submodules/assertf/assertf.h"
#include "submodules/b64.c/b64.h"
#include "submodules/bytes/bytes.h"
#include "submodules/c_vector/include/vector.h"
#include "submodules/dbg/dbg.h"
#include "submodules/ee.c/src/ee.h"
#include "submodules/greatest/greatest.h"
#include "submodules/log.h/log.h"
#include "submodules/ms/ms.h"
#include "submodules/path-normalize.c/src/path-normalize.h"
#include "submodules/progress.c/progress.h"
#include "submodules/subprocess.h/subprocess.h"
#include "submodules/timestamp/timestamp.h"
#include "submodules/tinydir/tinydir.h"
#include "submodules/wildcardcmp/wildcardcmp.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define F_RED        "\x1B[1;31m"
#define F_GREEN      "\x1B[1;32m"
#define F_YELLOW     "\x1B[1;33m"
#define F_INVERSE    "\x1B[7m"
#define COL_RESET    "\x1B[0m"
static char *introspect_meson_build_file_in_subprocess(char *MESON_BUILD_FILE);

typedef void (*ee_target_handler)(JSON_Object *Target);

typedef enum {                           //         Repo Item Type
  REPO_ITEM_STATIC_LIBRARY = 1,
  REPO_ITEM_LIBRARY        = 2,
  REPO_ITEM_EXECUTABLE     = 3,
} repo_item_type_t;

typedef struct {                        //         Repo Item
  char             *name;
  repo_item_type_t type;
} repo_item_t;

typedef struct {                       //          Repo comprised of repo types
  char        *name;
  repo_item_t **types;
  size_t      items_qty;
} repo_t;

typedef struct {                       //          List of repos
  repo_t *repos;
  size_t repos_qty;
} repos_t;

//////////////////////////////////////////////////////////////
repos_t init_repos(); //    initialize a list of repos
repo_t init_repo();   //    initialize a repo

//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
void add_repo(repos_t **REPOS, repo_t *REPO);             //   add a repo to list of repos
repo_t parse_repo_type(JSON_Object *O);
void add_repo_type(repo_t *repo, repo_item_t *repo_item); //     add a repo item to repo

//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
struct Vector * get_meson_paths(char *BASE_PATH, char *PATH_FILTER, size_t PATH_LIMIT);                           //   get a list of meson.build paths
void iterate_paths(struct Vector *MESON_PATHS);
void iterate_free(struct Vector *VECTOR);
void iterate_parse_results(struct Vector *MESON_RESULTS);
size_t iterate_get_total_size(struct Vector *VECTOR);
void free_paths(struct Vector *MESON_PATHS);
void iterate_print(struct Vector *VECTOR);
struct Vector * execute_meson_introspects(struct Vector *MESON_PATHS);

//////////////////////////////////////////////////////////////


char *execute_processes();
JSON_Array *parse_execution_result(char *OUTPUT);
void iterate_targets(ee_t *ee, JSON_Array *A);
