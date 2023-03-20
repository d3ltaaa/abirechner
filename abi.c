#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct fach
{
	char abbr[3];
	char subject_type;
	float grades[4];
	float abi;
	int included[4];
}fach;


// header files
int print_buffer(char* buffer);
int combine_abbr(fach* subjects);
int update_included_arrays(fach* subjects);
float calculate_block1(fach* subjects);

int num_sub = 12;

fach mathe, physik, philosophie, englisch, deutsch, chemie, biologie, sowi, geschichte, kunst, sport, MINT; 

char* abbr[] = {"Ma'\0'", "Ph'\0'", "Pl'\0'", "En'\0'", "De'\0'", "Ch'\0'", "Bi'\0'", "Sw'\0'", "Ge'\0'", "Ku'\0'", "Sp'\0'", "Mi'\0'"}; 

FILE* ptr;
char* buffer;
long filelength;

int combine_abbr(fach* subjects){

	// combine abbreviations
	for (int j = 0; j < num_sub; j++){

		subjects[j].abbr[0] = abbr[j][0];
		subjects[j].abbr[1] = abbr[j][1];
		
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
	
	
	for (int i = 0; i < filelength; i++){
		
		int current_index;
		int quater_counter;

		// if '|' then choose the fach that correlates to | +1 & +2
		if (buffer[i] == '|') {
			
			current_index = 0;
			quater_counter = 0;

			// create temp to compare to abbreviations
			char temp[3];

			temp[0] = buffer[i+1];
			temp[1] = buffer[i+2];
			temp[2] = '\0';


			// compare temp to the abbreviations of every subject
			// if they are the same update current_index
			for (int j = 0; j < num_sub; j++){
				
				if (strcmp(temp, subjects[j].abbr) == 0){
					
					current_index = j;
					break;
				}
			}
			// update i +3 because then the next character in focus is not the second 
			// character of the abbreviation
			i += 3;
		}	
		
		if (buffer[i] == '-'){
			
			// create temp to update the subject_type variable
			
			subjects[current_index].subject_type = buffer[i+1];
			
			// update i +2 because then the subject_type character gets skipped
			i += 2;
		}

		if (buffer[i] == '.'){

			// read the next two characters as a string
			char temp[2];
			temp[0] = buffer[i + 1];
			temp[1] = buffer[i + 2];	
			temp[2] = '\0';
			
			subjects[current_index].grades[quater_counter] = atof(temp);

			//quater counter needs to be updated to keep track of the quater for passing in grades
			quater_counter++;
			
			i += 3;
		}
		
		if (buffer[i] == ':'){
			
			// read the next two characters as a string
			char temp1[3];
			temp1[0] = buffer[i + 1];
			temp1[1] = buffer[i + 2];	
			temp1[2] = '\0';
			
			subjects[current_index].abi =  atof(temp1);

			i += 3;

		}
	}

	return 0;
}


int update_included_arrays(fach* subjects){

	// go through every subject
	for (int i = 0; i < num_sub; i++){
		
		// go through every quater
		for (int j = 0; j < 4; j++){
			
			// check if grades[i] != 0 because then the course was not elected
			if (subjects[i].grades[j] != 0){

				// update the corresponding included index
				subjects[i].included[j] = 1;
			}
			else{
				
				subjects[i].included[j] = 0;
			
			}
		}
	}
	return 0;
}
	

float calculate_block1(fach* subjects){

	// points
	float points = 0.0;

	// go through every subject
	for (int i = 0; i < num_sub; i++){
		
		// go through every quater
		for (int j = 0; j < 4; j++){

			// if the corresponding included is 1 than count that grade
			if (subjects[i].included[j] == 1){
				

				// if the subject is of type L count the grade twice
				if (subjects[i].subject_type == 'L'){
					
					points += 2 * subjects[i].grades[j];

				}
				// else count the grade once
				else{
					points += subjects[i].grades[j];
				}
			}
		}
	}
	return points;
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
	update_included_arrays(subjects);
	
	// temp: check all abis
	for (int i = 0; i < num_sub; i++){
		printf("Note[%s]: %f ", subjects[i].abbr, subjects[i].abi);
		printf("Type: %c ", subjects[i].subject_type);
		printf("[%f, %f, %f, %f]  ", subjects[i].grades[0], subjects[i].grades[1], subjects[i].grades[2], subjects[i].grades[3]);
		printf("[%d, %d, %d, %d]\n", subjects[i].included[0], subjects[i].included[1],subjects[i].included[2],subjects[i].included[3]);
	}
	printf("sum of block1: %f\n", calculate_block1(subjects));
	
	// free buffer
	free(buffer);
	
	// close file
	fclose(ptr);
}

