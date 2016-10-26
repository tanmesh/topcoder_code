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

class GameOfLifeDivTwo {
    public:
    char update(char a,char b,char c)
    {
        int cnt=0;
        if(a=='0')
            ++cnt;
        if(b=='0')
            ++cnt;
        if(c=='0')
            ++cnt;
        if(cnt>1)
            return '0';
        else
            return '1';    
    }
    string theSimulation(string init, int T) {
        int n=init.size();
        string str=init;
        for(int i=0;i<T;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(j==0) {
                    str[j]=update(init[n-1],init[0],init[1]);
                    continue;
                }
                if(j==n-1) {
                    str[j]=update(init[n-2],init[n-1],init[0]);
                    continue;
                }
                    str[j]=update(init[j-1],init[j],init[j+1]);
            }
            init=str;
        }
        return init;
    }
};

// CUT begin
ifstream data("GameOfLifeDivTwo.sample");

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

bool do_test(string init, int T, string __expected) {
    time_t startClock = clock();
    GameOfLifeDivTwo *instance = new GameOfLifeDivTwo();
    string __result = instance->theSimulation(init, T);
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
        string init;
        from_stream(init);
        int T;
        from_stream(T);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(init, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477141396;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GameOfLifeDivTwo (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
