#include<iostream>
#include<msgpack.hpp>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;


int main()
{
    //read file//read file//read file//read file//read file//read file//read file//read file
    fstream inf;
    fstream outf;

    inf.open("input.txt", ios::in | ios::binary );
    outf.open("output.txt" , ios::out | ios :: binary) ;

    //initialize
    char * buf = NULL ;
    int bufsize =0 ;
    int n = 0 ;
    vector<int> arr ;
    //read msgpack declaration
    size_t off = 0 ;

    msgpack::object_handle oh ;
    //read file data
    inf.seekg(0 , ios::end) ;
    bufsize = inf.tellg() ;
    inf.seekg(0) ;
    buf = new char[bufsize] ;
    inf.read(buf , bufsize) ;

    //write msgpack declaration
    msgpack::sbuffer sbuf ;

    //get number from input
    oh = msgpack::unpack(buf , bufsize ,off) ;
    oh.get().convert(n) ;

    while(n)
    {
        oh = msgpack::unpack(buf , bufsize , off) ;
        oh.get().convert(arr) ;
        sort(arr.begin() , arr.end() , less<int>() ) ;
        msgpack::pack(sbuf , arr ) ;
        arr.clear() ;
        n--;
    }

    //write pack data to output file
    outf.write(sbuf.data() , sbuf.size()  ) ;

    delete [] buf ;
    inf.close() ;
    outf.close() ;


    return 0;
}







