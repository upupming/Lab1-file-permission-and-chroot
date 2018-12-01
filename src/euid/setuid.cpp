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
    cout << "执行 execl 之前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;

    cout << "正在执行 execl 调用 show_current_id..." << endl;
        if(execl("./show_current_id", "./show_current_id", (char*)0) < 0) {
            cout << "调用失败：" << strerror(errno) << endl;
        }
    
    return 0;
}