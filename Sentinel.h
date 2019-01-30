/*************************************************************************
    > File Name: Sentinel.h
    > Author: Ys
    > Created Time: 2019年01月30日 星期三 13时26分54秒
 ************************************************************************/
#include <sys/stat.h> 
#include <dirent.h>
#include <map>
#include <string>

using std::map;
using std::string;

class Sentinel
{
public:
	Sentinel(const string& configFile);
    bool handleFiles();
private:
	bool sortFiles();
	bool checkDir(const string& dir);
private:
	//key:pattern -> value:the addres for store files
	map<string, string> sortRule_;
	string srcDir_;
	string desDir_;
    string fileName_;     // return value for readdir()
    DIR	  *dirFd_;        // return value for opendir()
};
