import streamlit as st
import pandas as pd
import os

st.set_page_config(page_title="Resultados Benchmark", layout="wide")
st.title("Visualizador de Resultados")

opciones = [f for f in ['resultados.csv', 'prueba_individual.csv'] if os.path.exists(f)]

if not opciones:
    st.error("No se encontraron archivos CSV. ¡Ejecuta primero el programa en C!")
else:
    archivo = st.selectbox("Selecciona el set de datos:", opciones)
    df = pd.read_csv(archivo)
    st.subheader(f"Datos: {archivo}")
    st.dataframe(df)
    pivot = df.groupby(['Tamano', 'Algoritmo'])['Time_ms'].mean().unstack()
    st.line_chart(pivot, use_container_width=True)
