using System.Collections.Generic;
using log4net;
using Npgsql;
using project.domain;
using project.util;

namespace project.repository
{
    public class AthleteRepository : IAthleteRepository
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(AthleteRepository));
        private readonly NpgsqlConnection _connection = DbManager.GetConnection();

        public Athlete FindOne(int id)
        {
            const string commandText = "select id, name from alex_mpp.public.athlete where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        return new Athlete
                        {
                            Id = reader.GetInt32(0),
                            Name = reader.GetString(1)
                        };
                    }
                }
            }

            return null;
        }

        public IEnumerable<Athlete> FindAll()
        {
            const string commandText = "select id, name from alex_mpp.public.athlete";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                using (var reader = command.ExecuteReader())
                {
                    var athletes = new List<Athlete>();
                    while (reader.Read())
                    {
                        athletes.Add(new Athlete
                        {
                            Id = reader.GetInt32(0),
                            Name = reader.GetString(1)
                        });
                    }

                    return athletes;
                }
            }
        }

        public void Save(Athlete athlete)
        {
            const string commandText = "insert into alex_mpp.public.athlete values (@id, @name)";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", athlete.Id);
                command.Parameters.AddWithValue("name", athlete.Name);

                command.ExecuteNonQuery();
            }
        }

        public void Update(Athlete athlete)
        {
            const string commandText = "update alex_mpp.public.athlete set name = @name where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", athlete.Id);
                command.Parameters.AddWithValue("name", athlete.Name);

                command.ExecuteNonQuery();
            }
        }

        public void Delete(int id)
        {
            const string commandText = "delete from alex_mpp.public.athlete where id = @id";
            using (var command = new NpgsqlCommand(commandText, _connection))
            {
                Log.Debug(commandText);

                command.Parameters.AddWithValue("id", id);

                command.ExecuteNonQuery();
            }
        }
    }
}