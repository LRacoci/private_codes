#ifndef COMENT_CHAR
#define COMENT_CHAR '#'
#define EXIT_FAIL -1
#define EXIT_SUCESS 0

#define MAX_INSTR 17
#define MAX_DIR 5

static struct m{
    char id[10];
    unsigned short int opcode;
    __extension__ bool arg:1;
    __extension__ bool option:1;
} mne[MAX_INSTR] = {
    {     "LD" , true  , false },
    {     "LD-", true  , false },
    {     "LD|", true  , false },
    {    "LDmq", false , false },
    { "LDmq_mx", true  , false },
    {      "ST", true  , false },
    {     "JMP", true  , true  },
    {   "JUMP+", true  , true  },
    {     "ADD", true  , false },
    {    "ADD|", true  , false },
    {     "SUB", true  , false },
    {    "SUB|", true  , false },
    {     "MUL", true  , false },
    {     "DIF", true  , false },
    {     "LSH", false , false },
    {     "RSH", false , false },
    {  "STaddr", true  , true  }
};
typedef enum TypeArg{
	HEX,
	DEC,
	SYM,
	ROT
} TypeArg;

typedef enum TypeDir{
	set = 0,
	org = 1,
	align = 2,
	wfill = 3,
    word = 4,
    NONE = -1
} TypeDir;

typedef enum TypeExpr{
	ROTULO,
	DIRETIVA,
	INSTRUCAO,
	ARG_INSTR,
    ARG_DIR1,
    ARG_DIR2,
    NAOSEI
}TypeExpr;

static struct Dir{
    TypeDir dirType;
    char id[10];
    unsigned int n_args;
    struct Arg{
        TypeArg name[4];
        long int lowest;
        long int highest;
    }arg[2];
} dir[MAX_DIR] = {
    {   set ,  "set", 2, {
        {{SYM}                                         },
        {{HEX, DEC}         , 0           , 0x7FFFFFFF }
    }},
    {   org ,  "org", 1, {
        {{HEX, DEC}          , 0           , 0x3FF     }
    }},
    { align ,"align", 1, {
        {{DEC}              , 0           , 0x3FF      }
    }},
    { wfill ,"wfill", 2, {
        {{     DEC          }, 1          , 0x3FF      },
        {{HEX, DEC, ROT, SYM}, -0x80000000, 0x7FFFFFFF }
    }},
    {  word , "word", 1, {
        {{HEX, DEC, ROT, SYM}, 0          , 0x7FFFFFFF }
    }}
};

#define between(a, b, c) ((a) <= (b) && (b) <= (c))

#define alphanumeric(a) ( \
    between('a', (a), 'z') || \
    between('A', (a), 'Z') || \
    between('0', (a), '9') \
)
#define hexadecimal(a) ( \
    decimal(a) || \
    between('A', (a), 'F') || \
    between('a', (a), 'f') \
)
#define decimal(a) ( \
    between('0', (a), '9') \
)

#endif
