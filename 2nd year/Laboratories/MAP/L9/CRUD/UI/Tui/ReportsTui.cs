using System;
using System.Collections.Generic;
using System.Linq;
using CRUD.Service;

namespace CRUD.UI.Tui
{
    public class ReportsTui : BaseTui
    {
        private readonly ReportsService _service;

        public ReportsTui(ReportsService service)
        {
            _service = service;
            Initialize("Reports TUI", new Dictionary<string, Action>
            {
                {"Student averages", ReportStudentAverages},
                {"Punctual students", ReportPunctualStudents},
                {"Most difficult task", ReportTheMostDifficultTask},
                {"Students qualified for exam", ReportStudentsQualifiedForExam}
            });
        }

        private void ReportStudentAverages()
        {
            var studentAverages = _service.ReportStudentAverages();
            if (!studentAverages.Any())
            {
                Write("There are no students with marks...");
                return;
            }

            Write(string.Join("\t", "AVG", "ID", "NAME"));
            foreach (var studentAverage in studentAverages)
            {
                var student = studentAverage.Key;
                Write(string.Join("\t", Math.Round(studentAverage.Value, 2), student.Id, student.Name));
            }
        }

        private void ReportPunctualStudents()
        {
            var punctualStudents = _service.ReportPunctualStudents().ToList();
            if (!punctualStudents.Any())
            {
                Write("There are no punctual students...");
                return;
            }

            Write(string.Join("\t", "ID", "NAME"));
            foreach (var student in punctualStudents)
            {
                Write(string.Join("\t", student.Id, student.Name));
            }
        }

        private void ReportTheMostDifficultTask()
        {
            var task = _service.ReportTheMostDifficultTask();
            Write(string.Join("\t", "ID", "DESC"));
            Write(string.Join("\t", task.Id, task.Description));
        }

        private void ReportStudentsQualifiedForExam()
        {
            var qualifiedStudents = _service.ReportStudentsQualifiedForExam().ToList();
            if (!qualifiedStudents.Any())
            {
                Write("There are no students qualified for the exam...");
                return;
            }

            Write(string.Join("\t", "ID", "NAME"));
            foreach (var student in _service.ReportStudentsQualifiedForExam())
            {
                Write(string.Join("\t", student.Id, student.Name));
            }
        }
    }
}