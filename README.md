# BD2-lab6.2

## Implementación del índice

El script de Python en `generarIndex` utiliza la biblioteca Natural Language Toolkit (NLTK) para procesar texto en español. En específico, realiza la extracción y el almacenamiento de palabras raíces (o 'stems') de múltiples archivos de texto, excluyendo las palabras de parada (o 'stopwords'). Su funcionalidad es la siguiente:


1. Lectura de las palabras de parada: Lee un archivo de palabras de parada ('stoplist.txt') y las almacena en un conjunto para su uso posterior.

2. Procesamiento de archivos: Itera sobre cada archivo de texto (libro). Para cada archivo, realiza lo siguiente:

3. Abre el archivo y tokeniza el texto en palabras individuales.

4.  Filtra los tokens para excluir los que no son alfabéticos.

5. Aplica el algoritmo de derivación ('stemming') a cada token y verifica si la palabra raíz resultante está en la lista de palabras de parada. Si no está en la lista, se añade a un diccionario, donde la clave es la palabra raíz y el valor es un conjunto de los identificadores de archivo en los que aparece la palabra.

6.Reducción y ordenamiento de tokens: Limita el número de tokens al número especificado de las palabras raíz más frecuentes. Luego, ordena el diccionario alfabéticamente por palabra raíz.

7. Escritura de resultados: Escribe los tokens y sus respectivos identificadores de archivo en un archivo de salida ('index.txt'). Cada línea del archivo de salida tiene el formato "token:lista_de_identificadores_de_archivo".

## Resultados obtenidos
El archivo `main.cpp` ubicada en la carpeta "BD2-lab6.2" encontrará el programa que se encarga de leer el índice invertido "index.txt" generado en el paso anterior.

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
