all:listaParametros numeros mis_funciones.o suma punteros words

listaParametros: listaParametros.c
	gcc -o listaParametros listaParametros.c

numeros: numeros.c
	gcc -o numeros numeros.c

mis_funciones.o: mis_funciones.c mis_funciones.h
	gcc -c mis_funciones.c

suma: suma.c mis_funciones.h
	gcc -o suma suma.c mis_funciones.o -I ./

punteros: punteros.c
	gcc -o punteros punteros.c

words: words.c
	gcc -o words words.c mis_funciones.o -I ./
	rm mis_funciones.o

clean:
	rm listaParametros numeros *.o words punteros suma
