/*
 * Implementación de Algoritmos de Ordenamiento
 * Proyecto: Benchmarking en C
 */

#include "sorts.h"
#include <stdlib.h>

// 1. Insertion Sort O(n^2)
void insertion_sort(int *arr, int n, Metricas *m) {
    m->comparaciones = 0;
    m->swaps_moves = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        m->swaps_moves++; // Movimiento: guardar el elemento actual en 'key'
        int j = i - 1;

        // Mover los elementos mayores que 'key' una posición adelante
        while (j >= 0) {
            m->comparaciones++; // Contamos cada vez que evaluamos la condición del if implícito
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                m->swaps_moves++; // Movimiento: desplazar elemento a la derecha
                j = j - 1;
            } else {
                break; // Si ya no es mayor, rompemos el ciclo
            }
        }
        arr[j + 1] = key;
        m->swaps_moves++; // Movimiento: insertar 'key' en su posición final
    }
}

// 2. Merge Sort O(n log n)
// Funciones auxiliares para Merge Sort
void merge(int *arr, int left, int mid, int right, Metricas *m) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Reservar memoria dinámica para los sub-arreglos temporales
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copiar los datos a los arreglos L[] y R[]
    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        m->swaps_moves++; // Contabilizamos el movimiento de memoria
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        m->swaps_moves++; 
    }

    // Fusionar los arreglos temporales de vuelta al original arr[left..right]
    i = 0; 
    j = 0; 
    k = left;
    while (i < n1 && j < n2) {
        m->comparaciones++; // Contabilizamos la comparación
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        m->swaps_moves++; // Movimiento de vuelta al arreglo original
        k++;
    }

    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        m->swaps_moves++;
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        m->swaps_moves++;
        j++;
        k++;
    }

    // Liberar la memoria para evitar fugas (memory leaks)
    free(L);
    free(R);
}

// Función recursiva de Merge Sort
void merge_sort_recursive(int *arr, int left, int right, Metricas *m) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenar la primera y segunda mitad
        merge_sort_recursive(arr, left, mid, m);
        merge_sort_recursive(arr, mid + 1, right, m);

        // Fusionar ambas mitades
        merge(arr, left, mid, right, m);
    }
}

// 2. Merge Sort O(n log n) - Función Envolvente (Wrapper)
void merge_sort(int *arr, int n, Metricas *m) {
    m->comparaciones = 0;
    m->swaps_moves = 0;
    merge_sort_recursive(arr, 0, n - 1, m);
}

// 3. Radix Sort O(n)-------------------------------------------------------------
// Función auxiliar para Radix Sort: Obtener el valor máximo del arreglo
int get_max(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Subrutina Counting Sort adaptada para un dígito específico (exp)
void count_sort(int *arr, int n, int exp, Metricas *m) {
    int *output = (int *)malloc(n * sizeof(int));
    int i, count[10] = {0};

    // Almacenar el conteo de ocurrencias de cada dígito
    for (i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Cambiar count[i] para que contenga la posición real en output[]
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Construir el arreglo de salida (recorriendo de atrás hacia adelante para mantener estabilidad)
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        m->swaps_moves++; // Movimiento: de arr[] a output[]
    }

    // Copiar el arreglo de salida de vuelta al arreglo original
    for (i = 0; i < n; i++) {
        arr[i] = output[i];
        m->swaps_moves++; // Movimiento: de output[] a arr[]
    }
    free(output);
}

// 3. Radix Sort O(n)
void radix_sort(int *arr, int n, Metricas *m) {
    // Inicializar métricas. Radix Sort NO hace comparaciones entre elementos.
    m->comparaciones = 0; 
    m->swaps_moves = 0;

    // Encontrar el número máximo para saber cuántos dígitos tiene
    int max = get_max(arr, n);

    // Ejecutar Counting Sort para cada dígito (unidades, decenas, centenas...)
    for (int exp = 1; max / exp > 0; exp *= 10) {
        count_sort(arr, n, exp, m);
    }
}

// 4. Timsort (Híbrido)

// ============================================================================
// 4. TIMSORT (Híbrido) O(n log n)
// ============================================================================

// Definimos el tamaño del bloque (Run)
#define RUN 32

// Función auxiliar: Insertion Sort adaptado para un rango específico
void insertion_sort_rango(int *arr, int left, int right, Metricas *m) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        m->swaps_moves++; // Movimiento: guardar 'key'
        int j = i - 1;

        while (j >= left) {
            m->comparaciones++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                m->swaps_moves++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        m->swaps_moves++;
    }
}

// Función principal: Timsort
void timsort(int *arr, int n, Metricas *m) {
    m->comparaciones = 0;
    m->swaps_moves = 0;

    // 1. Ordenar sub-arreglos de tamaño RUN usando Insertion Sort
    for (int i = 0; i < n; i += RUN) {
        // Calcular el límite derecho sin pasarse del tamaño total del arreglo
        int right = (i + RUN - 1 < n - 1) ? (i + RUN - 1) : (n - 1);
        insertion_sort_rango(arr, i, right, m);
    }

    // 2. Empezar a fusionar a partir del tamaño RUN, doblando el tamaño cada vez
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

            // Solo fusionar si hay un arreglo derecho (mid < right)
            if (mid < right) {
                // ¡Reutilizamos la función merge que ya programaste arriba!
                merge(arr, left, mid, right, m);
            }
        }
    }
}