#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    uid_t uid =getuid();
    
    cout << "当前用户的 uid 为 " << uid << endl;

    uid_t ruid, euid, suid;

    if(fork() == 0) {
        // 子进程
        getresuid(&ruid, &euid, &suid);
        cout << "子进程中 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    } else {
        // 父进程
        getresuid(&ruid, &euid, &suid);
        cout << "父进程中 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    }

    return 0;
}