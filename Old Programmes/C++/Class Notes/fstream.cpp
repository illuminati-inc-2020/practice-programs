/* 
 * File:   main.cpp
 * Author: rakeshmalik
 *
 * Created on 27 March, 2012, 1:42 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string buf="";
    ifstream in;
    in.open("t.txt");
    if(!in.is_open())
        cerr<<"File read error"<<endl;
    else
    {
        while(true)
        {
            char c=in.get();
            if(in.eof()) break;
            buf+=toupper(c);
            cout<<c;
        }
        in.close();
    }
    ofstream out;
    out.open("t.txt",ios::app);
    if(!out.is_open())
        cerr<<"File write error"<<endl;
    else
    {
        out<<buf;
        out.close();
    }
    return 0;
}