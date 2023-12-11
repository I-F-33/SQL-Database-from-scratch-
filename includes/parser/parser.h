#ifndef PARSER_H
#define PARSER_H
#include "../table/table.h"
#include "../token/tokenizer/stokenize.h"
using namespace std;


class Parser
{
    public : 

        Parser(const char* s);

        void set_string(const char* s);

        int get_column(string s);

        bool get_parse_tree();

        void init_parse_table();

        bool fail();

        MMap<string,string> parse_tree();

        void init_keywords_map();

    private:
        STokenizer _stk;
        MMap<string,string> _ptree; //parse tree
        Map<string,int> keywords_map; //map of keywords
        static int _table[MAX_ROWS][MAX_COLUMNS];
        bool fail_flag;
        Queue<string> input_queue;
        enum keys {UNKNOWN,SELECT,FROM,WHERE,AND,OR,INSERT,INTO,VALUES,STAR,MAKE,COMMA,RIGHTPAREN,LEFTPAREN,TABLE,FIELDS,QUOTES,SPECIALQ};


};



#endif // PARSER_H