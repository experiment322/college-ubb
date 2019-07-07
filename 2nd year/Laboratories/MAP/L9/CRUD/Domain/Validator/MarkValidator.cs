using static CRUD.Utils.WeekUtils;

namespace CRUD.Domain.Validator
{
    public class MarkValidator : IValidator<Mark, string>
    {
        public void Validate(Mark mark)
        {
            if (mark.Id == null || mark.TaskId < 1 || mark.StudentId < 1)
            {
                throw new ValidationException("Id is invalid (null or negative)");
            }

            if (mark.Value < 1 || mark.Value > 10)
            {
                throw new ValidationException("Value is invalid (not between 1 - 10)");
            }

            if (mark.Week < 1 || mark.Week > SemesterWeekSpan)
            {
                throw new ValidationException($"Week is invalid (not between 1 - {SemesterWeekSpan})");
            }

            if (string.IsNullOrEmpty(mark.Feedback))
            {
                throw new ValidationException("Feedback is invalid (null or empty)");
            }
        }
    }
}