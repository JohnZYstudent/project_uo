/* 
 * Project 1 command.c
 * 
 * Author: <John Zhou>
 * 
 * Date: 10/20/2019 
 * 
 * Notes: <write anything you would like us to keep in mind when grading.> 
 * Proper code documentation includes: 
 * 1. Using a readable formatting. 
 * 2. Adequate use of comments and white space.  
 * 3. Explanation attached to code blocks that do not work. 
 * 4. Keep the width of the program under 80 columns to avoid overwrap. 
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> 
#include "command.h"

void listDir(){
	struct dirent *entry;
	char path[100];
	DIR *dir;
	getcwd(path,sizeof(path));
	dir = opendir(path);
	while((entry = readdir(dir)) != NULL){
		write(1,entry->d_name,strlen(entry->d_name));
		write(1," ",1);
	}
	write(1,"\n",1);
	closedir(dir);
} /*for the ls command*/

void showCurrentDir(){
	char path[100];
	if(getcwd(path,sizeof(path)) != NULL){
		write(1, path,strlen(path));
		write(1,"\n",1);
	}
} /*for the pwd command*/

void makeDir(char *dirName){
	mkdir(dirName, S_IRWXU);
} /*for the mkdir command*/

void changeDir(char *dirName){
	chdir(dirName);
} /*for the cd command*/

void copyFile(char *sourcePath, char *destinationPath){
	int destfile;
	int sourfile;
	int data;
	char *filename;
	char currentdir[100];
	char buffer[1024];
	getcwd(currentdir,sizeof(currentdir));
	sourfile = open(sourcePath, O_RDONLY);
	destfile = open(destinationPath, O_WRONLY | O_CREAT);
	if(destfile == -1){
		filename = strrchr(sourcePath, '/')+1;
		chdir(destinationPath);
		destfile = open(filename, O_WRONLY | O_CREAT);
	}
	
	while((data = read(sourfile,buffer,sizeof(buffer))) > 0){
		destfile = write(destfile,buffer,data);
	}
	chdir(currentdir);
	close(sourfile);
	close(destfile);
} /*for the cp command*/

void moveFile(char *sourcePath, char *destinationPath){
	int destfile;
	int sourfile;
	int data;
	int index;
	char buffer[1024];
	char destination[100];
	char currentdir[100];
	char *filename;
	getcwd(currentdir,sizeof(currentdir));
	sourfile = open(sourcePath, O_RDONLY);
	destfile = open(destinationPath, O_WRONLY | O_CREAT);
	if(destfile == -1){
		filename = strrchr(sourcePath, '/')+1;
		chdir(destinationPath);
		destfile = open(filename, O_WRONLY | O_CREAT);
	}
	while((data = read(sourfile,buffer,sizeof(buffer))) > 0){
		destfile = write(destfile,buffer,data);
	}
	chdir(currentdir);
	unlink(sourcePath);
	close(sourfile);
	close(destfile);
	
} /*for the mv command*/

void deleteFile(char *filename){
	unlink(filename);
} /*for the rm command*/

void displayFile(char *filename){
	char buffer[1024];
	DIR *dirsearch;
	struct dirent *dirent;
	int file;
	int data;
	dirsearch = opendir(".");
	while((dirent = readdir(dirsearch)) != NULL){
		if(strcmp(dirent->d_name,filename) == 0){
			file = open(filename,O_RDONLY);
			while((data = read(file,buffer,sizeof(buffer))) > 0){
				write(1,buffer,data);
			}
		}
	}
	close(file);
	closedir(dirsearch);
} /*for the cat command*/
