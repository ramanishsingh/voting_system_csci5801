// Tests for main
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <stdlib.h>

class MainTests:public::testing::Test {
    virtual void TearDown () {}
};

// Test if the program can take in one OPLV file
TEST_F (MainTests, SingleFileOPLV)
{
    // system() will run a script that runs the program
    // and passing in two csvs.
    int status = system("bash testonefile.sh");

    // Inspired from https://stackoverflow.com/a/10931234
    if (status < 0) ADD_FAILURE_AT("Program encountered error: ", errno);
    else {
        if(WIFEXITED(status)) SUCCEED();
        else ADD_FAILURE_AT("Program exited with status" , WEXITSTATUS(status));

    }
};

// Test if the program can take in multiple OPLV files
TEST_F (MainTests, MultipleFilesOPLV)
{
    // system() will run a script that runs the program
    // and passing in two csvs.
    int status = system("bash testmultifile.sh");

    // Inspired from https://stackoverflow.com/a/10931234
    if (status < 0) ADD_FAILURE_AT("Program encountered error: ", errno);
    else {
        if(WIFEXITED(status)) SUCCEED();
        else ADD_FAILURE_AT("Program exited with status" , WEXITSTATUS(status));

    }
};

// Test if the program can take in one IRV file
TEST_F (MainTests, SingleFileIRV)
{
    // system() will run a script that runs the program
    // and passing in two csvs.
    int status = system("bash testonefileirv.sh");

    // Inspired from https://stackoverflow.com/a/10931234
    if (status < 0) ADD_FAILURE_AT("Program encountered error: ", errno);
    else {
        if(WIFEXITED(status)) SUCCEED();
        else ADD_FAILURE_AT("Program exited with status" , WEXITSTATUS(status));

    }
};

// Test if the program can take in multiple IRV files
TEST_F (MainTests, MultipleFilesIRV)
{
    // system() will run a script that runs the program
    // and passing in two csvs.
    int status = system("bash testmultifileirv.sh");

    // Inspired from https://stackoverflow.com/a/10931234
    if (status < 0) ADD_FAILURE_AT("Program encountered error: ", errno);
    else {
        if(WIFEXITED(status)) SUCCEED();
        else ADD_FAILURE_AT("Program exited with status" , WEXITSTATUS(status));

    }
};