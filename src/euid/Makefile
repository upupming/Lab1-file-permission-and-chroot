CC = g++

all:
	swtt fork setuid

show_current_id: show_current_id.cpp
	${CC} show_current_id.cpp -o show_current_id
	sudo chown doraemon:doraemon show_current_id
	sudo chmod u+s show_current_id

setuid: setuid.cpp show_current_id
	${CC} setuid.cpp -o setuid

fork:
	${CC} fork.cpp -o fork

swtt: swtt.cpp
	${CC} swtt.cpp -o swtt
	chmod +x touch.sh

run_swtt: 
	./swtt
run_fork:
	./fork
run_setuid:
	./setuid

clean:
	rm swtt tempfile fork setuid show_current_id -f