#include <bits/stdc++.h>
using namespace std;
class solution
{
    bool res = 0;
    void recAns(const vector<int> &arr, int acc, int i = 1)
    {
        if (i > 4)
        {
            if (acc == 27)
                res = 1;
            return;
        }
        recAns(arr, acc + arr[i], i + 1);
        recAns(arr, acc - arr[i], i + 1);
        recAns(arr, acc * arr[i], i + 1);
    }

public:
    solution()
    {
        vector<int> arr(5);
        for (int &i : arr)
            cin >> i;
        sort(arr.begin(), arr.end());
        while (next_permutation(arr.begin(), arr.end()) && !res)
        {
            recAns(arr, arr[0]);
        }
        if (res)
            cout << "Possible";
        else
            cout << "Impossible";
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    solution *x = new solution();
    delete x;
    return 0;
}