chroot: chroot.sh
	bash chroot.sh
cpp_chroot: chroot.cpp
	g++ -o chroot chroot.cpp
run_chroot:
	./chroot
run_chroot_as_root:
	sudo ./chroot
run_chroot_with_cd:
	./chroot cd-into-jail
run_chroot_as_root_with_cd:
	sudo ./chroot cd-into-jail
run_chroot_as_root_with_cd_and_abandon_permission:
	sudo ./chroot cd-into-jail abandon-permission

clean:
	rm ./jail -rf