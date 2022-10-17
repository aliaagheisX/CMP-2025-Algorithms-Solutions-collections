#include <bits/stdc++.h>
using namespace std;



/* 
how many binary strings of length (n)
that count of 1's divisable by 3
like if n = 3 sol_set = {000,111} ans = 2

 */

int n;
int rec(int i,int cntOnes) {
    if(i == n) return (cntOnes % 3 == 0);

    return rec(i+1, cntOnes+1) + rec(i+1, cntOnes);

}

void solve() {
    cin >> n;

    cout << rec(0, 0);
}
 
int main()
{
   
    solve();   
    return 0;
}
