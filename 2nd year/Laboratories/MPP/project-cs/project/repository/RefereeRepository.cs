using System.Collections.Generic;
using log4net;
using Npgsql;
using project.domain;
using project.util;

namespace project.repository
{
    public class RefereeRepository : IRefereeRepository
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(RefereeRepository));
        private readonly NpgsqlConnection _connection = DbManager.GetConnection();

        public Referee FindOne(int id)
        {
            const string commandText =
                "select id, game_id, name, username, password from alex_mpp.public.referee where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        return new Referee
                        {
                            Id = reader.GetInt32(0),
                            GameId = reader.GetInt32(1),
                            Name = reader.GetString(2),
                            Username = reader.GetString(3),
                            Password = reader.GetString(4)
                        };
                    }
                }
            }

            return null;
        }

        public IEnumerable<Referee> FindAll()
        {
            const string commandText = "select id, game_id, name, username, password from alex_mpp.public.referee";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                using (var reader = command.ExecuteReader())
                {
                    var referees = new List<Referee>();
                    while (reader.Read())
                    {
                        referees.Add(new Referee
                        {
                            Id = reader.GetInt32(0),
                            GameId = reader.GetInt32(1),
                            Name = reader.GetString(2),
                            Username = reader.GetString(3),
                            Password = reader.GetString(4)
                        });
                    }

                    return referees;
                }
            }
        }

        public void Save(Referee referee)
        {
            const string commandText =
                "insert into alex_mpp.public.referee values (@id, @game_id, @name, @username, @password)";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", referee.Id);
                command.Parameters.AddWithValue("game_id", referee.GameId);
                command.Parameters.AddWithValue("name", referee.Name);
                command.Parameters.AddWithValue("username", referee.Username);
                command.Parameters.AddWithValue("password", referee.Password);

                command.ExecuteNonQuery();
            }
        }

        public void Update(Referee referee)
        {
            const string commandText =
                "update alex_mpp.public.referee set game_id = @game_id, name = @name, username = @username, password = @password where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", referee.Id);
                command.Parameters.AddWithValue("game_id", referee.GameId);
                command.Parameters.AddWithValue("name", referee.Name);
                command.Parameters.AddWithValue("username", referee.Username);
                command.Parameters.AddWithValue("password", referee.Password);

                command.ExecuteNonQuery();
            }
        }

        public void Delete(int id)
        {
            const string commandText = "delete from alex_mpp.public.referee where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                command.ExecuteNonQuery();
            }
        }
    }
}