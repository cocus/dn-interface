namespace monitor
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
            this.components = new System.ComponentModel.Container();
            this.cmbxRemote = new System.Windows.Forms.ComboBox();
            this.txtLog = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cmbxPlayer = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.edBaud = new System.Windows.Forms.TextBox();
            this.chkActive = new System.Windows.Forms.CheckBox();
            this.RemotePort = new System.IO.Ports.SerialPort(this.components);
            this.PlayerPort = new System.IO.Ports.SerialPort(this.components);
            this.edPacket = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnListen = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // cmbxRemote
            // 
            this.cmbxRemote.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbxRemote.FormattingEnabled = true;
            this.cmbxRemote.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4",
            "COM5",
            "COM6",
            "COM7",
            "COM8",
            "COM9",
            "COM10"});
            this.cmbxRemote.Location = new System.Drawing.Point(91, 13);
            this.cmbxRemote.Margin = new System.Windows.Forms.Padding(4);
            this.cmbxRemote.Name = "cmbxRemote";
            this.cmbxRemote.Size = new System.Drawing.Size(180, 27);
            this.cmbxRemote.TabIndex = 2;
            // 
            // txtLog
            // 
            this.txtLog.Location = new System.Drawing.Point(16, 151);
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.Size = new System.Drawing.Size(615, 398);
            this.txtLog.TabIndex = 3;
            this.txtLog.Text = "";
            this.txtLog.WordWrap = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 19);
            this.label1.TabIndex = 4;
            this.label1.Text = "Remote:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 51);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 19);
            this.label2.TabIndex = 6;
            this.label2.Text = "Player:";
            // 
            // cmbxPlayer
            // 
            this.cmbxPlayer.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbxPlayer.FormattingEnabled = true;
            this.cmbxPlayer.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4",
            "COM5",
            "COM6",
            "COM7",
            "COM8",
            "COM9",
            "COM10"});
            this.cmbxPlayer.Location = new System.Drawing.Point(91, 48);
            this.cmbxPlayer.Margin = new System.Windows.Forms.Padding(4);
            this.cmbxPlayer.Name = "cmbxPlayer";
            this.cmbxPlayer.Size = new System.Drawing.Size(180, 27);
            this.cmbxPlayer.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(338, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(54, 19);
            this.label3.TabIndex = 7;
            this.label3.Text = "Baud:";
            // 
            // edBaud
            // 
            this.edBaud.Location = new System.Drawing.Point(416, 12);
            this.edBaud.Name = "edBaud";
            this.edBaud.Size = new System.Drawing.Size(180, 26);
            this.edBaud.TabIndex = 8;
            this.edBaud.Text = "76780";
            // 
            // chkActive
            // 
            this.chkActive.AutoSize = true;
            this.chkActive.Location = new System.Drawing.Point(514, 76);
            this.chkActive.Name = "chkActive";
            this.chkActive.Size = new System.Drawing.Size(82, 23);
            this.chkActive.TabIndex = 9;
            this.chkActive.Text = "Active";
            this.chkActive.UseVisualStyleBackColor = true;
            // 
            // RemotePort
            // 
            this.RemotePort.ReadBufferSize = 512;
            this.RemotePort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.RemotePort_DataReceived);
            // 
            // PlayerPort
            // 
            this.PlayerPort.ReadBufferSize = 512;
            this.PlayerPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.PlayerPort_DataReceived);
            // 
            // edPacket
            // 
            this.edPacket.Location = new System.Drawing.Point(416, 44);
            this.edPacket.Name = "edPacket";
            this.edPacket.Size = new System.Drawing.Size(180, 26);
            this.edPacket.TabIndex = 11;
            this.edPacket.Text = "13";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(338, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 19);
            this.label4.TabIndex = 10;
            this.label4.Text = "Packet:";
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(521, 105);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 27);
            this.btnClear.TabIndex = 12;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnListen
            // 
            this.btnListen.Location = new System.Drawing.Point(416, 76);
            this.btnListen.Name = "btnListen";
            this.btnListen.Size = new System.Drawing.Size(75, 27);
            this.btnListen.TabIndex = 13;
            this.btnListen.Text = "Listen";
            this.btnListen.UseVisualStyleBackColor = true;
            this.btnListen.Click += new System.EventHandler(this.btnListen_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 19F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(639, 561);
            this.Controls.Add(this.btnListen);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.edPacket);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.chkActive);
            this.Controls.Add(this.edBaud);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cmbxPlayer);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtLog);
            this.Controls.Add(this.cmbxRemote);
            this.Font = new System.Drawing.Font("Consolas", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "frmMain";
            this.Text = "Packet Monitor";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cmbxRemote;
        private System.Windows.Forms.RichTextBox txtLog;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cmbxPlayer;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox edBaud;
        private System.Windows.Forms.CheckBox chkActive;
        private System.IO.Ports.SerialPort RemotePort;
        private System.IO.Ports.SerialPort PlayerPort;
        private System.Windows.Forms.TextBox edPacket;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnListen;
    }
}

