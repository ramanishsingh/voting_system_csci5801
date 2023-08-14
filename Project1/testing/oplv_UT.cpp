// Tests for OPLV
#include <gtest/gtest.h>
#include "../src/oplv.cpp"

 class OPLVTests:public::testing::Test
{

protected:
OPLV * testoplv;
  
 
virtual void
  TearDown ()
  {
    
delete testoplv;
    
testoplv = NULL;

} 
};


 
TEST_F (OPLVTests, Constructor)
{
  
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testoplv = new OPLV (audit);
  
EXPECT_EQ (testoplv->GetTotalCandidates (), 0);
  
EXPECT_EQ (testoplv->GetTypeofElection (), "");
  
EXPECT_EQ (testoplv->GetTotalBallots (), 0);

};


 
TEST_F (OPLVTests, AddCandidate)
{
  
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testoplv = new OPLV (audit);
  
OPLVCandidate * can1 = new OPLVCandidate ("John", 'R');
  
OPLVCandidate * can2 = new OPLVCandidate ("Susan", 'R');
  
OPLVCandidate * can3 = new OPLVCandidate ("Ralph", 'D');
  
OPLVCandidate * can4 = new OPLVCandidate ("Guy", 'I');
  
testoplv->AddCandidate (can1);
  
testoplv->AddCandidate (can2);
  
testoplv->AddCandidate (can3);
  
testoplv->AddCandidate (can4);
  
std::vector < OPLVParty * >testparties = testoplv->GetParties ();
  
 
EXPECT_EQ (testparties.size (), 2);
  
EXPECT_EQ (testparties[0]->GetNumCandidates (), 2);
  
EXPECT_EQ (testparties[1]->GetNumCandidates (), 1);

};


 
TEST_F (OPLVTests, FindWinner)
{
  
Audit audit;
  
audit.auditFile = "audittest.txt";
  
testoplv = new OPLV (audit);
  
testoplv->FindWinner ("oplv_data.csv");
  
std::vector < OPLVCandidate * >winners = testoplv->GetWinners ();
  
 
EXPECT_EQ (winners.size (), 3);
  
EXPECT_EQ (winners[0]->GetName (), "Pike");
  
EXPECT_EQ (winners[1]->GetName (), "Foster");
  
EXPECT_EQ (winners[2]->GetName (), "Borg");

};
