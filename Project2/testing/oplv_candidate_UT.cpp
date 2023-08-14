// Tests for OPLVCandidate
#include <gtest/gtest.h>
#include "../src/oplv_candidate.cpp"
#include <iostream>

 class OPLVCandidateTests:public::testing::Test
{

protected:
OPLVCandidate * testcandidate;
  
 
virtual void
  TearDown ()
  {
    
delete testcandidate;
    
testcandidate = NULL;

} 
};


 
TEST_F (OPLVCandidateTests, Constructor)
{
  
testcandidate = new OPLVCandidate ("John", 'R');
  
EXPECT_EQ (testcandidate->GetName (), "John");
  
EXPECT_EQ (testcandidate->GetParty (), 'R');
  
EXPECT_EQ (testcandidate->GetCurPartyRank (), -1);
  
EXPECT_EQ (testcandidate->GetNumVotes (), 0);

};


 
TEST_F (OPLVCandidateTests, SetCurPartyRank)
{
  
testcandidate = new OPLVCandidate ("John", 'R');
  
EXPECT_EQ (testcandidate->GetCurPartyRank (), -1);
  
testcandidate->SetCurPartyRank (4);
  
EXPECT_EQ (testcandidate->GetCurPartyRank (), 4);

};


 
TEST_F (OPLVCandidateTests, AddVote)
{
  
testcandidate = new OPLVCandidate ("John", 'R');
  
EXPECT_EQ (testcandidate->GetNumVotes (), 0);
  
testcandidate->AddVote ();
  
EXPECT_EQ (testcandidate->GetNumVotes (), 1);
  
for (int i = 0; i < 1000000; i++)
    testcandidate->AddVote ();
  
EXPECT_EQ (testcandidate->GetNumVotes (), 1000001);

// New test for integer overflow - 3 billion, overflows at ~2.1 billion
// for (long long i = 0; i < 3000000000; i++) {
//   if((i % 1000000000) == 0) std::cout << "Calculating...\n";
//   testcandidate->AddVote ();
// }

// For speed
for (long long i = 2000000000; i < 2200000000; i++) {
  //if((i % 1000000000) == 0) std::cout << "Calculating...\n";
  testcandidate->AddVote ();
}

// If it were long long, then would = 3,001,000,001
EXPECT_NE (testcandidate->GetNumVotes (), (long long) 3001000001);

testcandidate = new OPLVCandidate ("Susan", 'R');
  
EXPECT_EQ (testcandidate->GetNumVotes (), 0);

// Max int
// for (int i = 0; i < 2147483647; i++) {
//   if((i % 1000000000) == 0) std::cout << "Calculating...\n";
//   testcandidate->AddVote ();
// }

// For speed
testcandidate->SetNumVotes (2147483640);
for (int i = 2147483640; i < 2147483647; i++) {
   //if((i % 1000000000) == 0) std::cout << "Calculating...\n";
   testcandidate->AddVote ();
 }

EXPECT_EQ (testcandidate->GetNumVotes (), 2147483647);

// Go past the max
testcandidate->AddVote ();

	EXPECT_NE (testcandidate->GetNumVotes (), (long long) 2147483648);


};


 
TEST_F (OPLVCandidateTests, SetNumVotes)
{
  
testcandidate = new OPLVCandidate ("John", 'R');
  
testcandidate->SetNumVotes (432);
  
EXPECT_EQ (testcandidate->GetNumVotes (), 432);
 	
testcandidate->SetNumVotes (1000001);

EXPECT_EQ (testcandidate->GetNumVotes (), 1000001);

testcandidate->SetNumVotes (3000000000);

EXPECT_NE (testcandidate->GetNumVotes (),(long long)  3000000000);

testcandidate->SetNumVotes (2147483647);

EXPECT_EQ (testcandidate->GetNumVotes (), 2147483647);

//Going over the max
testcandidate->SetNumVotes (2147483648);

	EXPECT_NE (testcandidate->GetNumVotes (), (long long) 2147483648);


};


 
TEST_F (OPLVCandidateTests, SetWonSeat)
{
  
testcandidate = new OPLVCandidate ("John", 'R');
  
EXPECT_EQ (testcandidate->GetWonSeat (), false);
  
testcandidate->SetWonSeat ();
  
EXPECT_EQ (testcandidate->GetWonSeat (), true);

};


 
TEST_F (OPLVCandidateTests, AwardSeat)
{
  
testcandidate = new OPLVCandidate ("John", 'R');
  
testcandidate->SetCurPartyRank (4);
  
testcandidate->AwardSeat (5);
  
EXPECT_EQ (testcandidate->GetWonSeat (), true);
  
testcandidate = new OPLVCandidate ("John", 'R');
  
testcandidate->SetCurPartyRank (5);
  
testcandidate->AwardSeat (5);
  
EXPECT_EQ (testcandidate->GetWonSeat (), true);
  
testcandidate = new OPLVCandidate ("John", 'R');
  
testcandidate->SetCurPartyRank (6);
  
testcandidate->AwardSeat (5);
  
EXPECT_EQ (testcandidate->GetWonSeat (), false);
  
testcandidate = new OPLVCandidate ("John", 'R');
  
testcandidate->SetCurPartyRank (-1);
  
testcandidate->AwardSeat (5);
  
EXPECT_EQ (testcandidate->GetWonSeat (), true);

};
