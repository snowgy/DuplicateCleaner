#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <dirent.h>  
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include "find_dup.hpp"
#include "VectorSort.hpp"

using namespace std;

int main(int argc,char *argv[])  
 { 
	clock_t start, finish;
	double total_time;
	const char * firstpath;
	int length;
	start = clock();     //start the time
 	if(argc!=2)
 		{
 			fprintf(stderr, "the argument cout is not 2.\nUsage:./find_dup /home/gongyue/mycode\n");
 			return 1;
 		}
	else{
		const char * firstpath = argv[1];
		length = strlen(firstpath);
	}	
        if(listDir(argv[1])==1) //when listDir returns 1, it failed
	{
		return 1;
	}
	std::sort(fileVec.begin(),fileVec.end(),SortBySize);  //sort the vector by the size
	
	for(int i=0; i< fileVec.size()-1; i++){
		if(fileVec[i].size==0 && fileVec[i+1].size==0) //when sizes both 0, must be equal 
		{
			string path1(fileVec[i].file_path);
			string path2(fileVec[i+1].file_path);
			printf("%s\t%s\n", path1.substr(length+1).c_str(), path2.substr(length+1).c_str());
			continue;		
		}
		//when sizes euqal, call file_equals
		if(fileVec[i].size == fileVec[i+1].size){
			if( file_equals(fileVec[i].file_path, fileVec[i+1].file_path))
			{
				string path1(fileVec[i].file_path);
				string path2(fileVec[i+1].file_path);
				printf("%s\t%s\n", path1.substr(length+1).c_str(), path2.substr(length+1).c_str());
			}
			else  //when the adjacent files don't equal, apply a double loop to make sure
			{
				for(int j=i+2; j<fileVec.size(); j++)
				{
					if(fileVec[i].size != fileVec[j].size) break;
					else{
						
						if(file_equals(fileVec[i].file_path, fileVec[j].file_path)){
							string path1(fileVec[i].file_path);
							string path2(fileVec[j].file_path);
							printf("%s\t%s\n", path1.substr(length+1).c_str(), path2.substr(length+1).c_str());
							break;
						}
					}
				}
			}
	}
}
	finish = clock();  // end the time
	total_time = (double)(finish-start)/ CLOCKS_PER_SEC; //calculate total time
	fprintf(stderr, "Total Time: %f\n", total_time);
	
	return 0;
}
