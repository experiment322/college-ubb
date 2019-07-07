def run(clienti_controller):
    """Ruleaza loop-ul de ui pentru clienti utilizand controller-ul (clienti_controller)"""
    while True:
        print("=" * 80)
        print("Comenzi: cauta, confirma, iesire")
        comanda = input("COMANDA: ")
        if comanda == "cauta":
            nume = input("NUME: ")
            print(*clienti_controller.gaseste(nume), sep="\n")
        if comanda == "confirma":
            nume = input("NUME: ")
            zbor = input("COD: ")
            data = input("DATA: ")
            confirmare = clienti_controller.confirma(nume, zbor, data)
            if confirmare is not None:
                print("Confirmare reusita")
                print(confirmare)
            else:
                print("Confirmare esuata")
        if comanda == "iesire":
            break
