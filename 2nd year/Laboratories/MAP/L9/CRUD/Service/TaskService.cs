using System;
using System.Collections.Generic;
using CRUD.Domain;
using CRUD.Repository;
using CRUD.Utils;

namespace CRUD.Service
{
    public class TaskService
    {
        private readonly WeekUtils _weekUtils;
        private readonly ICrudRepository<int, Task> _repository;

        public TaskService(WeekUtils weekUtils, ICrudRepository<int, Task> repository)
        {
            _weekUtils = weekUtils;
            _repository = repository;
        }

        private void FillTaskDefaults(IDictionary<string, string> dictionary)
        {
            dictionary.TryGetValue("AssignmentWeek", out var assignmentWeek);
            if (string.IsNullOrEmpty(assignmentWeek))
            {
                dictionary["AssignmentWeek"] = _weekUtils.GetCurrentDidacticWeek().ToString();
            }
        }

        private Task FromDictionary(IDictionary<string, string> dictionary)
        {
            FillTaskDefaults(dictionary);
            return new Task
            {
                Id = Convert.ToInt32(dictionary["Id"]),
                Description = dictionary["Description"],
                AssignmentWeek = Convert.ToInt32(dictionary["AssignmentWeek"]),
                DeadlineWeek = Convert.ToInt32(dictionary["DeadlineWeek"])
            };
        }

        public bool CreateTask(IDictionary<string, string> dictionary)
        {
            return _repository.Save(FromDictionary(dictionary)) == null;
        }

        public bool UpdateTask(IDictionary<string, string> dictionary)
        {
            return _repository.Update(FromDictionary(dictionary)) == null;
        }

        public bool DeleteTask(string id)
        {
            return _repository.Delete(Convert.ToInt32(id)) != null;
        }

        public Task ReadOneTask(string id)
        {
            return _repository.FindOne(Convert.ToInt32(id));
        }

        public IEnumerable<Task> ReadAllTasks()
        {
            return _repository.FindAll();
        }

        public bool ExtendTaskDeadline(string id, string newDeadlineWeek)
        {
            var task = _repository.FindOne(Convert.ToInt32(id));
            if (task == null)
            {
                throw new KeyNotFoundException(nameof(id) + ' ' + id);
            }

            if (task.DeadlineWeek < _weekUtils.GetCurrentDidacticWeek())
            {
                throw new InvalidOperationException("Task is finished");
            }

            if (Convert.ToInt32(newDeadlineWeek) < _weekUtils.GetCurrentDidacticWeek())
            {
                throw new InvalidOperationException("New deadline is before current week");
            }

            var updatedTask = EntityUtils.Clone<Task, int>(task);
            updatedTask.DeadlineWeek = Convert.ToInt32(newDeadlineWeek);
            return _repository.Update(updatedTask) == null;
        }
    }
}