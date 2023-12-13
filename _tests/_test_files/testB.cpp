#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../includes/sql/sql.h"

  
bool test_parentheses(bool debug){
  
string s1 = "create table student fields fname, lname, major, age";
string s2 = "insert into student values \"Flo\", \"Yao\", \"CS\", 20";
string s3 = "insert into student values \"Flo\", \"Jackson\", \"Math\", 21";
string s4 = "insert into student values \"Calvin\", \"Woo\", \"Physics\", 22";
string s5 = "insert into student values \"Anna Grace\", \"Del Rio\", \"CS\", 22";
string s6 = "insert into student values \"Anna Kat\", \"The Bat\", \"Art\", 33";
string s7 = "insert into student values \"Lilli\", \"Sutton\", \"Communications\", 34";
string s8 = "insert into student values \"Oliver\", \"Knox\", \"Math\", 25";
string s9 = "insert into student values \"Johnathan\", \"Salinas\", \"Biology\", 18";
string s10 = "insert into student values \"Justin\", \"Wang\", \"History\", 19";
 std::string s11 = "insert into student values \"Sophie\", \"Turner\", \"Film Studies\", 23";
    std::string s12 = "insert into student values \"Alexander\", \"Graham\", \"Mechanical Engineering\", 20";
    std::string s13 = "insert into student values \"Haley\", \"Porter\", \"Environmental Science\", 21";
    std::string s14 = "insert into student values \"Ethan\", \"Spencer\", \"Chemical Engineering\", 24";
    std::string s15 = "insert into student values \"Madison\", \"Harper\", \"Graphic Design\", 22";
    std::string s16 = "insert into student values \"Carter\", \"West\", \"Business Administration\", 23";
    std::string s17 = "insert into student values \"Zoe\", \"Fisher\", \"Music\", 19";
    std::string s18 = "insert into student values \"Brandon\", \"Lawrence\", \"Computer Engineering\", 20";
    std::string s19 = "insert into student values \"Grace\", \"Harrison\", \"Chemistry\", 25";
    std::string s20 = "insert into student values \"Leo\", \"Keller\", \"Mathematics\", 22";

    vector<string> commands = {
      s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20//,s21,s22,s23,s24,s25
    };
  
    
    SQL sql; 
    for(int i = 0; i < commands.size(); i++){
     cout <<  sql.command(commands[i]) << endl;; 

    }

  if(true){
    cout<<"full table\n"; 
    cout<<sql.command("select * from student")<<endl; 

    string command; 
    command = "select * from student where age < 30 and ((major = CS or major = Physics) and (lname < Y))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (fname = \"Anna Grace\" and lname = \"Del Rio\") or (age >= 22)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 


    //professor tests
    command = "select * from student where (age < 30 and age > 20) and ((major = CS or major = Physics) or (lname < M))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where ((age < 30 and age > 20) and major = Communications) or ((major = CS or major = Physics))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= H))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where age < 25 or (age > 20 and major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (age < 25 or age > 20) and major = Communications"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (age < 25 and age > 20) and major = Communications"; //will give non-existent
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= N))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (age < 25 and age > 20) and (lname > D and lname <= N) or (major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    command = "select * from student where (age < 25 and age > 20) and (lname > J) or (major = Math)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    command = "select * from student where ((age < 20 and age > 30)) and ((major = Art) or (major = Math))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

  }
 
  if(false){
    cout<<"full table\n";
    cout<<sql.command("select * from student")<<endl;
    
    string command = "select * from student where (age < 25 and age > 20) and (lname > D and lname <= N) or (major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

  }
  return true;
}




/*
build git:(master) ✗  😊 $> tree ../includes/table
../includes/table
├── table.cpp
├── table.h
└── typedefs.h

0 directories, 3 files
build git:(master) ✗  😊 $> ./bin/basic_test       


----------running basic_test.cpp---------


[==========] Running 5 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 1 test from TABLE_BASIC
[ RUN      ] TABLE_BASIC.TableBasic
Here is table t: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


Here are all the Yaos:

Table name: _select_table_1, records: 2
                   record                    fname                    lname                      age

                        0                      Flo                      Yao                       29
                        1                     Jack                      Yao                       19



here is the student table: 
Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15



20 year-olds:

Table name: _select_table_4, records: 3
                   record                      age                    fname                    lname

                        0                       20                      Joe                    Gomez
                        1                       20                      Flo                  Jackson
                        2                       20                      Flo                    Gomez

record numbers from original table: 0 4 5 


older than 20 years old:

Table name: _select_table_6, records: 2
                   record                      age                    fname                    lname

                        0                       21                    Karen                   Orozco
                        1                       29                      Flo                      Yao

record numbers from original table: 1 2 


younger than 20 years old:

Table name: _select_table_8, records: 2
                   record                      age                    fname                    lname

                        0                       15                    Karen                  Jackson
                        1                       19                     Jack                      Yao

record numbers from original table: 6 3 


20 or younger:

Table name: _select_table_10, records: 5
                   record                      age                    fname                    lname

                        0                       15                    Karen                  Jackson
                        1                       19                     Jack                      Yao
                        2                       20                      Joe                    Gomez
                        3                       20                      Flo                  Jackson
                        4                       20                      Flo                    Gomez

record numbers from original table: 6 3 0 4 5 


20 or older:

Table name: _select_table_12, records: 5
                   record                      age                    fname                    lname

                        0                       20                      Joe                    Gomez
                        1                       20                      Flo                  Jackson
                        2                       20                      Flo                    Gomez
                        3                       21                    Karen                   Orozco
                        4                       29                      Flo                      Yao

record numbers from original table: 0 4 5 1 2 

----- END TEST --------
[       OK ] TABLE_BASIC.TableBasic (23 ms)
[----------] 1 test from TABLE_BASIC (23 ms total)

[----------] 2 tests from TABLE_INTERMEDIATE
[ RUN      ] TABLE_INTERMEDIATE.TableRelational
recnos from all the Yaos query: 2 3 
all the Yaos: 

Table name: _select_table_15, records: 2
                   record                    lname                      age

                        0                      Yao                       29
                        1                      Yao                       19


[       OK ] TABLE_INTERMEDIATE.TableRelational (7 ms)
[ RUN      ] TABLE_INTERMEDIATE.TableLogical
here is the table: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


recnos from all the 17 to 20 year olds: 0 3 4 5 
all the 17 to 20 year olds : 

Table name: _select_table_18, records: 4
                   record                    lname                      age

                        0                    Gomez                       20
                        1                      Yao                       19
                        2                  Jackson                       20
                        3                    Gomez                       20


[       OK ] TABLE_INTERMEDIATE.TableLogical (5 ms)
[----------] 2 tests from TABLE_INTERMEDIATE (12 ms total)

[----------] 2 tests from TABLE_ADVANCED
[ RUN      ] TABLE_ADVANCED.TableFullCondition
here is the table: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


recnos from all all the 17 to 20 year olds (non inclusive) along with all the Gomezes: 0 3 5 


Table name: _select_table_21, records: 3
                   record                    lname                      age

                        0                    Gomez                       20
                        1                      Yao                       19
                        2                    Gomez                       20


[       OK ] TABLE_ADVANCED.TableFullCondition (7 ms)
[ RUN      ] TABLE_ADVANCED.TableStringCondition
here is the table: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


recnos from all all younger than 17, all older than 20, who are Jacksons: 6 


Table name: _select_table_24, records: 1
                   record                    lname                      age

                        0                  Jackson                       15


[       OK ] TABLE_ADVANCED.TableStringCondition (5 ms)
[----------] 2 tests from TABLE_ADVANCED (12 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 3 test cases ran. (47 ms total)
[  PASSED  ] 5 tests.
build git:(master) ✗  😊 $> 


 */

 TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_parentheses(false));
}  

/*  TEST(TEST_BPLUS_TREE, BPlusTreeTest) {
  bool success = bplustree_test();
  EXPECT_EQ(success, true);
} 
 */
/*   TEST(Map_Test, MapTest) {
  bool success = map_test();
  EXPECT_EQ(success, true);
} 

  TEST(Multimap_Test, ultiMapTest) {
  bool success = multimap_test();
  EXPECT_EQ(success, true);
}  */

/* 
TEST(TABLE_BASIC, TableBasic) {
  bool success = table_basic();
  EXPECT_EQ(success, true);
}
TEST(TABLE_INTERMEDIATE, TableRelational) {
  bool success = table_relational(false);
  EXPECT_EQ(success, true);
}
TEST(TABLE_INTERMEDIATE, TableLogical) {
     bool success = table_logical(false);
}
TEST(TABLE_ADVANCED, TableFullCondition) {
     bool success = table_full_condition(false);
}

TEST(TABLE_ADVANCED, TableStringCondition) {
     bool success = condition_from_strings(false);
} 
 */
/* TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, insert_test(true));
} 
 */



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

