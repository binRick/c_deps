#pragma once
#include <sqxclib.h>
#include <stdio.h>

typedef struct Post   Post;
typedef struct City   City;
typedef struct User   User;

struct Post {
  char *title;
  char *desc;
};

struct City {
  int  id;
  char *name;
  bool visited;
};

struct User {
  int           id;        // primary key
  char          *name;
  char          *email;
  int           city_id;   // foreign key

  // make sure that SQ_CONFIG_HAVE_JSONC is enabled if you want to store array/object in SQL column
  SqIntptrArray ints;           // intptr_t array (JSON array  in SQL column)
  Post          *post;          // object pointer (JSON object in SQL column)

  time_t        created_at;
  time_t        updated_at;

  // add, drop, and rename
  unsigned int  test_add;
  unsigned int  test_drop;
  unsigned int  test_rename;
};
