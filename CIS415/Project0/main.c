//Name:John(Ziyuan) Zhou
//ID:951563967
//CIS415 Project0
//own work
#include "anagram.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	FILE* f1, *f2;
	if(argc == 1){
		f1 = stdin;
		f2 = stdout;
	}else if(argc == 2){
		if((f1 = fopen(argv[1],"r")) == NULL){
			printf("open %s failed", argv[1]);
			return -1;
		}
		f2 = stdout;
	}else if(argc >= 3){
		if((f1 = fopen(argv[1],"r")) == NULL){
			printf("open %s failed", argv[1]);
			return -1;
		}
		if((f2 = fopen(argv[2],"w")) == NULL){
			printf("open %s failed", argv[1]);
			return -1;
		}
	}
	int fstline = 1;
	struct AnagramList* An;
	while(!feof(f1)){
		char* str = (char*)malloc(150*sizeof(char));
		fscanf(f1,"%s",str);
		if(strcmp(str,"exit")==0){
			free(str);
			break;
		}
		if(strlen(str)>0){
			if(fstline){
				fstline = 0;
				An = MallocAList(str);
			}else{
				AddWordAList(&An,str);
			}
		}else{
			free(str);
		}
	}
	PrintAList(f2,An);
	fclose(f1);
	fclose(f2);
	FreeAList(&An);
	return 0;
}