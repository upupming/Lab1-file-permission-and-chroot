#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    uid_t uid =getuid();

    uid_t ruid, euid, suid;

    getresuid(&ruid, &euid, &suid);
    cout << "当前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    return 0;
}