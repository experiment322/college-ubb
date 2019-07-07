using static CRUD.Utils.EntityUtils;

namespace CRUD.Domain
{
    public class Task : IHasId<int>
    {
        [PropertySequence(1)] public int Id { get; set; }
        [PropertySequence(2)] public int AssignmentWeek { get; set; }
        [PropertySequence(3)] public int DeadlineWeek { get; set; }
        [PropertySequence(4)] public string Description { get; set; }

        private bool Equals(Task other)
        {
            return Id == other.Id && AssignmentWeek == other.AssignmentWeek && DeadlineWeek == other.DeadlineWeek &&
                   string.Equals(Description, other.Description);
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            return obj.GetType() == GetType() && Equals((Task) obj);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                var hashCode = Id;
                hashCode = (hashCode * 397) ^ AssignmentWeek;
                hashCode = (hashCode * 397) ^ DeadlineWeek;
                hashCode = (hashCode * 397) ^ (Description != null ? Description.GetHashCode() : 0);
                return hashCode;
            }
        }
    }
}