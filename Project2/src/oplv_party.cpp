/**
 * @file oplv_party.cpp
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <iostream>
#include "oplv_candidate.cpp"
#include "audit.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for a single OPLVParty.
 * 
 */
class OPLVParty {
    public:
        /**
         * @brief Constructor for an OPLV party with a name.
         *
         * @param[in] name_ Name of party
         */    
        OPLVParty(std::string name_) {
            name = name_;
            seatsWon = 0;
            remainingVotes = 0;
        }

        /**
         * @brief Adds candidate to the party.
         *
         * @param[in] newCandidate New candidate
         */
        void AddCandidate(OPLVCandidate * newCandidate) {
            candidates.push_back(newCandidate);
        }

        /**
         * @brief Gets name of party.
         *
         */
        std::string GetName() {
            return name;
        }

        /**
         * @brief Gets number of seats won by party.
         *
         */
        int GetSeats() {
            return seatsWon;
        }

        /**
         * @brief Gets remaining votes for party.
         *
         */        
        int GetRemainingVotes() {
            return remainingVotes;
        }

        /**
         * @brief Gets number of candidates in the party.
         *
         */        
        int GetNumCandidates() {
            return candidates.size();
        }

        /**
         * @brief Sets the party's remaining votes to a new count.
         *
         * @param[in] remainingVotes_ New remaining votes
         */        
        void SetRemainingVotes(int remainingVotes_) {
            remainingVotes = remainingVotes_;
        }

        /**
         * @brief Sets the number of seats the party won.
         *
         * @param[in] seatsWon_ Amount of seats won
         */        
        void SetSeatsWon(int seatsWon_) {
            seatsWon = seatsWon_;
        }

        /**
         * @brief Increments seats won by party by 1.
         *
         */        
        void AddSeat() {
            seatsWon++;
        }

        /**
         * @brief Initializes remaining votes to the sum of all candidate's votes in the party.
         *
         */        
        void InitializeRemainingVotes() {
            // set remaininVotes to total # of votes for party
            int totalVotes = 0;
            for (auto it = candidates.begin(); it != candidates.end(); it++) {
                int canvotes = (*it)->GetNumVotes();
                totalVotes += canvotes;
            }

            this->SetRemainingVotes(totalVotes);
        }

        /**
         * @brief Updates the rank of each candidate based on their total votes.
         *
         */        
        void UpdateRank(Audit audit) {
            // Set rank of candidates based on num votes
            // The ranks array will keep track of candidates based on
            //   the number of votes, highets to lowest.
            // Ex. ranks = [2,0,1] -> can[2].rank = 1, can[0].rank = 2, can[1].rank = 3
            // for i, candidates[ranks[i]].setrank(i + 1)
            int ranks[candidates.size()];
            
            // Initialize ranks to -1 as default value
            for(int i = 0; i < candidates.size(); i++) ranks[i] = -1;
            
            // Loop through each candidate
            int i = 0;
            for (auto it = candidates.begin(); it != candidates.end(); it++) {
                int votes = candidates[i]->GetNumVotes();

                // Insert candidate into ranking array
                for(int j = 0; j < candidates.size(); j++) {
                    if (ranks[j] == -1) {
                        ranks[j] = i;
                        break;
                    }

                    // Current candidate's votes > rank[j]'s votes                    
                    else if(candidates[ranks[j]]->GetNumVotes() < votes) {
                        int temp = ranks[j];
                        ranks[j] = i;
                        j++;

                        // Move each rank down the array by 1
                        while(j < candidates.size()) {
                            int temp2 = ranks[j];
                            ranks[j] = temp;
                            temp = temp2;
                            j++;
                        }

                        break;
                    }
                }
                i++;
            }

            // Update ranks
            audit.auditPrint("\nIn party "+GetName()+":");
            for(int i = 0; i < candidates.size(); i++) {
                candidates[ranks[i]]->SetCurPartyRank(i + 1);
                audit.auditPrint(candidates[ranks[i]]->GetName()+" has rank "+std::to_string(candidates[ranks[i]]->GetCurPartyRank())+".");
            }

            // Award seats
            for(int i = 0; i < candidates.size(); i++) {
                candidates[i]->AwardSeat(seatsWon);
            }
        }

    private:
        std::vector<OPLVCandidate*> candidates;
        int seatsWon;
        std::string name;
        int remainingVotes;
};