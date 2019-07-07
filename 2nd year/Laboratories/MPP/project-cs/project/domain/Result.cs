namespace project.domain
{
    public class Result
    {
        public int Id { get; set; }
        public int GameId { get; set; }
        public int AthleteId { get; set; }
        public double Value { get; set; }

        public override string ToString()
        {
            return
                $"{nameof(Id)}: {Id}, {nameof(GameId)}: {GameId}, {nameof(AthleteId)}: {AthleteId}, {nameof(Value)}: {Value}";
        }
    }
}