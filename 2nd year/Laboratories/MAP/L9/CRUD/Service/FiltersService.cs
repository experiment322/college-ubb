using System;
using System.Collections.Generic;
using System.Linq;
using CRUD.Domain;
using CRUD.Repository;

namespace CRUD.Service
{
    public class FiltersService
    {
        private readonly ICrudRepository<int, Task> _taskRepository;
        private readonly ICrudRepository<int, Student> _studentRepository;
        private readonly ICrudRepository<string, Mark> _markRepository;

        public FiltersService(
            ICrudRepository<int, Task> taskRepository,
            ICrudRepository<int, Student> studentRepository,
            ICrudRepository<string, Mark> markRepository)
        {
            _taskRepository = taskRepository;
            _studentRepository = studentRepository;
            _markRepository = markRepository;
        }

        public IEnumerable<Mark> FilterMarksByTask(string taskId)
        {
            var task = _taskRepository.FindOne(Convert.ToInt32(taskId));
            if (task == null)
            {
                throw new KeyNotFoundException(nameof(taskId));
            }

            return from mark in _markRepository.FindAll()
                where mark.TaskId == task.Id
                select mark;
        }

        public IEnumerable<Mark> FilterMarksByStudent(string studentId)
        {
            var student = _studentRepository.FindOne(Convert.ToInt32(studentId));
            if (student == null)
            {
                throw new KeyNotFoundException(nameof(studentId));
            }

            return from mark in _markRepository.FindAll()
                where mark.StudentId == student.Id
                select mark;
        }

        public IEnumerable<Mark> FilterMarksByPeriod(string startWeek, string endWeek)
        {
            return from mark in _markRepository.FindAll()
                where Convert.ToInt32(startWeek) <= mark.Week && mark.Week <= Convert.ToInt32(endWeek)
                select mark;
        }

        public IEnumerable<Mark> FilterMarksByTaskAndStudentGroup(string taskId, string studentGroup)
        {
            return from mark in _markRepository.FindAll()
                join student in _studentRepository.FindAll() on mark.StudentId equals student.Id
                where mark.TaskId == Convert.ToInt32(taskId) && student.Group == Convert.ToInt32(studentGroup)
                select mark;
        }
    }
}