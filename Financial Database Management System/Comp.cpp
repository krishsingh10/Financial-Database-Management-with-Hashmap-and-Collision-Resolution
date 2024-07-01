#include "Comp.h"
using namespace std;

void Comp::createAccount(std::string id, int count) {
     int idx = hash(id);
    if(count < 0){
        return;
    }
    if (idx >= 0 && idx < bankStorage2d.size()) {
        for (const auto& acnt : bankStorage2d[idx]) {
            if (acnt.id == id) {
                return;
            }
        }
    }

    Account newacnt = { id, count };
    bankStorage2d[idx].push_back(newacnt);
}

vector<Account> mergeCom(vector<Account>& left, vector<Account>& right) {
        vector<Account> res;
        int idx1 = 0;
        int idx2 = 0;
        while (idx1 < left.size() && idx2 < right.size()) {
            if (left[idx1].balance >= right[idx2].balance) {
                res.push_back(left[idx1]);
                idx1++;
            }
            else {
                res.push_back(right[idx2]);
                idx2++;
            }
        }

        while (idx1 < left.size()) {
            res.push_back(left[idx1]);
            idx1++;
        }

        while (idx2 < right.size()) {
            res.push_back(right[idx2]);
            idx2++;
        }

        return res;
    }

     vector<Account> mergeSortCom(vector<Account>& acnts) {
        if (acnts.size() <= 1) {
            return acnts;
        }

        int mid = acnts.size() / 2;
        vector<Account> left(acnts.begin(), acnts.begin() + mid);
        vector<Account> right(acnts.begin() + mid, acnts.end());

        left = mergeSortCom(left);
        right = mergeSortCom(right);

        return mergeCom(left, right);
    }


std::vector<int> Comp::getTopK(int k) {
      vector<int> topblnce;
    vector<Account> allacnt;
    for (const auto& acnts : bankStorage2d) {
        for (const auto& acnt : acnts) {
            allacnt.push_back(acnt);
        }
    }
    vector<Account> allacnt1;

    allacnt1 = mergeSortCom(allacnt);

    for (int i = 0; i < k && i < allacnt1.size(); i++) {
        topblnce.push_back(allacnt1[i].balance);
    }
    return topblnce;
}

int Comp::getBalance(std::string id) {
     int idx = hash(id);
   if(idx >= 0 && idx < bankStorage2d.size()){
    for(auto& acnt: bankStorage2d[idx]){
        if(acnt.id == id){
            return acnt.balance;
        }
    }
   }
   return -1;
}

void Comp::addTransaction(std::string id, int count) {
   int idx = hash(id);
    if(idx >= 0 && idx < bankStorage2d.size()){
        for(auto &acnt: bankStorage2d[idx]){
             if(acnt.id == id){
                int k = acnt.balance + count;
                if(k >= 0){
                    acnt.balance = acnt.balance + count;
                    return;
                }
             }
        }
    }

    else{
       if(count < 0){
        return;
       }
       if(count >= 0){
        createAccount(id,count);
       }
       return;
    }
}

bool Comp::doesExist(std::string id) {
     int idx = hash(id);
    if (idx >= 0 && idx < bankStorage2d.size()) {
        for (auto& acnt : bankStorage2d[idx]) {
            if (acnt.id == id) {
                return true;
            }
        }
    }
    return false;
}

bool Comp::deleteAccount(std::string id) {
      int idx = hash(id);
    if (idx >= 0 && idx < bankStorage2d.size()) {
        vector<Account>& acnt = bankStorage2d[idx];
        for (auto it = acnt.begin(); it != acnt.end(); ++it) {
            if (it->id == id) {
                acnt.erase(it);
                return true;
            }
        }
    }
    return false;
}
int Comp::databaseSize() {
     int num = 0;
   for(vector<Account>& acnt : bankStorage2d){
    num = num + acnt.size();
   }
   return num;
}

int Comp::hash(std::string id) {
   
    const int prime1 = 31; 
    const int prime2 = 17;  
    const int prime3 = 13; 
    int hashValue = 0;

    int charFrequency[256] = {0};  

    
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

