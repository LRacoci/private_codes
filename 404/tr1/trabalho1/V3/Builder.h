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
#include "iasDefs.c"

bool first_pass(FILE * src, FILE * out, HashT dict);
bool second_pass(FILE * src, FILE * out, HashT dict);

bool build(FILE * src, FILE * out);
