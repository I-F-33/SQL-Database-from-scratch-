#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../includes/sql/sql.h"

  
  bool test_sql(bool debug = false)
{
  bool debug2 = false;
  if(debug)
  {
    SQL sql;
    

     std::vector<std::string> commands = {
        "make table players fields fname, lname, age, position, team",
        "insert into players values LeBron, James, 36, Forward, \"Los Angeles Lakers\"",
        "insert into players values Kevin, Durant, 33, Forward, \"Brooklyn Nets\"",
        "insert into players values Stephen, Curry, 33, Guard, \"Golden State Warriors\"",
        "insert into players values Giannis, Antetokounmpo, 27, Forward, \"Milwaukee Bucks\"",
        "insert into players values Luka, Doncic, 30, Guard, \"Dallas Mavericks\"",
        "insert into players values James, Harden, 32, Guard, \"Brooklyn Nets\"",
        "insert into players values Anthony, Davis, 28, Forward, \"Los Angeles Lakers\"",
        "insert into players values Kawhi, Leonard, 30, Forward, \"Los Angeles Clippers\"",
        "insert into players values Joel, Embiid, 27, Center, \"Philadelphia 76ers\""
        // "insert into players values Devin, Booker, 25, Guard, \"Phoenix Suns\"",
        // "insert into players values Jayson, Tatum, 23, Forward, \"Boston Celtics\"",
        // "insert into players values \"Karl Anthony\", Towns, 26, Center, \"Minnesota Timberwolves\"",
        // "insert into players values Trae, Young, 23, Guard, \"Atlanta Hawks\"",
        // "insert into players values Jimmy, Butler, 32, Forward, \"Miami Heat\"",
        // "insert into players values Donovan, Mitchell, 25, Guard, \"Utah Jazz\"",
        // "insert into players values Bam, Adebayo, 24, Center, \"Miami Heat\"",
        // "insert into players values Rudy, Gobert, 29, Center, \"Utah Jazz\"",
        // "insert into players values Chris, Paul, 37, Guard, \"Phoenix Suns\"",
        // "insert into players values Russell, Westbrook, 33, Guard, \"Los Angeles Lakers\""
    };

    for(int i = 0; i < commands.size(); i++)
    {
      cout << ">" << commands[i] << endl;
      sql.command(commands[i]);
     
    }
 
 cout << "ere" << endl;
    cout << sql.command("select * from players where age < \"30\" and team > \"Los Angeles Lakers\" or team = \"Dallas Mavericks\"") << endl;

    cout << sql.command("select * from players where team > \"Los Angeles Lakers\"") ;

    cout << sql.command("select * from players where team < \"Los Angeles Lakers\"") ;

    cout << sql.command("select * from players where team <= \"Los Angeles Lakers\"") ;






  }
  
  return true;
}


 TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_sql(true));
}  



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

