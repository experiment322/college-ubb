using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace GUI
{
    public partial class Form1 : Form
    {
        private static string GetConnectionString()
        {
            return "Server=alex-pc;Database=APP_STORE;User=SA;Password=SA;";
        }

        public Form1()
        {
            InitializeComponent();
            LoadParent();
            dataGridViewCooks.SelectionChanged += LoadChildren;
            dataGridViewSoups.UserDeletingRow += DeleteChild;
        }

        private void LoadParent()
        {
            var command = new SqlCommand("select * from Subiectul32019.dbo.Bucatari",
                new SqlConnection(GetConnectionString()));
            var appCategoryTable = new SqlDataAdapter(command);

            var dataSet = new DataSet();
            appCategoryTable.Fill(dataSet, "BUCATARI");
            dataGridViewCooks.DataSource = dataSet.Tables["BUCATARI"];
        }

        private void LoadChildren(object sender, EventArgs e)
        {
            var command = new SqlCommand("select * from Subiectul32019.dbo.Supe where cod_bucatar = @id",
                new SqlConnection(GetConnectionString()));
            command.Parameters.AddWithValue("@id", dataGridViewCooks.CurrentRow?.Cells[0].Value);
            var appTable = new SqlDataAdapter(command);

            var dataSet = new DataSet();
            appTable.Fill(dataSet, "SUPE");
            dataGridViewSoups.DataSource = dataSet.Tables["SUPE"];
        }

        private static void DeleteChild(object sender, DataGridViewRowCancelEventArgs args)
        {
            string message = "Simple MessageBox";
            MessageBox.Show(message);
            Console.WriteLine(args.Row);
            var command = new SqlCommand(
                "delete from Subiectul32019.dbo.Supe where cod_supa = @cod_supa",
                new SqlConnection(GetConnectionString()));
            command.Parameters.AddWithValue("@cod_supa", 0);
        }

        private void ButtonView_Click(object sender, EventArgs e)
        {
            var command = new SqlCommand("select * from Subiectul32019.dbo.Supe",
                new SqlConnection(GetConnectionString()));
            var appTable = new SqlDataAdapter(command);

            var dataSet = new DataSet();
            appTable.Fill(dataSet, "SUPE");
            dataGridViewSoups.DataSource = dataSet.Tables["SUPE"];
        }
    }
}