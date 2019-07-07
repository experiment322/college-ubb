from datetime import date
from domain.confirmare import Confirmare


class ClientiController(object):
    def __init__(self, repo):
        self._repo = repo

    def gaseste(self, nume):
        """Returneaza o lista de reprezentari textuale cu toti clientii care contin sirul (nume) in numele lor"""
        clienti = self._repo.get_all()
        result = [client.to_string() for client in clienti if nume in client.get_nume()]
        return result

    def confirma(self, nume, zbor, data):
        """
        Creeaza o confirmare si returneaza o reprezentare textuala a sa
        Daca combinatia (nume)+(zbor) nu exista sau (data) este invalida/in trecut atunci returneaza None
        """
        try:
            data = date(*[int(part) for part in data.split("/")])
            client, *_ = self._repo.gaseste_zbor(zbor)
            if nume == client.get_nume() and data > date.today():
                return Confirmare(client, data).to_string()
            else:
                raise ValueError
        except ValueError:
            return None
