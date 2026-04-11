#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;

    if (argc == 1) {
        printf("You only have one argument. You suck.\n");
    } else if (argc > 1 && argc <= 10) {
        printf("You have too many arguments. You suck");

        for (i = 0; i < argc; i++) {
            printf("%d: %s\n", i, argv[i]);
        }
    } else {
        printf("You have too many arguments. You suck.\n");
    }
}