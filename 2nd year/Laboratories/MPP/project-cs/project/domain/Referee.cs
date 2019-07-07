namespace project.domain
{
    public class Referee
    {
        public int Id { get; set; }
        public int GameId { get; set; }
        public string Name { get; set; }
        public string Username { get; set; }
        public string Password { get; set; }

        public override string ToString()
        {
            return
                $"{nameof(Id)}: {Id}, {nameof(GameId)}: {GameId}, {nameof(Name)}: {Name}, {nameof(Username)}: {Username}, {nameof(Password)}: {Password}";
        }
    }
}