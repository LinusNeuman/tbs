; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Fimbulvinter"
#define MyAppVersion "1.0"
#define MyAppPublisher "TheGameAssembly"
#define MyAppURL "http://www.thegameassembly.com/"
#define MyAppExeName "Launcher.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{F035E5C4-CFF4-46B2-AED6-0A37139FF617}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputBaseFilename=FimbluvinterSetup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "install_dxweb"; Description: "Install directX"; GroupDescription: "Required installs"
Name: "install_vcRedist"; Description: "Install vcRedist"; GroupDescription: "Required installs"

[Files]
Source: "C:\Users\sthahu2\Source\Repos\tbs\TBSA\Bin\Launcher.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\sthahu2\Source\Repos\tbs\TBSA\Bin\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\externalInstallers\dxwebsetup.exe"; Tasks: install_dxweb
Filename: "{app}\externalInstallers\vcredist_x86.exe"; Tasks: install_vcRedist
Filename: "{app}\{#MyAppExeName}"; Flags: nowait postinstall skipifsilent; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"

[UninstallDelete]
Type: filesandordirs; Name: "{app}"

[Messages]
WizardInfoAfter=Find more cool games at http://games.thegameassembly.com/
