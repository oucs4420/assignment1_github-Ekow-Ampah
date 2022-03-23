/*************************************************************
 *
 * uniq - Uniq
 *   simple text formatting using only system calls
 *
 * WHO ARE YOU AND WHEN DID YOU 
 THIS???
 *
 ************************************************************/

/* include all of the header files that the manual pages say I need */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;

/* global variables */
static int debug = 0;
char *progname;
int fd; /* file descriptor for the file to format */

/*************************************************************
 **
 ** ReadChar: read the char at position pos
 **    returns EOF on end of file
 **
 ** I strongly recommend that you make use of this routine
 **
 *************************************************************/
int
ReadChar(
    unsigned pos)
{
if (debug) fprintf(stdout,"Here in ReadChar\n");
 
	int ch,ck1,ck2;
	ck1 = lseek(fd,pos,SEEK_SET);
	if (ck1 == -1){
		perror("Lseek");
	}
	else{
		ck2 = read(fd,&ch,1);
		//cout << ck2 << endl;
		if (ck2 == 0){ 
		//close(fd);
		return 0;
		}
		if (ck2 == -1){
		perror("Read");
		exit(1);
		}
		else{
			return ch;
		}	

	}
	
	return ch;
	

}

/*************************************************************
 **
 ** PrintLine: print the line starting at index pos
 **
 ** I strongly recommend that you make use of this routine
 **
 *************************************************************/
void
PrintLine(unsigned pos)
{
	char ch;
	int ck1;
	
	ch = ReadChar(pos);
	
	pos++;
	while(1){
	if (ch == 0){
	
	}
	ck1 = write(1,&ch,1);
	if (ch == '\n') break;
	if (ck1 == -1){
		perror("./uniq");
		exit(2);

	}
	if (ck1 == 0) break;
	else{
			if (debug) fprintf(stdout,"Character has been printed\n");}
	
	
	ch = ReadChar(pos);
	pos++;
	}
	
	
	

    return;  // not finished
}

/*************************************************************
 **
 ** NextLineIx: what is the index of the beginning of the next line?
 **
 ** I strongly recommend that you make use of this routine
 **
 *************************************************************/
int
NextLineIx(
    unsigned pos)
{
	
	char ch;
	ch = ReadChar(pos);
	
	pos++;
	while(1){
	if (ch == '\n'|| ch == 0) break;
	
	else{
			if (debug) fprintf(stdout,"Character has been printed\n");}
	//cout << "In here" << endl;
	//cout << pos << endl;
	ch = ReadChar(pos);
	
	pos++;
	}


	return pos;
}
/*************************************************************
 **
 ** SameLine: are two lines the same??
 **
 ** I strongly recommend that you make use of this routine
 **
 *************************************************************/
int
SameLine(
    unsigned pos1,
    unsigned pos2)
{
	//cout << "Here in Same line" << endl;
	int org1 = pos1;
	int org2 = pos2;
	char ch1, ch2;
	ch1 = ReadChar(pos1);
	if (ch1 == 0) {
		//cout << pos1 << endl;cout << "Returned 2" << endl;
		PrintLine(org1);
		close(fd);
		exit(7);

	}
	pos1++;
	//PrintLine(pos1);
	ch2 = ReadChar(pos2);
	pos2++;
	if (ch2 == 0) {
		//cout << pos1 << end;
		PrintLine(org1);
		close(fd);
		exit(7);

	}
	//cout << "here" << endl;
	
	while(1){
	//cout << "Rught here" << endl;
	if(ch1 == ch2){
		ch1 = ReadChar(pos1);
		pos1++;
		ch2 = ReadChar(pos2);
//cout << ch2 << endl;
		pos2++;
if (ch1 == '\n' && ch2 == '\n') break;
	}
	
	
	else{
	

		PrintLine(org1);
	//cout << "Returned 1" << endl;
		return org2;
	
	
	

	}
		
	//cout << ch2 << endl;
}
if (debug) fprintf(stdout,"before print\n");
//cout << "cout" << endl;
	
	return org2;

    
}


/*************************************************************
 **
 ** Main program, usage "uniq file"
 **
 *************************************************************/
int main(
    int argc,
    char *argv[])
{
    int i; 
    int pos1;
    int pos2;
                    /* arg counter */
    progname = argv[0];
	
    for (i = 1; i < argc; ++i) { 
        if (strcmp(argv[i],"-d") == 0) {
                    ++debug;
	}
	
        } 
 
	
    	if (debug) fprintf(stdout,"Debugging enabled\n");
	
	
	//PrintLine(pos1);
		//pos1 = NextLineIx(pos1);
		//pos2 = NextLineIx(pos2);
	//}
	fd = open(argv[1],O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        exit(1);
    } else{
		pos1 = 0;
		pos2 = NextLineIx(pos1);	
		
		//cout << pos2 << endl;
		while(1){
		if(ReadChar(pos1) == 0){
		//cout << "pos1" << endl;
			exit(9);
		}
		if(ReadChar(pos2) == 0){
		//cout << "this one" << endl;
		PrintLine(pos1);
		close(fd);
			exit(9);
		}
		
		 //cout << "Before same line" << endl;
		 i = SameLine(pos1,pos2);
		 pos1 = i;
		if(ReadChar(i) == 0){
		//cout << "Came here" << endl;
	exit(4);}	
		 pos2 = NextLineIx(pos1);
		//cout << pos2 << endl;
		
		if (debug) fprintf(stdout,"About to print\n");
		if(ReadChar(pos1) == 0){
		PrintLine(pos1);
			exit(9);
		}
		
	}	
	}
	
    return(0); // everything worked 

  

}
