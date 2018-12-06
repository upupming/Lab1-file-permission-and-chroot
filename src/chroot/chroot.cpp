#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    uid_t ruid, euid, suid;
    char path[100] = "./jail";
    if(argc >= 2 && string(argv[1]) == "cd-into-jail") {
        chdir("./jail");
        strcpy(path, ".");
    }
    if(chroot(path) < 0) {
        cerr << "chroot 失败: " << strerror(errno) << endl;
    }
    if(argc >= 3 && string(argv[2]) == "abandon-permission") {
        setresuid(ruid, 1000, 1000);
    }
    getresuid(&ruid, &euid, &suid);
    cout << "当前用户的 (ruid, euid, suid) = " << "(" << ruid << ", " << euid << ", " << suid << ")" << endl;
    execl("/bin/bash", "/bin/bash", NULL);
    return 0;
}