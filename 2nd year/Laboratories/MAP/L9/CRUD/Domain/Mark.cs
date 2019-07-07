using System;
using static CRUD.Utils.EntityUtils;

namespace CRUD.Domain
{
    public class Mark : IHasId<string>
    {
        public const char IdSeparator = '~';

        public string Id
        {
            get => string.Join(IdSeparator.ToString(), TaskId, StudentId);
            set
            {
                TaskId = int.Parse(value.Split(new[] {IdSeparator}, 2)[0]);
                StudentId = int.Parse(value.Split(new[] {IdSeparator}, 2)[1]);
            }
        }

        [PropertySequence(1)] public int TaskId { get; set; }
        [PropertySequence(2)] public int StudentId { get; set; }
        [PropertySequence(3)] public int Week { get; set; }
        [PropertySequence(4)] public double Value { get; set; }
        [PropertySequence(5)] public string Feedback { get; set; }

        private bool Equals(Mark other)
        {
            return TaskId == other.TaskId && StudentId == other.StudentId && Week == other.Week &&
                   Value.Equals(other.Value) && string.Equals(Feedback, other.Feedback);
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            return obj.GetType() == GetType() && Equals((Mark) obj);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                var hashCode = TaskId;
                hashCode = (hashCode * 397) ^ StudentId;
                hashCode = (hashCode * 397) ^ Week;
                hashCode = (hashCode * 397) ^ Value.GetHashCode();
                hashCode = (hashCode * 397) ^ (Feedback != null ? Feedback.GetHashCode() : 0);
                return hashCode;
            }
        }
    }
}