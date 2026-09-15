# Bank Clients Management System

A console-based **C++ bank management system** for managing client records and performing basic banking transactions.
The application stores client data in a text file, allowing data to persist between program runs.

## Features

### Client Management

* **Show Client List** — Displays all clients in a formatted table.
* **Add New Client** — Adds a new client and checks that the account number is unique.
* **Delete Client** — Displays the client's information and asks for confirmation before deletion.
* **Update Client Info** — Updates the PIN code, name, phone number, and account balance.
* **Find Client** — Searches for a client using the account number.

### Transactions

* **Deposit** — Adds money to a client's account balance.
* **Withdraw** — Withdraws money after checking that the requested amount does not exceed the available balance.
* **Total Balances** — Displays all clients and calculates the total balance of all accounts.

## Technologies Used

* **C++**
* File Handling (`fstream`)
* `struct`
* `vector`
* Iterators
* String Manipulation
* Functions
* Basic Input/Output
* Console-based User Interface

## Code Structure

| Function                      | Purpose                                      |
| ----------------------------- | -------------------------------------------- |
| `SplitString`                 | Splits a string into parts using a delimiter |
| `ConvertLineToRecord`         | Converts a file line into a client record    |
| `LoadClientsDataFromFile`     | Loads client data from the text file         |
| `SaveClientsDataToFile`       | Saves client data to the text file           |
| `ShowMainMenu`                | Displays the main menu                       |
| `ShowAllClients`              | Displays all clients in a formatted table    |
| `AddNewClient`                | Adds a new client                            |
| `DeleteClient`                | Deletes a client after confirmation          |
| `UpdateClientByAccountNumber` | Updates a client's information               |
| `FindClient`                  | Searches for a client by account number      |
| `Deposit`                     | Deposits money into an account               |
| `Withdraw`                    | Withdraws money from an account              |
| `TotalBalances`               | Calculates and displays total balances       |
| `Transactions`                | Displays and handles the transactions menu   |
| `StartBankSystem`             | Controls the main program loop               |


## Future Improvements

Some possible improvements for future versions:

* Add PIN verification before sensitive operations.
* Add stronger input validation.
* Prevent invalid or negative transaction amounts.
* Replace `system("pause>0")` with a more portable solution.
* Improve error handling for file operations.
* Refactor the client structure into a class using OOP principles.
* Add transaction history.
* Add authentication and different user roles.

## Project Status

This project was built as a **C++ practice project** to apply programming fundamentals, file handling, vectors, iterators, functions, and problem-solving concepts in a complete console application.
