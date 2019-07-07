import os
import json
from collections import OrderedDict


class EntityFileRepository(object):
    def __init__(self, file_name, entity_class):
        self._file_name = file_name
        self._entity_class = entity_class
        self._can_add = lambda entity: True
        self._can_del = lambda entity: True
        self._can_mod = lambda entity: True
        with open(file_name, "r") as repo_file:
            latest_tag = repo_file.readline()
            self._available_tag = int(latest_tag) if latest_tag else 0

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
        with open(self._file_name, "r") as repo_file, \
                open("temp", "w") as temp_file:
            entity_json = json.dumps(entity.to_ordered_dict())
            temp_file.write("{}\n".format(self._available_tag))
            temp_file.write("{}\n".format(entity_json))
            repo_file.readline()
            for repo_line in repo_file:
                temp_file.write(repo_line)
        os.remove(self._file_name)
        os.rename("temp", self._file_name)

    def del_entity(self, entity):
        if not self._can_del(entity):
            raise PermissionError("Cannot del entity")
        tag = entity.get_tag()
        found = False
        with open(self._file_name, "r") as repo_file, \
                open("temp", "w") as temp_file:
            temp_file.write(repo_file.readline())
            for repo_line in repo_file:
                entity_dict = json.loads(repo_line)
                if tag != entity_dict["ID"]:
                    temp_file.write(repo_line)
                else:
                    found = True
        os.remove(self._file_name)
        os.rename("temp", self._file_name)
        if not found:
            raise LookupError("Cannot del nonexistent entity")

    def mod_entity(self, entity):
        if not self._can_mod(entity):
            raise PermissionError("Cannot mod entity")
        tag = entity.get_tag()
        found = False
        with open(self._file_name, "r") as repo_file, \
                open("temp", "w") as temp_file:
            temp_file.write(repo_file.readline())
            for repo_line in repo_file:
                entity_dict = json.loads(repo_line)
                if tag != entity_dict["ID"]:
                    temp_file.write(repo_line)
                else:
                    entity_json = json.dumps(entity.to_ordered_dict())
                    temp_file.write("{}\n".format(entity_json))
                    found = True
        os.remove(self._file_name)
        os.rename("temp", self._file_name)
        if not found:
            raise LookupError("Cannot mod nonexistent entity")

    def get_entity(self, entity):
        result = []
        with open(self._file_name, "r") as repo_file:
            repo_file.readline()
            for entry_json in repo_file:
                entry_dict = json.loads(entry_json, object_pairs_hook=OrderedDict)
                entry = self._entity_class(*entry_dict.values())
                if entry.matches(entity):
                    result.append(entry.to_ordered_dict())
        return result
