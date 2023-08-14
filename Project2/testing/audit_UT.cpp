// Tests for Audit
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../src/audit.h"

 class AuditTests:public::testing::Test
{

protected:
Audit * testaudit;
  
 
virtual void
  TearDown ()
  {
    
delete testaudit;
    
testaudit = NULL;

} 
};


 
// Test if auditPrint prints correctly
TEST_F (AuditTests, auditPrint)
{
  
testaudit = new Audit ();
  
testaudit->auditFile = "audittest.txt";
  
testaudit->auditPrint ("Here's a test.");
  
testaudit->auditPrint ("It has two lines.");
  
std::ifstream file;
  
file.open ("audittest.txt");
  
int
    opened;
  
std::string one = "";
  
std::string two = "";
  
 
if (file.is_open ())
    {
      
opened = 1;
      
std::getline (file, one);
      
std::getline (file, two);
    
}
  
  else
    {
      
opened = 0;
    
}
  
 
EXPECT_EQ (1, opened);
  
EXPECT_EQ ("Here's a test.", one);
  
EXPECT_EQ ("It has two lines.", two);

};
