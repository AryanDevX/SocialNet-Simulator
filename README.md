# 🧑‍🤝‍🧑 SocialNet Simulator

A command-line social network simulator built in C++ using custom Graph and AVL Tree implementations.  
Now includes **comprehensive error handling** for invalid inputs, usernames with spaces, missing arguments, and more.

---

## Table of Contents
- [Overview](#overview)
- [Data Structures Used](#data-structures-used)
- [File Structure](#file-structure)
- [Build Instructions](#build-instructions)
- [Running the Program](#running-the-program)
- [Supported Commands](#supported-commands)
- [Error Handling](#error-handling)
- [Example Usage](#example-usage)
- [Notes](#notes)

---

## 🧩 Overview

This simulator models a miniature **social network backend** where:
- Each user is represented as a **vertex** in an undirected graph.
- Each friendship is an **edge** between two users.
- Each user’s posts are stored in an **AVL Tree**, ordered by creation time.

The program reads and executes commands from **standard input (stdin)**.

---

## ⚙️ Data Structures Used

| Structure | Purpose |
|------------|----------|
| **Graph** | Manages users and friendships. Provides friend suggestions and degrees of separation. |
| **AVL Tree** | Stores and retrieves user posts efficiently in sorted order. |
| **HashMap (C++ STL)** | Maps usernames to graph vertices for O(1) lookups. |

---

## 📂 File Structure

```
.
├── main.cpp              # Entry point with command parsing & error handling
├── graph.hpp             # Graph class managing users and friendships
├── user.hpp              # User class managing user-specific data and posts
├── AVLTree.hpp           # AVL Tree implementation for posts
├── build.sh              # Shell script to compile and run the program
└── README.md             # Documentation
```

---

## 🏗️ Build Instructions

Make sure you have **g++** installed.

### Linux / macOS / WSL / Git Bash:
```bash
chmod +x build.sh
./build.sh
```

### Windows (PowerShell):
```bash
bash build.sh
```

This will:
- Compile the project using `g++`.
- Generate an executable named `program`.
- Automatically run the simulator.

---

## ▶️ Running the Program

Once built, you can also run manually with:
```bash
./program
```

You’ll see:
```
---------SocialNet Simulator--------
Enter commands (type EXIT to quit):
```

---

## 💬 Supported Commands

### 1️⃣ User Operations
| Command | Description |
|----------|-------------|
| `ADD USER <username>` | Adds a new user. Prevents usernames with spaces and duplicates. |
| `ADD FRIEND <username1> <username2>` | Creates a friendship (must exist beforehand). Validates both usernames. |
| `LIST FRIENDS <username>` | Lists the user’s friends alphabetically. |

---

### 2️⃣ Friend Recommendation
| Command | Description |
|----------|-------------|
| `SUGGEST FRIENDS <username> <N>` | Suggests up to **N** friends-of-friends (ranked by mutual count). Validates username and N. |

---

### 3️⃣ Degrees of Separation
| Command | Description |
|----------|-------------|
| `DEGREES OF SEPARATION <username1> <username2>` | Prints the shortest friendship path or “No connection found.” |

---

### 4️⃣ User Posts
| Command | Description |
|----------|-------------|
| `ADD POST <username> "<content>"` | Adds a new post. Validates username and non-empty content. |
| `OUTPUT POSTS <username> <N>` | Displays most recent **N** posts. Validates number and username. |

---

### 5️⃣ Exit
| Command | Description |
|----------|-------------|
| `EXIT` | Exits the program safely. |

---

## ⚠️ Error Handling

The simulator now includes **robust validation and error messages**:

| Scenario | Error Message |
|-----------|----------------|
| Missing username in `ADD USER` | `No username provided.` |
| Username with spaces | `Username has spaces.` |
| Duplicate user addition | `User <username> has been already added.` |
| Missing usernames in `ADD FRIEND` | `Provide both the usernames.` |
| Nonexistent user in any command | `User '<username>' is not found.` |
| Missing post content | `Provide the content for the post.` |
| Invalid or missing number in `OUTPUT POSTS` | `Provide the number of posts to output.` |
| Non-positive number in `OUTPUT POSTS` | `Invalid number.` |
| Malformed SUGGEST command | `Wrong command format!` or `Invalid SUGGEST command format.` |
| Missing keywords in DEGREES command | `Invalid command. Try again.` |
| Any unknown command | `Invalid command. Try again.` |

These validations ensure that:
- The program **never crashes** on invalid inputs.
- **All user errors** are clearly explained.
- **Input spacing issues** are caught and handled gracefully.

---

## 🧠 Example Usage

```
ADD USER Alice
ADD USER Bob
ADD USER Charlie
ADD FRIEND Alice Bob
ADD FRIEND Bob Charlie
LIST FRIENDS Bob
SUGGEST FRIENDS Alice 2
ADD POST Alice "Hello SocialNet!"
ADD POST Alice "Second post"
OUTPUT POSTS Alice 2
DEGREES OF SEPARATION Alice Charlie
EXIT
```

---

## 📝 Notes

- Usernames **cannot contain spaces**.
- Invalid commands do **not terminate** the program — they simply print an error.
- Posts are output in **reverse chronological order**.
- The program ensures all arguments are validated before use.

---

## 👨‍💻 Author
**Aryan Patel**  
*COL106 Long Assignment 2 — IIT Delhi*  
November 2025
