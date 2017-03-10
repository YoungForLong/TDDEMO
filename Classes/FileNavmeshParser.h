#ifndef _FILE_NAVMESH_PARSER_H_
#define _FILE_NAVMESH_PARSER_H_

#include<cocos2d.h>

using namespace std;
USING_NS_CC;

namespace recast_navigation {

	class FileNavmeshParser
	{
	public:
		enum DataType{
		comment,
		poly,
		vertex,
		invalid
		};

		FileNavmeshParser();
		~FileNavmeshParser();

		bool load(const string& filename);

		void parse();
	private:
		unsigned char* _pFileData;
		ssize_t _fileSize;
	};

	typedef FileNavmeshParser FNP;
}


#endif
