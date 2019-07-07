import json
from collections import OrderedDict
from domain.entity import Entity
from repository.entity_file_repository import EntityFileRepository


class RelationFileRepository(EntityFileRepository):
    def __init__(self, left_repository, right_repository, file_name, entity_class):
        super().__init__(file_name, entity_class)
        self._left_repository = left_repository
        self._right_repository = right_repository
        self.set_add_negotiator(lambda entity: self.relation_entities_exist(entity))
        self.set_mod_negotiator(lambda entity: self.relation_entities_exist(entity))
        left_repository.set_del_negotiator(lambda entity: self.entity_not_in_relation(entity))
        right_repository.set_del_negotiator(lambda entity: self.entity_not_in_relation(entity))

    def relation_entities_exist(self, entity):
        left, right = entity.get_relation()
        if len(self._left_repository.get_entity(Entity(left))) == 0:
            return False
        if len(self._right_repository.get_entity(Entity(right))) == 0:
            return False
        return True

    def entity_not_in_relation(self, entity):
        tag = entity.get_tag()
        with open(self._file_name, "r") as repo_file:
            repo_file.readline()
            for entry_json in repo_file:
                entry_dict = json.loads(entry_json, object_pairs_hook=OrderedDict)
                entry = self._entity_class(*entry_dict.values())
                left, right = entry.get_relation()
                if left == tag or right == tag:
                    return False
        return True
