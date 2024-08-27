namespace PlayerDemo
{
    partial class frmMain
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.btnOpen2 = new System.Windows.Forms.Button();
            this.btnOpen1 = new System.Windows.Forms.Button();
            this.cmbxPort = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.btnInit = new System.Windows.Forms.Button();
            this.ofd = new System.Windows.Forms.OpenFileDialog();
            this.cmbxOutput1 = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.cmbxModel = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.vScrollBar1 = new System.Windows.Forms.VScrollBar();
            this.vScrollBar2 = new System.Windows.Forms.VScrollBar();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Black;
            this.panel1.Controls.Add(this.vScrollBar2);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.vScrollBar1);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Controls.Add(this.btnOpen2);
            this.panel1.Controls.Add(this.btnOpen1);
            this.panel1.Location = new System.Drawing.Point(14, 103);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(734, 149);
            this.panel1.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(450, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(254, 32);
            this.label3.TabIndex = 8;
            this.label3.Text = "2";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(26, 30);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(254, 32);
            this.label2.TabIndex = 7;
            this.label2.Text = "1";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(283, 62);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(168, 66);
            this.label1.TabIndex = 6;
            this.label1.Text = "DENON\r\nDN-2x00F";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.Color.Black;
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel3.Location = new System.Drawing.Point(454, 62);
            this.panel3.Margin = new System.Windows.Forms.Padding(0, 0, 30, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(250, 26);
            this.panel3.TabIndex = 5;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.Black;
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel2.Location = new System.Drawing.Point(30, 62);
            this.panel2.Margin = new System.Windows.Forms.Padding(30, 0, 0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(250, 26);
            this.panel2.TabIndex = 4;
            // 
            // btnOpen2
            // 
            this.btnOpen2.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.btnOpen2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnOpen2.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnOpen2.ForeColor = System.Drawing.Color.White;
            this.btnOpen2.Location = new System.Drawing.Point(384, 30);
            this.btnOpen2.Margin = new System.Windows.Forms.Padding(0, 0, 30, 0);
            this.btnOpen2.Name = "btnOpen2";
            this.btnOpen2.Size = new System.Drawing.Size(40, 28);
            this.btnOpen2.TabIndex = 3;
            this.btnOpen2.Text = "2";
            this.btnOpen2.UseVisualStyleBackColor = false;
            this.btnOpen2.Click += new System.EventHandler(this.btnOpen2_Click);
            // 
            // btnOpen1
            // 
            this.btnOpen1.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.btnOpen1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnOpen1.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnOpen1.ForeColor = System.Drawing.Color.White;
            this.btnOpen1.Location = new System.Drawing.Point(310, 30);
            this.btnOpen1.Margin = new System.Windows.Forms.Padding(30, 30, 0, 0);
            this.btnOpen1.Name = "btnOpen1";
            this.btnOpen1.Size = new System.Drawing.Size(40, 28);
            this.btnOpen1.TabIndex = 2;
            this.btnOpen1.Text = "1";
            this.btnOpen1.UseVisualStyleBackColor = false;
            this.btnOpen1.Click += new System.EventHandler(this.btnOpen1_Click);
            // 
            // cmbxPort
            // 
            this.cmbxPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbxPort.FormattingEnabled = true;
            this.cmbxPort.Items.AddRange(new object[] {
            "COM1:",
            "COM2:",
            "COM3:",
            "COM4:",
            "COM5:",
            "COM6:",
            "COM7:",
            "COM8:",
            "COM9:",
            "COM10:",
            "COM252:",
            "COM260:"});
            this.cmbxPort.Location = new System.Drawing.Point(113, 35);
            this.cmbxPort.Name = "cmbxPort";
            this.cmbxPort.Size = new System.Drawing.Size(121, 21);
            this.cmbxPort.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(24, 38);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Port:";
            // 
            // btnInit
            // 
            this.btnInit.Location = new System.Drawing.Point(673, 74);
            this.btnInit.Name = "btnInit";
            this.btnInit.Size = new System.Drawing.Size(75, 23);
            this.btnInit.TabIndex = 3;
            this.btnInit.Text = "Init";
            this.btnInit.UseVisualStyleBackColor = true;
            this.btnInit.Click += new System.EventHandler(this.btnInit_Click);
            // 
            // ofd
            // 
            this.ofd.FileName = "openFileDialog1";
            this.ofd.InitialDirectory = "C:\\Users\\Pete\\Documents\\Nerva\\trunk\\driver\\PlayerTest";
            // 
            // cmbxOutput1
            // 
            this.cmbxOutput1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbxOutput1.FormattingEnabled = true;
            this.cmbxOutput1.Location = new System.Drawing.Point(113, 8);
            this.cmbxOutput1.Name = "cmbxOutput1";
            this.cmbxOutput1.Size = new System.Drawing.Size(332, 21);
            this.cmbxOutput1.TabIndex = 4;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(24, 11);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(74, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Sound output:";
            // 
            // cmbxModel
            // 
            this.cmbxModel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbxModel.FormattingEnabled = true;
            this.cmbxModel.Items.AddRange(new object[] {
            "DN-2000F mk II",
            "DN-2500F"});
            this.cmbxModel.Location = new System.Drawing.Point(113, 62);
            this.cmbxModel.Name = "cmbxModel";
            this.cmbxModel.Size = new System.Drawing.Size(121, 21);
            this.cmbxModel.TabIndex = 6;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(24, 65);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(39, 13);
            this.label6.TabIndex = 7;
            this.label6.Text = "Model:";
            // 
            // vScrollBar1
            // 
            this.vScrollBar1.Location = new System.Drawing.Point(6, 30);
            this.vScrollBar1.Name = "vScrollBar1";
            this.vScrollBar1.Size = new System.Drawing.Size(17, 80);
            this.vScrollBar1.TabIndex = 9;
            this.vScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar1_Scroll);
            // 
            // vScrollBar2
            // 
            this.vScrollBar2.Location = new System.Drawing.Point(707, 30);
            this.vScrollBar2.Name = "vScrollBar2";
            this.vScrollBar2.Size = new System.Drawing.Size(17, 80);
            this.vScrollBar2.TabIndex = 9;
            this.vScrollBar2.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar2_Scroll);
            // 
            // txtLog
            // 
            this.txtLog.Location = new System.Drawing.Point(13, 259);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.Size = new System.Drawing.Size(735, 305);
            this.txtLog.TabIndex = 9;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(760, 576);
            this.Controls.Add(this.txtLog);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.cmbxModel);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.cmbxOutput1);
            this.Controls.Add(this.btnInit);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.cmbxPort);
            this.Controls.Add(this.panel1);
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Player Test";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.frmMain_FormClosed);
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button btnOpen2;
        private System.Windows.Forms.Button btnOpen1;
        private System.Windows.Forms.ComboBox cmbxPort;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnInit;
        private System.Windows.Forms.OpenFileDialog ofd;
        private System.Windows.Forms.ComboBox cmbxOutput1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cmbxModel;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.VScrollBar vScrollBar1;
        private System.Windows.Forms.VScrollBar vScrollBar2;
        private System.Windows.Forms.TextBox txtLog;
    }
}

