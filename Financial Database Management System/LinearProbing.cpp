#include "LinearProbing.h"

using namespace std;

LinearProbing::LinearProbing() {
    tablesize = 100000;
    for (size_t i = 0; i < 100000; i++)
    {
        Account a;
        a.id = "x";
        bankStorage1d.push_back(a);
    }
    
}

void LinearProbing::createAccount(std::string id, int count) {
    if (count < 0) {
        return;
    }
    else {
        int idx = hash(id);
       while ((bankStorage1d[idx].id!="x")&&(bankStorage1d[idx].id!="y")) {
            idx = (idx + 1) % mod;
        }

        bankStorage1d[idx] = { id, count };
    }
}

vector<int> mergeL(const vector<int>& left, const vector<int>& right) {
    vector<int> res;
    int leftIndex = 0;
    int rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (left[leftIndex] > right[rightIndex]) {
            res.push_back(left[leftIndex]);
            leftIndex++;
        }
        else {
            res.push_back(right[rightIndex]);
            rightIndex++;
        }
    }

    while (leftIndex < left.size()) {
        res.push_back(left[leftIndex]);
        leftIndex++;
    }

    while (rightIndex < right.size()) {
        res.push_back(right[rightIndex]);
        rightIndex++;
    }

    return res;
}

vector<int> mergeSortL(const vector<int>& sorarr) {
    if (sorarr.size() <= 1) {
        return sorarr;
    }

    int middle = sorarr.size() / 2;
    vector<int> left(sorarr.begin(), sorarr.begin() + middle);
    vector<int> right(sorarr.begin() + middle, sorarr.end());

    left = mergeSortL(left);
    right = mergeSortL(right);

    return mergeL(left, right);
}

vector<int> LinearProbing::getTopK(int k) {
    vector<int> allblnc;

    for (int i = 0; i < tablesize; i++) {
       if ((bankStorage1d[i].id!="x")&&(bankStorage1d[i].id!="y")) {
            allblnc.push_back(bankStorage1d[i].balance);
        }
    }

    vector<int> sortedblnc = mergeSortL(allblnc);

    vector<int> topblnc;
    for (int i = 0; i < k && i < sortedblnc.size(); i++) {
        topblnc.push_back(sortedblnc[i]);
    }

    return topblnc;
}

int LinearProbing::getBalance(std::string id) {
    int idx = hash(id);

    for (int i = 0; i < tablesize; i++) {
        if (bankStorage1d[idx].id == id) {
            return bankStorage1d[idx].balance;
        }
        idx = (idx + 1) % mod;
    }

    return -1;
}

void LinearProbing::addTransaction(std::string id, int count) {
    int idx = hash(id);

    for (int i = 0; i < tablesize; i++) {
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
        idx = (idx + 1) % mod;
    }

    createAccount(id, count);
}

bool LinearProbing::doesExist(std::string id) {
    int idx = hash(id);

    for (int i = 0; i < tablesize; i++) {
        if (bankStorage1d[idx].id == id) {
            return true;
        }
        idx = (idx + 1) % mod;
    }

    return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    int idx = hash(id);

    for (int i = 0; i < tablesize; i++) {
        if (bankStorage1d[idx].id == id) {
            Account a;
            a.id="y";
            bankStorage1d[idx] = a;
            return true;
        }
        idx = (idx + 1) % mod;
    }

    return false;
}

int LinearProbing::databaseSize() {

   int size = 0;

    for (int i = 0; i < tablesize; i++) {
        if (!(bankStorage1d[i].id=="x" || bankStorage1d[i].id=="y")) {
            size++;
        }
    }
    return size;
}

int LinearProbing::hash(std::string id) {
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

    hashValue = (hashValue * prime3 + id.length()) % tablesize;

    return hashValue;
}
