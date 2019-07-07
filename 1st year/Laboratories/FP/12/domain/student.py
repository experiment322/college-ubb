from re import compile
from domain.entity import Entity


class Student(Entity):
    def __init__(self, tag, name):
        super().__init__(tag)
        self._name = name

    def set_name(self, name):
        self._name = name

    def get_name(self):
        return self._name

    def validate(self):
        name_template = compile("[A-Z][a-z]{1,15} [A-Z][a-z]{1,15}(?: [A-Z][a-z]{1,15})*")
        if not name_template.fullmatch(self._name):
            raise ValueError("Student name should be at least two capitalized words")

    def to_ordered_dict(self):
        result = super().to_ordered_dict()
        result["NAME"] = self._name
        return result

    def matches(self, target):
        target_name = target.try_get("get_name", None)
        if super().matches(target) \
                and self.fields_match(self._name, target_name):
            return True
        return False
