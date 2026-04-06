#include "common.h"
#include "utils.h"

void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****Yet Another Shell****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
    printf("\n");
    sleep(1);
    clear();
}

int letter_Occurance(char** command ,char* searchToken)
{
    int index = -1;
    for (int j = 0; command[j] != NULL; j++) {
        if (strcmp(command[j], searchToken) == 0) {
            index = j;
            break;
        }
    }
    return index;
}
