/**
 * @file po_candidate.cpp
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "candidate.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for a single POCandidate.
 * 
 */
class POCandidate : public Candidate {
    public:
        POCandidate() {
            name = "";
            party = '\0';
            numVotes = 0;
        }
        /**
         * @brief Constructor for a PO candidate with a name and party.
         *
         * @param[in] name_ Name of candidate
         * @param[in] party_ Party of candidate
         */
        POCandidate(std::string name_, char party_) {
            name = name_;
            party = party_;
            numVotes = 0;
        }

        /**
         * @brief Gets the candidate's total votes.
         *
         */
        int GetNumVotes() {return numVotes;}

        /**
         * @brief Gets the candidate's name
         *
         */
        std::string GetName() {return name;}

        /**
         * @brief Increments candidate's total votes by 1.
         *
         */
        void AddVote() {numVotes++;}

        /**
         * @brief Sets the candidate's current number of votes.
         *
         * @param[in] newVotes New votes for candidate
         */
        void SetNumVotes(int newVotes) {numVotes = newVotes;}
    
    private:
        int numVotes;
};