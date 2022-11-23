#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;
int di[] = {0, 0, 1, -1};
int dj[] = {1, -1, 0, 0};
class solution
{
    // hash function
    long hash(string x)
    {
        long res = 39 * (int)x[0];
        for (int i = 1; i < 4 && i < x.size(); i++)
        {
            res += (391 + i) * (int)x[i];
        }
        res %= 24000;
        return res;
    }
    void insert(vector<string> &h, string x)
    {
        int spot = hash(x);
        int count = 0;
        while (h[spot] != "" && count < 24000)
        {
            if (h[spot] == "-1")
                break;
            spot = (spot + 1) % 24000;
            count++;
        }
        h[spot] = x;
    }
    void deleteHash(vector<string> &h, string x, int &mn, int &mx, int &sum)
    {
        int spot = hash(x);
        int probes = 0;
        int count = 0;
        while (h[spot] != "" && h[spot] != x && count < 24000)
        {
            spot = (spot + 1) % 24000;
            probes++;
            count++;
        }
        if (count < 24000)
        {
            h[spot] = "-1";
            mn = min(mn, probes);
            mx = max(mx, probes);
            sum += probes;
        }
    }

public:
    solution()
    {
        vector<string> a(20000);
        int i = 0;
        ifstream wordsFile("C:\\Users\\walid\\Desktop\\Lab3 - hashing\\words20K.txt");
        string x;
        while (wordsFile >> x)
            a[i++] = x;
        vector<string> h(24000, "");
        int count = 1;
        auto now = high_resolution_clock::now();
        for (auto i : a)
        {
            if (count % 500 == 0)
            {
                auto end = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(end - now);
                cout << duration.count() / 500.f << "\n";
                now = high_resolution_clock::now();
            }
            insert(h, i);
            count++;
        }
        int mn = INT_MAX, mx = INT_MIN, sum = 0;
        for (int i = 14000; i <= 14999; i++)
        {
            deleteHash(h, a[i], mn, mx, sum);
        }
        cout << mn << " " << mx << " " << (sum / 1000);
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