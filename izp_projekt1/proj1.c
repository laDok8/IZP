/**
* IZP prvni projekt
* Autor: Ladislav Dokoupil, <xdokou14@stud.fit.vutbr.cz>
* Datum: 01.11.2019
*/ 


#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXLEN 300
#define NAMELEN 101
#define NUMLEN 14
#define EOSC 1 //reserving char for eos

bool interuptedSearch(char str[],char combination[]){
	int len1 = strlen(str);
	int len2 = strlen(combination);
	int p = 0;
	for (int i = 0; i < len1; i++)
	{
		if(str[i] == combination[p]){
			p++;
		}
	}
	return p == len2;

}

int numCombinations(char argv[]){
		int c = strlen(argv);
		bool works = true;
		int d = 1;

		//number of combinations + works
		for (int i = 0; i < c; i++)	{

			if(argv[i] >= '0' && argv[i] <= '9' ){
				if( argv[i] == '7' || argv[i] == '9'){
					d*=5;
				}
				else if(argv[i] == '0'){
					d*=2;
				}
				else if(argv[i] == '1'){
					//d*=1 not neccesary
				}
				else{
					d *= 4;
				}
			}
			else{
				works = false;
			}
		}

	if(works){
		return d;
	}
	else{
		return -1;
	}
}

void combinate(int x, int len, char out[][len], char in[]){

	char ascii[] = {'+', '+'+1, 'a', 'd', 'g', 'j', 'm', 'p', 't', 'w', 'w'+4};
	int write[len];
	int jump=len;
	int po;
	int curCh;
	int nextCh;
	int writeNum[len];

	len -= EOSC;

	//nulovani
	for(int i = 0; i < len; i++){
		write[i] = 0;
		writeNum[i] = -1;
	}

	//pocet moznosti
	for (int i = 0; i < x; i++){

		//write by index
		for(int p = 0; p < len ; p++){

			po = in[p] - '0';
			curCh = (int)ascii[po];
			nextCh = (int)ascii[po+1];

			out[i][p]=curCh + write[p];

			//@overide 1
			if(po == 1){
				out[i][p] = '1';
			}

			//@overide to add numbers
			if(writeNum[p] != -1){
				out[i][p] = in[p];
			}
			//write EOS
			if(p == len-1){
				out[i][len]='\0';
			}
		}

		//changing write variables for each index
		for (int r = len - EOSC; r >= 0; r--)
		{
			po = in[r] - '0';
			curCh = (int)ascii[po];
			nextCh = (int)ascii[po+1];

			//incerment at last possible index
			//if imposible set jump to this index
			if(curCh + write[r] < nextCh - 1 && po != 1){

					write[r]++;
					break;
			}
			else{
				if(writeNum[r] == -1 && po != 1){
					writeNum[r] = 1;
					break;
				}
				else{
					jump = r;
				}
			}
		}
		//reseting write from jump var to the end of array
		for (int r = jump; r < len; r++)
		{
			write[r] = 0;
			writeNum[r] = -1;
			jump = len;
		}


	}
}

bool searchName(int x, char combinations[][x], char name[], int combi){
	//lowerCase name
	char str[NAMELEN];
	int length = strlen(name);
	bool vysl = false;

	//preempty
	strcpy(str,"");

	for(int i = 0; i < length; i++){
  		str[i] = tolower(name[i]);
	}

		for (int p = 0; p < combi; p++)
		{
			if(interuptedSearch(str, combinations[p]))
			{
				vysl = true;
			}

		}

	return vysl;
}

bool searchNum(char number[], char str[]){
		return interuptedSearch(number,str);
}

int main(int argc , char* argv[])
{
	int pocetVysl = 0;
	int combi = 1;
	int vstup = 1;
	bool vysl[3];
	char name[MAXLEN];
	char number[MAXLEN];
	int isEOF[2];

	//preempty
	strcpy(name,"");
	strcpy(number,"");

	//getting combinations from input if exists
	if(argc >= 2){
			combi = numCombinations(argv[1]);
			vstup = strlen(argv[1]) + EOSC; 
	}
	char combinations[combi][vstup];

	if(argc >= 2 && combi != -1){
		combinate( combi, vstup, combinations, argv[1]);
	}
	if(combi == -1){
		fprintf(stderr, "Input error\n" );
		return EXIT_FAILURE;
	}
	//scan and logic
	do{
		isEOF[0] = scanf("%[^\n]%*c", name);
		isEOF[1] = scanf("%[^\n]%*c",number);
		if(strlen(name) > NAMELEN - EOSC || strlen(number) > NUMLEN - EOSC){
			fprintf(stderr, "Long name error \n");
			return EXIT_FAILURE;
		}
		if(isEOF[0] != isEOF[1]){
			fprintf(stderr, "Odd line error \n");
			return EXIT_FAILURE;
		}
		if(isEOF[1] == EOF || isEOF[1] == 0){
			break;
		}

		if(argc >= 2){
			vysl[0]=false;
			if(combi != -1){
				vysl[0] = searchName(vstup, combinations, name, combi);
			}
			vysl[1] = searchNum(number, argv[1]);
			if(argv[1][0] == '0'){
				argv[1][0] = '+';
				vysl[2] = searchNum(number, argv[1]);
				argv[1][0] = '0';
			}
			if(vysl[2] && argv[1][0] == '0'){
				printf("%s, %s \n", name, number);
				pocetVysl++;
			}
			else if(vysl[0] || vysl[1]){
				printf("%s, %s \n", name, number);
				pocetVysl++;
			}
		}
		else{
			printf("%s, %s \n", name, number);
			pocetVysl++;
		}
	}while(true);//infinite
	if(pocetVysl == 0){
		printf("Not found\n");
	}

	return 0;
}
