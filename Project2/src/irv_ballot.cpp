/**
 * @file irv_ballot.cpp
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "ballot.cpp"
#include <vector>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for a single IRVBallot.
 * 
 */
class IRVBallot : public Ballot {
    private: 
    
    //Initializing the attributes
        int priorityIndex;
        //int transformedVote[];
        std::vector <int> transformedVote;
        bool validity;
    
    public:
        //Constructor, takes the voterNum_ and transformedVote_ variables and makes an IRVBallot object
        /**
         * @brief Constructor for an IRVBallot with voterNum, transformedVote, numCandidates.
         *
         * @param[in] voterNum_ voterId of the candidate
         * @param[in] transformedVote_ transformed vote, we take the vote of each ballot and transform it into transformed vote
         * @param[in] numCandidates Number of Candidates in the election
         */
        IRVBallot(int voterNum_, std::vector <int> transformedVote_ , int numCandidates)
        {
            voterNum=voterNum_ ;
            for (int i = 0; i < numCandidates; ++i) 
            {
                transformedVote.push_back(transformedVote_[i]) ;
            }
            
            priorityIndex=0 ;
            validity=true ;
        }

        // method to check if the ballot is still valid

        /**
         * @brief Check if the ballot is valid or not
         *
         */
        
        bool Valid() 
        {   
            return validity;
        }

        // when a candidate is eliminated, we need to increment the priority index so the ballot can be
        // transferred to the next candidate in line

        /**
         * @brief Increment the priority index of the ballot
         *
         */
        void Incrementindex()
        {
            priorityIndex=priorityIndex+1;
            if (priorityIndex>=GetVoteSize())
                {
                    validity=false;
                }
        }

        /**
         * @brief Makes the ballot invalid
         *
         */
        void MakeInvalid()
        {
            
            validity=false;
        
        }
        
        // method to get how many preferences are indicated on the ballot by the voter

        /**
         * @brief Get how many preferences are marked by the voter in the ballot
         *
         */

        int GetVoteSize()
        {
            
            int i, count;
            count = 0;
            for (i = 0; i <transformedVote.size()  ; i++)
                if (transformedVote[i] != -1)
                    count++;

            return count;
        }
        
        // method to get the curret preferred candidate in the ballot
        /**
         * @brief Get the current preference of the ballot
         *
         */
        int GetCurrentPref()
        {
            return transformedVote[priorityIndex];
        }

        // returns the priority index of the ballot

        /**
         * @brief Gets the priorityIndex of the ballot
         *
         */

        int GetIndex()
        {
            return priorityIndex;
        }

        /**
         * @brief Gets the transformed vote of the ballot
         *
         */
        std::vector <int> GetTransformedVote()

        {
            return transformedVote;
        }

}; 