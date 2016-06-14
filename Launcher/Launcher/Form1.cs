using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Management;
using Newtonsoft.Json;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Launcher
{
    public class Evil
    {
        [DllImport("user32.dll")]
        public static extern bool EnumDisplaySettings(
              string deviceName, int modeNum, ref DEVMODE devMode);
        const int ENUM_CURRENT_SETTINGS = -1;

        const int ENUM_REGISTRY_SETTINGS = -2;

        [StructLayout(LayoutKind.Sequential)]

        public struct DEVMODE
        {

            private const int CCHDEVICENAME = 0x20;
            private const int CCHFORMNAME = 0x20;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 0x20)]
            public string dmDeviceName;
            public short dmSpecVersion;
            public short dmDriverVersion;
            public short dmSize;
            public short dmDriverExtra;
            public int dmFields;
            public int dmPositionX;
            public int dmPositionY;
            public ScreenOrientation dmDisplayOrientation;
            public int dmDisplayFixedOutput;
            public short dmColor;
            public short dmDuplex;
            public short dmYResolution;
            public short dmTTOption;
            public short dmCollate;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 0x20)]
            public string dmFormName;
            public short dmLogPixels;
            public int dmBitsPerPel;
            public int dmPelsWidth;
            public int dmPelsHeight;
            public int dmDisplayFlags;
            public int dmDisplayFrequency;
            public int dmICMMethod;
            public int dmICMIntent;
            public int dmMediaType;
            public int dmDitherType;
            public int dmReserved1;
            public int dmReserved2;
            public int dmPanningWidth;
            public int dmPanningHeight;

        }
    }

    public partial class Form1 : Form
    {
        public SettingsData mySettings = new SettingsData();
        public Form1()
        {
            InitializeComponent();

            string fileData = System.IO.File.ReadAllText("Settings.json");
            mySettings = JsonConvert.DeserializeObject<SettingsData>(fileData);

            Evil.DEVMODE vDevMode = new Evil.DEVMODE();
            int i = 0;
            while (Evil.EnumDisplaySettings(null, i, ref vDevMode))
            {
                string resolution = vDevMode.dmPelsWidth.ToString() + "x" + vDevMode.dmPelsHeight.ToString();
                if (resolutionBox.Items.Contains(resolution) == false)
                { 
                    resolutionBox.Items.Add(resolution);
                }
                i++;
            }

            checkBox1.Checked = mySettings.myIsFullscreen;
            resolutionBox.SelectedIndex = resolutionBox.Items.IndexOf(mySettings.myResolutionX.ToString() + "x" + mySettings.myResolutionY.ToString());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            mySettings.myIsFullscreen = checkBox1.Checked;
            int index = 0;

            string resX = resolutionBox.SelectedItem.ToString();
            index = resX.LastIndexOf("x");
            resX = resX.Substring(0, index);
            mySettings.myResolutionX = Convert.ToInt32(resX);

            string resY = resolutionBox.SelectedItem.ToString();
            index = resY.LastIndexOf("x");
            index += 1;
            resY = resY.Substring(index, resY.Length - index);
            mySettings.myResolutionY = Convert.ToInt32(resY);

           /* string sizeX = windowSizeBox.SelectedItem.ToString();
            index = sizeX.LastIndexOf("x");
            sizeX = sizeX.Substring(0, index);
            settings.myWindowSizeX = Convert.ToInt32(sizeX);

            string sizeY = windowSizeBox.SelectedItem.ToString();
            index = sizeY.LastIndexOf("x");
            index += 1;
            sizeY = sizeY.Substring(index, sizeY.Length - index);
            settings.myWindowSizeY = Convert.ToInt32(sizeY);*/

            string jsonString = JsonConvert.SerializeObject(mySettings, Formatting.Indented);
            System.IO.File.WriteAllText(Directory.GetCurrentDirectory() + "/" + "Settings.json", jsonString);
            string exePath = "";
            exePath = Directory.GetCurrentDirectory();
            exePath += "\\Launcher_DevMode.exe";
            Process.Start(exePath);
            Application.Exit();
        }

       /* private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBox1.Checked == false)
            {
                windowSizeBox.Enabled = true;
            }
            else
            {
                windowSizeBox.Enabled = false;
            }
        }*/
    }
}
