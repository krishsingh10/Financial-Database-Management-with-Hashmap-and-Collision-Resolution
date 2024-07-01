#include "CubicProbing.h"
using namespace std;

CubicProbing::CubicProbing()
{
    Tablesize = 100000;
    for (size_t i = 0; i < 100000; i++)
    {
        Account a;
        a.id = "x";
        bankStorage1d.push_back(a);
    }
}

void CubicProbing::createAccount(std::string id, int count)
{
    if (count < 0)
    {
        return;
    }
    else
    {
        int idx = hash(id);
        int i = 1;

        while ((bankStorage1d[idx].id!="x")&&(bankStorage1d[idx].id!="y"))
        {
            idx = (idx + i * i * i) % mod;
            i++;
        }

        bankStorage1d[idx] = {id, count};
    }
}

vector<int> mergeC(const vector<int> &left, const vector<int> &right)
{
    vector<int> result;
    int leftIndex = 0;
    int rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size())
    {
        if (left[leftIndex] > right[rightIndex])
        {
            result.push_back(left[leftIndex]);
            leftIndex++;
        }
        else
        {
            result.push_back(right[rightIndex]);
            rightIndex++;
        }
    }

    while (leftIndex < left.size())
    {
        result.push_back(left[leftIndex]);
        leftIndex++;
    }

    while (rightIndex < right.size())
    {
        result.push_back(right[rightIndex]);
        rightIndex++;
    }

    return result;
}

vector<int> mergeSortC(const vector<int> &arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }

    int middle = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + middle);
    vector<int> right(arr.begin() + middle, arr.end());

    left = mergeSortC(left);
    right = mergeSortC(right);

    return mergeC(left, right);
}

vector<int> CubicProbing::getTopK(int k)
{
    vector<int> allBalances;

    for (int i = 0; i < Tablesize; i++)
    {
        if ((bankStorage1d[i].id != "x") && (bankStorage1d[i].id != "y"))
        {
            allBalances.push_back(bankStorage1d[i].balance);
        }
    }

    vector<int> sortedBalances = mergeSortC(allBalances);

    vector<int> topBalances;
    for (int i = 0; i < k && i < sortedBalances.size(); i++)
    {
        topBalances.push_back(sortedBalances[i]);
    }

    return topBalances;
}

int CubicProbing::getBalance(std::string id)
{
    int idx = hash(id);
    int j = 1;

    for (int i = 0; i < Tablesize; i++)
    {
        if (bankStorage1d[idx].id == id)
        {
            return bankStorage1d[idx].balance;
        }
        idx = (idx + j * j * j) % mod;
        j++;
    }

    return -1;
}

void CubicProbing::addTransaction(std::string id, int count)
{
    int idx = hash(id);
    int j = 1;

    for (int i = 0; i < Tablesize; i++)
    {
        if (bankStorage1d[idx].id == id)
        {
            int changeblnc = bankStorage1d[idx].balance + count;

            if (changeblnc >= 0)
            {
                bankStorage1d[idx].balance = changeblnc;
                return;
            }
            else
            {
                return;
            }
        }
        idx = (idx + j * j * j) % mod;
        j++;
    }

    createAccount(id, count);
}

bool CubicProbing::doesExist(std::string id)
{
    int idx = hash(id);
    int j = 1;
    int i = 0;
    while (!(bankStorage1d[idx].id=="x"))
    {
        if (bankStorage1d[idx].id == id)
        {
            return true;
        }
        idx = (idx + j * j * j) % mod;
        j++;
        i++;
    }

    return false;
}

bool CubicProbing::deleteAccount(std::string id)
{
    int idx = hash(id);
    int j = 1;

    for (int i = 0; i < Tablesize; i++)
    {
        if (bankStorage1d[idx].id == id)
        {
            Account a;
            a.id="y";
            bankStorage1d[idx] = a;
            return true;
        }
        idx = (idx + j * j * j) % mod;
        j++;
    }

    return false;
}

int CubicProbing::databaseSize()
{
    int size = 0;

    for (int i = 0; i < Tablesize; i++)
    {
        if (!(bankStorage1d[i].id == "x" || bankStorage1d[i].id == "y"))
        {
            size++;
        }
    }

    return size;
}

int CubicProbing::hash(std::string id)
{
    const int prime1 = 31;
    const int prime2 = 17;
    const int prime3 = 13;
    int hashValue = 0;

    int charFrequency[256] = {0};

    for (char c : id)
    {
        charFrequency[c]++;
    }

    int position = 0;
    for (char c : id)
    {
        if (charFrequency[c] > 0)
        {
            hashValue = (hashValue * prime1 + (c - 'a' + 1) * prime2 + position) % prime3;
            position++;
        }
    }

    hashValue = (hashValue * prime3 + id.length()) % 100007;

    return hashValue;
}
