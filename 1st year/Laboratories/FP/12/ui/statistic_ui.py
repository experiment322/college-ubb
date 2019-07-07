from ui.loop import loop_ui
from util.printing import print_table


def run(statistic_controller):
    loop_ui("[ ULTIMATE CLASS BOOK STATISTICS ]", {
        "getStudsMarksBySubjSortAvg":
            lambda dto: print_table(statistic_controller.get_students_marks_by_subject(dto, "avg", True)),
        "getStudsMarksBySubjSortName":
            lambda dto: print_table(statistic_controller.get_students_marks_by_subject(dto, "name", False)),
        "getTopStuds":
            lambda: print_table(statistic_controller.get_top_students())
    })
