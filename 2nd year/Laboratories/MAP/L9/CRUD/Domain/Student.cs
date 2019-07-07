using static CRUD.Utils.EntityUtils;

namespace CRUD.Domain
{
    public class Student : IHasId<int>
    {
        [PropertySequence(1)] public int Id { get; set; }
        [PropertySequence(2)] public int Group { get; set; }
        [PropertySequence(3)] public string Name { get; set; }
        [PropertySequence(4)] public string Email { get; set; }
        [PropertySequence(5)] public string TeacherName { get; set; }
        [PropertySequence(6)] public int Absences { get; set; }
        [PropertySequence(7)] public int JustifiedAbsences { get; set; }

        private bool Equals(Student other)
        {
            return Id == other.Id && Group == other.Group && string.Equals(Name, other.Name) &&
                   string.Equals(Email, other.Email) && string.Equals(TeacherName, other.TeacherName) &&
                   Absences == other.Absences && JustifiedAbsences == other.JustifiedAbsences;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            return obj.GetType() == GetType() && Equals((Student) obj);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                var hashCode = Id;
                hashCode = (hashCode * 397) ^ Group;
                hashCode = (hashCode * 397) ^ (Name != null ? Name.GetHashCode() : 0);
                hashCode = (hashCode * 397) ^ (Email != null ? Email.GetHashCode() : 0);
                hashCode = (hashCode * 397) ^ (TeacherName != null ? TeacherName.GetHashCode() : 0);
                hashCode = (hashCode * 397) ^ Absences;
                hashCode = (hashCode * 397) ^ JustifiedAbsences;
                return hashCode;
            }
        }
    }
}