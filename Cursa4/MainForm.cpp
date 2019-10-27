#include "MainForm.h"

System::Void Cursa4::MainForm::loadMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	loadImageDialog->Filter = "Изображения (bmp, jpg, jpeg) | *.jpg;*.bmp;*.jpeg";
	loadImageDialog->Title = "Выберите файл изображения";
	if (loadImageDialog->ShowDialog() ==
		System::Windows::Forms::DialogResult::OK)
	{
		image1Box->Image = Bitmap::FromFile(loadImageDialog->FileName);
		delete image2Box->Image;
		image2Box->Image = nullptr;
		saveMenuItem->Enabled = false;
	}

}

System::Void Cursa4::MainForm::saveMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	saveImageDialog->Title = "Сохранение изображения";
	saveImageDialog->Filter = "Изображения (*.bmp, *.jpg, *.jpeg) | *.jpg; *.bmp; *.jpeg";
	if (saveImageDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		Bitmap^ bitmap = gcnew Bitmap(image2Box->Image);
		bitmap->Save(saveImageDialog->FileName);
	}
}

System::Void Cursa4::MainForm::configureDevices()
{
	cl_uint numberOfPlatforms;
	cl_platform_id platform = NULL;
	cl_int status = clGetPlatformIDs(0, NULL, &numberOfPlatforms);
	if (numberOfPlatforms > 0)
	{
		cl_platform_id* platforms = new cl_platform_id[numberOfPlatforms];
		status = clGetPlatformIDs(numberOfPlatforms, platforms, NULL);
		platform = platforms[0];
		delete[] platforms;
	}
	cl_uint numberOfDevices = 0;
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &numberOfDevices);
	if (status != CL_SUCCESS)
	{
		System::Windows::Forms::MessageBox::Show("Device not found!", "Error", System::Windows::Forms::MessageBoxButtons::OK);
		return;
	}
	this->devices = new cl_device_id[numberOfDevices];
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, numberOfDevices, this->devices, NULL);
	if (status != CL_SUCCESS)
	{
		System::Windows::Forms::MessageBox::Show("Не найдено устройств, поддерживающих OpenCL!", "Ошибка", System::Windows::Forms::MessageBoxButtons::OK);
		return System::Void();
	}
	this->numberOfDevices = numberOfDevices;
	System::Windows::Forms::MessageBox::Show("Устройства проинициализированы!", "Успешно", System::Windows::Forms::MessageBoxButtons::OK);
	return System::Void();
}

System::Void Cursa4::MainForm::disposeDevices()
{
	delete[] devices;
	numberOfDevices = 0;
	addDeviceListToList();
	return System::Void();
}

System::Void Cursa4::MainForm::DeviceInitMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	configureDevices();
	addDeviceListToList();
}

System::Void Cursa4::MainForm::addDeviceListToList()
{
	String ^ firstVar = methodComboBox->Items[0]->ToString();
	String ^ secondVar = methodComboBox->Items[1]->ToString();
	methodComboBox->Items->Clear();
	methodComboBox->Items->Add(firstVar);
	methodComboBox->Items->Add(secondVar);

	if (numberOfDevices > 0)
	{
		methodComboBox->Items->Add("OpenCL");
	}

	methodComboBox->SelectedIndex = 0;

	return System::Void();
}

System::Void Cursa4::MainForm::остановкаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	disposeDevices();
}

System::Void Cursa4::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	methodComboBox->SelectedIndex = 0;
}

System::Void Cursa4::MainForm::processButton_Click(System::Object^ sender, System::EventArgs^ e) {
	delete image2Box->Image;
	image2Box->Image = nullptr;

	DateTime dt1 = DateTime::Now;
	if (methodComboBox->SelectedIndex == SEQUENTIAL_ITEM)
	{
		image2Box->Image = Utils::SequentialChangeContrast(gcnew Bitmap(image1Box->Image), double(numericUpDown1->Value) / 100.0);
	}
	else if (methodComboBox->SelectedIndex == OPENMP_ITEM)
	{
		image2Box->Image = Utils::OmpChangeContrast(gcnew Bitmap(image1Box->Image), double(numericUpDown1->Value) / 100.0);
	}
	else
	{
		int deviceNum = int(methodComboBox->SelectedIndex - 2);
		image2Box->Image = Utils::CLChangeContrast(devices, gcnew Bitmap(image1Box->Image), double(numericUpDown1->Value) / 100.0);
	}
	saveMenuItem->Enabled = true;
	DateTime dt2 = DateTime::Now;
	TimeSpan ts = dt2 - dt1;

	MessageBox::Show(ts.TotalMilliseconds.ToString() + " мсек", "Время работы алгоритма", System::Windows::Forms::MessageBoxButtons::OK);
}
