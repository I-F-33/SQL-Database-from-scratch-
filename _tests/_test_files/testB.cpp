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



TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_parentheses(true));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

