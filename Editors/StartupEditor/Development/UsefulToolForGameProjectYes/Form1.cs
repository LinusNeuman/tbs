using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UsefulToolForGameProjectYes
{
    public enum eGameState
    {
        eMainMenu,
        eInGame,
        eLevelSelect,
        ePauseMenu,
        eOptionsMenu,
        eCredits
    }

    public partial class GameSettings : Form
    {
        

        public GameSettings()
        {
            InitializeComponent();
            

            ToolTip.SetToolTip(this.GroupBoxDebug, "Location originates in Bin, not C");
            ToolTip.SetToolTip(this.TextBoxDebuglogsDirectory, "Location originates in Bin, not C");
            ToolTip.SetToolTip(this.LabelDebugDirectory, "Location originates in Bin, not C");

            mySetup = new GameSetup();
            InitResolution();
        }

        void InitResolution()
        {
            Resolution tempSelected = new Resolution(1920, 1080);
            ComboBoxResolution.Items.Add(tempSelected);
            ComboBoxResolution.Items.Add(new Resolution(600, 800));
            ComboBoxResolution.SelectedItem = tempSelected;
        }

        private void SaveGameSettingsToFile(string aFilePath)
        {
            mySetup.DebugFolderLocation = TextBoxDebuglogsDirectory.Text;
            string output = JsonConvert.SerializeObject(mySetup, Formatting.Indented);
            System.IO.File.WriteAllText(aFilePath, output);
        }

        private void LoadGameSettingsFromFile(string aFilePath)
        {
            string input = System.IO.File.ReadAllText(aFilePath);
            mySetup = JsonConvert.DeserializeObject<GameSetup>(input);

           
            
            ComboBoxResolution.SelectedItem = mySetup.ResolutionSettings;
            ComboBoxResolution.Refresh();
            CheckBoxFullscreen.Checked = mySetup.IsFullscreen;
            CheckBoxSkipIntro.Checked = mySetup.SkipIntro;
            CheckBoxSkipSplashScreen.Checked = mySetup.SkipSplashscreen;
            CheckBoxMute.Checked = mySetup.MuteAllSounds;
            CheckBoxCreateDebugLogs.Checked = mySetup.CreateDebugLogs;
            TextBoxDebuglogsDirectory.Text = mySetup.DebugFolderLocation;
            switch ((eGameState)mySetup.StartingGameState)
            {
                case eGameState.eMainMenu:
                    RadioButtonGamestateMenu.Checked = true;
                    break;
                case eGameState.eInGame:
                    RadioButtonGamestateInGame.Checked = true;
                    break;
                case eGameState.eLevelSelect:
                    RadioButtonLevelSelect.Checked = true;
                    break;
                case eGameState.ePauseMenu:
                    RadioButtonGamestatePauseMenu.Checked = true;
                    break;
                case eGameState.eOptionsMenu:
                    RadioButtonGamestateOptionsMenu.Checked = true;
                    break;
                case eGameState.eCredits:
                    RadioButtonGamestateCredits.Checked = true;
                    break;
            }

        }

        private void ComboBoxResolution_SelectedIndexChanged(object sender, EventArgs e)
        {
            mySetup.ResolutionSettings = ComboBoxResolution.SelectedItem as Resolution;
        }

        private void CheckBoxFullscreen_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.IsFullscreen = CheckBoxFullscreen.Checked;
        }

        private void CheckBoxSkipIntro_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.SkipIntro = CheckBoxSkipIntro.Checked;
        }

        private void CheckBoxSkipSplashScreen_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.SkipSplashscreen = CheckBoxSkipSplashScreen.Checked;
        }

        private void CheckBoxMute_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.MuteAllSounds = CheckBoxMute.Checked;
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog tempSaveFileDialog = new SaveFileDialog();
            string folderPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\JSON";
            System.IO.Directory.CreateDirectory(folderPath);
            tempSaveFileDialog.InitialDirectory = folderPath;
            tempSaveFileDialog.Filter = "Json Files(*.json) | *.json";
            tempSaveFileDialog.ShowDialog(this);

            if (tempSaveFileDialog.FileName != "")
            {
                mySetup.StartingGameState = (int)GetSelectedGameState();
                SaveGameSettingsToFile(tempSaveFileDialog.FileName);
            }
        }


        private void buttonLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog tempLoadFileDialog = new OpenFileDialog();
            string folderPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\JSON";
            System.IO.Directory.CreateDirectory(folderPath);
            tempLoadFileDialog.InitialDirectory = folderPath;
            tempLoadFileDialog.RestoreDirectory = false;
            tempLoadFileDialog.Filter = "Json Files(*.json) | *.json";
            tempLoadFileDialog.ShowDialog(this);

            if (tempLoadFileDialog.FileName != "")
            {
                LoadGameSettingsFromFile(tempLoadFileDialog.FileName);
            }
        }

        private eGameState GetSelectedGameState()
        {
            if (RadioButtonGamestateMenu.Checked == true)
            {
                return eGameState.eMainMenu;
            }
            else if (RadioButtonGamestateInGame.Checked == true)
            {
                return eGameState.eInGame;
            }
            else if (RadioButtonLevelSelect.Checked == true)
            {
                return eGameState.eLevelSelect;
            }
            else if (RadioButtonGamestatePauseMenu.Checked == true)
            {
                return eGameState.ePauseMenu;
            }
            else if (RadioButtonGamestateOptionsMenu.Checked == true)
            {
                return eGameState.eOptionsMenu;
            }
            else
            {
                return eGameState.eCredits;
            }
        }

        private void ButtonHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Hello!\n\nIf you think something is missing or that something is confusing among the options here, go tell your friendly neighborhood programmers about it, and we will modify the tool according to feedback.");
        }
        private GameSetup mySetup;
    }
}
