using System;
using System.Collections.Generic;
using CRUD.Domain;
using CRUD.Service;
using CRUD.Utils;

namespace CRUD.UI.Tui
{
    public class StudentTui : BaseTui
    {
        private readonly StudentService _service;

        public StudentTui(StudentService service)
        {
            _service = service;
            Initialize("Student TUI", new Dictionary<string, Action>
            {
                {"Create student", CreateStudent},
                {"Update student", UpdateStudent},
                {"Delete student", DeleteStudent},
                {"Read one student", ReadOneStudent},
                {"Read all students", ReadAllStudents},
                {"Mark student absent", MarkStudentAbsent},
                {"Justify student absence", JustifyStudentAbsence}
            });
        }

        private void CreateStudent()
        {
            var student = Read("Id", "Group", "Name", "Email", "TeacherName");
            Write(GenerateMessage(_service.CreateStudent(student)));
        }

        private void UpdateStudent()
        {
            var student = Read("Id", "Group", "Name", "Email", "TeacherName");
            Write(GenerateMessage(_service.UpdateStudent(student)));
        }

        private void DeleteStudent()
        {
            var id = Read("Id");
            Write(GenerateMessage(_service.DeleteStudent(id)));
        }

        private void ReadOneStudent()
        {
            var id = Read("Id");
            var student = _service.ReadOneStudent(id);
            Write(student == null
                ? "Student not found..."
                : EntityUtils.DumpString<Student, int>(student));
        }

        private void ReadAllStudents()
        {
            foreach (var student in _service.ReadAllStudents())
            {
                Write(EntityUtils.DumpString<Student, int>(student));
            }
        }

        private void MarkStudentAbsent()
        {
            var id = Read("Id");
            var week = Read("Week");
            Write(GenerateMessage(_service.MarkStudentAbsent(id, week)));
        }

        private void JustifyStudentAbsence()
        {
            var id = Read("Id");
            var week = Read("Week");
            Write(GenerateMessage(_service.JustifyStudentAbsence(id, week)));
        }
    }
}