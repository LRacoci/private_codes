#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"
#include "Word.h"
#include "HashTable.h"
#include "MemMap.h"

/* Macros úteis no código de Builder.c */
#define seems_directive(String) (String[0] == '.')
#define seems_label(String) (String[len-1] == ':')
#define seems_argument(String) (String[0] == '"' && String[len-1] == '"')

typedef union Type{
    TypeDir   d;
    TypeInstr i;
    TypeArg   a;
} GenericType;
bool build(FILE * src, FILE * out);
