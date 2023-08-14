/**
 * This is the audit file class where given a filename and you can use Auditprint function
 * to add any string to the auditfile
 * @file audit.h
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#ifndef SRC_AUDIT_H_
#define SRC_AUDIT_H_
#include <string> 
#include <iostream>
#include <fstream>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/** 
 * @brief This is class for Audit
 * 
 */
class Audit{ 
    public: 
        std::string auditFile;
        /** 
        * @brief Function auditPrint that given a string prints to a file obj.auditfile
        * @param[in] buffer A string that will be written inside the auditfile
        */
        void auditPrint(std::string buffer){  
            std::fstream myfile;  
            myfile.open(auditFile,std::fstream::app);
            //Writing the string to the file 
            myfile << buffer << "\n"; 
            //Closing the file 
            myfile.close(); 
        }
};
#endif //SRC_AUDIT_H_