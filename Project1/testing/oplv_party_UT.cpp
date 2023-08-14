// Tests for OPLVParty
#include <gtest/gtest.h>
#include "../src/oplv_party.cpp"
#include <stdio.h>
#include <iostream>

 class OPLVPartyTests:public::testing::Test
{

protected:
OPLVParty * testparty;
  
 
virtual void
  TearDown ()
  {
    
delete testparty;
    
testparty = NULL;

} 
};


 
TEST_F (OPLVPartyTests, Constructor)
{
  
testparty = new OPLVParty ("Republican");
  
EXPECT_EQ (testparty->GetName (), "Republican");
  
EXPECT_EQ (testparty->GetSeats (), 0);
  
EXPECT_EQ (testparty->GetRemainingVotes (), 0);
  
EXPECT_EQ (testparty->GetNumCandidates (), 0);

};


 
TEST_F (OPLVPartyTests, AddCandidate)
{
  
testparty = new OPLVParty ("Republican");
  
OPLVCandidate * can1 = new OPLVCandidate ("John", 'R');	// 1 vote
  OPLVCandidate *
    can2 = new OPLVCandidate ("Susan", 'R');	// 3 votes
  OPLVCandidate *
    can3 = new OPLVCandidate ("Ralph", 'R');	// 2 votes
  testparty->AddCandidate (can1);
  
testparty->AddCandidate (can2);
  
testparty->AddCandidate (can3);
  
EXPECT_EQ (testparty->GetNumCandidates (), 3);

};


 
TEST_F (OPLVPartyTests, UpdateRank)
{
  
testparty = new OPLVParty ("Republican");
  
OPLVCandidate * can1 = new OPLVCandidate ("John", 'R');	// 1 vote
  OPLVCandidate *
    can2 = new OPLVCandidate ("Susan", 'R');	// 3 votes
  OPLVCandidate *
    can3 = new OPLVCandidate ("Ralph", 'R');	// 2 votes
  testparty->AddCandidate (can1);
  
testparty->AddCandidate (can2);
  
testparty->AddCandidate (can3);
  
can1->AddVote ();
  
can2->AddVote ();
  
can2->AddVote ();
  
can2->AddVote ();
  
can3->AddVote ();
  
can3->AddVote ();
  
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testparty->UpdateRank (audit);
  
 
EXPECT_EQ (can1->GetCurPartyRank (), 3);
  
EXPECT_EQ (can2->GetCurPartyRank (), 1);
  
EXPECT_EQ (can3->GetCurPartyRank (), 2);

};
