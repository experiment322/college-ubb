using System;
using System.Collections.Generic;
using CRUD.Domain;
using CRUD.Service;
using CRUD.Utils;

namespace CRUD.UI.Tui
{
    public class MarkTui : BaseTui
    {
        private readonly MarkService _service;

        public MarkTui(MarkService service)
        {
            _service = service;
            Initialize("Mark TUI", new Dictionary<string, Action>
            {
                {"Create mark", CreateMark},
                {"Read one mark", ReadOneMark},
                {"Read all marks", ReadAllMarks}
            });
        }

        private void CreateMark()
        {
            var mark = Read("TaskId", "StudentId", "Value", "Feedback", "Week");
            var didCreateMark = _service.CreateMark(mark);
            if (didCreateMark)
            {
                var maximumMarkValue = _service.GetMaximumMarkValue(mark);
                if (double.Parse(mark["Value"]) > maximumMarkValue)
                {
                    Write($"Mark value was set to {maximumMarkValue} because of the delay");
                }
            }

            Write(GenerateMessage(didCreateMark));
        }

        private void ReadOneMark()
        {
            var taskId = Read("TaskId");
            var studentId = Read("StudentId");
            var mark = _service.ReadOneMark(taskId, studentId);
            Write(mark == null
                ? "Mark not found..."
                : EntityUtils.DumpString<Mark, string>(mark));
        }

        private void ReadAllMarks()
        {
            foreach (var mark in _service.ReadAllMarks())
            {
                Write(EntityUtils.DumpString<Mark, string>(mark));
            }
        }
    }
}