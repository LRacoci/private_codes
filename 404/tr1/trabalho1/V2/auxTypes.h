#ifndef STRING_DEFINED
#define STRING_DEFINED
typedef char* String;
#endif

#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef char bool;
#define true 1
#define false 0
#endif

#ifndef HASH_TYPE
#define HASH_TYPE
typedef unsigned long int Hash;
#endif

#ifndef COMP_TYPE
#define COMP_TYPE
typedef short int Comp;
#endif

#ifndef min
#define min(x, y) ((x < y) ? (x) : (y))
#endif

#ifndef sign
#define sign(x) ((x >= 0) ? (1) : (-1))
#endif

#ifndef abs
#define abs(x) ( sign(x) * x)
#endif
