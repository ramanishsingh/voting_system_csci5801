/**
 * @file election.h
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#ifndef SRC_ELECTION_H_
#define SRC_ELECTION_H_

#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The election header for the IRV and OPLV election classes.
 * 
 */

class Election{

    protected:
        // class attributes
        std::string typeOfElection;
        int totalBallots;
        int totalCandidates;

    public: 
        // election methods

        /** 
         * @brief this virtual method will be defined by the IRV and OPLV classes.
         * @brief It drives the election process for them individually.
         * 
         * @param[in] filename needed to read csv file
         */
        virtual int FindWinner(std::string filename) = 0;

        /**
         * @brief gets the election type
         */
        std::string GetTypeofElection() {return typeOfElection;}

        /**
         * @brief get the total number of candidates in the election
         */
        int GetTotalCandidates(){return totalCandidates;}

        /**
         * get the number of ballots in the election
         */
        int GetTotalBallots() {return totalBallots;}
        void SetTotalBallots(int num) { totalBallots=num;}

};

#endif // SRC_ELECTION_H_