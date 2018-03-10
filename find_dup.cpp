#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <dirent.h>  
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <vector>
#include <time.h>
#include "find_dup.hpp"

using namespace std;

//global variable

vector<My_File> fileVec;
const char *exit_error = "Too many open files";
//function implements

long get_file_size(char *path)         //if success, return size. if error, return -1
{          
	FILE *pFile;
	long size;
	pFile = fopen(path,"rb");
	if(pFile == NULL){
	fprintf(stderr, "Error when getting the size of file %s : %s\n", path, strerror(errno));
	size = -1;
	}
	else{
	fseek(pFile,0,SEEK_END);
	size = ftell(pFile);
	fclose(pFile);
	}
	
	return size;
}

int listDir(char *path)     // if success, return 0 if error, return 1
 {  
         DIR              *pDir ;  
         struct dirent    *ent  ;   
         int               i=0  ;  
         char              childpath[1024] = {0}; 
	 My_File           my_file;
         
        
         pDir=opendir(path); //  open the path
         
         memset(childpath,0,sizeof(childpath)); //set to zero
	     memset(my_file.file_path,0,sizeof(my_file.file_path));

         if(NULL==pDir)
         {
         	fprintf(stderr, "Error when open path %s : %s\n", path, strerror(errno)); // if pDir is null, output error
         	return 1;
         }
   
         while((ent=readdir(pDir))!=NULL)   
         {                  
                 if(ent->d_type & DT_DIR) 
                 {  
   
                        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)  
                                       //if d_name is . or .. , continue.
                                 continue;  
   
                        sprintf(childpath,"%s/%s",path,ent->d_name);  // get childpath
   
                        listDir(childpath);
			 
   
                 }  
               else  //if d_type isn't DT_DIR, we meet a file and push it to fileVec
               {   
                 
		   sprintf(my_file.file_path,"%s/%s",path,ent->d_name);
	
		   if(get_file_size(my_file.file_path) > -1){
		   my_file.size = get_file_size(my_file.file_path);}    //get the size of the file
		   else{
			return 1;
		   }
		   fileVec.push_back(my_file);        //push the file to fileVec
               }
         }  
   		closedir(pDir);
		return 0;
 }  
 

int file_equals(char *path1, char *path2)   //success:1 fail:0
{         
	int flag = 1;
	FILE *p1 = fopen(path1, "r");
	FILE *p2 = fopen(path2, "r");
	char buffer1[1024];
	char buffer2[1024];
	memset(buffer1,0,sizeof(buffer1)); //set to zero
	memset(buffer2,0,sizeof(buffer2));
	fread(buffer1,sizeof(char),1024,p1);
	fread(buffer2,sizeof(char),1024,p2);
	if(strcmp(buffer1, buffer2)!=0){
			flag = 0;
	}
	while(!feof(p1) && !feof(p2))
    {   
		if(strcmp(buffer1, buffer2)!=0){
			flag = 0;
			break;
		}
		fread(buffer1,sizeof(char),1024,p1);
		fread(buffer2,sizeof(char),1024,p2);
		
		memset(buffer1,0,sizeof(buffer1)); //set to zero
	    memset(buffer2,0,sizeof(buffer2));
	}
	
	fclose(p1);
	fclose(p2);
	//cout << "flag:"<< flag << endl;
	return flag;
}


 	

