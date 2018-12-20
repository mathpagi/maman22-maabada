#include "complex.h"
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#define EMPTY SCHAR_MIN
#define EMPTY_NUM 1

/*determine what function has  been  inserted*/
int what_func(const char *func, int *num_comp , int* num_args){
	int function = no_function;	
	
	if(!strcmp(func, "print_comp")){
		*num_comp = 1;
		function = print;
		}
	else if(!strcmp(func, "abs_comp")){
		*num_comp = 1;
		function = abs_c;
		}
	else if(!strcmp(func, "add_comp")){
		*num_comp = 2;
		function = add;
		}
	else if(!strcmp(func, "sub_comp")){
		*num_comp = 2;
		function = sub;
		}
	else if(!strcmp(func, "mult_comp_comp")){
		*num_comp = 2;
		function = mult_comp;
		}
	else if(!strcmp(func, "mult_comp_real")){
		*num_comp = 1;
		*num_args = 1;
		function = mult_real;
		}
	else if(!strcmp(func, "mult_comp_img")){
		*num_comp = 1;
		*num_args = 1;
		function = mult_img;
		}
	else if(!strcmp(func, "read_comp")){
		*num_comp = 1;
		*num_args = 2;
		function = read;
		}
	else if(!strcmp(func, "stop"))
		function = stp;
	else if( func[0] == '\0')
		function = EMPTY;	
		
	return function;

}

/*get complex variable, if is empty returns EMPTY*/
char get_var(char * input ){
	char var;
	int i = 0;
		
	while(isspace(input[(i)])){
		if(input[i] == '\n')
			var = EMPTY;
		(i)++;
		}	
		
	if(var!=EMPTY && input[i] == '\0')
		var = ',';	
	else if(isalpha(input[i])){
		var = input[i] -'A';
		(i)++;
	}
	return var ;
}


/*check if the variable is valid ,empty ,or a comma */
int valid_var(char var, function **func , int *err){
	int validity = FALSE;
	
	*err = TRUE;
	if(var>=0 && var<6){
		validity =  TRUE;
		*err = FALSE;
		}
	else
		if (var == ',')
			(*func)->err_type = illegal_comma; /* illegal comma*/
		else if (var == EMPTY)
				(*func)->err_type = miss_param;
			else
			(*func)->err_type = undefined_var; /* undefined variable*/
	
	return validity;
	}


/*check if the string is a valid number, and empty number*/	
int valid_num(const char * str , int * err ,function **func){
	int point = FALSE;
	int is_number = FALSE;
	int i = 0;
	char extra = '\0';
	
	while(isspace(str[i]))
		i++;
	if(str[i] == '-' || str[i] == '+')
		i++;
	while( (str[i] == '.' && !point) || isdigit((int)str[i]) ){
		is_number =TRUE;
		if(str[i] == '.')
			point = TRUE;
		i++;
		}
	extra = str[i];	
	if(!isspace(extra) && extra !='\0'){
		*err = TRUE;
		(*func)->err_type = not_number;
		return FALSE;
		}
	return is_number + EMPTY_NUM;	
}

/*check if number parameter isempty*/
void not_empty (int param , function **func , int *err){
	if (param == EMPTY_NUM){
		(*func)->err_type = miss_param;
		*err = TRUE;
		}
	return;
}
		

/* check  there is extra text after the command*/
int extra_text(int err,const char *str , int num_comma , function ** func ,const char* token){
	int flag = FALSE;
	int i =0;
	
	if(err)
		flag =TRUE;
	if(token && !flag){
		flag = TRUE;
	
		(*func)->err_type = text_after;
		}
			
	if(str && !flag){
		
			if(num_comma != 0 ){
				flag = TRUE;
				(*func)->err_type = illegal_comma; /*illegal comma*/
			}
		
			else{
				while(isspace(str[i]) && str[i] != '\0')
					i++;	
				while(!isspace(str[i]) && str[i] != '\0')
					i++;
				while(isspace(str[i]) && str[i] != '\0')
					i++;	
				if(str[i] != '\0' && str[i] != ' ' ){
					(*func)->err_type =text_after; 			/*extra text*/
					flag =  TRUE;	
				}
			}	
	}
	return flag;
}


	
/*check if between 2 variables there is a exactly 1 comma*/

int check_commas(const char* str , int num_comp, int num_args,function ** func){
	int i = 0;
	int flag = FALSE;
	if(num_args+num_comp != 0){
		while(isspace(str[i]))
			i++;
		if(str[i] =='\0'){
			(*func)->err_type =many_comma;
			flag = TRUE;
			}
	
		else{
			while(!isspace(str[i]) && str[i] !='\0')
				i++;
			while(isspace(str[i]))
				i++;
			if(str[i] !='\0'){
				(*func)->err_type = miss_comma;
				flag =  TRUE;
				i++;
			}
			i++;
			while(isspace(str[i]) && !flag)
				i++;
			if(str[i] == ','){
				flag = TRUE;
				(*func)->err_type = many_comma;
				}
		}
	}	
	return flag;	
			
	}
		
/*check errors for missing parameters*/
	
int check_param(int err  , int left_param ,function ** func){
	int flag = FALSE;
	
	if(err)	
		flag = TRUE;
	else				
		if(left_param != 0){
			flag = TRUE;
			(*func)->err_type = miss_param;	/* missing parameters*/
		}		
		
		
	
	return flag;				
}

		
/*parsing the input after getting the function, number of complex variables and number of numbers.  */

function * parsing_vars(char * input, int index ,int num_comp, int num_args){
	int num_of_commas = num_comp + num_args , i = 0 , err = FALSE; 			 /*expected number of commas +1*/
	char comma[] = ",", *token;
	function func , *pfunc = &func;
	
	if(!num_of_commas) 							/*stop cammand*/
		err = extra_text(err, input, num_of_commas ,&pfunc,NULL);	
	else{
		pfunc->err_buf = token = strtok((input+index),comma);
		while(num_comp && token && !err){
			pfunc->err_buf = token;
			pfunc->var[i] =  get_var(token);
			if(valid_var(pfunc->var[i++] ,&pfunc , &err )){
				num_comp --;
				err = check_commas(token,num_comp,num_args,&pfunc);
				token = strtok(NULL, comma);
				num_of_commas--;
			}	
		}
		i=0;
		while(num_args && token && !err){
			int parameter;
			pfunc->err_buf = token;
			if((parameter = valid_num(token , &err ,&pfunc ))){
				pfunc->num[i++] =  atof(token);
				num_args --;
				err = check_commas(token,num_comp,num_args,&pfunc);	
				token = strtok(NULL, comma);
				num_of_commas--;
			}
			not_empty (parameter ,&pfunc , &err);
		}	
		err = check_param(err, num_comp + num_args ,&pfunc);
		err = extra_text(err, pfunc->err_buf,num_of_commas,&pfunc,token);
	}
	if(!err){
		pfunc-> err_buf = NULL;
		pfunc->err_type = no_error;
		}
	return pfunc;
}

/*parsing the input line by parameters*/
void parsing(char input[], function **func){
	int i = 0, j=0, temp_func_type;
	char function[MAX_FUN_SIZE]={0};
	int num_comp = 0,num_args = 0;
	int comma = FALSE;
	
	while(isspace( input[i]))
		i++;
	while(!isspace(input[i]) && j < MAX_FUN_SIZE){
		if(input[i] == ',')
			comma =TRUE;           /*there is a comma after cammand name*/
		function[j++] = input[i++];
		}		
	switch( temp_func_type = what_func(function, &num_comp, &num_args )){
		case no_function:
				 if(comma)
					(*func)->err_type = illegal_comma;
				 else		
					(*func)->err_type = undefined_command;
				 break;
		case stp:{
				*func = parsing_vars(input, i , num_comp, num_comp);
				if((*func)->err_buf)
					(*func)->err_type = text_after;
				break;
				}
		case EMPTY :
				(*func)->err_type = no_input;
				break; 
		default:
				*func = parsing_vars(input, i , num_comp, num_args);			
	}
	(*func)->fun_type = temp_func_type;
	return;			
}

