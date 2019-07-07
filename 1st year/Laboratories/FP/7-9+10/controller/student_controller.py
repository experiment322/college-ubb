from domain.student import Student


class StudentController(object):
    def __init__(self, student_repository):
        self._student_repository = student_repository

    def add_student(self, dto):
        """
        Call validate on dto(), convert dto to Student, call validate() on it and add it to the repo.
        dto should contain "name". Missing fields are initialised with None.
        Validate and repo exceptions are raised.
        """
        dto.validate(["name"])
        student = Student(None, *dto.split())
        student.validate()
        self._student_repository.add_entity(student)

    def del_student(self, dto):
        """
        Call validate on dto(), convert dto to Student and delete it from the repo.
        dto should contain "id". Missing fields are initialised with None.
        Repo exceptions are raised.
        """
        dto.validate(["id"])
        student = Student(*dto.split(), None)
        self._student_repository.del_entity(student)

    def mod_student(self, dto):
        """
        Call validate on dto(), convert dto to Student, call validate() on it replace it in the repo.
        dto should contain "id,name". Missing fields are initialised with None.
        Validate and repo exceptions are raised.
        """
        dto.validate(["id", "name"])
        student = Student(*dto.split())
        Student.validate(student)
        self._student_repository.mod_entity(student)

    def get_all(self):
        """
        Return a list of all students as ordered dicts.
        """
        return self._student_repository.get_entity(Student(None, None))

    def get_student_by_name(self, dto):
        """
        Call validate on dto(), convert dto to Student and return a list of matching students as ordered dicts.
        dto should contain "name". Missing fields are initialised with None.
        """
        dto.validate(["name"])
        student = Student(None, *dto.split())
        return self._student_repository.get_entity(student)
