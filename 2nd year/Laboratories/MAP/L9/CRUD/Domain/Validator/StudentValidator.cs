using System.Text.RegularExpressions;
using static CRUD.Utils.WeekUtils;

namespace CRUD.Domain.Validator
{
    public class StudentValidator : IValidator<Student, int>
    {
        private const int MaxAbsences = (1 << SemesterWeekSpan) - 1;

        public void Validate(Student student)
        {
            if (student.Id < 1)
            {
                throw new ValidationException("Id is invalid (negative)");
            }

            if (student.Group < 1)
            {
                throw new ValidationException("Group is invalid (negative)");
            }

            if (student.Name == null || !Regex.IsMatch(student.Name, "^[A-Z][a-z]+([ -][A-Z][a-z]+)+$"))
            {
                throw new ValidationException("Name is invalid (null or malformed)");
            }

            if (student.Email == null || !Regex.IsMatch(student.Email, "^\\w+@\\w+\\.\\w+$"))
            {
                throw new ValidationException("Email is invalid (null or malformed)");
            }

            if (student.TeacherName == null || !Regex.IsMatch(student.TeacherName, "^[A-Z][a-z]+([ -][A-Z][a-z]+)+$"))
            {
                throw new ValidationException("TeacherName is invalid (null or malformed)");
            }

            if (student.Absences < 0 || student.Absences > MaxAbsences)
            {
                throw new ValidationException($"Absences are invalid (negative or more than {SemesterWeekSpan})");
            }

            if (student.JustifiedAbsences < 0 || (student.JustifiedAbsences | student.Absences) != student.Absences)
            {
                throw new ValidationException("JustifiedAbsences are invalid (negative or mismatched with Absences)");
            }
        }
    }
}