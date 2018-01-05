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

int dp[2000][2000];

class EmoticonsDiv2 {
    public:

    int emoji(int on_screen, int on_clipboard, int smiles) {  
        int& res = dp[on_screen][on_clipboard];

        if(res == -1) {
            res = 0;
            if(on_screen > smiles) {
                res = 10000;
            }
            else if(on_screen == smiles) {
                res = 0;
            }
            else if(on_clipboard == 0) {
                // only copy
                on_clipboard = on_screen;
                res = 1 + emoji(on_screen, on_clipboard, smiles);
            }

            else if(on_clipboard == on_screen) {
                // only paste
                res = 1 + emoji(on_screen + on_clipboard, on_clipboard, smiles);
            }
            else {
                int paste = 1 + emoji(on_screen + on_clipboard, on_clipboard, smiles);
                
                on_clipboard = on_screen;
                int copy = 1 + emoji(on_screen, on_clipboard, smiles);
                
                res = min(paste, copy);
            }
        }
        return res;
    }

    int printSmiles(int smiles) {

        int on_clipboard = 0, on_screen = 1;
        memset(dp, -1, sizeof(dp));

        return emoji(on_screen, on_clipboard, smiles); 

    }
};

// CUT begin
ifstream data("EmoticonsDiv2.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int smiles, int __expected) {
    time_t startClock = clock();
    EmoticonsDiv2 *instance = new EmoticonsDiv2();
    int __result = instance->printSmiles(smiles);
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
        int smiles;
        from_stream(smiles);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(smiles, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514999837;
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
        cout << "EmoticonsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
