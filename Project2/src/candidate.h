/**
 * @file candidate.h
 * 
 */
#ifndef SRC_CANDIDATE_H_
#define SRC_CANDIDATE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for a Candidate.
 * 
 */
class Candidate {
    protected:
        std::string name;
        char party;

    public:
        /**
         * @brief Gets the candidate's name.
         *
         */
        std::string GetName() {return name;}

        /**
         * @brief Gets the candidate's party.
         *
         */
        char GetParty() {return party;}

        /**
         * @brief Gets the candidate's current number of votes. This is a pure virtual function.
         *
         */
        virtual int GetNumVotes() = 0;

};

#endif //SRC_CANDIDATE_H_