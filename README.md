# 🧑‍🤝‍🧑 SocialNet Simulator

A command-line social network simulator built in C++ using custom Graph and AVL Tree implementations. Supports adding users, friendships, posts, friend suggestions, and degrees of separation — demonstrating efficient data structure design and algorithms.

---

## 📘 Table of Contents
- [Overview](#overview)
- [Data Structures Used](#data-structures-used)
- [File Structure](#file-structure)
- [Build Instructions](#build-instructions)
- [Running the Program](#running-the-program)
- [Supported Commands](#supported-commands)
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
| **Graph** | Manages users and friendships. Provides features like friend suggestions and degrees of separation. |
| **AVL Tree** | Stores and retrieves user posts efficiently in sorted order. |
| **HashMap (C++ STL)** | Maps usernames to graph vertices for O(1) lookups. |

---

## 📂 File Structure

```
.
├── main.cpp              # Entry point for the simulator
├── graph.hpp             # Graph class managing users and friendships
├── user.hpp              # User class managing user-specific data and posts
├── AVLTree.hpp           # AVL Tree implementation for posts
├── build.sh              # Shell script to compile and run the program
└── COL106_LongAssignment_2.pdf  # Assignment description
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
------- SocialNet Simulator -------
Enter commands (type EXIT to quit):
```

---

## 💬 Supported Commands

### 1️⃣ User Operations
| Command | Description |
|----------|-------------|
| `ADD USER <username>` | Adds a new user to the network. |
| `ADD FRIEND <username1> <username2>` | Creates a friendship between two users. |
| `LIST FRIENDS <username>` | Displays the user’s friends alphabetically. |

---

### 2️⃣ Friend Recommendation
| Command | Description |
|----------|-------------|
| `SUGGEST FRIENDS <username> <N>` | Suggests up to **N** new friends who are “friends of friends”, ranked by mutual friends (then alphabetically). |

---

### 3️⃣ Degrees of Separation
| Command | Description |
|----------|-------------|
| `DEGREES OF SEPARATION <username1> <username2>` | Prints the shortest path length (number of friendships) between two users. Returns `-1` if no connection exists. |

---

### 4️⃣ User Posts
| Command | Description |
|----------|-------------|
| `ADD POST <username> "<content>"` | Adds a new post for the given user. |
| `OUTPUT POSTS <username> <N>` | Displays the most recent **N** posts in reverse chronological order. Use `-1` to display all posts. |

---

### 5️⃣ Exit
| Command | Description |
|----------|-------------|
| `EXIT` | Quits the program. |

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

- Usernames are **case-insensitive**.
- Posts are stored in **reverse chronological order** when output.
- If a command is invalid or incomplete, an appropriate message will be shown.

---

## 👨‍💻 Author
**Aryan Patel**  
*COL106 Long Assignment 2 — IIT Delhi*  
October 2025
