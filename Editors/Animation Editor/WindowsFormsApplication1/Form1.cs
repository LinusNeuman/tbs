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

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Timer myAnimationTimer = new Timer();
        private Animation myAnimation = new Animation();
        OpenFileDialog fileExplorer = new OpenFileDialog();
        SaveFileDialog saveExplorer = new SaveFileDialog();
        KUtility.DDSImage ddsImage;
        
        public Form1()
        {
            InitializeComponent();
            myAnimationTimer.Tick += AnimationTimerTick;
            myAnimationTimer.Interval = 10;
        }

        private void BrowseButton_Click(object sender, EventArgs e)
        {
            fileExplorer.InitialDirectory = Path.GetFullPath("../../../../../TBSA/Bin/Sprites/");
            fileExplorer.Filter = "DDS (*.dds)|*.dds";

            if (fileExplorer.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                KUtility.DDSImage image = new KUtility.DDSImage(File.ReadAllBytes(fileExplorer.FileName));
                SpriteSheet.Image = image.images[0];
                SpriteX.Text = "X: " + SpriteSheet.Image.Width;
                SpriteY.Text = "Y: " + SpriteSheet.Image.Height;

                if(SpriteSheet.Image.Width > SpriteSheet.Width)
                {
                    int xDifference = SpriteSheet.Image.Width - SpriteSheet.Width; ;
                    int yDifference = 0;
                    if(SpriteSheet.Image.Height > SpriteSheet.Height)
                    {
                        yDifference = SpriteSheet.Image.Height - SpriteSheet.Height;
                    }
                    
                    if(xDifference >= yDifference)
                    {
                        Size newSize = new Size(SpriteSheet.Width, SpriteSheet.Height);
                        Bitmap newImage = new Bitmap(SpriteSheet.Image, newSize);
                        SpriteSheet.Image = newImage;
                    }
                }
                ImagePathText.Text = fileExplorer.FileName;
                int index = ImagePathText.Text.LastIndexOf("Bin\\");
                if (index > -1)
                {
                    string tempString = ImagePathText.Text.Substring(index + 4, ImagePathText.Text.Length - (index + 4));
                    ImagePathText.Text = tempString;
                }
            }
        }

        private void AnimationTimerTick(object sender, EventArgs e)
        {
            int frame = myAnimation.myCurrentFrame;
            myAnimation.Update(myAnimationTimer.Interval);
            if (frame != myAnimation.myCurrentFrame)
            { 
                AnimationViewer.Refresh();
            }
            else
            {
                //AnimationViewer.Paint(sender, e);
            }
            FrameLabel.Text = "Current Frame: " + (myAnimation.myCurrentFrame + 1);
            RowLabel.Text = "Current Row: " + (myAnimation.myCurrentRow + 1);
            ColumnLabel.Text = "Current Column: " + (myAnimation.myCurrentColumn);
        }

        private void Frames_TextChanged(object sender, EventArgs e)
        {
            if(Frames.Text != "")
            {
                StartFrame.Items.Clear();
                EndFrame.Items.Clear();
                for(int i = 1; i <= Convert.ToInt32(Frames.Text); i++)
                {
                    StartFrame.Items.Add(i.ToString());
                    EndFrame.Items.Add(i.ToString());
                }
                StartFrame.Text = "1";
                EndFrame.Text = Frames.Text;
            }
            else
            {
                StartFrame.Text = "";
                EndFrame.Text = "";
            }
        }

        private void PlayButton_Click(object sender, EventArgs e)
        {
            if(AnimationNameText.Text != "" && ImagePathText.Text != "" && SizeXText.Text != "" &&
                    SizeYText.Text != "" && ColumnsText.Text != "" && RowsText.Text != "" &&
                    Frames.Text != "" && FPSText.Text != "" && StartFrame.Text != "" && EndFrame.Text != "")
            {
                myAnimationTimer.Start();
                myAnimation.Initialize(AnimationNameText.Text, ImagePathText.Text, Convert.ToInt32(SizeXText.Text)
                    , Convert.ToInt32(SizeYText.Text), Convert.ToInt32(ColumnsText.Text), Convert.ToInt32(RowsText.Text)
                    , Convert.ToInt32(Frames.Text), Convert.ToInt32(FPSText.Text),Convert.ToInt32(StartFrame.Text)
                    , Convert.ToInt32(EndFrame.Text), ShouldLoop.Checked, Interruptible.Checked
                    , InTransitionText.Text, OutTransitionText.Text);
                myAnimation.myAnimationData.Name = AnimationNameText.Text;
                myAnimation.myAnimationData.FilePath = ImagePathText.Text;
                myAnimation.myAnimationData.SizeX = Convert.ToInt32(SizeXText.Text);
                myAnimation.myAnimationData.SizeY = Convert.ToInt32(SizeYText.Text);
                myAnimation.myAnimationData.AmountOfColumns = Convert.ToInt32(ColumnsText.Text);
                myAnimation.myAnimationData.AmountOfRows = Convert.ToInt32(RowsText.Text);
                myAnimation.myAnimationData.AmountOfFrames = Convert.ToInt32(Frames.Text);
                myAnimation.myAnimationData.AnimationSpeed = Convert.ToInt32(FPSText.Text);
                myAnimation.myAnimationData.LoopStart = Convert.ToInt32(StartFrame.Text);
                myAnimation.myAnimationData.LoopEnd = Convert.ToInt32(EndFrame.Text); 
                myAnimation.myAnimationData.ShouldLoop = ShouldLoop.Checked;
                myAnimation.myAnimationData.IsInterruptible = Interruptible.Checked;
                myAnimation.myAnimationData.InTransition = InTransitionText.Text;
                myAnimation.myAnimationData.OutTransition = OutTransitionText.Text;
            }
            else
            {
                MessageBox.Show("You need to fill in all the necessary information.");
            }
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            myAnimation.StopAnimation();
        }

        private void AnimationViewer_Paint(object sender, PaintEventArgs e)
        {
            if (SpriteSheet.Image != null)
            {
                if (ddsImage == null)
                {
                    ddsImage = new KUtility.DDSImage(File.ReadAllBytes(fileExplorer.FileName));
                }
                Bitmap image = ddsImage.images[0];
                int xValue = myAnimation.mySizeX * myAnimation.myCurrentColumn;
                int yValue = myAnimation.mySizeY * (myAnimation.myCurrentRow - 1);
                e.Graphics.DrawImage(image, (AnimationViewer.Width / 2) - myAnimation.mySizeX / 4, (AnimationViewer.Height / 2) - myAnimation.mySizeY / 4
                    , new Rectangle(xValue, yValue, myAnimation.mySizeX, myAnimation.mySizeY), GraphicsUnit.Pixel);
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fileExplorer.InitialDirectory = Path.GetFullPath("../../../../../TBSA/Bin/Data/Animations/");
            fileExplorer.Filter = "JSON (*.json)|*.json";
            if (fileExplorer.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                myAnimation.StopAnimation();

                string fileData = System.IO.File.ReadAllText(fileExplorer.FileName);
                myAnimation.myAnimationData = JsonConvert.DeserializeObject<AnimationData>(fileData);

                AnimationNameText.Text = myAnimation.myAnimationData.Name;
                ImagePathText.Text = myAnimation.myAnimationData.FilePath;
                SizeXText.Text = myAnimation.myAnimationData.SizeX.ToString();
                SizeYText.Text = myAnimation.myAnimationData.SizeY.ToString();
                ColumnsText.Text = myAnimation.myAnimationData.AmountOfColumns.ToString();
                RowsText.Text = myAnimation.myAnimationData.AmountOfRows.ToString();
                Frames.Text = myAnimation.myAnimationData.AmountOfFrames.ToString();
                FPSText.Text = myAnimation.myAnimationData.AnimationSpeed.ToString();
                StartFrame.Text = myAnimation.myAnimationData.LoopStart.ToString();
                EndFrame.Text = myAnimation.myAnimationData.LoopEnd.ToString();
                ShouldLoop.Checked = myAnimation.myAnimationData.ShouldLoop;
                Interruptible.Checked = myAnimation.myAnimationData.IsInterruptible;
                InTransitionText.Text = myAnimation.myAnimationData.InTransition;
                OutTransitionText.Text = myAnimation.myAnimationData.OutTransition;

                ddsImage = new KUtility.DDSImage(File.ReadAllBytes("../../../../../TBSA/Bin/" + ImagePathText.Text));
                SpriteSheet.Image = ddsImage.images[0];
                SpriteX.Text = "X: " + SpriteSheet.Image.Width;
                SpriteY.Text = "Y: " + SpriteSheet.Image.Height;

                if (SpriteSheet.Image.Width > SpriteSheet.Width)
                {
                    int xDifference = SpriteSheet.Image.Width - SpriteSheet.Width; ;
                    int yDifference = 0;
                    if (SpriteSheet.Image.Height > SpriteSheet.Height)
                    {
                        yDifference = SpriteSheet.Image.Height - SpriteSheet.Height;
                    }

                    if (xDifference >= yDifference)
                    {
                        Size newSize = new Size(SpriteSheet.Width, SpriteSheet.Height);
                        Bitmap newImage = new Bitmap(SpriteSheet.Image, newSize);
                        SpriteSheet.Image = newImage;
                    }
                }

                int index = ImagePathText.Text.LastIndexOf("Bin\\");
                if (index > -1)
                {
                    string tempString = ImagePathText.Text.Substring(index + 4, ImagePathText.Text.Length - (index + 4));
                    ImagePathText.Text = tempString;
                }
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (AnimationNameText.Text != "" && ImagePathText.Text != "" && SizeXText.Text != "" &&
                    SizeYText.Text != "" && ColumnsText.Text != "" && RowsText.Text != "" &&
                    Frames.Text != "" && FPSText.Text != "" && StartFrame.Text != "" && EndFrame.Text != "")
            {
                myAnimation.myAnimationData.Name = AnimationNameText.Text;
                myAnimation.myAnimationData.FilePath = ImagePathText.Text;
                myAnimation.myAnimationData.SizeX = Convert.ToInt32(SizeXText.Text);
                myAnimation.myAnimationData.SizeY = Convert.ToInt32(SizeYText.Text);
                myAnimation.myAnimationData.AmountOfColumns = Convert.ToInt32(ColumnsText.Text);
                myAnimation.myAnimationData.AmountOfRows = Convert.ToInt32(RowsText.Text);
                myAnimation.myAnimationData.AmountOfFrames = Convert.ToInt32(Frames.Text);
                myAnimation.myAnimationData.AnimationSpeed = Convert.ToInt32(FPSText.Text);
                myAnimation.myAnimationData.LoopStart = Convert.ToInt32(StartFrame.Text);
                myAnimation.myAnimationData.LoopEnd = Convert.ToInt32(EndFrame.Text);
                myAnimation.myAnimationData.ShouldLoop = ShouldLoop.Checked;
                myAnimation.myAnimationData.IsInterruptible = Interruptible.Checked;
                myAnimation.myAnimationData.InTransition = InTransitionText.Text;
                myAnimation.myAnimationData.OutTransition = OutTransitionText.Text;
            
                saveExplorer.InitialDirectory = Path.Combine(Application.StartupPath, "../../../../../TBSA/Bin/Data/Animations/");
                saveExplorer.Filter = "JSON (*.json)|*.json";
                saveExplorer.FileName = myAnimation.myAnimationData.Name + "Animation";

                if (saveExplorer.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    string jsonString = JsonConvert.SerializeObject(myAnimation.myAnimationData, Formatting.Indented);
                    string file = saveExplorer.FileName;
                    System.IO.File.WriteAllText(file, jsonString);
                }
            }
            else
            {
                MessageBox.Show("You need to fill in some more data before you save this animation.");
            }
        }
    }
}
