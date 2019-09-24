#include "stdafx.h"
#include "SimpleFile.h"


SimpleFile::SimpleFile()
{

}

BOOLEAN SimpleFile::ReadFile(WCHAR * pathName)
{
	//读取文件
	wifstream inFile(pathName, ios::in);
	//如果读取的内容为空，返回一个值为失败
	if (!inFile)
	{
		return false;
	}
	inFile.imbue(locale(locale(), "", LC_CTYPE));
	//定义一个缓冲
	wstring buffer;
	while (inFile.good())
	{
		std::getline(inFile, buffer);
		//将缓冲当中的数据放到数据FileContent中
		FileContent.push_back(buffer);
	}
	//关闭上
	inFile.close();
	return TRUE;
}

BOOLEAN SimpleFile::WriteFile(WCHAR * pathName, WCHAR * fileLines)
{
	if (fileLines != NULL)
	{
		wstringstream mySS;
		//将每行文件放到mySS
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

