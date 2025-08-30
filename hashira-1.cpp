#include <bits/stdc++.h>
using namespace std;

// Convert string number in given base to decimal (long long)
long long convertToDecimal(const string &value, int base)
{
    long long result = 0;
    for (char c : value)
    {
        int digit;
        if (isdigit(c))
            digit = c - '0';
        else
            digit = 10 + (tolower(c) - 'a');
        result = result * base + digit;
    }
    return result;
}

// Multiply polynomials
vector<long long> multiplyPoly(const vector<long long> &a, const vector<long long> &b)
{
    vector<long long> res(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < b.size(); j++)
        {
            res[i + j] += a[i] * b[j];
        }
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read full JSON input
    string input, line;
    while (getline(cin, line))
        input += line;

    // Extract n and k
    int n = 0, k = 0;
    {
        size_t pos = input.find("\"n\"");
        if (pos != string::npos)
        {
            sscanf(input.c_str() + pos, "\"n\": %d", &n);
        }
        pos = input.find("\"k\"");
        if (pos != string::npos)
        {
            sscanf(input.c_str() + pos, "\"k\": %d", &k);
        }
    }

    // Extract all roots
    vector<long long> roots;
    size_t pos = 0;
    while (true)
    {
        pos = input.find("\"base\"", pos);
        if (pos == string::npos)
            break;
        int base;
        char value[200];
        sscanf(input.c_str() + pos, "\"base\": \"%d\", \"value\": \"%199[^\"]\"", &base, value);
        roots.push_back(convertToDecimal(value, base));
        pos++;
    }

    int m = k - 1; // degree = k-1 roots needed

    cout << "Total points = " << n << ", Required roots = " << m << "\n\n";

    // Print correct roots
    cout << "✅ Correct roots (used for polynomial):\n";
    for (int i = 0; i < m && i < (int)roots.size(); i++)
    {
        cout << "r" << (i + 1) << " = " << roots[i] << "\n";
    }
    cout << "\n";

    // Print wrong roots
    cout << "❌ Wrong dataset points:\n";
    for (int i = m; i < (int)roots.size(); i++)
    {
        cout << "r" << (i + 1) << " = " << roots[i] << "\n";
    }
    cout << "\n";

    // Build polynomial
    vector<long long> poly = {1}; // start with 1
    for (int i = 0; i < m; i++)
    {
        vector<long long> term = {1, -roots[i]}; // (x - root)
        poly = multiplyPoly(poly, term);
    }

    // Print polynomial factored
    cout << "Polynomial factored form:\nP(x) = ";
    for (int i = 0; i < m; i++)
    {
        cout << "(x - " << roots[i] << ")";
    }
    cout << "\n\n";

    // Print polynomial expanded
    cout << "Polynomial expanded coefficients (highest degree → constant):\n";
    for (int i = 0; i < (int)poly.size(); i++)
    {
        cout << poly[i] << (i + 1 == (int)poly.size() ? "\n" : " ");
    }

    return 0;
}
