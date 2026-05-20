#ifndef SORTS_H
#define SORTS_H

#include "utils.h" // Necesario para reconocer la estructura Metricas

// Declaración de los 4 algoritmos actualizados para recibir métricas
void insertion_sort(int *arr, int n, Metricas *m);
void merge_sort(int *arr, int n, Metricas *m);
void radix_sort(int *arr, int n, Metricas *m);
void timsort(int *arr, int n, Metricas *m);

#endif