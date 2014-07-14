#pragma once

ref class ToonState;
ref class pondConfig;
typedef System::Collections::Generic::List<pondConfig^> pondConfigList_t;

namespace fisherman {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
                        fd_ = -1;
                        stateA_ = 0;
                        stateB_ = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	public: 
                static System::Windows::Forms::ListBox^  WindowPicker_;
                static ToonState^  pi_, ^selectedpi_;
                static pondConfig ^defaultpc_;
                pondConfigList_t ^ponds_;
                String ^defaultFile_;

                int fd_;
                XINPUT_STATE *stateA_, *stateB_;
                struct sockaddr_in *si_other_;

                HDC hDC_;

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  refreshWindowsToolStripMenuItem;
	private: System::Windows::Forms::Timer^  fisherTimer;
	private: System::Windows::Forms::Timer^  emergencyTimer;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  primaryTabPage;

	private: System::Windows::Forms::Button^  MoveMouse;
	private: System::Windows::Forms::Button^  ReshapeButton;
	private: System::Windows::Forms::Label^  WindowShape;
	private: System::Windows::Forms::CheckedListBox^  WindowPicker;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  fishYSpeed;
        private: System::Windows::Forms::TextBox^  fishLocY;
        private: System::Windows::Forms::TextBox^  fishXSpeed;
        private: System::Windows::Forms::TextBox^  fishLocX;





















	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  fishSpeedY;
	private: System::Windows::Forms::TextBox^  FishY;
	private: System::Windows::Forms::TextBox^  fishSpeedX;
	private: System::Windows::Forms::TextBox^  FishX;

	private: System::Windows::Forms::Button^  StartFishing;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  PondXLabel;
	private: System::Windows::Forms::TextBox^  pondHeight;
	private: System::Windows::Forms::TextBox^  pondY;
	private: System::Windows::Forms::TextBox^  pondWidth;
	private: System::Windows::Forms::TextBox^  pondX;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  ToleranceTextBox;
	private: System::Windows::Forms::TextBox^  BTextBox;
	private: System::Windows::Forms::TextBox^  GTextBox;
	private: System::Windows::Forms::TextBox^  RTextBox;
private: System::Windows::Forms::Panel^  pondConfigPanel;


private: System::Windows::Forms::TextBox^  pondDescription;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::TextBox^  pondPondHeight;

private: System::Windows::Forms::TextBox^  pondPondWidth;

private: System::Windows::Forms::TextBox^  pondPondY;

private: System::Windows::Forms::TextBox^  pondPondX;

private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::TextBox^  pondFishT;

private: System::Windows::Forms::TextBox^  pondFishB;

private: System::Windows::Forms::TextBox^  pondFishG;

private: System::Windows::Forms::TextBox^  pondFishR;

private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::CheckBox^  pondEstate;

private: System::Windows::Forms::TextBox^  pondFisherY;

private: System::Windows::Forms::TextBox^  pondFisherX;

private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::TextBox^  pondDockY;

private: System::Windows::Forms::TextBox^  pondDockX;

private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::ToolStripMenuItem^  plansToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  loadPlansToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  savePlansToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  deletePlanToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  sampleDockToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  sampleFisherToolStripMenuItem;
private: System::Windows::Forms::Panel^  fish2;
private: System::Windows::Forms::Panel^  fish1;
private: System::Windows::Forms::TabPage^  tabPage1;
private: System::Windows::Forms::TabPage^  tabPage2;
private: System::Windows::Forms::SplitContainer^  splitContainer1;
private: System::Windows::Forms::ListBox^  plansList;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::RadioButton^  dockradio2;
private: System::Windows::Forms::RadioButton^  dockradio3;
private: System::Windows::Forms::RadioButton^  dockradio4;
private: System::Windows::Forms::RadioButton^  dockradio1;
private: System::Windows::Forms::GroupBox^  GolfCourses;
private: System::Windows::Forms::RadioButton^  largeCourseRadio;

private: System::Windows::Forms::RadioButton^  mediumCourseRadio;

private: System::Windows::Forms::RadioButton^  smallCourseRadio;
private: System::Windows::Forms::Button^  startGolfing;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::TextBox^  golfDelay;
private: System::Windows::Forms::TabPage^  tabPage3;

private: System::Windows::Forms::Timer^  GolfTimer;
private: System::Windows::Forms::Timer^  RaceViewTimer;
private: System::Windows::Forms::Timer^  RaceTimer;
private: System::Windows::Forms::Button^  findbase;
private: System::Windows::Forms::ToolStripMenuItem^  stopToolStripMenuItem;
private: System::Windows::Forms::GroupBox^  GolfMoves;
private: System::Windows::Forms::Button^  GolfTap;
private: System::Windows::Forms::Button^  PerfectHit;




private: System::Windows::Forms::Button^  GolfMiss;


private: System::Windows::Forms::ListBox^  GolfHole;
private: System::Windows::Forms::Button^  startScanner;

private: System::Windows::Forms::Button^  StillGolfing;
private: System::Windows::Forms::TextBox^  holdTime;

private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::TextBox^  turnTime;
private: System::Windows::Forms::TextBox^  scanResults;


private: System::Windows::Forms::Button^  ScanButton;
private: System::Windows::Forms::GroupBox^  CastGroup;


private: System::Windows::Forms::RadioButton^  castCenterButton;

private: System::Windows::Forms::RadioButton^  castRightButton;
private: System::Windows::Forms::RadioButton^  castLeftButton;
private: System::Windows::Forms::CheckBox^  centerCast;
private: System::Windows::Forms::CheckBox^  perfectShots;
private: System::Windows::Forms::Button^  raceScanButton;
private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::RadioButton^  cityRadio;
private: System::Windows::Forms::RadioButton^  rusticRadio;
private: System::Windows::Forms::RadioButton^  screwballRadio;
private: System::Windows::Forms::CheckBox^  tallToon;

private: System::Windows::Forms::Panel^  toonViewPanel;
private: System::Windows::Forms::Label^  thresholdTxt;
private: System::Windows::Forms::TextBox^  toonThreshold;
private: System::Windows::Forms::Panel^  playview;
private: System::Windows::Forms::TextBox^  middle;
private: System::Windows::Forms::TextBox^  roadBox;
private: System::Windows::Forms::Button^  RunThere;
private: System::Windows::Forms::TextBox^  raceScanOut;
private: System::Windows::Forms::Button^  justRace;
private: System::Windows::Forms::TextBox^  raceTrack;
private: System::Windows::Forms::CheckBox^  bitBlit;
private: System::Windows::Forms::CheckBox^  grandPrix;
private: System::Windows::Forms::CheckBox^  onWin;
private: System::Windows::Forms::TextBox^  counterBox;
private: System::Windows::Forms::TabPage^  multiTab;
private: System::Windows::Forms::CheckBox^  followToon;
private: System::Windows::Forms::Timer^  followToonTimer;
private: System::Windows::Forms::Button^  alignToons;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Button^  pushVals;
private: System::Windows::Forms::CheckBox^  TrackBox;
private: System::Windows::Forms::TextBox^  HBox;
private: System::Windows::Forms::TextBox^  ZBox;
private: System::Windows::Forms::TextBox^  YBox;
private: System::Windows::Forms::TextBox^  XBox;
private: System::Windows::Forms::TextBox^  statusBox;
private: System::Windows::Forms::Timer^  GolfEmergencyTimer;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::TabPage^  CJToolPage;
private: System::Windows::Forms::TabPage^  VPTools;

private: System::Windows::Forms::Button^  VPStandAside;
private: System::Windows::Forms::Button^  VPMiddleTopRamp;
private: System::Windows::Forms::Button^  VPMiddlePlatform;
private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::Button^  VPBottom;
private: System::Windows::Forms::Button^  VPGetPie;
private: System::Windows::Forms::Timer^  VPTimer;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::ToolStripMenuItem^  controllerToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  genericToolStripMenuItem;

private: System::Windows::Forms::Button^  VPJump;

private: System::Windows::Forms::Button^  VPThrow;
private: System::Windows::Forms::ToolStripMenuItem^  vPModeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFOModeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cJModeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cEOModeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  DisabledMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
private: System::Windows::Forms::ToolStripMenuItem^  publishStripMenuItem1;
private: System::Windows::Forms::Timer^  ControllerTimer;











	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->refreshWindowsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plansToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadPlansToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->savePlansToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deletePlanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sampleDockToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sampleFisherToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stopToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->controllerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DisabledMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->genericToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->vPModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cFOModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cJModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cEOModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->publishStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fisherTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->primaryTabPage = (gcnew System::Windows::Forms::TabPage());
			this->pondEstate = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->dockradio2 = (gcnew System::Windows::Forms::RadioButton());
			this->dockradio3 = (gcnew System::Windows::Forms::RadioButton());
			this->dockradio4 = (gcnew System::Windows::Forms::RadioButton());
			this->dockradio1 = (gcnew System::Windows::Forms::RadioButton());
			this->plansList = (gcnew System::Windows::Forms::ListBox());
			this->fish2 = (gcnew System::Windows::Forms::Panel());
			this->fish1 = (gcnew System::Windows::Forms::Panel());
			this->pondConfigPanel = (gcnew System::Windows::Forms::Panel());
			this->pondFisherY = (gcnew System::Windows::Forms::TextBox());
			this->pondFisherX = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->pondDockY = (gcnew System::Windows::Forms::TextBox());
			this->pondDockX = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->pondPondHeight = (gcnew System::Windows::Forms::TextBox());
			this->pondPondWidth = (gcnew System::Windows::Forms::TextBox());
			this->pondPondY = (gcnew System::Windows::Forms::TextBox());
			this->pondPondX = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->pondFishT = (gcnew System::Windows::Forms::TextBox());
			this->pondFishB = (gcnew System::Windows::Forms::TextBox());
			this->pondFishG = (gcnew System::Windows::Forms::TextBox());
			this->pondFishR = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->StartFishing = (gcnew System::Windows::Forms::Button());
			this->MoveMouse = (gcnew System::Windows::Forms::Button());
			this->ReshapeButton = (gcnew System::Windows::Forms::Button());
			this->WindowShape = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->fishYSpeed = (gcnew System::Windows::Forms::TextBox());
			this->fishLocY = (gcnew System::Windows::Forms::TextBox());
			this->fishXSpeed = (gcnew System::Windows::Forms::TextBox());
			this->fishLocX = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pondDescription = (gcnew System::Windows::Forms::TextBox());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->playview = (gcnew System::Windows::Forms::Panel());
			this->perfectShots = (gcnew System::Windows::Forms::CheckBox());
			this->centerCast = (gcnew System::Windows::Forms::CheckBox());
			this->CastGroup = (gcnew System::Windows::Forms::GroupBox());
			this->castCenterButton = (gcnew System::Windows::Forms::RadioButton());
			this->castRightButton = (gcnew System::Windows::Forms::RadioButton());
			this->castLeftButton = (gcnew System::Windows::Forms::RadioButton());
			this->scanResults = (gcnew System::Windows::Forms::TextBox());
			this->ScanButton = (gcnew System::Windows::Forms::Button());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->turnTime = (gcnew System::Windows::Forms::TextBox());
			this->holdTime = (gcnew System::Windows::Forms::TextBox());
			this->startScanner = (gcnew System::Windows::Forms::Button());
			this->StillGolfing = (gcnew System::Windows::Forms::Button());
			this->GolfMoves = (gcnew System::Windows::Forms::GroupBox());
			this->GolfTap = (gcnew System::Windows::Forms::Button());
			this->PerfectHit = (gcnew System::Windows::Forms::Button());
			this->GolfMiss = (gcnew System::Windows::Forms::Button());
			this->GolfHole = (gcnew System::Windows::Forms::ListBox());
			this->findbase = (gcnew System::Windows::Forms::Button());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->golfDelay = (gcnew System::Windows::Forms::TextBox());
			this->startGolfing = (gcnew System::Windows::Forms::Button());
			this->GolfCourses = (gcnew System::Windows::Forms::GroupBox());
			this->largeCourseRadio = (gcnew System::Windows::Forms::RadioButton());
			this->mediumCourseRadio = (gcnew System::Windows::Forms::RadioButton());
			this->smallCourseRadio = (gcnew System::Windows::Forms::RadioButton());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->counterBox = (gcnew System::Windows::Forms::TextBox());
			this->onWin = (gcnew System::Windows::Forms::CheckBox());
			this->grandPrix = (gcnew System::Windows::Forms::CheckBox());
			this->bitBlit = (gcnew System::Windows::Forms::CheckBox());
			this->raceTrack = (gcnew System::Windows::Forms::TextBox());
			this->justRace = (gcnew System::Windows::Forms::Button());
			this->raceScanOut = (gcnew System::Windows::Forms::TextBox());
			this->RunThere = (gcnew System::Windows::Forms::Button());
			this->roadBox = (gcnew System::Windows::Forms::TextBox());
			this->middle = (gcnew System::Windows::Forms::TextBox());
			this->thresholdTxt = (gcnew System::Windows::Forms::Label());
			this->toonThreshold = (gcnew System::Windows::Forms::TextBox());
			this->tallToon = (gcnew System::Windows::Forms::CheckBox());
			this->toonViewPanel = (gcnew System::Windows::Forms::Panel());
			this->raceScanButton = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->cityRadio = (gcnew System::Windows::Forms::RadioButton());
			this->rusticRadio = (gcnew System::Windows::Forms::RadioButton());
			this->screwballRadio = (gcnew System::Windows::Forms::RadioButton());
			this->multiTab = (gcnew System::Windows::Forms::TabPage());
			this->statusBox = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->pushVals = (gcnew System::Windows::Forms::Button());
			this->TrackBox = (gcnew System::Windows::Forms::CheckBox());
			this->HBox = (gcnew System::Windows::Forms::TextBox());
			this->ZBox = (gcnew System::Windows::Forms::TextBox());
			this->YBox = (gcnew System::Windows::Forms::TextBox());
			this->XBox = (gcnew System::Windows::Forms::TextBox());
			this->alignToons = (gcnew System::Windows::Forms::Button());
			this->followToon = (gcnew System::Windows::Forms::CheckBox());
			this->VPTools = (gcnew System::Windows::Forms::TabPage());
			this->VPJump = (gcnew System::Windows::Forms::Button());
			this->VPThrow = (gcnew System::Windows::Forms::Button());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->VPStandAside = (gcnew System::Windows::Forms::Button());
			this->VPMiddleTopRamp = (gcnew System::Windows::Forms::Button());
			this->VPMiddlePlatform = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->VPBottom = (gcnew System::Windows::Forms::Button());
			this->VPGetPie = (gcnew System::Windows::Forms::Button());
			this->CJToolPage = (gcnew System::Windows::Forms::TabPage());
			this->WindowPicker = (gcnew System::Windows::Forms::CheckedListBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->fishSpeedY = (gcnew System::Windows::Forms::TextBox());
			this->FishY = (gcnew System::Windows::Forms::TextBox());
			this->fishSpeedX = (gcnew System::Windows::Forms::TextBox());
			this->FishX = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->PondXLabel = (gcnew System::Windows::Forms::Label());
			this->pondHeight = (gcnew System::Windows::Forms::TextBox());
			this->pondY = (gcnew System::Windows::Forms::TextBox());
			this->pondWidth = (gcnew System::Windows::Forms::TextBox());
			this->pondX = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ToleranceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->BTextBox = (gcnew System::Windows::Forms::TextBox());
			this->GTextBox = (gcnew System::Windows::Forms::TextBox());
			this->RTextBox = (gcnew System::Windows::Forms::TextBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->GolfTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->emergencyTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->RaceViewTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->RaceTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->followToonTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->GolfEmergencyTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->VPTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->ControllerTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->primaryTabPage->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->pondConfigPanel->SuspendLayout();
			this->panel3->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->CastGroup->SuspendLayout();
			this->GolfMoves->SuspendLayout();
			this->GolfCourses->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->multiTab->SuspendLayout();
			this->VPTools->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->helpToolStripMenuItem, this->plansToolStripMenuItem, this->stopToolStripMenuItem, this->controllerToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(819, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->refreshWindowsToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// refreshWindowsToolStripMenuItem
			// 
			this->refreshWindowsToolStripMenuItem->Name = L"refreshWindowsToolStripMenuItem";
			this->refreshWindowsToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->refreshWindowsToolStripMenuItem->Text = L"Refresh Windows";
			this->refreshWindowsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::refreshWindowsToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// plansToolStripMenuItem
			// 
			this->plansToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->loadPlansToolStripMenuItem, 
				this->savePlansToolStripMenuItem, this->deletePlanToolStripMenuItem, this->sampleDockToolStripMenuItem, this->sampleFisherToolStripMenuItem});
			this->plansToolStripMenuItem->Name = L"plansToolStripMenuItem";
			this->plansToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->plansToolStripMenuItem->Text = L"Plans";
			// 
			// loadPlansToolStripMenuItem
			// 
			this->loadPlansToolStripMenuItem->Name = L"loadPlansToolStripMenuItem";
			this->loadPlansToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->loadPlansToolStripMenuItem->Text = L"Load Plans";
			this->loadPlansToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::loadPlansToolStripMenuItem_Click);
			// 
			// savePlansToolStripMenuItem
			// 
			this->savePlansToolStripMenuItem->Name = L"savePlansToolStripMenuItem";
			this->savePlansToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->savePlansToolStripMenuItem->Text = L"Save Plans";
			this->savePlansToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::savePlansToolStripMenuItem_Click);
			// 
			// deletePlanToolStripMenuItem
			// 
			this->deletePlanToolStripMenuItem->Name = L"deletePlanToolStripMenuItem";
			this->deletePlanToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->deletePlanToolStripMenuItem->Text = L"Delete Plan";
			this->deletePlanToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deletePlanToolStripMenuItem_Click);
			// 
			// sampleDockToolStripMenuItem
			// 
			this->sampleDockToolStripMenuItem->Name = L"sampleDockToolStripMenuItem";
			this->sampleDockToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->sampleDockToolStripMenuItem->Text = L"Sample Dock";
			// 
			// sampleFisherToolStripMenuItem
			// 
			this->sampleFisherToolStripMenuItem->Name = L"sampleFisherToolStripMenuItem";
			this->sampleFisherToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->sampleFisherToolStripMenuItem->Text = L"Sample Fisher";
			// 
			// stopToolStripMenuItem
			// 
			this->stopToolStripMenuItem->Name = L"stopToolStripMenuItem";
			this->stopToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->stopToolStripMenuItem->Text = L"stop";
			this->stopToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::stopToolStripMenuItem_Click);
			// 
			// controllerToolStripMenuItem
			// 
			this->controllerToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->DisabledMenuItem, 
				this->genericToolStripMenuItem, this->vPModeToolStripMenuItem, this->cFOModeToolStripMenuItem, this->cJModeToolStripMenuItem, 
				this->cEOModeToolStripMenuItem, this->toolStripSeparator1, this->publishStripMenuItem1});
			this->controllerToolStripMenuItem->Name = L"controllerToolStripMenuItem";
			this->controllerToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->controllerToolStripMenuItem->Text = L"Controller";
			// 
			// DisabledMenuItem
			// 
			this->DisabledMenuItem->Checked = true;
			this->DisabledMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->DisabledMenuItem->Name = L"DisabledMenuItem";
			this->DisabledMenuItem->Size = System::Drawing::Size(152, 22);
			this->DisabledMenuItem->Text = L"Disabled";
			this->DisabledMenuItem->Click += gcnew System::EventHandler(this, &Form1::DisabledMenuItem_Click);
			// 
			// genericToolStripMenuItem
			// 
			this->genericToolStripMenuItem->Name = L"genericToolStripMenuItem";
			this->genericToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->genericToolStripMenuItem->Text = L"Generic";
			this->genericToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::genericToolStripMenuItem_Click);
			// 
			// vPModeToolStripMenuItem
			// 
			this->vPModeToolStripMenuItem->Name = L"vPModeToolStripMenuItem";
			this->vPModeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->vPModeToolStripMenuItem->Text = L"VP";
			this->vPModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::vPModeToolStripMenuItem_Click);
			// 
			// cFOModeToolStripMenuItem
			// 
			this->cFOModeToolStripMenuItem->Name = L"cFOModeToolStripMenuItem";
			this->cFOModeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->cFOModeToolStripMenuItem->Text = L"CFO";
			this->cFOModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::cFOModeToolStripMenuItem_Click);
			// 
			// cJModeToolStripMenuItem
			// 
			this->cJModeToolStripMenuItem->Name = L"cJModeToolStripMenuItem";
			this->cJModeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->cJModeToolStripMenuItem->Text = L"CJ";
			this->cJModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::cJModeToolStripMenuItem_Click);
			// 
			// cEOModeToolStripMenuItem
			// 
			this->cEOModeToolStripMenuItem->Name = L"cEOModeToolStripMenuItem";
			this->cEOModeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->cEOModeToolStripMenuItem->Text = L"CEO";
			this->cEOModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::cEOModeToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(149, 6);
			// 
			// publishStripMenuItem1
			// 
			this->publishStripMenuItem1->Name = L"publishStripMenuItem1";
			this->publishStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->publishStripMenuItem1->Text = L"publish control";
			this->publishStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::publishStripMenuItem1_Click);
			// 
			// fisherTimer
			// 
			this->fisherTimer->Tick += gcnew System::EventHandler(this, &Form1::fisherTimer_Tick);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->primaryTabPage);
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->multiTab);
			this->tabControl1->Controls->Add(this->VPTools);
			this->tabControl1->Controls->Add(this->CJToolPage);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(723, 511);
			this->tabControl1->TabIndex = 29;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->label37);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(715, 485);
			this->tabPage3->TabIndex = 3;
			this->tabPage3->Text = L"About";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(214, 115);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(273, 117);
			this->label37->TabIndex = 0;
			this->label37->Text = resources->GetString(L"label37.Text");
			// 
			// primaryTabPage
			// 
			this->primaryTabPage->Controls->Add(this->pondEstate);
			this->primaryTabPage->Controls->Add(this->groupBox1);
			this->primaryTabPage->Controls->Add(this->plansList);
			this->primaryTabPage->Controls->Add(this->fish2);
			this->primaryTabPage->Controls->Add(this->fish1);
			this->primaryTabPage->Controls->Add(this->pondConfigPanel);
			this->primaryTabPage->Controls->Add(this->StartFishing);
			this->primaryTabPage->Controls->Add(this->MoveMouse);
			this->primaryTabPage->Controls->Add(this->ReshapeButton);
			this->primaryTabPage->Controls->Add(this->WindowShape);
			this->primaryTabPage->Controls->Add(this->label14);
			this->primaryTabPage->Controls->Add(this->panel3);
			this->primaryTabPage->Controls->Add(this->label2);
			this->primaryTabPage->Controls->Add(this->pondDescription);
			this->primaryTabPage->Location = System::Drawing::Point(4, 22);
			this->primaryTabPage->Name = L"primaryTabPage";
			this->primaryTabPage->Padding = System::Windows::Forms::Padding(3);
			this->primaryTabPage->Size = System::Drawing::Size(715, 485);
			this->primaryTabPage->TabIndex = 0;
			this->primaryTabPage->Text = L"Billy the fisherman";
			this->primaryTabPage->UseVisualStyleBackColor = true;
			// 
			// pondEstate
			// 
			this->pondEstate->AutoSize = true;
			this->pondEstate->Location = System::Drawing::Point(17, 133);
			this->pondEstate->Name = L"pondEstate";
			this->pondEstate->Size = System::Drawing::Size(56, 17);
			this->pondEstate->TabIndex = 27;
			this->pondEstate->Text = L"Estate";
			this->pondEstate->UseVisualStyleBackColor = true;
			this->pondEstate->CheckedChanged += gcnew System::EventHandler(this, &Form1::pondEstate_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->dockradio2);
			this->groupBox1->Controls->Add(this->dockradio3);
			this->groupBox1->Controls->Add(this->dockradio4);
			this->groupBox1->Controls->Add(this->dockradio1);
			this->groupBox1->Location = System::Drawing::Point(109, 39);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(96, 111);
			this->groupBox1->TabIndex = 48;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Docks";
			// 
			// dockradio2
			// 
			this->dockradio2->AutoSize = true;
			this->dockradio2->Location = System::Drawing::Point(3, 37);
			this->dockradio2->Name = L"dockradio2";
			this->dockradio2->Size = System::Drawing::Size(58, 17);
			this->dockradio2->TabIndex = 3;
			this->dockradio2->Text = L"dock 2";
			this->dockradio2->UseVisualStyleBackColor = true;
			this->dockradio2->CheckedChanged += gcnew System::EventHandler(this, &Form1::dockradio2_CheckedChanged);
			// 
			// dockradio3
			// 
			this->dockradio3->AutoSize = true;
			this->dockradio3->Location = System::Drawing::Point(2, 60);
			this->dockradio3->Name = L"dockradio3";
			this->dockradio3->Size = System::Drawing::Size(58, 17);
			this->dockradio3->TabIndex = 2;
			this->dockradio3->Text = L"dock 3";
			this->dockradio3->UseVisualStyleBackColor = true;
			this->dockradio3->CheckedChanged += gcnew System::EventHandler(this, &Form1::dockradio3_CheckedChanged);
			// 
			// dockradio4
			// 
			this->dockradio4->AutoSize = true;
			this->dockradio4->Location = System::Drawing::Point(2, 83);
			this->dockradio4->Name = L"dockradio4";
			this->dockradio4->Size = System::Drawing::Size(58, 17);
			this->dockradio4->TabIndex = 1;
			this->dockradio4->Text = L"dock 4";
			this->dockradio4->UseVisualStyleBackColor = true;
			this->dockradio4->CheckedChanged += gcnew System::EventHandler(this, &Form1::dockradio4_CheckedChanged);
			// 
			// dockradio1
			// 
			this->dockradio1->AutoSize = true;
			this->dockradio1->Checked = true;
			this->dockradio1->Location = System::Drawing::Point(3, 16);
			this->dockradio1->Name = L"dockradio1";
			this->dockradio1->Size = System::Drawing::Size(58, 17);
			this->dockradio1->TabIndex = 0;
			this->dockradio1->TabStop = true;
			this->dockradio1->Text = L"dock 1";
			this->dockradio1->UseVisualStyleBackColor = true;
			this->dockradio1->CheckedChanged += gcnew System::EventHandler(this, &Form1::dockradio1_CheckedChanged);
			// 
			// plansList
			// 
			this->plansList->FormattingEnabled = true;
			this->plansList->Location = System::Drawing::Point(217, 39);
			this->plansList->Name = L"plansList";
			this->plansList->Size = System::Drawing::Size(260, 108);
			this->plansList->TabIndex = 47;
			this->plansList->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::plansList_SelectedIndexChanged);
			// 
			// fish2
			// 
			this->fish2->Location = System::Drawing::Point(613, 185);
			this->fish2->Name = L"fish2";
			this->fish2->Size = System::Drawing::Size(100, 100);
			this->fish2->TabIndex = 46;
			// 
			// fish1
			// 
			this->fish1->Location = System::Drawing::Point(498, 185);
			this->fish1->Name = L"fish1";
			this->fish1->Size = System::Drawing::Size(100, 100);
			this->fish1->TabIndex = 45;
			// 
			// pondConfigPanel
			// 
			this->pondConfigPanel->Controls->Add(this->pondFisherY);
			this->pondConfigPanel->Controls->Add(this->pondFisherX);
			this->pondConfigPanel->Controls->Add(this->label26);
			this->pondConfigPanel->Controls->Add(this->label27);
			this->pondConfigPanel->Controls->Add(this->pondDockY);
			this->pondConfigPanel->Controls->Add(this->pondDockX);
			this->pondConfigPanel->Controls->Add(this->label28);
			this->pondConfigPanel->Controls->Add(this->label29);
			this->pondConfigPanel->Controls->Add(this->pondPondHeight);
			this->pondConfigPanel->Controls->Add(this->pondPondWidth);
			this->pondConfigPanel->Controls->Add(this->pondPondY);
			this->pondConfigPanel->Controls->Add(this->pondPondX);
			this->pondConfigPanel->Controls->Add(this->label19);
			this->pondConfigPanel->Controls->Add(this->label23);
			this->pondConfigPanel->Controls->Add(this->label24);
			this->pondConfigPanel->Controls->Add(this->label25);
			this->pondConfigPanel->Controls->Add(this->pondFishT);
			this->pondConfigPanel->Controls->Add(this->pondFishB);
			this->pondConfigPanel->Controls->Add(this->pondFishG);
			this->pondConfigPanel->Controls->Add(this->pondFishR);
			this->pondConfigPanel->Controls->Add(this->label22);
			this->pondConfigPanel->Controls->Add(this->label21);
			this->pondConfigPanel->Controls->Add(this->label20);
			this->pondConfigPanel->Controls->Add(this->label6);
			this->pondConfigPanel->Location = System::Drawing::Point(17, 128);
			this->pondConfigPanel->Name = L"pondConfigPanel";
			this->pondConfigPanel->Size = System::Drawing::Size(318, 202);
			this->pondConfigPanel->TabIndex = 42;
			// 
			// pondFisherY
			// 
			this->pondFisherY->Location = System::Drawing::Point(243, 173);
			this->pondFisherY->Name = L"pondFisherY";
			this->pondFisherY->Size = System::Drawing::Size(61, 20);
			this->pondFisherY->TabIndex = 26;
			this->pondFisherY->TextChanged += gcnew System::EventHandler(this, &Form1::pondFisherY_TextChanged);
			// 
			// pondFisherX
			// 
			this->pondFisherX->Location = System::Drawing::Point(243, 147);
			this->pondFisherX->Name = L"pondFisherX";
			this->pondFisherX->Size = System::Drawing::Size(61, 20);
			this->pondFisherX->TabIndex = 25;
			this->pondFisherX->TextChanged += gcnew System::EventHandler(this, &Form1::pondFisherX_TextChanged);
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(192, 176);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(45, 13);
			this->label26->TabIndex = 24;
			this->label26->Text = L"Fisher Y";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(192, 150);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(45, 13);
			this->label27->TabIndex = 23;
			this->label27->Text = L"Fisher X";
			// 
			// pondDockY
			// 
			this->pondDockY->Location = System::Drawing::Point(82, 173);
			this->pondDockY->Name = L"pondDockY";
			this->pondDockY->Size = System::Drawing::Size(61, 20);
			this->pondDockY->TabIndex = 22;
			this->pondDockY->TextChanged += gcnew System::EventHandler(this, &Form1::pondDockY_TextChanged);
			// 
			// pondDockX
			// 
			this->pondDockX->Location = System::Drawing::Point(82, 147);
			this->pondDockX->Name = L"pondDockX";
			this->pondDockX->Size = System::Drawing::Size(61, 20);
			this->pondDockX->TabIndex = 21;
			this->pondDockX->TextChanged += gcnew System::EventHandler(this, &Form1::pondDockX_TextChanged);
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(34, 173);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(43, 13);
			this->label28->TabIndex = 20;
			this->label28->Text = L"Dock Y";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(34, 150);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(43, 13);
			this->label29->TabIndex = 19;
			this->label29->Text = L"Dock X";
			// 
			// pondPondHeight
			// 
			this->pondPondHeight->Location = System::Drawing::Point(243, 121);
			this->pondPondHeight->Name = L"pondPondHeight";
			this->pondPondHeight->Size = System::Drawing::Size(61, 20);
			this->pondPondHeight->TabIndex = 18;
			this->pondPondHeight->TextChanged += gcnew System::EventHandler(this, &Form1::pondPondHeight_TextChanged);
			// 
			// pondPondWidth
			// 
			this->pondPondWidth->Location = System::Drawing::Point(243, 95);
			this->pondPondWidth->Name = L"pondPondWidth";
			this->pondPondWidth->Size = System::Drawing::Size(61, 20);
			this->pondPondWidth->TabIndex = 17;
			this->pondPondWidth->TextChanged += gcnew System::EventHandler(this, &Form1::pondPondWidth_TextChanged);
			// 
			// pondPondY
			// 
			this->pondPondY->Location = System::Drawing::Point(243, 69);
			this->pondPondY->Name = L"pondPondY";
			this->pondPondY->Size = System::Drawing::Size(61, 20);
			this->pondPondY->TabIndex = 16;
			this->pondPondY->TextChanged += gcnew System::EventHandler(this, &Form1::pondPondY_TextChanged);
			// 
			// pondPondX
			// 
			this->pondPondX->Location = System::Drawing::Point(243, 43);
			this->pondPondX->Name = L"pondPondX";
			this->pondPondX->Size = System::Drawing::Size(61, 20);
			this->pondPondX->TabIndex = 15;
			this->pondPondX->TextChanged += gcnew System::EventHandler(this, &Form1::pondPondX_TextChanged);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(195, 46);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(42, 13);
			this->label19->TabIndex = 14;
			this->label19->Text = L"Pond X";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(195, 72);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(42, 13);
			this->label23->TabIndex = 13;
			this->label23->Text = L"Pond Y";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(171, 124);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(66, 13);
			this->label24->TabIndex = 12;
			this->label24->Text = L"Pond Height";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(174, 98);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(63, 13);
			this->label25->TabIndex = 11;
			this->label25->Text = L"Pond Width";
			// 
			// pondFishT
			// 
			this->pondFishT->Location = System::Drawing::Point(82, 121);
			this->pondFishT->Name = L"pondFishT";
			this->pondFishT->Size = System::Drawing::Size(61, 20);
			this->pondFishT->TabIndex = 10;
			this->pondFishT->TextChanged += gcnew System::EventHandler(this, &Form1::pondFishT_TextChanged);
			// 
			// pondFishB
			// 
			this->pondFishB->Location = System::Drawing::Point(82, 95);
			this->pondFishB->Name = L"pondFishB";
			this->pondFishB->Size = System::Drawing::Size(61, 20);
			this->pondFishB->TabIndex = 9;
			this->pondFishB->TextChanged += gcnew System::EventHandler(this, &Form1::pondFishB_TextChanged);
			// 
			// pondFishG
			// 
			this->pondFishG->Location = System::Drawing::Point(82, 69);
			this->pondFishG->Name = L"pondFishG";
			this->pondFishG->Size = System::Drawing::Size(61, 20);
			this->pondFishG->TabIndex = 8;
			this->pondFishG->TextChanged += gcnew System::EventHandler(this, &Form1::pondFishG_TextChanged);
			// 
			// pondFishR
			// 
			this->pondFishR->Location = System::Drawing::Point(82, 43);
			this->pondFishR->Name = L"pondFishR";
			this->pondFishR->Size = System::Drawing::Size(61, 20);
			this->pondFishR->TabIndex = 7;
			this->pondFishR->TextChanged += gcnew System::EventHandler(this, &Form1::pondFishR_TextChanged);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(40, 46);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(37, 13);
			this->label22->TabIndex = 6;
			this->label22->Text = L"Fish R";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(40, 72);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(37, 13);
			this->label21->TabIndex = 5;
			this->label21->Text = L"Fish G";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(41, 124);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(36, 13);
			this->label20->TabIndex = 4;
			this->label20->Text = L"Fish T";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(41, 98);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(36, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Fish B";
			// 
			// StartFishing
			// 
			this->StartFishing->Location = System::Drawing::Point(17, 102);
			this->StartFishing->Name = L"StartFishing";
			this->StartFishing->Size = System::Drawing::Size(75, 23);
			this->StartFishing->TabIndex = 41;
			this->StartFishing->Text = L"start fishing";
			this->StartFishing->UseVisualStyleBackColor = true;
			this->StartFishing->Click += gcnew System::EventHandler(this, &Form1::StartFishing_Click);
			// 
			// MoveMouse
			// 
			this->MoveMouse->Location = System::Drawing::Point(17, 73);
			this->MoveMouse->Name = L"MoveMouse";
			this->MoveMouse->Size = System::Drawing::Size(75, 23);
			this->MoveMouse->TabIndex = 38;
			this->MoveMouse->Text = L"Test Scan";
			this->MoveMouse->UseVisualStyleBackColor = true;
			this->MoveMouse->Click += gcnew System::EventHandler(this, &Form1::MoveMouse_Click);
			// 
			// ReshapeButton
			// 
			this->ReshapeButton->Location = System::Drawing::Point(17, 44);
			this->ReshapeButton->Name = L"ReshapeButton";
			this->ReshapeButton->Size = System::Drawing::Size(75, 23);
			this->ReshapeButton->TabIndex = 37;
			this->ReshapeButton->Text = L"Reshape";
			this->ReshapeButton->UseVisualStyleBackColor = true;
			this->ReshapeButton->Click += gcnew System::EventHandler(this, &Form1::ReshapeButton_Click);
			// 
			// WindowShape
			// 
			this->WindowShape->AutoSize = true;
			this->WindowShape->Location = System::Drawing::Point(352, 302);
			this->WindowShape->Name = L"WindowShape";
			this->WindowShape->Size = System::Drawing::Size(77, 13);
			this->WindowShape->TabIndex = 36;
			this->WindowShape->Text = L"WindowShape";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(147, 66);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(23, 13);
			this->label14->TabIndex = 34;
			this->label14->Text = L"fish";
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->label15);
			this->panel3->Controls->Add(this->label16);
			this->panel3->Controls->Add(this->label17);
			this->panel3->Controls->Add(this->label18);
			this->panel3->Controls->Add(this->fishYSpeed);
			this->panel3->Controls->Add(this->fishLocY);
			this->panel3->Controls->Add(this->fishXSpeed);
			this->panel3->Controls->Add(this->fishLocX);
			this->panel3->Location = System::Drawing::Point(498, 39);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(190, 134);
			this->panel3->TabIndex = 33;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(36, 44);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(14, 13);
			this->label15->TabIndex = 33;
			this->label15->Text = L"Y";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(4, 70);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(46, 13);
			this->label16->TabIndex = 32;
			this->label16->Text = L"speed X";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(4, 96);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(46, 13);
			this->label17->TabIndex = 31;
			this->label17->Text = L"speed Y";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(36, 12);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(14, 13);
			this->label18->TabIndex = 30;
			this->label18->Text = L"X";
			// 
			// fishYSpeed
			// 
			this->fishYSpeed->Location = System::Drawing::Point(53, 89);
			this->fishYSpeed->Name = L"fishYSpeed";
			this->fishYSpeed->Size = System::Drawing::Size(100, 20);
			this->fishYSpeed->TabIndex = 29;
			// 
			// fishLocY
			// 
			this->fishLocY->Location = System::Drawing::Point(53, 37);
			this->fishLocY->Name = L"fishLocY";
			this->fishLocY->Size = System::Drawing::Size(100, 20);
			this->fishLocY->TabIndex = 28;
			// 
			// fishXSpeed
			// 
			this->fishXSpeed->Location = System::Drawing::Point(53, 63);
			this->fishXSpeed->Name = L"fishXSpeed";
			this->fishXSpeed->Size = System::Drawing::Size(100, 20);
			this->fishXSpeed->TabIndex = 27;
			// 
			// fishLocX
			// 
			this->fishLocX->Location = System::Drawing::Point(53, 9);
			this->fishLocX->Name = L"fishLocX";
			this->fishLocX->Size = System::Drawing::Size(100, 20);
			this->fishLocX->TabIndex = 26;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(14, 13);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Description";
			// 
			// pondDescription
			// 
			this->pondDescription->Location = System::Drawing::Point(79, 11);
			this->pondDescription->Name = L"pondDescription";
			this->pondDescription->Size = System::Drawing::Size(256, 20);
			this->pondDescription->TabIndex = 0;
			this->pondDescription->TextChanged += gcnew System::EventHandler(this, &Form1::pondDescription_TextChanged);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->playview);
			this->tabPage1->Controls->Add(this->perfectShots);
			this->tabPage1->Controls->Add(this->centerCast);
			this->tabPage1->Controls->Add(this->CastGroup);
			this->tabPage1->Controls->Add(this->scanResults);
			this->tabPage1->Controls->Add(this->ScanButton);
			this->tabPage1->Controls->Add(this->label32);
			this->tabPage1->Controls->Add(this->label31);
			this->tabPage1->Controls->Add(this->turnTime);
			this->tabPage1->Controls->Add(this->holdTime);
			this->tabPage1->Controls->Add(this->startScanner);
			this->tabPage1->Controls->Add(this->StillGolfing);
			this->tabPage1->Controls->Add(this->GolfMoves);
			this->tabPage1->Controls->Add(this->GolfHole);
			this->tabPage1->Controls->Add(this->findbase);
			this->tabPage1->Controls->Add(this->label30);
			this->tabPage1->Controls->Add(this->golfDelay);
			this->tabPage1->Controls->Add(this->startGolfing);
			this->tabPage1->Controls->Add(this->GolfCourses);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(715, 485);
			this->tabPage1->TabIndex = 1;
			this->tabPage1->Text = L"Tiger Toon";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// playview
			// 
			this->playview->Location = System::Drawing::Point(10, 533);
			this->playview->Name = L"playview";
			this->playview->Size = System::Drawing::Size(856, 37);
			this->playview->TabIndex = 18;
			// 
			// perfectShots
			// 
			this->perfectShots->AutoSize = true;
			this->perfectShots->Location = System::Drawing::Point(229, 26);
			this->perfectShots->Name = L"perfectShots";
			this->perfectShots->Size = System::Drawing::Size(87, 17);
			this->perfectShots->TabIndex = 17;
			this->perfectShots->Text = L"perfect shots";
			this->perfectShots->UseVisualStyleBackColor = true;
			// 
			// centerCast
			// 
			this->centerCast->AutoSize = true;
			this->centerCast->Location = System::Drawing::Point(291, 150);
			this->centerCast->Name = L"centerCast";
			this->centerCast->Size = System::Drawing::Size(112, 17);
			this->centerCast->TabIndex = 16;
			this->centerCast->Text = L"center before cast";
			this->centerCast->UseVisualStyleBackColor = true;
			// 
			// CastGroup
			// 
			this->CastGroup->Controls->Add(this->castCenterButton);
			this->CastGroup->Controls->Add(this->castRightButton);
			this->CastGroup->Controls->Add(this->castLeftButton);
			this->CastGroup->Location = System::Drawing::Point(200, 150);
			this->CastGroup->Name = L"CastGroup";
			this->CastGroup->Size = System::Drawing::Size(77, 100);
			this->CastGroup->TabIndex = 15;
			this->CastGroup->TabStop = false;
			this->CastGroup->Text = L"Cast";
			// 
			// castCenterButton
			// 
			this->castCenterButton->AutoSize = true;
			this->castCenterButton->Location = System::Drawing::Point(6, 42);
			this->castCenterButton->Name = L"castCenterButton";
			this->castCenterButton->Size = System::Drawing::Size(56, 17);
			this->castCenterButton->TabIndex = 2;
			this->castCenterButton->TabStop = true;
			this->castCenterButton->Text = L"Center";
			this->castCenterButton->UseVisualStyleBackColor = true;
			// 
			// castRightButton
			// 
			this->castRightButton->AutoSize = true;
			this->castRightButton->Location = System::Drawing::Point(6, 65);
			this->castRightButton->Name = L"castRightButton";
			this->castRightButton->Size = System::Drawing::Size(50, 17);
			this->castRightButton->TabIndex = 1;
			this->castRightButton->TabStop = true;
			this->castRightButton->Text = L"Right";
			this->castRightButton->UseVisualStyleBackColor = true;
			// 
			// castLeftButton
			// 
			this->castLeftButton->AutoSize = true;
			this->castLeftButton->Location = System::Drawing::Point(6, 19);
			this->castLeftButton->Name = L"castLeftButton";
			this->castLeftButton->Size = System::Drawing::Size(43, 17);
			this->castLeftButton->TabIndex = 0;
			this->castLeftButton->TabStop = true;
			this->castLeftButton->Text = L"Left";
			this->castLeftButton->UseVisualStyleBackColor = true;
			// 
			// scanResults
			// 
			this->scanResults->Location = System::Drawing::Point(50, 494);
			this->scanResults->Name = L"scanResults";
			this->scanResults->Size = System::Drawing::Size(751, 20);
			this->scanResults->TabIndex = 14;
			// 
			// ScanButton
			// 
			this->ScanButton->Location = System::Drawing::Point(50, 452);
			this->ScanButton->Name = L"ScanButton";
			this->ScanButton->Size = System::Drawing::Size(75, 23);
			this->ScanButton->TabIndex = 13;
			this->ScanButton->Text = L"Scan";
			this->ScanButton->UseVisualStyleBackColor = true;
			this->ScanButton->Click += gcnew System::EventHandler(this, &Form1::ScanButton_Click);
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(285, 203);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(55, 13);
			this->label32->TabIndex = 12;
			this->label32->Text = L"Turn Time";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(288, 173);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(54, 13);
			this->label31->TabIndex = 11;
			this->label31->Text = L"Cast Time";
			// 
			// turnTime
			// 
			this->turnTime->Location = System::Drawing::Point(359, 196);
			this->turnTime->Name = L"turnTime";
			this->turnTime->Size = System::Drawing::Size(100, 20);
			this->turnTime->TabIndex = 10;
			this->turnTime->Text = L"0";
			// 
			// holdTime
			// 
			this->holdTime->Location = System::Drawing::Point(359, 170);
			this->holdTime->Name = L"holdTime";
			this->holdTime->Size = System::Drawing::Size(100, 20);
			this->holdTime->TabIndex = 9;
			this->holdTime->Text = L"27";
			// 
			// startScanner
			// 
			this->startScanner->Location = System::Drawing::Point(10, 105);
			this->startScanner->Name = L"startScanner";
			this->startScanner->Size = System::Drawing::Size(83, 23);
			this->startScanner->TabIndex = 8;
			this->startScanner->Text = L"StartScanner";
			this->startScanner->UseVisualStyleBackColor = true;
			this->startScanner->Click += gcnew System::EventHandler(this, &Form1::startScanner_Click);
			// 
			// StillGolfing
			// 
			this->StillGolfing->Location = System::Drawing::Point(10, 76);
			this->StillGolfing->Name = L"StillGolfing";
			this->StillGolfing->Size = System::Drawing::Size(83, 23);
			this->StillGolfing->TabIndex = 7;
			this->StillGolfing->Text = L"Still Golfing";
			this->StillGolfing->UseVisualStyleBackColor = true;
			this->StillGolfing->Click += gcnew System::EventHandler(this, &Form1::StillGolfing_Click);
			// 
			// GolfMoves
			// 
			this->GolfMoves->Controls->Add(this->GolfTap);
			this->GolfMoves->Controls->Add(this->PerfectHit);
			this->GolfMoves->Controls->Add(this->GolfMiss);
			this->GolfMoves->Location = System::Drawing::Point(200, 256);
			this->GolfMoves->Name = L"GolfMoves";
			this->GolfMoves->Size = System::Drawing::Size(267, 62);
			this->GolfMoves->TabIndex = 6;
			this->GolfMoves->TabStop = false;
			this->GolfMoves->Text = L"Golf Moves";
			// 
			// GolfTap
			// 
			this->GolfTap->Location = System::Drawing::Point(92, 19);
			this->GolfTap->Name = L"GolfTap";
			this->GolfTap->Size = System::Drawing::Size(75, 23);
			this->GolfTap->TabIndex = 2;
			this->GolfTap->Text = L"Tap";
			this->GolfTap->UseVisualStyleBackColor = true;
			this->GolfTap->Click += gcnew System::EventHandler(this, &Form1::GolfTap_Click);
			// 
			// PerfectHit
			// 
			this->PerfectHit->Location = System::Drawing::Point(173, 19);
			this->PerfectHit->Name = L"PerfectHit";
			this->PerfectHit->Size = System::Drawing::Size(75, 23);
			this->PerfectHit->TabIndex = 1;
			this->PerfectHit->Text = L"Perfect";
			this->PerfectHit->UseVisualStyleBackColor = true;
			this->PerfectHit->Click += gcnew System::EventHandler(this, &Form1::PerfectHit_Click);
			// 
			// GolfMiss
			// 
			this->GolfMiss->Location = System::Drawing::Point(11, 19);
			this->GolfMiss->Name = L"GolfMiss";
			this->GolfMiss->Size = System::Drawing::Size(75, 23);
			this->GolfMiss->TabIndex = 0;
			this->GolfMiss->Text = L"Miss";
			this->GolfMiss->UseVisualStyleBackColor = true;
			this->GolfMiss->Click += gcnew System::EventHandler(this, &Form1::GolfMiss_Click);
			// 
			// GolfHole
			// 
			this->GolfHole->FormattingEnabled = true;
			this->GolfHole->Location = System::Drawing::Point(10, 150);
			this->GolfHole->Name = L"GolfHole";
			this->GolfHole->Size = System::Drawing::Size(171, 173);
			this->GolfHole->TabIndex = 5;
			// 
			// findbase
			// 
			this->findbase->Location = System::Drawing::Point(10, 20);
			this->findbase->Name = L"findbase";
			this->findbase->Size = System::Drawing::Size(83, 23);
			this->findbase->TabIndex = 4;
			this->findbase->Text = L"Find Base";
			this->findbase->UseVisualStyleBackColor = true;
			this->findbase->Click += gcnew System::EventHandler(this, &Form1::findbase_Click);
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(226, 52);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(72, 13);
			this->label30->TabIndex = 3;
			this->label30->Text = L"First Hit Delay";
			// 
			// golfDelay
			// 
			this->golfDelay->Location = System::Drawing::Point(304, 48);
			this->golfDelay->Name = L"golfDelay";
			this->golfDelay->Size = System::Drawing::Size(100, 20);
			this->golfDelay->TabIndex = 2;
			this->golfDelay->Text = L"0";
			// 
			// startGolfing
			// 
			this->startGolfing->Location = System::Drawing::Point(10, 47);
			this->startGolfing->Name = L"startGolfing";
			this->startGolfing->Size = System::Drawing::Size(83, 23);
			this->startGolfing->TabIndex = 1;
			this->startGolfing->Text = L"Start Golfing";
			this->startGolfing->UseVisualStyleBackColor = true;
			this->startGolfing->Click += gcnew System::EventHandler(this, &Form1::startGolfing_Click);
			// 
			// GolfCourses
			// 
			this->GolfCourses->Controls->Add(this->largeCourseRadio);
			this->GolfCourses->Controls->Add(this->mediumCourseRadio);
			this->GolfCourses->Controls->Add(this->smallCourseRadio);
			this->GolfCourses->Location = System::Drawing::Point(110, 20);
			this->GolfCourses->Name = L"GolfCourses";
			this->GolfCourses->Size = System::Drawing::Size(108, 108);
			this->GolfCourses->TabIndex = 0;
			this->GolfCourses->TabStop = false;
			this->GolfCourses->Text = L"Courses";
			// 
			// largeCourseRadio
			// 
			this->largeCourseRadio->AutoSize = true;
			this->largeCourseRadio->Location = System::Drawing::Point(24, 65);
			this->largeCourseRadio->Name = L"largeCourseRadio";
			this->largeCourseRadio->Size = System::Drawing::Size(52, 17);
			this->largeCourseRadio->TabIndex = 2;
			this->largeCourseRadio->Text = L"Large";
			this->largeCourseRadio->UseVisualStyleBackColor = true;
			this->largeCourseRadio->CheckedChanged += gcnew System::EventHandler(this, &Form1::largeCourseRadio_CheckedChanged);
			// 
			// mediumCourseRadio
			// 
			this->mediumCourseRadio->AutoSize = true;
			this->mediumCourseRadio->Location = System::Drawing::Point(24, 42);
			this->mediumCourseRadio->Name = L"mediumCourseRadio";
			this->mediumCourseRadio->Size = System::Drawing::Size(62, 17);
			this->mediumCourseRadio->TabIndex = 1;
			this->mediumCourseRadio->Text = L"Medium";
			this->mediumCourseRadio->UseVisualStyleBackColor = true;
			this->mediumCourseRadio->CheckedChanged += gcnew System::EventHandler(this, &Form1::mediumCourseRadio_CheckedChanged);
			// 
			// smallCourseRadio
			// 
			this->smallCourseRadio->AutoSize = true;
			this->smallCourseRadio->Checked = true;
			this->smallCourseRadio->Location = System::Drawing::Point(24, 19);
			this->smallCourseRadio->Name = L"smallCourseRadio";
			this->smallCourseRadio->Size = System::Drawing::Size(50, 17);
			this->smallCourseRadio->TabIndex = 0;
			this->smallCourseRadio->TabStop = true;
			this->smallCourseRadio->Text = L"Small";
			this->smallCourseRadio->UseVisualStyleBackColor = true;
			this->smallCourseRadio->CheckedChanged += gcnew System::EventHandler(this, &Form1::smallCourseRadio_CheckedChanged);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->button1);
			this->tabPage2->Controls->Add(this->counterBox);
			this->tabPage2->Controls->Add(this->onWin);
			this->tabPage2->Controls->Add(this->grandPrix);
			this->tabPage2->Controls->Add(this->bitBlit);
			this->tabPage2->Controls->Add(this->raceTrack);
			this->tabPage2->Controls->Add(this->justRace);
			this->tabPage2->Controls->Add(this->raceScanOut);
			this->tabPage2->Controls->Add(this->RunThere);
			this->tabPage2->Controls->Add(this->roadBox);
			this->tabPage2->Controls->Add(this->middle);
			this->tabPage2->Controls->Add(this->thresholdTxt);
			this->tabPage2->Controls->Add(this->toonThreshold);
			this->tabPage2->Controls->Add(this->tallToon);
			this->tabPage2->Controls->Add(this->toonViewPanel);
			this->tabPage2->Controls->Add(this->raceScanButton);
			this->tabPage2->Controls->Add(this->groupBox2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(715, 485);
			this->tabPage2->TabIndex = 2;
			this->tabPage2->Text = L"Racer";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(10, 20);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(83, 23);
			this->button1->TabIndex = 17;
			this->button1->Text = L"Find Base";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// counterBox
			// 
			this->counterBox->Location = System::Drawing::Point(10, 134);
			this->counterBox->Name = L"counterBox";
			this->counterBox->Size = System::Drawing::Size(100, 20);
			this->counterBox->TabIndex = 16;
			this->counterBox->Text = L"0";
			// 
			// onWin
			// 
			this->onWin->AutoSize = true;
			this->onWin->Location = System::Drawing::Point(113, 24);
			this->onWin->Name = L"onWin";
			this->onWin->Size = System::Drawing::Size(65, 17);
			this->onWin->TabIndex = 15;
			this->onWin->Text = L"won win";
			this->onWin->UseVisualStyleBackColor = true;
			// 
			// grandPrix
			// 
			this->grandPrix->AutoSize = true;
			this->grandPrix->Location = System::Drawing::Point(113, 53);
			this->grandPrix->Name = L"grandPrix";
			this->grandPrix->Size = System::Drawing::Size(75, 17);
			this->grandPrix->TabIndex = 14;
			this->grandPrix->Text = L"Grand Prix";
			this->grandPrix->UseVisualStyleBackColor = true;
			// 
			// bitBlit
			// 
			this->bitBlit->AutoSize = true;
			this->bitBlit->Location = System::Drawing::Point(113, 109);
			this->bitBlit->Name = L"bitBlit";
			this->bitBlit->Size = System::Drawing::Size(51, 17);
			this->bitBlit->TabIndex = 13;
			this->bitBlit->Text = L"bitBlit";
			this->bitBlit->UseVisualStyleBackColor = true;
			// 
			// raceTrack
			// 
			this->raceTrack->Location = System::Drawing::Point(534, 24);
			this->raceTrack->Name = L"raceTrack";
			this->raceTrack->Size = System::Drawing::Size(100, 20);
			this->raceTrack->TabIndex = 12;
			this->raceTrack->Text = L"0";
			// 
			// justRace
			// 
			this->justRace->Location = System::Drawing::Point(10, 49);
			this->justRace->Name = L"justRace";
			this->justRace->Size = System::Drawing::Size(83, 23);
			this->justRace->TabIndex = 11;
			this->justRace->Text = L"Just Race";
			this->justRace->UseVisualStyleBackColor = true;
			this->justRace->Click += gcnew System::EventHandler(this, &Form1::justRace_Click);
			// 
			// raceScanOut
			// 
			this->raceScanOut->Location = System::Drawing::Point(640, 24);
			this->raceScanOut->Name = L"raceScanOut";
			this->raceScanOut->Size = System::Drawing::Size(327, 20);
			this->raceScanOut->TabIndex = 10;
			// 
			// RunThere
			// 
			this->RunThere->Location = System::Drawing::Point(10, 76);
			this->RunThere->Name = L"RunThere";
			this->RunThere->Size = System::Drawing::Size(83, 23);
			this->RunThere->TabIndex = 9;
			this->RunThere->Text = L"Run There";
			this->RunThere->UseVisualStyleBackColor = true;
			this->RunThere->Click += gcnew System::EventHandler(this, &Form1::RunThere_Click);
			// 
			// roadBox
			// 
			this->roadBox->Location = System::Drawing::Point(317, 134);
			this->roadBox->Name = L"roadBox";
			this->roadBox->Size = System::Drawing::Size(100, 20);
			this->roadBox->TabIndex = 8;
			this->roadBox->Text = L"0";
			this->roadBox->TextChanged += gcnew System::EventHandler(this, &Form1::roadBox_TextChanged);
			// 
			// middle
			// 
			this->middle->Location = System::Drawing::Point(423, 134);
			this->middle->Name = L"middle";
			this->middle->Size = System::Drawing::Size(100, 20);
			this->middle->TabIndex = 6;
			// 
			// thresholdTxt
			// 
			this->thresholdTxt->AutoSize = true;
			this->thresholdTxt->Location = System::Drawing::Point(152, 137);
			this->thresholdTxt->Name = L"thresholdTxt";
			this->thresholdTxt->Size = System::Drawing::Size(53, 13);
			this->thresholdTxt->TabIndex = 5;
			this->thresholdTxt->Text = L"thresthold";
			// 
			// toonThreshold
			// 
			this->toonThreshold->Location = System::Drawing::Point(211, 134);
			this->toonThreshold->Name = L"toonThreshold";
			this->toonThreshold->Size = System::Drawing::Size(100, 20);
			this->toonThreshold->TabIndex = 4;
			this->toonThreshold->Text = L"120";
			this->toonThreshold->TextChanged += gcnew System::EventHandler(this, &Form1::toonThreshold_TextChanged);
			// 
			// tallToon
			// 
			this->tallToon->AutoSize = true;
			this->tallToon->Location = System::Drawing::Point(113, 80);
			this->tallToon->Name = L"tallToon";
			this->tallToon->Size = System::Drawing::Size(67, 17);
			this->tallToon->TabIndex = 3;
			this->tallToon->Text = L"tall Toon";
			this->tallToon->UseVisualStyleBackColor = true;
			this->tallToon->CheckedChanged += gcnew System::EventHandler(this, &Form1::tallToon_CheckedChanged);
			// 
			// toonViewPanel
			// 
			this->toonViewPanel->Location = System::Drawing::Point(29, 171);
			this->toonViewPanel->Name = L"toonViewPanel";
			this->toonViewPanel->Size = System::Drawing::Size(640, 480);
			this->toonViewPanel->TabIndex = 2;
			// 
			// raceScanButton
			// 
			this->raceScanButton->Location = System::Drawing::Point(10, 105);
			this->raceScanButton->Name = L"raceScanButton";
			this->raceScanButton->Size = System::Drawing::Size(83, 23);
			this->raceScanButton->TabIndex = 1;
			this->raceScanButton->Text = L"Race Scan";
			this->raceScanButton->UseVisualStyleBackColor = true;
			this->raceScanButton->Click += gcnew System::EventHandler(this, &Form1::raceScanButton_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->cityRadio);
			this->groupBox2->Controls->Add(this->rusticRadio);
			this->groupBox2->Controls->Add(this->screwballRadio);
			this->groupBox2->Location = System::Drawing::Point(211, 24);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(149, 96);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Race tracks";
			// 
			// cityRadio
			// 
			this->cityRadio->AutoSize = true;
			this->cityRadio->Location = System::Drawing::Point(11, 62);
			this->cityRadio->Name = L"cityRadio";
			this->cityRadio->Size = System::Drawing::Size(74, 17);
			this->cityRadio->TabIndex = 2;
			this->cityRadio->TabStop = true;
			this->cityRadio->Text = L"City Circuit";
			this->cityRadio->UseVisualStyleBackColor = true;
			// 
			// rusticRadio
			// 
			this->rusticRadio->AutoSize = true;
			this->rusticRadio->Location = System::Drawing::Point(11, 39);
			this->rusticRadio->Name = L"rusticRadio";
			this->rusticRadio->Size = System::Drawing::Size(103, 17);
			this->rusticRadio->TabIndex = 1;
			this->rusticRadio->TabStop = true;
			this->rusticRadio->Text = L"Rustic Raceway";
			this->rusticRadio->UseVisualStyleBackColor = true;
			// 
			// screwballRadio
			// 
			this->screwballRadio->AutoSize = true;
			this->screwballRadio->Location = System::Drawing::Point(11, 16);
			this->screwballRadio->Name = L"screwballRadio";
			this->screwballRadio->Size = System::Drawing::Size(112, 17);
			this->screwballRadio->TabIndex = 0;
			this->screwballRadio->TabStop = true;
			this->screwballRadio->Text = L"Screwball Stadium";
			this->screwballRadio->UseVisualStyleBackColor = true;
			// 
			// multiTab
			// 
			this->multiTab->Controls->Add(this->statusBox);
			this->multiTab->Controls->Add(this->label36);
			this->multiTab->Controls->Add(this->label35);
			this->multiTab->Controls->Add(this->label34);
			this->multiTab->Controls->Add(this->label33);
			this->multiTab->Controls->Add(this->pushVals);
			this->multiTab->Controls->Add(this->TrackBox);
			this->multiTab->Controls->Add(this->HBox);
			this->multiTab->Controls->Add(this->ZBox);
			this->multiTab->Controls->Add(this->YBox);
			this->multiTab->Controls->Add(this->XBox);
			this->multiTab->Controls->Add(this->alignToons);
			this->multiTab->Controls->Add(this->followToon);
			this->multiTab->Location = System::Drawing::Point(4, 22);
			this->multiTab->Name = L"multiTab";
			this->multiTab->Padding = System::Windows::Forms::Padding(3);
			this->multiTab->Size = System::Drawing::Size(715, 485);
			this->multiTab->TabIndex = 4;
			this->multiTab->Text = L"MultiToon";
			this->multiTab->UseVisualStyleBackColor = true;
			// 
			// statusBox
			// 
			this->statusBox->Location = System::Drawing::Point(197, 181);
			this->statusBox->Name = L"statusBox";
			this->statusBox->Size = System::Drawing::Size(100, 20);
			this->statusBox->TabIndex = 12;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(150, 126);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(15, 13);
			this->label36->TabIndex = 11;
			this->label36->Text = L"H";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(150, 103);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(14, 13);
			this->label35->TabIndex = 10;
			this->label35->Text = L"Z";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(150, 77);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(14, 13);
			this->label34->TabIndex = 9;
			this->label34->Text = L"Y";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(150, 51);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(14, 13);
			this->label33->TabIndex = 8;
			this->label33->Text = L"X";
			// 
			// pushVals
			// 
			this->pushVals->Location = System::Drawing::Point(207, 152);
			this->pushVals->Name = L"pushVals";
			this->pushVals->Size = System::Drawing::Size(75, 23);
			this->pushVals->TabIndex = 7;
			this->pushVals->Text = L"button2";
			this->pushVals->UseVisualStyleBackColor = true;
			this->pushVals->Click += gcnew System::EventHandler(this, &Form1::pushVals_Click);
			// 
			// TrackBox
			// 
			this->TrackBox->AutoSize = true;
			this->TrackBox->Location = System::Drawing::Point(207, 22);
			this->TrackBox->Name = L"TrackBox";
			this->TrackBox->Size = System::Drawing::Size(94, 17);
			this->TrackBox->TabIndex = 6;
			this->TrackBox->Text = L"Track Position";
			this->TrackBox->UseVisualStyleBackColor = true;
			this->TrackBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::TrackBox_CheckedChanged);
			// 
			// HBox
			// 
			this->HBox->Location = System::Drawing::Point(197, 126);
			this->HBox->Name = L"HBox";
			this->HBox->Size = System::Drawing::Size(100, 20);
			this->HBox->TabIndex = 5;
			this->HBox->TextChanged += gcnew System::EventHandler(this, &Form1::HBox_TextChanged);
			// 
			// ZBox
			// 
			this->ZBox->Location = System::Drawing::Point(197, 100);
			this->ZBox->Name = L"ZBox";
			this->ZBox->Size = System::Drawing::Size(100, 20);
			this->ZBox->TabIndex = 4;
			this->ZBox->TextChanged += gcnew System::EventHandler(this, &Form1::ZBox_TextChanged);
			// 
			// YBox
			// 
			this->YBox->Location = System::Drawing::Point(197, 74);
			this->YBox->Name = L"YBox";
			this->YBox->Size = System::Drawing::Size(100, 20);
			this->YBox->TabIndex = 3;
			this->YBox->TextChanged += gcnew System::EventHandler(this, &Form1::YBox_TextChanged);
			// 
			// XBox
			// 
			this->XBox->Location = System::Drawing::Point(197, 48);
			this->XBox->Name = L"XBox";
			this->XBox->Size = System::Drawing::Size(100, 20);
			this->XBox->TabIndex = 2;
			this->XBox->TextChanged += gcnew System::EventHandler(this, &Form1::XBox_TextChanged);
			// 
			// alignToons
			// 
			this->alignToons->Location = System::Drawing::Point(29, 45);
			this->alignToons->Name = L"alignToons";
			this->alignToons->Size = System::Drawing::Size(75, 23);
			this->alignToons->TabIndex = 1;
			this->alignToons->Text = L"align toons";
			this->alignToons->UseVisualStyleBackColor = true;
			this->alignToons->Click += gcnew System::EventHandler(this, &Form1::alignToons_Click);
			// 
			// followToon
			// 
			this->followToon->AutoSize = true;
			this->followToon->Location = System::Drawing::Point(29, 22);
			this->followToon->Name = L"followToon";
			this->followToon->Size = System::Drawing::Size(78, 17);
			this->followToon->TabIndex = 0;
			this->followToon->Text = L"followToon";
			this->followToon->UseVisualStyleBackColor = true;
			this->followToon->CheckedChanged += gcnew System::EventHandler(this, &Form1::followToon_CheckedChanged);
			// 
			// VPTools
			// 
			this->VPTools->Controls->Add(this->VPJump);
			this->VPTools->Controls->Add(this->VPThrow);
			this->VPTools->Controls->Add(this->label38);
			this->VPTools->Controls->Add(this->VPStandAside);
			this->VPTools->Controls->Add(this->VPMiddleTopRamp);
			this->VPTools->Controls->Add(this->VPMiddlePlatform);
			this->VPTools->Controls->Add(this->button4);
			this->VPTools->Controls->Add(this->VPBottom);
			this->VPTools->Controls->Add(this->VPGetPie);
			this->VPTools->Location = System::Drawing::Point(4, 22);
			this->VPTools->Name = L"VPTools";
			this->VPTools->Size = System::Drawing::Size(715, 485);
			this->VPTools->TabIndex = 6;
			this->VPTools->Text = L"VP Tools";
			this->VPTools->UseVisualStyleBackColor = true;
			// 
			// VPJump
			// 
			this->VPJump->Location = System::Drawing::Point(237, 230);
			this->VPJump->Name = L"VPJump";
			this->VPJump->Size = System::Drawing::Size(103, 23);
			this->VPJump->TabIndex = 9;
			this->VPJump->Text = L"Jump (X)";
			this->VPJump->UseVisualStyleBackColor = true;
			this->VPJump->Click += gcnew System::EventHandler(this, &Form1::VPJump_Click);
			// 
			// VPThrow
			// 
			this->VPThrow->Location = System::Drawing::Point(128, 230);
			this->VPThrow->Name = L"VPThrow";
			this->VPThrow->Size = System::Drawing::Size(103, 23);
			this->VPThrow->TabIndex = 8;
			this->VPThrow->Text = L"Throw (RB)";
			this->VPThrow->UseVisualStyleBackColor = true;
			this->VPThrow->Click += gcnew System::EventHandler(this, &Form1::VPThrow_Click);
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(64, 28);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(329, 117);
			this->label38->TabIndex = 7;
			this->label38->Text = resources->GetString(L"label38.Text");
			// 
			// VPStandAside
			// 
			this->VPStandAside->Location = System::Drawing::Point(237, 288);
			this->VPStandAside->Name = L"VPStandAside";
			this->VPStandAside->Size = System::Drawing::Size(103, 23);
			this->VPStandAside->TabIndex = 5;
			this->VPStandAside->Text = L"Stand Aside";
			this->VPStandAside->UseVisualStyleBackColor = true;
			this->VPStandAside->Click += gcnew System::EventHandler(this, &Form1::VPStandAside_Click);
			// 
			// VPMiddleTopRamp
			// 
			this->VPMiddleTopRamp->Location = System::Drawing::Point(237, 172);
			this->VPMiddleTopRamp->Name = L"VPMiddleTopRamp";
			this->VPMiddleTopRamp->Size = System::Drawing::Size(103, 23);
			this->VPMiddleTopRamp->TabIndex = 4;
			this->VPMiddleTopRamp->Text = L"Top Ramp (Y)";
			this->VPMiddleTopRamp->UseVisualStyleBackColor = true;
			this->VPMiddleTopRamp->Click += gcnew System::EventHandler(this, &Form1::VPMiddleTopRamp_Click);
			// 
			// VPMiddlePlatform
			// 
			this->VPMiddlePlatform->Location = System::Drawing::Point(128, 201);
			this->VPMiddlePlatform->Name = L"VPMiddlePlatform";
			this->VPMiddlePlatform->Size = System::Drawing::Size(103, 23);
			this->VPMiddlePlatform->TabIndex = 3;
			this->VPMiddlePlatform->Text = L"Middle (B)";
			this->VPMiddlePlatform->UseVisualStyleBackColor = true;
			this->VPMiddlePlatform->Click += gcnew System::EventHandler(this, &Form1::VPMiddlePlatform_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(237, 201);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(103, 23);
			this->button4->TabIndex = 2;
			this->button4->Text = L"Bottom Ramp (A)";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::BottomRamp_Click);
			// 
			// VPBottom
			// 
			this->VPBottom->Location = System::Drawing::Point(128, 288);
			this->VPBottom->Name = L"VPBottom";
			this->VPBottom->Size = System::Drawing::Size(103, 23);
			this->VPBottom->TabIndex = 1;
			this->VPBottom->Text = L"Bottom";
			this->VPBottom->UseVisualStyleBackColor = true;
			this->VPBottom->Click += gcnew System::EventHandler(this, &Form1::VPBottom_Click);
			// 
			// VPGetPie
			// 
			this->VPGetPie->Location = System::Drawing::Point(128, 172);
			this->VPGetPie->Name = L"VPGetPie";
			this->VPGetPie->Size = System::Drawing::Size(103, 23);
			this->VPGetPie->TabIndex = 0;
			this->VPGetPie->Text = L"Get Pie (LB)";
			this->VPGetPie->UseVisualStyleBackColor = true;
			this->VPGetPie->Click += gcnew System::EventHandler(this, &Form1::VPGetPie_Click);
			// 
			// CJToolPage
			// 
			this->CJToolPage->Location = System::Drawing::Point(4, 22);
			this->CJToolPage->Name = L"CJToolPage";
			this->CJToolPage->Padding = System::Windows::Forms::Padding(3);
			this->CJToolPage->Size = System::Drawing::Size(715, 485);
			this->CJToolPage->TabIndex = 5;
			this->CJToolPage->Text = L"CJ Tools";
			this->CJToolPage->UseVisualStyleBackColor = true;
			// 
			// WindowPicker
			// 
			this->WindowPicker->Dock = System::Windows::Forms::DockStyle::Fill;
			this->WindowPicker->FormattingEnabled = true;
			this->WindowPicker->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"a", L"b", L"c"});
			this->WindowPicker->Location = System::Drawing::Point(0, 0);
			this->WindowPicker->Margin = System::Windows::Forms::Padding(15);
			this->WindowPicker->Name = L"WindowPicker";
			this->WindowPicker->Size = System::Drawing::Size(92, 511);
			this->WindowPicker->TabIndex = 35;
			this->WindowPicker->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::WindowPicker_SelectedIndexChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(36, 44);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(14, 13);
			this->label10->TabIndex = 33;
			this->label10->Text = L"Y";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(4, 70);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(46, 13);
			this->label11->TabIndex = 32;
			this->label11->Text = L"speed X";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(4, 96);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(46, 13);
			this->label12->TabIndex = 31;
			this->label12->Text = L"speed Y";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(36, 12);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(14, 13);
			this->label13->TabIndex = 30;
			this->label13->Text = L"X";
			// 
			// fishSpeedY
			// 
			this->fishSpeedY->Location = System::Drawing::Point(53, 89);
			this->fishSpeedY->Name = L"fishSpeedY";
			this->fishSpeedY->Size = System::Drawing::Size(100, 20);
			this->fishSpeedY->TabIndex = 29;
			// 
			// FishY
			// 
			this->FishY->Location = System::Drawing::Point(53, 37);
			this->FishY->Name = L"FishY";
			this->FishY->Size = System::Drawing::Size(100, 20);
			this->FishY->TabIndex = 28;
			// 
			// fishSpeedX
			// 
			this->fishSpeedX->Location = System::Drawing::Point(53, 63);
			this->fishSpeedX->Name = L"fishSpeedX";
			this->fishSpeedX->Size = System::Drawing::Size(100, 20);
			this->fishSpeedX->TabIndex = 27;
			// 
			// FishX
			// 
			this->FishX->Location = System::Drawing::Point(53, 9);
			this->FishX->Name = L"FishX";
			this->FishX->Size = System::Drawing::Size(100, 20);
			this->FishX->TabIndex = 26;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(68, 57);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(14, 13);
			this->label9->TabIndex = 25;
			this->label9->Text = L"Y";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(45, 83);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(35, 13);
			this->label8->TabIndex = 24;
			this->label8->Text = L"Width";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(42, 109);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(38, 13);
			this->label7->TabIndex = 23;
			this->label7->Text = L"Height";
			// 
			// PondXLabel
			// 
			this->PondXLabel->AutoSize = true;
			this->PondXLabel->Location = System::Drawing::Point(68, 25);
			this->PondXLabel->Name = L"PondXLabel";
			this->PondXLabel->Size = System::Drawing::Size(14, 13);
			this->PondXLabel->TabIndex = 22;
			this->PondXLabel->Text = L"X";
			// 
			// pondHeight
			// 
			this->pondHeight->Location = System::Drawing::Point(88, 102);
			this->pondHeight->Name = L"pondHeight";
			this->pondHeight->Size = System::Drawing::Size(100, 20);
			this->pondHeight->TabIndex = 3;
			this->pondHeight->Text = L"400";
			// 
			// pondY
			// 
			this->pondY->Location = System::Drawing::Point(88, 50);
			this->pondY->Name = L"pondY";
			this->pondY->Size = System::Drawing::Size(100, 20);
			this->pondY->TabIndex = 2;
			this->pondY->Text = L"200";
			// 
			// pondWidth
			// 
			this->pondWidth->Location = System::Drawing::Point(88, 76);
			this->pondWidth->Name = L"pondWidth";
			this->pondWidth->Size = System::Drawing::Size(100, 20);
			this->pondWidth->TabIndex = 1;
			this->pondWidth->Text = L"700";
			// 
			// pondX
			// 
			this->pondX->Location = System::Drawing::Point(88, 22);
			this->pondX->Name = L"pondX";
			this->pondX->Size = System::Drawing::Size(100, 20);
			this->pondX->TabIndex = 0;
			this->pondX->Text = L"200";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(61, 50);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(15, 13);
			this->label5->TabIndex = 23;
			this->label5->Text = L"G";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(62, 76);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(14, 13);
			this->label4->TabIndex = 22;
			this->label4->Text = L"B";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(21, 102);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(55, 13);
			this->label3->TabIndex = 21;
			this->label3->Text = L"Tolerance";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(61, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(15, 13);
			this->label1->TabIndex = 20;
			this->label1->Text = L"R";
			// 
			// ToleranceTextBox
			// 
			this->ToleranceTextBox->Location = System::Drawing::Point(82, 99);
			this->ToleranceTextBox->Name = L"ToleranceTextBox";
			this->ToleranceTextBox->Size = System::Drawing::Size(100, 20);
			this->ToleranceTextBox->TabIndex = 19;
			this->ToleranceTextBox->Text = L"10";
			// 
			// BTextBox
			// 
			this->BTextBox->Location = System::Drawing::Point(82, 73);
			this->BTextBox->Name = L"BTextBox";
			this->BTextBox->Size = System::Drawing::Size(100, 20);
			this->BTextBox->TabIndex = 18;
			this->BTextBox->Text = L"141";
			// 
			// GTextBox
			// 
			this->GTextBox->Location = System::Drawing::Point(82, 47);
			this->GTextBox->Name = L"GTextBox";
			this->GTextBox->Size = System::Drawing::Size(100, 20);
			this->GTextBox->TabIndex = 17;
			this->GTextBox->Text = L"139";
			// 
			// RTextBox
			// 
			this->RTextBox->Location = System::Drawing::Point(82, 22);
			this->RTextBox->Name = L"RTextBox";
			this->RTextBox->Size = System::Drawing::Size(100, 20);
			this->RTextBox->TabIndex = 16;
			this->RTextBox->Text = L"21";
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer1->Location = System::Drawing::Point(0, 24);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->WindowPicker);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->tabControl1);
			this->splitContainer1->Size = System::Drawing::Size(819, 511);
			this->splitContainer1->SplitterDistance = 92;
			this->splitContainer1->TabIndex = 36;
			// 
			// GolfTimer
			// 
			this->GolfTimer->Tick += gcnew System::EventHandler(this, &Form1::GolfTimer_Tick);
			// 
			// emergencyTimer
			// 
			this->emergencyTimer->Tick += gcnew System::EventHandler(this, &Form1::emergencyTimer_Tick);
			// 
			// RaceViewTimer
			// 
			this->RaceViewTimer->Tick += gcnew System::EventHandler(this, &Form1::RaceViewTimer_Tick);
			// 
			// RaceTimer
			// 
			this->RaceTimer->Tick += gcnew System::EventHandler(this, &Form1::RaceTimer_Tick);
			// 
			// followToonTimer
			// 
			this->followToonTimer->Tick += gcnew System::EventHandler(this, &Form1::followToonTimer_Tick);
			// 
			// GolfEmergencyTimer
			// 
			this->GolfEmergencyTimer->Tick += gcnew System::EventHandler(this, &Form1::GolfEmergencyTimer_Tick);
			// 
			// VPTimer
			// 
			this->VPTimer->Tick += gcnew System::EventHandler(this, &Form1::VPTimer_Tick);
			// 
			// ControllerTimer
			// 
			this->ControllerTimer->Tick += gcnew System::EventHandler(this, &Form1::ControllerTimer_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(819, 535);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Enigmeows magic tools version 0.06";
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->primaryTabPage->ResumeLayout(false);
			this->primaryTabPage->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->pondConfigPanel->ResumeLayout(false);
			this->pondConfigPanel->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->CastGroup->ResumeLayout(false);
			this->CastGroup->PerformLayout();
			this->GolfMoves->ResumeLayout(false);
			this->GolfCourses->ResumeLayout(false);
			this->GolfCourses->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->multiTab->ResumeLayout(false);
			this->multiTab->PerformLayout();
			this->VPTools->ResumeLayout(false);
			this->VPTools->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: 
                void refreshWindows();
                System::Void loadPondList();
                System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
                System::Void refreshWindowsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void WindowPicker_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void ReshapeButton_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void MoveMouse_Click(System::Object^  sender, System::EventArgs^  e);
                void resetScale();
				void loadPonds();
                void updateDone();
				                void loadCurrentPond();
                void startCast();
                bool centerFish(HDC hdl, int &x, int &y, int deltax, int deltay);
                void doCast(int dx, int dy);
                System::Void fisherTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void emergencyTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void StartFishing_Click(System::Object^  sender, System::EventArgs^  e);

                System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
                }
                void savePonds(bool interactive);
                void loadPonds(bool interactive);
                System::Void loadPlansToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                  loadPonds(true);
                }
                System::Void savePlansToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                  savePonds(true); 
                }
                System::Void deletePlanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                }
                System::Void stopToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                  this->fisherTimer->Enabled = false;
                  this->GolfTimer->Enabled = false;
                  this->RaceViewTimer->Enabled = false;
                  this->RaceTimer->Enabled = false;
                  this->emergencyTimer->Enabled = false;
                  this->GolfEmergencyTimer->Enabled = false;
                }
                System::Void pondDescription_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondFishR_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondFishG_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondFishB_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondFishT_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondDockX_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondDockY_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondPondX_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondPondY_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondPondWidth_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondPondHeight_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondFisherX_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondFisherY_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pondEstate_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void Form1::plansList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void dockradio1_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void dockradio2_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void dockradio3_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void dockradio4_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void startGolfing_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void smallCourseRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void mediumCourseRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void largeCourseRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void GolfTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void RaceViewTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void RaceTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void findbase_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void processLogs();
                System::Void doGolfScan();
                int doRaceScan();
                System::Void StillGolfing_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void PerfectHit_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void perfectHit();
                System::Void GolfTap_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void GolfMiss_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void startScanner_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void ScanButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void raceScanButton_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void tallToon_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void toonThreshold_TextChanged(System::Object^  sender, System::EventArgs^  e);
                void turnTo(int direction);
                void grabScreen(RECT &rect);
                int vscan(int middlev, int bottom, int top, RECT &rect);
                int hscan(int middleh, int startx, int endx, int delta, RECT &rect);
                double countroad(int startx, int starty, int width, int height, RECT &rect);
                System::Void roadBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
                void runTo(double x, double y, bool getpos, bool nohop);
                void turnTo(double x, double y, bool getpos);
                double distanceTo(double x, double y, bool getpos);
                bool runToPrelaunch(bool getpos);
                bool runToLaunch(int slot, bool getpos);
                System::Void RunThere_Click(System::Object^  sender, System::EventArgs^  e);
                void racetick();
                System::Void justRace_Click(System::Object^  sender, System::EventArgs^  e);
                void mouseClick(int x, int y);

                System::Void runTick(double dx, double dy);

                System::Void followToonTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void followToon_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void alignToons_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void TrackBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void pushVals_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void XBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void YBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void ZBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void HBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void GolfEmergencyTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void genericToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void vPModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void cFOModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void cJModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void cEOModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPGetPie_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPMiddleTopRamp_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPMiddlePlatform_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void BottomRamp_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPThrow_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPJump_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPBottom_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPStandAside_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void VPTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void DisabledMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
                int openPort(unsigned int &addr, unsigned short &port, int sender);
                DWORD LoadControllerStatus(XINPUT_STATE &state);
                System::Void bool_controller(bool oldv, bool newv, XINPUT_STATE &state, int button);
                System::Void vp_controller(bool oldv, bool newv, XINPUT_STATE &state, int button);
                void CheckControllerStatus(XINPUT_STATE &old, XINPUT_STATE &state);
                System::Void ControllerTimer_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void publishStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void resetMenus();

};
}


