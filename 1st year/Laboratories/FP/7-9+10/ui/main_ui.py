from ui import mark_ui, statistic_ui, student_ui, subject_ui
from ui.loop import loop_ui


def run(mark_controller, statistic_controller, student_controller, subject_controller):
    loop_ui("[ ULTIMATE CLASS BOOK ]", {
        "marks":
            lambda: mark_ui.run(mark_controller),
        "statistics":
            lambda: statistic_ui.run(statistic_controller),
        "students":
            lambda: student_ui.run(student_controller),
        "subjects":
            lambda: subject_ui.run(subject_controller)
    })
