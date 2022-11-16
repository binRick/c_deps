#include <inttypes.h>   // PRId64, PRIu64
#include <stdio.h>

#include "CStructs.h"  // struct User
#include "sqxclib.h"
#include <SqApp.h>

typedef struct MyApp MyApp;

struct MyApp {
  SqApp base;

  // user data
};

MyApp *my_app_new(){
  MyApp *myapp;

  myapp = malloc(sizeof(MyApp));
  // 'SQ_APP_DEFAULT' has database settings and migration data for user application.
  sq_app_init(&myapp->base, SQ_APP_DEFAULT);

  return(myapp);
}

void  my_app_free(MyApp *myapp){
  sq_app_final(&myapp->base);
  free(myapp);
}

int  main(void){
  MyApp *myapp;

  myapp = my_app_new();

#if 0
  // open database that defined in SqApp-config.h
  if (sq_app_open_database(&myapp->base, NULL) != SQCODE_OK)
    return(EXIT_FAILURE);


#else
  // open user specified database
  if (sq_app_open_database(&myapp->base, "myapp-db") != SQCODE_OK)
    return(EXIT_FAILURE);


#endif

  /*	If you use command-line program "sqxctool" to do migrate,
   *      you can remove below sq_app_migrate() code.
   */
  // if the version of schema in database is 0 (no migrations have been done)
  if (sq_app_make_schema(&myapp->base, 0) == SQCODE_DB_SCHEMA_VERSION_0)
    // run migrations that defined in ../database/migrations
    if (sq_app_migrate(&myapp->base, 0) != SQCODE_OK)
      return(EXIT_FAILURE);


  /*	SQL table "users" defined in  database/migrations/2021_10_12_000000_create_users_table.c
   *      strcut User defined in  sqxcapp/CStructs.h
   */
  SqStorage *storage = myapp->base.storage;
  User      user     = { 0 };
  User      *user_ptr;
  int64_t   id[2];
  int64_t   n;

  user.age   = 18;
  user.email = "alex@guest";
  user.name  = "Alex";
  id[0]      = sq_storage_insert(storage, "users", NULL, &user);
  user.age   = 28;
  user.name  = "Alan";
  user.email = "alan@guest";
  id[1]      = sq_storage_insert(storage, "users", NULL, &user);

  // update columns - "age" and "name"
  user.age  = 21;
  user.name = "Ti";
  n         = sq_storage_update_all(storage, "users", NULL, &user,
                                    "WHERE id > 0",
                                    "age", "name",
                                    NULL);
  printf("number of rows changed : %" PRId64 "\n", n);

  user_ptr = sq_storage_get(storage, "users", NULL, id[0]);
  if (user_ptr)
    printf("\n"
           "User::age   = %d" "\n"
           "User::name  = %s" "\n"
           "User::email = %s" "\n",
           user_ptr->age,
           user_ptr->name,
           user_ptr->email);

#if SQ_CONFIG_HAS_STORAGE_UPDATE_FIELD
  // update fields - User::name and User::email
  user.age   = 38;
  user.name  = "Sky";
  user.email = "sky@host";
  n          = sq_storage_update_field(storage, "users", NULL, &user,
                                       "WHERE id > 0",
                                       offsetof(User, name),
                                       offsetof(User, email),
                                       -1);
  printf("number of rows changed : %" PRId64 "\n", n);
#endif  // SQ_CONFIG_HAS_STORAGE_UPDATE_FIELD

  user_ptr = sq_storage_get(storage, "users", NULL, id[1]);
  if (user_ptr)
    printf("\n"
           "User::age   = %d" "\n"
           "User::name  = %s" "\n"
           "User::email = %s" "\n",
           user_ptr->age,
           user_ptr->name,
           user_ptr->email);

  sq_storage_remove_all(storage, "users", NULL);

  sq_app_close_database(&myapp->base);
  my_app_free(myapp);

  return(EXIT_SUCCESS);
} /* main */
