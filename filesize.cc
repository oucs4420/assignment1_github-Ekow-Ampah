#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// output format to use IDENTICALLY:
//BSH:Saru> ./filesize input.3lines input.1line 
//program: ./filesize
// input.3lines: 3
// input.1line: 1
//
int read_num_of_lines(string filename){
    int number_of_lines = 0;
     string tmp;
    ifstream myfile(filename);
    if(!myfile){  //checks if ifstream file can be opened
        return -1;
    }else{
        while (getline(myfile, tmp)){
        number_of_lines++;
    }
    return number_of_lines;
    }
    
}


int main( int argc, char** argv){
    cout << "program: " << argv[0] << endl;
     
    // just to get you started, this is how to refer to the arguments that were passed
    for (int arg = 1; arg < argc; ++arg){
               
        cout << " " << argv[arg] << ": " << read_num_of_lines(argv[arg]) << endl;//prints out the filename and also calls prints the result of the function read_num_of_lines  
        
    }
      

    exit(0); // this means that the program executed correctly!
}
