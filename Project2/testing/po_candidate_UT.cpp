// Tests for POCandidate
#include <gtest/gtest.h>
#include "../src/po_candidate.cpp"
#include <iostream>

 class POCandidateTests:public::testing::Test
{

protected:
POCandidate * testcandidate;
  
 
virtual void
  TearDown ()
  {
    
delete testcandidate;
    
testcandidate = NULL;

} 
};


 
TEST_F (POCandidateTests, Constructor)
{
    testcandidate = new POCandidate ();
    
    EXPECT_EQ (testcandidate->GetName (), "");    
    EXPECT_EQ (testcandidate->GetParty (), '\0');
    EXPECT_EQ (testcandidate->GetNumVotes (), 0);

    testcandidate = new POCandidate ("John", 'R');
    
    EXPECT_EQ (testcandidate->GetName (), "John");    
    EXPECT_EQ (testcandidate->GetParty (), 'R');
    EXPECT_EQ (testcandidate->GetNumVotes (), 0);
};


 
TEST_F (POCandidateTests, GetNumVotes)
{
    testcandidate = new POCandidate ("John", 'R');
    
    EXPECT_EQ (testcandidate->GetNumVotes(), 0);
};


 
TEST_F (POCandidateTests, GetName)
{
    testcandidate = new POCandidate ("John", 'R');
  
    EXPECT_EQ (testcandidate->GetName(), "John");
};

TEST_F (POCandidateTests, AddVote)
{
    testcandidate = new POCandidate ("John", 'R');
    
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
        testcandidate->AddVote ();
    }

    // If it were long long, then would = 3,001,000,001
    EXPECT_NE (testcandidate->GetNumVotes (), (long long) 3001000001);

    testcandidate = new POCandidate ("Susan", 'R');
    
    EXPECT_EQ (testcandidate->GetNumVotes (), 0);

    // Max int
    // for (int i = 0; i < 2147483647; i++) {
    //   if((i % 1000000000) == 0) std::cout << "Calculating...\n";
    //   testcandidate->AddVote ();
    // }

    // For speed
    testcandidate->SetNumVotes (2147483640);
    for (int i = 2147483640; i < 2147483647; i++) {
        testcandidate->AddVote ();
    }

    EXPECT_EQ (testcandidate->GetNumVotes (), 2147483647);

    // Go past the max
    testcandidate->AddVote ();

	EXPECT_NE (testcandidate->GetNumVotes (), (long long) 2147483648);


};
 
TEST_F (POCandidateTests, SetNumVotes)
{
  
    testcandidate = new POCandidate ("John", 'R');
    
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