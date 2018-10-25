// Inclusion of the appropriate headers
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

// Using the standard namespace to save time and to not have to type std:: before almost everything
using namespace std;

// The main function that will house the user interface and will call every other function
int main(int argc, char *argv[]) {

/*
  // ***NOTE*** The following variable databaseItems is for use in a Linux environment with a shell script
  // This vector will house each filepath for each database entry
	vector<string> databaseItems;

  // This loop assigns each filepath to an element in the vector
	for(unsigned int i = 1; argv[i] != NULL; i++){
		databaseItems.push_back(argv[i]);
	}
// This is here solely for testing to ensure the database was passed in correctly
	for(unsigned int i = 0; i < databaseItems.size(); i++){
		cout << databaseItems[i];
		cout << " ";
	}

	cout << endl;
// End of the Linux environment code
*/

// The following file contains the database information as per a batch file for a Windows environment
// Using the batch file allows the cpcTemp.txt location to not have to be entered manually
	ifstream fileIn;

// This vector of string will hold the filepaths for each database entry
	vector<string> databaseItems;

// This string will take in the filepath from the text file
	string fileName = "";

// This command opens the file
	fileIn.open("cpcTemp.txt");

// This if else statement ensures that the file is opened as expected
	if(fileIn){
		fileIn >> fileName;
	}
// Theoretically, this else should never have to be called but it exists incase some unforseen error happens
	else{
		cout << "FATAL ERROR: cpcTemp.txt file not found, cannot find database, exiting program." << endl;
		return 0;
	}

// This while loop will assign each filepath to a spot in the vector and will end when there are no more filepaths
	while(fileIn){

// This adds the filepath to the vector
		databaseItems.push_back(fileName);

// This takes in a new filepath if there is one or sets fileIn to false which will exit the while loop
		fileIn >> fileName;
	}

// This closes the file properly
	fileIn.close();
/*
// This code is here as a preliminary test to see if reading from the database works at all
// 	this test code continues until the comment: "End of database read-test code"
// Also of note, this test code does not necessarily reflect how the finaly code will function
// 	and was based upon how the preliminary test database was made
	ifstream fileIn2;

	string testStr = "";

// Since Windows puts the directories as entries by themselves, calling a specific place is not recommended
// 	since the first few entries will only be the directories in the database folder. However, when
// 	looking at the entire database comparison, having the directories listed will not pose any issues.
// In fact, having the directories listed first actually helps tremendously in that we can append each
// 	new database filename to the first subdirectory of the database which will likely be for the current year
// The number in "[]" can be changed based on different tests but should not be changed to exceed databaseItems.size()
	fileIn2.open(databaseItems[1].c_str());

//	cout << "\n\nopen" << endl;
//	cout << "\n\n\n" << endl;
	if(fileIn2){
		fileIn2 >> testStr;
	}
	while(fileIn2){
		cout << testStr << " ";
		fileIn2 >> testStr;
	}
	cout << "\n\nclose\n";
	cout << "\n\n" << endl;

	fileIn2.close();
// End of database read-test code
*/

/*
	// This is here solely for testing to ensure the database was passed in correctly
		cout << "\n\n\n" << endl;
		for(unsigned int i = 0; i < databaseItems.size(); i++){
			cout << databaseItems[i];
			cout << " ";
		}

		cout << "\n\n" << endl;
*/

  // The following variables are used to take in the user's prompt for what code to execute
	int userIn = 0;
	string userStr = "";
	char userChar = 'a';

  // This variable is used to loop the user interface to allow continuous use
	bool cont = true;

  // This loop lets the user select their desired function and will loop until the user desires to close the program
	do{

    // This tells the user what each prompt will do and asks the user for their input
	cout << "Please select what you would like to do." << '\n';
	cout << "Enter 1 to compare two code files or excerpts" << '\n';
	cout << "Enter 2 to add a code file to the database" << '\n';
	cout << "Enter 3 to compare a code file to the entire database\n";
	cout << "Enter 4 to leave and close the program: ";

    // Taking in a string ensures that anything the user inputs will be technically valid while also allowing
    //    for error checking against the desired input
	cin >> userStr;

    // Setting the first character as the user's true input since an int should not be compared to a string
	userChar = userStr[0];

    // This turns that character into an int value so that a simple switch case can be used for comparison
    // Subtracting the char value '0' (an int value of 48) will make the char value '1' (an int value of 49)
    //    be an int value of 1, itself, and likewise for any number characters
	userIn = static_cast<int>(userChar - '0');

    // The switch statement evaluates the user's input and determines what the user wants to do; if the user
    //    did not input something that is recognized, an error will display and the user will be prompted to try again
	switch(userIn){
      // This case sets the control for the loop to false so that the program can close
		case 4:
		cont = false;
		break;

      // This case will run the file/text to file/text comparison
		case 1:
      // The output in each case is merely for testing to ensure the UI is working as it should
		cout << "\n\n\n" << endl;
		cout << "File to file comparison done\n" << endl;
		cout << "\n\n\n" << endl;
      // The function below is a placeholder for the actual function that will be called to execute this portion
      //    of the program
//		fileToFile();
		break;

      // This case will run the database addition
		case 2:
      // Output for testing
		cout << "\n\n\n" << endl;
		cout << "Database addition completed\n" << endl;
		cout << "\n\n\n" << endl;
      // The function below is a placeholder for the function to be executed
//		addToDatabase();
		break;

      // This case will run the file/text to database comparison
		case 3:
      // Output for testing
		cout << "\n\n\n" << endl;
		cout << "Code compared to the entire database\n" << endl;
		cout << "\n\n\n" << endl;
      // The function below is just a placeholder
//		compareToDatabase();
		break;

      // The default case prints an error message and prompts the user to input something of the correct format
		default:
		cout << "You did not enter something this system can recognize. Please try again.\n\n" << endl;
	}

    // While the control is true, the user interface will keep asking the user what they would like to do
	}while(cont);

  // This prints a friendly exit message to let the user know the program is closed
	cout << "The program is now closing.\n" << endl;

  // The program is now closed
  return 0;
}
