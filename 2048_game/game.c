#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 20
#define ROW 4
#define COL 4
#define MAX_CHAR 5
#define MAX_RAND 10000

struct client{
	int account_num;
	char user[MAX_SIZE];
	int row;
	int col;
	int value;
	};

int main(){
	char name[MAX_SIZE];
	char option[MAX_CHAR];
	
	//FILE* load_data;
	
	void option_statement();  //Prototypes...
	void print_help();
	
	printf("Enter your name: ");
	scanf("%s",name);
	printf("\n");
	printf("Welcome %s!\n",name);  //NEW PLAYER OLAYINI BASTIRMALISIN BUNDAN SONRA
	
	printf("Do you need help? ENTER H\n");
	scanf("%c",option);
	

	if(strcmp(option,"Y")==0){
		print_help();
		}
	else if(strcmp(option,"N")==0){
		printf("Okeyy\n");
		}
		
	option_statement(name);
	
	return EXIT_SUCCESS;
	}



void option_statement(char name[]){
	
	void print_help(char name[]);				//Prototypes..
	void new_game(int array[][COL],const int row_num,char name[]);
	//void new_user(FILE* fPtr);
	//void user_info(FILE* fPtr,char name[]); 
	void resume_saved(int account_num,int array[][COL],const int row_num,char name[]);
	void remove_saved(int account_num,int array[][COL],const int row_num,char name[]);
	void start_game(int array[][COL],const int row_num,char name[]);					
	
	int new_array[ROW][COL];
	char request[MAX_CHAR];
	
	srand(time(NULL));
	
	printf("Request?");
	scanf("%s",request);
	
	
	if(strcmp(request,"N")==0){
		new_game(new_array,ROW,name);				
		}
	else if(strcmp(request,"Q")==0){
		printf("Program is terminating..\n");
		return;
		}
	else if(strcmp(request,"P")==0){
		//new_user(load_data);
		}
	else if(strcmp(request,"I")==0){
		//user_info(load_file,name);    //BELKİ ID YARATABİLİRSİN, HOCAYA SOR
		}
	else if(strcmp(request,"H")==0){
		print_help(name);
		}
	else if(strcmp(request,"R1")==0){			
		resume_saved(1,new_array,ROW,name);
		}
	else if(strcmp(request,"R2")==0){
		resume_saved(2,new_array,ROW,name);					//PROBLEM
		}
	else if(strcmp(request,"R3")==0){
		resume_saved(3,new_array,ROW,name);					//PROBLEM
		}
	else if(strcmp(request,"R4")==0){
		resume_saved(4,new_array,ROW,name);					//PROBLEM
		}
	else if(strcmp(request,"R5")==0){
		resume_saved(5,new_array,ROW,name);					//PROBLEM
		}
	else if(strcmp(request,"D")==0){
		remove_saved(1,new_array,ROW,name);					//PROBLEM
		}
	else{
		printf("Wrong character you entered!!\n");
		}
	return;
	}
	
void print_help(char name[]){
	printf("The aim is to get to the 2048 \ntile by merging two consecutive \ntiles in one direction.\n");
	option_statement(name);
	return;
	}

void new_game(int array[][COL],const int row_numb,char name[]){
	
	void print_array(int array[][COL],const int row_num);
	void start_game(int array[][COL],const int row_num,char name[]);					

	int first_num;
	int second_num;
	int rand_col;
	int rand_row;
	
	for(int i=0;i<row_numb;i++){				//FILLING ARRAY WITH ZEROS
		for(int k=0;k<COL;k++){
			array[i][k]=0;
			}
		}

	rand_col= rand()%4;
	rand_row=rand()%4;
	first_num=rand()%100;		//GENERATING RAND NUMBER BETWEEN 0 AND 100
	second_num=rand()%100;
	
	if(first_num>30){			//PROBABILITY OF PERCENT 30 AND 70 !!
		first_num=2;
		}
	else{
		first_num=4;
		}
	if(second_num>30){
		second_num=2;
		}
	else{
		second_num=4;
		}
	array[rand_row][rand_col]=first_num;
	rand_col= rand()%4;							//CREATING ROW AND COL AGAIN
	rand_row=rand()%4;
	array[rand_row][rand_col]=second_num;		
	
	start_game(array,row_numb,name);					//STARTING GAME
	return;
	}
	
void start_game(int array[][COL],const int row_num,char name[]){
	
	int move_right(int array[][COL],const int row_num);  //PROTOTYPING MOVEMENTS
	int move_left(int array[][COL],const int row_num);
	int move_up(int array[][COL],const int row_num);
	int move_down(int array[][COL],const int row_num);
	void put_rand_value(int array[][COL],const int row_num);
	void print_array(int array[][COL],const int row_num);
	void save_game (int account_num,int array[][COL],const int row_num,char name[]);
	void write_best(int total);
	
	char request[MAX_CHAR];
	int total=0;		//ESKI BIR OYUN BASLATIRSAN TOTAL 0 OLMAYACAK !!	ÇOZULDU
	int my_best;

	FILE* best_score;
	
	do{

		best_score=fopen("best.dat","r");
		
		if(best_score==NULL){
			printf("File canoot be found");
			}
		fscanf(best_score,"%d",&my_best);
		printf("Score:%d\n",total);
		printf("Best Score:%d\n",my_best);
		print_array(array,row_num);
		printf("Move?");
		scanf("%s",request);
		
		if(strcmp(request,"U")==0){						//UP
			total+= move_up(array,row_num);
			}																			
		else if(strcmp(request,"D")==0){
			total+= move_down(array,row_num);			//DOWN
			}			
		else if(strcmp(request,"L")==0){				
			total+=move_left(array,row_num);			//LEFT
			}				
		else if(strcmp(request,"R")==0){
			total+=move_right(array,row_num);			//RIGHT
			}
		else if(strcmp(request,"S1")==0){				//SAVING GAME
			save_game(1,array,row_num,name);
			}						
		else if(strcmp(request,"S2")==0){				//SAVING GAME		//PROBLEM
			save_game(2,array,row_num,name);
			}		
		else if(strcmp(request,"S3")==0){				//SAVING GAME		//PROBLEM
			save_game(3,array,row_num,name);
			}		
		else if(strcmp(request,"S4")==0){				//SAVING GAME		//PROBLEM
			save_game(4,array,row_num,name);
			}		
		else if(strcmp(request,"S5")==0){				//SAVING GAME		//PROBLEM
			save_game(5,array,row_num,name);
			}
		else if(strcmp(request,"Q")==0){
			printf("Game is terminating..\n");
			}
		else{
			printf("Wrong character you entered, please try again :)\n");
			}		
		
		if(total>my_best){
			write_best(total);
			}
		fclose(best_score);
		}while(strcmp(request,"U")==0 || strcmp(request,"D")==0 || strcmp(request,"L")==0 || strcmp(request,"R")==0 || strcmp(request,"S1")==0 
		|| strcmp(request,"S2")==0 || strcmp(request,"S3")==0 || strcmp(request,"S4")==0 || strcmp(request,"S5")==0);								

	return;
	}			
	
int move_up(int array[][COL],const int row_num){
	
	void put_rand_value(int array[][COL],const int row_num);
	int r=0;
	int count=0;
	int total=0;
	
	
	for(int col=0;col<COL;col++){							//0 Olan boş arraylaer, sonraki dolu arrayler ile doldur
		for(int row=0;row<row_num;row++){
			if(array[row][col]==0){
				for(int a=row+1;a<ROW;a++){
					if(array[a][col]!=0){
						array[row+r][col]=array[a][col];
						array[a][col]=0;
						r++;
						}
					}
				r=0;
				}
			}
		}
	
	
	for(int i=0;i<COL;i++){													// RAKAMLARI EŞİT OLANLARI SÜTUN SÜTUN BUL(0 HARIÇ)
		for(int j=0;j<row_num-1;j++){											//ONLARI TOPLAYIP UST SUTUNA YAZ
			if(array[j][i]==array[j+1][i] && array[j][i]!=0){
				array[j][i]+=array[j+1][i];
				array[j+1][i]=0;
				total=array[j][i];
				count++;
				}
			}	
		}
	
	for(int col=0;col<COL;col++){							//0 Olan boş indexi, sonraki dolu indexler ile doldur.
		for(int row=0;row<row_num;row++){
			if(array[row][col]==0){
				for(int a=row+1;a<ROW;a++){
					if(array[a][col]!=0){
						array[row+r][col]=array[a][col];
						array[a][col]=0;
						r++;
						}
					}
				r=0;
				}
			}
		}
	
		
	put_rand_value(array,row_num);
	return total;
	}
	

	
int move_down(int array[][COL],const int row_num){
	
	void put_rand_value(int array[][COL],const int row_num);
	int c=0;
	int count=0;
	int total=0;
	
	for(int col=0;col<COL;col++){
		for(int row=row_num-1;row>=0;row--){
			if(array[row][col]==0){
				for(int a=row-1;a>=0;a--){
					if(array[a][col]!=0){
						array[row-c][col]=array[a][col];
						array[a][col]=0;
						c++;
						}
					}
				c=0;
				}
			}
		}

	for(int i=0;i<COL;i++){													// RAKAMLARI EŞİT OLANLARI SÜTUN SÜTUN BUL(0 HARIÇ)
		for(int j=row_num-1;j>=0;j--){											//ONLARI TOPLAYIP UST SUTUNA YAZ
			if(array[j][i]==array[j-1][i] && array[j][i]!=0){
				array[j][i]+=array[j-1][i];
				array[j-1][i]=0;
				total=array[j][i];
				count++;
				}
			}
		}
		
	for(int col=0;col<COL;col++){
		for(int row=row_num-1;row>=0;row--){								//0 Olan boş indexi, sonraki dolu indexler ile doldur.
			if(array[row][col]==0){
				for(int a=row-1;a>=0;a--){
					if(array[a][col]!=0){
						array[row-c][col]=array[a][col];
						array[a][col]=0;
						c++;
						}
					}
				c=0;
				}
			}
		}

	put_rand_value(array,row_num);
	return total;
	}

int move_left(int array[][COL],const int row_num){
	
	void put_rand_value(int array[][COL],const int row_num);
	int r=0;
	int count=0;
	int total=0;

	for(int row=0;row<row_num;row++){
		for(int col=0;col<COL-1;col++){
			if(array[row][col]==0){
				for(int a=col+1;a<COL;a++){
					if(array[row][a]!=0){
						array[row][col+r]=array[row][a];
						array[row][a]=0;
						r++;
						}
					}
				r=0;
				}
			}
		}

	for(int i=0;i<row_num;i++){													// RAKAMLARI EŞİT OLANLARI SÜTUN SÜTUN BUL(0 HARIÇ)
		for(int j=0;j<COL-1;j++){											//ONLARI TOPLAYIP UST SUTUNA YAZ
			if(array[i][j]==array[i][j+1] && array[i][j]!=0){
				array[i][j]+=array[i][j+1];
				array[i][j+1]=0;
				total=array[i][j];
				count++;
				}
			}
		}
			
	for(int row=0;row<row_num;row++){										//0 Olan boş indexi, sonraki dolu indexler ile doldur.
		for(int col=0;col<COL-1;col++){
			if(array[row][col]==0){
				for(int a=col+1;a<COL;a++){
					if(array[row][a]!=0){
						array[row][col+r]=array[row][a];
						array[row][a]=0;
						r++;
						}
					}
				r=0;
				}
			}
		}
		
	put_rand_value(array,row_num);
	return total;
	}

int move_right(int array[][COL],const int row_num){

	void put_rand_value(int array[][COL],const int row_num);
	int c=0;
	int count=0;
	int total=0;
	
	for(int row=0;row<row_num;row++){											//0 Olan boş indexi, sonraki dolu indexler ile doldur.
		for(int col=COL-1;col>=0;col--){
			if(array[row][col]==0){
				for(int a=col-1;a>=0;a--){
					if(array[row][a]!=0){
						array[row][col-c]=array[row][a];
						array[row][a]=0;
						c++;
						}
					}
				c=0;
				}
			}
		}
	
	for(int i=0;i<row_num;i++){													// RAKAMLARI EŞİT OLANLARI SÜTUN SÜTUN BUL(0 HARIÇ)
		for(int j=COL-1;j>=0;j--){											//ONLARI TOPLAYIP UST SUTUNA YAZ
			if(array[i][j]==array[i][j-1] && array[i][j]!=0){
				array[i][j]+=array[i][j-1];
				array[i][j-1]=0;
				total=array[i][j];
				count++;
				}
			}
		}
		
	for(int row=0;row<row_num;row++){
		for(int col=COL-1;col>=0;col--){
			if(array[row][col]==0){
				for(int a=col-1;a>=0;a--){
					if(array[row][a]!=0){
						array[row][col-c]=array[row][a];
						array[row][a]=0;
						c++;
						}
					}
				c=0;
				}
			}
		}

	put_rand_value(array,row_num);
	return total;
	}

void print_array(int array[][COL],const int row_num){		//ARRAYLER EKRANA YAZILIR
	
	for(int row=0;row<row_num;row++){
		for(int col=0;col<COL;col++){
			if(array[row][col]==0){
				printf(" \t");
				}
			else{
				printf("%d\t",array[row][col]);
				}
			}
		printf("\n");
		}
	return;
	}

void put_rand_value(int array[][COL],const int row_num){		//RASTGELE 2 VEYA 4 VERME
	int rand_row;
	int rand_col;
	int numb;
	
	srand(time(NULL));
	numb=1+rand()%100;
	
	if(numb<30){											//YUZDE 30, 4 VERIR
		numb=4;												//YUZDE 70, 2 VERIR
		}
	else{
		numb=2;
		}
	for(int a =0;a<MAX_RAND;a++){
		rand_row=rand()%4;
		rand_col=rand()%4;
		if(array[rand_row][rand_col]==0){
			array[rand_row][rand_col]=numb;
			break;
			}
		}
	return;
	}

void save_game(int account_num,int array[][COL],const int row_num,char name[]){
	FILE* save_data;
	
	struct client Client={0,"",0,0,0};		//BLANK DATA
	
	save_data=fopen("saved_games.dat","rb+");
	if(save_data==NULL){
		printf("File does not exist\n");
		}
	else{	
		
		Client.account_num=account_num;
		strcpy(Client.user,name);
		fseek(save_data,(Client.account_num-1)*sizeof(struct client),SEEK_SET);			//account_num-1 di	//PROBLEM!!
																							//SADECE 1 ARRAY KAYIT YAPIYOR, MULTI ARRAY KAYDEDEMIYOR, SORUN FSEEK TE OLABILIR
		for(int i=0;i<row_num;i++){															//VEYA DOGRU KAYEDIYOR, OYUNU DOSYADAN CEKERKEN SIKINTI YASIYOR..
			for(int k=0;k<COL;k++){
				Client.value=array[i][k];
				Client.row=i;
				Client.col=k;
				fwrite(&Client,sizeof(struct client),1,save_data);
				}
			}
		printf("GAME SAVED\n");
		fclose(save_data);
		option_statement(name);
		}
	return;
	}

void resume_saved(int account_num,int array[][COL],const int row_num,char name[]){
	int count=0;
	
	void start_game(int array[][COL],const int row_num,char name[]);					
	FILE* load_data;
	struct client Client={0,"",0,0,0};
	
	load_data=fopen("saved_games.dat","rb");
	
	if(load_data==NULL){
		printf("File could not be opened\n");
		}
	else{
		fseek(load_data,(account_num-1)*sizeof(struct client),SEEK_SET);		//account_num-1 di
		for(int i=0;i<row_num && !feof(load_data);i++){
			for(int j=0;j<COL;j++){
				fseek(load_data,(account_num-1)*sizeof(struct client),SEEK_CUR);		//account_num-1 di
				fread(&Client,sizeof(struct client),1,load_data);
				if(strcmp(Client.user,name)==0){
					array[Client.row][Client.col]=Client.value;
					}
				else{
					count++;
					}
				}
			}
		if(count==16){
			printf("Game cannot be found..\n");
			printf("Game is terminating...\n");
			return;
			}
		else{
			start_game(array,ROW,name);
			}
		fclose(load_data);
		}
	return;
	}
	
void remove_saved(int account_num,int array[][COL],const int row_num,char name[]){

	FILE* delete_data;
	
	struct client BlankClient={0,"",0,0,0};		//BLANK DATA
	
	delete_data=fopen("saved_games.dat","wb+");
	if(delete_data==NULL){
		printf("File does not exist\n");
		}
	else{	
		
		fseek(delete_data,(account_num-1)*sizeof(struct client),SEEK_SET);
				
		for(int i=0;i<row_num;i++){
			for(int k=0;k<COL;k++){
				fwrite(&BlankClient,sizeof(struct client),1,delete_data);
				}
			}
		printf("GAME DELETED\n");
		fclose(delete_data);
		option_statement(name);
		}
	return;
	}

void write_best(int total){
	FILE* write_best;
	write_best=fopen("best.dat","w+");
	if(write_best==NULL){
		printf("Fİle could not opened");
		}
	else{
		fprintf(write_best,"%d",total);
		}
	fclose(write_best);
	return;
	}
