#include <bits/stdc++.h>
using namespace std;
 

void rec(int sz, int n, string curr) {
    if(sz == n) cout << curr << '\n';
    else {
        rec(sz+1, n, curr+"0");
        rec(sz+1, n, curr+"1");
    }
}

int main()
{

    int n; cin >> n;
    rec(0,n, "");
    cout << '\n';

    
    return 0;
}