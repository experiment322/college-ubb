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

    def entity_not_in_relation(self, entity, entity_list=None):
        if entity_list is None:
            entity_list = list(self._list.values())
        entity_list_len = len(entity_list)
        if entity_list_len == 0:
            return True
        if entity_list_len == 1:
            tag = entity.get_tag()
            entry, = entity_list
            left, right = entry.get_relation()
            if left == tag or right == tag:
                return False
            return True
        return \
            self.entity_not_in_relation(entity, entity_list[:entity_list_len // 2]) and \
            self.entity_not_in_relation(entity, entity_list[entity_list_len // 2:])
        # =================================================================== #
        # tag = entity.get_tag()
        # for entry in self._list.values():
        #     left, right = entry.get_relation()
        #     if left == tag or right == tag:
        #         return False
        # return True
        # =================================================================== #
