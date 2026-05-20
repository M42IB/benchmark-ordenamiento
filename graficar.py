import pandas as pd
import matplotlib.pyplot as plt

print("Cargando datos desde resultados.csv...")

# 1. Leer el archivo CSV
try:
    df = pd.read_csv('resultados.csv')
except FileNotFoundError:
    print("Error: No se encontro el archivo resultados.csv")
    exit()

# 2. Filtrar los datos: Solo usaremos la distribución "Uniforme" para esta primera gráfica
df_uniforme = df[df['Distribucion'] == 'Uniforme']

# 3. Agrupar y promediar: Como hicimos 3 repeticiones, sacamos el tiempo promedio
# Esto crea una tabla donde las filas son los Tamaños y las columnas los Algoritmos
df_promedio = df_uniforme.groupby(['Tamano', 'Algoritmo'])['Time_ms'].mean().unstack()

# 4. Configurar la gráfica
plt.figure(figsize=(10, 6))

# Trazar una línea para cada algoritmo
for algoritmo in df_promedio.columns:
    plt.plot(df_promedio.index, df_promedio[algoritmo], marker='o', linewidth=2, label=algoritmo)

# 5. Diseño visual
plt.title('Tiempo de Ejecucion vs Tamano (Distribucion Uniforme) - Logaritmica', fontsize=14)
plt.xlabel('Tamano del Arreglo (N)', fontsize=12)
plt.ylabel('Tiempo Promedio (ms) - Escala Log', fontsize=12)

# ---> ACTIVAR LA ESCALA LOGARÍTMICA AQUÍ <---
plt.yscale('log')

plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(title='Algoritmos')

# 6. Guardar la imagen
nombre_imagen = 'grafica_uniforme.png'
plt.savefig(nombre_imagen, dpi=300, bbox_inches='tight')
print(f"¡Exito! La grafica se ha guardado como: {nombre_imagen}")