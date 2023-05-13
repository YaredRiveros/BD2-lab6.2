# BD2-lab6.2

## Implementación del índice


## Resultados obtenidos
El archivo main.cpp ubicada en la carpeta "BD2-lab6.2" encontrará el programa que se encarga de leer el índice invertido "index.txt" generado en el paso anterior.

El algoritmo que procesa la consulta se encuentra en solution.h ubicada en la misma carpeta. Está basado en la tarea "Evaluate Expressions" del curso AED, en el que se nos pedía verificar si una operación aritmética había sido introducida adecuadamente y devolver el resultado.

Para cada consulta, se realizan las siguientes operaciones:

1. Se toman las cadenas importantes (operadores y operandos) y se llevan a un vector
2. Se buscan las raíces más próximas a los operandos introducidos.
3. Se realizan validaciones para la forma infija.
4. Se transforma de forma infija a postfija.
5. Se revisa que se cierren todos los corchetes y paréntesis.
6. Se resuelven todos los AND, OR y ANDNOT a partir de la forma postfija utilizando las funciones llamar_AND, llamar_OR y llamar_ANDNOT. Éstos últimos utilizan el algoritmo de mezcla para tener una complejidad de O(m), siendo m la cantidad de libros en las que aparece la keyWord.

### Consulta 1

![consulta1_cod](https://github.com/YaredRiveros/BD2-lab6.2/assets/83974222/c38d1cbe-8853-47f0-a433-bfb188031f3b)
![consulta1_terminal](https://github.com/YaredRiveros/BD2-lab6.2/assets/83974222/1a06d261-fb4d-4906-b502-91f9fff9ba12)

### Consulta 2

![image](https://github.com/YaredRiveros/BD2-lab6.2/assets/83974222/0015a01d-4e14-4256-b242-aa9c9ec1a77b)
![image](https://github.com/YaredRiveros/BD2-lab6.2/assets/83974222/65b94608-0099-4d8f-bd56-3a94f635eb00)

### Consulta 3

En este caso no hay resultados puesto que "trampa" (cuya raíz es tramp) solo aparece en el libro 1, mientras que tambor OR refugio aparecen en el libro 2 y 3, por ende el AND arroja un resultado nulo.

![image](https://github.com/YaredRiveros/BD2-lab6.2/assets/83974222/47004259-a4e0-4cfb-b6fe-2dc0f6d484a6)
![image](https://github.com/YaredRiveros/BD2-lab6.2/assets/83974222/5f8d6e95-94fa-4171-a3bd-01ee0848d7eb)
