#include <bits/stdc++.h>
using namespace std;
int di[] = {1, -1, 1, -1, 1, 1};
int dj[] = {0, 0, 1, -1, -1, -1};
bool condition(int i, int j, int n, int m)
{
    return i < n && i >= 0 && j < m && j >= 0;
}
class solution
{
    int mat[3][3];
    int resMat[3][3];
    void recAns(map<pair<int, int>, bool> rec, int acc = 0, int i = 0, int j = 0)
    {
        if (!condition(i, j, 3, 3) || rec.find({i, j}) != rec.end())
            return;
        resMat[i][j] = max(mat[i][j] + acc, resMat[i][j]);
        rec[{i, j}] = 1;
        for (int dir = 0; dir < 6; dir++)
            recAns(rec, mat[i][j] + acc, i + di[dir], j + dj[dir]);
    }

public:
    solution()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                cin >> mat[i][j];
                resMat[i][j] = INT_MIN;
            }
        map<pair<int, int>, bool> x;
        recAns(x);
        cout << resMat[2][0];
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