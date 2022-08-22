#define MKCREFLECT_IMPL
#include "../submodules/generic-print/print.h"
#include "../submodules/log.h/log.h"
#include "reflect-test.h"
#include "submodules/c_greatest/greatest/greatest.h"
#include <assert.h>
#include <inttypes.h>
#include <math.h>
////////////////////////////////////////////////////////

Address    addresses[] = {
  { .street = "henry", .number = 1279, },
};

TestStruct test_structs[] = {
  {
    .i    = -100, .i0 = -666, .l = -12345, .ul = 999999, .s = 22222223232,
    .sh   = -12, .ui = 66123, .ll = -9912323, .ull = 22222222211,
    .name = "MY NAME", .n = "k", .n0 = "",
  },
};

size_t get_field_name_size(const char *FIELD_NAME){
  for (size_t i = 0; i < S_FIELDS_COUNT(TestStruct); i++) {
    MKCREFLECT_FieldInfo *F = &S_INFO(TestStruct)()->fields[i];
    if (strcmp(FIELD_NAME, F->field_name) == 0) {
      return(F->size);
    }
  }
  return(-1);
}

void *get_struct_field_name(void *STRUCT, const char *FIELD_NAME){
  void   *FIELD             = NULL;
  size_t FIELD_LEN          = -1;
  int    FIELD_DATA_TYPE_ID = -1;
  bool   VALID_FIELD        = false;
  int    IS_SIGNED          = -1;

  for (size_t i = 0; (i < S_FIELDS_COUNT(TestStruct)) && (FIELD == NULL); i++) {
    MKCREFLECT_FieldInfo *F = &S_INFO(TestStruct)()->fields[i];
    FIELD_DATA_TYPE_ID = (int)F->data_type;
    IS_SIGNED          = F->is_signed;
    if (strcmp(FIELD_NAME, F->field_name) == 0) {
      dbg(F->field_type, % s);
      switch (F->data_type) {
      case MKCREFLECT_TYPES_INTEGER:
        FIELD = calloc(1, F->size);
        memcpy(FIELD, (STRUCT + F->offset), F->size);
        if (F->is_signed) {
          if (strcmp(F->field_type, "int") == 0) {
            FIELD = *(int *)FIELD;
          }else if (strcmp(F->field_type, "short") == 0) {
            FIELD = *(short *)FIELD;
          }else{
            FIELD = *(long long *)FIELD;
          }
        }else{
          FIELD = *(size_t *)FIELD;
        }
        FIELD_LEN = ((long long)FIELD == 0) ? 1 : (int)log10(abs((long long)FIELD)) + 1;
        break;
      case MKCREFLECT_TYPES_STRING:
        FIELD = calloc(F->size + 1, 1);
        memcpy(FIELD, (STRUCT + F->offset), F->size);
        FIELD     = (char *)FIELD;
        FIELD_LEN = strlen(FIELD);
        break;
      }
    }
  }
  switch (FIELD_DATA_TYPE_ID) {
  case MKCREFLECT_TYPES_INTEGER:
    if (FIELD_LEN > 0) {
      VALID_FIELD = true;
      dbg((long long)FIELD, % ld);
      PRINT("valid integer field!- ", (char *)FIELD_NAME, "len:", FIELD_LEN);
    }
    break;
  case MKCREFLECT_TYPES_STRING:
    if (FIELD_LEN >= 0) {
      VALID_FIELD = true;
      PRINT("valid string field!- ", (char *)FIELD_NAME, "=>", (char *)FIELD, "len:", FIELD_LEN);
    }
    break;
  default:
    VALID_FIELD = false;
    PRINT("UNHANDLED FIELD!", (char *)FIELD_NAME, "type:", (int)FIELD_DATA_TYPE_ID);
    break;
  }
  if (VALID_FIELD) {
    return(FIELD);
  }else{
    log_error("invalid field!- %s", FIELD_NAME);
    return(NULL);
  }
} /* get_struct_field_name */

TEST t_mkcreflect(void){
  for (size_t si = 0; si < (sizeof(test_structs) / sizeof(test_structs[0])); si++) {
    for (size_t fi = 0; fi < S_FIELDS_COUNT(TestStruct); fi++) {
      MKCREFLECT_FieldInfo *FIELD           = &S_INFO(TestStruct)()->fields[fi];
      void                 *EXTRACTED_FIELD = get_struct_field_name(
        (void *)(&(test_structs[si])),
        (char *)FIELD->field_name
        );
    }
  }
  if (false) {
    dbg(S_NAME(Address), % s);
    dbg(S_NAME(TestStruct), % s);
    dbg(_S_INFO("TestStruct"), % s);
    dbg(S_SIZE(Address), %u);
    dbg(S_SIZE(TestStruct), %u);
    dbg(S_PACKED_SIZE(TestStruct), %u);
    dbg(S_PACKED_SIZE(Address), %u);
    dbg(S_FIELDS_COUNT(Address), %u);
    dbg(S_FIELDS_COUNT(TestStruct), %u);
  }
  PASS();
} /* t_mkcreflect */

SUITE(s_mkcreflect) {
  RUN_TEST(t_mkcreflect);
  PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_mkcreflect);
  GREATEST_MAIN_END();
}
