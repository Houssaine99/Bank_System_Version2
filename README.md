# 🏦 Bank Management System

A feature-rich, console-based bank management system built in **C++**, implementing object-oriented principles with a clean layered architecture. The system supports full client and user management, financial transactions, currency exchange, and audit logging.

---

## 📋 Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Architecture Overview](#architecture-overview)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Permissions System](#permissions-system)
- [Data Storage](#data-storage)
- [Technologies Used](#technologies-used)

---

## ✨ Features

### 👥 Client Management
- Add, update, delete, and search for bank clients
- View a full list of all clients
- Each client has: First Name, Last Name, Email, Phone, Account Number, PIN Code, and Balance

### 💰 Transactions
- **Deposit** funds into a client's account
- **Withdraw** funds with balance validation
- **Transfer** money between accounts with full logging
- View **Total Balances** across all accounts
- **Transfer Log** — complete audit trail of all transfers

### 👤 User Management
- Add, update, delete, and search for system users
- Granular **permissions system** controlling what each user can access
- Login history register for all users

### 💱 Currency Exchange
- List all supported currencies (country, code, name, rate)
- Find a currency by country or code
- Update currency exchange rates
- **Currency Calculator** — convert any amount between currencies
- **Currency Exchange Screen** — perform live conversions

### 🔐 Authentication
- Login screen with **3-attempt lockout** for security
- Login activity logged with timestamp, username, and permissions
- Session-based current user tracking

---

## 📁 Project Structure

```
Bank_System/
│
├── Bank_System.cpp              # Entry point (main)
├── Global.h                     # Global CurrentUser instance
│
├── Core/                        # Business logic / domain models
│   ├── clsPerson.h              # Base class: first name, last name, email, phone
│   ├── clsBankClient.h          # Client entity with file I/O and transactions
│   ├── clsUser.h                # User entity with permissions and login register
│   └── clsCurrency.h            # Currency entity with exchange logic
│
├── Lib/                         # Reusable utility library
│   ├── clsUtil.h                # Colors, UI drawing, encryption, number-to-text
│   ├── clsString.h              # String manipulation helpers
│   ├── clsDate.h                # Date/time utilities
│   └── clsInputValidate.h       # Safe input reading and validation
│
├── Screens/                     # Presentation layer
│   ├── clsScreen.h              # Base screen class (header drawing, permission checks)
│   ├── clsMainScreen.h          # Main menu
│   ├── clsLoginScreen.h         # Login screen with lockout
│   │
│   ├── Client/                  # Client-related screens
│   │   ├── clsListClientsScreen.h
│   │   ├── clsAddNewClientScreen.h
│   │   ├── clsDeleteClientScreen.h
│   │   ├── clsUpdateClientScreen.h
│   │   ├── clsFindClientScreen.h
│   │   ├── clsDepositScreen.h
│   │   ├── clsWithdrawScreen.h
│   │   ├── clsTransferScreen.h
│   │   ├── clsTransferLogScreen.h
│   │   ├── clsTotalBalancesScreen.h
│   │   ├── clsTransactionsScreen.h
│   │   └── clsLoginRegisterScreen.h
│   │
│   ├── User/                    # User management screens
│   │   ├── clsListUsersScreen.h
│   │   ├── clsAddNewUserScreen.h
│   │   ├── clsDeleteUserScreen.h
│   │   ├── clsUpdateUserScreen.h
│   │   ├── clsFindUserScreen.h
│   │   └── clsManageUsersScreen.h
│   │
│   └── Currency/                # Currency exchange screens
│       ├── clsListCurrenciesScreen.h
│       ├── clsFindCurrencyScreen.h
│       ├── clsUpdateRateScreen.h
│       ├── clsCurrencyCalculatorScreen.h
│       └── clsCurrencyExchangeScreen.h
│
└── Data/                        # Flat-file data storage
    ├── Clients.txt
    ├── Users.txt
    ├── Currencies.txt
    ├── TransferLog.txt
    └── LoginRegister.txt
```

---

## 🏗️ Architecture Overview

The project follows a **3-layer architecture**:

| Layer | Folder | Responsibility |
|---|---|---|
| **Data / Domain** | `Core/` | Business entities, file I/O, business rules |
| **Utilities** | `Lib/` | Reusable helpers: strings, dates, validation, UI |
| **Presentation** | `Screens/` | User-facing menus and screens |

Core classes use a **Mode Pattern** (`EmptyMode`, `UpdateMode`, `AddNewMode`) to safely distinguish between new and existing records, and a **Save()** method that dispatches to the correct internal operation.

---

## 🚀 Getting Started

### Prerequisites
- Windows OS (uses `system("cls")` and `system("pause")`)
- Visual Studio 2019 or later (project includes `.sln` and `.vcxproj` files)
- C++17 or later

### Build & Run

1. Clone or download the repository
2. Open `Bank_System(Fully By Me).sln` in Visual Studio
3. Build the solution (`Ctrl+Shift+B`)
4. Run the executable (`F5` or `Ctrl+F5`)
5. Make sure the `Data/` folder is in the **working directory** (same level as the `.exe`)

> ⚠️ The application reads and writes data files using relative paths (`Data/Clients.txt`, etc.). Ensure your working directory is set correctly in Visual Studio under **Project → Properties → Debugging → Working Directory**.

---

## 🖥️ Usage

On launch, you are presented with the **Login Screen**. Enter a valid username and password. After 3 failed attempts, the session is locked.

### Main Menu Options

| # | Option | Permission Required |
|---|---|---|
| 1 | Show Client List | `pListClient` |
| 2 | Add New Client | `pAddNewClient` |
| 3 | Delete Client | `pDeleteClient` |
| 4 | Update Client | `pUpdateClient` |
| 5 | Find Client | `pFindClient` |
| 6 | Transactions | `pTransactions` |
| 7 | Manage Users | `pManageUsers` |
| 8 | Login Register | `pLoginRegister` |
| 9 | Currency Exchange | `pCurrencyExchange` |
| 10 | Logout | — |

---

## 🔐 Permissions System

User permissions are stored as a **bitmask integer**, allowing fine-grained access control:

| Permission | Value |
|---|---|
| All (Admin) | `-1` |
| List Clients | `1` |
| Add New Client | `2` |
| Delete Client | `4` |
| Update Client | `8` |
| Find Client | `16` |
| Transactions | `32` |
| Manage Users | `64` |
| Login Register | `128` |
| Currency Exchange | `256` |

Permissions are combined using bitwise OR. For example, a user with `List Clients + Transactions` has permission value `33`.

---

## 💾 Data Storage

All data is persisted in plain text files using a `#//# ` delimiter:

| File | Contents |
|---|---|
| `Clients.txt` | Client records (name, email, phone, account number, encrypted PIN, balance) |
| `Users.txt` | User records (name, email, phone, username, encrypted password, permissions) |
| `Currencies.txt` | Currency data (country, code, name, rate vs USD) |
| `TransferLog.txt` | Transfer audit log (timestamp, source, destination, amount, balances) |
| `LoginRegister.txt` | Login history (timestamp, username, encrypted password, permissions) |

> Passwords and PINs are encrypted using a Caesar cipher (shift of 5).

---

## 🛠️ Technologies Used

- **Language:** C++17
- **IDE:** Visual Studio 2022
- **Storage:** Flat-file text database
- **UI:** ANSI escape codes for terminal colors
- **Platform:** Windows (console application)

---

## 👨‍💻 Author

Developed entirely from scratch as a personal learning project to practice object-oriented C++ design, layered architecture, and console UI development.
