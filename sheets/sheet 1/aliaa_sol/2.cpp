#include <bits/stdc++.h>
using namespace std;
 

void rec(int n, int k, string curr) {

    if(curr.size() == n) { 
        cout << curr << '\n';
        return;
    }
    int i = 0;
    for(char c = '0'; i < k ; i++,c++){
        if(i == 10) c = 'a';
        rec(n,k, curr+c);
    }
}

int main()
{

    int n,k; cin >> n >> k;
    rec(n,k, "");
    cout << '\n';
    
    return 0;
}