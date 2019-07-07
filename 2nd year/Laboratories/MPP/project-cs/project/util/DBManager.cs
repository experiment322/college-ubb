using System.Data;
using Npgsql;

namespace project.util
{
    public static class DbManager
    {
        private static NpgsqlConnection _connection;

        public static NpgsqlConnection GetConnection()
        {
            if (_connection == null)
            {
                _connection = new NpgsqlConnection("Host=localhost;Username=alex;Database=alex_mpp;");
            }

            if (_connection.State != ConnectionState.Open)
            {
                _connection.Open();
            }

            return _connection;
        }
    }
}