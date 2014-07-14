#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include "WS2tcpip.h"
#include <stdlib.h>
#include <math.h>
#include <XInput.h>                       // Defines XBOX controller API 

namespace twiz {

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
	public: System::Windows::Forms::TabControl^  tabControl1;
	protected: 
	public: System::Windows::Forms::TabPage^  tabPage1;
	public: System::Windows::Forms::Button^  button1;
	public: System::Windows::Forms::TabPage^  tabPage2;
	public: System::Windows::Forms::RadioButton^  radioButton3;
	public: System::Windows::Forms::RadioButton^  radioButton2;

	public: System::Windows::Forms::Button^  button2;
	public: System::Windows::Forms::Timer^  timer1;
	public: System::Windows::Forms::TextBox^  portBox;
	public: System::Windows::Forms::TextBox^  addressBox;
	public: System::Windows::Forms::RadioButton^  localMode;
	public: System::Windows::Forms::ListBox^  listBox1;
  public: System::Windows::Forms::Button^  refreshButton;
  public: System::Windows::Forms::TextBox^  processID;
  public: System::Windows::Forms::Label^  label2;
  public: System::Windows::Forms::Label^  label1;
  public: System::Windows::Forms::TextBox^  floatValue;
  public: System::Windows::Forms::Button^  doSearch;
  public: System::Windows::Forms::TextBox^  intBox;
  public: System::Windows::Forms::Label^  elements;

  public: System::Windows::Forms::Button^  removeChanged;
  public: System::Windows::Forms::Button^  removeUnchanged;
	public: System::Windows::Forms::Timer^  timer2;
	public: System::Windows::Forms::Label^  valueLabel;
	public: System::Windows::Forms::Label^  addressLabel;
	public: System::Windows::Forms::Button^  watch;
	public: System::Windows::Forms::Button^  searchSelected;
	public: System::Windows::Forms::CheckBox^  useFloat;
	public: System::Windows::Forms::CheckBox^  staticAddress;
	public: System::Windows::Forms::TextBox^  statbox;
	public: System::Windows::Forms::TextBox^  YBox;
	public: System::Windows::Forms::TextBox^  ZBox;
	public: System::Windows::Forms::TextBox^  HBox;



	public: System::Windows::Forms::TextBox^  XBox;

	public: System::Windows::Forms::Label^  label6;
	public: System::Windows::Forms::Label^  label5;
	public: System::Windows::Forms::Label^  label4;
	public: System::Windows::Forms::Label^  label3;
	public: System::Windows::Forms::TextBox^  baseBox;
	public: System::Windows::Forms::Label^  label7;
	public: System::Windows::Forms::Button^  findbase;

	public: System::Windows::Forms::Label^  label8;
	public: System::Windows::Forms::TextBox^  toonName;
	public: System::Windows::Forms::CheckBox^  enableController;
	public: System::Windows::Forms::CheckBox^  leaderBox1;
	public: System::Windows::Forms::TextBox^  DHBox;
	public: System::Windows::Forms::ComboBox^  addrEnter;
	public: System::Windows::Forms::CheckBox^  toonSpy;
	public: System::Windows::Forms::CheckBox^  toonFollow;
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::Button^  Wiggler;
	private: System::Windows::Forms::Timer^  timer3;
	private: System::Windows::Forms::Button^  Golf;
	private: System::Windows::Forms::TextBox^  TimeMultiple;
	private: System::Windows::Forms::TextBox^  PercentTime;
	private: System::Windows::Forms::Timer^  GolfTimer;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Button^  StopGolf;

	private: System::Windows::Forms::Button^  StartGolf;
	private: System::Windows::Forms::ComboBox^  CoursePicker;
	private: System::Windows::Forms::Timer^  GolfTimer2;
	public: 
 float tx_;
 float ty_;
 int golfstate_;


	public: 
	private: System::ComponentModel::IContainer^  components;
	public: 


	protected: 

	public:
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
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->Golf = (gcnew System::Windows::Forms::Button());
			this->TimeMultiple = (gcnew System::Windows::Forms::TextBox());
			this->PercentTime = (gcnew System::Windows::Forms::TextBox());
			this->Wiggler = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->toonFollow = (gcnew System::Windows::Forms::CheckBox());
			this->toonSpy = (gcnew System::Windows::Forms::CheckBox());
			this->addrEnter = (gcnew System::Windows::Forms::ComboBox());
			this->DHBox = (gcnew System::Windows::Forms::TextBox());
			this->leaderBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->enableController = (gcnew System::Windows::Forms::CheckBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->toonName = (gcnew System::Windows::Forms::TextBox());
			this->baseBox = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->findbase = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->YBox = (gcnew System::Windows::Forms::TextBox());
			this->ZBox = (gcnew System::Windows::Forms::TextBox());
			this->HBox = (gcnew System::Windows::Forms::TextBox());
			this->XBox = (gcnew System::Windows::Forms::TextBox());
			this->refreshButton = (gcnew System::Windows::Forms::Button());
			this->localMode = (gcnew System::Windows::Forms::RadioButton());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->portBox = (gcnew System::Windows::Forms::TextBox());
			this->addressBox = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->staticAddress = (gcnew System::Windows::Forms::CheckBox());
			this->statbox = (gcnew System::Windows::Forms::TextBox());
			this->useFloat = (gcnew System::Windows::Forms::CheckBox());
			this->searchSelected = (gcnew System::Windows::Forms::Button());
			this->valueLabel = (gcnew System::Windows::Forms::Label());
			this->addressLabel = (gcnew System::Windows::Forms::Label());
			this->watch = (gcnew System::Windows::Forms::Button());
			this->elements = (gcnew System::Windows::Forms::Label());
			this->removeChanged = (gcnew System::Windows::Forms::Button());
			this->removeUnchanged = (gcnew System::Windows::Forms::Button());
			this->intBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->floatValue = (gcnew System::Windows::Forms::TextBox());
			this->doSearch = (gcnew System::Windows::Forms::Button());
			this->processID = (gcnew System::Windows::Forms::TextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->StopGolf = (gcnew System::Windows::Forms::Button());
			this->StartGolf = (gcnew System::Windows::Forms::Button());
			this->CoursePicker = (gcnew System::Windows::Forms::ComboBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->GolfTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->GolfTimer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(626, 464);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->Golf);
			this->tabPage1->Controls->Add(this->TimeMultiple);
			this->tabPage1->Controls->Add(this->PercentTime);
			this->tabPage1->Controls->Add(this->Wiggler);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->toonFollow);
			this->tabPage1->Controls->Add(this->toonSpy);
			this->tabPage1->Controls->Add(this->addrEnter);
			this->tabPage1->Controls->Add(this->DHBox);
			this->tabPage1->Controls->Add(this->leaderBox1);
			this->tabPage1->Controls->Add(this->enableController);
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->toonName);
			this->tabPage1->Controls->Add(this->baseBox);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->findbase);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->YBox);
			this->tabPage1->Controls->Add(this->ZBox);
			this->tabPage1->Controls->Add(this->HBox);
			this->tabPage1->Controls->Add(this->XBox);
			this->tabPage1->Controls->Add(this->refreshButton);
			this->tabPage1->Controls->Add(this->localMode);
			this->tabPage1->Controls->Add(this->listBox1);
			this->tabPage1->Controls->Add(this->portBox);
			this->tabPage1->Controls->Add(this->addressBox);
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->radioButton3);
			this->tabPage1->Controls->Add(this->radioButton2);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(618, 438);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// Golf
			// 
			this->Golf->Location = System::Drawing::Point(348, 216);
			this->Golf->Name = L"Golf";
			this->Golf->Size = System::Drawing::Size(75, 23);
			this->Golf->TabIndex = 33;
			this->Golf->Text = L"Golf";
			this->Golf->UseVisualStyleBackColor = true;
			this->Golf->Click += gcnew System::EventHandler(this, &Form1::Golf_Click);
			// 
			// TimeMultiple
			// 
			this->TimeMultiple->Location = System::Drawing::Point(277, 190);
			this->TimeMultiple->Name = L"TimeMultiple";
			this->TimeMultiple->Size = System::Drawing::Size(100, 20);
			this->TimeMultiple->TabIndex = 32;
			this->TimeMultiple->Text = L"50";
			// 
			// PercentTime
			// 
			this->PercentTime->Location = System::Drawing::Point(277, 164);
			this->PercentTime->Name = L"PercentTime";
			this->PercentTime->Size = System::Drawing::Size(100, 20);
			this->PercentTime->TabIndex = 31;
			// 
			// Wiggler
			// 
			this->Wiggler->Location = System::Drawing::Point(166, 374);
			this->Wiggler->Name = L"Wiggler";
			this->Wiggler->Size = System::Drawing::Size(75, 23);
			this->Wiggler->TabIndex = 2;
			this->Wiggler->Text = L"Wiggle";
			this->Wiggler->UseVisualStyleBackColor = true;
			this->Wiggler->Click += gcnew System::EventHandler(this, &Form1::Wiggler_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(289, 90);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(88, 20);
			this->textBox1->TabIndex = 30;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox1_KeyDown);
			this->textBox1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox1_KeyUp);
			// 
			// toonFollow
			// 
			this->toonFollow->AutoSize = true;
			this->toonFollow->Location = System::Drawing::Point(485, 413);
			this->toonFollow->Name = L"toonFollow";
			this->toonFollow->Size = System::Drawing::Size(80, 17);
			this->toonFollow->TabIndex = 29;
			this->toonFollow->Text = L"toon Follow";
			this->toonFollow->UseVisualStyleBackColor = true;
			// 
			// toonSpy
			// 
			this->toonSpy->AutoSize = true;
			this->toonSpy->Location = System::Drawing::Point(485, 318);
			this->toonSpy->Name = L"toonSpy";
			this->toonSpy->Size = System::Drawing::Size(68, 17);
			this->toonSpy->TabIndex = 28;
			this->toonSpy->Text = L"toon Spy";
			this->toonSpy->UseVisualStyleBackColor = true;
			// 
			// addrEnter
			// 
			this->addrEnter->Location = System::Drawing::Point(485, 380);
			this->addrEnter->Name = L"addrEnter";
			this->addrEnter->Size = System::Drawing::Size(100, 21);
			this->addrEnter->TabIndex = 27;
			this->addrEnter->TextChanged += gcnew System::EventHandler(this, &Form1::addrEnter_TextChanged);
			// 
			// DHBox
			// 
			this->DHBox->Location = System::Drawing::Point(485, 351);
			this->DHBox->Name = L"DHBox";
			this->DHBox->Size = System::Drawing::Size(100, 20);
			this->DHBox->TabIndex = 26;
			this->DHBox->Text = L"13.962";
			// 
			// leaderBox1
			// 
			this->leaderBox1->AutoSize = true;
			this->leaderBox1->Location = System::Drawing::Point(485, 250);
			this->leaderBox1->Name = L"leaderBox1";
			this->leaderBox1->Size = System::Drawing::Size(55, 17);
			this->leaderBox1->TabIndex = 25;
			this->leaderBox1->Text = L"leader";
			this->leaderBox1->UseVisualStyleBackColor = true;
			this->leaderBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::leaderBox1_CheckedChanged);
			// 
			// enableController
			// 
			this->enableController->AutoSize = true;
			this->enableController->Location = System::Drawing::Point(444, 185);
			this->enableController->Name = L"enableController";
			this->enableController->Size = System::Drawing::Size(102, 17);
			this->enableController->TabIndex = 24;
			this->enableController->Text = L"enableController";
			this->enableController->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(297, 254);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(56, 13);
			this->label8->TabIndex = 22;
			this->label8->Text = L"toonName";
			// 
			// toonName
			// 
			this->toonName->Location = System::Drawing::Point(359, 251);
			this->toonName->Name = L"toonName";
			this->toonName->Size = System::Drawing::Size(100, 20);
			this->toonName->TabIndex = 9;
			this->toonName->TextChanged += gcnew System::EventHandler(this, &Form1::toonName_TextChanged);
			// 
			// baseBox
			// 
			this->baseBox->Location = System::Drawing::Point(359, 381);
			this->baseBox->Name = L"baseBox";
			this->baseBox->ReadOnly = true;
			this->baseBox->Size = System::Drawing::Size(100, 20);
			this->baseBox->TabIndex = 20;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(309, 384);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(31, 13);
			this->label7->TabIndex = 19;
			this->label7->Text = L"Base";
			// 
			// findbase
			// 
			this->findbase->Location = System::Drawing::Point(490, 280);
			this->findbase->Name = L"findbase";
			this->findbase->Size = System::Drawing::Size(75, 23);
			this->findbase->TabIndex = 18;
			this->findbase->Text = L"Find Base";
			this->findbase->UseVisualStyleBackColor = true;
			this->findbase->Click += gcnew System::EventHandler(this, &Form1::findbase_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(309, 306);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(14, 13);
			this->label6->TabIndex = 17;
			this->label6->Text = L"Y";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(309, 332);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Z";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(309, 358);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 15;
			this->label4->Text = L"H";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(309, 280);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(14, 13);
			this->label3->TabIndex = 14;
			this->label3->Text = L"X";
			// 
			// YBox
			// 
			this->YBox->Location = System::Drawing::Point(359, 303);
			this->YBox->Name = L"YBox";
			this->YBox->Size = System::Drawing::Size(100, 20);
			this->YBox->TabIndex = 11;
			this->YBox->Text = L"59.776";
			// 
			// ZBox
			// 
			this->ZBox->Location = System::Drawing::Point(359, 329);
			this->ZBox->Name = L"ZBox";
			this->ZBox->Size = System::Drawing::Size(100, 20);
			this->ZBox->TabIndex = 12;
			this->ZBox->Text = L"0.027";
			// 
			// HBox
			// 
			this->HBox->Location = System::Drawing::Point(359, 355);
			this->HBox->Name = L"HBox";
			this->HBox->Size = System::Drawing::Size(100, 20);
			this->HBox->TabIndex = 13;
			this->HBox->Text = L"13.962";
			// 
			// XBox
			// 
			this->XBox->Location = System::Drawing::Point(359, 277);
			this->XBox->Name = L"XBox";
			this->XBox->Size = System::Drawing::Size(100, 20);
			this->XBox->TabIndex = 10;
			this->XBox->Text = L"40.629";
			// 
			// refreshButton
			// 
			this->refreshButton->Location = System::Drawing::Point(52, 374);
			this->refreshButton->Name = L"refreshButton";
			this->refreshButton->Size = System::Drawing::Size(75, 23);
			this->refreshButton->TabIndex = 2;
			this->refreshButton->Text = L"Refresh";
			this->refreshButton->UseVisualStyleBackColor = true;
			this->refreshButton->Click += gcnew System::EventHandler(this, &Form1::refreshButton_Click);
			// 
			// localMode
			// 
			this->localMode->AutoSize = true;
			this->localMode->Location = System::Drawing::Point(441, 67);
			this->localMode->Name = L"localMode";
			this->localMode->Size = System::Drawing::Size(74, 17);
			this->localMode->TabIndex = 9;
			this->localMode->TabStop = true;
			this->localMode->Text = L"localMode";
			this->localMode->UseVisualStyleBackColor = true;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(18, 12);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(239, 342);
			this->listBox1->Sorted = true;
			this->listBox1->TabIndex = 8;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox1_SelectedIndexChanged);
			// 
			// portBox
			// 
			this->portBox->Location = System::Drawing::Point(312, 54);
			this->portBox->Name = L"portBox";
			this->portBox->Size = System::Drawing::Size(100, 20);
			this->portBox->TabIndex = 7;
			this->portBox->Text = L"12345";
			// 
			// addressBox
			// 
			this->addressBox->Location = System::Drawing::Point(312, 28);
			this->addressBox->Name = L"addressBox";
			this->addressBox->Size = System::Drawing::Size(100, 20);
			this->addressBox->TabIndex = 6;
			this->addressBox->Text = L"239.0.10.10";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(440, 146);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(84, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"StartController";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(441, 113);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(78, 17);
			this->radioButton3->TabIndex = 4;
			this->radioButton3->Text = L"ClientMode";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Checked = true;
			this->radioButton2->Location = System::Drawing::Point(441, 90);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(83, 17);
			this->radioButton2->TabIndex = 3;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"ServerMode";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(441, 25);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(98, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"TestKeyboard";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->staticAddress);
			this->tabPage2->Controls->Add(this->statbox);
			this->tabPage2->Controls->Add(this->useFloat);
			this->tabPage2->Controls->Add(this->searchSelected);
			this->tabPage2->Controls->Add(this->valueLabel);
			this->tabPage2->Controls->Add(this->addressLabel);
			this->tabPage2->Controls->Add(this->watch);
			this->tabPage2->Controls->Add(this->elements);
			this->tabPage2->Controls->Add(this->removeChanged);
			this->tabPage2->Controls->Add(this->removeUnchanged);
			this->tabPage2->Controls->Add(this->intBox);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->label1);
			this->tabPage2->Controls->Add(this->floatValue);
			this->tabPage2->Controls->Add(this->doSearch);
			this->tabPage2->Controls->Add(this->processID);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(618, 438);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// staticAddress
			// 
			this->staticAddress->AutoSize = true;
			this->staticAddress->Location = System::Drawing::Point(57, 379);
			this->staticAddress->Name = L"staticAddress";
			this->staticAddress->Size = System::Drawing::Size(92, 17);
			this->staticAddress->TabIndex = 14;
			this->staticAddress->Text = L"static Address";
			this->staticAddress->UseVisualStyleBackColor = true;
			// 
			// statbox
			// 
			this->statbox->Location = System::Drawing::Point(163, 379);
			this->statbox->Name = L"statbox";
			this->statbox->Size = System::Drawing::Size(100, 20);
			this->statbox->TabIndex = 13;
			// 
			// useFloat
			// 
			this->useFloat->AutoSize = true;
			this->useFloat->Location = System::Drawing::Point(213, 60);
			this->useFloat->Name = L"useFloat";
			this->useFloat->Size = System::Drawing::Size(69, 17);
			this->useFloat->TabIndex = 12;
			this->useFloat->Text = L"use Float";
			this->useFloat->UseVisualStyleBackColor = true;
			// 
			// searchSelected
			// 
			this->searchSelected->Location = System::Drawing::Point(100, 237);
			this->searchSelected->Name = L"searchSelected";
			this->searchSelected->Size = System::Drawing::Size(127, 23);
			this->searchSelected->TabIndex = 11;
			this->searchSelected->Text = L"search selected";
			this->searchSelected->UseVisualStyleBackColor = true;
			this->searchSelected->Click += gcnew System::EventHandler(this, &Form1::searchSelected_Click);
			// 
			// valueLabel
			// 
			this->valueLabel->AutoSize = true;
			this->valueLabel->Location = System::Drawing::Point(85, 330);
			this->valueLabel->Name = L"valueLabel";
			this->valueLabel->Size = System::Drawing::Size(35, 13);
			this->valueLabel->TabIndex = 10;
			this->valueLabel->Text = L"label4";
			// 
			// addressLabel
			// 
			this->addressLabel->AutoSize = true;
			this->addressLabel->Location = System::Drawing::Point(82, 313);
			this->addressLabel->Name = L"addressLabel";
			this->addressLabel->Size = System::Drawing::Size(44, 13);
			this->addressLabel->TabIndex = 9;
			this->addressLabel->Text = L"address";
			// 
			// watch
			// 
			this->watch->Location = System::Drawing::Point(82, 273);
			this->watch->Name = L"watch";
			this->watch->Size = System::Drawing::Size(89, 23);
			this->watch->TabIndex = 2;
			this->watch->Text = L"watchButton";
			this->watch->UseVisualStyleBackColor = true;
			this->watch->Click += gcnew System::EventHandler(this, &Form1::watch_Click);
			// 
			// elements
			// 
			this->elements->AutoSize = true;
			this->elements->Location = System::Drawing::Point(266, 107);
			this->elements->Name = L"elements";
			this->elements->Size = System::Drawing::Size(13, 13);
			this->elements->TabIndex = 8;
			this->elements->Text = L"0";
			// 
			// removeChanged
			// 
			this->removeChanged->Location = System::Drawing::Point(100, 179);
			this->removeChanged->Name = L"removeChanged";
			this->removeChanged->Size = System::Drawing::Size(127, 23);
			this->removeChanged->TabIndex = 7;
			this->removeChanged->Text = L"Remove Changed";
			this->removeChanged->UseVisualStyleBackColor = true;
			this->removeChanged->Click += gcnew System::EventHandler(this, &Form1::removeChanged_Click);
			// 
			// removeUnchanged
			// 
			this->removeUnchanged->Location = System::Drawing::Point(100, 208);
			this->removeUnchanged->Name = L"removeUnchanged";
			this->removeUnchanged->Size = System::Drawing::Size(127, 23);
			this->removeUnchanged->TabIndex = 6;
			this->removeUnchanged->Text = L"Remove Unchanged";
			this->removeUnchanged->UseVisualStyleBackColor = true;
			this->removeUnchanged->Click += gcnew System::EventHandler(this, &Form1::removeUnchanged_Click);
			// 
			// intBox
			// 
			this->intBox->Location = System::Drawing::Point(91, 87);
			this->intBox->Name = L"intBox";
			this->intBox->Size = System::Drawing::Size(100, 20);
			this->intBox->TabIndex = 5;
			this->intBox->Text = L"1234";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(40, 61);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Float";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(40, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(45, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Process";
			// 
			// floatValue
			// 
			this->floatValue->Location = System::Drawing::Point(91, 61);
			this->floatValue->Name = L"floatValue";
			this->floatValue->Size = System::Drawing::Size(100, 20);
			this->floatValue->TabIndex = 2;
			this->floatValue->Text = L"13.962";
			// 
			// doSearch
			// 
			this->doSearch->Location = System::Drawing::Point(100, 150);
			this->doSearch->Name = L"doSearch";
			this->doSearch->Size = System::Drawing::Size(127, 23);
			this->doSearch->TabIndex = 1;
			this->doSearch->Text = L"Do Search";
			this->doSearch->UseVisualStyleBackColor = true;
			this->doSearch->Click += gcnew System::EventHandler(this, &Form1::doSearch_Click);
			// 
			// processID
			// 
			this->processID->Location = System::Drawing::Point(91, 35);
			this->processID->Name = L"processID";
			this->processID->Size = System::Drawing::Size(100, 20);
			this->processID->TabIndex = 0;
			this->processID->Text = L"1852";
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->StopGolf);
			this->tabPage3->Controls->Add(this->StartGolf);
			this->tabPage3->Controls->Add(this->CoursePicker);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(618, 438);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Golf";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// StopGolf
			// 
			this->StopGolf->Location = System::Drawing::Point(189, 50);
			this->StopGolf->Name = L"StopGolf";
			this->StopGolf->Size = System::Drawing::Size(75, 23);
			this->StopGolf->TabIndex = 2;
			this->StopGolf->Text = L"StopGolf";
			this->StopGolf->UseVisualStyleBackColor = true;
			this->StopGolf->Click += gcnew System::EventHandler(this, &Form1::StopGolf_Click);
			// 
			// StartGolf
			// 
			this->StartGolf->Location = System::Drawing::Point(189, 21);
			this->StartGolf->Name = L"StartGolf";
			this->StartGolf->Size = System::Drawing::Size(75, 23);
			this->StartGolf->TabIndex = 1;
			this->StartGolf->Text = L"StartGolf";
			this->StartGolf->UseVisualStyleBackColor = true;
			this->StartGolf->Click += gcnew System::EventHandler(this, &Form1::StartGolf_Click);
			// 
			// CoursePicker
			// 
			this->CoursePicker->FormattingEnabled = true;
			this->CoursePicker->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Front", L"Middle", L"Back"});
			this->CoursePicker->Location = System::Drawing::Point(29, 36);
			this->CoursePicker->Name = L"CoursePicker";
			this->CoursePicker->Size = System::Drawing::Size(121, 21);
			this->CoursePicker->TabIndex = 0;
			this->CoursePicker->Text = L"Front";
			this->CoursePicker->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::CoursePicker_SelectedIndexChanged);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// timer3
			// 
			this->timer3->Interval = 5000;
			this->timer3->Tick += gcnew System::EventHandler(this, &Form1::timer3_Tick);
			// 
			// GolfTimer
			// 
			this->GolfTimer->Tick += gcnew System::EventHandler(this, &Form1::GolfTimer_Tick);
			// 
			// GolfTimer2
			// 
			this->GolfTimer2->Tick += gcnew System::EventHandler(this, &Form1::GolfTimer2_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(626, 464);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		
#ifndef MAPVK_VK_TO_VSC
#define MAPVK_VK_TO_VSC 0
#endif

        public:
                unsigned int addr_;
                unsigned short port_;
                int serv_;
                int fd_;
                XINPUT_STATE *stateA_;
                XINPUT_STATE *stateB_;
                struct sockaddr_in *si_other_;
                static System::Windows::Forms::ListBox^  listBox1_;
                void *snapshot_;

                void ThreadProc();
                System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
                System::Void refreshButton_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void doSearch_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void removeChanged_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void removeUnchanged_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e);
                System::Void watch_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void searchSelected_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void findbase_Click(System::Object^  sender, System::EventArgs^  e);
                System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void toonName_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void leaderBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void addrEnter_TextChanged(System::Object^  sender, System::EventArgs^  e);
                System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
                System::Void textBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
				DWORD LoadControllerStatus(XINPUT_STATE &state);
				void YButton(bool oldv, bool newv, XINPUT_STATE &state);
					void AButton(bool oldv, bool newv, XINPUT_STATE &state);
						void BButton(bool oldv, bool newv, XINPUT_STATE &state);
							void XButton(bool oldv, bool newv, XINPUT_STATE &state);
							void RightThumbButton(bool oldv, bool newv, XINPUT_STATE &state);
							void LeftThumbButton(bool oldv, bool newv, XINPUT_STATE &state);
							void BackButton(bool oldv, bool newv, XINPUT_STATE &state);
							void StartButton(bool oldv, bool newv, XINPUT_STATE &state) ;
void RightButton(bool oldv, bool newv, XINPUT_STATE &state) ;
void LeftButton(bool oldv, bool newv, XINPUT_STATE &state);
void DownButton(bool oldv, bool newv, XINPUT_STATE &state);
void UpButton(bool oldv, bool newv, XINPUT_STATE &state) ;
void RightThumbXY(int newx, int newy, XINPUT_STATE &state);
void LeftThumbXY(int newx, int newy, XINPUT_STATE &state);
void RightTrigger(int oldv, int newv, XINPUT_STATE &state);
void LeftTrigger(int oldv, int newv, XINPUT_STATE &state) ;
void RightShoulderButton(bool oldv, bool newv, XINPUT_STATE &state);
void LeftShoulderButton(bool oldv, bool newv, XINPUT_STATE &state);
void CheckControllerStatus(XINPUT_STATE &old, XINPUT_STATE &state);
 System::Void hScrollBar1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
		 }

 System::Void Wiggler_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->timer3->Enabled = !this->timer3->Enabled;
		 }
 System::Void timer3_Tick(System::Object^  sender, System::EventArgs^  e);

 System::Void Golf_Click(System::Object^  sender, System::EventArgs^  e);
 System::Void GolfTimer_Tick(System::Object^  sender, System::EventArgs^  e);
 System::Void GolfTimer2_Tick(System::Object^  sender, System::EventArgs^  e);
 System::Void StartGolf_Click(System::Object^  sender, System::EventArgs^  e);
 System::Void StopGolf_Click(System::Object^  sender, System::EventArgs^  e);
 System::Void CoursePicker_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

