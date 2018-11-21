# 计算机系统安全实验一

|学号|姓名|日期|
|:-:|:-:|:-:|
|1160300625|李一鸣||

- [计算机系统安全实验一](#%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E5%AE%89%E5%85%A8%E5%AE%9E%E9%AA%8C%E4%B8%80)
    - [实验要求](#%E5%AE%9E%E9%AA%8C%E8%A6%81%E6%B1%82)
        - [euid 管理](#euid-%E7%AE%A1%E7%90%86)
        - [搭建沙盒环境](#%E6%90%AD%E5%BB%BA%E6%B2%99%E7%9B%92%E7%8E%AF%E5%A2%83)
    - [实验过程](#%E5%AE%9E%E9%AA%8C%E8%BF%87%E7%A8%8B)
        - [Linux 系统文件和目录权限设置与辨识 setuid 程序 uid 差别](#linux-%E7%B3%BB%E7%BB%9F%E6%96%87%E4%BB%B6%E5%92%8C%E7%9B%AE%E5%BD%95%E6%9D%83%E9%99%90%E8%AE%BE%E7%BD%AE%E4%B8%8E%E8%BE%A8%E8%AF%86-setuid-%E7%A8%8B%E5%BA%8F-uid-%E5%B7%AE%E5%88%AB)
            - [设计并实现不同用户对不同类文件的 r、w、x 权限](#%E8%AE%BE%E8%AE%A1%E5%B9%B6%E5%AE%9E%E7%8E%B0%E4%B8%8D%E5%90%8C%E7%94%A8%E6%88%B7%E5%AF%B9%E4%B8%8D%E5%90%8C%E7%B1%BB%E6%96%87%E4%BB%B6%E7%9A%84-rwx-%E6%9D%83%E9%99%90)
                - [查看系统文件的权限设置](#%E6%9F%A5%E7%9C%8B%E7%B3%BB%E7%BB%9F%E6%96%87%E4%BB%B6%E7%9A%84%E6%9D%83%E9%99%90%E8%AE%BE%E7%BD%AE)
                - [设置文件或目录权限](#%E8%AE%BE%E7%BD%AE%E6%96%87%E4%BB%B6%E6%88%96%E7%9B%AE%E5%BD%95%E6%9D%83%E9%99%90)
            - [`setuid`](#setuid)
                - [HTTP 网络服务](#http-%E7%BD%91%E7%BB%9C%E6%9C%8D%E5%8A%A1)
                - [`fork`](#fork)
                - [`execl`](#execl)
                - [放弃 `root` 权限](#%E6%94%BE%E5%BC%83-root-%E6%9D%83%E9%99%90)
                - [`execl` 函数族](#execl-%E5%87%BD%E6%95%B0%E6%97%8F)
                    - [`execve`](#execve)
        - [利用 `chroot` 搭建沙盒环境](#%E5%88%A9%E7%94%A8-chroot-%E6%90%AD%E5%BB%BA%E6%B2%99%E7%9B%92%E7%8E%AF%E5%A2%83)
            - [Ubuntu 下 `chroot` SSH 客户端](#ubuntu-%E4%B8%8B-chroot-ssh-%E5%AE%A2%E6%88%B7%E7%AB%AF)
                - [准备基本 `chroot` 环境](#%E5%87%86%E5%A4%87%E5%9F%BA%E6%9C%AC-chroot-%E7%8E%AF%E5%A2%83)
                - [配置 `chroot` 环境](#%E9%85%8D%E7%BD%AE-chroot-%E7%8E%AF%E5%A2%83)

## 实验要求

### euid 管理

- [ ] 设想一种场景需要进行普通用户和 root 用户切换，设计程序实现 euid 的安全管理。

- [ ] 配合第 3 章完成进程中 euid 的切换，实现 root 权限临时性和永久性管理，加强程序的安全性。

说明：1学时，不分组实现。

### 搭建沙盒环境

- [ ] 搭建安全的沙盒环境，在沙盒环境中提供必须的常见工具，并提供程序验证沙盒环境的安全性。
- [ ] 配合第 3 章，实现系统中的虚拟化限制方法，实现安全的系统加固，测试虚拟化空间的加固程度。

说明：3 学时，2 人一组，分组实现。

## 实验过程

### Linux 系统文件和目录权限设置与辨识 setuid 程序 uid 差别

#### 设计并实现不同用户对不同类文件的 r、w、x 权限

##### 查看系统文件的权限设置

1. 查看 `/etc/passwd` 文件和 `/usr/bin/passwd` 文件的权限设置，并分析其权限为什么这么设置。

    ![20181120222018.png](https://i.loli.net/2018/11/20/5bf4183422a96.png)

    ```bash
    -rw-r--r-- 1 root root 1656 Nov 20 12:05 /etc/passwd
    -rwsr-xr-x 1 root root 54256 May 17  2017 /usr/bin/passwd
    ```

    `/etc/passwd` 存放着用户信息（不包含密码，密码存放在 `/etc/shadow` 中），因此所有者有读写权限，同组和其他人有读权限。

    `/usr/bin/passwd` 用来修改保存在 `/etc/passwd` 中的用户记录和 `/etc/shadow` 中的信息。可以看到其被设置了 `SUID` 位，这样普通用户可以以 `root` 身份运行程序，从而获得对 `/etc/passwd` 和 `/usr/bin/passwd` 的写权限。

2. 找到 2 个设置了 setuid 位的可执行程序，该程序的功能，该程序如果不设置 setuid 位是否能够达到相应的功能。

    ![20181121003819.png](https://i.loli.net/2018/11/21/5bf43880711e0.png)

    - `/bin/ping`

        `ping` 用来发送 ICMP ECHO_REQUEST 给网络主机。根据 [StackExchange](https://unix.stackexchange.com/a/320289/319953)，由于历史原因，`ping` 在安装时被设置了 `setuid` 位，让普通用户可以以 `root` 运行，但是现在有了能力位之后已经被弃用了。不过由于在 Ubuntu 中安装器对能力位的设置有问题，因此还是使用 `setuid` 位。

    - `/bin/su`

        根据 [unix.com](https://www.unix.com/aix/249476-why-bin-su-permission-suid.html) 的解释， `/bin/su` 必须有 `setuid` 位，这样普通用户才可以通过运行 `su` 切换用户。

##### 设置文件或目录权限

1. 用户 A 具有文本文件”流星雨.txt”，该用户允许别人下载；

    对所有用户可读，应该赋予权限权限 `444`。

    ![20181120225737.png](https://i.loli.net/2018/11/20/5bf420e2e65ac.png)

2. 用户 A 编译了一个可执行文件”cal.exe”，该用户想在系统启动时运行

    设置为可执行 `111` 即可。

3. 用户 A 有起草了文件”demo.txt”，想让同组的用户帮其修改文件

    设置为所有人同组可读、可写，权限为 `766`。

4. 一个 root 用户拥有的网络服务程序”netmonitor.exe”，需要设置 setuid 位才能完成其功能。

    可以参考 [How to use special permissions: the setuid, setgid and sticky bits](https://linuxconfig.org/how-to-use-special-permissions-the-setuid-setgid-and-sticky-bits) 设置 `setuid` 位。

    ```bash
    chmod u+s netmonitor.exe
    ```

#### `setuid`

一些可执行程序运行时需要系统管理员权限，在 UNIX 中可以利用 `setuid` 位实现其功能，但 `setuid` 了的程序运行过程中拥有了 root 权限，因此在完成管理操作后需要切换到普通用户的身份执行后续操作。

##### HTTP 网络服务

设想一种场景，比如提供 http 网络服务，需要设置 `setuid` 位，并为该场景编制相应的代码。

为相应的软件设置好 `setuid` 位即可，如果在一个程序中需要使用它，可以使用 `exec` 执行。

##### `fork`

用户 `fork` 进程后，父子进程的 `euid`、`ruid` 和 `suid` 均不会发生改变。

##### `execl`

使用 `execl` 执行 `setuid` 的程序之后，`euid` 和 `suid` 都会变为文件的拥有者，`ruid` 保持不变。

##### 放弃 `root` 权限

下文节选自 [最小化特权 - IBM](https://www.ibm.com/developerworks/cn/linux/l-sppriv/index.html)。

<blockquote>
只是当需要的时候才给予特权——片刻也不要多给。

只要可能，使用无论什么您立即需要的特权，然后永久地放弃它们。一旦它们被永久放弃，后来的攻击者就不能以其他方式利用那些特权。例如，需要个别的 root 特权的程序可能以 root 身份启动（比如说，通过成为 setuid root）然后切换到以较少特权用户身份运行。这是很多 Internet 服务器（包括 Apache Web 服务器）所采用的方法。类 UNIX 系统不允许任何程序打开 0 到 1024 TCP/IP 端口；您必须拥有 root 特权。但是大部分服务器只是在启动的时候需要打开端口，以后就再也不需要特权了。一个方法是以 root 身份运行，尽可能快地打开需要特权的端口，然后永久去除 root 特权（包括进程所属的任何有特权的组）。也要尝试去除所有其他继承而来的特权；例如，尽快关 闭需要特定的特权才能打开的文件。

如果您不能永久地放弃特权，那么您至少可以尽可能经常临时去除特权。这不如永久地去除特权好，因为如果攻击者可以控制您的程序，攻击者就可以重新启用特权并利用它。尽管如此，还是值得去做。很多攻击只有在它们欺骗有特权的程序做一些计划外的事情而且程序的特权被启用时才会成功（例如，通过创建不合常理的符号链接和硬链接）。 如果程序通常不启用它的特权，那么攻击者想利用这个程序就会更困难。
</blockquote>

我们为了防范攻击，尽可能在使用完高权限之后永久放弃 `root` 权限，如果无法永久放弃，也要临时放弃 `root` 权限，以使权限最小化。

##### `execl` 函数族

`execl` 函数族中有多个函数，有环境变量和无环境变量的函数使用的差异如下：

```c
#include <unistd.h>

extern char **environ;
int execl(const char *path, const char *arg0, ... /*, (char *)0 */);
int execle(const char *path, const char *arg0, ... /*,
       (char *)0, char *const envp[]*/);
int execlp(const char *file, const char *arg0, ... /*, (char *)0 */);
int execv(const char *path, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
int execvp(const char *file, char *const argv[]);
int fexecve(int fd, char *const argv[], char *const envp[]);
```

可以看到 `execve` 和 `fexecve` 是有环境变量的函数。具体的例子参见 [exec](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html)：

###### `execve`

```c
#include <unistd.h>


int ret;
char *cmd[] = { "ls", "-l", (char *)0 };
char *env[] = { "HOME=/usr/home", "LOGNAME=home", (char *)0 };
...
ret = execve ("/bin/ls", cmd, env);
```

### 利用 `chroot` 搭建沙盒环境

#### Ubuntu 下 `chroot` SSH 客户端

##### 准备基本 `chroot` 环境

执行 `ldd` 命令查看所需要的库文件。

```bash
root@mingcloud:~# ldd /usr/bin/ssh
    linux-vdso.so.1 =>  (0x00007ffc7b52b000)
    libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007f944ca4e000)
    libcrypto.so.1.0.0 => /lib/x86_64-linux-gnu/libcrypto.so.1.0.0 (0x00007f944c60a000)
    libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f944c406000)
    libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007f944c1ec000)
    libresolv.so.2 => /lib/x86_64-linux-gnu/libresolv.so.2 (0x00007f944bfd1000)
    libgssapi_krb5.so.2 => /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2 (0x00007f944bd87000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f944b9bd000)
    libpcre.so.3 => /lib/x86_64-linux-gnu/libpcre.so.3 (0x00007f944b74d000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f944cf20000)
    libkrb5.so.3 => /usr/lib/x86_64-linux-gnu/libkrb5.so.3 (0x00007f944b47b000)
    libk5crypto.so.3 => /usr/lib/x86_64-linux-gnu/libk5crypto.so.3 (0x00007f944b24c000)
    libcom_err.so.2 => /lib/x86_64-linux-gnu/libcom_err.so.2 (0x00007f944b048000)
    libkrb5support.so.0 => /usr/lib/x86_64-linux-gnu/libkrb5support.so.0 (0x00007f944ae3d000)
    libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f944ac20000)
    libkeyutils.so.1 => /lib/x86_64-linux-gnu/libkeyutils.so.1 (0x00007f944aa1c000)
```

创建 `chroot` 目录并安装 `ssh`、复制相应的库文件。

```bash
# 创建沙盒目录 /var/chroot/，安装 ssh
root@mingcloud:~# mkdir -p /var/chroot/usr/bin
root@mingcloud:~# install -C /usr/bin/ssh /var/chroot/usr/bin/

# 创建 /usr/lib/x86_64-linux-gnu
root@mingcloud:~# mkdir -p /var/chroot/usr/lib/x86_64-linux-gnu
root@mingcloud:~# install -C /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2 /usr/lib/x86_64-linux-gnu/libkrb5.so.3 /usr/lib/x86_64-linux-gnu/libk5crypto.so.3 /usr/lib/x86_64-linux-gnu/libkrb5support.so.0 /var/chroot/usr/lib/x86_64-linux-gnu

# 创建 /lib/x86_64-linux-gnu
root@mingcloud:~# mkdir -p /var/chroot/lib/x86_64-linux-gnu
root@mingcloud:~# install -C /lib/x86_64-linux-gnu/libselinux.so.1 /lib/x86_64-linux-gnu/libcrypto.so.1.0.0 /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libresolv.so.2 /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libpcre.so.3 /lib/x86_64-linux-gnu/libcom_err.so.2 /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libkeyutils.so.1 /var/chroot/lib/x86_64-linux-gnu/

# 创建 /lib64
root@mingcloud:~# mkdir /var/chroot/lib64
root@mingcloud:~# install -C /lib64/ld-linux-x86-64.so.2 /var/chroot/lib64/
```

##### 配置 `chroot` 环境

执行 `chroot` 进入沙盒时出现问题：

```bash
root@mingcloud:~# chroot /var/chroot /usr/bin/ssh
Couldn't open /dev/null: No such file or directory
```

维基百科写到：

> 在类Unix系统中，`/dev/null`，或称空设备，是一个特殊的设备文件，它丢弃一切写入其中的数据（但报告写入操作成功），读取它则会立即得到一个EOF。

于是把 `/dev/chroot` 也复制到沙盒环境中：

```bash
root@mingcloud:~# mkdir /var/chroot/dev
root@mingcloud:~# cp /dev/null /var/chroot/dev/null
```

再次运行：

```bash
root@mingcloud:~# chroot /var/chroot /usr/bin/ssh
No user exists for uid 0
```

出现了 `No user exists for uid 0` 错误，查阅[资料](https://unix.stackexchange.com/questions/63182/whoami-cannot-find-name-for-user-id-0)得知还要复制相应的 `/etc/passwd` 和 `/etc/group` 文件：

```bash
# 创建 /etc
mkdir /var/chroot/etc
# 复制 passwd、group 文件
cp /etc/{passwd,group} /var/chroot/etc
```

并且安装一些依赖库：

```bash
root@mingcloud:~# install -C /lib/x86_64-linux-gnu/libnss_* /var/chroot/lib/x86_64-linux-gnu/
root@mingcloud:~# chroot /var/chroot /usr/bin/ssh
```

最后终于运行成功，结果如下：

```bash
usage: ssh [-1246AaCfGgKkMNnqsTtVvXxYy] [-b bind_address] [-c cipher_spec]
           [-D [bind_address:]port] [-E log_file] [-e escape_char]
           [-F configfile] [-I pkcs11] [-i identity_file] [-L address]
           [-l login_name] [-m mac_spec] [-O ctl_cmd] [-o option] [-p port]
           [-Q query_option] [-R address] [-S ctl_path] [-W host:port]
           [-w local_tun[:remote_tun]] [user@]hostname [command]
```

整个过程已经记录在了 [`chroot.sh`](./src/chroot.sh) 文件中，可以直接运行。一个极小的沙盒环境已经保存在 `./src/chroot` 目录之下。

当我们以 `sshtest` 用户运行在沙盒环境中时，是完全安全的。