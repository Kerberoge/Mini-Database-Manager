//a = column, b = database.size()
int column_checker (int a, int b) {

    if (a <= b && a > 0) {
        return true;
    } else {
        return false;
    }

}

//a = row, b = database.at(0).size()
int row_checker (int a, int b) {

    if (a <= b && a > 0) {
        return true;
    } else {
        return false;
    }

}

void update_char_lengths (std::vector<std::vector<std::string>> *db_p, std::vector<std::vector<int>> *cl_p) {

    //resize the vector
    cl_p->resize(db_p->size());

    for (int i = 0; i < db_p->size(); i++) {

        cl_p->at(i).resize(db_p->at(0).size());

    }

    //fill the vector
    for (int ia = 0; ia < db_p->size(); ia++) {

        for (int ib = 0; ib < db_p->at(0).size(); ib++) {

            cl_p->at(ia).at(ib) = db_p->at(ia).at(ib).size();

        }

    }

}

//the function needs to know the length of the current number (a), the length of the longest number (b), and the minimum amount of spaces (c).
void add_spaces (int cur_cl, int max_cl, int am_s) {

    for (int i = 1; i <= max_cl + am_s - cur_cl; i++) {

        std::cout << " ";

    }

}
