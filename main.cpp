#include <iostream>
#include <iomanip>
#include "includes/sql/sql.h"


using namespace std;

int main(int argv, char** argc) {
    
    SQL sql;

    cout << setw(80) << "Welcome to the SQL Database" << endl;

    for (int i = 0; i < 70; i++)
    {
        cout << "*" << "*";
    }
    cout << endl << setw(95) << "Please enter a command or type help for a list of commands" << endl;


    string input; //= "make table student fields name, age, major";

    while(input != "x" || input != "X")
    {
        
        getline(cin, input);

        cout << input << endl;
        if(input == "help")
        {
            cout << endl;
            cout << "<CREATE | MAKE> : {  <create | make> table <TABLE_NAME> fields <FIELD_NAME> [, <FIELD_NAME>...]  }" << endl;
            cout << "<INSERT> : { insert <INTO> <TABLE_NAME> values <VALUE> [, <VALUE>...]      }" << endl;
            cout << "<SELECT> : {  select <* | FIELD_NAME> [, ,FIELD_NAME>...]" << endl;
            cout << "				                        from <TABLE_NAME>                                       " << endl;
            cout << "			                            where <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>        " << endl;
            cout << "					                            [<LOGICAL_OPERATOR>                             " << endl;
            cout << "						                                <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>...] " << endl;
                                

            cout << "<VALUE>  :  A string of alphanumeric characters, or a string of alphanumeric                   " << endl;
            cout << "		                characters and spaces enclosed by double quotation marks:               " << endl;
            cout << "		                \"Jean Luise\", Finch, 1923                   " << endl;          
            cout << "<RELATIONAL OPERATOR> : [ = | > | < | >= | <= ]                                               " << endl;               
            cout << "<LOGICAL OPERATOR>    : [and | or]                                                           " << endl << endl << endl;       

        }
        else if(input == "x" || input == "X")
        {
            cout << setw(80) << "Terminating program" << endl;
            return 0;
        }
        else
        {
            cout << sql.command(input) << endl;;
            
        }

        cout << setw(80) << "Please enter a command or type help for a list of commands or enter [X] to terminate" << endl;
    }
    

        
    return 0;
}
