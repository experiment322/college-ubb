from copy import deepcopy


class EntityDictRepository(object):
    def __init__(self):
        self._list = {}
        self._available_tag = 0
        self._can_add = lambda entity: True
        self._can_del = lambda entity: True
        self._can_mod = lambda entity: True

    def set_add_negotiator(self, negotiator):
        self._can_add = negotiator

    def set_del_negotiator(self, negotiator):
        self._can_del = negotiator

    def set_mod_negotiator(self, negotiator):
        self._can_mod = negotiator

    def add_entity(self, entity):
        if not self._can_add(entity):
            raise PermissionError("Cannot add entity")
        self._available_tag += 1
        entity.set_tag(str(self._available_tag))
        self._list[str(self._available_tag)] = deepcopy(entity)

    def del_entity(self, entity):
        if not self._can_del(entity):
            raise PermissionError("Cannot del entity")
        tag = entity.get_tag()
        if tag not in self._list:
            raise LookupError("Cannot del nonexistent entity")
        del self._list[tag]

    def mod_entity(self, entity):
        if not self._can_mod(entity):
            raise PermissionError("Cannot mod entity")
        tag = entity.get_tag()
        if tag not in self._list:
            raise LookupError("Cannot mod nonexistent entity")
        self._list[tag] = deepcopy(entity)

    def get_entity(self, entity):
        result = []
        for entry in self._list.values():
            if entry.matches(entity):
                result.append(entry.to_ordered_dict())
        return result
