#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"

int main() {

    bool stay_in_the_program = true;
    std::vector<std::vector<std::string>> database;
    std::vector<std::vector<std::string>> *db_p = &database;
    std::vector<std::vector<int>> char_lengths;
    std::vector<std::vector<int>> *cl_p = &char_lengths;

    std::cout << "Welcome to Mini Database Manager 3.1!";

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

            update_char_lengths(db_p, cl_p);

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

                //check that the user doesn't attempt to modify a row or a column out of the database's reach
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

                update_char_lengths(db_p, cl_p);

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

            std::vector<int> column_numbers;
            std::vector<int> row_numbers;

            for (int i = 1; i <= database.size(); i++) {

                column_numbers.push_back(i);

            }

            for (int i = 1; i <= database.at(0).size(); i++) {

                row_numbers.push_back(i);

            }

            std::cout << "\n";
            std::cout << "    ";

            //display the column numbers
            for (int ia = 0; ia < column_numbers.size(); ia++) {

                std::cout << column_numbers.at(ia);

                std::string conv_cur_cn_cl = std::to_string(column_numbers.at(ia));
                int cur_cn_cl = conv_cur_cn_cl.size();
                int max_cn_cl = *std::max_element(char_lengths.at(ia).begin(), char_lengths.at(ia).end());
                add_spaces(cur_cn_cl, max_cn_cl, 2);

            }

            std::cout << "\n\n";

            //display the row numbers
            for (int ib = 0; ib < row_numbers.size(); ib++) {

                std::cout << row_numbers.at(ib);

                std::string conv_cur_rn_cl = std::to_string(row_numbers.at(ib));
                int cur_rn_cl = conv_cur_rn_cl.size();
                int max_rn_cl = *std::max_element(row_numbers.begin(), row_numbers.end());
                add_spaces(cur_rn_cl, max_rn_cl, 3);

                //output row items
                for (int ia = 0; ia < database.size(); ia++) {

                    std::cout << database.at(ia).at(ib);

                    int cur_cl = char_lengths.at(ia).at(ib);
                    int max_cl = *std::max_element(char_lengths.at(ia).begin(), char_lengths.at(ia).end());
                    add_spaces(cur_cl, max_cl, 2);

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

    return 0;

}
