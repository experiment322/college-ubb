using System;
using System.Collections.Generic;
using System.Linq;
using CRUD.Domain;
using CRUD.Service;

namespace CRUD.UI.Tui
{
    public class FiltersTui : BaseTui
    {
        private readonly FiltersService _service;

        public FiltersTui(FiltersService service)
        {
            _service = service;
            Initialize("Filters TUI", new Dictionary<string, Action>
            {
                {"Filter marks by task", FilterMarksByTask},
                {"Filter marks by student", FilterMarksByStudent},
                {"Filter marks by period", FilterMarksByPeriod},
                {"Filter marks by task and student group", FilterMarksByTaskAndStudentGroup}
            });
        }

        private static void WriteMarks(IEnumerable<Mark> marks)
        {
            Write(string.Join("\t", "ID", "VAL", "DESC"));
            foreach (var mark in marks)
            {
                Write(string.Join("\t", mark.Id, mark.Value, mark.Feedback));
            }
        }

        private void FilterMarksByTask()
        {
            var marks = _service.FilterMarksByTask(Read("TaskId")).ToList();
            if (!marks.Any())
            {
                Write("There are no marks for the selected task...");
                return;
            }

            WriteMarks(marks);
        }

        private void FilterMarksByStudent()
        {
            var marks = _service.FilterMarksByStudent(Read("StudentId")).ToList();
            if (!marks.Any())
            {
                Write("There are no marks for the selected student...");
                return;
            }

            WriteMarks(marks);
        }

        private void FilterMarksByPeriod()
        {
            var marks = _service.FilterMarksByPeriod(Read("StartWeek"), Read("EndWeek")).ToList();
            if (!marks.Any())
            {
                Write("There are no marks for the selected period...");
                return;
            }

            WriteMarks(marks);
        }

        private void FilterMarksByTaskAndStudentGroup()
        {
            var marks = _service.FilterMarksByTaskAndStudentGroup(Read("TaskId"), Read("StudentGroup")).ToList();
            if (!marks.Any())
            {
                Write("There are no marks for the selected task and student group...");
                return;
            }

            WriteMarks(marks);
        }
    }
}