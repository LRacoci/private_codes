/* DECLARA ALGUNS TIPOS AUXILIARES ÚTEIS E CONVENIENTES */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef STRING_DEFINED
#define STRING_DEFINED
typedef char* String;
#endif

#ifndef LONG_INT_DEFINED
#define LONG_INT_DEFINED
typedef long int LongInt;
#endif

#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef enum bool {false = 0, true = 1} bool;
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
#define absolute(x) (sign(x) * (x))
#endif
