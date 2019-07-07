from ui.loop import loop_ui
from util.printing import print_table


def run(subject_controller):
    loop_ui("[ ULTIMATE SUBJECT MANAGER ]", {
        "add":
            lambda dto: subject_controller.add_subject(dto),
        "del":
            lambda dto: subject_controller.del_subject(dto),
        "mod":
            lambda dto: subject_controller.mod_subject(dto),
        "getAll":
            lambda: print_table(subject_controller.get_all()),
        "getByName":
            lambda dto: print_table(subject_controller.get_subject_by_name(dto)),
        "getByTeacher":
            lambda dto: print_table(subject_controller.get_subject_by_teacher(dto))
    })
