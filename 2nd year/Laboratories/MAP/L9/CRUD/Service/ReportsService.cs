using System.Collections.Generic;
using System.Linq;
using CRUD.Domain;
using CRUD.Repository;
using static CRUD.Utils.WeekUtils;

namespace CRUD.Service
{
    public class ReportsService
    {
        private readonly ICrudRepository<int, Task> _taskRepository;
        private readonly ICrudRepository<int, Student> _studentRepository;
        private readonly ICrudRepository<string, Mark> _markRepository;

        public ReportsService(
            ICrudRepository<int, Task> taskRepository,
            ICrudRepository<int, Student> studentRepository,
            ICrudRepository<string, Mark> markRepository)
        {
            _taskRepository = taskRepository;
            _studentRepository = studentRepository;
            _markRepository = markRepository;
        }

        public IDictionary<Student, double> ReportStudentAverages()
        {
            return (from student in _studentRepository.FindAll()
                join mark in _markRepository.FindAll() on student.Id equals mark.StudentId
                join task in _taskRepository.FindAll() on mark.TaskId equals task.Id
                group new {mark, task} by student
                into studentMarks
                select new
                {
                    Student = studentMarks.Key,
                    Average = studentMarks.Select(markTaskCombo =>
                    {
                        var weight = markTaskCombo.task.DeadlineWeek - markTaskCombo.task.AssignmentWeek;
                        return markTaskCombo.mark.Value * weight;
                    }).Sum() / (SemesterWeekSpan - 1)
                }).ToDictionary(entry => entry.Student, entry => entry.Average);
        }

        public IEnumerable<Student> ReportPunctualStudents()
        {
            return from student in _studentRepository.FindAll()
                join mark in _markRepository.FindAll() on student.Id equals mark.StudentId
                join task in _taskRepository.FindAll() on mark.TaskId equals task.Id
                group new {mark, task} by student
                into studentMarks
                where studentMarks.All(markTaskCombo => markTaskCombo.mark.Week == markTaskCombo.task.DeadlineWeek)
                select studentMarks.Key;
        }

        public Task ReportTheMostDifficultTask()
        {
            return (from task in _taskRepository.FindAll()
                join mark in _markRepository.FindAll() on task.Id equals mark.TaskId
                group mark by task
                into marks
                orderby marks.Average(mark => mark.Value)
                select marks).First().Key;
        }

        public IEnumerable<Student> ReportStudentsQualifiedForExam()
        {
            var studentAverages = ReportStudentAverages();
            return from studentAverage in studentAverages
                where studentAverage.Value >= 4
                select studentAverage.Key;
        }
    }
}