import random
#Generar numeros aleatorios ordenados de mayor a menor 

def generar_numeros(nombre_doc, cantidad_numeros):
    lista=[]
    archivo=open(nombre_doc,"w")
    for _ in range(cantidad_numeros):
        num = random.randint(-1000000, 1000000)
        lista.append(num)
    lista.sort()
    lista.reverse()
    for i in lista:
        archivo.write(str(i)+"\n")
    archivo.close()

a=10
b=6
valor= a**b
generar_numeros("dataset 2 de "+str(a)+"^"+str(b)+" numeros aleatorios ordenados de mayor a menor.txt",valor)
        
