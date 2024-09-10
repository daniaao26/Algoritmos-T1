import random

def generar_matrices(nombre_doc, filas, columnas):
    archivo = open(nombre_doc, "w")
    for _ in range(filas):
        fila=[]
        for _ in range(columnas):
            num= random.randint(-1000, 1000)
            fila.append(str(num))
        archivo.write(" ".join(fila)+"\n")
    archivo.close()
    
filas= 2000
columnas=2000
generar_matrices("matriz A de dimensiones "+str(filas)+"x"+str(columnas)+" rango de numeros de -1000 a 1000"+".txt",filas, columnas)