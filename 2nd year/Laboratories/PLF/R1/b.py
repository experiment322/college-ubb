from prog import *

def switchEven (l, e, p):
    if eListaVida(l): return Lista()
    if p % 2 == 0: return adaugaInceput(switchEven(sublista(l), e, p + 1), e)
    return adaugaInceput(switchEven(sublista(l), e, p + 1), primElem(l))

def switchEvenDriver (l, e):
    return switchEven(l, e, 1)

def main ():
    l = creareLista()
    e = int(input('e='))
    tipar(switchEvenDriver(l, e))

main()
