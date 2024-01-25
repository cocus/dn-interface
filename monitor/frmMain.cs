using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace monitor
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        public enum Source
        {
            Remote,
            Player
        }

        public delegate void PacketReceived(string Data);

        public class ReadBuffer
        {
            byte[] _buffer;
            int _offset = 0;
            int _totalread = 0;

            public PacketReceived PacketReceived { get; set; }

            public ReadBuffer(int Size)
            {
                _buffer = new byte[Size];
            }

            public void Reset()
            {
                _offset = 0;
                _totalread = 0;
            }

            public void ReadFromSerial(SerialPort SerialPort)
            {
                while (SerialPort.IsOpen && SerialPort.BytesToRead > 0)
                {
                    int read = SerialPort.Read(_buffer, _offset, _buffer.Length - _totalread);

                    _offset = _offset + read;

                    _totalread = _totalread + read;

                    if (_totalread == _buffer.Length)
                    {
                        PacketReceived?.Invoke(string.Join(" ", _buffer.Select(t => t.ToString("X2"))));
                        Reset();
                    }
                }
            }
        }

        ReadBuffer _remotebuffer;
        ReadBuffer _playerbuffer;

        private void RemotePort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
           if (RemotePort.IsOpen)
                _remotebuffer.ReadFromSerial(RemotePort);
        }

        private void PlayerPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (PlayerPort.IsOpen)
                _playerbuffer.ReadFromSerial(PlayerPort);
        }       

        private void frmMain_Load(object sender, EventArgs e)
        {
            cmbxRemote.SelectedItem = "COM3";
            cmbxPlayer.SelectedItem = "COM6";
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtLog.Clear();
        }

        private void btnListen_Click(object sender, EventArgs e)
        {
            RemotePort.PortName = Convert.ToString(cmbxRemote.SelectedItem);
            RemotePort.BaudRate = Convert.ToInt32(edBaud.Text);
            PlayerPort.PortName = Convert.ToString(cmbxPlayer.SelectedItem);
            PlayerPort.BaudRate = Convert.ToInt32(edBaud.Text);

            RemotePort.DataReceived += RemotePort_DataReceived;
            PlayerPort.DataReceived += PlayerPort_DataReceived;

            _remotebuffer = new ReadBuffer(Convert.ToInt32(edPacket.Text));
            _remotebuffer.PacketReceived = delegate (string Data)
            {
                if (chkActive.Checked)
                {
                    Invoke(new MethodInvoker(delegate
                    {
                        txtLog.SelectionColor = System.Drawing.Color.Red;
                        txtLog.AppendText(string.Format("Remote: {0}\r\n", Data));
                        txtLog.ScrollToCaret();
                    }));
                }
            };

            _playerbuffer = new ReadBuffer(Convert.ToInt32(edPacket.Text));
            _playerbuffer.PacketReceived = delegate (string Data)
            {
                if (chkActive.Checked)
                {
                    Invoke(new MethodInvoker(delegate
                    {
                        txtLog.SelectionColor = System.Drawing.Color.Blue;
                        txtLog.AppendText(string.Format("Player: {0}\r\n", Data));
                        txtLog.ScrollToCaret();
                    }));
                }
            };

            RemotePort.Open();
            PlayerPort.Open();
        }
    }
}
