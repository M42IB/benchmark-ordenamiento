import pandas as pd
import matplotlib.pyplot as plt

print("Cargando datos desde prueba_individual.csv...")

# 1. Leer el archivo CSV
try:
    df = pd.read_csv('prueba_individual.csv')
except FileNotFoundError:
    print("Error: No se encontro el archivo prueba_individual.csv")
    exit()

# 2. Agrupar los datos (tamaños en X, algoritmos como columnas)
df_promedio = df.groupby(['Tamano', 'Algoritmo'])['Time_ms'].mean().unstack()

# 3. Configurar el tamaño de la gráfica
plt.figure(figsize=(10, 6))

# 4. Trazar una línea para cada algoritmo
for algoritmo in df_promedio.columns:
    plt.plot(df_promedio.index, df_promedio[algoritmo], marker='x', linewidth=2, linestyle='--', label=algoritmo)

# 5. Textos y diseño visual
plt.title('Prueba Personalizada: Tiempo vs Tamano (Logaritmica)', fontsize=14)
plt.xlabel('Tamano del Arreglo (N)', fontsize=12)
plt.ylabel('Tiempo (ms) - Escala Log', fontsize=12)

# ---> ACTIVAR LA ESCALA LOGARÍTMICA AQUÍ <---
plt.yscale('log')

plt.grid(True, linestyle=':', alpha=0.7)
plt.legend(title='Algoritmos')

# 6. Guardar la imagen generada
nombre_imagen = 'grafica_personalizada.png'
plt.savefig(nombre_imagen, dpi=300, bbox_inches='tight')
print(f"¡Exito! La grafica se ha guardado como: {nombre_imagen}")