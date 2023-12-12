#include "parser.h"

    int Parser::_table[MAX_ROWS][MAX_COLUMNS];

     void Parser::init_keywords_map()
    {
        keywords_map.at("select") = SELECT;
        keywords_map.at("from") = FROM;
        keywords_map.at("where") = WHERE;
        keywords_map.at("and") = AND;
        keywords_map.at("or") = OR;
        keywords_map.at("insert") = INSERT;
        keywords_map.at("into") = INTO;
        keywords_map.at("values") = VALUES;
        keywords_map.at("*") = STAR;
        keywords_map.at("make") = MAKE;
        keywords_map.at(",") = COMMA;
        keywords_map.at("(") = LEFTPAREN;
        keywords_map.at(")") = RIGHTPAREN;
        keywords_map.at("table") = TABLE;
        keywords_map.at("fields") = FIELDS;
        keywords_map.at("\"") = QUOTES;
        keywords_map.at(">") = OPERATOR;
        keywords_map.at("<") = OPERATOR;
        keywords_map.at("=") = OPERATOR;
        keywords_map.at("!=") = OPERATOR;
        keywords_map.at(">=") = OPERATOR;
        keywords_map.at("<=") = OPERATOR;
       



    }

    void Parser::init_parse_table()
    {
        init_table(_table);

        //create state machine

        //mark fails
        mark_fail(_table,1);
        mark_fail(_table,2);
        mark_fail(_table,3);
        mark_fail(_table,4);
        mark_fail(_table,5);
        mark_fail(_table,7);
        mark_fail(_table,8);
        mark_fail(_table,9);
        mark_fail(_table,10);
        mark_fail(_table,11);
        mark_fail(_table,13);
        mark_fail(_table,14);
        mark_fail(_table,15);
        mark_fail(_table,18);
        mark_fail(_table,19);
        mark_fail(_table,20);
        mark_fail(_table,21);
        mark_fail(_table,23);
        mark_fail(_table,24);
        mark_fail(_table,25);
        mark_fail(_table,26);
        mark_fail(_table,27);
        mark_fail(_table,29);
        mark_fail(_table,30);
        mark_fail(_table,31);



        //mark successes
        mark_success(_table,6);
        mark_success(_table,12);
        mark_success(_table,16);
        mark_success(_table,22);
        mark_success(_table,28);
        mark_success(_table,32);
        mark_success(_table,35);
        mark_success(_table,39);
        mark_success(_table,42);

        //select workflow
        mark_cell(0, _table, SELECT, 1);
        mark_cell(0,_table,MAKE,18);
        mark_cell(0,_table,INSERT,24);

        //after select go to state 1
        mark_cell(1,_table,STAR,2);
        mark_cell(1,_table,20,3);

        mark_cell(2,_table,FROM,5);
        
        mark_cell(3,_table,FROM,5);
        mark_cell(3,_table,COMMA,4);

        mark_cell(4,_table,20,3);

        mark_cell(5,_table,20,6);

        mark_cell(6,_table,WHERE,7);

        mark_cell(7,_table,LEFTPAREN,8);
        mark_cell(7,_table,20,14);

        mark_cell(8, _table,20,9);

        mark_cell(9,_table,OPERATOR,10);

        mark_cell(10,_table,20,11);
        mark_cell(10,_table,QUOTES,36);

        //quote branch
        mark_cell(36,_table,20,37);
        mark_cell(37,_table, 20, 37);
        mark_cell(37,_table,QUOTES,38);

        mark_cell(38,_table,RIGHTPAREN,39);
        mark_cell(38,_table, AND, 13);
        mark_cell(38,_table, OR, 13);

        mark_cell(39,_table, AND, 13);
        mark_cell(39,_table,OR,13);


        mark_cell(11,_table,RIGHTPAREN,12);
        mark_cell(11,_table,AND,13);
        mark_cell(11,_table,OR,13);

        mark_cell(12,_table,AND,13);
        mark_cell(12,_table,OR,13);

        mark_cell(13,_table,20,9);
        mark_cell(13,_table,LEFTPAREN,8);
        
        mark_cell(14,_table,OPERATOR,15);

        mark_cell(15,_table,20,16);
        mark_cell(15,_table,QUOTES, 33);

        mark_cell(33,_table, 20,34);

        mark_cell(34,_table,20,34);

        mark_cell(34,_table, QUOTES, 35);

        mark_cell(35,_table, AND, 17);
        mark_cell(35,_table, OR, 17);


        mark_cell(16,_table,AND,17);
        mark_cell(16,_table,OR,17);

        mark_cell(17,_table,20,14);

        //MAKE workflow
        mark_cell(18,_table,TABLE,19);
        mark_cell(19,_table,20,20);
        mark_cell(20,_table,FIELDS,21);
        mark_cell(21,_table,20,22);
        mark_cell(22,_table,COMMA,23);
        mark_cell(23,_table,20,22);


        //INSERT workflow

        mark_cell(24,_table,INTO,25);
        mark_cell(25,_table,20,26);
        mark_cell(26,_table,VALUES,27);
        mark_cell(27,_table,20,28);
        mark_cell(27,_table,QUOTES,30);
        mark_cell(28,_table,COMMA,29);
        mark_cell(29,_table,20,28);
        mark_cell(29,_table,QUOTES,30);
        mark_cell(28, _table, QUOTES,30);
        mark_cell(30,_table,20,31);
        mark_cell(31,_table,QUOTES,32);
        mark_cell(31, _table, SPECIALQ,29);
        mark_cell(31, _table, 20,31);
        mark_cell(32,_table,COMMA,29);

    }

    Parser::Parser(const char* s)
    {
        init_keywords_map();
        init_parse_table();
        set_string(s);
    }

    Parser::Parser()
    {
        init_keywords_map();
        init_parse_table();
    }

    Parser::~Parser()
    {
        _ptree.clear();
        
    }

    void Parser::set_string(const char* s)
    {

        _ptree.clear();

        _stk.set_string(s);

        while(_stk.more())
        {
            Token_T t;

            _stk >> t;

            if(t.type_string() == "ALPHA")
            {
                input_queue.push(t.token_str());
            }
            else if(t.type_string() == "NUMBER")
            {
                input_queue.push(t.token_str());
            }
            else if(t.type_string() == "OPERATOR")
            {
                
                
                    input_queue.push(t.token_str());
                
                
            }
            else if(t.type_string() == "PUNCTUATION")
            {
                input_queue.push(t.token_str());
            }
            
            
        }

        bool valid = get_parse_tree();

        fail_flag = valid == false ? true : false;
    }

    int Parser::get_column(string s)
    {
        int column = 0;
        if(keywords_map.contains(s))
        {
            column = keywords_map.at(s);
        }
        else
        {
            //8 = string token
            column = 20;
        }

        return column;
    }
   

    bool Parser::get_parse_tree()
    {
        bool success;

        int last_key = 0;

        int state = 0;

        string s;

        bool quoted_string_flag = false;
        string quoted_string = "";

        while(!input_queue.empty())
        {
            s = input_queue.pop();
            
            int column = get_column(s);

            state = _table[state][column];

            success = is_success(_table,state);

            switch(last_key)
            {
                case SELECT:
                    if(s != "," and s != "from")
                    _ptree.at("fields").push_back(s);

                    if(s == "*")
                    {
                        last_key = 0;
                    }
                    break;
                case TABLE:
                case FROM:
                case INTO:
                    _ptree.at("table_name").push_back(s);
                    last_key = 0;
                    break;
                //INSERT
                case VALUES:

                    if((s == "\"" || s == "\"")&& !quoted_string_flag)
                    {
                        quoted_string_flag = true;
                    }
                    else if((s != "\"" && s != "\"" )&& !quoted_string_flag) 
                    {
                        if(s != "," && s != "\"")
                        _ptree.at("values").push_back(s);
                    }
                    else if((s != "\"")&& quoted_string_flag)
                    {
                         if(s == ".")
                        {
                            quoted_string = quoted_string + ".";

                        }
                        else
                        {
                            if(quoted_string.empty())
                            {
                                quoted_string += s;
                            }
                            else
                            {
                                quoted_string = quoted_string + " " + s;

                            }

                        }
                    }
                    else if((s == "\"") && quoted_string_flag)
                    {
                        _ptree.at("values").push_back(quoted_string);
                        quoted_string.clear();
                        quoted_string_flag = quoted_string_flag == false ? true : false;
                        
                    }
                   
                    
                    break;
                //MAKE
                case FIELDS:

                    if(s != ",")
                    _ptree.at("columns").push_back(s);

                    break;
                case WHERE:
                    if(s != "\"" && !quoted_string_flag)
                    {
                        _ptree.at("condition").push_back(s);
                    }
                    else if(s != "\"" && quoted_string_flag)
                    {
                        if(quoted_string.empty())
                        {
                            quoted_string += s;
                        }
                        else
                        {
                            quoted_string = quoted_string + " " + s;

                        }
                    }
                    else if(s == "\"" && quoted_string_flag)
                    {
                        _ptree.at("condition").push_back(quoted_string);
                        quoted_string.clear();
                        quoted_string_flag = false;
                        
                    }
                    else if(s == "\"" && !quoted_string_flag)
                    {
                        quoted_string_flag = true;
                    }

                    break;
                default:
                    break;
                
            };

            if(s == "select" || s == "make" || s == "insert")
            {
                _ptree.at("command").push_back(s);

                if(s == "select")
                {
                    last_key = keywords_map.at(s);
                }
            }
            else if(s == "where")
            {
                _ptree.insert("where", "yes");
                last_key = keywords_map.at(s);
            }
            else if(s == "values" )
            {
                last_key = keywords_map.at(s);
            }
            else if(s == "from")
            {
                last_key = keywords_map.at(s);
            }
            else if(s == "table")
            {
                last_key = keywords_map.at(s);
            }
            else if(s == "fields")
            {
                last_key = keywords_map.at(s);
            }
            else if(s == "into")
            {
                last_key = keywords_map.at(s);
            }
            
        }
        
        //if select and no where then where is "false"
        //and condition is "none"
        if(_ptree.at("command").at(0) == "select" && !_ptree.contains("where"))
        {
            _ptree.at("where").push_back("false");
            _ptree.at("condition").push_back("none");
        }
        
        return success;
    }



    bool Parser::fail()
    {
        return fail_flag;
    }

    MMap<string,string> Parser::parse_tree()
    {
        
        return _ptree;
    }
