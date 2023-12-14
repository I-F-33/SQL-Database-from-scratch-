#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../includes/sql/sql.h"

  
bool test_parentheses(bool debug){
   string s1 = "make table student fields fname, lname, major, age"; 
    string s2 = "insert into student values Flo, Yao, CS, 20"; 
    string s3 = "insert into student values \"Flo\", \"Jackson\", Math,21"; 
    string s4 = "insert into student values Calvin, Woo, Physics,22"; 
    string s5 = "insert into student values \"Anna Grace\", \"Del Rio\", CS, 22"; 
    string s6 = "insert into student values \"Anna Kat\", \"The Bat\", Art, 33"; 
    string s7 = "insert into student values Lilli, Sutton, Communications, 34"; 
    string s8 = "insert into student values Oliver, Knox, Math, 25"; 
    string s9 = "insert into student values Johnathan, Salinas, Biology, 18";
    string s10 = "insert into student values Justin, Wang, History, 19"; 

    vector<string> commands; 
    commands.push_back(s1);  

    //insertions
    commands.push_back(s2); 
    commands.push_back(s3); 
    commands.push_back(s4); 
    commands.push_back(s5);
    commands.push_back(s6); 
    commands.push_back(s7);
    commands.push_back(s8); 

    SQL sql; 
    for(int i = 0; i < commands.size(); i++){
      sql.command(commands[i]); 

    }

  if(debug){
    cout<<"full table\n"; 
    cout<<sql.command("select * from student")<<endl; 

    string command; 
    command = "select * from student where age < 30 and ((major = CS or major = Physics) and (lname < Y))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where (fname = \"Anna Grace\" and lname = \"Del Rio\") or (age >= 22)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 


    //professor tests
    command = "select * from student where (age < 30 and age > 20) and ((major = CS or major = Physics) or (lname < M))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where ((age < 30 and age > 20) and major = Communications) or ((major = CS or major = Physics))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= H))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where age < 25 or (age > 20 and major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where (age < 25 or age > 20) and major = Communications"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where (age < 25 and age > 20) and major = Communications"; //will give non-existent
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= N))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where (age < 25 and age > 20) and (lname > D and lname <= N) or (major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where (age < 25 and age > 20) and (lname > J) or (major = Math)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

    command = "select * from student where ((age < 20 and age > 30)) and ((major = Art) or (major = Math))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    cout << sql.select_recnos() << endl; 

  }

  if(true){
    cout<<"full table\n";
    cout<<sql.command("select * from student")<<endl;
    
    string command = "select * from student where (age < 25 and age > 20) and (lname > D and lname <= N) or (major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

  }
  return true;
}




// ----------running testB.cpp---------


// [==========] Running 2 tests from 2 test suites.
// [----------] Global test environment set-up.
// [----------] 1 test from TEST_STUB
// [ RUN      ] TEST_STUB.TestStub
// [       OK ] TEST_STUB.TestStub (0 ms)
// [----------] 1 test from TEST_STUB (1 ms total)

// [----------] 1 test from TEST_SQL
// [ RUN      ] TEST_SQL.TestSQL
// full table
// Table name: student1 record number: 11
// record                  age               major               fname               lname
//     0:                   11                  CS                 Flo                 Yao
//     1:                   12                Math                 Flo             Jackson
//     2:                   13             Physics              Calvin                 Woo
//     3:                   14                  CS           AnnaGrace              DelRio
//     4:                   15                 Art             AnnaKat              TheBat
//     5:                   16      Communications               Lilli              Sutton
//     6:                   17                Math              Oliver                Knox
//     8:                   19             History              Justin                Wang
//     9:                   10                  CS                Blow                 Joe
//    10:                   11                Math               Huang              Ricong
//    11:                   39             Physics                Tots                 Flo

// command: select * from student where age = 11 and lname > Y
// Queue: Head -> [age]  [11]  [=]  [lname]  [Y]  [>]  [and]

// Table name: student2 record number: 0
// record                  age               major               fname               lname
//     0:                   11                  CS                 Flo                 Yao

// [0 ]

// [       OK ] TEST_SQL.TestSQL (380 ms)
// [----------] 1 test from TEST_SQL (382 ms total)

// [----------] Global test environment tear-down
// [==========] 2 tests from 2 test suites ran. (385 ms total)
// [  PASSED  ] 2 tests.
// PS D:\OneDrive\Desktop\CSFALL 2023\99_99_final_project-RiceKon> ."D:/OneDrive/Desktop/CSFALL 2023/99_99_final_project-RiceKon/build/bin/testB.exe"


// ----------running testB.cpp---------


// [==========] Running 2 tests from 2 test suites.
// [----------] Global test environment set-up.
// [----------] 1 test from TEST_STUB
// [ RUN      ] TEST_STUB.TestStub
// [       OK ] TEST_STUB.TestStub (0 ms)
// [----------] 1 test from TEST_STUB (0 ms total)

// [----------] 1 test from TEST_SQL
// [ RUN      ] TEST_SQL.TestSQL
// full table
// Table name: student1 record number: 6
// record                fname               lname               major                 age
//     0:                  Flo                 Yao                  CS                  20
//     1:                  Flo             Jackson                Math                  21
//     2:               Calvin                 Woo             Physics                  22
//     3:           Anna Grace             Del Rio                  CS                  22
//     4:             Anna Kat             The Bat                 Art                  33
//     5:                Lilli              Sutton      Communications                  34
//     6:               Oliver                Knox                Math                  25

// command: select * from student where age < 30 and ((major = CS or major = Physics) and (lname < Y))
// Queue: Head -> [age]  [30]  [<]  [major]  [CS]  [=]  [major]  [Physics]  [=]  [or]  [lname]  [Y]  [<]  [and]  [and]  

// Table name: student2 record number: 1
// record                fname               lname               major                 age
//     0:               Calvin                 Woo             Physics                  22
//     1:           Anna Grace             Del Rio                  CS                  22

// [2 3 ]

// command: select * from student where (fname = "Anna Grace" and lname = "Del Rio")) or (age >= 22))
// Queue: Head -> [fname]  [Anna Grace]  [=]  [lname]  [Del Rio]  [=]  [and]  [age]  [22]  [>=]  [or]  

// Table name: student3 record number: 4
// record                fname               lname               major                 age
//     0:               Calvin                 Woo             Physics                  22
//     1:           Anna Grace             Del Rio                  CS                  22
//     2:             Anna Kat             The Bat                 Art                  33
//     3:                Lilli              Sutton      Communications                  34
//     4:               Oliver                Knox                Math                  25

// [2 3 4 5 6 ]

// command: select * from student where (age < 30 and age > 20) and ((major = CS or major = Physics) or (lname < M))
// Queue: Head -> [age]  [30]  [<]  [age]  [20]  [>]  [and]  [major]  [CS]  [=]  [major]  [Physics]  [=]  [or]  [lname]  [M]  [<]  [or]  [and]  

// Table name: student4 record number: 3
// record                fname               lname               major                 age
//     0:                  Flo             Jackson                Math                  21
//     1:               Calvin                 Woo             Physics                  22
//     2:           Anna Grace             Del Rio                  CS                  22
//     3:               Oliver                Knox                Math                  25

// [1 2 3 6 ]

// command: select * from student where ((age < 30 and age > 20) and major = Communications) or ((major = CS or major = Physics))
// Queue: Head -> [age]  [30]  [<]  [age]  [20]  [>]  [and]  [major]  [Communications]  [=]  [and]  [major]  [CS]  [=]  [major]  [Physics]  [=]  [or]  [or]  

// Table name: student5 record number: 2
// record                fname               lname               major                 age
//     0:                  Flo                 Yao                  CS                  20
//     1:               Calvin                 Woo             Physics                  22
//     2:           Anna Grace             Del Rio                  CS                  22

// [0 2 3 ]

// command: select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= H))
// Queue: Head -> [age]  [25]  [<]  [age]  [20]  [>]  [and]  [major]  [Communications]  [=]  [or]  [lname]  [D]  [>]  [lname]  [H]  [<=]  [and]  [or]

// Table name: student6 record number: 3
// record                fname               lname               major                 age
//     0:                  Flo             Jackson                Math                  21
//     1:               Calvin                 Woo             Physics                  22
//     2:           Anna Grace             Del Rio                  CS                  22
//     3:                Lilli              Sutton      Communications                  34

// [1 2 3 5 ]

// command: select * from student where age < 25 or (age > 20 and major = Communications)
// Queue: Head -> [age]  [25]  [<]  [age]  [20]  [>]  [major]  [Communications]  [=]  [and]  [or]

// Table name: student7 record number: 4
// record                fname               lname               major                 age
//     0:                  Flo                 Yao                  CS                  20
//     1:                  Flo             Jackson                Math                  21
//     2:               Calvin                 Woo             Physics                  22
//     3:           Anna Grace             Del Rio                  CS                  22
//     4:                Lilli              Sutton      Communications                  34

// [0 1 2 3 5 ]

// command: select * from student where (age < 25 or age > 20) and major = Communications
// Queue: Head -> [age]  [25]  [<]  [age]  [20]  [>]  [or]  [major]  [Communications]  [=]  [and]

// Table name: student8 record number: 0
// record                fname               lname               major                 age
//     0:                Lilli              Sutton      Communications                  34

// [5 ]

// command: select * from student where (age < 25 and age > 20) and major = Communications
// Queue: Head -> [age]  [25]  [<]  [age]  [20]  [>]  [and]  [major]  [Communications]  [=]  [and]

// Table name: student9 record number: 0
// record                fname               lname               major                 age

// []

// command: select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= N))
// Queue: Head -> [age]  [25]  [<]  [age]  [20]  [>]  [and]  [major]  [Communications]  [=]  [or]  [lname]  [D]  [>]  [lname]  [N]  [<=]  [and]  [or]

// Table name: student10 record number: 4
// record                fname               lname               major                 age
//     0:                  Flo             Jackson                Math                  21
//     1:               Calvin                 Woo             Physics                  22
//     2:           Anna Grace             Del Rio                  CS                  22
//     3:                Lilli              Sutton      Communications                  34
//     4:               Oliver                Knox                Math                  25

// [1 2 3 5 6 ]

// command: select * from student where (age < 25 and age > 20) and (lname > D and lname <= N) or (major = Communications)
// Queue: Head -> [age]  [25]  [<]  [age]  [20]  [>]  [and]  [lname]  [D]  [>]  [lname]  [N]  [<=]  [and]  [and]  [major]  [Communications]  [=]  [or]

// Table name: student11 record number: 2
// record                fname               lname               major                 age
//     0:                  Flo             Jackson                Math                  21
//     1:           Anna Grace             Del Rio                  CS                  22
//     2:                Lilli              Sutton      Communications                  34

// [1 3 5 ]
// command: select * from student where (age < 25 and age > 20) and (lname > J) or (major = Math)
// Queue: Head -> [age]  [25]  [<]  [age]  [20]  [>]  [and]  [lname]  [J]  [>]  [and]  [major]  [Math]  [=]  [or]

// Table name: student12 record number: 2
// record                fname               lname               major                 age
//     0:                  Flo             Jackson                Math                  21
//     1:               Calvin                 Woo             Physics                  22
//     2:               Oliver                Knox                Math                  25

// [1 2 6 ]
// command: select * from student where ((age < 20 and age > 30)) and ((major = Art) or (major = Math))
// Queue: Head -> [age]  [20]  [<]  [age]  [30]  [>]  [and]  [major]  [Art]  [=]  [major]  [Math]  [=]  [or]  [and]  

// Table name: student13 record number: 0
// record                fname               lname               major                 age

// []
// full table
// Queue: Head -> 

// Table name: student14 record number: 6
// record                fname               lname               major                 age
//     0:                  Flo                 Yao                  CS                  20
//     1:                  Flo             Jackson                Math                  21
//     2:               Calvin                 Woo             Physics                  22
//     3:           Anna Grace             Del Rio                  CS                  22
//     4:             Anna Kat             The Bat                 Art                  33
//     5:                Lilli              Sutton      Communications                  34
//     6:               Oliver                Knox                Math                  25

// command: select * from student where age >= 33
// Queue: Head -> [age]  [33]  [>=]

// Table name: student15 record number: 1
// record                fname               lname               major                 age
//     0:             Anna Kat             The Bat                 Art                  33
//     1:                Lilli              Sutton      Communications                  34

// [4 5 ]

// [       OK ] TEST_SQL.TestSQL (1066 ms)
// [----------] 1 test from TEST_SQL (1066 ms total)

// [----------] Global test environment tear-down
// [==========] 2 tests from 2 test suites ran. (1068 ms total)
// [  PASSED  ] 2 tests.
// PS D:\OneDrive\Desktop\CSFALL 2023\99_99_final_project-RiceKon> 
 TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_parentheses(true));
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

