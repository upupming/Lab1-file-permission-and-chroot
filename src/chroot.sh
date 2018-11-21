# 创建沙盒目录，复制 ssh
mkdir -p /var/chroot/usr/bin
install -C /usr/bin/ssh /var/chroot/usr/bin/

# 创建 /usr/lib
mkdir -p /var/chroot/usr/lib/x86_64-linux-gnu
# 安装依赖库
install -C /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2 /usr/lib/x86_64-linux-gnu/libkrb5.so.3 /usr/lib/x86_64-linux-gnu/libk5crypto.so.3 /usr/lib/x86_64-linux-gnu/libkrb5support.so.0 /var/chroot/usr/lib/x86_64-linux-gnu

# 创建 /lib
mkdir -p /var/chroot/lib/x86_64-linux-gnu
# 安装依赖库
install -C /lib/x86_64-linux-gnu/libselinux.so.1 /lib/x86_64-linux-gnu/libcrypto.so.1.0.0 /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libresolv.so.2 /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libpcre.so.3 /lib/x86_64-linux-gnu/libcom_err.so.2 /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libkeyutils.so.1 /var/chroot/lib/x86_64-linux-gnu/

# 创建 /lib64
mkdir /var/chroot/lib64
# 安装依赖库
install -C /lib64/ld-linux-x86-64.so.2 /var/chroot/lib64/

# 创建 /dev
mkdir /var/chroot/dev
# 复制 null 文件
cp /dev/null /var/chroot/dev/null

# 创建 /etc
mkdir /var/chroot/etc
# 复制 passwd、group 文件
cp /etc/{passwd,group} /var/chroot/etc

# 安装解析 uid 的库
install -C /lib/x86_64-linux-gnu/libnss_* /var/chroot/lib/x86_64-linux-gnu/

# 在沙盒中运行 ssh
chroot /var/chroot /usr/bin/ssh