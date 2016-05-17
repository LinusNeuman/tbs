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

namespace Object_Editor
{
    public partial class MainForm : Form
    {
        string myRootSerialized = "";//"{\"Gadgets\": [ ";
        string myGadgetSerialized = "";
        string myOpenJSONData;
        List<Gadget> myGadgetList = new List<Gadget>();
        public MainForm()
        {
            InitializeComponent();
            APCostComboBox.SelectedIndex = 0;
            LevelComboBox.SelectedIndex = 0;
            DamageComboBox.SelectedIndex = 0;
        }

        void RefreshList(ListBox aListbox)
        {
            aListbox.DisplayMember = "";
            aListbox.DisplayMember = "Name";
        }

        private void OpenFileItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = "Json Files (.json)|*.json|All Files (*.*)|*.*";
            open.FilterIndex = 1;
            string pathDefault = System.IO.Directory.GetCurrentDirectory();
            open.InitialDirectory = pathDefault;
            open.ShowDialog();
            if (open.FileName != "")
            {
                string path = open.FileName;
                using (System.IO.FileStream fs = System.IO.File.OpenRead(path))
                {
                    byte[] info = new byte[1024];
                    UTF8Encoding temp = new UTF8Encoding(true);
                    while (fs.Read(info, 0, info.Length) > 0)
                    {
                        myOpenJSONData = temp.GetString(info);
                    }
                }
                var deserializedRootFromRoot = JsonConvert.DeserializeObject<Root>(myOpenJSONData);
                GadgetListBox.Items.Clear();
                for (int i = 0; i < deserializedRootFromRoot.Gadgets.Count(); i++)
                {
                    GadgetListBox.Items.Add(deserializedRootFromRoot.Gadgets.ElementAt(i));
                    myGadgetList.Add(deserializedRootFromRoot.Gadgets.ElementAt(i));
                }
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();
            save.Filter = "Json Files (.json)|*.json|All Files (*.*)|*.*";
            save.FilterIndex = 1;
            string pathDefault = System.IO.Directory.GetCurrentDirectory();
            save.InitialDirectory = pathDefault;
            save.ShowDialog();
            if(save.FileName != "")
            {
                var root = new Root() { Gadgets = myGadgetList };
                myRootSerialized += JsonConvert.SerializeObject(root, Formatting.Indented);
                string path = save.FileName;
                if(System.IO.File.Exists(path))
                {
                    System.IO.File.Delete(path);
                }
                using (System.IO.FileStream fileStream = System.IO.File.Create(path))
                {
                    byte[] info = new UTF8Encoding(true).GetBytes(myRootSerialized);
                    fileStream.Write(info, 0, info.Length);
                }      
            }
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            if(NameTextBox.Text == "")
            {
                MessageBox.Show("Please name your gadget");
                return;
            }
            Gadget gadget = new Gadget();
            UpdateGadgetValues(gadget);
            GadgetListBox.Items.Add(gadget);
            myGadgetList.Add(gadget);
        }

        private void GadgetListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            Gadget gadget = GadgetListBox.SelectedItem as Gadget;
            if(gadget != null)
            {
                UpdateInterfaceValues(gadget);
            }
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {     
            Gadget gadget = GadgetListBox.SelectedItem as Gadget;
            if(gadget != null)
            {
                UpdateGadgetValues(gadget);
            }
            RefreshList(GadgetListBox);
        }

        private void DoesDamageCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if(DoesDamageCheckBox.Checked == true)
            {
                DamageLabel.Visible = true;
                DamageComboBox.Visible = true;
            }
            else
            {
                DamageLabel.Visible = false;
                DamageComboBox.Visible = false;
            }
        }

        private void UpdateGadgetValues(Gadget aGadget)
        {
            aGadget.Name = NameTextBox.Text;
            aGadget.Cost = Convert.ToInt32(APCostComboBox.GetItemText(APCostComboBox.SelectedItem));
            aGadget.Level = LevelComboBox.GetItemText(LevelComboBox.SelectedItem);
            aGadget.DoesDamage = DoesDamageCheckBox.Checked;
            aGadget.Damage = Convert.ToInt32(DamageComboBox.GetItemText(DamageComboBox.SelectedItem));
        }
        private void UpdateInterfaceValues(Gadget aGadget)
        {
            NameTextBox.Text = aGadget.Name;
            APCostComboBox.SelectedItem = aGadget.Cost.ToString();
            LevelComboBox.SelectedItem = aGadget.Level;
            DoesDamageCheckBox.Checked = aGadget.DoesDamage;
            DamageComboBox.SelectedItem = aGadget.Damage.ToString();
        }

        private void RemoveButton_Click(object sender, EventArgs e)
        {
            GadgetListBox.Items.Remove(GadgetListBox.SelectedItem);
            myGadgetList.Remove(GadgetListBox.SelectedItem as Gadget);
        }

        private void NameTextBox_TextChanged(object sender, EventArgs e)
        {
            string oldText = string.Empty;
            if (NameTextBox.Text.All(chr => char.IsLetter(chr)))
            {
                oldText = NameTextBox.Text;
                NameTextBox.Text = oldText;
            }
            else
            {
                NameTextBox.Text = oldText;
                MessageBox.Show("Gadget name only allows letters");
            }
            NameTextBox.SelectionStart = NameTextBox.Text.Length;
        }

    }
}
