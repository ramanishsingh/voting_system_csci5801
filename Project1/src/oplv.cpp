/**
 * @file oplv.cpp
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "election.h"
#include "oplv_party.cpp"
#include "audit.h"


/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for an OPLV election.
 * 
 */
class OPLV : public Election {
    private:
        std::vector <OPLVCandidate *> candidates;
        std::vector <OPLVCandidate *> indCandidates;
        std::vector <OPLVCandidate *> winners;
        std::vector <OPLVParty *> parties;
        int numParties;
        int quota;
        int numSeats;
        int seatsAllocated;
        Audit audit;

    public:
        /**
         * @brief Constructor for an OPLV election with an audit object.
         *
         * @param[in] audit_ Audit object
         */
        OPLV(Audit audit_) {
            numParties = 0;
            quota = 0;
            numSeats = 0;
            seatsAllocated = 0;
            typeOfElection = "";
            totalBallots = 0;
            totalCandidates = 0;
            audit = audit_;
        }

        /**
         * @brief Function to calculate the winner of the OPLV election.
         *
         * @param[in] filename Name of csv file
         */
        int FindWinner(std::string filename) {
            // Parse csv
            std::ifstream file(filename);
            if(file.is_open()) {
                std::string data;
                // Ignore first line
                std::getline(file, data);
                audit.auditPrint("Election type: "+data);

                // Number of candidates
                std::getline(file, data);
                int numCandidates = std::stoi(data);
                //std::cout << "numCandidates: " << numCandidates << "\n";
                audit.auditPrint("Number of candidates: "+std::to_string(numCandidates));


                // Get candidates
                std::getline(file, data);
                std::string candname = "";
                char candparty;
                int j = 0;
                // Loop for each candidate
                for(int i = 0; i < numCandidates; i++){
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
                    //std::cout<<"New candidate: "<<candname<<", "<<candparty<<"\n";
                    audit.auditPrint("Candidate: "+candname+", party: "+std::string(1,candparty));
                    AddCandidate(new OPLVCandidate(candname, candparty));

                    // Clear name
                    candname = "";

                    // Skip to next candidate
                    j += 4;
                }

                // Get number of seats
                std::getline(file, data);
                numSeats = std::stoi(data);
                //std::cout << "numSeats: " << numSeats << "\n";
                audit.auditPrint("Number of seats: "+std::to_string(numSeats));

                // Get number of ballots (maybe not needed?)
                std::getline(file, data);
                int numBallots = std::stoi(data);
                //std::cout << "numBallots: " << numBallots << "\n";
                audit.auditPrint("Number of ballots: "+std::to_string(numBallots));

                // Calculate the quota
                CalculateQuota(numBallots, numSeats);
                audit.auditPrint("Quota: "+std::to_string(quota));

                // Loop through all the ballots;
                audit.auditPrint("\nAwarding votes to candidates:");
                while(std::getline(file, data)) {
                    // Check which candidates get the vote
                    for(int i = 0; i < numCandidates; i++) {
                        if(data[i] != ',') {
                            candidates[i]->AddVote();
                            audit.auditPrint(candidates[i]->GetName()+" received a vote.");
                            break;
                        }
                    }
                }

                audit.auditPrint("\nObtained all info from "+filename+", closing file.");

                // Close csv
                file.close();
            }
            else {
                //std::cout << "Error: csv file name is incorrect.\n";
                audit.auditPrint("Error: csv file name is incorrect.");
                return 0;
            }
            
            // Calculate number of seats per party/independent
            audit.auditPrint("\nCalculating seats for parties and candidates (seats = votes / quota):");
            for (auto it = parties.begin(); it != parties.end(); it++) {
                // Set party votes to all candidate's votes
                (*it)->InitializeRemainingVotes();
                audit.auditPrint((*it)->GetName()+" has "+std::to_string((*it)->GetRemainingVotes())+" votes. "
                  +std::to_string((*it)->GetRemainingVotes())+" / "+std::to_string(quota)+" = "+std::to_string((*it)->GetRemainingVotes()/quota));

                // Give party initial seats
                (*it)->SetSeatsWon((*it)->GetRemainingVotes() / quota);
                seatsAllocated += (*it)->GetRemainingVotes() / quota;
                audit.auditPrint((*it)->GetName()+" received "+std::to_string((*it)->GetSeats())+" seats.");

                // Assign remaining votes to party
                (*it)->SetRemainingVotes((*it)->GetRemainingVotes() % quota);
                audit.auditPrint("After first allocation of seats, "+(*it)->GetName()+" has "+std::to_string((*it)->GetRemainingVotes())+" votes left.");
            }

            // output candidates's votes and party votes - debugging
            // for (auto it = candidates.begin(); it != candidates.end(); it++) {
            //     std::cout<<(*it)->GetName() << ": "<<(*it)->GetNumVotes()<<"\n";
            // }
            // for (auto it = parties.begin(); it != parties.end(); it++) {
            //     std::cout<<(*it)->GetName()<<": "<<(*it)->GetRemainingVotes()<<"\n";
            // }

            // Calculate seats for independent
            for (auto it = indCandidates.begin(); it != indCandidates.end(); it++) {
                // If beats quota, award seat
                if(((*it)->GetNumVotes() / quota) >= 1) {
                    (*it)->SetWonSeat();
                    audit.auditPrint("Independent "+(*it)->GetName()+" has won a seat.");
                    seatsAllocated++;
                }

                // Either way, set votes to modulus of quota
                (*it)->SetNumVotes((*it)->GetNumVotes() % quota);
                audit.auditPrint("After first allocation of seats, "+(*it)->GetName()+" has "+std::to_string((*it)->GetNumVotes())+" votes left.");
            }

            audit.auditPrint("\nAfter first allocation of seats, there are "+std::to_string(numSeats-seatsAllocated)+" seats left to allocate.");

            // Check for more seats
            while(seatsAllocated < numSeats) {
                audit.auditPrint("\nAllocating rest of seats:");
                // For biggest party/independent, add seat

                // If party is bigger than independent
                bool biggerParty = false;
                // Highest party
                OPLVParty* bigparty = NULL;
                // Highest independent
                OPLVCandidate* bigcand = NULL;

                for (auto it = parties.begin(); it != parties.end(); it++) {
                    if(bigparty == NULL) {
                        bigparty = (*it);
                    }
                    else if(bigparty->GetRemainingVotes() < (*it)->GetRemainingVotes()) {
                        bigparty = (*it);
                    }
                    //std::cout << "bigparty: " << bigparty->GetName() << "\n";
                }
                audit.auditPrint("Largest party is "+bigparty->GetName()+" with "+std::to_string(bigparty->GetRemainingVotes())+" votes.");

                // Calculate seats for independent
                for (auto it = indCandidates.begin(); it != indCandidates.end(); it++) {
                    if(bigcand == NULL) {
                        bigcand = (*it);
                    }
                    else if(bigcand->GetNumVotes() < (*it)->GetNumVotes()) {
                        bigcand = (*it);
                    }
                    //std::cout << "bigcand: " << bigcand->GetName() << "\n";
                }

                // Set either party or candidate's seat to won, set their votes to 0
                if(bigcand == NULL) {
                    bigparty->AddSeat();
                    audit.auditPrint("No independents, "+bigparty->GetName()+" wins a seat.");
                    audit.auditPrint("Setting "+bigparty->GetName()+" to zero votes.");
                    bigparty->SetRemainingVotes(0);
                }
                else if(bigparty->GetRemainingVotes() > bigcand->GetNumVotes()){
                    bigparty->AddSeat();
                    audit.auditPrint("Largest independent is "+bigcand->GetName()+" with "+std::to_string(bigcand->GetNumVotes())+" votes.");
                    audit.auditPrint(bigparty->GetName()+" has more votes and wins a seat.");
                    audit.auditPrint("Setting "+bigparty->GetName()+" to zero votes.");
                    bigparty->SetRemainingVotes(0);
                }
                else {
                    bigcand->SetWonSeat();
                    audit.auditPrint("Largest independent is "+bigcand->GetName()+" with "+std::to_string(bigcand->GetNumVotes())+" votes.");
                    audit.auditPrint(bigcand->GetName()+" has more votes and wins a seat.");
                    audit.auditPrint("Setting "+bigcand->GetName()+" to zero votes.");
                    bigcand->SetNumVotes(0);
                }

                // Increment won seats, reset vars
                seatsAllocated++;
                bigparty = NULL;
                bigcand = NULL;
            }
            
            // Parties will award seats to candidates
            for (auto it = parties.begin(); it != parties.end(); it++) {
                (*it)->UpdateRank(audit);
            }

            // Output seats won by party
            audit.auditPrint("");
            for (auto it = parties.begin(); it != parties.end(); it++) {
                audit.auditPrint((*it)->GetName()+" won "+std::to_string((*it)->GetSeats())+" seats.");
            }

            // Output winners to audit
            audit.auditPrint("\nElection winners:");
            for (auto it = candidates.begin(); it != candidates.end(); it++) {
                if((*it)->GetWonSeat()) {
                    audit.auditPrint((*it)->GetName()+" ("+(*it)->GetParty()+")");
                    winners.push_back(*it);
                }
            }

            return 0;
        }

        /**
         * @brief Output all candidates that won a seat.
         *
         */
        void OutputWinners(std::string filename) {
            // Output winners to screen and summary
            std::fstream file;  
            file.open(filename,std::fstream::app);
            
            // Output seats won by party
            std::cout << "Seats won by parties:\n";
            for (auto it = parties.begin(); it != parties.end(); it++) {
                std::cout << (*it)->GetName() << " won " << std::to_string((*it)->GetSeats()) << " seats.\n";
                file  << (*it)->GetName() << " won " << std::to_string((*it)->GetSeats()) << " seats.\n";
            }

            // Output winners
            std::cout << "\nWinners of seats:\n";
            file << "\nWinners of seats:\n";
            for (auto it = candidates.begin(); it != candidates.end(); it++) {
                if((*it)->GetWonSeat()){
                    std::cout << (*it)->GetName() << " (" << (*it)->GetParty() << ")\n";
                    file << (*it)->GetName() << " (" << (*it)->GetParty() << ")\n";
                }
            }

            file.close(); 
        }

        /**
         * @brief Calculate the seat quota for the election.
         *
         * @param[in] ballotnum Number of ballots
         * @param[in] seatnum Number of seats
         */
        int CalculateQuota(int ballotnum, int seatnum) {
            // I believe we do integer division for the quota
            quota = ballotnum / seatnum;
            return quota;
        }

        /**
         * @brief Add a new party to the election
         *
         * @param[in] name_ Name of party
         */
        OPLVParty* AddParty(char name_) {
            std::string partyname;
            if(name_ == 'R') {
                partyname = "Republican";
                OPLVParty* newparty = new OPLVParty(partyname);
                parties.push_back(newparty);
                return newparty;
            }
            else if(name_ == 'D') {
                partyname = "Democrat";
                OPLVParty* newparty = new OPLVParty(partyname);
                parties.push_back(newparty);
                return newparty;
            }
            else if(name_ == 'L') {
                partyname = "Libertarian";
                OPLVParty* newparty = new OPLVParty(partyname);
                parties.push_back(newparty);
                return newparty;
            }
            else if(name_ == 'G') {
                partyname = "Green";
                OPLVParty* newparty = new OPLVParty(partyname);
                parties.push_back(newparty);
                return newparty;
            }
            else {
                OPLVParty* newparty = new OPLVParty(std::string(1, name_));
                parties.push_back(newparty);
                return newparty;
            }
        }

        /**
         * @brief Add a new candidate to the election, and party if applicable.
         *
         * @param[in] newcandidate New candidate
         */
        void AddCandidate(OPLVCandidate * newcandidate) {
            char candparty = newcandidate->GetParty();
            bool addedtoparty = false;

            // If candidate is not independent, add to a party
            if(candparty != 'I') {
                for (auto it = parties.begin(); it != parties.end(); it++) {
                    // Party already exists
                    if ((*it)->GetName()[0] == candparty) {
                        (*it)->AddCandidate(newcandidate);
                        addedtoparty = true;
                        break;
                    }
                }
                // Party doesn't exist
                if(!addedtoparty) {
                    OPLVParty* newparty = AddParty(candparty);
                    newparty->AddCandidate(newcandidate);
                }
            }
            // Candidate is independent, mark as such
            else {
                newcandidate->SetIndependent();
                indCandidates.push_back(newcandidate);
            }
            // Add to candidates vector
            //std::cout <<"Adding candidate\n";
            candidates.push_back(newcandidate);
            addedtoparty = false;
        }

        /**
         * @brief Returns vector of parties.
         *
         */
        std::vector<OPLVParty *> GetParties() {
            return parties;
        }

        /**
         * @brief Returns vector of winning candidates.
         *
         */
        std::vector<OPLVCandidate *> GetWinners() {
            return winners;
        }
};