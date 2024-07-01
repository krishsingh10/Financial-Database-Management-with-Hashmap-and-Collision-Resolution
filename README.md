# Financial-Database-Management-with-Hashmap-and-Collision-Resolution
Designing a hashmap for a banking system to efficiently manage millions of accounts, identified uniquely by IFSC code and account number. Optimizing for fast operations, ensuring data security with encryption, and complying with industry standards and regulations for reliable, scalable performance.

## Project Overview

In this project, you will implement a hashmap to manage bank account information, identified uniquely by a combination of IFSC code and account number. The hashmap will serve as a fundamental component of a banking infrastructure, facilitating operations such as retrieving balances, adding transactions, validating accounts, and managing account data efficiently.

## Implemented Strategies

You will implement four collision resolution strategies:

1. **Chaining**: Manage collisions by using linked lists at each hash table index to handle accounts with the same hash code.
   
2. **Linear Probing**: Navigate hash table slots linearly to find the next available space when a collision occurs, emphasizing proximity and minimizing gaps.

3. **Quadratic Probing**: Use quadratic increments to find the next available slot, balancing proximity and distribution of data.

4. **Cubic Probing**: Employ cubic increments to search for open slots, adding complexity to the probe sequence to distribute data evenly and mitigate clustering issues.

## Functions Implemented

The `BankData` class provides the following functions to interact with the hashmap:

- `void createAccount(string id, int count)`: Create a new account with a unique ID and initial balance.
  
- `vector<int> getTopK(int k)`: Retrieve the top k balance values from the database.

- `int getBalance(string id)`: Get the current balance of an account identified by its ID.

- `void addTransaction(string id, int count)`: Add a transaction (deposit or withdrawal) to the account identified by its ID.

- `bool doesExist(string id)`: Check if an account with a given ID exists in the database.

- `int databaseSize()`: Get the total number of accounts currently stored in the database.

- `int hash(string id)`: Compute the hash value for a given ID.

- `bool delete(string id)`: Delete an account from the database.


## Requirements

- Ensure that all functions handle collisions appropriately based on the chosen strategy.


