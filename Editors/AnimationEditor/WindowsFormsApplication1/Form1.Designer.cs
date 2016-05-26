namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.PlayButton = new System.Windows.Forms.Button();
            this.ShouldLoop = new System.Windows.Forms.CheckBox();
            this.ColumnsText = new System.Windows.Forms.TextBox();
            this.Frames = new System.Windows.Forms.TextBox();
            this.FPSText = new System.Windows.Forms.TextBox();
            this.RowsText = new System.Windows.Forms.TextBox();
            this.StartFrame = new System.Windows.Forms.ComboBox();
            this.OutTransitionText = new System.Windows.Forms.TextBox();
            this.InTransitionText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.SizeXText = new System.Windows.Forms.TextBox();
            this.SizeYText = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.Interruptible = new System.Windows.Forms.CheckBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.EndFrame = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.ImagePathText = new System.Windows.Forms.TextBox();
            this.BrowseButton = new System.Windows.Forms.Button();
            this.SpriteSheet = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label12 = new System.Windows.Forms.Label();
            this.AnimationNameText = new System.Windows.Forms.TextBox();
            this.AnimationViewer = new System.Windows.Forms.GroupBox();
            this.SpriteX = new System.Windows.Forms.Label();
            this.SpriteY = new System.Windows.Forms.Label();
            this.FrameLabel = new System.Windows.Forms.Label();
            this.ColumnLabel = new System.Windows.Forms.Label();
            this.RowLabel = new System.Windows.Forms.Label();
            this.StopButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.SpriteSheet)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // PlayButton
            // 
            this.PlayButton.Location = new System.Drawing.Point(491, 469);
            this.PlayButton.Name = "PlayButton";
            this.PlayButton.Size = new System.Drawing.Size(117, 67);
            this.PlayButton.TabIndex = 15;
            this.PlayButton.Text = "Play";
            this.PlayButton.UseVisualStyleBackColor = true;
            this.PlayButton.Click += new System.EventHandler(this.PlayButton_Click);
            // 
            // ShouldLoop
            // 
            this.ShouldLoop.AutoSize = true;
            this.ShouldLoop.Checked = true;
            this.ShouldLoop.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ShouldLoop.Location = new System.Drawing.Point(207, 384);
            this.ShouldLoop.Name = "ShouldLoop";
            this.ShouldLoop.Size = new System.Drawing.Size(86, 17);
            this.ShouldLoop.TabIndex = 9;
            this.ShouldLoop.Text = "Should Loop";
            this.ShouldLoop.UseVisualStyleBackColor = true;
            // 
            // ColumnsText
            // 
            this.ColumnsText.Location = new System.Drawing.Point(116, 452);
            this.ColumnsText.Name = "ColumnsText";
            this.ColumnsText.Size = new System.Drawing.Size(56, 20);
            this.ColumnsText.TabIndex = 6;
            // 
            // Frames
            // 
            this.Frames.Location = new System.Drawing.Point(116, 429);
            this.Frames.Name = "Frames";
            this.Frames.Size = new System.Drawing.Size(56, 20);
            this.Frames.TabIndex = 5;
            this.Frames.TextChanged += new System.EventHandler(this.Frames_TextChanged);
            // 
            // FPSText
            // 
            this.FPSText.Location = new System.Drawing.Point(116, 498);
            this.FPSText.Name = "FPSText";
            this.FPSText.Size = new System.Drawing.Size(56, 20);
            this.FPSText.TabIndex = 8;
            // 
            // RowsText
            // 
            this.RowsText.Location = new System.Drawing.Point(116, 475);
            this.RowsText.Name = "RowsText";
            this.RowsText.Size = new System.Drawing.Size(56, 20);
            this.RowsText.TabIndex = 7;
            // 
            // StartFrame
            // 
            this.StartFrame.FormattingEnabled = true;
            this.StartFrame.Location = new System.Drawing.Point(309, 430);
            this.StartFrame.Name = "StartFrame";
            this.StartFrame.Size = new System.Drawing.Size(45, 21);
            this.StartFrame.TabIndex = 11;
            // 
            // OutTransitionText
            // 
            this.OutTransitionText.Location = new System.Drawing.Point(313, 499);
            this.OutTransitionText.Name = "OutTransitionText";
            this.OutTransitionText.Size = new System.Drawing.Size(100, 20);
            this.OutTransitionText.TabIndex = 14;
            // 
            // InTransitionText
            // 
            this.InTransitionText.Location = new System.Drawing.Point(207, 499);
            this.InTransitionText.Name = "InTransitionText";
            this.InTransitionText.Size = new System.Drawing.Size(100, 20);
            this.InTransitionText.TabIndex = 13;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(204, 480);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "In Transition";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(310, 483);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Out Transition";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 455);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(98, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Amount of Columns";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 478);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(85, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Amount of Rows";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 501);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(99, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Frames per Second";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 432);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(92, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "Amount of Frames";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 385);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 13);
            this.label7.TabIndex = 15;
            this.label7.Text = "Frame Size X";
            // 
            // SizeXText
            // 
            this.SizeXText.Location = new System.Drawing.Point(116, 382);
            this.SizeXText.Name = "SizeXText";
            this.SizeXText.Size = new System.Drawing.Size(56, 20);
            this.SizeXText.TabIndex = 3;
            // 
            // SizeYText
            // 
            this.SizeYText.Location = new System.Drawing.Point(116, 406);
            this.SizeYText.Name = "SizeYText";
            this.SizeYText.Size = new System.Drawing.Size(56, 20);
            this.SizeYText.TabIndex = 4;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(12, 409);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 13);
            this.label8.TabIndex = 18;
            this.label8.Text = "Frame Size Y";
            // 
            // Interruptible
            // 
            this.Interruptible.AutoSize = true;
            this.Interruptible.Checked = true;
            this.Interruptible.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Interruptible.Location = new System.Drawing.Point(207, 408);
            this.Interruptible.Name = "Interruptible";
            this.Interruptible.Size = new System.Drawing.Size(81, 17);
            this.Interruptible.TabIndex = 10;
            this.Interruptible.Text = "Interruptible";
            this.Interruptible.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(204, 433);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(102, 13);
            this.label9.TabIndex = 20;
            this.label9.Text = "Loop Starting Frame";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(204, 457);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(99, 13);
            this.label10.TabIndex = 21;
            this.label10.Text = "Loop Ending Frame";
            // 
            // EndFrame
            // 
            this.EndFrame.FormattingEnabled = true;
            this.EndFrame.Location = new System.Drawing.Point(309, 454);
            this.EndFrame.Name = "EndFrame";
            this.EndFrame.Size = new System.Drawing.Size(45, 21);
            this.EndFrame.TabIndex = 12;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(12, 319);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(61, 13);
            this.label11.TabIndex = 23;
            this.label11.Text = "Image Path";
            // 
            // ImagePathText
            // 
            this.ImagePathText.Location = new System.Drawing.Point(80, 319);
            this.ImagePathText.Name = "ImagePathText";
            this.ImagePathText.ShortcutsEnabled = false;
            this.ImagePathText.Size = new System.Drawing.Size(258, 20);
            this.ImagePathText.TabIndex = 0;
            // 
            // BrowseButton
            // 
            this.BrowseButton.Location = new System.Drawing.Point(344, 319);
            this.BrowseButton.Name = "BrowseButton";
            this.BrowseButton.Size = new System.Drawing.Size(75, 23);
            this.BrowseButton.TabIndex = 1;
            this.BrowseButton.Text = "Browse...";
            this.BrowseButton.UseVisualStyleBackColor = true;
            this.BrowseButton.Click += new System.EventHandler(this.BrowseButton_Click);
            // 
            // SpriteSheet
            // 
            this.SpriteSheet.AccessibleName = "SpriteSheet";
            this.SpriteSheet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SpriteSheet.Location = new System.Drawing.Point(15, 32);
            this.SpriteSheet.Name = "SpriteSheet";
            this.SpriteSheet.Size = new System.Drawing.Size(415, 281);
            this.SpriteSheet.TabIndex = 26;
            this.SpriteSheet.TabStop = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(921, 24);
            this.menuStrip1.TabIndex = 27;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.saveToolStripMenuItem.Text = "Save As";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(13, 360);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(84, 13);
            this.label12.TabIndex = 28;
            this.label12.Text = "Animation Name";
            // 
            // AnimationNameText
            // 
            this.AnimationNameText.Location = new System.Drawing.Point(116, 357);
            this.AnimationNameText.Name = "AnimationNameText";
            this.AnimationNameText.Size = new System.Drawing.Size(100, 20);
            this.AnimationNameText.TabIndex = 2;
            // 
            // AnimationViewer
            // 
            this.AnimationViewer.Location = new System.Drawing.Point(491, 32);
            this.AnimationViewer.Name = "AnimationViewer";
            this.AnimationViewer.Size = new System.Drawing.Size(396, 431);
            this.AnimationViewer.TabIndex = 30;
            this.AnimationViewer.TabStop = false;
            this.AnimationViewer.Text = "Animation Viewer";
            this.AnimationViewer.Paint += new System.Windows.Forms.PaintEventHandler(this.AnimationViewer_Paint);
            // 
            // SpriteX
            // 
            this.SpriteX.AutoSize = true;
            this.SpriteX.Location = new System.Drawing.Point(436, 287);
            this.SpriteX.Name = "SpriteX";
            this.SpriteX.Size = new System.Drawing.Size(20, 13);
            this.SpriteX.TabIndex = 31;
            this.SpriteX.Text = "X: ";
            // 
            // SpriteY
            // 
            this.SpriteY.AutoSize = true;
            this.SpriteY.Location = new System.Drawing.Point(436, 300);
            this.SpriteY.Name = "SpriteY";
            this.SpriteY.Size = new System.Drawing.Size(20, 13);
            this.SpriteY.TabIndex = 32;
            this.SpriteY.Text = "Y: ";
            // 
            // FrameLabel
            // 
            this.FrameLabel.AutoSize = true;
            this.FrameLabel.Location = new System.Drawing.Point(621, 469);
            this.FrameLabel.Name = "FrameLabel";
            this.FrameLabel.Size = new System.Drawing.Size(79, 13);
            this.FrameLabel.TabIndex = 33;
            this.FrameLabel.Text = "Current Frame: ";
            // 
            // ColumnLabel
            // 
            this.ColumnLabel.AutoSize = true;
            this.ColumnLabel.Location = new System.Drawing.Point(621, 483);
            this.ColumnLabel.Name = "ColumnLabel";
            this.ColumnLabel.Size = new System.Drawing.Size(85, 13);
            this.ColumnLabel.TabIndex = 34;
            this.ColumnLabel.Text = "Current Cloumn: ";
            // 
            // RowLabel
            // 
            this.RowLabel.AutoSize = true;
            this.RowLabel.Location = new System.Drawing.Point(621, 498);
            this.RowLabel.Name = "RowLabel";
            this.RowLabel.Size = new System.Drawing.Size(72, 13);
            this.RowLabel.TabIndex = 35;
            this.RowLabel.Text = "Current Row: ";
            // 
            // StopButton
            // 
            this.StopButton.Location = new System.Drawing.Point(618, 513);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(75, 23);
            this.StopButton.TabIndex = 16;
            this.StopButton.Text = "Stop";
            this.StopButton.UseVisualStyleBackColor = true;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // Form1
            // 
            this.AcceptButton = this.PlayButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(921, 548);
            this.Controls.Add(this.StopButton);
            this.Controls.Add(this.RowLabel);
            this.Controls.Add(this.ColumnLabel);
            this.Controls.Add(this.FrameLabel);
            this.Controls.Add(this.SpriteY);
            this.Controls.Add(this.SpriteX);
            this.Controls.Add(this.AnimationViewer);
            this.Controls.Add(this.AnimationNameText);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.SpriteSheet);
            this.Controls.Add(this.BrowseButton);
            this.Controls.Add(this.ImagePathText);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.EndFrame);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.Interruptible);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.SizeYText);
            this.Controls.Add(this.SizeXText);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.InTransitionText);
            this.Controls.Add(this.OutTransitionText);
            this.Controls.Add(this.StartFrame);
            this.Controls.Add(this.RowsText);
            this.Controls.Add(this.FPSText);
            this.Controls.Add(this.Frames);
            this.Controls.Add(this.ColumnsText);
            this.Controls.Add(this.ShouldLoop);
            this.Controls.Add(this.PlayButton);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Animation Editor";
            ((System.ComponentModel.ISupportInitialize)(this.SpriteSheet)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button PlayButton;
        private System.Windows.Forms.CheckBox ShouldLoop;
        private System.Windows.Forms.TextBox ColumnsText;
        private System.Windows.Forms.TextBox Frames;
        private System.Windows.Forms.TextBox FPSText;
        private System.Windows.Forms.TextBox RowsText;
        private System.Windows.Forms.ComboBox StartFrame;
        private System.Windows.Forms.TextBox OutTransitionText;
        private System.Windows.Forms.TextBox InTransitionText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox SizeXText;
        private System.Windows.Forms.TextBox SizeYText;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.CheckBox Interruptible;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox EndFrame;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox ImagePathText;
        private System.Windows.Forms.Button BrowseButton;
        private System.Windows.Forms.PictureBox SpriteSheet;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox AnimationNameText;
        public System.Windows.Forms.GroupBox AnimationViewer;
        private System.Windows.Forms.Label SpriteX;
        private System.Windows.Forms.Label SpriteY;
        private System.Windows.Forms.Label FrameLabel;
        private System.Windows.Forms.Label ColumnLabel;
        private System.Windows.Forms.Label RowLabel;
        private System.Windows.Forms.Button StopButton;
    }
}

