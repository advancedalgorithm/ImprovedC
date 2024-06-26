#ifndef TYPES_H
#define TYPES_H

#include "../iclibs/ic/string/str.h"

// Special Value Representation
typedef enum DATA_T {
    NULL_VAR                                = 0x00000001, // NO VALUE

    /* C Types */
    VOID                                    = 0x00000002,
    VOID_PTR                                = 0x00000003,
    CHAR                                    = 0x00000004,
    CHAR_PTR                                = 0x00000005,
    CHAR_DPTR                               = 0x00000006,
    INT                                     = 0x00000007,
    INT_PTR                                 = 0x00000008,
    FLOAT                                   = 0x00000009,
    DOUBLE                                  = 0x00000010,

    /* IC TYPES */
    STRING                                  = 0x00000011,
    INTEGER                                 = 0x00000012,
    ARRAY                                   = 0x00000013,
    MAP                                     = 0x00000014,
    F32                                     = 0x00000015,
    F64                                     = 0x00000016,
    DF64                                    = 0x00000017
} DATA_T;

extern DATA_T TYPES[];
extern char *TYPES_STR[];

typedef enum EXPRESSION_T {
    NO_EXPR_ERR                             = 0x00000100,
    EQUAL                                   = 0x00000101,
    APPEND                                  = 0x00000102,
} EXPRESSION_T;

typedef enum INCLUDE_ERR_T {
    NO_INCLUDE_ERR                          = 0x10000020,
    INVALID_PATH_ERR                        = 0x10000021,
    INVALID_PATH_FILES_ERR                  = 0x10000022
} INCLUDE_ERR_T;

typedef enum FILE_ERR_T {
    NO_FILE_ERR                             = 0x20000030,
    INVALID_FILE_EXTENSION_ERR              = 0x20000031,
    INVALID_SRC_CODE_ERR                    = 0x20000032,
    MISSING_ENTRY_FNC_ERR                   = 0x20000033
} FILE_ERR_T;

typedef enum STRUCT_ERR_T {
    NO_STRUCT_ERR                           = 0x4000000,
    MISSING_STRUCT_NAME_ERR                 = 0x4000001,
    INVALID_STRUCT_NAME_ERR                 = 0x4000002,

    MISSING_STRUCT_OPENING_BRACKET_ERR      = 0x4000003,
    MISSING_STRUCT_CLOSING_BREAKET_ERR      = 0x4000004,

    INVALID_DATA_T_ERR                      = 0x4000005,
    INVALID_FIELD_NAME_ERR                  = 0x4000006
} STRUCT_ERR_T;

DATA_T str2type(char *t);
char *type_to_cgen(DATA_T t);

#endif