using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Lab2
{
    public partial class Form1 : Form
    {
        private readonly DataSet ds = new DataSet();
        private readonly SqlDataAdapter da = new SqlDataAdapter();
        private readonly string childTableName = ConfigurationManager.AppSettings["ChildTableName"];

        private readonly string columnNamesInsertParameters =
            ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];

        private readonly List<string> columnNames =
            new List<string>(ConfigurationManager.AppSettings["ChildLabelNames"].Split(','));

        private readonly List<string> paramsNames =
            new List<string>(ConfigurationManager.AppSettings["ColumnNamesInsertParameters"].Split(','));

        private readonly List<string> columnInitiate =
            new List<string>(ConfigurationManager.AppSettings["ChildTextBoxContent"].Split(','));

        private readonly SqlConnection connection = new SqlConnection(GetConnectionString());
        private readonly int nr = Convert.ToInt32(ConfigurationManager.AppSettings["ChildNumberOfColumns"]);
        private TextBox[] textBoxes;
        private Label[] labels;

        private static string GetConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
        }

        public Form1()
        {
            InitializeComponent();
            PopulatePanel();
            dataGridViewParent.SelectionChanged += LoadChildren;
            dataGridViewChild.SelectionChanged += LoadInformation;
            LoadParent();
        }

        private void LoadInformation(object sender, EventArgs e)
        {
            LoadInformation();
        }

        private void LoadInformation()
        {
            for (var i = 0; i < nr; i++)
                textBoxes[i].Text = Convert.ToString(dataGridViewChild.CurrentRow?.Cells[i].Value);
        }

        private void PopulatePanel()
        {
            textBoxes = new TextBox[nr];
            labels = new Label[nr];

            for (var i = 0; i < nr; i++)
            {
                textBoxes[i] = new TextBox {Text = columnInitiate[i]};
                labels[i] = new Label {Text = columnNames[i], Width = 200};
            }

            for (var i = 0; i < nr; i++)
            {
                flowLayoutPanel1.Controls.Add(textBoxes[i]);
                flowLayoutPanel1.Controls.Add(labels[i]);
            }
        }

        private void LoadParent()
        {
            var select = ConfigurationSettings.AppSettings["SelectParent"];
            da.SelectCommand = new SqlCommand(select, connection);
            ds.Clear();
            da.Fill(ds);
            dataGridViewParent.DataSource = ds.Tables[0];
        }

        private void LoadChildren(object sender, EventArgs e)
        {
            LoadChildren();
        }

        private void LoadChildren()
        {
            var parentId = (int) dataGridViewParent.CurrentRow?.Cells[0].Value;
            var select = ConfigurationManager.AppSettings["SelectChild"];
            var cmd = new SqlCommand(select, connection);
            cmd.Parameters.AddWithValue("@id", parentId);
            var daChild = new SqlDataAdapter(cmd);
            var dataSet = new DataSet();

            daChild.Fill(dataSet);
            dataGridViewChild.DataSource = dataSet.Tables[0];
        }

        private void viewButton_Click(object sender, EventArgs e)
        {
            var select = ConfigurationManager.AppSettings["SelectQuery"];
            var cmd = new SqlCommand(select, connection);
            var daChild = new SqlDataAdapter(cmd);
            var dataSet = new DataSet();

            daChild.Fill(dataSet);
            dataGridViewChild.DataSource = dataSet.Tables[0];
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            try
            {
                var cmd = new SqlCommand(
                    "insert into " + childTableName + " ( " + ConfigurationManager.AppSettings["ChildLabelNames"] +
                    " ) values ( " + columnNamesInsertParameters + " )", connection);
                for (var i = 0; i < nr; i++)
                {
                    cmd.Parameters.AddWithValue(paramsNames[i], textBoxes[i].Text);
                }

                var daChild = new SqlDataAdapter(cmd);
                var dataSet = new DataSet();
                connection.Open();
                daChild.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Added!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                connection.Close();
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            try
            {
                var delete = ConfigurationManager.AppSettings["DeleteChild"];
                var cmd = new SqlCommand(delete, connection);
                cmd.Parameters.AddWithValue("@id", dataGridViewChild.CurrentRow?.Cells[0].Value);
                var daChild = new SqlDataAdapter(cmd);
                var dataSet = new DataSet();
                connection.Open();
                cmd.ExecuteNonQuery();
                daChild.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Deleted!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                connection.Close();
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                string update = ConfigurationManager.AppSettings["UpdateQuery"];
                SqlCommand cmd = new SqlCommand(update, connection);
                for (int i = 1; i < nr; i++)
                {
                    cmd.Parameters.AddWithValue(paramsNames[i], textBoxes[i].Text);
                }

                cmd.Parameters.AddWithValue("@id", (int) dataGridViewChild.CurrentRow.Cells[0].Value);
                SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                connection.Open();
                daChild.Fill(dataSet);
                connection.Close();
                MessageBox.Show("Updated!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                connection.Close();
            }
        }
    }
}