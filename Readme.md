# 🎓 Programming & Algorithms 1 C/C++ codes

> C++ programs from basics to file management.

![C++](https://img.shields.io/badge/C%2B%2B-98-blue?logo=cplusplus)
![Build](https://img.shields.io/badge/build-CMake-informational)
![License](https://img.shields.io/badge/license-MIT-green)

---

## 📂 Repository Structure

```
.
├── src/                # Source code (.cpp)
│   ├── program-01/ (example, not real name)
│   └── program-02/
├── tests/              # Unit tests
├── docs/               # Reports, diagrams, notes
├── CMakeLists.txt      # Build configuration
├── .gitignore
└── README.md
```

---

## 🧾 Program Index

| #  | Program          | Description                    | Status         |
|----|------------------|--------------------------------|----------------|
| 01 | Examen Parcial 1 | Implementing LU descomposition | ✅ Done         |
<!--✅ Done -->
<!--🚧 In progress -->
<!--⏳ Pending  -->
---

## ⚙️ Requirements

- C++ compiler with C++98 support (developed and tested with GCC 4.9.2)
- [CMake](https://cmake.org/) ≥ 3.16
- [Optional] [GoogleTest](https://github.com/google/googletest) (downloaded automatically by CMake)

---

## 🔨 Build

```bash
# Configure
cmake -S . -B build

# Compile
cmake --build build
```

Or compile a single program directly:

```bash
g++ -std=c++98 -Wall -Wextra -O2 src/program-01/main.cpp -o program-01
```

---

## ▶️ Run

```bash
./build/program-01
```
**Example:**

```
$ ./build/program-01
Input: 
Output: 
```

---

## 🧪 Testing

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

[Describe what is tested and how to add new tests.]

---

## 🌿 Branching Model

| Branch       | Purpose                                         |
|--------------|-------------------------------------------------|
| `main`       | Stable, reviewed, final versions of programs    |
| `develop`    | Integration branch — tested work before `main`  |
| `feature/*`  | New programs or features                        |
| `fix/*`      | Bug fixes                                       |

Workflow: `feature/*` → `develop` (tests pass) → `main` (tagged release).

---

## 📝 Commit Convention

```
feat: add program 03 (matrix multiplication)
fix: correct off-by-one in binary search
test: add unit tests for linked list
docs: update README program index
refactor: split utils into separate header
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE) — or [state academic use only].

---

## 👤 Author

**Angel Isaac Saldivar Delgado**
- GitHub: [@AngelKode](https://github.com/AngelKode)