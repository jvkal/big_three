#include "stdafx.h"
#include "SimpleFile.h"


SimpleFile::SimpleFile()
{

}

BOOLEAN SimpleFile::ReadFile(WCHAR * pathName)
{
	//��ȡ�ļ�
	wifstream inFile(pathName, ios::in);
	//�����ȡ������Ϊ�գ�����һ��ֵΪʧ��
	if (!inFile)
	{
		return false;
	}
	inFile.imbue(locale(locale(), "", LC_CTYPE));
	//����һ������
	wstring buffer;
	while (inFile.good())
	{
		std::getline(inFile, buffer);
		//�����嵱�е����ݷŵ�����FileContent��
		FileContent.push_back(buffer);
	}
	//�ر���
	inFile.close();
	return TRUE;
}

BOOLEAN SimpleFile::WriteFile(WCHAR * pathName, WCHAR * fileLines)
{
	if (fileLines != NULL)
	{
		wstringstream mySS;
		//��ÿ���ļ��ŵ�mySS
		mySS << fileLines;
		wofstream outFile(pathName, ios::out | ios::trunc);
		if (!outFile)
		{
			return FALSE;
		}
		outFile.imbue(locale(locale(), "", LC_CTYPE));
		wstring myString = mySS.str();
		outFile.write(myString.c_str(), wcslen(fileLines));
		outFile.close();
	}
	return TRUE;
}

vecLinesContainer SimpleFile::getFileLines(WCHAR * pathName)
{
	ReadFile(pathName);
	return FileContent;
}

