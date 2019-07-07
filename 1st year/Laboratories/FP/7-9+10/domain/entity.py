from collections import OrderedDict


class Entity(object):
    def __init__(self, tag):
        self._tag = tag

    def set_tag(self, tag):
        self._tag = tag

    def get_tag(self):
        return self._tag

    def to_ordered_dict(self):
        result = OrderedDict()
        result["ID"] = self._tag
        return result

    def matches(self, target):
        target_tag = target.get_tag()
        if self.fields_match(self._tag, target_tag):
            return True
        return False

    def try_get(self, getter, default):
        return getattr(self, getter)() if hasattr(self, getter) else default

    @staticmethod
    def fields_match(field_lt, field_rt):
        if field_lt is None or field_rt is None or field_lt == field_rt:
            return True
        return False
