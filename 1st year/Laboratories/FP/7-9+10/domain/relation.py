from domain.entity import Entity


class Relation(Entity):
    def __init__(self, tag, left, right):
        super().__init__(tag)
        self._left = left
        self._right = right

    def set_relation(self, left, right):
        self._left = left
        self._right = right

    def get_relation(self):
        return self._left, self._right

    def to_ordered_dict(self):
        result = super().to_ordered_dict()
        result["LEFT ID"] = self._left
        result["RIGHT ID"] = self._right
        return result

    def matches(self, target):
        target_left, target_right = target.try_get("get_relation", (None, None))
        if super().matches(target) \
                and self.fields_match(self._left, target_left) \
                and self.fields_match(self._right, target_right):
            return True
        return False
