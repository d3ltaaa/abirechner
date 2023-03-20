#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct fach
{
	char* abbr;
	char subject_type;
	float grades[4];
	float abi;
	int included[4];
}fach;


// header files
int print_buffer(char* buffer);
int combine_abbr(fach* subjects);


int num_sub = 12;

fach mathe, physik, philosophie, englisch, deutsch, chemie, biologie, sowi, geschichte, kunst, sport, MINT; 

char* abbr[] = {"Ma", "Ph", "Pl", "En", "De", "Ch", "Bi", "Sw", "Ge", "Ku", "Sp", "Mi"}; 

FILE* ptr;
char* buffer;
long filelength;

int combine_abbr(fach* subjects){

	// combine abbreviations
	for (int j = 0; j < num_sub; j++){

		subjects[j].abbr = abbr[j];
		
	}

	return 0;

}

int print_buffer(char* buffer){

	int i = 0;
	while (buffer[i] != '\0'){
	
		printf("%c", buffer[i]);
		i++;

	}

	printf("\n");
	
	return 0;

}

int take_input(fach* subjects){
	
	fach* current;

	for (int i = 0; i < filelength; i++){
		
		// if '|' then choose the fach that correlates to | +1 & +2
		if (buffer[i] == '|') {

			// create temp to compare to abbreviations
			char* temp;

			temp[0] = buffer[i+1];
			temp[1] = buffer[i+2];

			// compare temp to the abbreviations of every subject
			// if it is the same point current to it
			for (int j = 0; j < num_sub; j++){
				

				if (strcmp(temp, subjects[j].abbr) == 0){
					

					current = &subjects[j];
					printf("same abbr: %s\n", subjects[j].abbr);
					break;
				}
			}		
		}
	}
}


int main(){
	
	// create list of subjetcs
	fach subjects[] = {mathe, physik, philosophie, englisch, deutsch, chemie, biologie, sowi, geschichte, kunst, sport, MINT};
	
	// open file in read mode
	ptr = fopen("noten.txt", "r");

    	if (ptr == NULL) {
      		printf("Unable to open file.\n");
     		return 1;
   	}
	
	// get length of file
     	fseek(ptr, 0, SEEK_END);     // move the file pointer to the end of the file
        filelength = ftell(ptr);     // get the total size of the file
    	rewind(ptr);                 // move the file pointer back to the beginning 
	
	// move content of file into buffer
	buffer = (char*) malloc(filelength + 1);   // allocate memory to hold the file contents
        fread(buffer, filelength, 1, ptr);         // read the entire file into the buffer
        buffer[filelength] = '\0';                 // add a null terminator to the end of the buffer
	
	// combine abbreviations
	combine_abbr(subjects);

	// print document
	print_buffer(buffer);
	
	// temp: print all abbreviations
	for (int i = 0; i < num_sub; i++){
		printf("%s ", subjects[i].abbr);
	}
	printf("\n");
	
	// temp: check for same abbreviations
	take_input(subjects);

	// free buffer
	free(buffer);
	
	// close file
	fclose(ptr);
}

