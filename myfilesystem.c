#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECORD_SIZE (72)

#include "myfilesystem.h"

/* Data Structure */
typedef struct filesystem {
	FILE* filedata;
	FILE* directorytable;
	FILE* hashdata;
	ssize_t dir_size;
	int n_processors;
} VFS;

typedef struct record {
	char fname[64];
	unsigned int offset;
	unsigned int length;
} Record;
/*******************/

void * init_fs(char * f1, char * f2, char * f3, int n_processors) {
	FILE* f_data = fopen(f1, "rb+");
	FILE* dir_tab = fopen(f2, "rb+");
	FILE* h_data = fopen(f3, "rb+");
	
	// assign given parameters to VFS
	VFS *helper = malloc(sizeof(VFS));
	if(!f_data){
		perror("failed to read f1\n");
		return NULL;
	}
	else{
		helper->filedata = f_data;
	}
	
	if(!dir_tab){
		perror("failed to read f2\n");
		return NULL;
	}
	else{
		helper->directorytable = dir_tab;
	}
	
	if(!h_data){
		perror("failed to read f3\n");
		return NULL;
	}
	else{
		helper->hashdata = h_data;
	}
	
	// find the size of directory table
	fseek(dir_tab, 0, SEEK_END);
	int dir_len = ftell(dir_tab);
	int tab_size = dir_len / RECORD_SIZE;
	rewind(dir_tab);
	
	helper->dir_size = tab_size;
	helper->n_processors = n_processors;
	
    return (void *)helper;
}

void close_fs(void * helper) {
	VFS* aux = (VFS*)helper;
	fclose(aux->filedata);
	fclose(aux->directorytable);
	fclose(aux->hashdata);
	free(aux);
    return;
}

int create_file(char * filename, size_t length, void * helper) {
	VFS* aux = (VFS*)helper;
	
	Record rec;
	
	while(fread(&rec, sizeof(Record), 1, aux->directorytable) == 1){
		// Case 1: if filename already exists
		if(strcmp(filename, rec.fname) == 0){
			return 1;
		}
	}
	
	fseek(aux->directorytable, 0, SEEK_SET);
	fwrite(&filename, sizeof(char), 63, aux->directorytable);
	
	
	
    return 0;
}

int resize_file(char * filename, size_t length, void * helper) {
    return 0;
}

void repack(void * helper) {
    return;
}

int delete_file(char * filename, void * helper) {
	VFS* aux = (VFS*)helper;
	
	Record rec;
	
	while(fread(&rec, sizeof(Record), 1, aux->directorytable) == 1){
		if(strcmp(filename, rec.fname) == 0){
			rec.fname[0] = '\0';
			if(fseek(aux->directorytable, ftell(aux->directorytable)-RECORD_SIZE, SEEK_SET) == 0){
				fwrite(&rec, sizeof(Record), 1, aux->directorytable);
				return 0;
			}
			else{
				perror("fwrite() failed\n");
				return 1;
			}
			
		}
	}
	
    return 1;
}

int rename_file(char * oldname, char * newname, void * helper) {
	VFS* aux = (VFS*)helper;
	
	Record rec;
	
	while(fread(&rec, sizeof(Record), 1, aux->directorytable) == 1){
		// Case 1: if newname is gonna be duplicated
		if(strcmp(newname, rec.fname) == 0){
			return 1;
		}
		else if(strcmp(oldname, rec.fname) == 0){
			strncpy(rec.fname, newname, 64);
			if(fseek(aux->directorytable, ftell(aux->directorytable)-RECORD_SIZE, SEEK_SET) == 0){
				fwrite(&rec, sizeof(Record), 1, aux->directorytable);
				return 0;
			}
			else{
				perror("fwrite() failed\n");
				return 1;
			}
		}
		
	}
	
    return 1;
}

int read_file(char * filename, size_t offset, size_t count, void * buf, void * helper) {
	VFS* aux = (VFS*)helper;
	
	Record rec;
	
	buf = calloc(count, sizeof(char));
	
	while(fread(&rec, sizeof(Record), 1, aux->directorytable) == 1){
		if(strcmp(filename, rec.fname) == 0){
			// Case 1: provided offset make impossible to read count bytes; return 2
			if(rec.offset + offset > rec.length){
				return 2;
			}
			// Otherwise
			break;
		}
	}

	if(fseek(aux->filedata, rec.offset + offset, SEEK_SET) == 0){
		fread(&buf, sizeof(buf), 1, aux->filedata);
		return 0;
	}
	else{
		perror("fseek failed\n");
	}
	
    return 1;
}

int write_file(char * filename, size_t offset, size_t count, void * buf, void * helper) {
    return 0;
}

ssize_t file_size(char * filename, void * helper) {
	VFS* aux = (VFS*)helper;
	
	Record rec;
	
	while(fread(&rec, sizeof(Record), 1, aux->directorytable) == 1){
		if(strcmp(filename, rec.fname) == 0){
			return rec.length;
		}
	}
	
	
	return -1;
}

void fletcher(uint8_t * buf, size_t length, uint8_t * output) {
    return;
}

void compute_hash_tree(void * helper) {
    return;
}

void compute_hash_block(size_t block_offset, void * helper) {
    return;
}