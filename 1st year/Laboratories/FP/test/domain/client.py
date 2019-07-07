class Client(object):
    def __init__(self, nr, nume, zbor):
        self._nr = nr
        self._nume = nume
        self._zbor = zbor

    def set_nr(self, nr):
        """Seteaza numarul clientului"""
        self._nr = nr

    def get_nr(self):
        """Returneaza numarul clientului"""
        return self._nr

    def set_nume(self, nume):
        """Seteaza numele clientului"""
        self._nume = nume

    def get_nume(self):
        """Returneaza numele clientului"""
        return self._nume

    def set_zbor(self, zbor):
        """Seteaza codul de zbor asociat clientului"""
        self._zbor = zbor

    def get_zbor(self):
        """Returneaza codul de zbor asociat clientului"""
        return self._zbor

    def to_string(self):
        """Returneaza o reprezentare textuala a clientului"""
        return "{},{},{}".format(self._nr, self._nume, self._zbor)
