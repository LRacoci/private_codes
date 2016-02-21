#include "Helpers/Debug/Debug.h"

int main(){
    unsigned i;
    for(i = 0; i < (1<<8); i++){
        cfprintf(i, stdout, "Color code = %2d\n", i);
    }

    return 0;
}
