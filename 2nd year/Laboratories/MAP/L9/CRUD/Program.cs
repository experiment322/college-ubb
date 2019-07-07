using System.Collections.Generic;
using CRUD.Domain;
using CRUD.Domain.Validator;
using CRUD.Repository;
using CRUD.Service;
using CRUD.UI.Tui;
using CRUD.Utils;

namespace CRUD
{
    internal static class Program
    {
        public static void Main()
        {
            var weekUtils = new WeekUtils("ro-RO", '-', new[]
            {
                "01.10.2018 - 21.12.2018",
                "07.01.2019 - 20.01.2019"
            });
            var taskRepository = new OnDiskTextRepository<int, Task>(
                new TaskValidator(),
                new Dictionary<int, Task>(),
                "tasks.txt");
            var studentRepository = new OnDiskTextRepository<int, Student>(
                new StudentValidator(),
                new Dictionary<int, Student>(),
                "students.txt");
            var markRepository = new OnDiskTextRepository<string, Mark>(
                new MarkValidator(),
                new Dictionary<string, Mark>(),
                "marks.txt");
            var ui = new MainTui(
                new TaskService(weekUtils, taskRepository),
                new StudentService(weekUtils, studentRepository),
                new MarkService(weekUtils, markRepository, taskRepository, studentRepository),
                new ReportsService(taskRepository, studentRepository, markRepository),
                new FiltersService(taskRepository, studentRepository, markRepository));
            ui.Run();
        }
    }
}