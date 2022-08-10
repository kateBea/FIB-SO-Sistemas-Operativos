all: sin_nombre lector escritor escritor_v2 \
	escritor_socket lector_socket exClientSocket exServerSocket socketMng.o

exServerSocket: exServerSocket.c socketMng.o
	gcc -o exServerSocket exServerSocket.c socketMng.o

exClientSocket: exClientSocket.c socketMng.o
	gcc -o exClientSocket exClientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c socketMng.c

sin_nombre: sin_nombre.c
	gcc -o sin_nombre sin_nombre.c -g

escritor: escritor.c
	gcc -o escritor escritor.c

escritor_v2: escritor_v2.c
	gcc -o escritor_v2 escritor_v2.c

lector_socket: lector_socket.c socketMng.h socketMng.o
	gcc -o lector_socket lector_socket.c socketMng.o -I.

escritor_socket: escritor_socket.c socketMng.h socketMng.o
	gcc -o escritor_socket escritor_socket.c socketMng.o -I. 

lector: lector.c
	gcc -o lector lector.c

clean: 
	rm -f exServerSocket exClientSocket \
		socketMng.o sin_nombre lector escritor escritor_v2 lector_socket escritor_socket
