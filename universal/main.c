#include <stdio.h>

#include "universal.h"


int main(int argc, char *argv[]) {

    universal *u = universal_from_string(argv[1]);
    universal *v = universal_from_string(argv[2]);

    printf("%s, %s", universal_to_string(universal_add(u, v)), universal_to_string(universal_multiply(u, v)));

    return 0;
}