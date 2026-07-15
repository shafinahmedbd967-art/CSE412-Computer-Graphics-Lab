# 🎨 OpenGL (GLUT/FreeGLUT) Setup Guide for Visual Studio Code

> A complete guide for running legacy OpenGL (GLUT/FreeGLUT) projects in **Visual Studio Code** using **MinGW GCC** on **Windows**.

---

## 📖 Table of Contents

* [Overview](#-overview)
* [Prerequisites](#-prerequisites)
* [Project Structure](#-project-structure)
* [Verify MinGW Installation](#-verify-mingw-installation)
* [Configure FreeGLUT](#-configure-freeglut)
* [VS Code Configuration](#-vs-code-configuration)
* [Building and Running Programs](#-building-and-running-programs)
* [Creating a New OpenGL Project](#-creating-a-new-opengl-project)
* [Common Errors & Solutions](#-common-errors--solutions)
* [Workflow Summary](#-workflow-summary)

---

# 📌 Overview

This repository contains OpenGL programs originally developed using **Code::Blocks**. This guide explains how to migrate and run those projects in **Visual Studio Code** without modifying the source code.

Supported Technologies:

* OpenGL
* GLUT / FreeGLUT
* MinGW GCC
* Visual Studio Code
* Windows 10 / Windows 11

---

# 📋 Prerequisites

Install the following software before starting.

| Software                  | Required |
| ------------------------- | -------- |
| Visual Studio Code        | ✅        |
| Microsoft C/C++ Extension | ✅        |
| MinGW GCC Compiler        | ✅        |
| FreeGLUT                  | ✅        |

---

# 📁 Project Structure

A recommended folder structure is shown below.

```text
Computer Graphics Lab
│
├── .vscode
│   ├── tasks.json
│   └── launch.json
│
├── Code
│   ├── Lab Day 01
│   │   ├── 01 Program
│   │   │   ├── main.cpp
│   │   │   ├── freeglut.dll
│   │   │   └── main.exe
│   │   └── ...
│   │
│   ├── Lab Day 02
│   ├── Lab Day 03
│   └── ...
│
└── README.md
```

---

# 🔍 Verify MinGW Installation

Open the VS Code terminal and execute:

```bash
g++ --version
```

Expected output:

```text
g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0
```

If the compiler is not found, add the following directory to your Windows **PATH**:

```text
C:\MinGW\bin
```

---

# 📦 Configure FreeGLUT

Assume the FreeGLUT package is located at:

```text
D:\GLUT
```

Directory structure:

```text
GLUT
├── bin
│   └── freeglut.dll
├── include
│   └── GL
│       ├── glut.h
│       ├── freeglut.h
│       ├── freeglut_std.h
│       └── freeglut_ext.h
└── lib
    ├── libfreeglut.a
    └── libfreeglut_static.a
```

## Step 1 — Copy Header Files

Copy:

```text
D:\GLUT\include\GL\
```

Paste into:

```text
C:\MinGW\include\GL\
```

---

## Step 2 — Copy Library Files

Copy:

```text
D:\GLUT\lib\
```

Paste into:

```text
C:\MinGW\lib\
```

---

## Step 3 — Copy DLL

Copy:

```text
D:\GLUT\bin\freeglut.dll
```

Paste it into every OpenGL project folder.

Example:

```text
01 Scaling
│
├── main.cpp
├── freeglut.dll
└── main.exe
```

---

# ⚙️ VS Code Configuration

Create a `.vscode` folder in the project root.

```text
.vscode
├── tasks.json
└── launch.json
```

---

## tasks.json

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build OpenGL",
            "type": "shell",
            "command": "g++",
            "args": [
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-lfreeglut",
                "-lopengl32",
                "-lglu32"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [
                "$gcc"
            ]
        }
    ]
}
```

---

## launch.json

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Run OpenGL Program",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "cwd": "${fileDirname}",
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\MinGW\\bin\\gdb.exe",
            "preLaunchTask": "Build OpenGL"
        }
    ]
}
```

---

# ▶️ Building and Running Programs

## Step 1

Open the **root project folder** in Visual Studio Code.

Example:

```text
Computer Graphics Lab
```

---

## Step 2

Open the required `main.cpp`.

Example:

```text
Code
└── Lab Day 06
    └── 01 Scaling
        └── main.cpp
```

---

## Step 3

Verify that the project folder contains:

```text
main.cpp
freeglut.dll
```

---

## Step 4 — Build

Press:

```text
Ctrl + Shift + B
```

The executable will be generated automatically.

```text
main.exe
```

---

## Step 5 — Run

### Method 1 (Recommended)

Press:

```text
F5
```

VS Code will automatically:

* Build the project
* Generate the executable
* Launch the program
* Open the OpenGL window

---

### Method 2

Open a terminal in the project folder and execute:

```powershell
.\main.exe
```

---

### Method 3

Double-click `main.exe` using File Explorer.

---

# 📂 Creating a New OpenGL Project

For every new OpenGL program:

1. Create a new folder.
2. Copy `main.cpp`.
3. Copy `freeglut.dll`.
4. Open the root project folder in VS Code.
5. Open `main.cpp`.
6. Press **Ctrl + Shift + B**.
7. Press **F5**.

The program will compile and execute automatically.

---

# ❗ Common Errors & Solutions

| Error                                               | Solution                                                                  |
| --------------------------------------------------- | ------------------------------------------------------------------------- |
| `fatal error: GL/glut.h: No such file or directory` | Copy the `include/GL` folder to `C:\MinGW\include\GL\`.                   |
| `cannot find -lfreeglut`                            | Copy `libfreeglut.a` to `C:\MinGW\lib\`.                                  |
| `freeglut.dll was not found`                        | Copy `freeglut.dll` into the project folder.                              |
| `'g++' is not recognized`                           | Add `C:\MinGW\bin` to the Windows PATH environment variable.              |
| `undefined reference to glut...`                    | Ensure `-lfreeglut -lopengl32 -lglu32` are included in the build command. |

---

# 🚀 Workflow Summary

Every time you create a new OpenGL project:

```text
1. Create a project folder
2. Copy main.cpp
3. Copy freeglut.dll
4. Open the root folder in VS Code
5. Open main.cpp
6. Press Ctrl + Shift + B
7. Press F5
```

Your application will be compiled and executed automatically.

---

# 📄 License

This guide is provided for educational purposes and can be freely used in academic OpenGL laboratory projects.
