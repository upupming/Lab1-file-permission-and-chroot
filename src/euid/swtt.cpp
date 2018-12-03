#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
using namespace std;

void ls_root() {
    cout << "正在调用 ls /root..." << endl;
    if(system("/bin/ls /root") != 0) {
        cout << "调用失败：" << endl;
    } else {
        cout << "调用成功！" << endl;
    }
}

int main (int argc, char *argv[]) {
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    // new uid to be changed
    uid_t new_uid = 1001;
    
    cout << "当前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    ls_root();

    // 保存 uid 到 suid
    if(setresuid(ruid, new_uid, euid) < 0) {
        cout << argv[0] << ": 无法切换 euid - " << strerror(errno) << endl;
        return 1;
    } 
    
    cout << "临时抛弃权限，成功将用户切换为 " << new_uid << endl;
    if(getresuid(&ruid, &euid, &suid) < 0) {
        cout << strerror(errno) << endl;
        return 1;
    }
    cout << "当前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    ls_root();

    ////////////////////////////
    // 切换回来
    if(setresuid(ruid, suid, euid) < 0) {
        cout << argv[0] << ": 无法恢复 euid - " << strerror(errno) << endl;
        return 1;
    }
    if(getresuid(&ruid, &euid, &suid) < 0) {
        cout << strerror(errno) << endl;
        return 1;
    } 
    cout << "用户成功切换回来" << endl;
    cout << "当前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    ls_root();
    ///////////////////////////

    ////////////////////////////
    // 永久抛弃
    if(setresuid(new_uid, new_uid, new_uid) < 0) {
        cout << argv[0] << ": 无法恢复 euid - " << strerror(errno) << endl;
        return 1;
    }
    if(getresuid(&ruid, &euid, &suid) < 0) {
        cout << strerror(errno) << endl;
        return 1;
    } 
    cout << "用户彻底抛弃权限" << endl;
    cout << "当前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    ls_root();
    ///////////////////////////

    ////////////////////////////
    // 无法再次返回 root 权限
    if(setresuid(ruid, 0, euid) < 0) {
        cout << argv[0] << ": 无法恢复 euid（root 权限已被永久抛弃） - " << strerror(errno) << endl;
        return 0;
    }
    if(getresuid(&ruid, &euid, &suid) < 0) {
        cout << strerror(errno) << endl;
        return 1;
    }
    cout << "当前 (ruid, euid, suid) = (" << ruid << ", " << euid << ", " << suid << ")" << endl;
    ls_root();
    ///////////////////////////

    cout << "正在调用 touch.sh..." << endl;
    if(execl("/bin/sh", "sh", "./touch.sh", (char*)0) < 0) {
        cout << "调用失败：" << strerror(errno) << endl;
    }

    return 0;
}