using System;
using System.Collections.Generic;
using CRUD.Domain;
using CRUD.Service;
using CRUD.Utils;

namespace CRUD.UI.Tui
{
    public class TaskTui : BaseTui
    {
        private readonly TaskService _service;

        public TaskTui(TaskService service)
        {
            _service = service;
            Initialize("Task TUI", new Dictionary<string, Action>
            {
                {"Create task", CreateTask},
                {"Update task", UpdateTask},
                {"Delete task", DeleteTask},
                {"Read one task", ReadOneTask},
                {"Read all tasks", ReadAllTasks},
                {"Extend task deadline", ExtendTaskDeadline}
            });
        }

        private void CreateTask()
        {
            var task = Read("Id", "AssignmentWeek", "DeadlineWeek", "Description");
            Write(GenerateMessage(_service.CreateTask(task)));
        }

        private void UpdateTask()
        {
            var task = Read("Id", "AssignmentWeek", "DeadlineWeek", "Description");
            Write(GenerateMessage(_service.UpdateTask(task)));
        }

        private void DeleteTask()
        {
            var id = Read("Id");
            Write(GenerateMessage(_service.DeleteTask(id)));
        }

        private void ReadOneTask()
        {
            var id = Read("Id");
            var task = _service.ReadOneTask(id);
            Write(task == null
                ? "Task not found..."
                : EntityUtils.DumpString<Task, int>(task));
        }

        private void ReadAllTasks()
        {
            foreach (var task in _service.ReadAllTasks())
            {
                Write(EntityUtils.DumpString<Task, int>(task));
            }
        }

        private void ExtendTaskDeadline()
        {
            var id = Read("Id");
            var newDeadlineWeek = Read("NewDeadlineWeek");
            Write(GenerateMessage(_service.ExtendTaskDeadline(id, newDeadlineWeek)));
        }
    }
}