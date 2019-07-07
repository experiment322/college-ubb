from domain.mark import Mark


class MarkController(object):
    def __init__(self, mark_repository):
        self._mark_repository = mark_repository

    def add_mark(self, dto):
        """
        Call validate on dto(), convert dto to Mark, call validate() on it and add it to the repo.
        dto should contain "stud_id,subj_id,mark". Missing fields are initialised with None.
        Validate and repo exceptions are raised.
        """
        dto.validate(["stud_id", "subj_id", "mark"])
        mark = Mark(None, *dto.split())
        mark.validate()
        self._mark_repository.add_entity(mark)

    def del_mark(self, dto):
        """
        Call validate on dto(), convert dto to Mark and delete it from the repo.
        dto should contain "id". Missing fields are initialised with None.
        Repo exceptions are raised.
        """
        dto.validate(["id"])
        mark = Mark(*dto.split(), None, None, None)
        self._mark_repository.del_entity(mark)

    def mod_mark(self, dto):
        """
        Call validate on dto(), convert dto to Mark, call validate() on it replace it in the repo.
        dto should contain "id,stud_id,subj_id,mark". Missing fields are initialised with None.
        Validate and repo exceptions are raised.
        """
        dto.validate(["id", "stud_id", "subj_id", "mark"])
        mark = Mark(*dto.split())
        mark.validate()
        self._mark_repository.mod_entity(mark)

    def get_all(self):
        """
        Return a list of all marks as ordered dicts.
        """
        return self._mark_repository.get_entity(Mark(None, None, None, None))

    def get_mark_by_value(self, dto):
        """
        Call validate on dto(), convert dto to Mark and return a list of matching marks as ordered dicts.
        dto should contain "mark". Missing fields are initialised with None.
        """
        dto.validate(["mark"])
        mark = Mark(None, None, None, *dto.split())
        return self._mark_repository.get_entity(mark)

    def get_mark_by_relation(self, dto):
        """
        Call validate on dto(), convert dto to Mark and return a list of matching marks as ordered dicts.
        dto should contain "stud_id,subj_id". Missing fields are initialised with None.
        """
        dto.validate(["stud_id", "subj_id"])
        mark = Mark(None, *dto.split(), None)
        return self._mark_repository.get_entity(mark)
