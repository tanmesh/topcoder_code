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

class FoxProgression {
    public:
    int theCount(vector<int> seq) {
        if(seq.size()==1)
            return -1;

        //declaration
        int cntG=1,cntA=1;
        int commoDiff;
        int n=seq.size();

        // arithmetic
        for(int i=0;i+1<seq.size();++i)
        {
            if(i==0){
                commoDiff=seq[i+1]-seq[i];
            }
            if(commoDiff != seq[i+1]-seq[i])
                cntA=0;        
        }
             
        //geometrical
        int commoRatio;
        for(int i=0;i+1<seq.size();++i){                                            
            if(i==0){
                commoRatio=seq[1]/seq[0];
                if(commoRatio*seq[0] != seq[1]){
                    cntG =0;
                }
            }
            else{
                if(commoRatio*seq[i] != seq[i+1]){
                    cntG =0;
                }
            }
        }

        //output
        if((commoDiff+seq[n-1] == commoRatio*seq[n-1]) && cntA!=0 && cntG!=0) {
            return 1;
        }
        return cntG+cntA;

        
    }
};

// CUT begin
ifstream data("FoxProgression.sample");

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

bool do_test(vector<int> seq, int __expected) {
    time_t startClock = clock();
    FoxProgression *instance = new FoxProgression();
    int __result = instance->theCount(seq);
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
        vector<int> seq;
        from_stream(seq);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(seq, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476268941;
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
        cout << "FoxProgression (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
