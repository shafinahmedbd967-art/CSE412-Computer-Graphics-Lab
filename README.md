# CSE412 — Computer Graphics Lab

![Course](https://img.shields.io/badge/Course-CSE412-blue.svg)
![University](https://img.shields.io/badge/Daffodil%20International%20University-DIU-orange.svg)
![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C.svg)
![Graphics](https://img.shields.io/badge/Graphics-OpenGL%20%2F%20GLUT-green.svg)
![Status](https://img.shields.io/badge/Status-Semester%20Completed-brightgreen.svg)

A complete, semester-long archive of my **Computer Graphics Lab (CSE412)** coursework at **Daffodil International University**, covering every lab exercise, algorithm implementation, lab report, and the final mini project completed over the course of the semester. This repository documents my hands-on journey through fundamental computer graphics concepts using **C++, OpenGL, and GLUT** — from drawing basic primitives to building a full interactive 2D/3D scene.

---

## 📖 Table of Contents

- [Overview](#-overview)
- [Repository Structure](#-repository-structure)
- [Topics Covered](#-topics-covered)
- [Lab-Wise Breakdown](#-lab-wise-breakdown)
- [Final Mini Project](#-final-mini-project)
- [Tech Stack](#-tech-stack)
- [Getting Started](#-getting-started)
- [Acknowledgements](#-acknowledgements)
- [Author](#-author)
- [License](#-license)

---

## 🎯 Overview

This repository is **not a single project** — it is my full lab record for the **CSE412: Computer Graphics Lab** course, developed and committed progressively across the entire semester (**156+ commits**). It includes everything I worked on throughout the course: individual lab exercises, algorithm implementations, official lab reports, lab manuals provided by the department, and the final group mini project.

The goal of this course was to move from theory to practice — implementing core computer graphics algorithms (line drawing, circle drawing, transformations, clipping, curves, and animation) by hand in OpenGL, before combining everything into one complete interactive scene for the final project.

---

## 🗂️ Repository Structure

```
CSE412-Computer-Graphics-Lab/
├── .vscode/          # Editor/build configuration
├── Code/             # Source code for each lab exercise / algorithm implementation
├── Lab Manual/        # Official lab manuals and instructions provided for the course
├── Lab Report/         # Submitted lab reports for individual experiments
├── Lab Work/           # In-lab exercises, practice programs, and drafts
├── Project/            # Final mini project (Interactive Bangladeshi Primary School — OpenGL)
└── README.md
```

---

## 🧩 Topics Covered

Throughout the semester, this lab covered the following core areas of computer graphics, implemented practically using OpenGL:

**A. Graphics Primitives & Algorithms**
- Points and line drawing
- DDA and Bresenham's line drawing algorithms
- Midpoint Circle drawing algorithm
- Curve generation algorithms (including Bézier curves)
- Line clipping algorithms

**B. Geometric Transformations**
- 2D transformations: translation, rotation, scaling, reflection, shear
- 3D transformations and viewing concepts

**C. Color & Animation**
- RGB color model and color application
- Basic computer animation and moving objects

**D. Scene Design Using OpenGL**
- Real-life, application-based graphics project development
- Interactive scene/game design with keyboard-driven input

---

## 🧪 Lab-Wise Breakdown

| Week | Experiment | Key Concept |
|---|---|---|
| 1 | Introduction to OpenGL & Draw a Home | OpenGL setup, basic shape drawing |
| 2 | Four Stars with Color Variations | Multiple shapes, RGB color model |
| 3 | DDA & Bresenham's Line Drawing | Line rasterization algorithms |
| 4 | Midpoint Circle Drawing Algorithm | Circle rasterization |
| 5 | Shaheed Minar, Bicycle & Bangladesh Flag | Composite scenes using line/circle algorithms |
| 6 | 2D Transformations | Translation, rotation, scaling |
| 7 | Project Planning | Requirement analysis, initial design |
| 8 | Moving Particles (Basic Animation) | Timer-based animation |
| 9 | Drawing 3D Objects | 3D primitives |
| 10 | 3D Transformations | 3D translation, rotation, scaling |
| 11 | Clipping Algorithm | Line clipping |
| 12 | Project Development | Coding, debugging, refinement |
| 13 | Bézier Curve Algorithm | Curve generation |
| 14 | Final Project Presentation & Viva | Demonstration and evaluation |

> Full lab reports for each experiment are available in the [`Lab Report`](./Lab%20Report) folder, and corresponding source code is in [`Code`](./Code).

---

## 🏫 Final Mini Project

**Interactive Modern Bangladeshi Primary School Environment (OpenGL/GLUT)**

The semester's coursework culminated in a full-scale group project: an animated, interactive 2D/3D simulation of a Bangladeshi primary school campus, featuring a school building, garden, Shaheed Minar, playground, boundary wall with a working gate, roads with moving vehicles, ambient sound, and real-time keyboard interactivity.

📁 Located in [`/Project`](./Project)
🔗 Standalone repository: [Bangladesh-Primary-School-OpenGL](https://github.com/shafinahmedbd967-art/Bangladesh-Primary-School-OpenGL)

---

## 🛠️ Tech Stack

- **Language:** C++
- **Graphics API:** OpenGL (fixed-function / immediate mode)
- **Windowing & Input:** GLUT / freeglut
- **IDE:** Visual Studio Code
- **Documentation:** Microsoft Word / PDF (Lab Reports & Manuals)

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (MinGW / MSVC)
- **freeglut** (or classic GLUT) development libraries and headers
- Visual Studio Code or any C++ IDE

### Running a Lab Exercise
```bash
git clone https://github.com/shafinahmedbd967-art/CSE412-Computer-Graphics-Lab.git
cd CSE412-Computer-Graphics-Lab/Code
g++ <filename>.cpp -o output.exe -lfreeglut -lopengl32 -lglu32
output.exe
```

Each experiment's source file is organized inside the `Code` folder, generally matching the corresponding week/topic from the lab-wise breakdown above.

---

## 🙏 Acknowledgements

This repository reflects my own hands-on work and learning throughout the CSE412 course, completed over 4 months of the semester. While the core implementation, logic, and creative direction are my own, I made use of **AI assistants — ChatGPT, Claude, and Gemini** — at various points for debugging help, code explanation, documentation/report formatting, and general guidance. I'm crediting them here for transparency, since they were a genuine part of my learning and workflow throughout this course.

---

## 👤 Author

**Shafin Ahmed**
Department of Computer Science and Engineering
Daffodil International University

- GitHub: [@shafinahmedbd967-art](https://github.com/shafinahmedbd967-art)
- Repository: [CSE412-Computer-Graphics-Lab](https://github.com/shafinahmedbd967-art/CSE412-Computer-Graphics-Lab)

---

## 📄 License

This project is licensed under the **MIT License**. Feel free to explore, learn from, or reference this work for educational purposes.

```
MIT License

Copyright (c) 2026 Shafin Ahmed

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

<p align="center">A semester of learning computer graphics — one algorithm at a time. 🇧🇩</p>
