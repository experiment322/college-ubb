using System.Collections.Generic;
using log4net;
using Npgsql;
using project.domain;
using project.util;

namespace project.repository
{
    public class GameRepository : IGameRepository
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(GameRepository));
        private readonly NpgsqlConnection _connection = DbManager.GetConnection();

        public Game FindOne(int id)
        {
            const string commandText = "select id, name from alex_mpp.public.game where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        return new Game
                        {
                            Id = reader.GetInt32(0),
                            Name = reader.GetString(1)
                        };
                    }
                }
            }

            return null;
        }

        public IEnumerable<Game> FindAll()
        {
            const string commandText = "select id, name from alex_mpp.public.game";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                using (var reader = command.ExecuteReader())
                {
                    var games = new List<Game>();
                    while (reader.Read())
                    {
                        games.Add(new Game
                        {
                            Id = reader.GetInt32(0),
                            Name = reader.GetString(1)
                        });
                    }

                    return games;
                }
            }
        }

        public void Save(Game game)
        {
            const string commandText = "insert into alex_mpp.public.game values (@id, @name)";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", game.Id);
                command.Parameters.AddWithValue("name", game.Name);

                command.ExecuteNonQuery();
            }
        }

        public void Update(Game game)
        {
            const string commandText = "update alex_mpp.public.game set name = @name where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", game.Id);
                command.Parameters.AddWithValue("name", game.Name);

                command.ExecuteNonQuery();
            }
        }

        public void Delete(int id)
        {
            const string commandText = "delete from alex_mpp.public.game where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                command.ExecuteNonQuery();
            }
        }
    }
}