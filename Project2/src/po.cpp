/**
 * @file po.cpp
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
#include "audit.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "po_candidate.cpp"
  
using std::string;


/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for a PO election.
 * 
 */
class PO : public Election {
    private:
        std::vector <POCandidate *> candidates;
        Audit audit;
        POCandidate winner;

    public:
        /**
         * @brief Constructor for a PO election with an audit object.
         *
         * @param[in] audit_ Audit object
         */
        PO(Audit audit_) {
            typeOfElection = "PO";
            totalBallots = 0;
            totalCandidates = 0;
            audit = audit_;

        }

        /**
         * @brief Function to calculate the winner of the PO election.
         *
         * @param[in] filename Name of csv file
         */
        int FindWinner(std::vector<string> & files) {
            //loop through each file
            int numSeats = 0;
            for(int idx = 0; idx < files.size(); idx++){
                // Parse csv
                std::ifstream file(files[idx]);
                if(file.is_open()) {
                    std::string data;
                    // Ignore first line
                    std::getline(file, data);
                    audit.auditPrint("Processing file number: "+std::to_string(idx));
                    audit.auditPrint("Election type: "+data);

                    // Number of candidates
                    std::getline(file, data);
                    totalCandidates = std::stoi(data);
                    audit.auditPrint("Number of candidates: "+std::to_string(totalCandidates));


                    // Get candidates
                    std::getline(file, data);
                    std::string candname = "";
                    char candparty;
                    int j = 0;
                    // Loop for each candidate
                    for(int i = 0; i < totalCandidates; i++){
                        // Loop through the string
                        for (j; j < data.length(); j++) {
                            // Skip left bracket
                            if(data[j] == '[') {
                                continue;
                            }

                            // Find party, break to make candidate
                            else if(data[j] == ',') {
                                candparty = data[j+1];
                                break;
                            }

                            // Add to name
                            else {
                                candname = candname + std::string(1, data[j]);
                            }
                        }

                        // Add the candidate
                        audit.auditPrint("Candidate: "+candname+", party: "+std::string(1,candparty));

                        //only add new candidates if the file is the first file being processed from vector
                        //in order to not make new candidate objects that have already been created
                        if(idx == 0){
                            AddCandidate(new POCandidate(candname, candparty));
                        }

                        // Clear name
                        candname = "";

                        // Skip to next candidate
                        j += 4;
                    }

                    // Get number of seats
                    std::getline(file, data);
                    numSeats = std::stoi(data);
                    audit.auditPrint("Number of seats: "+std::to_string(numSeats));

                    // Get number of ballots (maybe not needed?)
                    std::getline(file, data);
                    totalBallots += std::stoi(data);
                    int cur_numBallot = std::stoi(data);
                    audit.auditPrint("Number of ballots: "+std::to_string(cur_numBallot));

                    // Loop through all the ballots;
                    audit.auditPrint("\nAwarding votes to candidates:");
                    while(std::getline(file, data)) {
                        // Check which candidates get the vote
                        for(int i = 0; i < totalCandidates; i++) {
                            if(data[i] != ',') {
                                candidates[i]->AddVote();
                                audit.auditPrint(candidates[i]->GetName()+" received a vote.");
                                break;
                            }
                        }
                    }

                    audit.auditPrint("\nObtained all info from "+files[idx]+", closing file.\n");

                    // Close csv
                    file.close();
                }
                else {
                    audit.auditPrint("Error: csv file name is incorrect.");
                    return 0;
                }
            } // END OF LOOP PROCESSING BALLOTS FROM THE FILES

            audit.auditPrint("Total number of ballots obtained from all files: "+std::to_string(totalBallots));

            ////////////////////////////////////////////////////////////////////////////////////////////////////

            // FIND OUT THE WINNER

            ////////////////////////////////////////////////////////////////////////////////////////////////////

            std::vector < int > votes;
            for (auto it = candidates.begin (); it < candidates.end (); it++)
            
	        {
                votes.push_back ((*it)->GetNumVotes ());
            }


            // Initialize V
	        std::vector < int > V;
	
            for (int i = 0; i < candidates.size (); i++)
	        {
                V.push_back (i);
            } 

            // Sort V based on votes
	        sort (V.begin (), V.end (),[&](int i, int j)
		    {
		        return votes[i] < votes[j];
		    }
	            );
            bool tied=false;
            if (V[totalCandidates - 2]==V[totalCandidates - 1]){
                tied=true;
            }

            if (tied){
                    int winnerIndex =TieBreaker();
                    winner = (*candidates[winnerIndex]);
            }

            else {
            int winnerIndex = V[totalCandidates - 1];
            
            winner = (*candidates[winnerIndex]);
            }
  
            std::cout << "The winner is " << winner.GetName()<<"\n";
            std:: cout << "Following are the vote percentages \n";

            int max_votes= totalBallots;

            for (int it =0 ; it < candidates.size(); it++)
            
	        {
                POCandidate cand;
                cand=*candidates[it];
                double perc;
                perc= (float) cand.GetNumVotes()/(float) totalBallots;
                std::cout << cand.GetName()<< " got "  << perc << " percent votes\n";
            }

            return 0;
        }

        // this function resolves any ties in the voting system
	    /**
         * @brief A function that resolved any ties if there are any during the process of po election
         *
         *
         */ 
        int TieBreaker ()
        {   
            std::vector < int > votes;
            for (auto it = candidates.begin (); it < candidates.end (); it++)
            
	        {
                votes.push_back ((*it)->GetNumVotes ());
            }
            // Initialize V
	        std::vector < int > V;
	
            for (int i = 0; i < candidates.size (); i++)
	        {
                V.push_back (i);
            } 

            // Sort V based on votes
	        sort (V.begin (), V.end (),[&](int i, int j)
		    {
		        return votes[i] < votes[j];
		    }
	            );

 
            int cand_total = candidates.size ();
    
            std::vector < int > cands;
    
 
            int pq = 0;
    
 
            while (pq < cand_total)
            {
	
 
                if (candidates[pq]->GetNumVotes()==V[cand_total-1])
	            {
	    
                    cands.push_back (pq);
	  
 
                }
	
                pq = pq + 1;
      
            }
    
 
            srand ((unsigned int) time (NULL));
    
            int rand_num = rand () % cands.size ();
    
           return cands[rand_num];;
  
 
            }

        /**
         * @brief Add a new candidate to the election
         *
         * @param[in] newcandidate New candidate
         */

        // Need to check if candidate already exists
        void AddCandidate(POCandidate * newcandidate) {
            candidates.push_back(newcandidate);
        }
         /**
         * @brief A function that calculates the percentage of votes given a candidate object
         *
         *
         */ 
        int CanPercent(POCandidate cand,int ttlNumVotes){
            int percentage = 100 * (cand.GetNumVotes())/ttlNumVotes;
        return percentage;
        }

        /**
         * @brief Get all candidates in PO election
         *
         */
        std::vector <POCandidate *> GetCandidates() {
            return candidates;
        }

        /**
         * @brief Get winning candidate in PO election
         *
         */
        POCandidate GetWinner() {
            return winner;
        }

        /**
         * @brief Create media summary file
         *
         * @param[in] filename to create media summary file and write results to it
         */
        void MediaFile(string filename){
            //open up file to write election summary to it
            std::fstream file;  
            file.open(filename,std::fstream::app);

            file << "This media file is for the PO election.\n";
            file << "There were a total of " << std::to_string(totalBallots) << " ballots processed in this session.\n";
            file << "The total number of candidates in this election is: " << std::to_string(totalCandidates) << ".\n";
            file << "Here are the results:\n";

            //print the candidates and their information to the media summary file
            for(auto current = candidates.begin(); current != candidates.end(); current++){
                file  << (*current)->GetName() << "(" << (*current)->GetParty() << ") " << " won " << std::to_string((*current)->GetNumVotes()) << " votes.\n";
            }

            file.close();
        }
};