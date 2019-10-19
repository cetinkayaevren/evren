#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double x_min,x_max=0;

double func1(double in){      	//f(x)=x
	return in;
	}

double func2(double in){	  	//f(x)=-x
	return -in;
	}

double func3(double in){	 	//f(x)=x^2
	return (in*in);
	}
	
double func4(double in){	  	//f(x)=-x^3
	return -(in*in*in);
	}

double func5(double in){  	  	//f(x)= (3*cos(x)-2*sin(4*x)-1)/2
	double y= (3*cos(in)-2*sin(4*in)-1)/2;   //HOCAYA MATH KUTUPHANESINI SOR!!
	return y;
	}
	
void print_menu(){
	printf("1.\tf(x) = x\n");
	printf("2.\tf(x) = -x\n");
	printf("3.\tf(x) = x^2 \n");
	printf("4.\tf(x) = -x^3\n");
	printf("5.\tf(x) = (3*cos(x)-2*sin(4*x)-1)/2\n");
	printf("0.\tExit\n");

	}

void print_function(int selection){  
	switch(selection){
		
		case 1:
		printf("Function to print x\n");
		break;
		
		case 2:
		printf("Function to print -x\n");
		break;

		case 3:
		printf("Function to print x^2\n");
		break;

		case 4:
		printf("Function to print -x^3\n");
		break;

		case 5:
		printf("Function to print (3*cos(x)-2*sin(4*x)-1)/2\n");
		break;

		default:
		printf("Wrong number you entered!!!\n");   //cozmelisin
		break;
			
		}
	}
double print_min(int selection,double start,double end,double range){
	double smallest=11111110;
	double outcome=0;
	for(double i=start;i<end;i+=range){
	//double x_min;
	switch(selection){
		case 1:
		outcome=func1(i);
		break;
		case 2:
		outcome=func2(i);
		break;
		case 3:
		outcome=func3(i);
		break;
		case 4:
		outcome=func4(i);
		break;
		case 5:
		outcome=func5(i);
		break;
		}
		if(outcome<smallest){   //FIND MIN VALUE
			smallest=outcome;
			x_min=i;
		}
	}
	return smallest;
}

double print_max(int selection,double start,double end,double range){
	double largest=-124422120;
	double outcome=0;
	//double x_max;
	int a=0;
	for(double i=start;i<end;i+=range){
	switch(selection){
		case 1:
		outcome=func1(i);
		break;
		
		case 2:
		outcome=func2(i);
		break;
		
		case 3:
		outcome=func3(i);
		break;
		
		case 4:
		outcome=func4(i);
		break;
		
		case 5:
		outcome=func5(i);
		break;
		
		}
		if(outcome>largest){   //FIND MAX VALUE
			largest=outcome;
			x_max=i;
		}
	a++;
	}
	return largest;
	
}


void print_result(double start,double end,double range,int selection){
	int array_range = (end-start)/range;
	int middle = (array_range)/2;
	char my_array[array_range];
	int row=1;	
	double max;
	double min;
	int normal;
	printf("%5s\t%15s\n","x","f(x)");

	for(double i=start;i<end;i+=range){
		double result;
		if(row==middle){
			for(int k=0;k<(array_range);k++){
				my_array[k]='-';
			}
		}
		else{
			for(int k=0;k<(array_range);k++){
				if(i==start){
					if(k==(array_range/2)){
						my_array[k]='^';
					}
					else if(k==(array_range/2)+1){
						my_array[k]='-';
						}
						
					else if(k==(array_range/2)+2){
						my_array[k]='x';
						}
					else{
						my_array[k]=' ';
						}
					}
				
				else{
					if(k==(array_range/2)){
						my_array[k]='|';
					}
					else{
						my_array[k]=' ';
						}
					}
				
			}
		}
		
		if(selection==1){
			result = func1(i);             //f(x)=x
			}
		else if(selection==2){
			result = func2(i);            //f(x)=-x
			}
		else if(selection==3){
			result = func3(i);   		 //f(x)=x^2
			}
		else if(selection==4){
			result = func4(i);			 //f(x)=-x^3
			}
		else if(selection==5){
			result = func5(i);			 //f(x)= (3*cos(x)-2*sin(4*x)-1)/2
		}
		
		
		printf("%+lf\t%+lf ",i,result);
		min = print_min(selection,start,end,range);
		max = print_max(selection,start,end,range);
		if(selection==3){
			for(int k=0;k<(array_range);k++){
				if(row==middle){
					for(int k=0;k<(array_range);k++){
						my_array[k]='-';
					}
				}
				if(i==start){
					if(k==(0)){
						my_array[k]='^';
					}
					else if(k==1){
						my_array[k]='-';
						}
						
					else if(k==2){
						my_array[k]='x';
						}
					else{
						my_array[k]=' ';
						}
					}
				
				else{
					if(k==0){
						my_array[k]='|';
					}
					else{
						my_array[k]=' ';
						}
					}
				}
			}
		normal=((result-min)/(max-min))*array_range;   //VALUE NORMALIZATION
		my_array[normal]='*';
		for(int l=0;l<(array_range);l++){
			printf("%2c",my_array[l]);
			}
		if(row==middle){
			printf("> +y");
		}
		printf("\n");
		row++;
	}

    printf("Min value for f(x)=%lf at x=%lf\nMax value for f(x)=%lf at x=%lf\n",min,x_min,max,x_max);//PRINTING MAX AND MIN VALUES
	return;
}
int main(){
	
	int selection;
	double to ;
	double step;
	double from;
	
	do{
		print_menu();			//PRINTING OPTIONS

		printf("Selection: ");
		scanf("%d",&selection);
		if(selection==0){
			return EXIT_SUCCESS;
			}
		else{
			print_function(selection);		//GOES TO FUNCTIONS
		}
		
		printf("From: ");
		scanf("%lf",&from);

		printf("To: ");
		scanf("%lf",&to);

		printf("Step: ");
		scanf("%lf",&step);

		if(step != 0){
			//print_max_min(from,to,step,selection);
			print_result(from,to,step,selection);			//PRINTING RESULTS AND GRAPH
			printf("..***************************************************..\n");  //SEPERATOR
			}
		else{
			printf("Your step is not valid. Please try again..\n");
			}
	}while(1);
return EXIT_SUCCESS;
}
