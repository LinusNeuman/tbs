namespace UsefulToolForGameProjectYes
{
    partial class GameSettings
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
            this.components = new System.ComponentModel.Container();
            this.ToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.TabGameSettings = new System.Windows.Forms.TabPage();
            this.GroupBoxDebug = new System.Windows.Forms.GroupBox();
            this.CheckBoxCreateDebugLogs = new System.Windows.Forms.CheckBox();
            this.TextBoxDebuglogsDirectory = new System.Windows.Forms.TextBox();
            this.LabelDebugDirectory = new System.Windows.Forms.Label();
            this.GroupBoxMisc = new System.Windows.Forms.GroupBox();
            this.CheckBoxMute = new System.Windows.Forms.CheckBox();
            this.CheckBoxSkipSplashScreen = new System.Windows.Forms.CheckBox();
            this.CheckBoxSkipIntro = new System.Windows.Forms.CheckBox();
            this.GroupBoxResolution = new System.Windows.Forms.GroupBox();
            this.CheckBoxFullscreen = new System.Windows.Forms.CheckBox();
            this.ComboBoxResolution = new System.Windows.Forms.ComboBox();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.TabWindow = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.GroupBoxGameStates = new System.Windows.Forms.GroupBox();
            this.RadioButtonLevelSelect = new System.Windows.Forms.RadioButton();
            this.RadioButtonGamestateCredits = new System.Windows.Forms.RadioButton();
            this.RadioButtonGamestateOptionsMenu = new System.Windows.Forms.RadioButton();
            this.RadioButtonGamestatePauseMenu = new System.Windows.Forms.RadioButton();
            this.RadioButtonGamestateInGame = new System.Windows.Forms.RadioButton();
            this.RadioButtonGamestateMenu = new System.Windows.Forms.RadioButton();
            this.ButtonHelp = new System.Windows.Forms.Button();
            this.TabGameSettings.SuspendLayout();
            this.GroupBoxDebug.SuspendLayout();
            this.GroupBoxMisc.SuspendLayout();
            this.GroupBoxResolution.SuspendLayout();
            this.TabWindow.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.GroupBoxGameStates.SuspendLayout();
            this.SuspendLayout();
            // 
            // TabGameSettings
            // 
            this.TabGameSettings.Controls.Add(this.GroupBoxDebug);
            this.TabGameSettings.Controls.Add(this.GroupBoxMisc);
            this.TabGameSettings.Controls.Add(this.GroupBoxResolution);
            this.TabGameSettings.Location = new System.Drawing.Point(4, 22);
            this.TabGameSettings.Name = "TabGameSettings";
            this.TabGameSettings.Padding = new System.Windows.Forms.Padding(3);
            this.TabGameSettings.Size = new System.Drawing.Size(204, 324);
            this.TabGameSettings.TabIndex = 0;
            this.TabGameSettings.Text = "Game Settings";
            this.TabGameSettings.UseVisualStyleBackColor = true;
            // 
            // GroupBoxDebug
            // 
            this.GroupBoxDebug.Controls.Add(this.CheckBoxCreateDebugLogs);
            this.GroupBoxDebug.Controls.Add(this.TextBoxDebuglogsDirectory);
            this.GroupBoxDebug.Controls.Add(this.LabelDebugDirectory);
            this.GroupBoxDebug.Location = new System.Drawing.Point(6, 217);
            this.GroupBoxDebug.Name = "GroupBoxDebug";
            this.GroupBoxDebug.Size = new System.Drawing.Size(188, 100);
            this.GroupBoxDebug.TabIndex = 4;
            this.GroupBoxDebug.TabStop = false;
            this.GroupBoxDebug.Text = "Debugging";
            // 
            // CheckBoxCreateDebugLogs
            // 
            this.CheckBoxCreateDebugLogs.AutoSize = true;
            this.CheckBoxCreateDebugLogs.Checked = true;
            this.CheckBoxCreateDebugLogs.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxCreateDebugLogs.Location = new System.Drawing.Point(16, 19);
            this.CheckBoxCreateDebugLogs.Name = "CheckBoxCreateDebugLogs";
            this.CheckBoxCreateDebugLogs.Size = new System.Drawing.Size(118, 17);
            this.CheckBoxCreateDebugLogs.TabIndex = 2;
            this.CheckBoxCreateDebugLogs.Text = "Create Debug Logs";
            this.CheckBoxCreateDebugLogs.UseVisualStyleBackColor = true;
            // 
            // TextBoxDebuglogsDirectory
            // 
            this.TextBoxDebuglogsDirectory.Location = new System.Drawing.Point(6, 65);
            this.TextBoxDebuglogsDirectory.Name = "TextBoxDebuglogsDirectory";
            this.TextBoxDebuglogsDirectory.Size = new System.Drawing.Size(174, 20);
            this.TextBoxDebuglogsDirectory.TabIndex = 1;
            this.TextBoxDebuglogsDirectory.Text = "Debug_Logs";
            // 
            // LabelDebugDirectory
            // 
            this.LabelDebugDirectory.AutoSize = true;
            this.LabelDebugDirectory.Location = new System.Drawing.Point(6, 49);
            this.LabelDebugDirectory.Name = "LabelDebugDirectory";
            this.LabelDebugDirectory.Size = new System.Drawing.Size(110, 13);
            this.LabelDebugDirectory.TabIndex = 0;
            this.LabelDebugDirectory.Text = "Debug Logs Directory";
            // 
            // GroupBoxMisc
            // 
            this.GroupBoxMisc.Controls.Add(this.CheckBoxMute);
            this.GroupBoxMisc.Controls.Add(this.CheckBoxSkipSplashScreen);
            this.GroupBoxMisc.Controls.Add(this.CheckBoxSkipIntro);
            this.GroupBoxMisc.Location = new System.Drawing.Point(6, 106);
            this.GroupBoxMisc.Name = "GroupBoxMisc";
            this.GroupBoxMisc.Size = new System.Drawing.Size(188, 105);
            this.GroupBoxMisc.TabIndex = 1;
            this.GroupBoxMisc.TabStop = false;
            this.GroupBoxMisc.Text = "Misc.";
            // 
            // CheckBoxMute
            // 
            this.CheckBoxMute.AutoSize = true;
            this.CheckBoxMute.Checked = true;
            this.CheckBoxMute.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxMute.Location = new System.Drawing.Point(16, 75);
            this.CheckBoxMute.Name = "CheckBoxMute";
            this.CheckBoxMute.Size = new System.Drawing.Size(103, 17);
            this.CheckBoxMute.TabIndex = 2;
            this.CheckBoxMute.Text = "Mute All Sounds";
            this.CheckBoxMute.UseVisualStyleBackColor = true;
            this.CheckBoxMute.CheckedChanged += new System.EventHandler(this.CheckBoxMute_CheckedChanged);
            // 
            // CheckBoxSkipSplashScreen
            // 
            this.CheckBoxSkipSplashScreen.AutoSize = true;
            this.CheckBoxSkipSplashScreen.Checked = true;
            this.CheckBoxSkipSplashScreen.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxSkipSplashScreen.Location = new System.Drawing.Point(16, 51);
            this.CheckBoxSkipSplashScreen.Name = "CheckBoxSkipSplashScreen";
            this.CheckBoxSkipSplashScreen.Size = new System.Drawing.Size(114, 17);
            this.CheckBoxSkipSplashScreen.TabIndex = 1;
            this.CheckBoxSkipSplashScreen.Text = "Skip Splashscreen";
            this.CheckBoxSkipSplashScreen.UseVisualStyleBackColor = true;
            this.CheckBoxSkipSplashScreen.CheckedChanged += new System.EventHandler(this.CheckBoxSkipSplashScreen_CheckedChanged);
            // 
            // CheckBoxSkipIntro
            // 
            this.CheckBoxSkipIntro.AutoSize = true;
            this.CheckBoxSkipIntro.Checked = true;
            this.CheckBoxSkipIntro.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxSkipIntro.Location = new System.Drawing.Point(16, 28);
            this.CheckBoxSkipIntro.Name = "CheckBoxSkipIntro";
            this.CheckBoxSkipIntro.Size = new System.Drawing.Size(71, 17);
            this.CheckBoxSkipIntro.TabIndex = 0;
            this.CheckBoxSkipIntro.Text = "Skip Intro";
            this.CheckBoxSkipIntro.UseVisualStyleBackColor = true;
            this.CheckBoxSkipIntro.CheckedChanged += new System.EventHandler(this.CheckBoxSkipIntro_CheckedChanged);
            // 
            // GroupBoxResolution
            // 
            this.GroupBoxResolution.Controls.Add(this.CheckBoxFullscreen);
            this.GroupBoxResolution.Controls.Add(this.ComboBoxResolution);
            this.GroupBoxResolution.Location = new System.Drawing.Point(6, 22);
            this.GroupBoxResolution.Name = "GroupBoxResolution";
            this.GroupBoxResolution.Size = new System.Drawing.Size(188, 78);
            this.GroupBoxResolution.TabIndex = 0;
            this.GroupBoxResolution.TabStop = false;
            this.GroupBoxResolution.Text = "Resolution";
            // 
            // CheckBoxFullscreen
            // 
            this.CheckBoxFullscreen.AutoSize = true;
            this.CheckBoxFullscreen.Location = new System.Drawing.Point(16, 46);
            this.CheckBoxFullscreen.Name = "CheckBoxFullscreen";
            this.CheckBoxFullscreen.Size = new System.Drawing.Size(74, 17);
            this.CheckBoxFullscreen.TabIndex = 1;
            this.CheckBoxFullscreen.Text = "Fullscreen";
            this.CheckBoxFullscreen.UseVisualStyleBackColor = true;
            this.CheckBoxFullscreen.CheckedChanged += new System.EventHandler(this.CheckBoxFullscreen_CheckedChanged);
            // 
            // ComboBoxResolution
            // 
            this.ComboBoxResolution.DisplayMember = "Tag";
            this.ComboBoxResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ComboBoxResolution.FormattingEnabled = true;
            this.ComboBoxResolution.Location = new System.Drawing.Point(6, 19);
            this.ComboBoxResolution.Name = "ComboBoxResolution";
            this.ComboBoxResolution.Size = new System.Drawing.Size(174, 21);
            this.ComboBoxResolution.TabIndex = 0;
            this.ComboBoxResolution.SelectedIndexChanged += new System.EventHandler(this.ComboBoxResolution_SelectedIndexChanged);
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(229, 310);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 2;
            this.buttonSave.Text = "&Save";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // buttonLoad
            // 
            this.buttonLoad.Location = new System.Drawing.Point(229, 281);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(75, 23);
            this.buttonLoad.TabIndex = 3;
            this.buttonLoad.Text = "&Load";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // TabWindow
            // 
            this.TabWindow.Controls.Add(this.TabGameSettings);
            this.TabWindow.Controls.Add(this.tabPage1);
            this.TabWindow.Location = new System.Drawing.Point(2, 3);
            this.TabWindow.Name = "TabWindow";
            this.TabWindow.SelectedIndex = 0;
            this.TabWindow.Size = new System.Drawing.Size(212, 350);
            this.TabWindow.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.GroupBoxGameStates);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(204, 324);
            this.tabPage1.TabIndex = 1;
            this.tabPage1.Text = "More Options";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // GroupBoxGameStates
            // 
            this.GroupBoxGameStates.Controls.Add(this.RadioButtonLevelSelect);
            this.GroupBoxGameStates.Controls.Add(this.RadioButtonGamestateCredits);
            this.GroupBoxGameStates.Controls.Add(this.RadioButtonGamestateOptionsMenu);
            this.GroupBoxGameStates.Controls.Add(this.RadioButtonGamestatePauseMenu);
            this.GroupBoxGameStates.Controls.Add(this.RadioButtonGamestateInGame);
            this.GroupBoxGameStates.Controls.Add(this.RadioButtonGamestateMenu);
            this.GroupBoxGameStates.Location = new System.Drawing.Point(6, 6);
            this.GroupBoxGameStates.Name = "GroupBoxGameStates";
            this.GroupBoxGameStates.Size = new System.Drawing.Size(192, 156);
            this.GroupBoxGameStates.TabIndex = 1;
            this.GroupBoxGameStates.TabStop = false;
            this.GroupBoxGameStates.Text = "Gamestate when Starting";
            // 
            // RadioButtonLevelSelect
            // 
            this.RadioButtonLevelSelect.AutoSize = true;
            this.RadioButtonLevelSelect.Checked = true;
            this.RadioButtonLevelSelect.Location = new System.Drawing.Point(6, 65);
            this.RadioButtonLevelSelect.Name = "RadioButtonLevelSelect";
            this.RadioButtonLevelSelect.Size = new System.Drawing.Size(84, 17);
            this.RadioButtonLevelSelect.TabIndex = 5;
            this.RadioButtonLevelSelect.TabStop = true;
            this.RadioButtonLevelSelect.Text = "Level Select";
            this.RadioButtonLevelSelect.UseVisualStyleBackColor = true;
            // 
            // RadioButtonGamestateCredits
            // 
            this.RadioButtonGamestateCredits.AutoSize = true;
            this.RadioButtonGamestateCredits.Location = new System.Drawing.Point(6, 134);
            this.RadioButtonGamestateCredits.Name = "RadioButtonGamestateCredits";
            this.RadioButtonGamestateCredits.Size = new System.Drawing.Size(57, 17);
            this.RadioButtonGamestateCredits.TabIndex = 4;
            this.RadioButtonGamestateCredits.Text = "Credits";
            this.RadioButtonGamestateCredits.UseVisualStyleBackColor = true;
            // 
            // RadioButtonGamestateOptionsMenu
            // 
            this.RadioButtonGamestateOptionsMenu.AutoSize = true;
            this.RadioButtonGamestateOptionsMenu.Location = new System.Drawing.Point(6, 111);
            this.RadioButtonGamestateOptionsMenu.Name = "RadioButtonGamestateOptionsMenu";
            this.RadioButtonGamestateOptionsMenu.Size = new System.Drawing.Size(91, 17);
            this.RadioButtonGamestateOptionsMenu.TabIndex = 3;
            this.RadioButtonGamestateOptionsMenu.Text = "Options Menu";
            this.RadioButtonGamestateOptionsMenu.UseVisualStyleBackColor = true;
            // 
            // RadioButtonGamestatePauseMenu
            // 
            this.RadioButtonGamestatePauseMenu.AutoSize = true;
            this.RadioButtonGamestatePauseMenu.Location = new System.Drawing.Point(6, 88);
            this.RadioButtonGamestatePauseMenu.Name = "RadioButtonGamestatePauseMenu";
            this.RadioButtonGamestatePauseMenu.Size = new System.Drawing.Size(85, 17);
            this.RadioButtonGamestatePauseMenu.TabIndex = 2;
            this.RadioButtonGamestatePauseMenu.Text = "Pause Menu";
            this.RadioButtonGamestatePauseMenu.UseVisualStyleBackColor = true;
            // 
            // RadioButtonGamestateInGame
            // 
            this.RadioButtonGamestateInGame.AutoSize = true;
            this.RadioButtonGamestateInGame.Location = new System.Drawing.Point(6, 42);
            this.RadioButtonGamestateInGame.Name = "RadioButtonGamestateInGame";
            this.RadioButtonGamestateInGame.Size = new System.Drawing.Size(65, 17);
            this.RadioButtonGamestateInGame.TabIndex = 1;
            this.RadioButtonGamestateInGame.Text = "In Game";
            this.RadioButtonGamestateInGame.UseVisualStyleBackColor = true;
            // 
            // RadioButtonGamestateMenu
            // 
            this.RadioButtonGamestateMenu.AutoSize = true;
            this.RadioButtonGamestateMenu.Location = new System.Drawing.Point(6, 19);
            this.RadioButtonGamestateMenu.Name = "RadioButtonGamestateMenu";
            this.RadioButtonGamestateMenu.Size = new System.Drawing.Size(78, 17);
            this.RadioButtonGamestateMenu.TabIndex = 0;
            this.RadioButtonGamestateMenu.Text = "Main Menu";
            this.RadioButtonGamestateMenu.UseVisualStyleBackColor = true;
            // 
            // ButtonHelp
            // 
            this.ButtonHelp.Location = new System.Drawing.Point(267, 12);
            this.ButtonHelp.Name = "ButtonHelp";
            this.ButtonHelp.Size = new System.Drawing.Size(37, 27);
            this.ButtonHelp.TabIndex = 4;
            this.ButtonHelp.Text = "Help";
            this.ButtonHelp.UseVisualStyleBackColor = true;
            this.ButtonHelp.Click += new System.EventHandler(this.ButtonHelp_Click);
            // 
            // GameSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(316, 355);
            this.Controls.Add(this.ButtonHelp);
            this.Controls.Add(this.TabWindow);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.buttonLoad);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "GameSettings";
            this.Text = "Game Settings";
            this.TabGameSettings.ResumeLayout(false);
            this.GroupBoxDebug.ResumeLayout(false);
            this.GroupBoxDebug.PerformLayout();
            this.GroupBoxMisc.ResumeLayout(false);
            this.GroupBoxMisc.PerformLayout();
            this.GroupBoxResolution.ResumeLayout(false);
            this.GroupBoxResolution.PerformLayout();
            this.TabWindow.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.GroupBoxGameStates.ResumeLayout(false);
            this.GroupBoxGameStates.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ToolTip ToolTip;
        private System.Windows.Forms.TabPage TabGameSettings;
        private System.Windows.Forms.GroupBox GroupBoxDebug;
        private System.Windows.Forms.CheckBox CheckBoxCreateDebugLogs;
        private System.Windows.Forms.TextBox TextBoxDebuglogsDirectory;
        private System.Windows.Forms.Label LabelDebugDirectory;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.GroupBox GroupBoxMisc;
        private System.Windows.Forms.CheckBox CheckBoxMute;
        private System.Windows.Forms.CheckBox CheckBoxSkipSplashScreen;
        private System.Windows.Forms.CheckBox CheckBoxSkipIntro;
        private System.Windows.Forms.GroupBox GroupBoxResolution;
        private System.Windows.Forms.CheckBox CheckBoxFullscreen;
        private System.Windows.Forms.ComboBox ComboBoxResolution;
        private System.Windows.Forms.TabControl TabWindow;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.GroupBox GroupBoxGameStates;
        private System.Windows.Forms.RadioButton RadioButtonLevelSelect;
        private System.Windows.Forms.RadioButton RadioButtonGamestateCredits;
        private System.Windows.Forms.RadioButton RadioButtonGamestateOptionsMenu;
        private System.Windows.Forms.RadioButton RadioButtonGamestatePauseMenu;
        private System.Windows.Forms.RadioButton RadioButtonGamestateInGame;
        private System.Windows.Forms.RadioButton RadioButtonGamestateMenu;
        private System.Windows.Forms.Button ButtonHelp;
    }
}

