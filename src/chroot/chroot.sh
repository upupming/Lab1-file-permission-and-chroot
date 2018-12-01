# 创建沙盒目录，复制 ssh
mkdir -p ./jail/usr/bin
install -C /usr/bin/ssh ./jail/usr/bin/

# 创建 /usr/lib
mkdir -p ./jail/usr/lib/x86_64-linux-gnu
# 安装依赖库
install -C /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2 /usr/lib/x86_64-linux-gnu/libkrb5.so.3 /usr/lib/x86_64-linux-gnu/libk5crypto.so.3 /usr/lib/x86_64-linux-gnu/libkrb5support.so.0 ./jail/usr/lib/x86_64-linux-gnu

# 创建 /lib
mkdir -p ./jail/lib/x86_64-linux-gnu
# 安装依赖库
install -C /lib/x86_64-linux-gnu/libselinux.so.1 /usr/lib/x86_64-linux-gnu/libcrypto.so.1.0.0 /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libresolv.so.2 /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libpcre.so.3 /lib/x86_64-linux-gnu/libcom_err.so.2 /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libkeyutils.so.1 ./jail/lib/x86_64-linux-gnu/

# 创建 /lib64
mkdir ./jail/lib64
# 安装依赖库
install -C /lib64/ld-linux-x86-64.so.2 ./jail/lib64/

# 创建 /dev
mkdir ./jail/dev
# 复制 null 文件
cp /dev/null ./jail/dev/null

# 创建 /etc
mkdir ./jail/etc
# 复制 passwd、group 文件
cp /etc/{passwd,group} ./jail/etc

# 安装解析 uid 的库
install -C /lib/x86_64-linux-gnu/libnss_* ./jail/lib/x86_64-linux-gnu/

# 在沙盒中运行 ssh
sudo chroot ./jail /usr/bin/ssh -V