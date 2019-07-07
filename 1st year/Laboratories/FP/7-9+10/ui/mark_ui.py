from ui.loop import loop_ui
from util.printing import print_table


def run(mark_controller):
    loop_ui("[ ULTIMATE MARK MANAGER ]", {
        "add":
            lambda dto: mark_controller.add_mark(dto),
        "del":
            lambda dto: mark_controller.del_mark(dto),
        "mod":
            lambda dto: mark_controller.mod_mark(dto),
        "getAll":
            lambda: print_table(mark_controller.get_all()),
        "getByValue":
            lambda dto: print_table(mark_controller.get_mark_by_value(dto)),
        "getByRelation":
            lambda dto: print_table(mark_controller.get_mark_by_relation(dto))
    })
