#include<iostream>
#include<msgpack.hpp>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<string>
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
    bool first = true ;
    vector<string> arr , new_arr;
    istringstream iss;

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


    oh = msgpack::unpack(buf , bufsize ,off) ;
    oh.get().convert(arr) ;

    iss.str(arr[0]) ;
    iss >> n ;       //get number from input
    iss.str("") ;
    iss.clear();
    int i = 1;

    while(i<=n)
    {
        int x = 0 , y = 0;
        string name ;
        string phone ;
        string query ;
        stringstream out ;
        pair<string , string> contact ;
        vector <pair<string , string> > many_contact  ;

        iss.str(arr[2*i-1]) ;
        iss >> x ;    //read the contacts' numbers
        //read every line of data
        for (int j = 0 ;j < x ;j ++)
        {
            iss >> name >> phone ;
            contact = make_pair( phone , name );
            many_contact.push_back(contact);
        }
        sort(many_contact.begin(), many_contact.end()) ;
        iss.str("");
        iss.clear();

        //start to read query
        iss.str(arr[2*i]);
        iss >> y ;

        for (int j = 0 ; j < y ; j ++)
        {
            iss >> query ;
            for (int k = 0 ;k < x ;k++)
            {
                bool substring = ((many_contact[k]).first).find(query) != string::npos ;

                if(substring && first)
                {
                    out << many_contact[k].second << " " << many_contact[k].first  ; first = false ;
                }
                else if(substring )
                {
                    out <<" " <<many_contact[k].second << " " << many_contact[k].first ;
                }
            }
        }
        first = true ;
        new_arr.push_back(out.str()) ;
        cout << out.str() ;
        out.str("") ;
        out.clear() ;
        iss.str("") ;
        iss.clear() ;
        many_contact.clear() ;
        i ++;
    }


    msgpack::pack(sbuf , new_arr) ;
    //write pack data to output file
    outf.write(sbuf.data() , sbuf.size()  ) ;

    arr.clear() ;
    delete [] buf ;
    inf.close() ;
    outf.close() ;

    return 0;



}
