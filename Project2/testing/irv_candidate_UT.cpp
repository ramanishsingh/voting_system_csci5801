#include <gtest/gtest.h>
#include "../src/irv_candidate.cpp"

 class IRVCandidateTests:public::testing::Test
{

protected:
IRVCandidate * testcandidate;
  
 
virtual void
  TearDown ()
  {
    
delete testcandidate;
    
testcandidate = NULL;

} 
};


 
TEST_F (IRVCandidateTests, ConstructorNoArgs)
{
  
testcandidate = new IRVCandidate ();
  
EXPECT_EQ (testcandidate->GetName (), "");
  
EXPECT_EQ (testcandidate->GetParty (), '\0');
  
EXPECT_EQ (testcandidate->GetCandidateID (), 0);

};


 
TEST_F (IRVCandidateTests, ConstructorArgs)
{
  
testcandidate = new IRVCandidate ("Beth", 'D', 1);
  
EXPECT_EQ (testcandidate->GetName (), "Beth");
  
EXPECT_EQ (testcandidate->GetParty (), 'D');
  
EXPECT_EQ (testcandidate->GetCandidateID (), 1);

};


 
TEST_F (IRVCandidateTests, Eliminate)
{
  
testcandidate = new IRVCandidate ("Beth", 'D', 1);
  
EXPECT_EQ (testcandidate->CheckInRace (), true);
  
testcandidate->Eliminate ();
  
EXPECT_EQ (testcandidate->CheckInRace (), false);

};


 
TEST_F (IRVCandidateTests, SetMyBallots)
{
  
testcandidate = new IRVCandidate ("Beth", 'D', 1);
  
std::vector < int >
    testvotes;
  
testvotes.push_back (0);
  
testvotes.push_back (0);
  
testvotes.push_back (1);
  
testvotes.push_back (0);
  
testvotes.push_back (1);
  
testcandidate->SetMyBallots (testvotes);
  
 
EXPECT_EQ (testcandidate->GetMyBallots ()[0], 0);
  
EXPECT_EQ (testcandidate->GetMyBallots ()[1], 0);
  
EXPECT_EQ (testcandidate->GetMyBallots ()[2], 1);
  
EXPECT_EQ (testcandidate->GetMyBallots ()[3], 0);
  
EXPECT_EQ (testcandidate->GetMyBallots ()[4], 1);

};


 
TEST_F (IRVCandidateTests, GetNumVotes)
{
  
testcandidate = new IRVCandidate ("Beth", 'D', 1);
  
std::vector < int >
    testvotes;
  
testvotes.push_back (0);
  
testvotes.push_back (0);
  
testvotes.push_back (1);
  
testvotes.push_back (0);
  
testvotes.push_back (1);
  
testcandidate->SetMyBallots (testvotes);
  
 
EXPECT_EQ (testcandidate->GetNumVotes (), 2);

};


 
