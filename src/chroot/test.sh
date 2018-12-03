# run test
echo "running ps"
ps -o pid,euid,ruid,suid,egid,rgid,sgid,cmd
echo "listing all open file descriptors"
ls -la /proc/$$/fd
echo "opening port 49"
nc -l 49