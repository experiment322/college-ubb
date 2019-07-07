class DTO(object):
    def __init__(self, data):
        self._data = data

    def split(self, sep=","):
        if len(self._data.split()) == 0:
            return []
        return self._data.split(sep)

    def validate(self, required_fields):
        fields = self.split()
        if len(fields) != len(required_fields):
            raise ValueError("Invalid parameters. Expected: {}".format(required_fields))
