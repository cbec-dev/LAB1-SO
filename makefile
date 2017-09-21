
DIR_OUTPUT = ./out
DIR_SRC = ./
NOMBRE_EJECUTABLE = lab1
NOMBRE_EJECUTABLE2 = comparador

all: lab1

# Compilación de lab1 (coordinador) y el comparador.
lab1:
	@echo 'Compilando lab1'
	mkdir -p $(DIR_OUTPUT)
	gcc $(DIR_SRC)/coordinador.c -o $(DIR_OUTPUT)/$(NOMBRE_EJECUTABLE)
	gcc $(DIR_SRC)/comparador.c -o $(DIR_OUTPUT)/$(NOMBRE_EJECUTABLE2)
	@echo ' '
	@echo $@ compilado en el directorio $(DIR_OUTPUT)
	@echo "Ingrese al directorio '"$(DIR_OUTPUT)"' escribiendo: cd "$(DIR_OUTPUT)
	@echo "Ejecute el programa haciendo: ./"$(NOMBRE_EJECUTABLE)""
	@echo ' '

clean:
	rm -rf $(DIR_OUTPUT)/*
	-@echo ' ' 
