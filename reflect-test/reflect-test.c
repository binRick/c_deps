#define MKCREFLECT_IMPL
#include "../submodules/generic-print/print.h"
#include "../submodules/log.h/log.h"
#include "reflect-test.h"
#include "submodules/greatest/greatest.h"
#include <assert.h>
#include <inttypes.h>
#include <math.h>
////////////////////////////////////////////////////////


TestStruct test_structs[] = {
  {
    .i    = -100, .i0 = -666, .l = -12345, .ul = 999999, .s = 22222223232,
    .sh   = -12, .ui = 66123, .ll = -9912323, .ull = 22222222211,
    .name = "MY NAME", .n = "k", .n0 = "",
  },
};


size_t get_field_name_size(const char *FIELD_NAME){
  for (size_t i = 0; i < TestStructInfo->fields_count; i++) {
    MKCREFLECT_FieldInfo *F = &TestStructInfo->fields[i];
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

  for (size_t i = 0; (i < TestStructInfo->fields_count) && (FIELD == NULL); i++) {
    MKCREFLECT_FieldInfo *F = &TestStructInfo->fields[i];
    FIELD_DATA_TYPE_ID = (int)F->data_type;
    IS_SIGNED          = F->is_signed;
    if (strcmp(FIELD_NAME, F->field_name) == 0) {
      switch (F->data_type) {
      case MKCREFLECT_TYPES_INTEGER:
        FIELD = calloc(1, F->size);
        memcpy(FIELD, (STRUCT + F->offset), F->size);
        dbg(F->field_type, %s);
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
      dbg((long long)FIELD, % lld);
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
  if (false) {
    printf(
      AC_RESETALL AC_GREEN AC_BOLD "<%s>" AC_RESETALL " "
      AC_YELLOW "%lub (%lub packed)" AC_RESETALL " "
      AC_BLUE "[%lu fields]" AC_RESETALL  " "
      AC_RESETALL "\n",
      TestStructInfo->name, TestStructInfo->size,
      TestStructInfo->packed_size,
      TestStructInfo->fields_count
      );
  }

  for (size_t si = 0; si < (sizeof(test_structs) / sizeof(test_structs[0])); si++) {
    for (size_t fi = 0; fi < TestStructInfo->fields_count; fi++) {
      MKCREFLECT_FieldInfo *FIELD           = &TestStructInfo->fields[fi];
      void                 *EXTRACTED_FIELD = get_struct_field_name(
        (void *)(&(test_structs[si])),
        (char *)FIELD->field_name
        );
    }
  }
  for (size_t i = 0; i < TestStructInfo->fields_count; i++) {
    MKCREFLECT_FieldInfo *field = &TestStructInfo->fields[i];
    if (false) {
      printf(
        AC_RESETALL AC_GREEN AC_BOLD "\t#%lu/%lu" " "
        AC_RESETALL AC_GREEN AC_BOLD "<"
        AC_RESETALL AC_BRIGHT_BLUE AC_BOLD AC_UNDERLINE AC_REVERSED "%s"
        AC_RESETALL AC_GREEN AC_BOLD ">"
        AC_RESETALL "\n"
        AC_MAGENTA "\t\tType: #"
        AC_RESETALL AC_CYAN AC_BOLD "%d" AC_RESETALL " "
        AC_MAGENTA "'"
        AC_RESETALL AC_YELLOW_BLACK AC_ITALIC "%s" AC_RESETALL
        AC_MAGENTA "'" AC_RESETALL  "\n"
        AC_CYAN "\t\tPointer? %s" AC_RESETALL  "\n"
        AC_BLUE "\t\t[%d|%s]" AC_RESETALL  "\n"
        AC_BLUE "\t\t[offset:%lub|size:%lub]" AC_RESETALL  "\n",
        i + 1, TestStructInfo->fields_count, field->field_name,
        field->data_type, field->field_type,
        BOOL_TO_STR(FIELD_IS_POINTER(field->data_type)),
        field->array_size,
        (field->array_size != -1) ?
        AC_RESETALL AC_BOLD AC_UNDERLINE AC_YELLOW "Array" AC_RESETALL
                :
        AC_RESETALL AC_BOLD AC_UNDERLINE AC_RED "Not Array" AC_RESETALL,
        field->offset, field->size
        );
    }
    if (false) {
      printf("    Type: %s\t", field->field_type);
      printf("    Total size: %lu\t", field->size);
      printf("    data_type: %d\t", field->data_type);
      printf("    is_signed: %s\t", field->is_signed?"Yes":"No");
      printf("    Offset: %lu\t", field->offset);
      if (field->array_size != -1) {
        printf("    It is an array! Number of elements: %d, size of single element: %lu\t",
               field->array_size, field->size / field->array_size);
      }
      printf("%s", "\n");
    }
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
  //ASSERT_EQ(used, 0);
}
