CC= gcc -Wall
HEADER_FILES_DIR = .
LIBRARIES = -lm
INCLUDES = -I $(HEADER_FILES_DIR)
MAIN= interpreteMatematico
SRCS = main.c lex.yy.c bison.tab.c ArbolBinario.c TablaDeSimbolos.c Errores.c 
DEPS = $(HEADER_FILES_DIR)/flex.yy.h bison.tab.h ArbolBinario.h Definiciones.h TablaDeSimbolos.h Errores.h
OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(LIBRARIES)
	rm -f *.o *~
%.o: %.c $(DEPS)
	$(CC) -c $< $(INCLUDES)
cleanall: clean
	rm -f $(MAIN)
clean:
	rm -f *.o *~
