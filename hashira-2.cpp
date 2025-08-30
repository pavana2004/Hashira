#include <bits/stdc++.h>
using namespace std;

// convert char to digit
int charToDigit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'z')
        return 10 + (c - 'a');
    if (c >= 'A' && c <= 'Z')
        return 10 + (c - 'A');
    return -1;
}

// multiply big integer (string) by int
string multiplyString(string num, int x)
{
    int carry = 0;
    string res = "";
    for (int i = num.size() - 1; i >= 0; i--)
    {
        int val = (num[i] - '0') * x + carry;
        res.push_back(char('0' + (val % 10)));
        carry = val / 10;
    }
    while (carry)
    {
        res.push_back(char('0' + (carry % 10)));
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

// add int to big integer string
string addString(string num, int x)
{
    int carry = x;
    for (int i = num.size() - 1; i >= 0 && carry > 0; i--)
    {
        int val = (num[i] - '0') + carry;
        num[i] = char('0' + (val % 10));
        carry = val / 10;
    }
    while (carry > 0)
    {
        num.insert(num.begin(), char('0' + (carry % 10)));
        carry /= 10;
    }
    return num;
}

// convert from base -> decimal string
string convertToDecimal(const string &value, int base)
{
    string result = "0";
    for (char c : value)
    {
        int digit = charToDigit(c);
        if (digit >= base)
        {
            cerr << "Invalid digit " << c << " for base " << base << endl;
            return "0";
        }
        result = multiplyString(result, base);
        result = addString(result, digit);
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // read full JSON input
    string jsonInput, line;
    while (getline(cin, line))
    {
        jsonInput += line;
    }

    // parse n and k
    int n = 0, k = 0;
    size_t posN = jsonInput.find("\"n\"");
    if (posN != string::npos)
    {
        size_t colon = jsonInput.find(":", posN);
        n = stoi(jsonInput.substr(colon + 1));
    }
    size_t posK = jsonInput.find("\"k\"");
    if (posK != string::npos)
    {
        size_t colon = jsonInput.find(":", posK);
        k = stoi(jsonInput.substr(colon + 1));
    }

    int m = k - 1; // polynomial degree roots needed

    vector<string> roots;
    vector<int> bases;

    // parse each "i": { "base": X, "value": Y }
    for (int i = 1; i <= n; i++)
    {
        string key = "\"" + to_string(i) + "\"";
        size_t pos = jsonInput.find(key);
        if (pos == string::npos)
            continue;

        // base
        size_t basePos = jsonInput.find("\"base\"", pos);
        size_t colon1 = jsonInput.find(":", basePos);
        size_t comma1 = jsonInput.find(",", colon1);
        int base = stoi(jsonInput.substr(colon1 + 1, comma1 - colon1 - 1));

        // value
        size_t valuePos = jsonInput.find("\"value\"", pos);
        size_t colon2 = jsonInput.find(":", valuePos);
        size_t quote1 = jsonInput.find("\"", colon2 + 1);
        size_t quote2 = jsonInput.find("\"", quote1 + 1);
        string value = jsonInput.substr(quote1 + 1, quote2 - quote1 - 1);

        // convert
        string decimal = convertToDecimal(value, base);

        bases.push_back(base);
        roots.push_back(decimal);
    }

    cout << "Correct roots (used for polynomial):\n";
    for (int i = 0; i < m && i < roots.size(); i++)
    {
        cout << "r" << (i + 1) << " = " << roots[i] << "\n";
    }

    cout << "\nWrong dataset points:\n";
    for (int i = m; i < roots.size(); i++)
    {
        cout << "r" << (i + 1) << " = " << roots[i] << "\n";
    }

    cout << "\nPolynomial in factored form:\nP(x) = ";
    for (int i = 0; i < m; i++)
    {
        cout << "(x - " << roots[i] << ")";
    }
    cout << "\n";

    return 0;
}
