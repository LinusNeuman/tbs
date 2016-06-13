using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.IO;
using System.Diagnostics;

namespace Launcher
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            resolutionBox.Items.Add("1920x1080");
            resolutionBox.Items.Add("1680x1050");
            resolutionBox.Items.Add("1280x800");
            resolutionBox.Items.Add("1024x768");
            resolutionBox.Items.Add("800x600");

            windowSizeBox.Items.Add("1920x1080");
            windowSizeBox.Items.Add("1680x1050");
            windowSizeBox.Items.Add("1280x800");
            windowSizeBox.Items.Add("1024x768");
            windowSizeBox.Items.Add("800x600");

            windowSizeBox.SelectedIndex = 0;
            resolutionBox.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SettingsData settings = new SettingsData();
            settings.myIsFullscreen = checkBox1.Checked;
            int index = 0;

            string resX = resolutionBox.SelectedItem.ToString();
            index = resX.LastIndexOf("x");
            resX = resX.Substring(0, index);
            settings.myResolutionX = Convert.ToInt32(resX);

            string resY = resolutionBox.SelectedItem.ToString();
            index = resY.LastIndexOf("x");
            index += 1;
            resY = resY.Substring(index, resY.Length - index);
            settings.myResolutionY = Convert.ToInt32(resY);

            string sizeX = windowSizeBox.SelectedItem.ToString();
            index = sizeX.LastIndexOf("x");
            sizeX = sizeX.Substring(0, index);
            settings.myWindowSizeX = Convert.ToInt32(sizeX);

            string sizeY = windowSizeBox.SelectedItem.ToString();
            index = sizeY.LastIndexOf("x");
            index += 1;
            sizeY = sizeY.Substring(index, sizeY.Length - index);
            settings.myWindowSizeY = Convert.ToInt32(sizeY);

            string jsonString = JsonConvert.SerializeObject(settings, Formatting.Indented);
            System.IO.File.WriteAllText(Directory.GetCurrentDirectory() + "/" + "Settings.json", jsonString);
            string exePath = "";
            exePath = Directory.GetCurrentDirectory();
            exePath += "\\Launcher_DevMode.exe";
            Process.Start(exePath);
            Application.Exit();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBox1.Checked == false)
            {
                windowSizeBox.Enabled = true;
            }
            else
            {
                windowSizeBox.Enabled = false;
            }
        }
    }
}
