using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Un4seen.Bass;

namespace PlayerDemo
{
    public partial class frmMain : Form
    {
        Deck[] Decks;

        frmDebug _frmdebug;

        public frmMain()
        {
            InitializeComponent();

            cmbxPort.SelectedIndex = 6;

            foreach (var d in Bass.BASS_GetDeviceInfos())
                cmbxOutput1.Items.Add(d.name);

            _frmdebug = new frmDebug();
            _frmdebug.VisibleChanged += delegate (object sender, EventArgs e)
            {
                btnLog.Enabled = !_frmdebug.Visible;
            };

        }


        private void PitchChangeHandler(byte Deck, float Pitch)
        {
            _frmdebug.Log(string.Format("Deck {0}. Pitch change. New Pitch: {1}%", Deck, Pitch));
        //    Decks[Deck - 1].ChangePitch(Pitch);
        }

        private void TimeModeHandler(byte Deck, byte Mode)
        {
            _frmdebug.Log(string.Format("Deck {0}. Time mode change. New Mode: {1}", Deck, Mode == 1 ? "Elapsed" : "Remain"));
          //  Decks[Deck - 1].ChangeTime(Mode);        
        }

        private void PlayPauseHandler(byte Deck)
        {
            _frmdebug.Log(string.Format("Deck {0}. Play/Pause", Deck));
            // Decks[Deck - 1].PlayPause();
        }

        private void CueHandler(byte Deck)
        {

           // Decks[Deck - 1].Cue();
        }

        private void ScanHandler(byte Deck, byte Direction, byte Speed)
        {
            _frmdebug.Log(string.Format("Deck {0}. Scan change. New Direction: {1}, Speed: {2}", Deck, Direction, Speed));
            // Decks[Deck - 1].Scan(Direction, Speed);
        }

        private void SearchHandler(byte Deck, byte Direction, byte Speed)
        {
          //  Decks[Deck - 1].Search(Direction, Speed);
        }
      
        private void btnInit_Click(object sender, EventArgs e)
        {
            var res = Native.Init((string)cmbxPort.SelectedItem, (byte)cmbxModel.SelectedIndex);

            Bass.BASS_Init(cmbxOutput1.SelectedIndex, 44100, BASSInit.BASS_DEVICE_DEFAULT, IntPtr.Zero);          

            Decks = new Deck[2];
            Decks[0] = new Deck(1);
            Decks[1] = new Deck(2);            

            Native.SetPitchChangeCallback(PitchChangeHandler);
            Native.SetTimeModeCallback(TimeModeHandler);
            Native.SetPlayPauseCallback(PlayPauseHandler);
            Native.SetCueCallback(CueHandler);
            Native.SetSearchCallback(SearchHandler);
            Native.SetScanCallback(ScanHandler);

            cmbxOutput1.Enabled = false;
            cmbxPort.Enabled = false;
            btnInit.Enabled = false;

            Native.UpdateTime(1, 11, 22, 33);
        }
       
        private void btnOpen1_Click(object sender, EventArgs e)
        {
            if (btnInit.Enabled)
            {
                MessageBox.Show("Init first!", "Information", MessageBoxButtons.OK);
                return;
            }

            if (ofd.ShowDialog() == DialogResult.OK)
                Decks[0].LoadTrack(ofd.FileName);
        }

        private void btnOpen2_Click(object sender, EventArgs e)
        {
            if (btnInit.Enabled)
            {
                MessageBox.Show("Init first!", "Information", MessageBoxButtons.OK);
                return;
            }

            if (ofd.ShowDialog() == DialogResult.OK)
                Decks[1].LoadTrack(ofd.FileName);
        }

        private void frmMain_Load(object sender, EventArgs e)
        {

        }

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (Decks != null)
            {
                Decks[0]._time_ev.Set();
                Decks[1]._time_ev.Set();
            }
        }

        private void btnLog_Click(object sender, EventArgs e)
        {
            _frmdebug.Show();            
        }
    }
}
