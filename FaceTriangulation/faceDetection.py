"""
Actividad 5.1 Triangulación de Delaunay
Author: Emiliano Viotti
Students: Samuel Alejandro Díaz del Guante (A01637592) y Roberto López Cisneros (A01637335)
Last update: November 05, 2021

Descripcion: 
  Codigo que lee una imagen para obtener las predicciones en una serie de puntos coordenada
  para despues escribirlos en un archivo de texto

Input: 
  Archivo jpg que sera procesado por las librerias cv2 y dlib
Output: 
  Escribir en un archivo los 68 puntos de los descriptores
"""

import cv2
import dlib

# Read image from image path
img = cv2.imread('image.jpg', 1)
    
# set up the 68 point facial landmark detector
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")

# convert to grayscale
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# detect faces in the image
faces_in_image = detector(img_gray, 0)

# Process only first image
face = faces_in_image[0]

# assign the facial landmarks
landmarks = predictor(img_gray, face)

# unpack the 68 landmark coordinates from the dlib object into a list
landmarks_list = []
for i in range(0, landmarks.num_parts):
    landmarks_list.append((landmarks.part(i).x, landmarks.part(i).y))

# write points to file
with open('data.txt', 'w') as my_list_file: 
    for element in landmarks_list: 
        line = str(element[0]) + " " + str(element[1])
        my_list_file.write('%s\n' % line)
