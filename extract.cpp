#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<string> Split_Word(string str)
{
    vector<string> v;
    istringstream ss(str);
    string word; // for storing each word
    while (ss >> word)
    {
        v.push_back(word);
        //cout << word << "\n";
    }
    return v;
}


void Parser_Handle(map<string,map<string,string>> Parsing_Table,stack<string> Main_Stack,string One_Token)
{
    bool flag =true;
    while(flag)
    {
        string Top =Main_Stack.top();
        auto it = Parsing_Table.find(Top);
        if ( it == Parsing_Table.end() ) { //check if X is terminal or not
            // Non terminal
             string Production = Parsing_Table[Top][One_Token];
             if(Production=="sync"){
                 Main_Stack.pop();
                cout<<"Ignore Error:(illegal "<<Top<<")"<<endl;
             }
             else if (Production==""){
                 cout<<"Error:(illegal "<<Top<<") – discard "<<One_Token<<endl; //discard token and take another one.
                 flag = false;
             }
             else{
                 Main_Stack.pop();
                 cout<<Production<<endl; //output.
                 vector<string> Words_Vector=Split_Word(Production);
                 int i=Words_Vector.size();
                 while(i--)
                 {
                    Main_Stack.push(Words_Vector[i]);
                 }
             }
        }
        else {
           // terminal
            if(Top==One_Token){
                cout<<Top <<" "; //element Matched.
                //take next Token .
                flag = false;
            }
            else{
                cout<<"Error: missing "<<Top<<", inserted"<<endl; //Report Error.
            }
            //take next Token.
            Main_Stack.pop();


        }
    }

}


