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

class MassiveNumbers {
    public:
    string getLargest(string numberA, string numberB) {
        double numbA=0,numbB=0;

        int i=0;
        while(numberA[i]!='^'){
            numbA=(numbA*10)+(numberA[i]-'0');
            ++i;
        }   
        numbA=log(numbA);   
        double numb=0;
        ++i;
        while(i!=numberA.size()){
            numb=(numb*10)+(numberA[i]-'0');
            ++i;
        }    
        numbA=numb*numbA;

        i=0;
        while(numberB[i]!='^'){
            numbB=(numbB*10)+(numberB[i]-'0');
            ++i;
        }
        numbB=log(numbB);
        numb=0;
        ++i;
        while(i!=numberB.size()){
            numb=(numb*10)+(numberB[i]-'0');
            ++i;
        }
        numbB=numb*numbB;

        if(numbA>numbB){
            return numberA;
        }
        else{
            return numberB;
        }
    }
};

// CUT begin
ifstream data("MassiveNumbers.sample");

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

bool do_test(string numberA, string numberB, string __expected) {
    time_t startClock = clock();
    MassiveNumbers *instance = new MassiveNumbers();
    string __result = instance->getLargest(numberA, numberB);
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
        string numberA;
        from_stream(numberA);
        string numberB;
        from_stream(numberB);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numberA, numberB, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1469302907;
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
        cout << "MassiveNumbers (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
