#include <bits/stdc++.h>
using namespace std;

int steps;

int rec(int curr) {
    if(curr >= steps) return (curr == steps);

    return rec(curr+1) + rec(curr+2) + rec(curr+3);
    
}

int main()
{

    cin >> steps;
    cout << rec(0) << '\n';
    
    
    return 0;
}