'''
Actividad 5.6 Implementación de Simulated annealing
Authors: Samuel Alejandro Díaz del Guante (A01637592) y Roberto López Cisneros (A01637335)
Last update: November 26, 2021

Simulated annealing
-Descripcion: 
    Código que resuelve el problema del agente viajero por medio del recocido simulado
-Complejidad computacional: O(~n^2)
    *Depende de los parametros de simulación que son la temperatura, el numero de iteraciones y 
    factor de enfriamiento.

Input: 
    Se proporciona un archivo csv que contiene las distancias y coordenadas entre 128 ciudades. 

Output: 
    Path propuesto como solución y su costo
    Grafica del path solución
    Grafica de comportamiento de la temperatura en el tiempo
    Grafica de comportamiento del costo en el tiempo
'''

import csv
import random
import copy
import math
import matplotlib.pyplot as plt

'''
Funcion: Leer archivos de datos csv y alamacenar datos en una matriz
Entrada: Nombre del archivo
Salida: Matriz con informacion del archivo
Complejidad: O(n^2)
'''
def readFile(fileName):
    matrix = []
    with open(fileName, mode ='r')as file:
        csvFile = csv.reader(file)
        for row in csvFile:
                line = []
                for number in row:
                    line.append(float(number))
                matrix.append(line)
    return matrix

'''
Funcion: Calcular el costo de una solucion del TSP
Entrada: Camino a seguir y matriz de adjacencia con las distancias entre cada punto
Salida: Costo total para recorrer todos los puntos (Entero)
Complejidad: O(n)
'''
def calculateTSP(path, dist):
    cost = 0
    for x in range(len(dist)):
        cost += int(dist[path[x]][path[x+1]])
    return cost

'''
Funcion: Generar un camino aleatorio con todas las ciudades para inicializar el recocido simulado
Entrada: Ninguna
Salida: Vector con el orden de los indices de puntos a visitar
Complejidad: O(1)
'''
def generateRandomPath():
    path = random.sample(range(128), 128)
    path.append(path[0])
    return path

'''
Funcion: Cambiar el orden de dos vecinos en el camino de forma aleatoria
Entrada: Vector con el camino original
Salida: Vector con el camino modificado
Complejidad: O(1)
'''
def switch(path):
    i = random.sample(range(0,128), 2)
    if i[0] == 0:
        path[len(path)-1] = path[i[1]]
    elif i[1] == 0:
        path[len(path)-1] = path[i[0]]
    tmp = path[i[0]]
    path[i[0]] = path[i[1]]
    path[i[1]] = tmp
    return path

# Leer archivo con distancias y coordenadas
distances = readFile('cities_128.csv')
coordinates = readFile("sgb128_xy.txt")

# Generar camino aleatorio y calcular su costo
bestPath = generateRandomPath()
bestCost = calculateTSP(bestPath, distances)

# Parametros para controlar el recocido simulado
# temperature = 2500
# minTemp = 0.001
# k = 0.999
# iterations = 2500
temperature = 100
minTemp = 0.1
k = 0.9
iterations = 1000

costArr = [bestCost]
tempArr = [temperature]

# Simulated Annealing
while temperature > minTemp:
    print("Curr temp: " + str(temperature))
    # Reducir temperatura periodicamente
    temperature = temperature*k
    tempArr.append(temperature)
    # Realizar modificaciones al camino n numero de veces con una temperatura
    for j in range(iterations):
        # Copiar mejor solucion y generar una nueva de forma aleatoria cambiando vecinos
        currPath = copy.copy(bestPath)
        currPath = switch(currPath)
        currCost = calculateTSP(currPath,distances)
        # La nueva solucion es la mejor
        if currCost < bestCost:
            bestPath = currPath
            bestCost = currCost
        # Posibilidad de que una peor solucion sea elegida
        elif random.uniform(0,1) < math.exp((bestCost-currCost)/temperature):
            bestPath = currPath
            bestCost = currCost
        costArr.append(bestCost)

print(f"Best Path Found: {bestPath}")
print(f"Best Cost Found : {bestCost}")

# Graficar resultados
figure, axis = plt.subplots(1,3)

x = []
y = []
for index in bestPath:
    x.append(coordinates[index][0])
    y.append(coordinates[index][1])

axis[0].plot(x,y)
axis[0].set_title("Path")

axis[1].plot(tempArr)
axis[1].set_title("Temperature")

axis[2].plot(costArr)
axis[2].set_title(f"Cost: {bestCost}")

plt.show()