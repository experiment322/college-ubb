using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Demo
{
    public class DemoForm : Form
    {
        private const string AppTable = "APP";
        private const string AppCategoryTable = "APP_CATEGORY";
        private const string ConnectionString = "Server=alex-pc;Database=APP_STORE;User=SA;Password=SA;";

        private readonly DataSet _dataSet;
        private readonly SqlDataAdapter _appDataAdapter;
        private readonly SqlDataAdapter _appCategoryDataAdapter;

        private BindingSource _appBinding;
        private BindingSource _appCategoryBinding;

        private DataGridView _appGrid;
        private DataGridView _appCategoryGrid;

        public DemoForm()
        {
            _dataSet = new DataSet();
            _appDataAdapter = new SqlDataAdapter
            {
                MissingSchemaAction = MissingSchemaAction.AddWithKey,
                SelectCommand = new SqlCommand("select * from APP_STORE.dbo.APP",
                    new SqlConnection(ConnectionString))
            };
            _appCategoryDataAdapter = new SqlDataAdapter
            {
                MissingSchemaAction = MissingSchemaAction.AddWithKey,
                SelectCommand = new SqlCommand("select * from APP_STORE.dbo.APP_CATEGORY",
                    new SqlConnection(ConnectionString))
            };

            FillTables();
            InitForm();
        }

        private void FillTables()
        {
            try
            {
                _appDataAdapter.Fill(_dataSet, AppTable);
                _appCategoryDataAdapter.Fill(_dataSet, AppCategoryTable);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private void InitForm()
        {
            Width = 800;
            Height = 600;

            var mainPanel = new Panel {Parent = this, Dock = DockStyle.Fill};

            _appBinding = new BindingSource {DataSource = _dataSet.Tables[AppTable]};
            _appGrid = new DataGridView
            {
                Top = 0,
                Left = 100,
                Width = 600,
                Height = 200,
                Parent = mainPanel,
                ReadOnly = true,
                DataSource = _appBinding,
                SelectionMode = DataGridViewSelectionMode.FullRowSelect,
                AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill
            };

            _appCategoryBinding = new BindingSource {DataSource = _dataSet.Tables[AppCategoryTable]};
            _appCategoryGrid = new DataGridView
            {
                Top = 200,
                Left = 100,
                Width = 600,
                Height = 200,
                Parent = mainPanel,
                ReadOnly = true,
                DataSource = _appCategoryBinding,
                SelectionMode = DataGridViewSelectionMode.FullRowSelect,
                AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill,
            };

            _appCategoryGrid.SelectionChanged += (sender, args) =>
            {
                var ids = new int[_appCategoryGrid.SelectedRows.Count];
                for (var i = 0; i < _appCategoryGrid.SelectedRows.Count; i++)
                {
                    ids[i] = (int) _appCategoryGrid.SelectedRows[i].Cells[0].Value;
                }

                if (_appCategoryGrid.SelectedRows.Count == 0)
                {
                    return;
                }

                try
                {
                    _appDataAdapter.SelectCommand =
                        new SqlCommand(
                            $"select * from APP_STORE.dbo.APP where APP_CATEGORY_ID in ({string.Join(", ", ids)})",
                            new SqlConnection(ConnectionString));
                    _appDataAdapter.Fill(_dataSet, AppTable);
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.Message);
                }
            };
        }
    }
}