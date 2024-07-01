#include "QuadraticProbing.h"
using namespace std;

QuadraticProbing::QuadraticProbing() {
    Tablesize = 100000;
    for (size_t i = 0; i < 100000; i++)
    {
        Account a;
        a.id = "x";
        bankStorage1d.push_back(a);
    }
    
}

void QuadraticProbing::createAccount(std::string id, int count) {
    if (count < 0) {
        return;
    }
    else {
        int idx = hash(id);
        int i = 1;
        while (!(bankStorage1d[idx].id=="x")) {
            idx = (idx + i * i) % mod;
            i++;
        }

        bankStorage1d[idx] = { id, count };
        
    }
}

vector<int> mergeQ(const vector<int>& left, const vector<int>& right) {
    vector<int> result;
    int leftIndex = 0;
    int rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (left[leftIndex] > right[rightIndex]) {
            result.push_back(left[leftIndex]);
            leftIndex++;
        }
        else {
            result.push_back(right[rightIndex]);
            rightIndex++;
        }
    }

    while (leftIndex < left.size()) {
        result.push_back(left[leftIndex]);
        leftIndex++;
    }

    while (rightIndex < right.size()) {
        result.push_back(right[rightIndex]);
        rightIndex++;
    }

    return result;
}

vector<int> mergeSortQ(const vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    int middle = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + middle);
    vector<int> right(arr.begin() + middle, arr.end());

    left = mergeSortQ(left);
    right = mergeSortQ(right);

    return mergeQ(left, right);
}

vector<int> QuadraticProbing::getTopK(int k) {
    vector<int> allBalances;

    for (int i = 0; i < Tablesize; i++) {
        if ((bankStorage1d[i].id!="x")&&(bankStorage1d[i].id!="y")) {
            allBalances.push_back(bankStorage1d[i].balance);
        }
    }

    vector<int> sortedBalances = mergeSortQ(allBalances);

    vector<int> topBalances;
    for (int i = 0; i < k && i < sortedBalances.size(); i++) {
        topBalances.push_back(sortedBalances[i]);
    }
    
            
    return topBalances;
}

int QuadraticProbing::getBalance(std::string id) {
    int idx = hash(id);
    int j = 1;

    for (int i = 0; i < Tablesize; i++) {
        if (bankStorage1d[idx].id == id) {
            return bankStorage1d[idx].balance;
        }
        idx = (idx + j * j) % mod;
        j++;
    }

    return -1;
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    int idx = hash(id);
    int j = 1;

    for (int i = 0; i < Tablesize; i++) {
        if (bankStorage1d[idx].id == id) {
            int changeblnc = bankStorage1d[idx].balance + count;

            if (changeblnc >= 0) {
                bankStorage1d[idx].balance = changeblnc;

                return;
            }
            else {
                return;
            }
        }
        idx = (idx + j * j) % mod;
        j++;
    }
    createAccount(id, count);
}

bool QuadraticProbing::doesExist(std::string id) {
    int idx = hash(id);
    int j = 1;
    int i = 0;
    while ((bankStorage1d[idx].id!="x")&&(bankStorage1d[idx].id!="y")) {
        if (bankStorage1d[idx].id == id) {
            return true;
        }
        idx = (idx + j * j) % mod;
        j++;
        i++;
    }

    return false;
}

bool QuadraticProbing::deleteAccount(std::string id) {
    int idx = hash(id);
    int j = 1;

    for (int i = 0; i < Tablesize; i++) {
        if (bankStorage1d[idx].id == id) {
            Account a;
            a.id="y";
            bankStorage1d[idx] = a;
            return true;
        }
        idx = (idx + j * j) % mod;
        j++;
    }

    return false;
}

int QuadraticProbing::databaseSize() {
    int size = 0;

    for (int i = 0; i < Tablesize; i++) {
        if (!(bankStorage1d[i].id=="x" || bankStorage1d[i].id=="y")) {
            size++;
        }
    }
    return size;
}

int QuadraticProbing::hash(std::string id) {
    const int prime1 = 31;
    const int prime2 = 17;
    const int prime3 = 13;
    int hashValue = 0;

    int charFrequency[256] = { 0 };

    for (char c : id) {
        charFrequency[c]++;
    }

    int position = 0;
    for (char c : id) {
        if (charFrequency[c] > 0) {
            hashValue = (hashValue * prime1 + (c - 'a' + 1) * prime2 + position) % prime3;
            position++;
        }
    }

    hashValue = (hashValue * prime3 + id.length()) % 100007;

    return hashValue;
}
