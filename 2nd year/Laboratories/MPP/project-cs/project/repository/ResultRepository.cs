using System.Collections.Generic;
using log4net;
using Npgsql;
using project.domain;
using project.util;

namespace project.repository
{
    public class ResultRepository : IResultRepository
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(RefereeRepository));
        private readonly NpgsqlConnection _connection = DbManager.GetConnection();

        public Result FindOne(int id)
        {
            const string commandText =
                "select id, game_id, athlete_id, value from alex_mpp.public.result where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        return new Result
                        {
                            Id = reader.GetInt32(0),
                            GameId = reader.GetInt32(1),
                            AthleteId = reader.GetInt32(2),
                            Value = reader.GetDouble(3)
                        };
                    }
                }
            }

            return null;
        }

        public IEnumerable<Result> FindAll()
        {
            const string commandText = "select id, game_id, athlete_id, value from alex_mpp.public.result";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                using (var reader = command.ExecuteReader())
                {
                    var results = new List<Result>();
                    while (reader.Read())
                    {
                        results.Add(new Result
                        {
                            Id = reader.GetInt32(0),
                            GameId = reader.GetInt32(1),
                            AthleteId = reader.GetInt32(2),
                            Value = reader.GetDouble(3)
                        });
                    }

                    return results;
                }
            }
        }

        public void Save(Result result)
        {
            const string commandText =
                "insert into alex_mpp.public.result values (@id, @game_id, @athlete_id, @value)";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", result.Id);
                command.Parameters.AddWithValue("game_id", result.GameId);
                command.Parameters.AddWithValue("athlete_id", result.AthleteId);
                command.Parameters.AddWithValue("value", result.Value);

                command.ExecuteNonQuery();
            }
        }

        public void Update(Result result)
        {
            const string commandText =
                "update alex_mpp.public.result set game_id = @game_id, athlete_id = @athlete_id, value = @value where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", result.Id);
                command.Parameters.AddWithValue("game_id", result.GameId);
                command.Parameters.AddWithValue("athlete_id", result.AthleteId);
                command.Parameters.AddWithValue("value", result.Value);

                command.ExecuteNonQuery();
            }
        }

        public void Delete(int id)
        {
            const string commandText = "delete from alex_mpp.public.result where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                command.ExecuteNonQuery();
            }
        }
    }
}