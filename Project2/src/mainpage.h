/**
 * @file mainpage.h
 *
 */
#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/*! \mainpage V-Pal Index Page
 *
 * \section intro_sec Introduction
 *
 * Welcome to the main page of this documentation of V-Pal, the election result calculator.
 *
 * \section install_sec Setup
 *
 * \subsection step1 Step 1: Downloading the Software
 *
 * To start, download the software from this link:
 *
 * https://github.umn.edu/umn-csci-5801-S21-002/repo-Team17
 *
 * \subsection step2 Step 2: Creating an Executable
 *
 * To compile the project, open the terminal, navigate to repo-Team17/Project2/src/, and
 * type "make". This will compile the executable 'main' in the current directory:
 *
 * \subsection step3 Step 3: Running the Program
 *
 * The program can be run with this command:
 *
 * ./main
 *
 * The program will prompt for a csv file. When you input the file, the program will
 * ask if you would like to input another csv file. You may either input another
 * csv file, or input "0" to move on. Once you input "0", the program will
 * automatically calculate the results, displaying the winner(s) to the screen.
 * A summary file will be created, along with an audit file detailing
 * the exact calculations.
 *
 * \section documentation Generating Documentation
 * \subsection doc1 HTML Documentation
 * 
 * All of the code is compatible with doxygen, so users can generate readable html documentation. 
 * The user is first required to have doxygen for the documentation and GraphViz to generate class diagrams.
 * 
 * Navigate to repo-Team17/Project2/documentation and run "doxygen Doxyfile" in the terminal. Once the program 
 * finishes, navigate into the new html/ folder, then open index.html.
 * 
 * \subsection doc2 Code Documentation
 * 
 * Alongside the doxygen documentation, the code is readable and has comments for maximum understandability.
 * 
 * \section tests Running Tests
 * \subsection step4 Step 1 : Creating the testing executable
 *
 * Navigate to the folder repo-Team17/Project2/testing/, and type "make" in the terminal. It will create a file named "unittest" in the folder.
 * \subsection step5 Step 2: Running the unit test
 *
 * Run the unit test using the following command: 
 * 
 * "./unittest"
 * 
 * The results will be presented on the screen. 
 *
 */
#endif  // SRC_MAINPAGE_H_
