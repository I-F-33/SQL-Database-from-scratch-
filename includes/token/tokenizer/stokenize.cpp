    #include "stokenize.h"


    int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

    STokenizer::STokenizer(): _pos(0), _done(false)  
    {
        make_table(_table);


    };   //default constructor

    STokenizer::STokenizer(const char str[]): _pos(0), _done(false)   //constructor that sets the string
    {
        set_string(str);
        make_table(_table);


    }

    bool STokenizer::done()            //true: there are no more tokens
    {
        return _done;
    }
    
    bool STokenizer::more()            //true: there are more tokens
    {
        return !_done;
    }

    //
    //returns the type of the character
    int STokenizer::get_char_type(int state)
    {
        int type;
        switch(state)
        {
            case 1:
                type = 2;
                break;
            case 3:
                type = 2;
                break;
            case 10:
                type = 1;
                break;
            case 12:
                type = 1;
                break;
            case 15:
                type = 4;
                break;
            case 20:
                type = 3;
                break;
            case 25:
                type = 5;
                break;
            default:
                type = -1;
                break;
        }
        return type;
    }

    //@PARAM str, the string that will be tokenized
    //set a new string as the input string
    //position is set to 0 and _done is set to false
    void STokenizer::set_string(const char str[])
    {
        strcpy(_buffer,str);
        _pos = 0;
        _done = false;
    }


    
    //@PARAM _table, the adjacency list that will be manipulated
    //This function will manipulate a given table to contain a state machine OR
    //create table for all the tokens we will recognize (e.g. doubles, words, etc.)
    void STokenizer::make_table(int _table[][MAX_COLUMNS])
    {
        /*
        *   This state machine will recognize the following tokens:
        *   
        */
        init_table(_table);

        //Branch 1 (Alpha)

        //marking appropriate states as success states
        mark_success(_table,1);
        mark_success(_table,3);
        
        //marking fail states
        mark_fail(_table, 0);
        mark_fail(_table,2);

        //marking cells according to the state machine
        mark_cells(0,_table,ALFA,1);
        mark_cells(1,_table,ALFA,1);
        mark_cells(1,_table,'\'','\'',2);
        mark_cells(2,_table,ALFA,3);
        mark_cells(3,_table,ALFA,3);


        //Branch 2-------------------------------------

        mark_success(_table,10);
        mark_success(_table,12);

        mark_fail(_table,11);

        mark_cells(0,_table,DIGITS,10);

        //state 10
        mark_cells(10,_table,DIGITS,10);
        mark_cells(10,_table,'.','.',11);

        //state 11
        mark_cells(11,_table,DIGITS,12);

        //state 12
        mark_cells(12,_table, DIGITS,12);

        //Branch 3------------------------------

        mark_success(_table,15);

        mark_cells(0,_table,OPERATORS,15);
        mark_cells(15,_table,OPERATORS,15);

        //Branch 4----------------------------

        mark_success(_table, 20);

        mark_cells(0,_table,SPACES,20);

        //state 20
        mark_cells(20,_table,SPACES,20);

        //Branch 5-------------------------

        mark_success(_table,25);

        mark_cells(0,_table,PUNC,25);
      //  mark_cells(25,_table,PUNC,25);


    }

    //extract the longest string that match
    //     one of the acceptable token types
    bool STokenizer::get_token(int& success_state, string& token)
    {

        if(_pos >= strlen(_buffer))
        {
            _done = true;
            return false;
        }
        bool success = 0;

        //last position in the string where we were at a success state
        int success_position= 0;

        //the position where the state machine breaks
        int break_position = 0;

        //This variable will be used as a tracker of the states
        int state = 0;

        //loop used to iterate the buffer
        for(int i = _pos; i < strlen(_buffer); i++)
        {
            int character = _buffer[i];
            //state will be updated to the state given by that character at that state
            state = _table[state][character];

            //if the new state is a success state then update the success position
            //update success to True
            if(is_success(_table,state))
            {
                success_position = i;
                success_state = state;
                success = 1;
            }
            //if the character is not part of this state machine 
            if(state == -1)
            {
                break_position = i;

                break;
            }
        }

        //if we successfully found a token
        if(success)
        {
            //extract the token from the buffer
            for(int i = _pos; i <= success_position; i++)
            {
                token += _buffer[i];
            }
            
            _pos = success_position + 1;
        } else {
            token += _buffer[_pos];
            _pos++;
        }

        //update the position to the break position

        return success;
    }