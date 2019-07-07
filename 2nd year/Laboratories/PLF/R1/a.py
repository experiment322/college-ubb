from prog import *

def inList (l, e):
    if eListaVida(l): return False
    if primElem(l) == e: return True
    return inList(sublista(l), e)

def main ():
    l = creareLista()
    e = int(input('e='))
    print(inList(l, e))

main()
