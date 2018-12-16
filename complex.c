#include "complex.h"


void read_comp (complex *var, float real, float img){
	var->real = real;
	var->img = img;
	}		
		
	
	
void print_comp (complex var){
	printf("\nthe result is: %g + (%g)i\n", var.real,var.img);
	}




void add_comp (complex var1, complex var2){
	complex res ;
	float real, img;
	
	real = var1.real + var2.real;
	img = var1.img + var2.img;
	
	read_comp(&res , real, img);
	print_comp(res);
	} 
	
	 	
	
	

void sub_comp ( complex var1, complex var2){
	complex res ;
	float real, img;
	
	real = var1.real - var2.real;
	img = var1.img - var2.img;
	
	read_comp(&res , real, img);
	print_comp(res);
	} 
	
	



void mult_comp_real ( complex var, float mul){
	complex res ;
	float real, img;
	
	real = var.real * mul;
	img = var.img * mul;
	
	read_comp(&res , real, img);
	print_comp(res);
	} 
	
	




void mult_comp_img (complex var, float mul){
	complex res ;
	float real, img;
	
	img = var.real * mul;
	real = var.img * (-mul);
	
	read_comp(&res , real, img);
	print_comp(res);
	} 
	
	
	
	
void mult_comp_comp ( complex var1, complex var2){
	complex res ;
	float real, img;
	
	real = var1.real * var2.real - ( var1.img * var2.img); /*ac -bd)*/
	img = var1.real * var2.img + ( var1.img * var2.real);
	
	read_comp(&res , real, img);
	print_comp(res);
	} 
	





void abs_comp ( complex var ){
	float res;
	res = sqrt(pow(var.real, 2) + pow(var.img , 2));
	printf("\nThe absolut value is : %g\n", res);
	}
	
	
	
		
	
	
	
	
	



