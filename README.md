# Tarea3
## Primeros pasos
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: [GitHub](https://github.com/Pupitah/Tarea2).
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
   
## Cómo ejecutar
Para ejecutar el programa, debemos:
1. Abrir un terminal
2. Usar el siguiente comando en la terminal:
````
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea3
````

Y luego ejecutar:
````
./tarea3
````
Al presionar el botón ``run``, ejecutaremos el programa y se desplegará este menú:

````
Estado inicial del puzzle:
x 2 8 
1 3 4 
6 5 7 

***** EJEMPLO MENU ******
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción:
````

## Opciones:
1. Búsqueda en Profundidad (DFS): Este método de resolución del rompecabezas se sumerge en las diferentes opciones de manera exhaustiva, como un explorador en un bosque, buscando minuciosamente cada sendero en busca de la salida. Si encuentra una solución, detalla el camino seguido para resolver el rompecabezas paso a paso.

2. Búsqueda en Anchura (BFS): A diferencia de DFS, esta estrategia examina de manera sistemática todas las posibles soluciones del rompecabezas, como un detective que revisa cada pista de manera ordenada y meticulosa. Explora todas las opciones en un nivel antes de pasar al siguiente. Si encuentra una solución, muestra el estado final del rompecabezas.

3. Salir: Al seleccionar esta opción, el programa concluye su ejecución y se cierra.

# ¡Gracias por usar mi código!
