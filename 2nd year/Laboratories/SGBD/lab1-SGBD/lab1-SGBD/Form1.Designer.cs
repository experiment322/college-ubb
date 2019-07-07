namespace lab1_SGBD
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewApps = new System.Windows.Forms.DataGridView();
            this.dataGridViewAppCategories = new System.Windows.Forms.DataGridView();
            this.labelAppCategories = new System.Windows.Forms.Label();
            this.labelApps = new System.Windows.Forms.Label();
            this.buttonView = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewApps)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAppCategories)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewApps
            // 
            this.dataGridViewApps.AllowUserToAddRows = false;
            this.dataGridViewApps.AllowUserToDeleteRows = false;
            this.dataGridViewApps.AllowUserToResizeColumns = false;
            this.dataGridViewApps.AllowUserToResizeRows = false;
            this.dataGridViewApps.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewApps.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewApps.Location = new System.Drawing.Point(12, 64);
            this.dataGridViewApps.Name = "dataGridViewApps";
            this.dataGridViewApps.RowTemplate.Height = 24;
            this.dataGridViewApps.Size = new System.Drawing.Size(920, 652);
            this.dataGridViewApps.TabIndex = 0;
            // 
            // dataGridViewAppCategories
            // 
            this.dataGridViewAppCategories.AllowUserToAddRows = false;
            this.dataGridViewAppCategories.AllowUserToDeleteRows = false;
            this.dataGridViewAppCategories.AllowUserToResizeColumns = false;
            this.dataGridViewAppCategories.AllowUserToResizeRows = false;
            this.dataGridViewAppCategories.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewAppCategories.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewAppCategories.Location = new System.Drawing.Point(954, 64);
            this.dataGridViewAppCategories.Name = "dataGridViewAppCategories";
            this.dataGridViewAppCategories.RowTemplate.Height = 24;
            this.dataGridViewAppCategories.Size = new System.Drawing.Size(393, 652);
            this.dataGridViewAppCategories.TabIndex = 1;
            // 
            // labelAppCategories
            // 
            this.labelAppCategories.AutoSize = true;
            this.labelAppCategories.Location = new System.Drawing.Point(1073, 28);
            this.labelAppCategories.Name = "labelAppCategories";
            this.labelAppCategories.Size = new System.Drawing.Size(168, 17);
            this.labelAppCategories.TabIndex = 2;
            this.labelAppCategories.Text = "App Categories (Parent)";
            // 
            // labelApps
            // 
            this.labelApps.AutoSize = true;
            this.labelApps.Location = new System.Drawing.Point(428, 28);
            this.labelApps.Name = "labelApps";
            this.labelApps.Size = new System.Drawing.Size(92, 17);
            this.labelApps.TabIndex = 3;
            this.labelApps.Text = "Apps (Child)";
            // 
            // buttonView
            // 
            this.buttonView.Location = new System.Drawing.Point(64, 18);
            this.buttonView.Name = "buttonView";
            this.buttonView.Size = new System.Drawing.Size(180, 37);
            this.buttonView.TabIndex = 4;
            this.buttonView.Text = "View all Apps table";
            this.buttonView.UseVisualStyleBackColor = true;
            this.buttonView.Click += new System.EventHandler(this.ButtonView_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1359, 728);
            this.Controls.Add(this.buttonView);
            this.Controls.Add(this.labelApps);
            this.Controls.Add(this.labelAppCategories);
            this.Controls.Add(this.dataGridViewAppCategories);
            this.Controls.Add(this.dataGridViewApps);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewApps)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAppCategories)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewApps;
        private System.Windows.Forms.DataGridView dataGridViewAppCategories;
        private System.Windows.Forms.Label labelAppCategories;
        private System.Windows.Forms.Label labelApps;
        private System.Windows.Forms.Button buttonView;
    }
}

