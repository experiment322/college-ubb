import domain.Mark;
import domain.Student;
import domain.Task;
import domain.validator.MarkValidator;
import domain.validator.StudentValidator;
import domain.validator.TaskValidator;
import repository.CrudRepository;
import repository.OnDiskXMLRepository;
import service.MarkService;
import service.StudentService;
import service.TaskService;
import ui.UI;
import ui.gui.MainGUI;
import utils.EntityUtils;
import utils.WeekUtils;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        WeekUtils weekUtils = new WeekUtils("dd.MM.yyyy", "-", Arrays.asList(
                "01.10.2018 - 21.12.2018",
                "07.01.2019 - 20.01.2019",
                "25.02.2019 - 28.04.2019",
                "06.05.2019 - 09.06.2019"
        ));
        CrudRepository<String, Mark> markRepository = new OnDiskXMLRepository<>(
                new MarkValidator(),
                "marks.xml",
                EntityUtils::dumpXML,
                element -> EntityUtils.fromXML(new Mark(), element)
        );
        CrudRepository<Integer, Task> taskRepository = new OnDiskXMLRepository<>(
                new TaskValidator(),
                "tasks.xml",
                EntityUtils::dumpXML,
                element -> EntityUtils.fromXML(new Task(), element)
        );
        CrudRepository<Integer, Student> studentRepository = new OnDiskXMLRepository<>(
                new StudentValidator(),
                "students.xml",
                EntityUtils::dumpXML,
                element -> EntityUtils.fromXML(new Student(), element)
        );
        UI mainUI = MainGUI.getInstance(
                new MarkService(weekUtils, markRepository, taskRepository, studentRepository),
                new TaskService(weekUtils, taskRepository),
                new StudentService(weekUtils, studentRepository)
        );
        mainUI.run();
    }
}
