/**
 * This is the main entrance for V-Pal's program.
 * It will read in the csv ballot and determine it's validity for processing.
 * @file main.cpp
 */  
  
/*******************************************************************************
 * Includes
 ******************************************************************************/ 
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include "irv.cpp"
#include "oplv.cpp"
#include "audit.h"
  using std::string;

using std::cout;

using std::endl;

 
/** 
 * @brief This method finds the type of election for processing
 * 
 * @param[in] filename needed to read csv file
 */ 
  
string FindType (string filename)
{
  
    //check that the file exists
    std::ifstream infile;
  
infile.open (filename);
  
if (infile)
    {				// if exists then return that ballot was found
      cout << "\n" << endl;
      
cout << "Ballot file found..." << endl;
    
}
  else
    {				// if not then return that ballot not found and prompt for file check. exit on failure
      cout << "\n" << endl;
      
cout << "ERROR: Ballot file not found..." << endl;
      
cout <<
	"Please make sure that the csv ballot file is in the current directory "
	<< endl;
      
exit (EXIT_FAILURE);
    
}
  
 
    // if success, then retrive election type and close file
    string type;
  
getline (infile, type);
  
infile.close ();
  
 
return type;

}


 
/**
 * 
 * @brief This method created the time format for unique signifier for summary files
 * 
 */ 
  
string CreateTime ()
{
  
 
    // call time library and extract the date and time information
    string extension = ".txt";
  
time_t now = time (0);
  
std::tm * ltm = localtime (&now);
  
 
    // extract year and format int to string
    int
    y = 1900 + ltm->tm_year;
  
string year = std::to_string (y);
  
 
    //extract month and format int to string
    int
    m = 1 + ltm->tm_mon;
  
string month = std::to_string (m);
  
 
    // extract day and format int to string
    int
    d = ltm->tm_mday;
  
string day = std::to_string (d);
  
 
    // extract hour and format int to string
    int
    h = ltm->tm_hour - 12;
  
    //cout << h << endl;
    string hour = std::to_string (h);
  
 
    // extract minutes and format int to string
    int
    min = ltm->tm_min;
string minutes = std::to_string (min);

if(min<10){     
minutes= "0" +minutes;
}
    // extract seconds and format int to string
    int
    sec = ltm->tm_sec;
  
string seconds = std::to_string (sec);
  
if(sec<10){
    seconds= "0" + seconds;
}
 
    // append the information together...day_month_year_hour:minutes:seconds.txt
    string date = day;
  
date.append ("_");
  
date.append (month);
  
date.append ("_");
  
date.append (year);
  
date.append ("_");
  
date.append (hour);
  
date.append (":");
  
date.append (minutes);
  
date.append (":");
  
date.append (seconds);
  
date.append (extension);
  
 
    //cout << date << endl;
    
return date;

 
}


 
/**
 * 
 * @brief This method displays the results from the IRV election
 * 
 * @param[in] person, party,votes, and ballots are taken in to display information
 * 
 */ 
  
void
IRVDisplay (string person, char party, int votes, int ballots)
{
  
 
    //creating the summary file name with unique signifier of time and date
    string title = "media_summary_irv_election_";
  
string time = CreateTime ();
  
title.append (time);
  
 
    // open summary file to write information to
    std::ofstream outfile;
  
 
outfile.open (title);
  
 
outfile << "Winner: \n" << endl;
  
outfile << "Candidate name : " << person << endl;
  
outfile << "Candidate's party: " << party << endl;
  
outfile << "Number of votes they received: " << votes << "\n" << endl;
  
    //outfile << "Total number of ballots casted in election: " << ballots <<endl;
    
outfile.close ();
  
 
cout << "RESULTS: \n" << endl;
  
cout << "Winner: " << endl;
  
cout << "Candidate name : " << person << endl;
  
cout << "Candidate's party: " << party << endl;
  
cout << "Number of votes they received: " << votes << "\n" << endl;
  
    //cout << "Total number of ballots casted in election: " << ballots <<endl;
} 
 

/**
 * 
 * @brief This method runs the elction according to the election type
 * 
 * @param[in] type and filename are taken in to process election
 */ 
  
void
Run (string type, string filename)
{
  
 
    // create audit object to pass into the specified election
    Audit audit;
  
string time = CreateTime ();
  
 
string irv_type = "IR\0";
  
string opl_type = "OPL\0";
  
 
if (type.compare (irv_type) == 0)
    {
      
 
	// if election is IRV then run IRV election and pass in audit object for documentation
	
cout << "Processing IRV ballot file...\n" << endl;
      
audit.auditFile = "audit_irv_election_";
      
audit.auditFile.append (time);
      
 
IRV * irv_election = new IRV (audit);
      
irv_election->FindWinner (filename);
      
cout << "Success! \n" << endl;
      
IRVCandidate winner = irv_election->GetWinner ();
      
 
	// retrieve winning candidates information
	string name = winner.GetName ();
      
int
	votes = winner.GetNumVotes ();
      
char
	party = winner.GetParty ();
      
int
	totl_bal = irv_election->GetTotalBallots ();
      
string stringParty (1, party);
      
audit.auditPrint ("RESULTS:");
      
audit.auditPrint ("Candidate name : " + name);
      
audit.auditPrint ("Number of votes they received: " +
			 std::to_string (votes));
      
audit.auditPrint ("Candidate's party: " + stringParty);
      
	// audit.auditPrint(std::to_string(totl_bal));
	
IRVDisplay (name, party, votes, totl_bal);
    
 
}
  else if (type.compare (opl_type) == 0)
    {
      
 
	// if election is OPL, then run OPLV election class and pass in audit object for documentation
	
cout << "Processing OPLV ballot file...\n" << endl;
      
audit.auditFile = "audit_oplv_election_";
      
audit.auditFile.append (time);
      
 
OPLV * oplv_election = new OPLV (audit);
      
 
	// FindWinner() runs the election process for OPLV to determine winner
	oplv_election->FindWinner (filename);
      
 
string opl_title = "media_summary_oplv_election_";
      
opl_title.append (time);
      
 
oplv_election->OutputWinners (opl_title);
      
 
cout << "Success! \n" << endl;
      
	// this part will change... not sure how the results are stored in OPLV at the moment
	// OPLVCandidate winner = oplv_election.GetResults();
    
}
  else
    {
      
cout << "Incorrect election type compatibility with V-Pal's system" <<
	endl;
      
exit (EXIT_FAILURE);
    
}

}


 
/**
 * 
 * @brief This is the main. Drives V-Pal's system
 * 
 * 
 */ 
  
int
main ()
{
  
string ballotFile;
  
std::ifstream infile;
  
    //read in the ballot file
    cout << "Please enter the name of the csv ballot file: ";
  
getline (std::cin, ballotFile);
  
 
    // Check start time of program
    auto start = std::chrono::high_resolution_clock::now ();
  
 
    //find the type of election to process the election 
    string election = FindType (ballotFile);
  
 
    // remove spaces and other notations
    remove_if (election.begin (), election.end (), isspace);
  
election.erase (remove_if (election.begin (), election.end (), isspace),
		   election.end ());
  
 
    // call Run to run the elections
    Run (election, ballotFile);
  
 
    // system has finished generating summary files
    cout << "Audit file and Media Summary file have been generated" << endl;
  
 
    // Check end time of program
    auto end = std::chrono::high_resolution_clock::now ();
  
 
std::chrono::duration < double >
    time_elapsed = end - start;
  
 
cout << "Runtime of program: " << time_elapsed.count () << " seconds\n";
  
 
return 0;

}


