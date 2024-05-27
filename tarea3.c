#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/queue.h"
#include "tdas/extra.h"
#include <string.h>
#include <stdbool.h>
#include "tdas/stack.h"

typedef struct {
    int square[3][3];
    int x;
    int y;
    List* actions;
} State;

int distancia_L1(State* state) {
    int ev = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int val = state->square[i][j];
            if (val == 0) continue;
            int ii = (val) / 3;
            int jj = (val) % 3;
            ev += abs(ii - i) + abs(jj - j);
        }
    }
    return ev;
}

int is_final_state(State *estado){
    int final[3][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8}
    };
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(estado->square[i][j] != final[i][j]) return 0;
        }
    }
    return 1;
}

int estadoSolucionado(State* estado){
    int i, j;
    int valor = estado->square[0][0];
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            if(i == 0 && j == 0) continue;
            if(estado->square[i][j] < valor) return 0;
            valor = estado->square[i][j];
        }
    }
    return 1;
}

void transicion(State *estado, int accion) {
    int fila = estado->x;
    int columna = estado->y;
    int *ptrAccion = (int *)malloc(sizeof(int));
    *ptrAccion = accion;

    if (accion == 1 && (fila - 1) >= 0) {
        estado->square[fila][columna] = estado->square[fila - 1][columna];
        estado->square[fila - 1][columna] = 0;
        estado->x--;
        list_pushBack(estado->actions, ptrAccion);
    } else if (accion == 2 && (fila + 1) <= 2) {
        estado->square[fila][columna] = estado->square[fila + 1][columna];
        estado->square[fila + 1][columna] = 0;
        estado->x++;
        list_pushBack(estado->actions, ptrAccion);
    } else if (accion == 3 && (columna - 1) >= 0) {
        estado->square[fila][columna] = estado->square[fila][columna - 1];
        estado->square[fila][columna - 1] = 0;
        estado->y--;
        list_pushBack(estado->actions, ptrAccion);
    } else if (accion == 4 && (columna + 1) <= 2) {
        estado->square[fila][columna] = estado->square[fila][columna + 1];
        estado->square[fila][columna + 1] = 0;
        estado->y++;
        list_pushBack(estado->actions, ptrAccion);
    } else {
        free(ptrAccion);
        estado->x = -1;
    }
}

State* copy(State* n){
    State* new = (State*) malloc(sizeof(State));
    *new = *n;
    return new;
}

State *swap(State* estado, int filaCero, int columnaCero, int direccion){
    State *aux = copy(estado);
    int temp;

    switch (direccion){
        case 1:  // hacia arriba
            if (filaCero > 0){
                temp = aux->square[filaCero - 1][columnaCero];
                aux->square[filaCero - 1][columnaCero] = 0;
                aux->square[filaCero][columnaCero] = temp;
                aux->x = filaCero;
                aux->y = columnaCero - 1;
            } else {
                free(aux);
                return NULL;
            }
            break;
        case 2: // hacia abajo
            if(filaCero < 2){
                temp = aux->square[filaCero + 1][columnaCero];
                aux->square[filaCero + 1][columnaCero] = 0;
                aux->square[filaCero][columnaCero] = temp;
                aux->x = filaCero + 1;
                aux->y = columnaCero;
            } else {
                free(aux);
                return NULL;
            }
            break;
        case 3: // hacia la derecha
            if(columnaCero < 2){
                temp = aux->square[filaCero ][columnaCero + 1];
                aux->square[filaCero ][columnaCero + 1] = 0;
                aux->square[filaCero][columnaCero] = temp;
                aux->x = filaCero;
                aux->y = columnaCero + 1;
            } else {
                free(aux);
                return NULL;
            }
            break;
        case 4: // hacia la izquierda
            if(columnaCero > 0){
                temp = aux->square[filaCero][columnaCero - 1];
                aux->square[filaCero][columnaCero - 1] = 0;
                aux->square[filaCero][columnaCero] = temp;
                aux->x = filaCero;
                aux->y = columnaCero;
            } else {
                free(aux);
                return NULL;
            }
            break;
    }
    return aux;
}

State* crearCopia(const State *estado) {
    State *copiaEstado = (State*) malloc(sizeof(State));
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            copiaEstado->square[i][k] = estado->square[i][k];
        }
    }
    copiaEstado->x = estado->x;
    copiaEstado->y = estado->y;
    if (estado->actions != NULL) {
        copiaEstado->actions = list_create();
        int *accion = (int *)list_first(estado->actions);
        while (accion != NULL) {
            list_pushBack(copiaEstado->actions, accion);
            accion = (int *)list_next(estado->actions);
        }
    } else {
        copiaEstado->actions = NULL;
    }

    return copiaEstado; 
}

void imprimirEstado(const State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0) {
                printf("x ");
            } else {
                printf("%d ", estado->square[i][j]);
            }
        }
        printf("\n");
    }
}

void imprimirSolucion(State original, List *solucion) {
    if (solucion == NULL) {
        printf("No se encontró una solución.\n");
    } else {
        int contador = 1;
        int *accionActual = (int *)list_first(solucion);

        printf("Se ha encontrado una solucion\n");
        printf("Los pasos para llegar a la solucion son:\n\n");
        while (accionActual != NULL) {
            puts("*****************");
            printf("Paso %d: ", contador);
            if (*accionActual == 1) printf("Arriba\n");
            else if (*accionActual == 2) printf("Abajo\n");
            else if (*accionActual == 3) printf("Izquierda\n");
            else printf("Derecha\n");

            transicion(&original, *accionActual);
            imprimirEstado(&original);
            printf("distancia l1 %i\n", distancia_L1(&original));
            printf("\n");

            contador++;
            accionActual = (int *)list_next(solucion);
        }
        puts("*****************");
        list_clean(solucion);
        free(solucion);
    }
    printf("\n");
}

List* obtener_estados_adyacente(State* estado) {
    List *adyacentes = list_create();
    for(int i = 1; i <= 4; i++) {
        State *estadoNuevo = crearCopia(estado);
        transicion(estadoNuevo, i);
        if (estadoNuevo->x != -1) {
            list_pushBack(adyacentes, estadoNuevo);
        } else {
            list_clean(estadoNuevo->actions);
            free(estadoNuevo->actions);
            free(estadoNuevo);
        }
    }
    return adyacentes;
}

List *estadosAdyacentes(State *estado) {
    List* adyacentes = list_create();
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

            if(estado->square[i][j] == 0) {
                for(int direccion = 1; direccion <= 4; direccion++) {

                    State *aux = swap(estado, i, j, direccion);
                    if (aux != NULL) {
                        list_pushBack(adyacentes, aux);
                        list_pushBack(aux->actions, &direccion);
                    }
                }
            }
        }
    }
    return adyacentes;
}

List *dfs(State *estado_incial) {
    printf("Estado inicial:\n");
    imprimirEstado(estado_incial);
    printf("\n");
    Stack* stack = stack_create(stack);
    stack_push(stack, estado_incial);

    while(stack_top(stack) != NULL) {
        State* estado_actual = (State*)stack_top(stack);
        stack_pop(stack);
        if(list_size(estado_actual->actions) >= 15) continue;
        if(distancia_L1(estado_actual) == 0) {
            stack_clean(stack);
            free(stack);
            return estado_actual->actions;
        }
        List *estadosAdyacentes = obtener_estados_adyacente(estado_actual);
        State *adyacentes = (State*)list_first(estadosAdyacentes);
        while(adyacentes != NULL) {
            if(distancia_L1(adyacentes) <= 10) {
                stack_push(stack, adyacentes);
            }
            adyacentes = (State*)list_next(estadosAdyacentes);
        }
        list_clean(estado_actual->actions);
        free(estado_actual->actions);

        list_clean(estadosAdyacentes);
        free(estadosAdyacentes);
    }
    stack_clean(stack);
    free(stack);
    return NULL;
}

void bfs(State* estado) {
    int cont = 0;
    Queue *cola = queue_create(cola);
    if (cola == NULL) exit(EXIT_FAILURE);
    queue_insert(cola, estado);

    while(cola != NULL) {
        State* nodo = queue_front(cola);
        queue_remove(cola);
        if(estadoSolucionado(nodo)) {
            puts("========================================");
            printf("Se encontró solución!!\n");
            puts(" ");
            imprimirEstado(nodo);
            puts(" ");
            printf("Solución encontrada en %d pasos\n", cont);
            puts("========================================");
            puts(" ");
            return;
        }

        List* ady = estadosAdyacentes(nodo);
        State* aux = list_first(ady);
        while(aux) {
            queue_insert(cola, aux);
            aux = list_next(ady);
        }
        free(ady);
        free(aux);
        cont++;
    }
    printf("No se encontró solución :(\n");
}

int main() {
    State estado_inicial = {
        {{0, 2, 8}, 
         {1, 3, 4}, 
         {6, 5, 7}, 
        },  
        0, 0
    };
    estado_inicial.actions = list_create();
    List *resultado = NULL;

    printf("Estado inicial del puzzle:\n");
    imprimirEstado(&estado_inicial);

    int opcion;
    do {
        puts("========================================");
        puts("       Escoge método de búsqueda:");
        puts("========================================");

        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Salir");

        printf("Ingrese su opción: ");
        scanf(" %d", &opcion);

        switch (opcion) {
            case 1:
                resultado = dfs(&estado_inicial);
                imprimirSolucion(estado_inicial, resultado);
                presioneTeclaParaContinuar();
                break;
            case 2:
                bfs(&estado_inicial);
                presioneTeclaParaContinuar();
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}

