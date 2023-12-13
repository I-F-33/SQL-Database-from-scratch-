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

#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>


//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/bplustree/btree_array_funcs.h"
#include "../../includes/bplustree/bplustree.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"


//------------------------------------------------------------------------------------------

using namespace std;

bool bplustree_test(){
  int a[] = {43, 20, 96, 100, 69};
  BPlusTree<int> bt(a, 5);
  cout << "Here is the tree: " << endl
      << bt << endl;

  cout << "in order:    " << bt.in_order() << endl;
  cout << "pre order:   " << bt.pre_order() << endl;
  cout << "post order:  " << bt.post_order() << endl;
  cout << "adding 10, 50, 200: " << endl;
  bt.insert(10);
  bt.insert(50);
  bt.insert(200);
  cout << "in order:    " << bt.in_order() << endl;
  cout << "pre order:   " << bt.pre_order() << endl;
  cout << "post order:  " << bt.post_order() << endl;

  cout << "Here is the tree: " << endl
       << bt << endl;
  cout << "bt.contains(20): " << boolalpha << bt.contains(20) << endl;
  cout << "bt.contains(0): " << boolalpha << bt.contains(0) << endl;
  cout << "bt.find(20): " << *(bt.find(20)) << endl;
  
  cout << "\nfind nonexisting key: " << endl;
  cout << "bt.find(0): ";
  bt.find(0).print_Iterator();
  cout << endl;

  cout << "\n\nexcess + grow: " << endl;

  bt.insert(12);
  cout << "adding 12: " << endl;
  cout << "Here is the tree: " << endl
       << bt << endl;
  cout << "in order:    " << bt.in_order() << endl;
  cout << "pre order:   " << bt.pre_order() << endl;
  cout << "post order:  " << bt.post_order() << endl;
  bt.insert(300);
  cout << "added 300: " << endl;
  cout << "Here is the tree: " << endl
       << bt << endl;
  cout << "in order:    " << bt.in_order() << endl;
  cout << "pre order:   " << bt.pre_order() << endl;
  cout << "post order:  " << bt.post_order() << endl;
  bt.insert(55);
  cout << "added 55: " << endl;
  cout << "Here is the tree: " << endl
       << bt << endl;
  cout << "in order:    " << bt.in_order() << endl;
  cout << "pre order:   " << bt.pre_order() << endl;
  cout << "post order:  " << bt.post_order() << endl;

  
  
  
  //Iterator test:
  cout << "\n---- iterator test: list of data: ------------\n\n";
  BPlusTree<int>::Iterator it = bt.begin();
  for (; it != bt.end(); it++){
      cout<<setw(5) << *it;

  }
  cout <<"\n---------------------------------------------\n\n";

  cout << "\n\nremove test: " << endl;

/*   int b[] = {43, 20, 96, 10, 50, 200, 12, 300, 55, 100, 69};
  for (int i = 0; i < 11; i++){
    cout << "\n removing: [" << b[i] << "]" << endl;
    bt.remove(b[i]);
    cout << bt << endl;
    cout << "in order:    " << bt.in_order() << endl;
    cout << "pre order:   " << bt.pre_order() << endl;
    cout << "post order:  " << bt.post_order() << endl;
    cout << "\nbt.empty()?" <<boolalpha<<bt.empty() << endl;
  }



  cout << "\nremove on empty:" << endl;
  bt.remove(666); */
  return true;
}

 bool map_test(){
  int keys[] = {43, 20, 96, 100, 69};
  string values[] = {"431", "201", "961", "1001", "691"};
  Map<int, string> map;
  for (int i = 0; i < 5; i++){
    map[keys[i]] = values[i];
  }
  for (int i = 0; i < 5; i++){
    cout << "map[" << keys[i] << "]: " << map[keys[i]] << endl;
  }
  for (int i = 0; i < 5; i++){
    map[keys[i]] = to_string(keys[i]*10+1);
  }
  cout << "\n----------\n";
  cout << map << endl;
  cout << "\n----------\n";
  for (int i = 0; i < 5; i++)
  {
    cout << "map[" << keys[i] << "]: " << map[keys[i]] << endl;
  }

  cout << "\n\n\n-------- iterator / range test ----------\n\n";
  Map<int, string>::Iterator it;
  for (it = map.begin(); it != map.end(); it++)
  {
    cout << *it << " | ";
  }
  
  cout << endl;
  cout << ". . .  lower_bound(): greater or equal to" << endl;
  it = map.lower_bound(10);
  cout << "lower_bound(10): " << *it << endl;
  //((it != map.end()) ? "NULL" : *it) << endl;
  it = map.lower_bound(20);
  cout << "lower_bound(20): " << *it << endl;
  it = map.lower_bound(42);
  cout << "lower_bound(42): " << *it << endl;
  it = map.lower_bound(150);
  if (it!=map.end())
    cout << "lower_bound(150): " << *it << endl;
  else
      cout << "lower_bound(150): " <<  "NULL"  << endl;
  
  
  cout << endl;
  cout << ". . .  upper_bound(): greater than" << endl;
  it = map.upper_bound(10);
  cout << "upper_bound(10): " << *it << endl;
  //((it != map.end()) ? "NULL" : *it) << endl;
  it = map.upper_bound(20);
  cout << "upper_bound(20): " << *it << endl;
  it = map.upper_bound(42);
  cout << "upper_bound(42): " << *it << endl;
  it = map.upper_bound(150);
  if (it!=map.end())
    cout << "upper_bound(150): " << *it << endl;
  else
      cout << "upper_bound(150): " <<  "NULL"  << endl;

  cout << "\n\n--- other functions --------\n\n";
  cout << "map.size():        " << map.size() << endl;
  cout << "map.empty():       " << map.empty() << endl;
  cout << "map.at(20):        " << map.at(20) << endl;
  cout << "map.find(43):      " << *map.find(43) << endl;
  cout << "map.contains(45):  " << boolalpha << map.contains(45) << endl;
  cout << "map.contains(100): " << boolalpha << map.contains(100) << endl;
  cout << "map.contains(150): " << boolalpha << map.contains(150) << endl;
  cout << "map.is_valud():    " << map.is_valid() << endl;
  return true;
} 


 bool multimap_test(){
  int keys[] = {43, 20, 96, 100, 69};
  string values[] = {"430", "200", "960", "1000", "690"};
  MMap<int, string> mmap;
  for (int i = 0; i < 5; i++){
    mmap[keys[i]] += values[i];
  }
  for (int i = 0; i < 5; i++){
    cout << "mmap[" << keys[i] << "]: " << mmap[keys[i]] << endl;
  }
  for (int i = 0; i < 5; i++){
    mmap[keys[i]] += to_string(keys[i]*10+1);
  }
  for (int i = 0; i < 5; i++){
    mmap[keys[i]] += to_string(keys[i]*10+3);
  }
  cout << "\n----------\n";
  cout << mmap << endl;
  for (int i = 0; i < 5; i++)
  {
    cout << "mmap[" << keys[i] << "]: " << mmap[keys[i]] << endl;
  }

  cout << "\n\n\n-------- iterator / range test ----------\n\n";
  MMap<int, string>::Iterator it;
  for (it = mmap.begin(); it != mmap.end(); it++)
  {
    cout << *it << " | ";
  }
  
  cout << endl;
  cout << ". . .  lower_bound(): greater or equal to" << endl;
  it = mmap.lower_bound(10);
  cout << "lower_bound(10): " << *it << endl;
  //((it != mmap.end()) ? "NULL" : *it) << endl;
  it = mmap.lower_bound(20);
  cout << "lower_bound(20): " << *it << endl;
  it = mmap.lower_bound(42);
  cout << "lower_bound(42): " << *it << endl;
  it = mmap.lower_bound(150);
  if (it!=mmap.end())
    cout << "lower_bound(150): " << *it << endl;
  else
      cout << "lower_bound(150): " <<  "NULL"  << endl;
  
  
  cout << endl;
  cout << ". . .  upper_bound(): greater than" << endl;
  it = mmap.upper_bound(10);
  cout << "upper_bound(10): " << *it << endl;
  //((it != mmap.end()) ? "NULL" : *it) << endl;
  it = mmap.upper_bound(20);
  cout << "upper_bound(20): " << *it << endl;
  it = mmap.upper_bound(42);
  cout << "upper_bound(42): " << *it << endl;
  it = mmap.upper_bound(150);
  if (it!=mmap.end())
    cout << "upper_bound(150): " << *it << endl;
  else
      cout << "upper_bound(150): " <<  "NULL"  << endl;
  
  cout << "\n\n--- other functions --------\n\n";
  cout << "mmap.size():        " << mmap.size() << endl;
  cout << "mmap.empty():       " << mmap.empty() << endl;
  cout << "mmap.at(20):        " << mmap.at(20) << endl;
  cout << "mmap.find(43):      " << *mmap.find(43) << endl;
  cout << "mmap.contains(45):  " << boolalpha << mmap.contains(45) << endl;
  cout << "mmap.contains(100): " << boolalpha << mmap.contains(100) << endl;
  cout << "mmap.contains(150): " << boolalpha << mmap.contains(150) << endl;
  cout << "mmap.is_valud():    " << mmap.is_valid() << endl;
  
  
  return true;
} 





#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/table/table.h"


//------------------------------------------------------------------------------------------

using namespace std;

Table make_table(){
    vectorstr fields={"fname", "lname", "age"};

    Table t("student", fields);
    vectorstr row;
    row = {"Joe", "Gomez", "20"};
    t.insert_into(row);
    row = {"Karen", "Orozco", "21"};
    t.insert_into(row);
    row = {"Flo", "Yao", "29"};
    t.insert_into(row);
    row = {"Jack", "Yao", "19"};
    t.insert_into(row);
    row = {"Flo", "Jackson", "20"};
    t.insert_into(row);
    row = {"Flo", "Gomez", "20"};
    t.insert_into(row);
    row = {"Karen", "Jackson", "15"};
    t.insert_into(row);
    return t;
}


bool table_basic(bool debug = false){
     Table t = make_table();
     cout<< "Here is table t: " << endl << t << endl;

     cout << "Here are all the Yaos:" << endl;
     cout << t.select({"age", "fname", "lname"}, "lname", "=", "yao");

     Table tbl_student("student");
     cout << "\n\nhere is the student table: " << tbl_student << endl;

     cout << "\n20 year-olds:" << endl;
     cout << tbl_student.select({"age", "fname", "lname"}, "age", "=", "20");
     cout <<"record numbers from original table: "<< tbl_student.select_recnos() << endl
          << endl;

     cout << "\nolder than 20 years old:" << endl;
     cout << tbl_student.select({"age", "fname", "lname"}, "age", ">", "20");
     cout <<"record numbers from original table: "<< tbl_student.select_recnos() << endl
          << endl;

     cout << "\nyounger than 20 years old:" << endl;
     cout << tbl_student.select({"age", "fname", "lname"}, "age", "<", "20");
     cout <<"record numbers from original table: "<< tbl_student.select_recnos() << endl
          << endl;

     cout << "\n20 or younger:" << endl;
     cout << tbl_student.select({"age", "fname", "lname"}, "age", "<=", "20");
     cout <<"record numbers from original table: "<< tbl_student.select_recnos() << endl
          << endl;


     cout << "\n20 or older:" << endl;
     cout << tbl_student.select({"age", "fname", "lname"}, "age", ">=", "20");
     cout <<"record numbers from original table: "<< tbl_student.select_recnos() << endl
          << endl;


     cout << "----- END TEST --------" << endl;
     return true;
}

bool table_relational(bool debug = false){
  Queue<Token *> post;
  Table t = make_table();
  post.push(new TokenStr("lname"));
  post.push(new TokenStr("Yao"));
  post.push(new Relational("="));
  Table selected = t.select({"lname", "age"}, post);
  cout << "recnos from all the Yaos query: " << t.select_recnos() << endl;
  cout << "all the Yaos: " << endl
     << selected << endl;
  return true;
}

bool table_logical(bool debug = false){
  Queue<Token *> post;
  Table t = make_table();
  cout << "here is the table: " << endl
       << t << endl;
  post = Queue<Token *>();
  post.push(new TokenStr("age"));
  post.push(new TokenStr("20"));
  post.push(new Relational("<="));
  post.push(new TokenStr("age"));
  post.push(new TokenStr("17"));
  post.push(new Relational(">="));
  post.push(new Logical("and"));
  Table selected = t.select({"lname", "age"}, post);
  cout << "recnos from all the 17 to 20 year olds: " << t.select_recnos() << endl;
  cout << "all the 17 to 20 year olds : " << endl
     << selected << endl;
  return true;

}

bool table_full_condition(bool debug = false){
  Queue<Token *> post;
  Table t = make_table();
  cout << "here is the table: " << endl
       << t << endl;
  post = Queue<Token *>();
  post.push(new TokenStr("age"));
  post.push(new TokenStr("20"));
  post.push(new Relational("<"));
  post.push(new TokenStr("age"));
  post.push(new TokenStr("17"));
  post.push(new Relational(">"));
  post.push(new Logical("and"));
  post.push(new TokenStr("lname"));
  post.push(new TokenStr("Gomez"));
  post.push(new Relational("="));
  post.push(new Logical("or"));
  Table selected = t.select({"lname", "age"}, post);
  cout << "recnos from all all the 17 to 20 year olds (non inclusive) along with all the Gomezes: " << t.select_recnos() << endl;
  cout << "" << endl
     << selected << endl;
  return true;

}

bool condition_from_strings(bool debug = false){
     vector<string> condition = {"(", "age", "<", "17", "or", "age", ">", "20", ")", "and", "(","lname", "=", "Jackson", "or", "lname", "=", "Yao", ")"};
     Table t = make_table();
     cout << "here is the table: " << endl
          << t << endl;
     Table selected = t.select({"lname", "age"}, condition);
     cout << "recnos from all all younger than 17, all older than 20, who are Jacksons: " << t.select_recnos() << endl;
     cout << endl
          << selected << endl;
     return true;

}

bool insert_test(bool debug = false)
{
  srand(1);
  
  vector<int> v;
  
  std::string data = "1082|1156|1156|1214|1214|1236|1236|1288|1347|1347|1456|1456|1478|1521|1521|1693|1702|1702|2127|2206|2206|2319|2319|2513|2513|2953|2953|2967|3077|3077|3110|3170|3170|3605|3605|3644|4024|4024|4406|4623|4623|4695|4695|4767|4885|4885|4909|4909|5001|5001|5445|5823|5823|5905|5905|6202|6202|6259|6261|6261|6342|6342|6640|6640|6769|6769|6842|6844|6844|7029|7029|7050|7050|7132|7139|7139|7177|7177|7187|7187|7251|7251|7416|7484|7484|7635|7670|7670|8013|8013|8025|8061|8061|8215|8215|8424|8424|8548|8732|8732|8768|8768|8907|9006|9006|9012|9012|9074|9074|9103|9384|9384|9504|9504|9566|9566|9663|9663|9809";

  std::replace(data.begin(), data.end(), '|', ' '); // Replace "|" with space

  istringstream iss(data);
  string token;
  set<int> uniqueNumbers;

  // Extracting numbers and adding them to the set to filter out duplicates
  while (iss >> token) {

    int number = std::stoi(token);
    uniqueNumbers.insert(number);

  }

  // Converting the set to a vector (array-like structure)
  vector<int> result(uniqueNumbers.begin(), uniqueNumbers.end());

  vector<int> v2;

  BPlusTree<int> bpt(false);

  for(int i = 0; i < 30; i++)
  {

    int a = rand();
    v2.push_back(a);
    bpt.insert(a);


  }


  
  //cout << bpt.in_order() << endl;

    bpt.print_tree();


cout << endl << endl;

  cout << bpt.in_order() << endl;
  cout << "end of testB.cpp" << endl;
  return 1;

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

