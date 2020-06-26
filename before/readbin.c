#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	char *filename = argv[1];

	//filesystem *vfs = malloc(sizeof(filesystem));
	

	FILE *f;
	f = fopen(filename, "rb+");
	if(!f){
		perror("failed to open the file\n");
		return 1;
	}

	int len, size;
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	
	size = len / 72;
	rewind(f);
	printf("Directory Table size: %d\n", size);
	/*
	vfs->records = malloc(sizeof(fname_record) * size);

	for (int i=0; i<size; i++){
		fread(&vfs->records[i].fname, sizeof(char), 64, f);
		fread(&vfs->records[i].offset, sizeof(uint32_t), 1, f);
		fread(&vfs->records[i].length, sizeof(uint32_t), 1, f);
	}

	for (int j=0; j< size; j++){
		printf("filename: %s\n", vfs->records[j].fname);
		printf("offset is: %d\n", vfs->records[j].offset);
		printf("length is: %d\n", vfs->records[j].length);
	}
*/
	Record rec;
	
	while(fread(&rec, sizeof(Record), 1, aux->directorytable) == 1){
		if(strcmp(filename, rec.fname) == 0){
			fseek(aux->directorytable, -72, SEEK_CUR);
			rec.fname[0] = '\0';
			fwrite(&rec, sizeof(Record), 1, aux->directorytable);
			return 0;
		}
	}

	return 0;
}