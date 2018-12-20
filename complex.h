#include <stdio.h>
#include <math.h>
#include <string.h>
#define NUM_OF_VARS 6
#define MAX_INPUT_SIZE 124
#define MAX_FUN_SIZE 15
#define NOT_VALID -10
#define TRUE 1
#define FALSE 0


typedef struct complex{
	float real;
	float img;
	} complex;
	
	
	
typedef struct func{  /* represents function with optional 2 variables , 2 numbers , and errors*/
	int fun_type;
	char var[2] ;
	float num[2];
	char *err_buf;
	int err_type;
	} function;
 
	 
enum error_type { no_error ,text_after, undefined_command , undefined_var , not_number , miss_param , miss_comma , illegal_comma , many_comma, no_input}; 	
	
enum function_type {stp , print , abs_c , add , sub , mult_comp , mult_real , mult_img, read , no_function};


	
void print_comp ( complex);

void abs_comp ( complex);

void add_comp (complex, complex);

void sub_comp ( complex , complex);

void mult_comp_comp ( complex , complex);

void mult_comp_real ( complex , float);

void mult_comp_img (complex , float);  

void read_comp (complex *, float, float);

void error(int err);

void parsing(char input[], function **func);

function * parsing_vars(char * input, int index ,int num_comp, int num_args);

