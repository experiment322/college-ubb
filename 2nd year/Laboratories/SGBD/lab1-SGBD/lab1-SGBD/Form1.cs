using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace lab1_SGBD
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
            dataGridViewAppCategories.SelectionChanged += LoadChildren;
        }

        private void LoadParent()
        {
            var command = new SqlCommand("select * from APP_STORE.dbo.APP_CATEGORY",
                new SqlConnection(GetConnectionString()));
            var appCategoryTable = new SqlDataAdapter(command);

            var dataSet = new DataSet();
            appCategoryTable.Fill(dataSet, "APP_CATEGORY");
            dataGridViewAppCategories.DataSource = dataSet.Tables["APP_CATEGORY"];
        }

        private void LoadChildren(object sender, EventArgs e)
        {
            var command = new SqlCommand("select * from APP_STORE.dbo.APP where APP_CATEGORY_ID=@id",
                new SqlConnection(GetConnectionString()));
            var appCategoryId = Convert.ToInt32(dataGridViewAppCategories.CurrentRow?.Cells[0].Value);
            command.Parameters.AddWithValue("@id", appCategoryId);
            var appTable = new SqlDataAdapter(command);

            var dataSet = new DataSet();
            appTable.Fill(dataSet, "APP");
            dataGridViewApps.DataSource = dataSet.Tables["APP"];
        }

        private void ButtonView_Click(object sender, EventArgs e)
        {
            var command = new SqlCommand("select * from APP_STORE.dbo.APP", new SqlConnection(GetConnectionString()));
            var appTable = new SqlDataAdapter(command);

            var dataSet = new DataSet();
            appTable.Fill(dataSet, "APP");
            dataGridViewApps.DataSource = dataSet.Tables["APP"];
        }
    }
}