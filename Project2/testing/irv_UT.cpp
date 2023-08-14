// Tests for IRV
#include <gtest/gtest.h>
#include "../src/irv.cpp"

 class IRVTests:public::testing::Test
{

protected:
IRV * testirv;
  
 
virtual void
  TearDown ()
  {
    
delete testirv;
    
testirv = NULL;

} 
};

// Taken from main.cpp, needed for each IRV object
string CreateTime ()
{
  string extension = ".txt";
  time_t now = time (0);
  std::tm * ltm = localtime (&now);
  int y = 1900 + ltm->tm_year;
  string year = std::to_string (y);
  int m = 1 + ltm->tm_mon;
  string month = std::to_string (m);
  int d = ltm->tm_mday;
  string day = std::to_string (d);
  int h = ltm->tm_hour - 12;
  string hour = std::to_string (h);
  int min = ltm->tm_min;
  string minutes = std::to_string (min);
  if(min<10){minutes= "0" +minutes;}
  int sec = ltm->tm_sec;
  string seconds = std::to_string (sec);
  if(sec<10){seconds= "0" + seconds;}
  string date = day;
  date.append ("_");
  date.append (month);
  date.append ("_");
  date.append (year);
  date.append ("_");
  date.append (hour);
  date.append (".");
  date.append (minutes);
  date.append (".");
  date.append (seconds);
  date.append (extension);
  return date;
}
 
// Test constructor
TEST_F (IRVTests, TestConstructor)
{
  
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testirv = new IRV (audit, CreateTime());
  
 
EXPECT_EQ (testirv->GetTypeofElection (), "");
  
EXPECT_EQ (testirv->GetTotalCandidates (), 0);
  
EXPECT_EQ (testirv->GetTotalBallots (), 0);

} 
 

// Testing find
TEST_F (IRVTests, Testfind)
{
  
int
  randomTransformedVote[4] = { 2, 3, 0, 1 };
  
std::vector < int >
  v (randomTransformedVote,
     randomTransformedVote +
     sizeof randomTransformedVote / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote1 = v;
  
 
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testirv = new IRV (audit, CreateTime());
  
EXPECT_EQ (testirv->find (randomTransformedVote1, 4, 3), 1);

 
 
 
};


 
// Testing TransformVote
TEST_F (IRVTests, TestTransformVote)
{
  
int
  randomTransformedVote[4] = { 2, 3, 4, 1 };
  
std::vector < int >
  v (randomTransformedVote,
     randomTransformedVote +
     sizeof randomTransformedVote / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote1 = v;
  
 
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testirv = new IRV (audit, CreateTime());
  
    //std::cout<<"\n";
    //std::cout<<testirv->TransformVote(v)[0];
    //std::cout<<"\n";
    EXPECT_EQ (testirv->TransformVote (randomTransformedVote1).size (), 4);
  
EXPECT_EQ (testirv->TransformVote (randomTransformedVote1)[1], 0);
  
EXPECT_EQ (testirv->TransformVote (randomTransformedVote1)[0], 3);
  
EXPECT_EQ (testirv->TransformVote (randomTransformedVote1)[2], 1);
  
EXPECT_EQ (testirv->TransformVote (randomTransformedVote1)[3], 2);

};


 
// Testing FindWinner
TEST_F (IRVTests, TestFindWinner)
{
  
 
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testirv = new IRV (audit, CreateTime());
  
    //std::cout<<"\n";
    //std::cout<<testirv->TransformVote(v)[0];
    //std::cout<<"\n";
    std::vector<std::string> files;
    files.push_back("irv_data.csv");
    testirv->FindWinner (files);
  
    // Winner should be rosen
    EXPECT_EQ ("Rosen", testirv->GetWinner ().GetName ());

};


 
//Testing sumVector
TEST_F (IRVTests, TestSumVector)
{
  
std::vector < int >
    testvec;
  
testvec.push_back (3);
  
testvec.push_back (12);
  
testvec.push_back (2);
  
 
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testirv = new IRV (audit, CreateTime());
  
 
EXPECT_EQ (testirv->SumVector (testvec), 17);

} 
 
 

// Testing TieBreaker
TEST_F (IRVTests, TestTieBreaker)
{
  
 
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testirv = new IRV (audit, CreateTime());

std::vector<std::string> files;
files.push_back("irv_data.csv");

testirv->FindWinner (files);
  
    // Winner should be rosen or Kleinberg
    std::string rosen = "Rosen";
  
std::string kleinberg = "Kleinberg";
  
bool one = rosen.compare (testirv->GetWinner ().GetName ()) == 0;
  
 
bool two = kleinberg.compare (testirv->GetWinner ().GetName ()) == 0;
  
    //EXPECT_THAT((std::array{"Rosen", "Kleinberg" }), Contains(testirv->GetWinner().GetName()));
    // EXPECT_EQ("Rosen", testirv->GetWinner().GetName()) || EXPECT_EQ("Kleinberg", testirv->GetWinner().GetName()) ;
    //EXPECT_TRUE (one || two);
    if((one || two)) SUCCEED();
    else FAIL() << "Neither " << rosen << " nor " << kleinberg << ", winner is " << testirv->GetWinner ().GetName ();

};


