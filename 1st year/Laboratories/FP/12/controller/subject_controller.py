from domain.subject import Subject


class SubjectController(object):
    def __init__(self, subject_repository):
        self._subject_repository = subject_repository

    def add_subject(self, dto):
        """
        Call validate on dto(), convert dto to Subject, call validate() on it and add it to the repo.
        dto should contain "name,teacher_name". Missing fields are initialised with None.
        Validate and repo exceptions are raised.
        """
        dto.validate(["name", "teacher_name"])
        subject = Subject(None, *dto.split())
        subject.validate()
        self._subject_repository.add_entity(subject)

    def del_subject(self, dto):
        """
        Call validate on dto(), convert dto to Subject and delete it from the repo.
        dto should contain "id". Missing fields are initialised with None.
        Repo exceptions are raised.
        """
        dto.validate(["id"])
        subject = Subject(*dto.split(), None, None)
        self._subject_repository.del_entity(subject)

    def mod_subject(self, dto):
        """
        Call validate on dto(), convert dto to Subject, call validate() on it replace it in the repo.
        dto should contain "id,name,teacher_name". Missing fields are initialised with None.
        Validate and repo exceptions are raised.
        """
        dto.validate(["id", "name", "teacher_name"])
        subject = Subject(*dto.split())
        subject.validate()
        self._subject_repository.mod_entity(subject)

    def get_all(self):
        """
        Return a list of all subjects as ordered dicts.
        """
        return self._subject_repository.get_entity(Subject(None, None, None))

    def get_subject_by_name(self, dto):
        """
        Call validate on dto(), convert dto to Subject and return a list of matching subjects as ordered dicts.
        dto should contain "name". Missing fields are initialised with None.
        """
        dto.validate(["name"])
        subject = Subject(None, *dto.split(), None)
        return self._subject_repository.get_entity(subject)

    def get_subject_by_teacher(self, dto):
        """
        Call validate on dto(), convert dto to Subject and return a list of matching subjects as ordered dicts.
        dto should contain "teacher_name". Missing fields are initialised with None.
        """
        dto.validate(["teacher_name"])
        subject = Subject(None, None, *dto.split())
        return self._subject_repository.get_entity(subject)
