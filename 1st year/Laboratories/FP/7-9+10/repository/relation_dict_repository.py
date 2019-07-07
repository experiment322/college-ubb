from domain.entity import Entity
from repository.entity_dict_repository import EntityDictRepository


class RelationDictRepository(EntityDictRepository):
    def __init__(self, left_repository, right_repository):
        super().__init__()
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
        for entry in self._list.values():
            left, right = entry.get_relation()
            if left == tag or right == tag:
                return False
        return True
