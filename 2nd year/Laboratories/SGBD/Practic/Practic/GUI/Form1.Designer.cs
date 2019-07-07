using System.Windows.Forms;

namespace GUI
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
            this.dataGridViewSoups = new System.Windows.Forms.DataGridView();
            this.dataGridViewCooks = new System.Windows.Forms.DataGridView();
            this.labelSoups = new System.Windows.Forms.Label();
            this.labelCooks = new System.Windows.Forms.Label();
            this.buttonView = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewSoups)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCooks)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewApps
            // 
            this.dataGridViewSoups.AllowUserToAddRows = false;
            this.dataGridViewSoups.AllowUserToDeleteRows = true;
            this.dataGridViewSoups.AllowUserToResizeColumns = false;
            this.dataGridViewSoups.AllowUserToResizeRows = false;
            this.dataGridViewSoups.EditMode = DataGridViewEditMode.EditOnKeystroke;
            this.dataGridViewSoups.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewSoups.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewSoups.Location = new System.Drawing.Point(12, 64);
            this.dataGridViewSoups.Name = "dataGridViewSoups";
            this.dataGridViewSoups.RowTemplate.Height = 24;
            this.dataGridViewSoups.Size = new System.Drawing.Size(920, 652);
            this.dataGridViewSoups.TabIndex = 0;
            // 
            // dataGridViewAppCategories
            // 
            this.dataGridViewCooks.AllowUserToAddRows = false;
            this.dataGridViewCooks.AllowUserToDeleteRows = false;
            this.dataGridViewCooks.AllowUserToResizeColumns = false;
            this.dataGridViewCooks.AllowUserToResizeRows = false;
            this.dataGridViewCooks.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewCooks.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewCooks.Location = new System.Drawing.Point(954, 64);
            this.dataGridViewCooks.Name = "dataGridViewCooks";
            this.dataGridViewCooks.RowTemplate.Height = 24;
            this.dataGridViewCooks.Size = new System.Drawing.Size(393, 652);
            this.dataGridViewCooks.TabIndex = 1;
            // 
            // labelAppCategories
            // 
            this.labelSoups.AutoSize = true;
            this.labelSoups.Location = new System.Drawing.Point(1073, 28);
            this.labelSoups.Name = "labelSoups";
            this.labelSoups.Size = new System.Drawing.Size(168, 17);
            this.labelSoups.TabIndex = 2;
            this.labelSoups.Text = "BUCATARI";
            // 
            // labelApps
            // 
            this.labelCooks.AutoSize = true;
            this.labelCooks.Location = new System.Drawing.Point(428, 28);
            this.labelCooks.Name = "labelCooks";
            this.labelCooks.Size = new System.Drawing.Size(92, 17);
            this.labelCooks.TabIndex = 3;
            this.labelCooks.Text = "SUPE";
            // 
            // buttonView
            // 
            this.buttonView.Location = new System.Drawing.Point(64, 18);
            this.buttonView.Name = "buttonView";
            this.buttonView.Size = new System.Drawing.Size(180, 37);
            this.buttonView.TabIndex = 4;
            this.buttonView.Text = "AFISEAZA TOATE SUPELE";
            this.buttonView.UseVisualStyleBackColor = true;
            this.buttonView.Click += new System.EventHandler(this.ButtonView_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1359, 728);
            this.Controls.Add(this.buttonView);
            this.Controls.Add(this.labelCooks);
            this.Controls.Add(this.labelSoups);
            this.Controls.Add(this.dataGridViewCooks);
            this.Controls.Add(this.dataGridViewSoups);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewSoups)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCooks)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion
        
        private System.Windows.Forms.DataGridView dataGridViewSoups;
        private System.Windows.Forms.DataGridView dataGridViewCooks;
        private System.Windows.Forms.Label labelSoups;
        private System.Windows.Forms.Label labelCooks;
        private System.Windows.Forms.Button buttonView;
    }
}
