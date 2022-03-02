#include <iostream>
#include <vector>

int main() {

    std::vector<std::string> database;
    int userchoice;
    bool stay_in_the_program = true;

    std::cout << "Welcome to Mini Database Manager 1.1!";

    while (stay_in_the_program == true) {

        std::cout << "\n\nPlease select an action by typing the corresponding number:\n";
        std::cout << "1. Change database size (Note: you must first set the database size before being able to view or change variables!)\n";
        std::cout << "2. Change a current value\n";
        std::cout << "3. Display a value\n";
        std::cout << "4. Exit the program\n";
        std::cin >> userchoice;
        std::cout << "\n";

        if (userchoice == 1) {
            //change database size
            int size;

            std::cout << "Please enter the new size of the database (integers only): ";
            std::cin >> size;
            database.resize(size, "0");
            std::cout << "\nSize changed successfully. The database now has " << database.size() << " positions.\n";

        } else if (userchoice == 2) {
            //change a current value
            int index;
            std::string newvalue;

            std::cout << "Please enter the index number of the variable you wish to change (0 is the first variable, integers only): ";
            std::cin >> index;
            std::cout << "Please enter the new value of the variable: ";
            std::cin.ignore(); //this is to prevent std::getline() from not waiting for user input
            std::getline(std::cin, newvalue);
            database.at(index) = newvalue;
            std::cout << "Variable " << index << " has been altered. Its value is now '" << database.at(index) << "'.\n";

        } else if (userchoice == 3) {
            //viewing a variable
            int index;

            std::cout << "Please enter the index number of the variable whose value you wish to view (integers only): ";
            std::cin >> index;
            std::cout << "\nThe value of variable " << index << " is '" << database.at(index) << "'.\n";

        } else if (userchoice == 4) {
            //exit the program
            stay_in_the_program = false;

        } else {
            std::cout << "Invalid option.\n";

        }
    }
}
