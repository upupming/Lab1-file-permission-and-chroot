CC = g++

all: create_files ls fork swtt setuid

chroot:
	cd ./src/chroot && make chroot
cpp_chroot:
	cd ./src/chroot && make cpp_chroot
run_chroot:
	cd ./src/chroot && make run_chroot
run_chroot_with_cd:
	cd ./src/chroot && make run_chroot_with_cd
run_chroot_as_root_with_cd:
	cd ./src/chroot && make run_chroot_as_root_with_cd
run_chroot_as_root_with_cd_and_abandon_permission:
	cd ./src/chroot && make run_chroot_as_root_with_cd_and_abandon_permission

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