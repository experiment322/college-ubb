from collections import defaultdict
from domain.mark import Mark
from domain.student import Student
from util.sorting import sorted_custom


class StatisticController(object):
    def __init__(self, mark_repository, student_repository, subject_repository):
        self._mark_repository = mark_repository
        self._student_repository = student_repository
        self._subject_repository = subject_repository

    def get_students_marks_by_subject(self, dto, sort_method, sort_reverse):
        """
        Call validate() on dto, convert dto to Mark and
            return all students which have marks at this subject as ordered dicts.
        dto should contain "subj_id". Missing fields are initialised with None.
        sort_method is "avg" or "name", where "avg" sorts by marks average and "name" sorts by student name.
        sort_reverse instructs to sort in ascending order if False or in descending order if True.
        """
        dto.validate(["subj_id"])
        mark = Mark(None, None, *dto.split(), None)
        marks = self._mark_repository.get_entity(mark)
        students = self._student_repository.get_entity(Student(None, None))
        compact_marks = defaultdict(list)
        for mark in marks:
            compact_marks[mark["STUD ID"]].append(mark["MARK"])
        result = []
        for student in students:
            if student["ID"] in compact_marks:
                student_marks = compact_marks[student["ID"]]
                student_average = sum([int(mark) for mark in student_marks]) / len(student_marks)
                student["MARKS"] = ", ".join(student_marks)
                student["AVERAGE"] = format(student_average, ".2f")
                result.append(student)
        sort_methods = {
            "avg": lambda item: float(item["AVERAGE"]),
            "name": lambda item: item["NAME"]
        }
        # result = sorted(result, key=sort_methods[sort_method], reverse=sort_reverse)
        result = sorted_custom(result, "bubble", key=sort_methods[sort_method], reverse=sort_reverse)
        return result

    def get_top_students(self):
        """
        Get all marks, compute total average for every student which has marks by subject average and
            return the first 20% students(or 1 if 20% < 1) with highest averages as ordered dicts.
        """
        marks = self._mark_repository.get_entity(Mark(None, None, None, None))
        students = self._student_repository.get_entity(Student(None, None))
        compact_marks = defaultdict(lambda: defaultdict(list))
        for mark in marks:
            compact_marks[mark["STUD ID"]][mark["SUBJ ID"]].append(mark["MARK"])
        result = []
        for student in students:
            if student["ID"] in compact_marks:
                student_averages = []
                for subject in compact_marks[student["ID"]]:
                    subject_marks = compact_marks[student["ID"]][subject]
                    subject_average = sum([int(mark) for mark in subject_marks]) / len(subject_marks)
                    student_averages.append(subject_average)
                student_average = sum(student_averages) / len(student_averages)
                student["AVERAGE"] = format(student_average, ".2f")
                result.append(student)
        # result = sorted(result, key=lambda item: float(item["AVERAGE"]), reverse=True)
        result = sorted_custom(result, "shell", key=lambda item: float(item["AVERAGE"]), reverse=True)
        top_students_limit = 20 * len(students) // 100 or 1
        return result[:top_students_limit]
