#include "FileNavmeshParser.h"

recast_navigation::FileNavmeshParser::FileNavmeshParser()
{
	_pFileData = NULL;
	_fileSize = 0;
}

recast_navigation::FileNavmeshParser::~FileNavmeshParser()
{
	if (!_pFileData)
		return;
	delete _pFileData;
	_pFileData = NULL;
}

bool recast_navigation::FileNavmeshParser::load(const string & filename)
{
	_pFileData = FileUtils::getInstance()->getFileData(filename, "r", &_fileSize);

	if (_fileSize == 0)
	{
		CCLOG("file not found: %s", filename);
		_pFileData = NULL;
		return false;
	}

	return true;
}

void recast_navigation::FileNavmeshParser::parse()
{
	if (_fileSize == 0)
		return;

	string curStr = "";
	DataType curState = invalid;
	int count = 0;
	while (count < _fileSize)
	{
		if (_pFileData[count] == unsigned char(" "))
			continue;


	}
}
