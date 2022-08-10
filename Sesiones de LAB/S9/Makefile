OPTIONS = -Wall -Wextra -Wpedantic

#build command 
all: crea_fichero insertax append insertax2 invirtiendo_fichero

#rules to make targets
crea_fichero: crea_fichero.c
	gcc -o crea_fichero crea_fichero.c $(OPTIONS) -g

insertax: insertax.c
	gcc -o insertax insertax.c $(OPTIONS) -g

append: append.c
	gcc -o append append.c $(OPTIONS) -g

insertax2: insertax2.c
	gcc -o insertax2 insertax2.c $(OPTIONS) -g -D _DEBUG

invirtiendo_fichero: invirtiendo_fichero.c
	gcc -o invirtiendo_fichero invirtiendo_fichero.c $(OPTIONS) -g

#clean command
clean:
	rm crea_fichero insertax append insertax2 invirtiendo_fichero