class Confirmare(object):
    def __init__(self, client, data):
        self._client = client
        self._data = data

    def set_client(self, client):
        """Seteaza clientul asociat confirmarii"""
        self._client = client

    def get_client(self):
        """Returneaza clientul asociat confirmarii"""
        return self._client

    def set_data(self, data):
        """Seteaza data confirmarii"""
        self._data = data

    def get_data(self):
        """Returneaza data confirmarii"""
        return self._data

    def to_string(self):
        """Returneaza o reprezentare textuala a confirmarii"""
        return "{},{}".format(self._client.to_string(), self._data)
