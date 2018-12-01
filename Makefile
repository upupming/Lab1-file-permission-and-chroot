CC = g++

all: create_files ls fork swtt setuid

chroot:
	cd ./src/chroot && make chroot

create_files:
	cd ./src/permissions && make create_files

ls:
	cd ./src/permissions && make ls

setuid:
	cd ./src/euid && make setuid

fork:
	cd ./src/euid && make fork

swtt:
	cd ./src/euid && make swtt

chroot:
	cd ./src/chroot && make chroot

run_setuid:
	cd ./src/euid && make run_setuid

run_fork:
	cd ./src/euid && make run_fork

run_swtt:
	cd ./src/euid && make run_swtt

clean:
	cd ./src/euid && make clean
	cd ./src/permissions && make clean
	cd ./src/chroot && make clean