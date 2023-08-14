// Tests for IRVBallot
#include <gtest/gtest.h>
#include "../src/irv_ballot.cpp"

 class IRVBallotTests:public::testing::Test
{

protected:
IRVBallot * testballot;
  
 
virtual void
  TearDown ()
  {
    
delete testballot;
    
testballot = NULL;

} 
};


 
// testing the constructor with two values of transformedVOte
TEST_F (IRVBallotTests, Constructor)
{
  
int
  randomTransformedVote[4] = { 2, 3, 4, 1 };
  
std::vector < int >
  v (randomTransformedVote,
     randomTransformedVote +
     sizeof randomTransformedVote / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote1 = v;
  
testballot = new IRVBallot (200, randomTransformedVote1, 4);
  
EXPECT_EQ (testballot->GetVoterNum (), 200);
  
EXPECT_EQ (testballot->Valid (), true);
  
EXPECT_EQ (testballot->GetVoteSize (), 4);
  
EXPECT_EQ (testballot->GetIndex (), 0);
  
int
  randomTransformedVote2[4] = { 2, 3, -1, -1 };
  
std::vector < int >
  v1 (randomTransformedVote2,
      randomTransformedVote2 +
      sizeof randomTransformedVote2 / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote3 = v1;
  
testballot = new IRVBallot (92, randomTransformedVote3, 4);
  
EXPECT_EQ (testballot->GetVoterNum (), 92);
  
EXPECT_EQ (testballot->Valid (), true);
  
EXPECT_EQ (testballot->GetVoteSize (), 2);
  
EXPECT_EQ (testballot->GetIndex (), 0);

};


 
 
// test for the GetVoteSize method
TEST_F (IRVBallotTests, CheckVoteSize)
{
  
int
  randomTransformedVote[4] = { 2, 3, 4, -1 };
  
std::vector < int >
  v (randomTransformedVote,
     randomTransformedVote +
     sizeof randomTransformedVote / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote1 = v;
  
testballot = new IRVBallot (200, randomTransformedVote1, 4);
  
 
EXPECT_EQ (testballot->GetVoteSize (), 3);
  
 
int
  randomTransformedVote2[4] = { 2, -1, -1, -1 };
  
std::vector < int >
  v1 (randomTransformedVote2,
      randomTransformedVote2 +
      sizeof randomTransformedVote2 / sizeof randomTransformedVote2[0]);
  
 
std::vector < int >
    randomTransformedVote3 = v1;
  
testballot = new IRVBallot (200, randomTransformedVote3, 4);
  
 
EXPECT_EQ (testballot->GetVoteSize (), 1);

 
};


 
 
// test to see if the Incrementindex method is working properly
TEST_F (IRVBallotTests, CheckIncrementIndex)
{
  
int
  randomTransformedVote[4] = { 2, 3, 4, -1 };
  
std::vector < int >
  v (randomTransformedVote,
     randomTransformedVote +
     sizeof randomTransformedVote / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote1 = v;
  
testballot = new IRVBallot (200, randomTransformedVote1, 4);
  
 
 
testballot->Incrementindex ();
  
EXPECT_EQ (testballot->GetIndex (), 1);

};


 
// test for the GetCurrentPref method
TEST_F (IRVBallotTests, CheckCurrentPref)
{
  
int
  randomTransformedVote[4] = { 2, 3, 4, -1 };
  
std::vector < int >
  v (randomTransformedVote,
     randomTransformedVote +
     sizeof randomTransformedVote / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote1 = v;
  
testballot = new IRVBallot (200, randomTransformedVote1, 4);
  
 
EXPECT_EQ (testballot->GetCurrentPref (), 2);
  
testballot->Incrementindex ();
  
EXPECT_EQ (testballot->GetCurrentPref (), 3);

};


 
// test to check when the priority index surpasses the voteSize the ballot should become invalid
TEST_F (IRVBallotTests, CheckMulipleIncrements)
{
  
int
  randomTransformedVote[4] = { 2, 3, 4, -1 };
  
std::vector < int >
  v (randomTransformedVote,
     randomTransformedVote +
     sizeof randomTransformedVote / sizeof randomTransformedVote[0]);
  
 
std::vector < int >
    randomTransformedVote1 = v;
  
testballot = new IRVBallot (200, randomTransformedVote1, 4);
  
 
testballot->Incrementindex ();
  
EXPECT_EQ (testballot->Valid (), true);
  
 
testballot->Incrementindex ();
  
EXPECT_EQ (testballot->Valid (), true);
  
testballot->Incrementindex ();
  
EXPECT_EQ (testballot->Valid (), false);

};


