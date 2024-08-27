using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Un4seen.Bass;
using static PlayerDemo.Native;

namespace PlayerDemo
{
    public partial class frmMain : Form
    {
        Deck[] Decks;

        frmDebug _frmdebug;

        public frmMain()
        {
            InitializeComponent();

            foreach (var d in Bass.BASS_GetDeviceInfos())
                cmbxOutput1.Items.Add(d.name);

            cmbxOutput1.SelectedIndex = cmbxOutput1.Items.Count - 1;
            cmbxPort.SelectedIndex = 6;
            cmbxModel.SelectedIndex = 1;

        }
        public void Log(string Event)
        {
            this.Invoke(new MethodInvoker(() =>
            {
                txtLog.AppendText(Event + "\r\n");
            }));
        }
        private void PitchChangeHandler(byte Deck, float Pitch)
        {
            Log(string.Format("Deck {0}. Pitch change. New Pitch: {1}%", Deck, Pitch));
            if ((Deck == 1) || (Deck == 2))
                Decks[Deck - 1].ChangePitch(Pitch);
        }

        private void TimeModeHandler(byte Deck, byte Mode)
        {
            Log(string.Format("Deck {0}. Time mode change. New Mode: {1}", Deck, Mode == 1 ? "Elapsed" : "Remain"));
            if ((Deck == 1) || (Deck == 2))
                Decks[Deck - 1].ChangeTime(Mode);        
        }

        private void PlayPauseHandler(byte Deck, bool IsPlaying, bool EnableBreak)
        {
            Log(string.Format("Deck {0}. Play/Pause, playing? {1}, break? {2}", Deck, IsPlaying, EnableBreak));
            if ((Deck == 1) || (Deck == 2))
                Decks[Deck - 1].PlayPause();
        }

        private void CueHandler(byte Deck)
        {
            Log(string.Format("Deck {0}. Cue", Deck));
            if ((Deck == 1) || (Deck == 2))
            {
                if (Decks[Deck-1].IsCueing == false)
                    Decks[Deck - 1].Cue();
            }
        }

        private void SearchHandler(byte Deck, byte Direction, byte Speed)
        {
            Log(string.Format("Deck {0}. SearchHandler, {1} {2}", Deck, Direction, Speed));
            if ((Deck == 1) || (Deck == 2))
                Decks[Deck - 1].Search(Direction, Speed);
        }

        private void ScanHandler(byte Deck, byte Direction, byte Speed)
        {
            Log(string.Format("Deck {0}. Scan change. New Direction: {1}, Speed: {2}", Deck, Direction, Speed));
            if ((Deck == 1) || (Deck == 2))
                Decks[Deck - 1].Scan(Direction, Speed);
        }

        private void OpenCloseHandler(byte Deck)
        {
            Log(string.Format("Deck {0}. Open/Close", Deck));
        }

        private void TrackChangeHandler(byte Deck, byte To)
        {
            Log(string.Format("Deck {0}. Track change, to {1}", Deck, To));
        }

        private void IndexChangeHandler(byte Deck, byte To, byte Direction)
        {
            Log(string.Format("Deck {0}. Index change, to {1}, direction {2}", Deck, To, Direction));
        }

        private void ReverseHandler(byte Deck)
        {
            Log(string.Format("Deck {0}. Reverse", Deck));
        }

        private void PlayModeChangeHandler(byte Deck, byte Mode)
        {
            Log(string.Format("Deck {0}. Play mode changed to {1}", Deck, Mode));
        }

        private void VoiceReducerChangeHandler(byte Deck, bool Enabled)
        {
            Log(string.Format("Deck {0}. Voice reducer set to {1}", Deck, Enabled));
        }


        private void KeyChangeHandler(byte Deck, byte Mode, float Key)
        {
            Log(string.Format("Deck {0}. Key changed to {2}, mode {1}", Deck, Mode, Key));
        }

        private void btnInit_Click(object sender, EventArgs e)
        {
            var res = Native.Init((string)cmbxPort.SelectedItem, (byte)cmbxModel.SelectedIndex);

            Log(String.Format("Init({0}, {1}) = {2}", cmbxPort.SelectedItem, cmbxModel.SelectedIndex, res));

            if (res != 0)
                return;

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
            Native.SetOpenCloseCallback(OpenCloseHandler);
            Native.SetTrackChangeCallback(TrackChangeHandler);
            Native.SetIndexChangeCallback(IndexChangeHandler);
            Native.SetReverseCallback(ReverseHandler);
            Native.SetPlayModeChangeCallback(PlayModeChangeHandler);
            Native.SetVoiceReducerChangeCallback(VoiceReducerChangeHandler);
            Native.SetKeyChangeCallback(KeyChangeHandler);

            cmbxOutput1.Enabled = false;
            cmbxPort.Enabled = false;
            cmbxModel.Enabled = false;
            btnInit.Enabled = false;

            //Native.UpdateTime(1, 11, 22, 33);
            //Native.UpdateTime(2, 11, 22, 33);
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
                Decks[0].Dispose();
                Decks[1].Dispose();
                Decks[0] = null;
                Decks[1] = null;

                var res = Native.DeInit();
            }
        }

        private void btnLog_Click(object sender, EventArgs e)
        {
            _frmdebug.Show();            
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            Decks[0].Volume(vScrollBar1.Value / 100.0f);
        }

        private void vScrollBar2_Scroll(object sender, ScrollEventArgs e)
        {
            Decks[1].Volume(vScrollBar1.Value / 100.0f);
        }
    }
}
