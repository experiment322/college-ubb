using static CRUD.Utils.WeekUtils;

namespace CRUD.Domain.Validator
{
    public class TaskValidator : IValidator<Task, int>
    {
        public void Validate(Task task)
        {
            if (task.Id < 1)
            {
                throw new ValidationException("Id is invalid (negative)");
            }

            if (task.AssignmentWeek < 1 || task.AssignmentWeek > SemesterWeekSpan - 1)
            {
                throw new ValidationException($"AssignmentWeek is invalid (not between 1 - {SemesterWeekSpan - 1})");
            }

            if (task.DeadlineWeek < task.AssignmentWeek + 1 || task.DeadlineWeek > SemesterWeekSpan)
            {
                throw new ValidationException(
                    $"DeadlineWeek is invalid (not between (AssignmentWeek + 1) - {SemesterWeekSpan})");
            }

            if (string.IsNullOrEmpty(task.Description))
            {
                throw new ValidationException("Description is invalid (null or empty)");
            }
        }
    }
}