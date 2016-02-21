#include "auxTypes.h"

#ifndef DATA_DEFINED
#define DATA_DEFINED


typedef void * Info, **pInfo;
typedef void (*func_free)(pInfo );
typedef Info (*func_copy)(Info );
typedef Comp (*func_comp)(Info , Info );
typedef void (*func_print)(Info );
typedef Hash (*func_hash)(Info );

typedef enum DataType{
    ___List,
    ___int,
    ___LongInt,
    ___OutLine,
    ___String,
    ___HashVal
} DataType;

#define numcmp(a, b) (((a) == (b)) ? 0 : ((a) < (b))? -1 : 1)

/* Example with type = List and v = l:
new_data(
    ___List_copy(&(l)),
    ___List_size(&(l)),
    ___List_free,
    ___List_copy,
    ___List_print,
    ___List_hash,
    ___List_comp,
    ___List
)
*/

#define comp_info(arg1 , arg2 , size) memcmp( \
    (const Info) (arg1), \
    (const Info) (arg2), \
    (size) \
)



#endif
