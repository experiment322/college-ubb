using System;
using System.Collections.Generic;
using CRUD.Domain;
using CRUD.Repository;
using CRUD.Utils;

namespace CRUD.Service
{
    public class StudentService
    {
        private readonly WeekUtils _weekUtils;
        private readonly ICrudRepository<int, Student> _repository;

        public StudentService(WeekUtils weekUtils, ICrudRepository<int, Student> repository)
        {
            _weekUtils = weekUtils;
            _repository = repository;
        }

        private void FillStudentDefaults(IDictionary<string, string> dictionary)
        {
            dictionary.TryGetValue("Absences", out var absences);
            if (string.IsNullOrEmpty(absences))
            {
                dictionary["Absences"] = "0";
            }

            dictionary.TryGetValue("JustifiedAbsences", out var justifiedAbsences);
            if (string.IsNullOrEmpty(justifiedAbsences))
            {
                dictionary["JustifiedAbsences"] = "0";
            }
        }

        private Student FromDictionary(IDictionary<string, string> dictionary)
        {
            FillStudentDefaults(dictionary);
            return new Student
            {
                Id = Convert.ToInt32(dictionary["Id"]),
                Group = Convert.ToInt32(dictionary["Group"]),
                Name = dictionary["Name"],
                Email = dictionary["Email"],
                TeacherName = dictionary["TeacherName"],
                Absences = Convert.ToInt32(dictionary["Absences"]),
                JustifiedAbsences = Convert.ToInt32(dictionary["JustifiedAbsences"])
            };
        }

        public bool CreateStudent(IDictionary<string, string> dictionary)
        {
            return _repository.Save(FromDictionary(dictionary)) == null;
        }

        public bool UpdateStudent(IDictionary<string, string> dictionary)
        {
            return _repository.Update(FromDictionary(dictionary)) == null;
        }

        public bool DeleteStudent(string id)
        {
            return _repository.Delete(Convert.ToInt32(id)) != null;
        }

        public Student ReadOneStudent(string id)
        {
            return _repository.FindOne(Convert.ToInt32(id));
        }

        public IEnumerable<Student> ReadAllStudents()
        {
            return _repository.FindAll();
        }

        public bool MarkStudentAbsent(string id, string week)
        {
            if (string.IsNullOrEmpty(week))
            {
                week = _weekUtils.GetCurrentDidacticWeek().ToString();
            }

            if (Convert.ToInt32(week) > _weekUtils.GetCurrentDidacticWeek())
            {
                throw new ArgumentOutOfRangeException(nameof(week) + ' ' + week);
            }

            var student = _repository.FindOne(Convert.ToInt32(id));
            if (student == null)
            {
                throw new KeyNotFoundException(nameof(id) + ' ' + id);
            }

            var updatedStudent = EntityUtils.Clone<Student, int>(student);
            updatedStudent.Absences |= 1 << (Convert.ToInt32(week) - 1);
            return _repository.Update(updatedStudent) == null;
        }

        public bool JustifyStudentAbsence(string id, string week)
        {
            var student = _repository.FindOne(Convert.ToInt32(id));
            if (student == null)
            {
                throw new KeyNotFoundException(nameof(id) + ' ' + id);
            }

            var updatedStudent = EntityUtils.Clone<Student, int>(student);
            updatedStudent.JustifiedAbsences |= 1 << (Convert.ToInt32(week) - 1);
            return _repository.Update(updatedStudent) == null;
        }
    }
}