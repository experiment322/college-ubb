from re import compile
from domain.entity import Entity


class Subject(Entity):
    def __init__(self, tag, name, teacher):
        super().__init__(tag)
        self._name = name
        self._teacher = teacher

    def set_name(self, name):
        self._name = name

    def get_name(self):
        return self._name

    def set_teacher(self, teacher):
        self._teacher = teacher

    def get_teacher(self):
        return self._teacher

    def validate(self):
        name_template = compile("[A-Z][a-z]{1,15}(?: [A-Z][a-z]{1,15})*")
        if not name_template.fullmatch(self._name):
            raise ValueError("Subject name should be at least one capitalized word")

        teacher_template = compile("[A-Z][a-z]{1,15} [A-Z][a-z]{1,15}(?: [A-Z][a-z]{1,15})*")
        if not teacher_template.fullmatch(self._teacher):
            raise ValueError("Subject teacher name should be at least two capitalized words")

    def to_ordered_dict(self):
        result = super().to_ordered_dict()
        result["NAME"] = self._name
        result["TEACHER"] = self._teacher
        return result

    def matches(self, target):
        target_name = target.try_get("get_name", None)
        target_teacher = target.try_get("get_teacher", None)
        if super().matches(target) \
                and self.fields_match(self._name, target_name) \
                and self.fields_match(self._teacher, target_teacher):
            return True
        return False
