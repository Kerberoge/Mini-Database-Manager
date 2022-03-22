#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"

int main() {
    
    //declare available commands
    std::vector<std::string> cmd_name;
    std::vector<std::string> cmd_description;
    
    cmd_name.push_back("size");
    cmd_description.push_back("Change the current amount of columns and rows");
    
    cmd_name.push_back("edit");
    cmd_description.push_back("Edit a value");
    
    cmd_name.push_back("table");
    cmd_description.push_back("Display all the values of the database in a table");
    
    cmd_name.push_back("clear");
    cmd_description.push_back("Clear the console screen");
    
    cmd_name.push_back("exit");
    cmd_description.push_back("Leave the program");

    bool stay_in_the_program = true;
    std::vector<std::vector<std::string>> database;
    std::vector<std::vector<int>> char_lengths;

    std::cout << "Welcome to Mini Database Manager 4.0!\n" << "Type 'help' for a list of available commands.\n";

    while (stay_in_the_program == true) {

        std::cout << "\033[32m[MDM-shell]$ \033[0m";
        std::string user_cmd;
        std::cin >> user_cmd;

        if (user_cmd == "size") {
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

            update_char_lengths(&database, &char_lengths);

            std::cout << "Size changed successfully. The database now has " << database.size() << " columns and " << database.at(0).size() << " rows.\n";

        } else if (user_cmd == "edit") {

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

            update_char_lengths(&database, &char_lengths);

            std::cout << "The value on column " << column << ", row " << row << " has been altered. It is now '" << database.at(column - 1).at(row - 1) << "'.\n";

        } else if (user_cmd == "table") {
            //display the whole database as a table
            
            if (database_empty(&database) == false) {
            
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
                    std::string longest_row_element = *std::max_element(database.at(ia).begin(), database.at(ia).end());
                    int max_cn_cl = longest_row_element.size();
    
                    add_spaces(cur_cn_cl, max_cn_cl, 2);
    
                }
    
                std::cout << "\n\n";
    
                //display the row numbers
                for (int ib = 0; ib < row_numbers.size(); ib++) {
    
                    std::cout << row_numbers.at(ib);
    
                    std::string conv_cur_rn_cl = std::to_string(row_numbers.at(ib));
                    int cur_rn_cl = conv_cur_rn_cl.size();
                    std::string conv_max_rn_cl = std::to_string(*row_numbers.end());
                    int max_rn_cl = conv_max_rn_cl.size();
                    
                    add_spaces(cur_rn_cl, max_rn_cl, 3);
    
                    //output row items
                    for (int ia = 0; ia < database.size(); ia++) {
    
                        std::cout << database.at(ia).at(ib);
    
                        int cur_cl = database.at(ia).at(ib).size();
                        int max_cl = max_char_length(&database.at(ia));
                        
                        add_spaces(cur_cl, max_cl, 2);
    
                    }
    
                    std::cout << "\n";
    
                }
                
            } else {
                
                std::cout << "Error: database is empty, nothing to display\n";
                
            }

        } else if (user_cmd == "help") {
            
            for (int i = 0; i < cmd_name.size(); i++) {
                
                int current_size = cmd_name.at(i).size();
                int max_size = max_char_length(&cmd_name);
                
                std::cout << cmd_name.at(i);
                add_spaces(current_size, max_size, 2);
                std::cout << cmd_description.at(i) << "\n";
                
            }

        } else if (user_cmd == "clear") {
            
            system("clear");
            
        } else if (user_cmd == "exit") {

            //exit the program
            stay_in_the_program = false;

        } else {

            std::cout << "Error: command not found\n";

        }
    }

    return 0;

}
