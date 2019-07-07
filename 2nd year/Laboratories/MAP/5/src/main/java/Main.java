import domain.validator.HomeworkValidator;
import domain.validator.StudentValidator;
import repository.HomeworkFileRepository;
import repository.StudentFileRepository;
import service.HomeworkService;
import service.StudentService;
import ui.UI;
import ui.tui.MainTUI;

public class Main {
    public static void main(String[] args) {
        StudentFileRepository studentFileRepository = new StudentFileRepository(new StudentValidator());
        HomeworkFileRepository homeworkFileRepository = new HomeworkFileRepository(new HomeworkValidator());
        UI mainUI = new MainTUI(new StudentService(studentFileRepository), new HomeworkService(homeworkFileRepository));
        mainUI.run();
    }
}
