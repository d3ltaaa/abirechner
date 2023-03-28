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
int print_info(fach* subjects);
int combine_abbr(fach* subjects);
int update_included_arrays(fach* subjects);
float calculate_block1(fach* subjects);
int return_rightness(fach* subjects);
void print_included(int* arr);
void print_grades(float* arr);

int num_sub = 12;

fach mathe, physik, philosophie, englisch, deutsch, chemie, biologie, sowi, geschichte, kunst, sport, MINT; 

char* abbr[] = {"Ma'\0'", "Ph'\0'", "Pl'\0'", "En'\0'", "De'\0'", "Ch'\0'", "Bi'\0'", "Sw'\0'", "Ge'\0'", "Ku'\0'", "Sp'\0'", "Mi'\0'"}; 

FILE* ptr;
char* buffer;
long filelength;
char abi_subjects[4][3];

int combine_abbr(fach* subjects){

	// combine abbreviations
	for (int j = 0; j < num_sub; j++){

		subjects[j].abbr[0] = abbr[j][0];
		subjects[j].abbr[1] = abbr[j][1];
		
	}

	return 0;

}

int print_info(fach* subjects){
	
	printf("abbr - t - included\n");

	for (int i = 0; i < num_sub; i++){

		printf("'%s' - %c -", subjects[i].abbr, subjects[i].subject_type);

		for (int j = 0; j < 4; j++){

			printf(" %d", subjects[i].included[j]);

		}

		printf("\n");
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

		if (buffer[i] == '/'){

			subjects[current_index].grades[quater_counter] = 0;

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

void print_included(int* arr){

	for (int i = 0; i < 4; i++){

		printf("%d ", arr[i]);
	}
	printf("\n");
}

void print_grades(float* arr){
	
	for (int i = 0; i < 4; i++){

		printf("%f ", arr[i]);
	}
	printf("\n");
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

		
void must_subjects(fach* subjects){

	// every subject of type L M and S needs to be included for every quate
	for (int i = 0; i < num_sub; i++){

		char temp = subjects[i].subject_type;
		
		// if the subject type is L M or S
		if (temp == 'L' || temp == 'S' ||temp == 'M'){
			
			// go through every quater
			for (int j = 0; j < 4; j++){

				// if there is a quater without a 1 than it prints an erro
				if (subjects[i].included[j] == 0){

					printf("Subjects %s needs to be included in quater %d.\n", subjects[i].abbr, j + 1);
				
				}
			}
		} 
	}
}

void four_quater_subjects(fach* subjects){
	
	// IMPORTANT 		    
	char* must_every_subjects[] = { "De\0", "En\0", "Ma\0" }; 
	int l_m_e_sub = 3; 

	// check if the subjects that have to be included in every quater are included
	for (int cycle = 0; cycle < l_m_e_sub; cycle++){
	       	
		
		char temp_subject[3];
	        temp_subject[0] = must_every_subjects[cycle][0];
		temp_subject[1] = must_every_subjects[cycle][1];
		temp_subject[2] = '\0';

		// check if it is an abi subject
		int c = 0;		
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++;
		}
		// in case it is not
		if (c == 0){	
		
			// go through every subject
			for (int i = 0; i < num_sub; i++){
				
				// until temp_subject is found 
				if (strcmp(temp_subject, subjects[i].abbr) == 0){
					
					// go through every quater
					for (int j = 0; j < 4; j++){
					
						// if included of this quater is 0 return an error
						if (subjects[i].included[j] == 0){

							printf("Subjects %s needs to be included in quater %d.\n", subjects[i].abbr, j + 1);
						}
					}
				}
			}
		}		
	}	

}

void two_quater_subjects(fach* subjects){

	// IMPORTANT
	char* must_half_subjects[] = {"Ku\0", "Ge\0", "Sw\0", "Pl\0"};
	int l_m_h_sub = 4;
	// check if the subjects that have to be included in at least two quaters are included
	for (int cycle = 0; cycle < l_m_h_sub; cycle++){

		char temp_subject[3];
	        temp_subject[0] = must_half_subjects[cycle][0];
		temp_subject[1] = must_half_subjects[cycle][1];
		temp_subject[2] = '\0';

		// a variable to keep track of the included quaters for every subject
		int quater_c = 0;

		
		// check if it is an abi subject	
		int c = 0;
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++;
		}	

		// in case it is not
		if (c == 0){

			// go through every subject
			for (int i = 0; i < num_sub; i++){

				// until temp_subject is found
				if (strcmp(temp_subject, subjects[i].abbr) == 0){

										
					// go through every quater
					for (int j = 0; j < 4; j++){

						// count the included with quater_c
						if (subjects[i].included[j] == 1){

							quater_c++;
						}
					}
				}
			}
			// if there is less than two included
			if (quater_c < 2){
			
				printf("Subjects %s needs to be included more often (included = %d; supposed >= 2)\n", temp_subject, quater_c);
			}
		}
		
	}
}

void social_subjects(fach* subjects){

	// IMPORTANT
	char* social_subjects[] = {"Pl\0", "Ge\0", "Sw\0"};
        int l_s_sub = 3;

	// variable to keep track if one subject fulfills requirements	
	int ok_social = 0;	
	// there needs to be at least one social subject that is included for 4 quaters
	// that means either one of them is in the abi_subjects
	// or one of them is included 4 times
	for (int cycle = 0; cycle < l_s_sub; cycle++){

		char temp_subject[3];
	        temp_subject[0] = social_subjects[cycle][0];
		temp_subject[1] = social_subjects[cycle][1];
		temp_subject[2] = '\0';

		// a variable to keep track of the included quaters for every subject
		int quater_c = 0;

		// check if it is an abi subject because it would be included 4 times automatically
		int c = 0;
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++, ok_social = 1;
		}	

		// in case it is not
		if (c == 0){

			// go through every subject
			for (int i = 0; i < num_sub; i++){

				// until temp_subject is found
				if (strcmp(temp_subject, subjects[i].abbr) == 0){

					// go through every quater
					for (int j = 0; j < 4; j++){

						// count the included with quater_c
						if (subjects[i].included[j] == 1){

							quater_c++;
						}
					}
				}
			}
			// break if quater_c is 4 because it is a minimum of 1 subject that needs to be 4 times included
			if (quater_c == 4) ok_social = 1; break;
		}	
	}

	if (ok_social == 0){

		printf("One of these subjects ");

		for (int i = 0; i < l_s_sub; i++){

			printf("%s ", social_subjects[i]);

		}

		printf("needs to be included 4 times.\n");

	}
}

void science_subjects(fach* subjects){

	// IMPORTANT
	char* science_subjects[] = {"Ph\0", "Ch\0", "Bi\0"};
        int l_c_sub = 3;

	// variable to keep track if one subject fulfills requirements	
	int ok_science = 0;	
	// there needs to be at least one science subject that is included for 4 quaters
	// that means either one of them is in the abi_subjects
	// or one of them is included 4 times
	for (int cycle = 0; cycle < l_c_sub; cycle++){

		char temp_subject[3];
	        temp_subject[0] = science_subjects[cycle][0];
		temp_subject[1] = science_subjects[cycle][1];
		temp_subject[2] = '\0';

		// a variable to keep track of the included quaters for every subject
		int quater_c = 0;

		// check if it is an abi subject because it would be included 4 times automatically
		int c = 0;
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++, ok_science = 1;
		}	

		// in case it is not
		if (c == 0){

			// go through every subject
			for (int i = 0; i < num_sub; i++){

				// until temp_subject is found
				if (strcmp(temp_subject, subjects[i].abbr) == 0){

					// go through every quater
					for (int j = 0; j < 4; j++){

						// count the included with quater_c
						if (subjects[i].included[j] == 1){

							quater_c++;
						}
					}
				}
			}
			// break if quater_c is 4 because it is a minimum of 1 subject that needs to be 4 times included
			if (quater_c == 4) ok_science = 1; break;
		}	
	}

	if (ok_science == 0){

		printf("One of these subjects ");

		for (int i = 0; i < l_c_sub; i++){

			printf("%s ", science_subjects[i]);

		}

		printf("needs to be included 4 times.\n");

	}
}



int return_r(fach* subjects){
	
	// create an abi-subject array
	int abi_subject_counter = 0;

	// go through every subject and search for abbr of type 'L' 'S' or 'M'
	for (int i = 0; i < num_sub; i++){

		char temp = subjects[i].subject_type;

		if (temp == 'L' || temp == 'S' ||temp == 'M'){

			// update abi_subjects with the help of abi_subject_counter
			abi_subjects[abi_subject_counter][0] = subjects[i].abbr[0];
			abi_subjects[abi_subject_counter][1] = subjects[i].abbr[1]; 
			abi_subjects[abi_subject_counter][2] = '\0';
			
			abi_subject_counter++;
		}
	}


		
	// does every abi-subject have 4 included quaters?
	must_subjects(subjects);

	// if not in the abi-subjects, are these 4-quater-Subjects included (De, En, Ma, Sp)
	four_quater_subjects(subjects);	

	// if not in the abi-subjects, are these 2-quater-Subjects included (Ku, Ge, Sw)
	two_quater_subjects(subjects);	

	// if not in the abi-subjects, is one social study included 4 times (out of Pl, Ge, Sw)
	social_subjects(subjects);

	// if not in the abi-subjects, is one science study included 4 times (out of Ph, Ch, Bi)
	science_subjects(subjects);

	// if not in the abi-subjects, is one religion study included 2 times (out of Pl, Kt, Ef)
	
	// is the SCHWERPUNKTFACH included 2 in the second year
	
	// is every included more or equal to 35 (and if P is included 36)





}
int return_rightness(fach* subjects){

	char abi_subjects[4][3];

	int abi_subject_counter = 0;

	// every subject of type L M and S needs to be included for every quate
	for (int i = 0; i < num_sub; i++){

		char temp = subjects[i].subject_type;
		
		// if the subject type is L M or S
		if (temp == 'L' || temp == 'S' ||temp == 'M'){
			
			// update abi_subjects with the help of abi_subject_counter
			abi_subjects[abi_subject_counter][0] = subjects[i].abbr[0];
			abi_subjects[abi_subject_counter][1] = subjects[i].abbr[1]; 
			abi_subjects[abi_subject_counter][2] = '\0';
			
			abi_subject_counter++;

			// go through every quater
			for (int j = 0; j < 4; j++){

				// if there is a quater without a 1 than it prints an erro
				if (subjects[i].included[j] == 0){

					printf("Subjects %s needs to be included in quater %d.\n", subjects[i].abbr, j + 1);
				
				}
			}
		} 
	} 
	// IMPORTANT 		    
	char* must_every_subjects[] = { "De\0", "En\0", "Ma\0" }; 
	int l_m_e_sub = 3; 

	// check if the subjects that have to be included in every quater are included
	for (int cycle = 0; cycle < l_m_e_sub; cycle++){
	       	
		
		char temp_subject[3];
	        temp_subject[0] = must_every_subjects[cycle][0];
		temp_subject[1] = must_every_subjects[cycle][1];
		temp_subject[2] = '\0';

		// check if it is an abi subject
		int c = 0;		
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++;
		}
		// in case it is not
		if (c == 0){	
		
			// go through every subject
			for (int i = 0; i < num_sub; i++){
				
				// until temp_subject is found 
				if (strcmp(temp_subject, subjects[i].abbr) == 0){
					
					// go through every quater
					for (int j = 0; j < 4; j++){
					
						// if included of this quater is 0 return an error
						if (subjects[i].included[j] == 0){

							printf("Subjects %s needs to be included in quater %d.\n", subjects[i].abbr, j + 1);
						}
					}
				}
			}
		}		
	}
	// IMPORTANT
	char* must_half_subjects[] = {"Ku\0", "Ge\0", "Sw\0", "Pl\0"};
	int l_m_h_sub = 4;
	// check if the subjects that have to be included in at least two quaters are included
	for (int cycle = 0; cycle < l_m_h_sub; cycle++){

		char temp_subject[3];
	        temp_subject[0] = must_half_subjects[cycle][0];
		temp_subject[1] = must_half_subjects[cycle][1];
		temp_subject[2] = '\0';

		// a variable to keep track of the included quaters for every subject
		int quater_c = 0;

		
		// check if it is an abi subject	
		int c = 0;
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++;
		}	

		// in case it is not
		if (c == 0){

			// go through every subject
			for (int i = 0; i < num_sub; i++){

				// until temp_subject is found
				if (strcmp(temp_subject, subjects[i].abbr) == 0){

										
					// go through every quater
					for (int j = 0; j < 4; j++){

						// count the included with quater_c
						if (subjects[i].included[j] == 1){

							quater_c++;
						}
					}
				}
			}
			// if there is less than two included
			if (quater_c < 2){
			
				printf("Subjects %s needs to be included more often (included = %d; supposed >= 2)\n", temp_subject, quater_c);
			}
		}
		
	}

	// IMPORTANT
	char* social_subjects[] = {"Pl\0", "Ge\0", "Sw\0"};
        int l_s_sub = 3;

	// variable to keep track if one subject fulfills requirements	
	int ok_social = 0;	
	// there needs to be at least one social subject that is included for 4 quaters
	// that means either one of them is in the abi_subjects
	// or one of them is included 4 times
	for (int cycle = 0; cycle < l_s_sub; cycle++){

		char temp_subject[3];
	        temp_subject[0] = social_subjects[cycle][0];
		temp_subject[1] = social_subjects[cycle][1];
		temp_subject[2] = '\0';

		// a variable to keep track of the included quaters for every subject
		int quater_c = 0;

		// check if it is an abi subject because it would be included 4 times automatically
		int c = 0;
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++, ok_social = 1;
		}	

		// in case it is not
		if (c == 0){

			// go through every subject
			for (int i = 0; i < num_sub; i++){

				// until temp_subject is found
				if (strcmp(temp_subject, subjects[i].abbr) == 0){

					// go through every quater
					for (int j = 0; j < 4; j++){

						// count the included with quater_c
						if (subjects[i].included[j] == 1){

							quater_c++;
						}
					}
				}
			}
			// break if quater_c is 4 because it is a minimum of 1 subject that needs to be 4 times included
			if (quater_c == 4) ok_social = 1; break;
		}	
	}

	if (ok_social == 0){

		printf("One of these subjects ");

		for (int i = 0; i < l_s_sub; i++){

			printf("%s ", social_subjects[i]);

		}

		printf("needs to be included 4 times.\n");

	}

	// IMPORTANT
	char* science_subjects[] = {"Ph\0", "Ch\0", "Bi\0"};
        int l_c_sub = 3;

	// variable to keep track if one subject fulfills requirements	
	int ok_science = 0;	
	// there needs to be at least one science subject that is included for 4 quaters
	// that means either one of them is in the abi_subjects
	// or one of them is included 4 times
	for (int cycle = 0; cycle < l_c_sub; cycle++){

		char temp_subject[3];
	        temp_subject[0] = science_subjects[cycle][0];
		temp_subject[1] = science_subjects[cycle][1];
		temp_subject[2] = '\0';

		// a variable to keep track of the included quaters for every subject
		int quater_c = 0;

		// check if it is an abi subject because it would be included 4 times automatically
		int c = 0;
		for (int i = 0; i < 4; i++){
		
			if (strcmp(temp_subject, abi_subjects[i]) == 0) c++, ok_science = 1;
		}	

		// in case it is not
		if (c == 0){

			// go through every subject
			for (int i = 0; i < num_sub; i++){

				// until temp_subject is found
				if (strcmp(temp_subject, subjects[i].abbr) == 0){

					// go through every quater
					for (int j = 0; j < 4; j++){

						// count the included with quater_c
						if (subjects[i].included[j] == 1){

							quater_c++;
						}
					}
				}
			}
			// break if quater_c is 4 because it is a minimum of 1 subject that needs to be 4 times included
			if (quater_c == 4) ok_science = 1; break;
		}	
	}

	if (ok_science == 0){

		printf("One of these subjects ");

		for (int i = 0; i < l_s_sub; i++){

			printf("%s ", science_subjects[i]);

		}

		printf("needs to be included 4 times.\n");

	}

	return 0;
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

	// take input and update included arrays
	take_input(subjects);
	update_included_arrays(subjects);
	
	// print info
	print_info(subjects);

	// return if everything is right or something needs to be included
	return_rightness(subjects);
	
	// free buffer
	free(buffer);
	
	// close file
	fclose(ptr);
}

