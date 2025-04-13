# Generador-Combinaciones-CPP
Programa que genera todas las combinaciones de (n,r) en orden lexicográfico creciente que son exportadas a un archivo CSV

**Autor:** María Fernanda Hernández García

---
## Requisitos del sistema para ejecutar el código
 - C++
 - g++
 ## Compilación y ejecución del código


Introducir en la terminal:

***Clonación:***
  ```bash
   git clone https://github.com/FerHdez08/Generador-Combinaciones-CPP.git
```
***Cambio de directorio:***
```bash
   cd Generador-Combinaciones-CPP
```
***Compilación:***
```bash
   g++ "GeneradorCombinaciones.cpp" -o GeneradorCombinaciones
```
***Ejecución:***
```bash
   GeneradorCombinaciones
```
*o en su defecto, si no es reconocido, ejecute:*
```bash
   .\GeneradorCombinaciones
```
<br>

***Alternativa:*** <br>

*Descargar el archivo Generador-Combinaciones-CPP.cpp y compilar desde un IDE a su preferencia.*


---

## Explicación del algoritmo: 

Este programa genera todas las **combinaciones de tamaño r** de un conjunto base de n elementos (numerados del 1 al n), guardándolas en un archivo CSV en **orden lexicográfico creciente**. El algoritmo sigue un enfoque iterativo eficiente sin recursión.

###  Pasos Clave del Algoritmo

1. **Inicialización**:
   - Crea un arreglo s de tamaño r con los primeros r elementos ([1, 2, ..., r]), que representa la primera combinación válida.

2. **Generación de Combinaciones**:
   - **Busca el "pivote" (m)**: El índice más a la derecha en s que puede incrementarse sin superar su valor máximo permitido (n - r + m + 1).
   - **Incrementa y ajusta**:
     - Aumenta s[m] en 1.
     - Los elementos a la derecha de m se rellenan en secuencia creciente (s[j] = s[j-1] + 1).
   - **Guarda cada combinación** en el archivo CSV.

3. **Terminación**:
   - El proceso termina cuando no quedan elementos por incrementar (m < 0), indicando que se generaron todas las combinaciones.
---

##  Orden Lexicográfico
El orden lexicográfico (como en un diccionario) organiza combinaciones comparando elementos de izquierda a derecha. Para combinaciones de r elementos de {1, 2, ..., n}:

- [a₁, a₂, ..., aᵣ] < [b₁, b₂, ..., bᵣ] si existe un índice k donde:
  - aₖ < bₖ
  - aᵢ = bᵢ para todo i < k

**Ejemplo** (combinaciones de 3 en {1,2,3,4,5}):  
1,2,3 < 1,2,4 < 1,2,5 < 1,3,4 < ... < 3,4,5

El código genera esas combinaciones mediante:

1. **Inicialización**: Comienza con [1, 2, ..., r]
2. **Iteración**:
   - Encuentra el elemento más a la derecha que puede incrementarse
   - Lo incrementa y reinicia los siguientes elementos
3. **Terminación**: Cuando ningún elemento puede incrementarse más
---

##  Validación de Entrada de Datos

El programa implementa un sistema robusto de validación para garantizar que los datos ingresados cumplan con los requisitos necesarios:

### Para la variable n (tamaño del conjunto base)
- **Límite inferior**: n > 1 (el conjunto no puede ser vacío o unitario)
- **Límite superior**: n ≤ 22 (valor predeterminado)

**Motivación del límite superior**:  
Se estableció este límite para:
- Prevenir la generación de archivos CSV excesivamente grandes
- Evitar superar el límite de 1,048,576 filas que soporta Microsoft Excel
- Garantizar un manejo eficiente de los archivos generados

**Nota**:  
Si necesitas procesar conjuntos más grandes, puedes modificar el límite cambiando el valor en la línea 16:
```c
 #define MAX 22  // Ajusta este valor según tus necesidades
 ```

### Para la variable r (tamaño de las combinaciones)
- **Límite inferior**: r ≥ 0 
- **Límite superior**: r ≤ n (no puede haber combinaciones más grandes que el conjunto base)


---

## Formato de salida:

El programa genera los resultados en un archivo CSV con el siguiente formato:

### Estructura del archivo
- **Nombre del archivo**: `combinaciones_n{X}_r{Y}.csv` (donde X es el valor de `n` e Y es el valor de `r`)
- **Por cada combinación**:
  - Los elementos aparecen separados por comas (`,`)
  - Cada combinación ocupa un renglón independiente

**Ruta absoluta** mostrada en consola al finalizar la ejecución

---

## Verificación C(n,r):

El programa incluye un sistema de verificación para garantizar que se generaron todas las combinaciones correctamente:

### Mecanismo de Verificación
1. **Cálculo Teórico**:
   - Utiliza las funciones **NumComb()** y **Factorial()**
   - Implementa la fórmula matemática estándar: <br>
      C(n,r) = n! / (r! * (n-r)!)


2. **Conteo Experimental**:
   - Cuenta cada combinación generada durante la ejecución
   - Almacena el total en la variable total

3. **Comparación Final**:
   ```cpp
   if(total == NumComb(n,r)) {
       cout << "Por lo que el conteo experimental y teórico coincide" << endl;
   }

---
