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
	using namespace System::Runtime::InteropServices;
	using namespace System::Security::Cryptography;


	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

	String^ BasePath = "";
	private: System::Windows::Forms::ToolStripMenuItem^  ñîõğàíèòüÊàêToolStripMenuItem;
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

			array<Byte>^ salt = gcnew array<Byte> { 'U', 'v', 'a', 'r', 'i', 'c', 'h', 'e', 'v', 'a'};
			int iterations = 1042;
			DecryptFile(BasePath, BasePath + ".tmp", "afckingpinecone.", salt, iterations);

			try
			{
				PasswordsDataSet->ReadXmlSchema(sr);
				PasswordsDataSet->ReadXml(BasePath + ".tmp");
			}
			catch(...)
			{ 
				File::Delete(BasePath + ".tmp");
			}

			File::Delete(BasePath + ".tmp");
			dataGridView1->DataSource = PasswordsDataSet;
			dataGridView1->DataMember = "data";
			
		}


		void saveTable()
		{
			try 
			{
				PasswordsDataSet->WriteXml(BasePath+".tmp");

				array<Byte>^ salt = gcnew array<Byte> { 'U', 'v', 'a', 'r', 'i', 'c', 'h', 'e', 'v', 'a'}; 
				int iterations = 1042;
				EncryptFile(BasePath + ".tmp", BasePath, "afckingpinecone.", salt, iterations);
				File::Delete(BasePath + ".tmp");

				MessageBox::Show("Ñîõğàíåíî!", "Ğåçóëüòàò");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message, "Ğåçóëüòàò");
				File::Delete(BasePath + ".tmp");
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
				MessageBox::Show(ex->Message, "Ğåçóëüòàò");
			}
		}


void DecryptFile(String^ sourceFilename, String^ destinationFilename, String^ password, array<Byte>^ salt, int iterations) {
	try {
		RijndaelManaged^ aes = gcnew RijndaelManaged();
		aes->BlockSize = aes->LegalBlockSizes[0]->MaxSize;
		aes->KeySize = aes->LegalKeySizes[0]->MaxSize;
		// NB: Rfc2898DeriveBytes initialization and subsequent calls to   GetBytes   must be eactly the same, including order, on both the encryption and decryption sides.
		Rfc2898DeriveBytes ^key = gcnew Rfc2898DeriveBytes(password, salt, iterations);
		aes->Key = key->GetBytes(aes->KeySize / 8);
		aes->IV = key->GetBytes(aes->BlockSize / 8);
		aes->Mode = CipherMode::CBC;
		ICryptoTransform^ transform = aes->CreateDecryptor(aes->Key, aes->IV);

		FileStream^ destination = gcnew FileStream(destinationFilename, FileMode::OpenOrCreate, FileAccess::Write, FileShare::None);
		CryptoStream^ cryptoStream = gcnew CryptoStream(destination, transform, CryptoStreamMode::Write);
		FileStream^ source = gcnew FileStream(sourceFilename, FileMode::Open, FileAccess::Read, FileShare::Read);
		source->CopyTo(cryptoStream);
		source->Close();
		cryptoStream->Close();
		destination->Close();
	}
	catch (Exception^ exception) { Console::WriteLine(exception->Message); }
}

void EncryptFile(String^ sourceFilename, String^ destinationFilename, String^ password, array<Byte>^ salt, int iterations) {
	try {
		RijndaelManaged^ aes = gcnew RijndaelManaged();
		aes->BlockSize = aes->LegalBlockSizes[0]->MaxSize;
		aes->KeySize = aes->LegalKeySizes[0]->MaxSize;
		// NB: Rfc2898DeriveBytes initialization and subsequent calls to   GetBytes   must be eactly the same, including order, on both the encryption and decryption sides.
		Rfc2898DeriveBytes^ key = gcnew Rfc2898DeriveBytes(password, salt, iterations);
		aes->Key = key->GetBytes(aes->KeySize / 8);
		aes->IV = key->GetBytes(aes->BlockSize / 8);
		aes->Mode = CipherMode::CBC;
		ICryptoTransform^ transform = aes->CreateEncryptor(aes->Key, aes->IV);

		FileStream^ destination = gcnew FileStream(destinationFilename, FileMode::OpenOrCreate, FileAccess::Write, FileShare::None);
		CryptoStream^ cryptoStream = gcnew CryptoStream(destination, transform, CryptoStreamMode::Write);
		FileStream^ source = gcnew FileStream(sourceFilename, FileMode::Open, FileAccess::Read, FileShare::Read);
		source->CopyTo(cryptoStream);
		source->Close();
		cryptoStream->Close();
		destination->Close();

	}
	catch (Exception^ exception) { Console::WriteLine(exception->Message); }
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
	private: System::Windows::Forms::ToolStripMenuItem^  ôàéëToolStripMenuItem;
	private: System::Windows::Forms::BindingSource^  bindingSource1;
	private: System::Windows::Forms::ToolStripMenuItem^  ñîçäàòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  îòêğûòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  âûõîäToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  ñîõğàíèòüToolStripMenuItem;



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
			this->ôàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîçäàòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îòêğûòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõğàíèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõğàíèòüÊàêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âûõîäToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->openFileDialog1->Filter = L"Âñå ôàéëû|*.*";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Âñå ôàéëû|*.*";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ôàéëToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(686, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ôàéëToolStripMenuItem
			// 
			this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->ñîçäàòüToolStripMenuItem,
					this->îòêğûòüToolStripMenuItem, this->ñîõğàíèòüToolStripMenuItem, this->ñîõğàíèòüÊàêToolStripMenuItem, this->âûõîäToolStripMenuItem
			});
			this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
			this->ôàéëToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->ôàéëToolStripMenuItem->Text = L"Ôàéë";
			// 
			// ñîçäàòüToolStripMenuItem
			// 
			this->ñîçäàòüToolStripMenuItem->Name = L"ñîçäàòüToolStripMenuItem";
			this->ñîçäàòüToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->ñîçäàòüToolStripMenuItem->Text = L"Ñîçäàòü";
			this->ñîçäàòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ñîçäàòüToolStripMenuItem_Click);
			// 
			// îòêğûòüToolStripMenuItem
			// 
			this->îòêğûòüToolStripMenuItem->Name = L"îòêğûòüToolStripMenuItem";
			this->îòêğûòüToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->îòêğûòüToolStripMenuItem->Text = L"Îòêğûòü";
			this->îòêğûòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::îòêğûòüToolStripMenuItem_Click);
			// 
			// ñîõğàíèòüToolStripMenuItem
			// 
			this->ñîõğàíèòüToolStripMenuItem->Name = L"ñîõğàíèòüToolStripMenuItem";
			this->ñîõğàíèòüToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->ñîõğàíèòüToolStripMenuItem->Text = L"Ñîõğàíèòü";
			this->ñîõğàíèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ñîõğàíèòüToolStripMenuItem_Click);
			// 
			// ñîõğàíèòüÊàêToolStripMenuItem
			// 
			this->ñîõğàíèòüÊàêToolStripMenuItem->Name = L"ñîõğàíèòüÊàêToolStripMenuItem";
			this->ñîõğàíèòüÊàêToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->ñîõğàíèòüÊàêToolStripMenuItem->Text = L"Ñîõğàíèòü êàê...";
			this->ñîõğàíèòüÊàêToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ñîõğàíèòüÊàêToolStripMenuItem_Click);
			// 
			// âûõîäToolStripMenuItem
			// 
			this->âûõîäToolStripMenuItem->Name = L"âûõîäToolStripMenuItem";
			this->âûõîäToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->âûõîäToolStripMenuItem->Text = L"Âûõîä";
			this->âûõîäToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::âûõîäToolStripMenuItem_Click);
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
			this->Text = L"Ìåíåäæåğ ïàğîëåé";
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
	//Óñòàíîâêà ñõåìû
	String^ s = rm->GetString(L"Schema_ru");
	StringReader^ sr = gcnew StringReader(s);
	PasswordsDataSet->ReadXmlSchema(sr);

	//Çàãğóçêà øàáëîíà
	s = rm->GetString(L"Template_ru");
	sr = gcnew StringReader(s);
	PasswordsDataSet->ReadXml(sr);
	
	dataGridView1->DataSource = PasswordsDataSet;
	dataGridView1->DataMember = "data";
}

private: System::Void âûõîäToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}

private: System::Void îòêğûòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
		MessageBox::Show(ex->Message, "Ğåçóëüòàò");
	}

}

private: System::Void ñîçäàòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	try
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
			saveFileDialog1->FileName->Length > 0)
		{
			
			BasePath = saveFileDialog1->FileName;
			
			//Ñîçäàíèå íîâûé ôàéë íà îñíîâå ğåñóğñà
			String^ s = rm->GetString(L"Template_ru");

			StreamWriter^ stream = gcnew StreamWriter(BasePath);
			stream->Write(s);
			stream->Close();

			refreshTable();
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message, "Ğåçóëüòàò");
	}
}

private: System::Void ñîõğàíèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		if (BasePath == "")
			saveAsTable();
		else
			saveTable();
		
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message, "Ğåçóëüòàò");
	}
}
private: System::Void ñîõğàíèòüÊàêToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
		MessageBox::Show(ex->Message, "Ğåçóëüòàò");
	}
}
};
}
