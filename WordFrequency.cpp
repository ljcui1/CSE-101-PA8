//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA8
//
//-----------------------------------------------------------------------------
#include <fstream>
#include <string>
#include <iostream>
#include"Dictionary.h"
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

    int line_count;
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
    
    //string delim = " "; 
    string delim = "\%\t\n\r\\\"\' ,<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789";

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    line_count = 0;
    Dictionary D;
    while( getline(in, line) )  {
        line_count++;
        len = line.length();
        
        

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        
        while( token != "" ){  // we have a token
            // update token buffer
            std::transform(token.begin(), token.end(), token.begin(), ::tolower);

            if(D.contains(token)){
                int x = D.getValue(token) + 1;
                D.setValue(token, x);
            }else{
                D.setValue(token, 1);
            }
            

            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }

    }

    out << D.to_string() << endl;
    out.flush();
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

