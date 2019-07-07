from re import compile
from domain.relation import Relation


class Mark(Relation):
    def __init__(self, tag, student_tag, subject_tag, value):
        super().__init__(tag, student_tag, subject_tag)
        self._value = value

    def set_value(self, value):
        self._value = value

    def get_value(self):
        return self._value

    def validate(self):
        value_template = compile("10|[1-9]")
        if not value_template.fullmatch(self._value):
            raise ValueError("Mark value should be a number from 1 to 10")

    def to_ordered_dict(self):
        result = super().to_ordered_dict()
        result["STUD ID"] = result.pop("LEFT ID")
        result["SUBJ ID"] = result.pop("RIGHT ID")
        result["MARK"] = self._value
        return result

    def matches(self, target):
        target_value = target.try_get("get_value", None)
        if super().matches(target) \
                and self.fields_match(self._value, target_value):
            return True
        return False
