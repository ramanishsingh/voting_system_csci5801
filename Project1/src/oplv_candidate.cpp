/**
 * @file oplv_candidate.cpp
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
 * @brief The main class for a single OPLVCandidate.
 * 
 */
class OPLVCandidate : public Candidate {
    public:
        /**
         * @brief Constructor for an OPLV candidate with a name and party.
         *
         * @param[in] name_ Name of candidate
         * @param[in] party_ Party of candidate
         */
        OPLVCandidate(std::string name_, char party_) {
            name = name_;
            party = party_;
            curPartyRank = -1;
            numVotes = 0;
            wonSeat = false;
            isIndependent = false;
        }

        /**
         * @brief Gets the candidate's current party rank.
         *
         */
        int GetCurPartyRank() {return curPartyRank;}

        /**
         * @brief Sets the candidate's current party rank.
         *
         * @param[in] newRank New rank of candidate
         */
        void SetCurPartyRank(int newRank) {curPartyRank = newRank;}

        /**
         * @brief Gets the candidate's total votes.
         *
         */
        int GetNumVotes() {return numVotes;}

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

        /**
         * @brief Returns whether the candidate won a seat or not.
         *
         */
        bool GetWonSeat() {return wonSeat;}

        /**
         * @brief Immediately awards seat to candidate
         *
         */
        void SetWonSeat() {wonSeat = true;}

        /**
         * @brief Sets the candidate to be an independent.
         *
         */
        void SetIndependent() {isIndependent = true;}

        /**
         * @brief Awards seat to candidate if their current party rank is high enough.
         *
         * @param[in] neededRank Lowest rank to get seat
         */
        void AwardSeat(int neededRank) {
            // Has better rank than needed, wins seat
            if(curPartyRank <= neededRank) {
                SetWonSeat();
            }
        }
    
    private:
        int curPartyRank;
        int numVotes;
        bool wonSeat;
        bool isIndependent;

};