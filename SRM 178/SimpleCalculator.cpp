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

class SimpleCalculator {
    public:
    int calculate(string input) {
        int i=0,numb=0,div=0;
        char op;
        while(1){
            numb=(numb*10)+(input[i++]-'0');
            //cout<<"in loop 1 "<<numb<<endl;
            if(input[i]=='+'){
                op=input[i++];
                break;
            }
            if(input[i]=='-'){
                op=input[i++];
                break;
            }
            if(input[i]=='*'){
                op=input[i++];
                break;
            }
            if(input[i]=='/'){
                op=input[i++];
                break;
            }
        }
            //cout<<"out loop "<<op<<endl;
    
        while(i<(input.size())){
            div=(div*10)+(input[i++]-'0');
            //cout<<"in loop 2 "<<div<<endl;
        }
        int ans;
        if(op=='/'){
            ans=numb/div;
        }
        if(op=='*'){
            ans=numb*div;
        }
        if(op=='-'){
            ans=numb-div;
        }
        if(op=='+'){
            ans=numb+div;
        }
        return ans;
    }
};

// CUT begin
ifstream data("SimpleCalculator.sample");

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

bool do_test(string input, int __expected) {
    time_t startClock = clock();
    SimpleCalculator *instance = new SimpleCalculator();
    int __result = instance->calculate(input);
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
        string input;
        from_stream(input);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(input, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1470547879;
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
        cout << "SimpleCalculator (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end