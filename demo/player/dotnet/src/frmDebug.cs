using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PlayerDemo
{
    public partial class frmDebug : Form
    {
        public frmDebug()
        {
            InitializeComponent();
            FormClosing += delegate (object sender, FormClosingEventArgs e)
            {
                Hide();
                e.Cancel = true;
            };
        }

        public void Log(string Event)
        {
            this.Invoke(new MethodInvoker(() =>
           {
               edLog.AppendText(Event + "\r\n");
           }));
        }
    }
}
