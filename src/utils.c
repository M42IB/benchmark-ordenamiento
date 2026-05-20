/*
 * Funciones de utilidad y generación de datos
 * Proyecto: Benchmarking de Algoritmos de Ordenamiento en C
 * Equipo: Ivan Montoya Barrera, Gustavo Perez Garduño
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// 1. Aleatorio uniforme
void generar_uniforme(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000; // Números entre 0 y 99,999
    }
}

// 2. Ya ordenado
void generar_ordenado(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i; 
    }
}

// 3. Orden reverso (inverso)
void generar_reverso(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

// 4. Casi ordenado (pocas permutaciones)
void generar_casi_ordenado(int *arr, int n) {
    generar_ordenado(arr, n);
    // Intercambiar un 5% de los elementos para desordenarlo un poco
    int swaps = n * 0.05;
    for (int i = 0; i < swaps; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

// 5. Muchos repetidos (duplicados)
void generar_duplicados(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        // Solo genera 5 valores posibles, forzando muchísimas repeticiones
        arr[i] = rand() % 5; 
    }
}

// Utilidad para copiar el arreglo original al arreglo de prueba
void copiar_arreglo(int *origen, int *destino, int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}