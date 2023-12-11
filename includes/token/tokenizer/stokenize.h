#ifndef STOKENIZE_H
#define STOKENIZE_H

#include "token_t.h"
#include "state_machine_functions.h"
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

class STokenizer
{
public:
    STokenizer();   //default constructor

    STokenizer(const char str[]);   //constructor that sets the string


    bool done();            //true: there are no more tokens

    bool more();           //true: there are more tokens
    //
   
    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Token_T& t)
    {
    //the string that the token will be extracted into
    string str = "";

    int state = 0;

    //extraction of token form buffer
    bool extract_token = s.get_token(state,str);

    t.set_string(str);

    int type = extract_token ? s.get_char_type(state) : TOKEN_UNKNOWN;

    t.set_type(type);

    return s;

 }


    //set a new string as the input string
    void set_string(const char str[]);

private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    //@PARAM _table, the adjacency list that will be manipulated
    //This function will manipulate a given table to contain a state machine
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int& success_state, string& token);
   
    

     //returns the type of the character
    int get_char_type(int state);
   

    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
    bool _done; 
};

#endif //TOKENIZER_H