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
            resolutionBox.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SettingsData settings = new SettingsData();
            settings.myIsFullscreen = checkBox1.Checked;
            int index = 0;

            string x = resolutionBox.SelectedItem.ToString();
            index = x.LastIndexOf("x");
            x = x.Substring(0, index);
            settings.myResolutionX = Convert.ToInt32(x);

            string y = resolutionBox.SelectedItem.ToString();
            index = y.LastIndexOf("x");
            index += 1;
            y = y.Substring(index, y.Length - index);
            settings.myResolutionY = Convert.ToInt32(y);

            string jsonString = JsonConvert.SerializeObject(settings, Formatting.Indented);
            System.IO.File.WriteAllText(Directory.GetCurrentDirectory() + "/" + "Settings.json", jsonString);
            string exePath = "";
            exePath = Directory.GetCurrentDirectory();
            /*index = exePath.IndexOf("Bin");
            exePath = exePath.Substring(0, index);*/
            exePath += "\\Launcher_Release.exe";
            Process.Start(exePath);
            Application.Exit();
        }
    }
}
