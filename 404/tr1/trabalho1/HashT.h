#include "Data.h"
#include "List.h"
#include "auxTypes.h"

#ifndef HASH_TABLE_DEFINED
#define HASH_TABLE_DEFINED


typedef struct sHashT{
    unsigned int size, s0;
    List *t;
} sHashT, *HashT;



size_t ___HashT_size(Info i);
void ___HashT_print(Info i);
void ___HashT_free(Info i);
Info ___HashT_copy(Info i);
Hash ___HashT_hash(Info i);

#endif
