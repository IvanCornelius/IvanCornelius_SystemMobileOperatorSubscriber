# Mobile Operator Subscriber System

**English** | [Русский](README.ru.md)

A console and GUI application for managing mobile operator subscribers, developed as a freelance project. The system handles subscriber data, call records, and billing details.

## 📋 Project Summary & Technical Details

The system manages subscriber information with the following shared attributes:
*   Phone number
*   Subscriber type (Individual, Legal Entity, Internal Employee)
*   Incoming call duration (minutes)
*   Outgoing call duration (minutes)

**Type-specific attributes:**
*   **Individual:** Full name, passport details, account balance.
*   **Legal Entity:** Tax ID (INN), company name, address.
*   **Internal Employee:** Full name, employee ID.

**Implemented features (as per requirements):**
1.  Add new subscriber.
2.  Log incoming/outgoing call duration by phone number.
3.  Display full subscriber list with all details.
4.  Show individuals with negative balance.
5.  Remove terminated subscribers.
6.  List subscribers belonging to a selected legal entity.

## 🚀 Releases & Version Features

Ready-to-run executables (`.exe`), compiled with *MinGW 7.3.0 32-bit for C++*, are available in the [`/releases`](/releases) folder.

| Version | Interface | Highlights | Download |
| :--- | :--- | :--- | :--- |
| **v1.0.0** (2022-05-16) | Console | Core data management. | [v1.0.0](/releases/v1.0.0) |
| **v2.0.0** (2022-05-17) | Console | Sorted subscriber lists; uses `map`/`multimap` instead of `vector`. | [v2.0.0](/releases/v2.0.0) |
| **v3.0.0** (2022-12-10) | **Qt GUI** | Graphical interface, file dialogs, enhanced sorting. | [v3.0.0](/releases/v3.0.0) |
| **v4.0.0** (2022-12-15) | Qt GUI | Chart dialog for outgoing call duration visualization. | [v4.0.0](/releases/v4.0.0) |

> **Encoding note:** Source code for v1.0.0 and v2.0.0 uses `windows-1251 / CP 1251`.  
> **Test data:** A sample database `test.database.txt` with mock entries is included in source and release folders.

## 🔧 For Developers (Source Code)

Full C++/Qt source code for each version is located in [`/src`](/src).

*   **v1.0.0, v2.0.0:** Standard C++ using STL containers.
*   **v3.0.0, v4.0.0:** Qt-based GUI with custom dialogs, sorting, and QCustomPlot integration (v4.0.0).

## 📄 License

Open-source under the **MIT License**. See [LICENSE](LICENSE) for details.