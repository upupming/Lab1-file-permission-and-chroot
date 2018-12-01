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

    // 保存 uid 到 suid
    if(setresuid(uid, 1001, uid) < 0) {
        cout << argv[0] << ": 无法切换 euid - " << strerror(errno) << endl;
        return 1;
    } else {
        uid_t ruid, euid, suid;
        cout << "成功将用户切换为 " << 1001 << endl;
        if(getresuid(&ruid, &euid, &suid) < 0) {
            cout << strerror(errno) << endl;
        }
        cout << "当前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;

        cout << "正在调用 touch.sh..." << endl;
        if(execl("/bin/sh", "sh", "./touch.sh", (char*)0) < 0) {
            cout << "调用失败：" << strerror(errno) << endl;
        }
    } 

    return 0;
}