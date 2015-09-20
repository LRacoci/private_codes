#ifndef GENERIC_DEFS
#define GENERIC_DEFS

#define COMENT_CHAR '#'
#define EXIT_FAIL -1
#define EXIT_SUCESS 0

#define cfprintf(file, color, ...){ \
    fprintf(file, "\033[0;%02dm", color); \
    fprintf(file, __VA_ARGS__); \
    fprintf(stderr, "\033[0;00m"); \
}

#endif
