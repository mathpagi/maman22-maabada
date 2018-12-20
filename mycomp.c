#include "complex.h"
#include <stdlib.h>
#include <ctype.h>
#include <float.h>


void free_comp(complex ***arr);


/*print the error*/
void err(int err){
	switch(err){
	case text_after:
		printf("\nExtraneous text after end of cammand\n");
		break;
	case undefined_command:
		printf("\nUndefined command name\n");
		break;
	case undefined_var:
		printf("\nUndefined complax variable\n");
		break;
	case not_number:
		printf("\nInvalid parameter - not a number\n");
		break;	
	case miss_param:
		printf("\nMissing parameter\n");
		break;
	case miss_comma:
		printf("\nMissing comma\n");
		break;
	case illegal_comma:
		printf("\nIllegal comma\n");
		break;
	case many_comma:
		printf("\nMultiple consecutive commas\n");
		break;
	case no_input:
		printf("\ninsert cammand please\n");
		break;

	default:;

	}
}

/*executing the right function*/
void exe(function *func, complex **arr){
	int var1 = (int)func->var[0];
	int var2 = (int)func->var[1];
	
	switch(func->fun_type){
	case stp:{
		free_comp(&arr);
		exit(0);
		}
	case print:
		print_comp ( *arr[var1]);
		break;
	case abs_c:
		abs_comp ( *arr[var1]);
		break;
	case add:
		add_comp (*arr[var1], *arr[var2]);
		break;
	case sub:
 		sub_comp ( *arr[var1] , *arr[var2]);
		break;	
	case mult_comp:
 		mult_comp_comp ( *arr[var1] , *arr[var2]);
		break;
	case mult_real:
 		mult_comp_real ( *arr[var1] , func->num[0]);
		break;
	case mult_img :
 		mult_comp_img (*arr[var1] ,  func->num[0]);  
		break;
	case read:
		 read_comp ((arr[var1]) ,  func->num[0],  func->num[1]);
		break;
	default:;
	}
}



/*initializint array of variables with value  of 0*/
void initiate_vars(complex ***arr){
	int i;
	int flag = FALSE;
	
	*arr = (complex**)malloc(NUM_OF_VARS*sizeof(complex*));
	if(*arr == NULL)
		flag = TRUE;
		
	for(i=0; i< NUM_OF_VARS &&(!flag); i++){
		(*arr)[i] = (complex*)malloc(sizeof(complex));
		if((*arr)[i] == NULL)
			flag = TRUE;
		else
		read_comp((*arr)[i],0,0);
		}
	if(flag){
		printf("allocation failed , stack overflow");
		free_comp(arr);
		exit(0);
	}
	return ;

}

void free_comp(complex ***arr){
	int i;
	
	for(i=0; i< NUM_OF_VARS; i++)
		free((*arr)[i]);
	free(*arr);
	return ;
	
}

void clean (char* input){
	int i;
	for (i=0; i < strlen(input) ; i++)
		input[i] = '\0';	
	return;
}



	
int main(){
	char input[MAX_INPUT_SIZE];
	complex **arr; 			/*representing A-F, A=0,...F=5 */
	function func1;
	function *func = &func1;
	
	printf("\nplease insert commands, insert stop to exit\n");
	initiate_vars(&arr);
	while(TRUE){
		fgets(input,MAX_INPUT_SIZE,stdin); 
		parsing(input,&func);
				
		if(func-> err_type)
			err(func-> err_type);
		else
			exe(func, arr);
		clean(input);
	}
	
	return 0;
	
}
