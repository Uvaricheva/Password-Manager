#pragma once

namespace pm_xml {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;
	using namespace System::IO;
	using namespace System::Resources;
	using namespace System::Reflection;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		String^ BasePath = "";
	private: System::Windows::Forms::ToolStripMenuItem^  ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem;
	public:
		ResourceManager^ rm = gcnew ResourceManager(L"pm_xml.Resource", this->GetType()->Assembly);

		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void refreshTable()
		{
			
			String^ s = rm->GetString(L"Schema_ru");
			
			StringReader^ sr = gcnew StringReader(s);

			PasswordsDataSet->Clear();

			PasswordsDataSet->ReadXml(BasePath);
			PasswordsDataSet->ReadXmlSchema(sr);

			dataGridView1->DataSource = PasswordsDataSet;
			dataGridView1->DataMember = "data";
			
		}

		void saveTable()
		{
			try 
			{
				PasswordsDataSet->WriteXml(BasePath);
				MessageBox::Show("—Óı‡ÌÂÌÓ!");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

		void saveAsTable()
		{
			try 
			{
				if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
					saveFileDialog1->FileName->Length > 0)
				{
					BasePath = saveFileDialog1->FileName;
					saveTable();
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	protected:


	private: System::Data::DataSet^  PasswordsDataSet;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  Ù‡ÈÎToolStripMenuItem;












	private: System::Windows::Forms::BindingSource^  bindingSource1;
	private: System::Windows::Forms::ToolStripMenuItem^  ÒÓÁ‰‡Ú¸ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ÓÚÍ˚Ú¸ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ‚˚ıÓ‰ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  ÒÓı‡ÌËÚ¸ToolStripMenuItem;



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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->PasswordsDataSet = (gcnew System::Data::DataSet());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->Ù‡ÈÎToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ÒÓÁ‰‡Ú¸ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ÓÚÍ˚Ú¸ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ÒÓı‡ÌËÚ¸ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->‚˚ıÓ‰ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PasswordsDataSet))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(0, 27);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(681, 200);
			this->dataGridView1->TabIndex = 0;
			// 
			// PasswordsDataSet
			// 
			this->PasswordsDataSet->DataSetName = L"NewDataSet";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"xml files|*.xml|¬ÒÂ Ù‡ÈÎ˚|*.*";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"xml files|*.xml|¬ÒÂ Ù‡ÈÎ˚|*.*";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->Ù‡ÈÎToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(686, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// Ù‡ÈÎToolStripMenuItem
			// 
			this->Ù‡ÈÎToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->ÒÓÁ‰‡Ú¸ToolStripMenuItem,
					this->ÓÚÍ˚Ú¸ToolStripMenuItem, this->ÒÓı‡ÌËÚ¸ToolStripMenuItem, this->ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem, this->‚˚ıÓ‰ToolStripMenuItem
			});
			this->Ù‡ÈÎToolStripMenuItem->Name = L"Ù‡ÈÎToolStripMenuItem";
			this->Ù‡ÈÎToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->Ù‡ÈÎToolStripMenuItem->Text = L"‘‡ÈÎ";
			// 
			// ÒÓÁ‰‡Ú¸ToolStripMenuItem
			// 
			this->ÒÓÁ‰‡Ú¸ToolStripMenuItem->Name = L"ÒÓÁ‰‡Ú¸ToolStripMenuItem";
			this->ÒÓÁ‰‡Ú¸ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->ÒÓÁ‰‡Ú¸ToolStripMenuItem->Text = L"—ÓÁ‰‡Ú¸";
			this->ÒÓÁ‰‡Ú¸ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ÒÓÁ‰‡Ú¸ToolStripMenuItem_Click);
			// 
			// ÓÚÍ˚Ú¸ToolStripMenuItem
			// 
			this->ÓÚÍ˚Ú¸ToolStripMenuItem->Name = L"ÓÚÍ˚Ú¸ToolStripMenuItem";
			this->ÓÚÍ˚Ú¸ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->ÓÚÍ˚Ú¸ToolStripMenuItem->Text = L"ŒÚÍ˚Ú¸";
			this->ÓÚÍ˚Ú¸ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ÓÚÍ˚Ú¸ToolStripMenuItem_Click);
			// 
			// ÒÓı‡ÌËÚ¸ToolStripMenuItem
			// 
			this->ÒÓı‡ÌËÚ¸ToolStripMenuItem->Name = L"ÒÓı‡ÌËÚ¸ToolStripMenuItem";
			this->ÒÓı‡ÌËÚ¸ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->ÒÓı‡ÌËÚ¸ToolStripMenuItem->Text = L"—Óı‡ÌËÚ¸";
			this->ÒÓı‡ÌËÚ¸ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ÒÓı‡ÌËÚ¸ToolStripMenuItem_Click);
			// 
			// ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem
			// 
			this->ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem->Name = L"ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem";
			this->ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem->Text = L"—Óı‡ÌËÚ¸ Í‡Í...";
			this->ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem_Click);
			// 
			// ‚˚ıÓ‰ToolStripMenuItem
			// 
			this->‚˚ıÓ‰ToolStripMenuItem->Name = L"‚˚ıÓ‰ToolStripMenuItem";
			this->‚˚ıÓ‰ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->‚˚ıÓ‰ToolStripMenuItem->Text = L"¬˚ıÓ‰";
			this->‚˚ıÓ‰ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::‚˚ıÓ‰ToolStripMenuItem_Click);
			// 
			// bindingSource1
			// 
			this->bindingSource1->DataSource = this->PasswordsDataSet;
			this->bindingSource1->Position = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(686, 241);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"ÃÂÌÂ‰ÊÂ Ô‡ÓÎÂÈ";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PasswordsDataSet))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	//”ÒÚ‡ÌÓ‚Í‡ ÒıÂÏ˚
	String^ s = rm->GetString(L"Schema_ru");
	StringReader^ sr = gcnew StringReader(s);
	PasswordsDataSet->ReadXmlSchema(sr);

	//«‡„ÛÁÍ‡ ¯‡·ÎÓÌ‡
	s = rm->GetString(L"Template_ru");
	sr = gcnew StringReader(s);
	PasswordsDataSet->ReadXml(sr);
	
	dataGridView1->DataSource = PasswordsDataSet;
	dataGridView1->DataMember = "data";
}

private: System::Void ‚˚ıÓ‰ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}

private: System::Void ÓÚÍ˚Ú¸ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			BasePath = openFileDialog1->FileName;

			refreshTable();
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}

}

private: System::Void ÒÓÁ‰‡Ú¸ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	try
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
			saveFileDialog1->FileName->Length > 0)
		{
			
			BasePath = saveFileDialog1->FileName;
			
			//—ÓÁ‰‡ÌËÂ ÌÓ‚˚È Ù‡ÈÎ Ì‡ ÓÒÌÓ‚Â ÂÒÛÒ‡
			String^ s = rm->GetString(L"Template_ru");

			StreamWriter^ stream = gcnew StreamWriter(BasePath);
			stream->Write(s);
			stream->Close();

			refreshTable();
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
}

private: System::Void ÒÓı‡ÌËÚ¸ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		if (BasePath == "")
			saveAsTable();
		else
			saveTable();
		
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
}
private: System::Void ÒÓı‡ÌËÚ¸ ‡ÍToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
			saveFileDialog1->FileName->Length > 0)
		{

			BasePath = saveFileDialog1->FileName;
			saveTable();
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
}
};
}
