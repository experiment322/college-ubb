using System;
using System.Collections.Generic;
using CRUD.Service;

namespace CRUD.UI.Tui
{
    public class MainTui : BaseTui
    {
        public MainTui(
            TaskService taskService,
            StudentService studentService,
            MarkService markService,
            ReportsService reportsService,
            FiltersService filtersService)
        {
            var taskTui = new TaskTui(taskService);
            var studentTui = new StudentTui(studentService);
            var markTui = new MarkTui(markService);
            var reportsTui = new ReportsTui(reportsService);
            var filtersTui = new FiltersTui(filtersService);
            Initialize("Main TUI", new Dictionary<string, Action>
            {
                {"Tasks", taskTui.Run},
                {"Students", studentTui.Run},
                {"Marks", markTui.Run},
                {"Reports", reportsTui.Run},
                {"Filters", filtersTui.Run}
            });
        }
    }
}