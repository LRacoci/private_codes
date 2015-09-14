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

void first_pass(FILE * src, FILE * out, HashT dict);
void second_pass(FILE * src, FILE * out, HashT dict);

void build(FILE * src, FILE * out);
