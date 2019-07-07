import json
from domain.client import Client


class ClientiRepository(object):
    def __init__(self, repo_file):
        self._list = []
        file = open(repo_file)
        for line in file:
            # stringul de tip JSON este parsat
            # iar apoi separat in argumente pentru constructorul Client
            client = Client(**json.loads(line))
            self._list.append(client)
        file.close()

    def get_all(self):
        """Returneaza o lista cu toti clientii"""
        return self._list

    def gaseste_zbor(self, cod):
        """Returneaza o lista cu toti clientii care au codul de zbor (cod)"""
        result = []
        for client in self._list:
            if client.get_zbor() == cod:
                result.append(client)
        return result
