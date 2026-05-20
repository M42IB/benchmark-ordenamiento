# Benchmarking de Algoritmos de Ordenamiento en C

**Autores:** Ivan Montoya Barrera y Gustavo Perez Garduño  
**Materia:** Análisis de algoritmos
**Fecha de entrega:** 25 de Mayo del 2026

## Descripción del Proyecto
Este proyecto es un banco de pruebas (benchmark) desarrollado en lenguaje C para analizar y comparar empíricamente el rendimiento de cuatro algoritmos de ordenamiento frente a diferentes escenarios y volúmenes de datos. 

Los algoritmos analizados son:
1. **Insertion Sort** ($O(n^2)$)
2. **Merge Sort** ($O(n \log n)$)
3. **Radix Sort** ($O(n)$)
4. **Timsort** ($O(n \log n)$ optimizado para datos reales)

El programa evalúa el tiempo de ejecución (en milisegundos), el número de comparaciones y los movimientos en memoria (swaps) a través de arreglos de distintos tamaños ($N$) y 5 distribuciones de datos diferentes: *Uniforme, Ordenado, Reverso, Casi Ordenado y con Duplicados*.

---

## Compilación y Ejecución

Para garantizar que el entorno cuente con todas las herramientas necesarias para compilar el código C y generar las gráficas en Python, siga estos pasos en su terminal de Linux (o WSL):

### Instalar dependencias (Requisitos previos)
El proyecto requiere el compilador GCC, la herramienta Make, y Python 3 con las librerías de análisis de datos. Ejecute este comando para instalar todo lo necesario:
```bash
sudo apt update && sudo apt install build-essential python3 python3-pandas python3-matplotlib -y

## Guía rápida
1. **Instalar dependencias:** `sudo apt update && sudo apt install build-essential python3 python3-pandas python3-matplotlib python3-pip -y`
2. **Compilar:** `cd src && make`
3. **Ejecutar:** `./benchmark`
4. **Visualizar:** `pip install streamlit && streamlit run app.py`
