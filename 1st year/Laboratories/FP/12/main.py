from repository.entity_dict_repository import EntityDictRepository
from repository.relation_dict_repository import RelationDictRepository
# from repository.entity_file_repository import EntityFileRepository
# from repository.relation_file_repository import RelationFileRepository
# from domain.mark import Mark
# from domain.student import Student
# from domain.subject import Subject
from controller.mark_controller import MarkController
from controller.statistic_controller import StatisticController
from controller.student_controller import StudentController
from controller.subject_controller import SubjectController
from ui import main_ui


def main():
    # Repositories
    student_repository = EntityDictRepository()
    subject_repository = EntityDictRepository()
    mark_repository = RelationDictRepository(student_repository, subject_repository)
    # student_repository = EntityFileRepository("students.txt", Student)
    # subject_repository = EntityFileRepository("subjects.txt", Subject)
    # mark_repository = RelationFileRepository(student_repository, subject_repository, "marks.txt", Mark)
    # Controllers
    mark_controller = MarkController(mark_repository)
    student_controller = StudentController(student_repository)
    subject_controller = SubjectController(subject_repository)
    statistic_controller = StatisticController(mark_repository, student_repository, subject_repository)
    # Start UI
    main_ui.run(mark_controller, statistic_controller, student_controller, subject_controller)


if __name__ == "__main__":
    main()
