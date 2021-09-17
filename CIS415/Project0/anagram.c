//Name:John(Ziyuan) Zhou
//ID:951563967
//CIS415 Project0
//own work
#include "anagram.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void lowercase(char *word){
	int i = 0;
	while(i < strlen(word)){
		word[i] = tolower(word[i]);
		i++;
	}
}

int cmp(const void* p, const void* q){
	char* f = (char*)p;
	char* s = (char*)q;
	return strcmp(f,s);
}

void sort(char** word){
	int length = strlen(*word);
	qsort(*word,length,sizeof(char),cmp);
}

struct StringList *MallocSList(char *word){
	struct StringList *SL = (struct StringList*)malloc(sizeof(struct StringList));
	if(NULL == SL){
		return NULL;
	}
	lowercase(word);
	SL->Word = word;
	SL->Next = NULL;
	return SL;
}


void AppendSList(struct StringList **head, struct StringList *node){
	struct StringList* p = (*head);
	while(NULL != p->Next){
		p = p->Next;
	}
	p->Next = node;
}

void FreeSList(struct StringList **node){
	struct StringList* p, *q;
	p = (*node)->Next;
	while(p){
		q = p->Next;
		free(p->Word);
		free(p);
		p = q;
	}
	free((*node)->Word);
	free(*node);
	*node = NULL;
}

void PrintSList(FILE *file,struct StringList *node){
	if(node != NULL){
		while(node->Next != NULL){
			fprintf(file,"\t%s\n",node->Word);
			node = node->Next;
		}
		fprintf(file, "\t%s\n", node->Word);
	}
	
}

int SListCount(struct StringList *node){
	int count = 0;
	if(node != NULL){
		count = 1;
		while(node->Next != NULL){
			count++;
			node = node->Next;
		}
	}
	return count;
}

struct AnagramList* MallocAList(char *word){
	struct AnagramList* AL = (struct AnagramList*)malloc(sizeof(struct AnagramList));
	char* p = (char*)malloc(strlen(word) * sizeof(char) + 1);
	strcpy(p,word);
	sort(&p);
	AL->Anagram = p;
	AL->Words = MallocSList(word);
	AL->Next = NULL;
	return AL;
}

void FreeAList(struct AnagramList **node){
	struct AnagramList* p, *q;
	p = (*node)->Next;
	while(p){
		q = p->Next;
		FreeSList(&(p->Words));
		free(p->Anagram);
		free(p);
		p = q;
	}
	FreeSList(&((*node)->Words));
	free((*node)->Anagram);
	free(*node);
	*node = NULL;
}

void PrintAList(FILE *file,struct AnagramList *node){
	if(node != NULL){
		int count = 0;
		while(node->Next != NULL){
			count = SListCount(node->Words);
			if(count > 1){
				fprintf(file,"%s:%d\n",node->Anagram,count);
				PrintSList(file,node->Words);
			}
			node = node->Next;
		}
		count = SListCount(node->Words);
		if(count > 1){
				fprintf(file,"%s:%d\n",node->Anagram,count);
				PrintSList(file,node->Words);
		}
	}
}

void AddWordAList(struct AnagramList **node, char *word){
	struct AnagramList* p = *node;
	char* q = (char*)malloc(strlen(word)*sizeof(char) + 1);
	strcpy(q,word);
	sort(&q);
	int found = 0;
	while(p != NULL && p->Next != NULL){
		if(strcmp(p->Anagram,q) == 0){
			found = 1;
			break;
		}
		p = p->Next;
	}
	if(strcmp(p->Anagram,q) == 0){
			found = 1;
	}
	free(q);
	if(found){
		AppendSList(&p->Words,MallocSList(word));
		return;
	}
	struct AnagramList* a = MallocAList(word);
	p->Next = a;
}

