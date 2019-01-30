/*************************************************************************
    > File Name: Sentinel.cpp
    > Author: Ys
    > Created Time: 2019年01月30日 星期三 13时30分38秒
 ************************************************************************/
#include <iostream>
#include "Sentinel.h"
#include <string.h>
#include <sys/stat.h>
#include <regex>
#include <unistd.h>

using std::cout;
using std::endl;

int errorHandle(const string& info, int ret);

Sentinel::Sentinel(const string& configFile)
{
	//todo: read the configFile and construct the sortRule. 

	
	// check if dir is valid
	srcDir_ = "/home/ciker/project/Sentinel";
	desDir_ = "/home/ciker/project/Sentinel/des";
     if(!checkDir(srcDir_))
         return;

     // check if dir is valid
     if(!checkDir(desDir_)){
         string command("mkdir ");
         command += desDir_;
         system(command.c_str());
         cout << "handleFiles():" << command << endl;
     }
	//test
	sortRule_["(.*)(\\.cpp)"] = desDir_ + "/cpp";                                                 
    sortRule_["(.*)(\\.c)"]   = desDir_ + "/c";
}

bool Sentinel::handleFiles()
{
     //open the srcDir for read
	 struct stat s;
     memset(&s, 0, sizeof(s));
     dirFd_ = opendir(srcDir_.c_str()); //打开的目录由操作系统自动关闭？？？
     if( nullptr == dirFd_ )
         errorHandle("Can not open dir(" + srcDir_ + ")", false);
     //read all the files in the dir
	 struct dirent *fileName;
	 while((fileName = readdir(dirFd_)) != NULL ){
         lstat( fileName->d_name , &s );
         //if is a subDir
         if(S_ISDIR( s.st_mode ) ){
             //cout<< "handleFile(): " << filename->d_name << " is a dir!"<<endl;
             continue;
         }
		 fileName_ = srcDir_ + '/' + fileName->d_name;
         sortFiles();
     }
     return true;

}

bool Sentinel::sortFiles()
{
	map<string, string>::iterator it = sortRule_.begin();
     for(; it != sortRule_.end(); ++it){
         if(!std::regex_match(fileName_, std::regex(it->first)))
             continue;
         // check if dir is valid
         if(!checkDir(it->second)){
             string command("mkdir ");
             command += it->second;
             system(command.c_str());
             cout << "sortFiles():" << command << endl;
         }
         string command("cp  ");
         command += fileName_ + "  " + it->second;
         cout << command << endl;
         system(command.c_str());
     }
     return true;
}

bool Sentinel::checkDir(const string& dir)
{
	struct stat s;
    memset(&s, 0, sizeof(s));
    lstat( dir.c_str() , &s );
    if( ! S_ISDIR( s.st_mode ) ){
        cout<< dir << "is not a valid directory !"<<endl;
        return false;
    }
    return true;

}

int errorHandle(const string& info, int ret)
{
	cout << info << endl;
	exit(ret);
}
