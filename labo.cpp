//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

class Array
{
public:
    template <class T>
    static void input(vector<T> &A, int n)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d ", &A[i]);
        }
    }

    template <class T>
    static void print(vector<T> &A)
    {
        for (int i = 0; i < A.size(); i++)
        {
            cout << A[i] << " ";
        }
        cout << endl;
    }
};

// } Driver Code Ends

int dp[101][1001][101];

class Solution
{
public:
    bool makeChanges(int N, int K, int target, vector<int> &coins)
    {

        // Inicialización de la matriz dp
        for (int i = 0; i <= N; i++)
        {
            for (int j = 0; j <= target; j++)
            {
                for (int k = 0; k <= K; k++)
                {
                    if (j == 0 && k == 0)
                    {
                        dp[i][j][k] = 0;
                    }
                    else
                    {
                        dp[i][j][k] = -1;
                    }
                }
            }
        }

        // Calcular usando programación dinámica
        for (int i = 1; i <= N; i++)
        {
            for (int j = 0; j <= target; j++)
            {
                for (int k = 0; k <= K; k++)
                {
                    if (coins[i - 1] > j || k == 0)
                    {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                    else
                    {
                        if (dp[i][j - coins[i - 1]][k - 1] != -1)
                        {
                            dp[i][j][k] = dp[i][j - coins[i - 1]][k - 1] + 1;
                        }
                        else
                        {
                            dp[i][j][k] = dp[i - 1][j][k];
                        }
                    }
                }
            }
        }

        // Verificar si es posible lograr el objetivo con k monedas.
        return dp[N][target][K] >= 0;
    }
};

int main()
{
    int t;
    scanf("%d ", &t);
    while (t--)
    {

        int N;
        scanf("%d", &N);

        int K;
        scanf("%d", &K);

        int target;
        scanf("%d", &target);

        vector<int> coins(N);
        Array::input(coins, N - 1);

        Solution obj;
        bool res = obj.makeChanges(N, K, target, coins);

        cout << res << endl;
    }
}

// } Driver Code Ends