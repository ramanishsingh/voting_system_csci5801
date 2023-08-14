/*!
 * The IRVCandidate class inherits the Candidate class.
 * It sets up all of the attributes and methods for a candidate
 * in an IRV election
 * 
*/
/**
 * @file irv_candidate.cpp
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "candidate.h"
#include <vector>
#include <string>
#include <numeric>
using std::string;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief the main class for IRVCandidate
 * 
 */
class IRVCandidate : public Candidate{

    private:
        bool stillInRace;
        int candidateID;
        std::vector <int> myBallots;

    public:
        IRVCandidate() {
            candidateID = 0;
            name = "";
            party = '\0';
            stillInRace = true;
        }
        /**
         * @brief Constructor for an IRV candidate with a name and party and id.
         *
         * @param[in] person Name of candidate
         * @param[in] part  Party of candidate
         * @param[in] id id of the candidate 
         */
        IRVCandidate(std::string person, char part, int id){
            candidateID = id;
            name = person;
            party = part;
            stillInRace = true;
        }

        /**
         * @brief A function that eliminates candidate by set stillInRace to false
         */
        void Eliminate(){
            stillInRace = false;
        }

        /**
         * @brief A function that given vector of ballots sets the ballots for given candidate
         * @param[in] a a vector of the ballot for respective candidate
         */
        void SetMyBallots(std::vector <int> a){
            myBallots=a;
        }

        /**
         * @brief A function checks to see that the candidate is still in the race
         * 
         */
        bool CheckInRace(){
            return stillInRace;
        }

        /**
         * @brief A function that returns the number of votes the candidate 
         * has according to the sum of the ballots that they have where 
         * they are the preferred candidate
         * 
         */
        int GetNumVotes(){
            int sum = std::accumulate(myBallots.begin(), myBallots.end(), 0);
            return sum;
        }
        /**
         * @brief A function that returns the candidateID 
         * 
         */
        int GetCandidateID(){
            return candidateID;
        }

        /**
         * @brief A function that returns a vector of the ballots for respective candidate
         * 
         */
        std::vector<int> GetMyBallots(){
            return myBallots;
        }
};
