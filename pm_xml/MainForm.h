#include <sstream>
#include <msclr\marshal_cppstd.h>

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
	private: System::Windows::Forms::ToolStripMenuItem^  ������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;

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

		void newTable()
		{
			PasswordsDataSet->Clear();
			//��������� �����
			String^ s = rm->GetString(L"Schema_ru");
			StringReader^ sr = gcnew StringReader(s);
			PasswordsDataSet->ReadXmlSchema(sr);

			//�������� �������
			s = rm->GetString(L"Template_ru");
			sr = gcnew StringReader(s);
			PasswordsDataSet->ReadXml(sr);

			dataGridView1->DataSource = PasswordsDataSet;
			dataGridView1->DataMember = "data";
		}


		void saveTable()
		{
			try 
			{
				PasswordsDataSet->WriteXml(BasePath+".tmp");
				PasswordsDataSet->WriteXmlSchema(BasePath + "1.tmp");
				array<Byte>^ salt = gcnew array<Byte> { 'U', 'v', 'a', 'r', 'i', 'c', 'h', 'e', 'v', 'a'}; 
				int iterations = 1042;
				EncryptFile(BasePath + ".tmp", BasePath, "afckingpinecone.", salt, iterations);
				File::Delete(BasePath + ".tmp");

				MessageBox::Show("���������!", "���������");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message, "���������");
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
				MessageBox::Show(ex->Message, "���������");
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
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  �������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �����ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  ���������ToolStripMenuItem;



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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->PasswordsDataSet = (gcnew System::Data::DataSet());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PasswordsDataSet))->BeginInit();
			this->menuStrip1->SuspendLayout();
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
			this->openFileDialog1->Filter = L"��� �����|*.*";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"��� �����|*.*";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->����ToolStripMenuItem,
					this->toolStripMenuItem2, this->toolStripMenuItem1, this->toolStripTextBox1
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(686, 27);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->�������ToolStripMenuItem,
					this->�������ToolStripMenuItem, this->���������ToolStripMenuItem, this->������������ToolStripMenuItem, this->�����ToolStripMenuItem
			});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(48, 23);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// �������ToolStripMenuItem
			// 
			this->�������ToolStripMenuItem->Name = L"�������ToolStripMenuItem";
			this->�������ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->�������ToolStripMenuItem->Text = L"�������";
			this->�������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�������ToolStripMenuItem_Click);
			// 
			// �������ToolStripMenuItem
			// 
			this->�������ToolStripMenuItem->Name = L"�������ToolStripMenuItem";
			this->�������ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->�������ToolStripMenuItem->Text = L"�������";
			this->�������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�������ToolStripMenuItem_Click);
			// 
			// ���������ToolStripMenuItem
			// 
			this->���������ToolStripMenuItem->Name = L"���������ToolStripMenuItem";
			this->���������ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->���������ToolStripMenuItem->Text = L"���������";
			this->���������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::���������ToolStripMenuItem_Click);
			// 
			// ������������ToolStripMenuItem
			// 
			this->������������ToolStripMenuItem->Name = L"������������ToolStripMenuItem";
			this->������������ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->������������ToolStripMenuItem->Text = L"��������� ���...";
			this->������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::������������ToolStripMenuItem_Click);
			// 
			// �����ToolStripMenuItem
			// 
			this->�����ToolStripMenuItem->Name = L"�����ToolStripMenuItem";
			this->�����ToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->�����ToolStripMenuItem->Text = L"�����";
			this->�����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�����ToolStripMenuItem_Click);
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Enabled = false;
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(22, 23);
			this->toolStripMenuItem2->Text = L" ";
			this->toolStripMenuItem2->Visible = false;
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(57, 23);
			this->toolStripMenuItem1->Text = L"�����:";
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 23);
			this->toolStripTextBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::toolStripTextBox1_TextChanged);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(686, 241);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"�������� �������";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PasswordsDataSet))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	newTable();
}

private: System::Void �����ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}

private: System::Void �������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
		MessageBox::Show(ex->Message, "���������");
	}

}

private: System::Void �������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	try
	{
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
			saveFileDialog1->FileName->Length > 0)
		{
			
			BasePath = saveFileDialog1->FileName;
			
			//�������� ����� ���� �� ������ �������
			String^ s = rm->GetString(L"Template_ru");

			StreamWriter^ stream = gcnew StreamWriter(BasePath);
			stream->Write(s);
			stream->Close();

			newTable();
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message, "���������");
	}
}

private: System::Void ���������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		if (BasePath == "")
			saveAsTable();
		else
			saveTable();
		
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message, "���������");
	}
}
private: System::Void ������������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
		MessageBox::Show(ex->Message, "���������");
	}
}
private: System::Void toolStripTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	String ^search = toolStripTextBox1->Text;
	dataGridView1->CurrentCell = dataGridView1->Rows[dataGridView1->Rows->Count-1]->Cells[0];
	
	if (search == "") {
		for (int i = 0; i < dataGridView1->Rows->Count; i++)
			dataGridView1->Rows[i]->Visible = true;
	}
	else
		try {
		for (int i = 0; i < dataGridView1->Rows->Count; i++) {
			dataGridView1->Rows[i]->Selected = false;
			dataGridView1->Rows[i]->Visible = (dataGridView1[0, i]->Value->ToString() == search) || (dataGridView1[1, i]->Value->ToString() == search) || (dataGridView1[2, i]->Value->ToString() == search);
		}
	}
	catch(...)
	{ }

}
};
}
