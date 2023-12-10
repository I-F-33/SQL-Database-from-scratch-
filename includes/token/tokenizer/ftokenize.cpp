#include "ftokenize.h"

//@PARAM -> fname, the name of the file to be tokenized
//Constructor that sets the file to be tokenized
FTokenizer::FTokenizer(char* fname)
{
    //try to open the file if fail then catch exception 

        _f.open(fname);

        _pos = 0;
        //setting up stokenizer
        _more = get_new_block();
;




/*      }
     catch(exception e)
     {
         cout << "File not found" << endl;
         throw exception();
     } */
    
    
    
}

Token_T FTokenizer::next_token()
{
    Token_T token;

    _stk >> token;

    //position in block is increased by the length of the token
    _blockPos += token.token_str().length() - 1;

    //if stk is done then get a new block
    //if there is nothing left to read and tokenize then 
    //more is set to false
    if(_stk.done())
    {
        _more = get_new_block();
  
    }
  
    //position in block of ma
    return token;

}

//returns the current value of _more
bool FTokenizer::more()        
{
    return _more;
}

//returns the value of _pos
int FTokenizer::pos()
{
    return _pos;
}

//returns the value of _blockPos
int FTokenizer::block_pos()
{
    return _blockPos;
}   

bool FTokenizer::get_new_block()
{   
    bool more = true;

    //check if there is more to read
    //if not then return false and close the file


    if(_f && _f.peek() == EOF)
    {
        _f.close();
        more = false;


    }
    else{

    //more blocks in file?

    _blockPos = 0;

     //setting up stokenizer
    char block[MAX_BUFFER] = "";


    int counter = 0;
    
    //MAX_buffer -1 because need one byte for the null character
    while(!(_f.peek() == EOF) &&  counter < (MAX_BUFFER - 1))
    {
    
       block[counter] = _f.get();
        _pos++;
        counter++;
    }

    _stk.set_string(block);

    //if there is nothing left to read then more is set to false
    //and close the file

    cout << "--------- New Block ----------- [" << counter << "] bytes" << endl;

    }


    return more;


}