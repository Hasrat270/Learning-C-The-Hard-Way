#include <stdio.h>

int main(int argc, char* argv[]) {
    int num = 25;
    while (num <= 25 && num >= 1) {
        if (num == 25) {
            printf("State %d: Karachi\n", num);
        } else if (num == 24) {
            printf("State %d: Lahore\n", num);
        } else {
            printf("Num %d:\n", num);
        }
        num--;
    }
    return 0;
}