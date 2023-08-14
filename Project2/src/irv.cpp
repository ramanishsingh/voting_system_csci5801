/*!
 * This is the IRV class. It inherits the Election class and drives the 
 * process of summarizing the calculations for Instant Runoff Voting system.
 * 
*/  
/**
 * @file irv.cpp
 * 
 */ 
  
/*******************************************************************************
 * Includes
 ******************************************************************************/ 
  
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "election.h"
#include "irv_ballot.cpp"
#include "irv_candidate.cpp"
#include "audit.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
  
using std::string;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/ 
/**
 * @brief Main class for IRV election
 * 
 */ 
class IRV:public Election
{

 
public:
IRV (Audit audit_, string invalidate_time)
  {
    
typeOfElection = "";
    
numCandidates = 0;
    
totalBallots = 0;
    
totalCandidates = 0;
    
audit = audit_;

invalidFile = "invalidated_";
invalidFile.append(invalidate_time);
  
}
  
 
 
	 /**
         * @brief A find function that gives index of the integer seek given a vector and length.
         *
         * @param[in] arr A vector of type int
         * @param[in] len Length or the size of the given arr
         * @param[in] seek A vector of type int
         */ 
    int
  find (std::vector < int >arr, int len, int seek) 
  {
    
for (int i = 0; i < len; ++i)
      
      {
	
if (arr[i] == seek)
	  return i;
      
}
    
return -1;
  
}
  
	/**
         * @brief A function that returns the sum of all elements of a vector
         *
         * @param[in] vec A vector of type int
         */ 
    int
  SumVector (std::vector < int >vec) 
  {
    int
      sum = 0;
    
int
      i = 0;
    
 
while (i < vec.size ())
      {
	
sum = sum + vec[i];
	
i = i + 1;
      
}
    
 
return sum;
  
}
  
	 /**
         * @brief A function that given a filename of csv for irv, it finds the winner
         *
         * @param[in] filename a filename of type string that is the csv file.
         */ 
    int FindWinner (std::vector<string> & files)
  {
    
	  int numBallots = 0;
	  int ballotno=0;
	// We need to loop through all the files

      // candidates is the vector of all * IRVcandidates
      // ballots is the vector of all * ballots
      
 
      // first we need to create the ballot objects and the candidate objects. 
      
      // read the csv files

	  for(int idx = 0; idx < files.size(); idx++)
	  {
		// Parse csv
        std::ifstream file(files[idx]);

    
		if (file.is_open ())
      	{
	
		std::string data;
	
	  	// Ignore first line
	  	std::getline (file, data);
	
		audit.auditPrint ("The type of election is IRV");
	
	  	// Number of candidates
	  	std::getline (file, data);
	
		numCandidates = std::stoi (data);
	
		audit.auditPrint ("Number of candidates: " +
			   std::to_string (numCandidates));
	
	  	// Get candidates
	  	std::getline (file, data);
	
		std::string candname = "";
	
		char candparty;
	
		int j = 0;
	
	  	// Loop for each candidate
	  	for (int i = 0; i < numCandidates; i++)
	  
	  	{
	    
	      // Loop through the string
	      for (j; j < data.length (); j++)
	      {
		
		  // Skip spaces
		  if (data[j] == ' ')
		  {
		    
			continue;
		  
			}
		
 
		  // Find party, break to make candidate
		  else if (data[j] == '(')
		  {
		    
		candparty = data[j + 1];
		    
		break;
		  
			}
		
 
		  // Add to name
		  else
		  {
		    
		candname = candname + std::string (1, data[j]);
		  
			}
	      
			}
	    
		if(idx == 0){
                       GenerateCandidates (candname, candparty, i);
	    
		audit.auditPrint ("Candidate: " + candname + ", party: " +
			       std::string (1, candparty));
                        }
	      // Add the candidate
	      
	    
		candname = "";
	    
	      // Skip to next candidate
	      j = j + 4;
	  
		}
	
 
	  // Get number of ballots
	 	 std::getline (file, data);
	
		//int numBallots = std::stoi (data);
		numBallots += std::stoi (data);
	
		audit.auditPrint ("Number of ballots after this file is: " +
			   std::to_string (numBallots));
	
		SetTotalBallots (numBallots);
	
 
	 	 // Loop through all the ballots;
	 	// int k = 0;
	
	audit.auditPrint("Following is the ballot data ( 0 means no pref indicated at that position");
	
	while (std::getline (file, data))
	  
	 	 {
	    
 
			std::vector < int >
	    	  output;
	    
			std::string input = data;
	    
		for (std::string::size_type p0 = 0, p1 = input.find (',');
		  
		p1 != std::string::npos || p0 != std::string::npos;
		  
		(p0 = (p1 == std::string::npos) ? p1 : ++p1), p1 =
		  input.find (',', p0))
	      
		output.push_back (strtol (input.c_str () + p0, NULL, 0));
	    
		string ballot_data_str = "";
	    
		int e = 0;
	    
		while (e < numCandidates)
	      {
		
			ballot_data_str =
		 	 ballot_data_str + std::to_string (output[e]);
		
 
			e = e + 1;
	      
			}
	    
	audit.auditPrint (ballot_data_str);
	    
 
	GenerateBallots (output, ballotno);
	    
		ballotno = ballotno + 1;
	  
	}
	
	audit.auditPrint ("Generated a total of " + std::to_string (numBallots) +
			   " ballots");
	
	  // Close csv
		  file.close ();
      
}
 else {audit.auditPrint("Error: csv file name is incorrect.");
        return 0;
        }

	  }



// Invalidate any invalid files
std::vector < int > invalidated = InvalidateBallots();

UpdateCandidates ();



// Record invalid files
std::fstream myfile;  
myfile.open(invalidFile,std::fstream::app);

for (auto it = invalidated.begin (); it < invalidated.end (); it++)
	  {
	    
myfile << (*it) << "\n"; 
	  
}

myfile.close(); 
    
bool winnerNotFound = true;
    
 
 
while (winnerNotFound)
      {
	
 
	  // votes is an array that contains the amount of ballots in which that candidate is the
	  // first choice
	  // Initialize votes
	std::vector < int >
	  votes;
	
for (auto it = candidates.begin (); it < candidates.end (); it++)
	  {
	    
votes.push_back ((*it)->GetNumVotes ());
	  
}
	
 
	  // Initialize V
	std::vector < int >
	  V;
	
for (int i = 0; i < candidates.size (); i++)
	  {
	    
V.push_back (i);
	  
} 
	  //Now we need to check if the candidate wih the highest votes has a mojority
	  int
	  N = numCandidates;
	
 
std::string print_cand_name;
	
std::string print_cand_votes;
	
	  //Next loop is just for printing to audit file
	  int
	  pw = 0;
	
while (pw < candidates.size ())
	  {
	    
if (candidates[pw]->CheckInRace ())
	      
	      {
		
print_cand_name = candidates[pw]->GetName ();
		
print_cand_votes = std::to_string (votes[pw]);
		
audit.auditPrint (print_cand_name + " has " +
				   print_cand_votes + " ballots");
	      
}
	    
pw = pw + 1;
	  
}
	
 
int
	  x = 0;
	
 
 
 
 
	  // Sort V based on votes
	  sort (V.begin (), V.end (),[&](int i, int j)
		{
		return votes[i] < votes[j];
		}
	);
	
 
 
	  //checking if we have majority
	  bool majority =
	  (votes[V[numCandidates - 1]] > (GetTotalBallots () / 2));
	
 
 
	  // if majority have found the winner. Just return the name of that candidate
	  if (majority)
	  {
	    
 
winnerNotFound = false;
	    
int
	      winnerIndex = V[numCandidates - 1];
	    
winner = (*candidates[winnerIndex]);
	    
audit.auditPrint ("We found a majority, Candidate " +
			       winner.GetName () + " has " +
			       std::to_string (votes[V[numCandidates - 1]]) +
			       " ballots");
	    
return 0;
	  
 
 
}
	
 
 
	  //If there is no majority, we need to remove candidate with least votes
	  // However, there can be candiates who are already eliminated
	  // So, first we sort the candidates based on their votes, then find the
	  // candidate with the least amount of votes in the list of valid candidates
	  
 
	  // Vector V contains the indices of the canidates sorted based on votes, lowest to highest
	  bool removed = false;
	
	  // removed is a boolean, which keeps track if we have removed someone
	  while (!removed)
	  {
	    
int
	      j = 0;
	    
	      // Now we iterate over all candidates, starting from the candidate with the lowest number of votes, first we check
	      // if they are in race. If yes, we compare their #votes with the number of votes that the highest candidate got. 
	      // If those two numbers are equal, this means we have a tie between all the candidates that are StillInRace. 
	      // If votes recieved by the first (valid) index in V is lower than the votes recieved by the last candidate in V
	      // we can simply remove the first (valid) candidate. 
	      while (j < numCandidates)
	      {
		
if (candidates[V[j]]->CheckInRace ())
		  {
		    
 
if (votes[V[j]] < votes[V[numCandidates - 1]])
		      {
			
			  //redistribute their votes (look where myBallots for that candidate was !0, then take those indices and find ballots with the ID. incremenetPriorityindex in those ballots.
			  // Get the new candidate for those ballots using transformedVote[PriorityIndex]. Update myBallot in those candidates (0 to 1))
			  //eliminate the candidate that has he index V[j] i.e. set StillInRace to False (I think)
			  removed = true;
			
std::string transferredBallots;
			
int
			  pe = 0;
			
while (pe <
				(candidates[V[j]]->GetMyBallots ().size ()))
			  {
			    
 
if (candidates[V[j]]->GetMyBallots ()[pe] == 1)
			      {
				
 
transferredBallots =
				  transferredBallots + std::to_string (pe) +
				  ",";
			      
}
			    
pe = pe + 1;
			  
}
			
audit.auditPrint ("We removed Candidate " +
					   candidates[V[j]]->GetName () +
					   ". Their votes are being redistributed");
			
audit.
			  auditPrint
			  ("Following ballots should be redistributed");
			
audit.auditPrint (transferredBallots);
			
 
RedistributeVotes (V[j]);
			
candidates[V[j]]->Eliminate ();
			
 
 
 
 
break;
		      
}
		    else
		      {
			
			  //it's a tie between the remaining candidates
			  //Call the tiebreaker function which takes candidates, find the caniddates who are still in Race. Chooses One of them
			  //break out of FindWinner
		      
std:string allcandstie;
			
 
int
			  cand_total = candidates.size ();
			
std::vector < int >
			  cands;
			
 
int
			  pq = 0;
			
 
while (pq < cand_total)
			  {
			    
 
if (candidates[pq]->CheckInRace ())
			      {
				
allcandstie =
				  allcandstie + candidates[pq]->GetName () +
				  " , ";
			      
 
}
			    
pq = pq + 1;
			  
}
			
 
 
audit.auditPrint ("We have a tie between " + allcandstie);
			  
int alpha = TieBreaker ();
			
 
removed = true;
			
 
winnerNotFound = false;
			
winner = (*candidates[alpha]);
			
audit.auditPrint ("We randomly chose " +
					   winner.GetName () +
					   " as the winner.");
			
 
return 0;
		      
}
		  
 
}
		
j = j + 1;
	      
}
	  
}
      
}
    
return 0;
  
}
  
 
 
	/**
         * @brief A function that returns the candidate object that is the winner
         *
         */ 
    IRVCandidate GetWinner ()
  {
    
return winner;
  
}
  
 
 
    // this function resolves any ties in the voting system
	/**
         * @brief A function that resolved any ties if there are any during the process of irv election
         *
         *
         */ 
    int
  TieBreaker ()
  {
    
 
int
      cand_total = candidates.size ();
    
std::vector < int >
      cands;
    
 
int
      pq = 0;
    
 
while (pq < cand_total)
      {
	
 
if (candidates[pq]->CheckInRace ())
	  {
	    
cands.push_back (candidates[pq]->GetCandidateID ());
	  
 
}
	
pq = pq + 1;
      
}
    
 
srand ((unsigned int) time (NULL));
    
int
      rand_num = rand () % cands.size ();
    
return cands[rand_num];;
  
 
}
  
	/**
         * @brief A function that redistributes the votes of the eleminated candidate given a the eliminated candidate id
         * @param[in] candidate_id_remove the id of the candidate that was eliminated or the least voted candidate.
         *
         */ 
    void
  RedistributeVotes (int candidate_id_remove)
  {
    
std::vector < int >
      candidate_removed_ballots;
    
 
      //access the ballots of the removed candidate
      candidate_removed_ballots =
      candidates[candidate_id_remove]->GetMyBallots ();
    
 
int
      i = 0;
    
 
while (i < candidate_removed_ballots.size ())
      {
	
	  //if the myBallot [i] is one for the removed candidate, we need to redistribute it
	  if (candidate_removed_ballots[i] == 1)
	  {
	    
std::vector < int >
	      updated_myBallot =
	      candidates[candidate_id_remove]->GetMyBallots ();
	    
updated_myBallot[i] = 0;
	    
	      //make myBallot[i]=0 for the removed candidate
	      candidates[candidate_id_remove]->
	      SetMyBallots (updated_myBallot);
	    
ballots[i]->Incrementindex ();
	    
	      //increment the index because now the ballots belng to the next pref
	      bool new_cand_assigned = false;
	    
	      //if the ballot is now invalid, we do not need to redistribute
	      if (!ballots[i]->Valid ())
	      {
		
audit.auditPrint ("Ballot" + std::to_string (i) +
				   " is now exhausted");
	      
}
	    
 
while (ballots[i]->Valid () && !new_cand_assigned)
	      {
		
int
		  newPref = ballots[i]->GetCurrentPref ();
		
if (candidates[newPref]->CheckInRace ())
		  
 
		  {
		    audit.auditPrint ("Ballot " + std::to_string (i) +
				      " is being given to " +
				      candidates[newPref]->GetName ());
		    
std::vector < int >
		      new_pref_myBallots =
		      candidates[newPref]->GetMyBallots ();
		    
new_pref_myBallots[i] = 1;
		    
candidates[newPref]->SetMyBallots (new_pref_myBallots);
		    
new_cand_assigned = true;
		  
}
		
		else
		  {
		    
ballots[i]->Incrementindex ();
		  
}
		
if (!ballots[i]->Valid ())
		  {
		    
audit.auditPrint ("Ballot" + std::to_string (i) +
				       "is now exhausted");
		  
}
	      
 
}
	  
}
	
i = i + 1;
      
}
  
 
}
  
	/**
         * @brief A function that adds a ballot to the ballot vector given a ballot object
         * @param[in] newBallot a ballot object to be added
         *
         */ 
    void
  AddBallot (IRVBallot * newBallot)
  {
    
      // This functions adds a new ballot at the end of the ballots vector
      ballots.push_back (newBallot);
  
} 
 
    //TransformVote takes an integer array, vote, and converts it into a transformed vote array, which
    // is used to instantiate the irv_ballot class
	/**
         * @brief A function given a vote vector transforms it and returns the transformed vector
         * @param[in] vote a vector containing the votes
         *
         */ 
  std::vector < int >
  TransformVote (std::vector < int >vote)
  {
    
std::vector < int >
      transformedVoteold;
    
int
      x;
    
 
for (int i = 0; i < vote.size (); i++)
      
      {
	
x = find (vote, vote.size (), i + 1);
	
transformedVoteold.push_back (x);
      
} 
 
 
return transformedVoteold;
  
}
  
	/**
         * @brief A function given a ballot (vector vote) and id of said ballot generates a ballot object 
         * @param[in] vote vector of the vote i.e <1,2,3,4> 
         * @param[in] id the id for the said vote (id of the line)
         *
         */ 
    
void
  GenerateBallots (std::vector < int >vote, int id) 
  {
    
      //skip to the line where the ballot data is stored
    
 
std::vector < int >
      transformedVote;
    
transformedVote = TransformVote (vote);
    
 
IRVBallot * newBallot_ =
      new IRVBallot (id, transformedVote, numCandidates);
    
AddBallot (newBallot_);
  
 
 
} 

	/**
         * @brief This function invalidates a balllot in IRV if num cands ranked in a ballot is less than 50 pc of total candidates. It also returns the vector of invalidated ballots.  
         *
         */ 

std::vector < int > InvalidateBallots () 
  {
    
    
 
std::vector < int > invalidatedballots;
    
for (int ballotno = 0; ballotno < ballots.size (); ballotno++)
	  {	  

		  if (ballots[ballotno]->GetVoteSize()/double(candidates.size())<0.5)
		  {
			  	invalidatedballots.push_back (ballotno);
				ballots[ballotno]->MakeInvalid();
		  }
	  }

 return invalidatedballots;
 
} 



	/**
         * @brief A function given a candidate name and candiate party with id generated a IRVcandidate object to be added to candidates vector
         * @param[in] cand is the candidate name 
         * @param[in] p is the party of said candidate
         * @param[in] id id of the said candidate
         *
         */ 
    void
  GenerateCandidates (string cand, char p, int id)
  {
    
IRVCandidate * new_candidate = new IRVCandidate (cand, p, id);
    
candidates.push_back (new_candidate);
  
} 
	/**
         * @brief A function that updates each ballots for each of thier respective candidates
         * 
         */ 
    
void
  UpdateCandidates ()
  {
    
int
      j = 0;
    
 
while (j < candidates.size ())
      
      {
	
std::vector < int >
	  new_candidate_myBallots;
	
int
	  i = 0;
	
	  //whenever ballots[i] belong to a candidate, make their myBallots[i]=1
	  while (i < ballots.size ())
	  {
	    
if (ballots[i]->Valid ())
	      
	      {
		
if (ballots[i]->GetCurrentPref () == j)
		  
		  {
		    
new_candidate_myBallots.push_back (1);
		  
}
		
		else
		  
		  {
		    
new_candidate_myBallots.push_back (0);
		  
}
	      
 
}
	    
	    else
	      
	      {
		
new_candidate_myBallots.push_back (0);
	      
}
	    
i = i + 1;
	  
}
	
candidates[j]->SetMyBallots (new_candidate_myBallots);
	
 
 
j = j + 1;
      
}
  
 
}

 
private:
int
    numCandidates;
  
std::vector < IRVBallot * >ballots;
  
std::vector < IRVCandidate * >candidates;
  
IRVCandidate winner;
  
Audit audit;

std::string invalidFile;

 
};


