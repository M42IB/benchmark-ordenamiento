import streamlit as st
import pandas as pd
import os

# Configuración de la página web
st.set_page_config(page_title="Resultados Benchmark", layout="wide")
st.title("📊 Visualizador de Resultados: Benchmarking de Algoritmos")

# 1. Buscar de forma dinámica los archivos de datos generados en C
opciones = [f for f in ['resultados.csv', 'prueba_individual.csv'] if os.path.exists(f)]

if not opciones:
    st.error("No se encontraron archivos CSV en la raíz. ¡Ejecuta primero tu programa en C!")
else:
    # Selector interactivo de archivo
    archivo = st.selectbox("Selecciona el set de datos a visualizar:", opciones)
    df = pd.read_csv(archivo)
    
    # 2. Barra lateral interactiva para filtrar datos al gusto
    st.sidebar.header("Filtros de Análisis")
    algoritmos = st.sidebar.multiselect("Seleccionar Algoritmos:", df['Algoritmo'].unique(), default=df['Algoritmo'].unique())
    distribuciones = st.sidebar.multiselect("Seleccionar Distribuciones:", df['Distribucion'].unique(), default=df['Distribucion'].unique())
    
    # Aplicar filtros dinámicos
    df_filtrado = df[(df['Algoritmo'].isin(algoritmos)) & (df['Distribucion'].isin(distribuciones))]
    
    # 3. Despliegue de la tabla de datos procesados
    st.subheader(f"Vista de Tabla: {archivo}")
    st.dataframe(df_filtrado)
    
    # 4. Agrupar y promediar los tiempos para la gráfica de líneas
    pivot = df_filtrado.groupby(['Tamano', 'Algoritmo'])['Time_ms'].mean().unstack()
    
    # Despliegue de la gráfica interactiva de líneas (Estándar actualizado)
    st.subheader("Gráfica de Rendimiento (Tiempo vs Tamaño)")
    st.line_chart(pivot, width="stretch")
