import random

#Generar numeros aleatorios 
def generar_numeros(nombre_doc, cantidad_numeros):
    archivo=open(nombre_doc,"w")
    for _ in range(cantidad_numeros):
        num = random.randint(-1000, 1000)
        archivo.write(str(num)+"\n")
    archivo.close()

a=10
b=6
valor= a**b
generar_numeros("dataset de "+str(a)+"^"+str(b)+" numeros aleatorios.txt",valor)
        
