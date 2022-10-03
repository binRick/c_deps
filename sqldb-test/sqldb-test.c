#include "generic-print/print.h"
#include "log/log.h"
#include "sqldb-test.h"
#include "submodules/c_greatest/greatest/greatest.h"
#include <assert.h>
#include <inttypes.h>
#include <math.h>
////////////////////////////////////////////////////////
#define ASSERT_SQLDB_RESULT()    { do {                                \
                                     ASSERT_EQ(rc, SQLDBAL_STATUS_OK); \
                                   } while (0); }

////////////////////////////////////////////////////////
TEST t_sqldb(void){
  int64_t                  ts = -1, qty = -1, rowid = -1, ins_id = -1, ins_item_id = -1, created_ts = -1;
  enum sqldbal_status_code rc;
  struct sqldbal_db        *db;
  struct sqldbal_stmt      *stmt;
  const char               *text, *_created;
  char                     ts_s[1024];

  rc = sqldbal_open(SQLDBAL_DRIVER_SQLITE, LOCATION, NULL, NULL, NULL, NULL, FLAGS, NULL, 0, &db);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_exec(db, "PRAGMA foreign_keys = ON", NULL, NULL);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_exec(db,
                    "\
CREATE TABLE IF NOT EXISTS test(\
 _id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT\
, _created  DATETIME NOT NULL DEFAULT (datetime(CURRENT_TIMESTAMP, 'localtime'))\
, ts INTEGER NOT NULL\
, str VARCHAR(20) NOT NULL\
)",
                    NULL,
                    NULL);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_exec(db,
                    "\
CREATE TABLE IF NOT EXISTS test_items(\
 _id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT\
, _created  DATETIME NOT NULL DEFAULT (datetime(CURRENT_TIMESTAMP, 'localtime'))\
, test_id INTEGER NOT NULL\
, str VARCHAR(20) NOT NULL\
, CONSTRAINT fk_test_ids FOREIGN KEY (test_id) REFERENCES test(_id)\
  ON DELETE CASCADE ON UPDATE CASCADE\
)",
                    NULL,
                    NULL);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_stmt_prepare(db,
                            "DELETE FROM test",
                            -1,
                            &stmt);
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_stmt_prepare(db,
                            "DELETE FROM test_items",
                            -1,
                            &stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
  printf(
    AC_RESETALL AC_BRIGHT_RED ">DELETED all rows\n" AC_RESETALL
    );
  rc = sqldbal_stmt_close(stmt);
  ASSERT_EQ(rc, SQLDBAL_STATUS_OK);

  for (size_t i = 0; i < INSERT_QTY; i++) {
    ts = timestamp();
    sprintf(ts_s, "%llu", ts);
    rc = sqldbal_stmt_prepare(db,
                              "INSERT INTO test(ts, str) VALUES(?, ?)",
                              -1,
                              &stmt);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_bind_int64(stmt, 0, ts);
    ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
    rc = sqldbal_stmt_bind_text(stmt, 1, ts_s, -1);
    ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
    rc = sqldbal_stmt_execute(stmt);
    ASSERT_SQLDB_RESULT();

    ins_id = -1;
    rc     = sqldbal_last_insert_id(db, "test_id_seq", &ins_id);
    ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
    ASSERT_GTE(ins_id, 1);
    rc = sqldbal_stmt_close(stmt);
    ASSERT_SQLDB_RESULT();

    for (size_t ii = 0; ii < INSERT_QTY; ii++) {
      rc = sqldbal_stmt_prepare(db, "INSERT INTO test_items(test_id, str) VALUES(?, ?)", -1, &stmt);
      ASSERT_SQLDB_RESULT();
      rc = sqldbal_stmt_bind_int64(stmt, 0, ins_id);
      ASSERT_SQLDB_RESULT();
      rc = sqldbal_stmt_bind_text(stmt, 1, ts_s, -1);
      ASSERT_SQLDB_RESULT();
      rc = sqldbal_stmt_execute(stmt);
      ASSERT_SQLDB_RESULT();
      ins_item_id = -1;
      rc          = sqldbal_last_insert_id(db, "test_items_id_seq", &ins_item_id);
      ASSERT_EQ(rc, SQLDBAL_STATUS_OK);
      ASSERT_GTE(ins_item_id, 1);
      rc = sqldbal_stmt_close(stmt);
      ASSERT_SQLDB_RESULT();
    }
  }

  rc = sqldbal_stmt_prepare(db,
                            "SELECT COUNT(*) FROM test",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &qty);
    ASSERT_SQLDB_RESULT();
    printf(
      AC_RESETALL AC_YELLOW ">%llu test rows\n" AC_RESETALL,
      qty
      );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();

  rc = sqldbal_stmt_prepare(db,
                            "SELECT COUNT(*) FROM test_items",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &qty);
    ASSERT_SQLDB_RESULT();
    printf(
      AC_RESETALL AC_YELLOW ">%llu test_item rows\n" AC_RESETALL,
      qty
      );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();

  rc = sqldbal_stmt_prepare(db,
                            "DELETE from test where _id = ?",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_bind_int64(stmt, 0, INSERT_QTY);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();

  rc = sqldbal_stmt_prepare(db,
                            "SELECT COUNT(*) FROM test_items",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &qty);
    ASSERT_SQLDB_RESULT();
    printf(
      AC_RESETALL AC_YELLOW ">%llu test_item rows\n" AC_RESETALL,
      qty
      );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();

  rc = sqldbal_stmt_prepare(db,
                            "SELECT\
  _id\
, _created\
, ts\
, str\
, CAST(((julianday(_created)-2440587.5)*86400) as created_ts)\
  FROM test",
                            -1,
                            &stmt);
  ASSERT_SQLDB_RESULT();
  rc = sqldbal_stmt_execute(stmt);
  ASSERT_SQLDB_RESULT();
  while (sqldbal_stmt_fetch(stmt) == SQLDBAL_FETCH_ROW) {
    rc = sqldbal_stmt_column_int64(stmt, 0, &rowid);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_text(stmt, 1, &_created, NULL);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_int64(stmt, 2, &ts);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_text(stmt, 3, &text, NULL);
    ASSERT_SQLDB_RESULT();
    rc = sqldbal_stmt_column_int64(stmt, 4, &created_ts);
    ASSERT_SQLDB_RESULT();
    fprintf(stderr,
            AC_RESETALL AC_CYAN "#%llu> %llu / %s|_created:%s|created_ts:%llu|\n" AC_RESETALL,
            rowid, ts, text, _created, created_ts
            );
  }
  rc = sqldbal_stmt_close(stmt);
  ASSERT_SQLDB_RESULT();

  rc = sqldbal_close(db);
  ASSERT_SQLDB_RESULT();
  PASS();
} /* t_sqldb */

SUITE(s_sqldb){
  RUN_TEST(t_sqldb);
  PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_sqldb);
  GREATEST_MAIN_END();
  return(0);
}
