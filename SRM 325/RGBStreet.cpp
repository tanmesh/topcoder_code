#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

int dp[9][4];

class RGBStreet {
    public:

    int convertStringToInt(string s) {
        int numb = 0;
        for(int i=0; i<s.length(); ++i) {
            numb = numb*10 + (s[i]-'0');
        }
        return numb;
    }

    vector<vector<int> > extractPrices(vector<string> houses) {
        vector<vector<int> > prices(houses.size());
        for(int i=0 ;i<houses.size(); ++i) {
            int start = 0;
            vector<int> tmp;
            for(int j=0; j<houses[i].length(); ++j) {
                if(houses[i][j] == ' ') {
                    string str1 = houses[i].substr(start, j-start);
                    tmp.push_back(convertStringToInt(str1));
                    start = j+1;  
                }
                else if(j+1 == houses[i].length()) {
                    string str1 = houses[i].substr(start);
                    tmp.push_back(convertStringToInt(str1));
                }
            }
            prices[i] = tmp;
        }

        return prices;
    }

    int minPrice(int i, int previousColour, int housesCnt, vector< vector< int> >& prices) {
        if(i >= housesCnt) {
            return 0;
        }
        int ans = INT_MAX;
        if(previousColour != 0) {
            ans = prices[i][0] + min(minPrice(i+1, 0, housesCnt, prices), ans);
        }
        if(previousColour != 1) {
            ans = prices[i][1] + min(minPrice(i+1, 1, housesCnt, prices), ans);
        }
        if(previousColour != 2) {
            ans = prices[i][2] + min(minPrice(i+1, 2, housesCnt, prices), ans);
        }
        return ans;
    }

    int estimateCost(vector<string> houses) {
        vector<vector<int> > prices = extractPrices(houses);

        return minPrice(0, -1, houses.size(), prices);
    }
};

// CUT begin
ifstream data("RGBStreet.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<string> houses, int __expected) {
    time_t startClock = clock();
    RGBStreet *instance = new RGBStreet();
    int __result = instance->estimateCost(houses);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<string> houses;
        from_stream(houses);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(houses, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515061662;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "RGBStreet (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
