from ui.loop import loop_ui
from util.printing import print_table


def run(student_controller):
    loop_ui("[ ULTIMATE STUDENT MANAGER ]", {
        "add":
            lambda dto: student_controller.add_student(dto),
        "del":
            lambda dto: student_controller.del_student(dto),
        "mod":
            lambda dto: student_controller.mod_student(dto),
        "getAll":
            lambda: print_table(student_controller.get_all()),
        "getByName":
            lambda dto: print_table(student_controller.get_student_by_name(dto))
    })
