#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/exceptions.h"


char ex_str[][128] = {
    "Invalid shape",
    "Index Error"
};

void raise(int ex, char info[]) {
    printf(BRED "%s %s\n" RESET, ex_str[ex], info);
    exit(ex);
}
