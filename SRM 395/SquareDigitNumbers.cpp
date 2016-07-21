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

class SquareDigitNumbers {
    public:
    int getNumber(int n) {
        int flag=0;
        int i=0,numb=0,j=0;
        int check;
        while(j<n){
            check =check_numb(i);
            if(check==1){
                numb=i;
                ++j;
            }
            i++;
        }
        return numb;
    }
    int check_numb(int i){
        int m,p=i,count=0,t_digi=0;
        if(i==0){
            return 1;
        }
        while(p>0){
            m=p%10;
            if(m==0 || m==1 || m==4 || m==9) {
                ++count;
            }
            p=p/10;
            ++t_digi;
        }
        if(count==t_digi){
            return 1;
        }
        return 0;
    }
//     int getNumber(int n) {
//     int num=0;
//     for(int i=0;i<=n;){
//         bool success = check_numb(num);
//         if(success == true){
//             ++i;
//         }
//         ++num;
//     }
//     return num;
// }
    
// bool check_numb(int num){
//     while(num!=0){
//         int last = num%10;
//         if(!(last==0 || last == 1 || last ==4 || last ==9)){
//             return false;
//         }
//         num=num/10;
//     }        
//     return true;
// }
};

// CUT begin
ifstream data("SquareDigitNumbers.sample");

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

bool do_test(int n, int __expected) {
    time_t startClock = clock();
    SquareDigitNumbers *instance = new SquareDigitNumbers();
    int __result = instance->getNumber(n);
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
        int n;
        from_stream(n);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468789801;
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
        cout << "SquareDigitNumbers (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
