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

class TriangleType {
    public:
    string type(int a, int b, int c) {
        int arr[3]={a,b,c};
        //SORT
        for(int i=3;i>0;--i){
            for(int j=0;j+1<i;++j){
                if(arr[j]>arr[j+1]){
                int tmp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
                }
            }
        }

        if((arr[0]+arr[1])<=arr[2])
            return "IMPOSSIBLE";
        if((arr[1]+arr[2])<=arr[0])
            return "IMPOSSIBLE";
        if((arr[2]+arr[0])<=arr[1])
            return "IMPOSSIBLE";

        int cnt=(arr[0]*arr[0])+(arr[1]*arr[1]);
        if(cnt==(arr[2]*arr[2]))
            return "RIGHT";
        if(cnt>(arr[2]*arr[2]))
            return "ACUTE";
        if(cnt<(arr[2]*arr[2]))
            return "OBTUSE";
    }
};

// CUT begin
ifstream data("TriangleType.sample");

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

bool do_test(int a, int b, int c, string __expected) {
    time_t startClock = clock();
    TriangleType *instance = new TriangleType();
    string __result = instance->type(a, b, c);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1471257425;
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
        cout << "TriangleType (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
