#include <iostream>
#include <fstream>
#include "parse_grammar.h"
#include "generate_follow.h"
#include "generate_table.h"
#include <bits/stdc++.h>
using namespace std;
using std::ifstream;

parse_grammar parse;
generate_follow follower;
generate_table gtable;

void print(map<string,vector< pair<string,string>>> First){
    map<string,vector< pair<string,string>>>::iterator itr;
    for (itr = First.begin(); itr != First.end(); ++itr) {
        for(int i=0;i<itr->second.size();i++){
            cout << itr->first << '\t' ;
            cout << itr->second[i].first << '\t' << itr->second[i].second <<'\n';
        }
        cout<<'\n'<<"-------------------------------------------------------"<<'\n';
    }
}

void readFile(char *fileName){
    char c;
    string line ;
    ifstream myFile(fileName,std::ios::ate);
    std::streampos size = myFile.tellg();
    for(int i=1;i<=size;i++){
        myFile.seekg(-i,std::ios::end);
        myFile.get(c);
        if(c=='\n'){
            if(line[0]=='#'){
                parse.extract_from_line(line);
                line = "";
            }
        }
        else
            line = c + line;
    }
    parse.extract_from_line(line);
}

void print_follow (map<string,vector<string>> follow){
    for (auto m: follow ){
       cout << m.first<< "                      ";
       for (auto v: m.second){
            cout << v <<" ";
       }
        cout << endl;
   }
}

void print_table (map<string,map<string,string>> Parsing_Table){
    cout<<"-------------------------------------------------------------"<<endl;
    for (auto m: Parsing_Table ){
       cout <<"        "<< m.first<< endl <<endl;
       for (auto v: m.second){
            cout << v.first <<"         " << v.second <<endl;
       }
       cout<<"--------------------------------------------------" <<endl;
   }
}

int main(){
   readFile("grammar.txt");
   map<string,vector<pair<string,string>>> first = parse.get_first();
  // print(first);

   map<string,vector<string>> follow = follower.get_follow(parse);
  // print_follow(follow);

   map<string,map<string,string>> Parsing_Table = gtable.get_Parsing_Table(first,follow);
   print_table(Parsing_Table);

   return 0;
}
