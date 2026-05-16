# 💬 WhatsApp Console Clone

A **console-based messaging application** written in C++ that simulates core WhatsApp features — including user authentication, private chats, group chats with admin controls, emoji support, message search, and chat export.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Class Design](#class-design)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build with Code::Blocks](#build-with-codeblocks)
  - [Build with g++](#build-with-g)
- [How to Use](#how-to-use)
  - [Authentication](#authentication)
  - [Private Chat](#private-chat)
  - [Group Chat](#group-chat)
  - [Inside a Chat](#inside-a-chat)
- [Emoji Support](#emoji-support)
- [Data & Persistence](#data--persistence)

---

## Overview

This project is a fully interactive terminal messaging app built entirely in C++ using **Object-Oriented Programming**. It models the core concepts behind a real messaging platform: users, messages with timestamps, private one-on-one chats, and multi-user group chats — all navigated through a console menu.

---

## ✨ Features

### 👤 User Management
- **Sign up** with a unique username, phone number, and password (length > 6)
- **Login / Logout** with credential validation
- User **status** (Available) and **last seen** timestamp

### 💬 Messaging
- **Private Chat** — one-on-one messaging between two users
- **Group Chat** — multi-user chat with a named group
- **Reply to messages** — link a message to a previous one
- **Delete messages** — only the original sender can delete
- **Search messages** — keyword-based search within a chat
- **Export chat** — saves full chat history to a `.txt` file
- **Typing indicator** — shown in private chats

### 👑 Group Admin Controls
- Group creator is automatically the **admin**
- Admin can **promote** other participants to admin
- Admin can **remove participants** from the group
- **Join request** system (waitlist for pending approvals)

### 😀 Emoji Support
Shortcodes are automatically converted to real emoji characters:

| Shortcode | Emoji |
|-----------|-------|
| `:)` | 😊 |
| `:(` | 😢 |
| `:D` | 😃 |
| `<3` | ❤️ |
| `:thumbsup:` | 👍 |

---

## 🏗️ Class Design

```
Chat  (base class)
├── participants: vector<string>
├── messages: vector<Message>
├── addMessage(), deleteMessage(), searchMessages(), exportToFile()
│
├── PrivateChat  (extends Chat)
│   ├── user1, user2
│   ├── displayChat()          → shows both usernames
│   └── showTypingIndicator()
│
└── GroupChat  (extends Chat)
    ├── admins: vector<string>
    ├── joinRequests: vector<string>
    ├── addAdmin(), removeParticipant(), isAdmin()
    ├── sendJoinRequest()
    └── displayChat()          → shows group name + all participants

User
├── username, password, phoneNumber, status, lastSeen
├── checkPassword(), changePassword()
├── setPhoneNumber()           → validates digits and optional '+'
└── updateLastSeen()           → uses ctime for real timestamps

Message
├── sender, content, timestamp, status
├── replyTo: Message*          → pointer for reply chain
├── addEmoji()                 → replaces shortcodes with Unicode emoji
├── display()                  → formatted console output
└── updateTimestamp()

WhatsApp  (application controller)
├── users: vector<User>
├── chats: vector<Chat*>
├── signUp(), login(), logout()
├── startPrivateChat(), createGroup(), viewChats()
└── run()                      → main event loop
```

---

## 📁 Project Structure

```
ProjectOne/
│
├── main.cpp              # All source code
│
├── ProjectOne.cbp        # Code::Blocks project file
├── ProjectOne.depend     # Code::Blocks dependency file
├── ProjectOne.layout     # Code::Blocks layout file
│
└── .gitignore
```

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler supporting **C++11 or later** (`g++`, MSVC, Clang)
- No external libraries — uses only the C++ Standard Library
- On Windows: UTF-8 console output is enabled automatically via `SetConsoleOutputCP`

---

### Build with Code::Blocks

1. Open `ProjectOne.cbp` in **Code::Blocks**
2. Select **Debug** or **Release** from the build target dropdown
3. Press `Ctrl+F9` to build
4. Press `Ctrl+F10` to run

---

### Build with g++

**Linux / macOS:**
```bash
g++ -std=c++11 -o ProjectOne main.cpp
./ProjectOne
```

**Windows (MinGW):**
```bash
g++ -std=c++11 -o ProjectOne.exe main.cpp
ProjectOne.exe
```

---

## 🕹️ How to Use

### Authentication

When not logged in, the main menu shows:

```
1. Login
2. Sign Up
3. Exit
```

**Sign Up:**
- Enter a unique username
- Enter a phone number (digits only, optional `+` prefix)
- Enter a password (must be longer than 6 characters)

**Login:**
- Enter your registered username and password

---

### Private Chat

```
1. Start Private Chat
```
- Enter the username of the person you want to chat with
- Type messages and press Enter to send
- Type `exit` to close the chat and return to the menu

---

### Group Chat

```
2. Create Group
```
- Enter a group name
- Enter the number of participants (minimum 2, excluding yourself)
- Add participants by username one by one
- You become the group admin automatically
- Start sending messages immediately; type `exit` to close

---

### Inside a Chat

Once you open a chat from **View Chats**, you can:

```
1. Send Message
2. Search Messages
3. Delete Message
4. Export Chat
5. Exit Chat          (or 5/6/7 for group admins with extra controls)
```

**Group admins** also see:
```
5. Add Admin
6. Remove Participant
7. Exit Chat
```

---

## 😀 Emoji Support

Shortcodes in messages are **automatically converted** when the message is sent. Just type them naturally:

```
"Hello! :) I love this project <3 :thumbsup:"
```

Becomes:

```
"Hello! 😊 I love this project ❤️ 👍"
```

---

## 💾 Data & Persistence

- All data (users, chats, messages) is stored **in memory** during the session
- Data is **not saved** between runs — restarting the app resets everything
- **Chat export** saves a chat's message content to a `.txt` file in the working directory:

```
Enter filename: my_chat
→ Creates: my_chat.txt
```

---

## 👥 Authors

**Group 5 — ProjectOne**
