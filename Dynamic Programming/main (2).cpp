#include <iostream>
#include <msgpack.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;
struct card{
    string type ;
    int cost ;
    int attack ;
};
bool cmp(struct card i , struct card j){
    return i.attack > j.attack ;
}
int main()
{
    fstream fin  ;
    fstream fout ;
    fin.open("input.txt" , ios::in | ios :: binary) ;
    fout.open("output.txt" , ios::out) ;
    char * buf = NULL ;
    int bufsize =0 ;
    int N , C  , P ;
    vector<string > INFO   ;
    vector<struct card> group ;
    struct card temp ;
    int dmg[10001] , number[10001] ;
    string t ;
    int c ,a , defense ;
    istringstream iss ;
    //read msgpack declaration
    size_t off = 0 ;
    msgpack::object_handle oh ;
    //read file data
    fin.seekg(0 , ios::end) ;
    bufsize = fin.tellg() ;
    fin.seekg(0 ) ;
    buf = new char[bufsize] ;
    fin.read(buf , bufsize) ;

    //unpack to get number of test data
    oh = msgpack::unpack(buf , bufsize ,off) ;
    oh.get().convert(N) ;
    for(int i = 0 ; i < N ; i++){
        //unpack
        oh = msgpack::unpack(buf , bufsize ,off) ;
        oh.get().convert(C) ;
        oh = msgpack::unpack(buf , bufsize ,off) ;
        oh.get().convert(P) ;
        oh = msgpack::unpack(buf , bufsize ,off) ;
        oh.get().convert(INFO) ;

        //read information
        for(int j = 0 ; j < C ; j++){
            iss.str(INFO[j]) ;
            iss >> t >> c >> a >> defense ;
            temp.type = t ;
            temp.cost = c ;
            temp.attack = a ;
            group.push_back(temp) ;
            iss.str("") ;
            iss.clear() ;
            t.clear() ;
        }
        sort(group.begin() , group.end() , cmp) ;

        int  can_play = 0 , play = 0  ;
        //initialize DP
        for(int j = 0 ; j < 10001 ; j++)
        {
            dmg[j] = 0 ;
            number[j] = 0 ;
        }
       for(int n = 1 ; n <= C ; n++)
        for(int c = P ; c >= 0 ; c--){
            can_play = 0 , play = 0 ;
            //judge if can play this card
            if(c >= group[n-1].cost){
                if(group[n-1].type == "spell") can_play = 1 ;
                else if(number[c-group[n-1].cost] < 5 ) can_play = 1 ;
                else can_play = 0 ;
            }
            else{
                can_play = 0 ;
            }
           if(!can_play) {
                dmg[c] = dmg[c] ;
                play = 0 ;
           }
           else{
                if(number[c-group[n-1].cost] > 0 || group[n-1].type == "spell" ){
                    if(dmg[c] < dmg[c-group[n-1].cost] + group[n-1].attack ){
                        play = 1 ;
                        dmg[c] = dmg[c-group[n-1].cost] + group[n-1].attack ;
                    }
                    else{
                        play = 0 ;
                        dmg[c] = dmg[c] ;
                    }
                }
                else{
                    if(dmg[c] < dmg[c-group[n-1].cost] + group[n-1].attack +2 ){
                        play = 1 ;
                        dmg[c] = dmg[c-group[n-1].cost] + group[n-1].attack + 2;

                    }
                    else{
                        play = 0 ;
                        dmg[c] = dmg[c] ;
                    }
                }
           }
            if(play  && group[n-1].type == "follower" ) number[c] =  number[c- group[n-1].cost] + 1  ;
            else if(play ) number[c] = number[c- group[n-1].cost] ;
            else number[c] = number[c] ;

       }
        fout << dmg[P] << endl ;
        group.clear() ;
        INFO.clear() ;

    }



    delete [] buf ;
    fin.close() ;
    fout.close() ;

    return 0;
}
