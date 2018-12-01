printf "\n"

echo "Listing passwd files..."
ls -l /etc/passwd
ls -l /etc/bin/passwd
ls -l /usr/bin/passwd

printf "\n" 

echo "Listing some files with setuid bit..."
ls -l /bin/ping
ls -l /bin/su