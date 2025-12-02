#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct range {
    long long lower;
    long long upper;
};

vector<range> input = {};

int parse_input() {
    ifstream inputFile("../part1/pr2p1.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    string str_input = "";

    while(getline(inputFile, line)) {
        str_input += line;
    }

    // transcribe input to vector
    while (str_input.size() != 0) {
        int comma = str_input.find(",");
        int dash = str_input.find("-");
        string curr;

        if (comma != string::npos) {
            curr = str_input.substr(0,comma);
            str_input = str_input.substr(comma+1);
        } else {
            // last elem in str_input
            curr = str_input.substr(0);
            str_input = "";
        }

        string lower_str = curr.substr(0,dash);
        string upper_str = curr.substr(dash+1);
        long long lower = stoll(lower_str);
        long long upper = stoll(upper_str);
        range curr_range = {lower, upper};
        input.push_back(curr_range);
    }

    return 0;
}

long long get_invalid_ids() {
    long long sum = 0;

    // iter through all ranges
    for (int i = 0; i < input.size(); i++) {
        range elem = input[i];
        // iter through each elem in given range
        for (long long iter = elem.lower; iter <= elem.upper; iter++) {
            string str = to_string(iter);
            // dynamically set n [1-str.length()/2]
            // if str.length() % n != 0 or pattern doesnt repeat, go to next val of n
            // if valid n found, invalid id

            // iter through all indices of str
            for (int n = 1; n <= (str.length() / 2); n++) {
                // n doesn't fit in str evenly
                if (str.length() % n != 0) {
                    continue;
                }

                int m = str.length() / n;
                int isInvalid = 1;
                for (int index = 1; index < m; index++) {
                    if (str.substr(0,n) == str.substr(n*index, n)) {
                        // continue while number still known to be invalid
                        continue;
                    } else {
                        isInvalid = 0;
                        break;
                    }
                }

                // add iter to sum if iter is invalid
                if (isInvalid) {
                    sum += iter;
                    break;
                }
            }
        }
    }

    return sum;
}

int main() {
    /*
    parse input
    trav lower to upper bound (inclusive)
    find sum of invalid IDs
    */
    parse_input();
    // for (range elem : input) {
    //     cout << elem.lower << "-" << elem.upper << ",";
    // }
    // cout << endl;

    long long sum = get_invalid_ids();
    cout << sum << endl;
    return 0;
}