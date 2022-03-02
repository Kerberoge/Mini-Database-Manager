#include <iostream>
#include <vector>

//functions used to check that the user doesn't attempt to change a row or column out of the database's reach
int column_checker (int a, int b) {

    //a = column, b = database.size()
    if (a <= b && a > 0) {
        return true;
    } else {
        return false;
    }

}

int row_checker (int a, int b) {

    //a = row, b = database.at(0).size()
    if (a <= b && a > 0) {
        return true;
    } else {
        return false;
    }

}

int main() {

    bool stay_in_the_program = true;
    std::vector<std::vector<std::string>> database;

    std::cout << "Welcome to Mini Database Manager 3.0!";

    while (stay_in_the_program == true) {

        std::string userchoice;

        std::cout << "\n\nPlease select an action by typing the corresponding number:\n";

        if (database.size() == 0) {
            //database is empty
            std::cout << "1. Initiate database\n";
            std::cout << "2. Exit the program\n";

        } else {
            //database is not empty
            std::cout << "1. Change amount of rows and columns\n";
            std::cout << "2. Change a current value\n";
            std::cout << "3. Display a value\n";
            std::cout << "4. Display the whole database as a table\n";
            std::cout << "5. Exit the program\n";

        }

        std::cin >> userchoice;

        if (userchoice == "1" || userchoice == "one") {

            //change amount of columns and rows, or initiate database
            int columns_amount;
            int rows_amount;

            std::cout << "Please enter the desired amount of columns (integers only): ";
            std::cin >> columns_amount;
            std::cout << "Please enter the desired amount of rows (integers only): ";
            std::cin >> rows_amount;

            //database must have at least 1 column and 1 row
            while (columns_amount < 1 || rows_amount < 1) {

                std::cout << "Database must have at least 1 column and 1 row. Please try again.\n";
                std::cout << "Please enter the desired amount of columns (integers only): ";
                std::cin >> columns_amount;
                std::cout << "Please enter the desired amount of rows (integers only): ";
                std::cin >> rows_amount;

            }

            //adjust number of columns
            database.resize(columns_amount);

            //adjust number of rows
            for (int i = 0; i < columns_amount; i++) {

                database.at(i).resize(rows_amount, "0");

            }

            std::cout << "Size changed successfully. The database now has " << database.size() << " columns and " << database.at(0).size() << " rows.\n";

        } else if (userchoice == "2" || userchoice == "two") {

            //option 2 has two different actions, we need to differentiate between them
            if (database.size() == 0) {

                //exit the program
                stay_in_the_program = false;

            } else {

                //change a current value
                int column;
                int row;
                std::string newvalue;

                std::cout << "Please enter the column number of the value you wish to change: ";
                std::cin >> column;
                std::cout << "Please enter the row number of the value you wish to change: ";
                std::cin >> row;

                //check that the user doesn´t attempt to modify a row or a column out of the database's reach
                while (column_checker(column, database.size()) == false || row_checker(row, database.at(0).size()) == false) {

                    std::cout << "The database only has " << database.size() << " columns and " << database.at(0).size() << " rows. Please ensure that the value you wish to change is inside the database's reach.\n";
                    std::cout << "Please enter the column number of the value you wish to change: ";
                    std::cin >> column;
                    std::cout << "Please enter the row number of the value you wish to change: ";
                    std::cin >> row;

                }

                std::cout << "Please enter the new value: ";
                std::cin.ignore(); //this is to prevent std::getline() from not waiting for user input
                std::getline(std::cin, newvalue);
                database.at(column - 1).at(row - 1) = newvalue;
                std::cout << "The value on column " << column << ", row " << row << " has been altered. It is now '" << database.at(column - 1).at(row - 1) << "'.\n";

            }

        } else if (userchoice == "3" || userchoice == "three") {

            //view a variable
            int column;
            int row;

            std::cout << "Please enter the column number of the value you wish to view (integers only): ";
            std::cin >> column;
            std::cout << "Please enter the row number (integers only): ";
            std::cin >> row;

            while (column_checker(column, database.size()) == false || row_checker(row, database.at(0).size()) == false) {

                    std::cout << "The database only has " << database.size() << " columns and " << database.at(0).size() << " rows. Please ensure that the value you wish to view is inside the database's reach.\n";
                    std::cout << "Please enter the column number of the value you wish to view: ";
                    std::cin >> column;
                    std::cout << "Please enter the row number of the value you wish to view: ";
                    std::cin >> row;

            }

            std::cout << "The value on column " << column << ", row " << row << " is '" << database.at(column - 1).at(row - 1) << "'.\n";

        } else if (userchoice == "4" || userchoice == "four") {
            //display the whole database as a table

            std::cout << "\n";

            for (int i = 1; i <= database.size(); i++) {
            //display the column numbers

                std::cout << "    " << i;

            }

            std::cout << "\n\n";

            for (int ia = 1; ia <= database.at(0).size(); ia++) {
            //display the row numbers

                std::cout << ia << "   ";

                //the for loop for outputting row items comes below
                for (int ib = 0; ib < database.size(); ib++) {

                    std::cout << database.at(ib).at(ia - 1) << "    ";

                }

                std::cout << "\n";

            }

        } else if (userchoice == "5" || userchoice == "five") {

            //exit the program
            stay_in_the_program = false;

        } else {

            std::cout << "Invalid option.\n";

        }
    }
}
