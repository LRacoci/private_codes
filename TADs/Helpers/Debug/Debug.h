#include <stdio.h>

typedef enum color{
    SimpleGrey = 30,
    SimpleRed = 31,
    SimpleGreen = 32,
    SimpleYellow = 33,
    SimpleBlue = 34,
    SimplePurple = 35,
    SimpleCian = 36,
    SimpleWhite = 37,

    BG_SimpleGrey = 40,
    BG_SimpleRed = 41,
    BG_SimpleGreen = 42,
    BG_SimpleYellow = 43,
    BG_SimpleBlue = 44,
    BG_SimplePurple = 45,
    BG_SimpleCian = 46,
    BG_simpleWhite = 47,

    LightGrey = 90,
    LightRed = 91,
    LightGreen = 92,
    LightYellow = 93,
    LightBlue = 94,
    LightPurple = 95,
    LightCian = 96,
    LightWhite = 97,

    BG_LightGrey = 100,
    BG_LightRed = 101,
    BG_LightGreen = 102,
    BG_LightYellow = 103,
    BG_LightBlue = 104,
    BG_LightPurple = 105,
    BG_LightCian = 106,
    BG_LightWhite = 107

}BashColor;

#define cfprintf(color, file, ...){ \
    fprintf(file, "\033[0;%2dm", color);\
    fprintf(file, __VA_ARGS__);\
    fprintf(file, "\033[0;00m");\
}
#define cprintf(color, ...){ \
    cfprintf(color, stdout, __VA_ARGS__);\
}
