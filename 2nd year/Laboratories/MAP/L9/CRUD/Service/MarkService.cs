using System;
using System.Collections.Generic;
using System.Linq;
using CRUD.Domain;
using CRUD.Repository;
using CRUD.Utils;

namespace CRUD.Service
{
    public class MarkService
    {
        private readonly WeekUtils _weekUtils;
        private readonly ICrudRepository<string, Mark> _repository;
        private readonly ICrudRepository<int, Task> _taskRepository;
        private readonly ICrudRepository<int, Student> _studentRepository;

        public MarkService(
            WeekUtils weekUtils,
            ICrudRepository<string, Mark> repository,
            ICrudRepository<int, Task> taskRepository,
            ICrudRepository<int, Student> studentRepository)
        {
            _weekUtils = weekUtils;
            _repository = repository;
            _taskRepository = taskRepository;
            _studentRepository = studentRepository;
        }

        private void FillMarkDefaults(IDictionary<string, string> dictionary)
        {
            dictionary.TryGetValue("Feedback", out var feedback);
            if (string.IsNullOrEmpty(feedback))
            {
                dictionary["Feedback"] = "NO FEEDBACK";
            }

            dictionary.TryGetValue("Week", out var week);
            if (string.IsNullOrEmpty(week))
            {
                dictionary["Week"] = _weekUtils.GetCurrentDidacticWeek().ToString();
            }
        }

        private Mark FromDictionary(IDictionary<string, string> dictionary)
        {
            FillMarkDefaults(dictionary);
            return new Mark
            {
                TaskId = Convert.ToInt32(dictionary["TaskId"]),
                StudentId = Convert.ToInt32(dictionary["StudentId"]),
                Week = Convert.ToInt32(dictionary["Week"]),
                Value = Convert.ToDouble(dictionary["Value"]),
                Feedback = dictionary["Feedback"]
            };
        }

        private void AssertMark(Mark mark)
        {
            var task = _taskRepository.FindOne(mark.TaskId);
            var student = _studentRepository.FindOne(mark.StudentId);

            if (task == null || student == null)
            {
                throw new NullReferenceException(task == null
                    ? nameof(mark.TaskId) + ' ' + mark.TaskId
                    : nameof(mark.StudentId) + ' ' + mark.StudentId);
            }

            if (mark.Week < task.DeadlineWeek)
            {
                throw new ArgumentOutOfRangeException(nameof(mark.Week) + " < " + nameof(task.DeadlineWeek));
            }

            if ((student.Absences & (1 << (mark.Week - 1))) != 0 &&
                (student.JustifiedAbsences & (1 << (mark.Week - 1))) == 0)
            {
                throw new InvalidOperationException("Student absent in week " + mark.Week);
            }
        }

        private int ComputeAssignmentDelay(Mark mark)
        {
            AssertMark(mark);
            var task = _taskRepository.FindOne(mark.TaskId);
            var student = _studentRepository.FindOne(mark.StudentId);

            if (mark.Week == task.DeadlineWeek)
            {
                return 0;
            }

            var justifiedAbsenceCount = Enumerable
                .Range(task.DeadlineWeek, mark.Week - task.DeadlineWeek)
                .Count(week => (student.JustifiedAbsences & (1 << (week - 1))) != 0);

            return mark.Week - (task.DeadlineWeek + justifiedAbsenceCount);
        }

        public double GetMaximumMarkValue(IDictionary<string, string> dictionary)
        {
            var mark = FromDictionary(dictionary);
            var assignmentDelay = ComputeAssignmentDelay(mark);
            if (assignmentDelay > 2)
            {
                throw new InvalidOperationException("Assignment is due");
            }

            return 10.0 - assignmentDelay * 2.5;
        }

        public bool CreateMark(IDictionary<string, string> dictionary)
        {
            var mark = FromDictionary(dictionary);
            mark.Value = Math.Min(mark.Value, GetMaximumMarkValue(dictionary));

            return _repository.Save(mark) == null;
        }

        public Mark ReadOneMark(string taskId, string studentId)
        {
            var id = string.Join(Mark.IdSeparator.ToString(), Convert.ToInt32(taskId), Convert.ToInt32(studentId));
            return _repository.FindOne(id);
        }

        public IEnumerable<Mark> ReadAllMarks()
        {
            return _repository.FindAll();
        }
    }
}