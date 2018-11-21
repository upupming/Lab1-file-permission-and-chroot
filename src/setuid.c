#include <sys/types.h>
#include <unistd.h>

int main() {
    if(fork() > 0) {
        printf("In child process");
    }

    return 0;
}