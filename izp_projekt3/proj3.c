/**
* IZP treti projekt - Pruchod bludistem
* Autor: Ladislav Dokoupil, <xdokou14@stud.fit.vutbr.cz>
* Datum: 12.12.2019
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<errno.h>

#define LEFT  1
#define RIGHT  2
#define INVALIDB 10
#define ALLBORD 7
#define NOBORD 0
#define HELP "\
How to use:\n ./proj3 [args] [R] [C] [file.txt]\n\
options:\nargs\n--test -> for validing map\n\
--rpath -> solves maze by right hand rule\n\
--lpath -> solves maze by left hand rule\n\
--shortest -> find fastest way from maze rule\n\
R -> starting row\nC -> starting column\nfile.txt -> text file with maze \n"

enum border {left = 1, right = 2, horiz = 4};

typedef struct {
  int rows;//y
  int cols;//x
  unsigned char *cells;
} Map;

//initialize map and writes its cell from file
Map init_map(FILE *fp){
	Map map;
	char buffer[5];
	int x, y, c, h=0;

	fgets(buffer,5,fp);
    sscanf(buffer,"%d %d", &y, &x);
	map.cells = malloc(sizeof(*(map.cells)) * x * y);
	if(map.cells == NULL)
		return map;
	map.rows = y;
	map.cols = x;
	for(int i=0;(c = fgetc(fp)) != EOF;i++){
	    if(h > (map.cols)*(map.rows)){
	   		map.cells[0] = INVALIDB;
	    	break;
	    }
	    if(i%2 == 0){
			map.cells[h] = c-'0';
			h++;
	    }
	}
	if(h != (map.cols)*(map.rows)){
		map.cells[0] = INVALIDB;
	}
	return map;
}
void free_map(Map map){
		free(map.cells);
}
//modified XNOR function
//returns true if 1+ bits are diferent
bool check_border(char b1, char b2, char bit1, char bit2){
	return ~((b1^bit1)^(b2^bit2));
}
bool is_map(Map map){
	char z, r[3];
	for (int i = 0; i < map.rows; i++)
	{
		for (int p = 0;p < map.cols; p++)
		{
			z = map.cells[i*map.cols + p];
			//checks if borders are complete from both directions
			if(p == 0)//TODO try loop ?
				r[0] = (z&1 ? ALLBORD:NOBORD);
			else
				r[0] = map.cells[i*map.cols + p-1];
			if(p == map.cols-1)
				r[1] = (z&2 ? ALLBORD:NOBORD);
			else
				r[1] = map.cells[i*map.cols + p+1];
			//down triangle
			if((i*map.cols + p)%2 == 0){
				if(i == 0){
					r[2] = (z&4 ? ALLBORD:NOBORD);
				}
				else
					r[2] = map.cells[(i-1)*map.cols + p];
			}
			//up triangle
			else{
				if(i == map.rows-1)
					r[2] = (z&4 ? ALLBORD:NOBORD);
				else
					r[2] = map.cells[(i+1)*map.cols + p];
			}
			if(z < 0 || z > 7)
				return false;
			if(!(check_border(z,r[0],1,2) && check_border(z,r[1],2,1)
				&& check_border(z,r[2],4,4))){
				return false;
			}
		}
	}
	return true;
}
//checks if border is in given direction
bool is_border(Map map, int r, int c, int dir){
	return (map.cells[(r-1)*map.cols + (c-1)])&dir;
}
//finds next dir to check clockwise for LEFT and anticlockwise for RIGHT
int next_dir(int dir,int r,int c, int leftright){
	//anticlockwise for right - down triangle || left - up triangle
	if( (c + r + leftright)%2 == 0 ){
		if(dir == 4)
			return 1;
		else
			return dir*2;
	}
	//clockwise for right - up triangle || left - down triangle
	else{
		if(dir == 1)
			return 4;
		else
			return dir/2;	
	}
}
int start_direction(Map map, int r, int c, int leftright){
	int dir = left, i = 0;
	//basic + errors
	if (c == 1)
		dir = left;
	if (c == map.cols)
		dir = right;
	if (r == 1){
		dir = horiz;
		if(((c%2)^(r%2)) == 1)
			return -1;
	}
	if(r == map.rows && r != 1){
		dir = horiz;
		if(((c%2)^(r%2)) == 0)
			return -1;
	}
	if(is_border(map, r, c, dir)){
		if(c == map.cols)
			dir = right;
		if(c == 1)
			dir = left;
	}
	if(is_border(map, r, c, dir))
		return -1;
	do{
		i++;
		dir = next_dir(dir, r, c, leftright);
		if(i > 3)
			return -1;
	}while(is_border(map, r, c, dir));
	return dir;
}
void move(int *r, int *c,int dir){
	if(dir == left)
		*c=*c-1;
	else if(dir == right)
		*c=*c+1;
	else if(dir == horiz){
		if((*c+*r)%2 == 0)
			*r=*r-1;
		else
			*r=*r+1;
	}
}
//dir i came from
int prev_dir(int dir){
	if(dir == left)
		return right;
	else if(dir == right)
		return left;
	else
		return dir;
}
bool is_inside(Map map, int r, int c){
	return r > 0 && r <= map.rows && c > 0 && c <= map.cols;
}
bool is_end(Map map, int r, int c){
	if(!is_inside(map, r, c))
		return true;
	else
		return false;
}
//main maze solving loop
int play(Map map, int r,int c,int leftright){
    int dir = start_direction(map, r, c, leftright);
    if(dir == -1)
    	return dir;

    printf("%d,%d\n", r, c);
    move(&r, &c, dir);

    while(!is_end(map, r, c)){
		dir = prev_dir(dir);
	    dir = next_dir(dir, r, c, leftright);
		while(is_border(map, r, c, dir))
			dir = next_dir(dir, r, c, leftright);
	    printf("%d,%d\n",r,c);
	    move(&r, &c, dir);
    }
    return 0;
}
//arguments and error handling
int main(int argc, char **argv){
	Map map;
	int r, c, leftright;
	errno = 0;

    if(argc > 1){
       if(strcmp(argv[1],"--help") == 0){
           printf(HELP);
           return 0;
       }
       FILE *fp = fopen(argv[argc-1],"r");
       if(fp == NULL){
           fprintf(stderr,"error: file");
           return 1;
       }
       map = init_map(fp);
       if(map.cells == NULL){
       	   fprintf(stderr,"error: init_map");
           return 6;
       }
       fclose(fp);

       if(strcmp(argv[1],"--test") == 0){
           if(is_map(map)){
           		printf("Valid\n");
           		free_map(map);
            	return 0;
           }
           else{
                printf("Invalid\n");
                free_map(map);
            	return 1;
           }
       }
       if(strcmp(argv[1],"--rpath") == 0)
       		leftright = RIGHT;
       else if(strcmp(argv[1],"--lpath") == 0)
       		leftright = LEFT;
       else{
       	fprintf(stderr, "error: args\n");
       	free_map(map);
       	return 4;
       }

       if(argc == 5){
            r = strtod(argv[2],NULL);
            c = strtod(argv[3],NULL);
            if(errno != 0 || !(r == map.rows || r == 1 || c == map.cols || c == 1)){
            	fprintf(stderr, "error: cordinates\n");
            	free_map(map);
            	return 2;
            }
            if(!is_map(map)){
            	fprintf(stderr,"error: map");
            	free_map(map);
            	return 3;
            }
            int end = play(map, r, c, leftright);
            if(end == -1){
            	fprintf(stderr, "error: dir/stuck");
            	return 5;
            }
            free_map(map);
        }
    return 0;
    }
}