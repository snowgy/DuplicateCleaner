#ifndef FIND_DUP_HPP
#define FIND_DUP_HPP



//define struct my_file
typedef struct my_file{
	char file_path[1024];
	long size;
}My_File;
//declare a extern global variable

extern std::vector<My_File> fileVec;

//declare functions

long get_file_size(char *path);
int listDir(char *path);
int file_equals(char *path1, char *path2);

//declare constant
extern const char * firstpath;
#endif
