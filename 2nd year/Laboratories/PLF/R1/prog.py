class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None

class Lista:
    def __init__(self):
        self.prim = None


'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod


'''
verificare lista vida
'''
def eListaVida(lista):
    return lista.prim is None


'''
returnare prim element din lista
'''
def primElem(lista):
    return lista.prim.e


'''
adaugare inceput
'''
def adaugaInceput(lista, e):
    nod = Nod(e)
    nod.urm = lista.prim
    lista.prim = nod
    return lista


'''
clonare lista fara primul element
'''
def sublista(lista):
    return sublista_rec(lista.prim.urm)

def sublista_rec(nod):
    if nod is None: return Lista()
    return adaugaInceput(sublista_rec(nod.urm), nod.e)


'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)

def tipar_rec(nod):
    if nod != None:
        print (nod.e)
        tipar_rec(nod.urm)


'''
program pentru test
'''
#def main():
#    list = creareLista()
#    tipar(list)
#    tipar(adaugaInceput(sublista(list),4))

#main()
