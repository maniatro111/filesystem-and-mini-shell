build:
	gcc -o fsminishell main.c prelucrareinstr.c "functii fs.c" -g -Wall
run:
	./fsminishell
clean:
	rm fsminishell
