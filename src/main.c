/*
 * Proyecto: Benchmarking de Algoritmos de Ordenamiento en C
 * Autores: Ivan Montoya Barrera y Gustavo Perez Garduño
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sorts.h"
#include "utils.h"

// Tamaños de prueba definidos por los requisitos del proyecto
int sizes[] = {100, 200, 300, 400, 500, 1000, 2500, 5000, 7500};
int num_sizes = 9;

const char *nombres_algoritmos[] = {"Insertion", "Merge", "Radix", "Timsort"};
const char *nombres_distribuciones[] = {"Uniforme", "Ordenado", "Reverso", "Casi_Ordenado", "Duplicados"};

// Envolvente para ejecutar el algoritmo correcto según el índice
void ejecutar_algoritmo(int algo_idx, int *arr, int n, Metricas *m) {
    if (algo_idx == 0) insertion_sort(arr, n, m);
    else if (algo_idx == 1) merge_sort(arr, n, m);
    else if (algo_idx == 2) radix_sort(arr, n, m);
    else if (algo_idx == 3) timsort(arr, n, m);
}

// Función para la Opción 1: El lote de pruebas obligatorio (Multiplataforma)
void ejecutar_benchmark_completo() {
    printf("\n[+] Iniciando el benchmark completo...\n");
    
    FILE *csv = fopen("../resultados.csv", "w");
    if (csv == NULL) {
        printf("[!] Error: No se pudo crear el archivo resultados.csv\n");
        return;
    }

    // Cabecera del CSV
    fprintf(csv, "Algoritmo,Tamano,Distribucion,Repeticion,Time_ms,Comparaciones,Swaps_Moves,Estable\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *arr_original = (int *)malloc(n * sizeof(int));
        int *arr_test = (int *)malloc(n * sizeof(int));

        for (int dist = 0; dist < 5; dist++) {
            for (int rep = 1; rep <= 3; rep++) {
                // 1. Generar la distribución correspondiente
                if (dist == 0) generar_uniforme(arr_original, n);
                else if (dist == 1) generar_ordenado(arr_original, n);
                else if (dist == 2) generar_reverso(arr_original, n);
                else if (dist == 3) generar_casi_ordenado(arr_original, n);
                else if (dist == 4) generar_duplicados(arr_original, n);

                for (int algo = 0; algo < 4; algo++) {
                    copiar_arreglo(arr_original, arr_test, n);
                    Metricas m = {0, 0, 0, 1}; // Los 4 algoritmos elegidos son estables (1 = SI)

                    // 2. Medir el tiempo exacto de ejecución
                    clock_t start = clock();
                    ejecutar_algoritmo(algo, arr_test, n, &m);
                    clock_t end = clock();
                    
                    m.time_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

                    // 3. Escribir resultados en el CSV
                    // Si es Radix (algo == 2), imprimimos NA en comparaciones
                    if (algo == 2) {
                        fprintf(csv, "%s,%d,%s,%d,%.4f,NA,%lld,SI\n",
                            nombres_algoritmos[algo], n, nombres_distribuciones[dist],
                            rep, m.time_ms, m.swaps_moves);
                    } else {
                        fprintf(csv, "%s,%d,%s,%d,%.4f,%lld,%lld,SI\n",
                            nombres_algoritmos[algo], n, nombres_distribuciones[dist],
                            rep, m.time_ms, m.comparaciones, m.swaps_moves);
                    }
                }
            }
        }
        free(arr_original);
        free(arr_test);
        printf("[-] Evaluados algoritmos para N = %d\n", n);
    }
    fclose(csv);
    printf("[+] Benchmark completado con exito. Resultados guardados en resultados.csv\n");

    printf("[+] Generando graficas con Python...\n");
    
    // Ejecuta de forma segura el script de Python sin forzar comandos dependientes de un OS específico
    int sys_ret = system("cd .. && python3 graficar.py");
    if (sys_ret == -1) {
        printf("[!] Aviso: No se pudo ejecutar el script de Python automáticamente.\n");
    } else {
        printf("\n========================================================\n");
        printf(" ¡Todo listo! Ya puedes revisar los siguientes archivos \n");
        printf(" en la carpeta principal de tu proyecto:               \n");
        printf(" 1. resultados.csv (Tabla de datos)                    \n");
        printf(" 2. grafica_uniforme.png (Grafica comparativa)         \n");
        printf("========================================================\n");
    }
}

// Función para la Opción 2: Prueba interactiva Múltiple
void ejecutar_prueba_personalizada() {
    int num_valores;
    printf("\n--- PRUEBA PERSONALIZADA MULTIPLE ---\n");
    printf("¿Cuantos tamanos diferentes deseas probar? (ej. 3): ");
    
    if (scanf("%d", &num_valores) != 1 || num_valores <= 0) {
        printf("[!] Entrada no valida.\n");
        while (getchar() != '\n'); 
        return;
    }

    // Crear arreglo para guardar los tamaños que elija el usuario
    int *tamanos_custom = (int *)malloc(num_valores * sizeof(int));
    
    for (int i = 0; i < num_valores; i++) {
        printf("Ingresa el tamano #%d: ", i + 1);
        if (scanf("%d", &tamanos_custom[i]) != 1 || tamanos_custom[i] <= 0) {
            printf("[!] Entrada no valida. Se usara 1000 por defecto.\n");
            tamanos_custom[i] = 1000;
            while (getchar() != '\n'); 
        }
    }

    // Abrir el CSV en modo sobreescritura ("w") para que la gráfica siempre salga limpia
    FILE *csv = fopen("../prueba_individual.csv", "w");
    if (csv != NULL) {
        fprintf(csv, "Algoritmo,Tamano,Distribucion,Repeticion,Time_ms,Comparaciones,Swaps_Moves,Estable\n");
        
        printf("\n[+] Ejecutando algoritmos...\n");
        
        for (int s = 0; s < num_valores; s++) {
            int n = tamanos_custom[s];
            int *arr_test = (int *)malloc(n * sizeof(int));

            for (int algo = 0; algo < 4; algo++) {
                generar_uniforme(arr_test, n); // Usamos uniforme por defecto para la prueba rápida
                Metricas m = {0, 0, 0, 1};

                clock_t start = clock();
                ejecutar_algoritmo(algo, arr_test, n, &m);
                clock_t end = clock();
                
                m.time_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
                
                if (algo == 2) {
                    fprintf(csv, "%s,%d,Uniforme,1,%.4f,NA,%lld,SI\n", nombres_algoritmos[algo], n, m.time_ms, m.swaps_moves);
                } else {
                    fprintf(csv, "%s,%d,Uniforme,1,%.4f,%lld,%lld,SI\n", nombres_algoritmos[algo], n, m.time_ms, m.comparaciones, m.swaps_moves);
                }
            }
            free(arr_test);
            printf("    -> Listo tamano %d\n", n);
        }
        fclose(csv);
        printf(" Resultados guardados en 'prueba_individual.csv'\n");
    }

    free(tamanos_custom);

    // Llamar al nuevo script de Python
    printf("[+] Generando grafica de tu prueba personalizada...\n");
   int sys_ret = system("cd .. && python3 graficar_prueba.py");
    if (sys_ret == -1) {
        printf("[!] Aviso: No se pudo ejecutar el script de Python automáticamente.\n");
    }
}

int main() {
    srand(time(NULL));
    int opcion;

    do {
        printf("\n========================================\n");
        printf("                  MENU\n");
        printf("========================================\n");
        printf("1. Ejecutar benchmark completo (Generar CSV y Grafica)\n");
        printf("2. Ejecutar prueba personalizada rapida (Registrar en CSV)\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            opcion = 0;
            while (getchar() != '\n'); 
        }

        switch(opcion) {
            case 1: ejecutar_benchmark_completo(); break;
            case 2: ejecutar_prueba_personalizada(); break;
            case 3: printf("\nSaliendo del programa...\n"); break;
            default: printf("\n[!] Opcion no valida.\n");
        }
    } while(opcion != 3);

    return 0;
}