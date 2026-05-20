#ifndef UTILS_H
#define UTILS_H

// Estructura para almacenar las métricas de cada corrida
typedef struct {
    double time_ms;
    long long comparaciones;
    long long swaps_moves;
    int estable; // 1 para SI, 0 para NO
} Metricas;

// Generadores de arreglos para las 5 distribuciones
void generar_uniforme(int *arr, int n);
void generar_ordenado(int *arr, int n);
void generar_reverso(int *arr, int n);
void generar_casi_ordenado(int *arr, int n);
void generar_duplicados(int *arr, int n);

// Función de utilidad para clonar arreglos (necesario para pruebas justas)
void copiar_arreglo(int *origen, int *destino, int n);

#endif