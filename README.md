# Bank System Console App (C++)

## 📌 Overview

A simple **Bank Management System** built in C++ for learning purposes. The program manages clients' data stored in a text file and provides an interactive console menu to perform operations like adding, deleting, updating, and listing clients.

---

## ✨ Features

* Add, update, and delete clients
* Search for clients by account number
* Display all clients in a formatted table
* Deposit and withdraw money
* Data persistence using text files
* Simple, menu-driven interface

---

## 🗂 Data Storage

All client information is stored in a plain text file (`Clients.txt`) with a custom delimiter `#//#`.

**Example record:**

```
A123#//#1234#//#John Doe#//#123456789#//#5000.50
```

**Fields:**

1. Account Number
2. PIN Code
3. Name
4. Phone
5. Account Balance

---

## 📖 Menu Options

1. Show Clients List
2. Add New Client
3. Delete Client
4. Update Client Info
5. Find Client
6. Deposit
7. Withdraw
8. Exit

---

## ⚙️ How to Build & Run

### Using g++ (MinGW / Linux / macOS)

```bash
g++ main.cpp -o BankSystem
./BankSystem
```

### Using MSVC (Visual Studio)

* Create a new C++ Console Project
* Add source files
* Build & Run

---

## 🔧 Configuration

* File path: Update the `ClientsFileName` constant in code if needed.
* Delimiter: Can be changed from `#//#` to another symbol if preferred.

---

## 🚀 Future Improvements

* Add authentication system (login with account + PIN)
* Support transactions history
* Encrypt client data
* Improve UI with colors / better formatting

---

## 📜 License

This project is open-source under the **MIT License**.
