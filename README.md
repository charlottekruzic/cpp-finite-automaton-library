# Finite automaton library
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey.svg)](https://opensource.org/licenses/MIT)

## 🔎 Overview

This project implements a C++ library for working with finite automata (FA). It provides a comprehensive set of operations for creating, manipulating, and analyzing finite automata.

## ⚙️ Features

The library includes the following key features:

- **Basic automaton operations**:
  - Creation and manipulation of states and transitions
  - Support for epsilon transitions
  - Management of initial and final states
  - Addition and removal of symbols from the alphabet

- **Automaton analysis**:
  - Determinism checking (`isDeterministic()`)
  - Completeness checking (`isComplete()`)
  - Empty language detection (`isLanguageEmpty()`)
  - Word matching (`match()`)
  - String reading and state calculation (`readString()`)

- **Automaton transformations**:
  - Determinization (`createDeterministic()`)
  - Completion (`createComplete()`)
  - Minimization via Moore algorithm (`createMinimalMoore()`)
  - Minimization via Brzozowski algorithm (`createMinimalBrzozowski()`)
  - Mirroring (`createMirror()`)
  - Complementation (`createComplement()`)
  - Product construction (`createProduct()`)

- **State accessibility**:
  - Removal of non-accessible states (`removeNonAccessibleStates()`)
  - Removal of non-co-accessible states (`removeNonCoAccessibleStates()`)

- **Language relations**:
  - Language inclusion testing (`isIncludedIn()`)
  - Empty intersection testing (`hasEmptyIntersectionWith()`)

## 🛠️ Building the project

The project uses CMake as its build system. To build the project:

```bash
# Create a build directory
mkdir build && cd build

# Generate build files with CMake
cmake ..

# Build the project
make
```

## 🧪 Testing

The project includes a comprehensive test suite using Google Test. After building the project, you can run the tests:

```bash
./testfa
```

## 📋 Requirements

- C++17 compatible compiler
- CMake 3.10 or higher
- Google Test (included in the project)

## 📐 Project structure

- `Automaton.h`: Header file defining the `Automaton` class and related structures
- `Automaton.cc`: Implementation of the `Automaton` class
- `testfa.cc`: Test suite for the automaton library
- `CMakeLists.txt`: CMake build configuration

## 💡 Usage example

Here's a simple example of how to use the library:

```cpp
#include "Automaton.h"
#include <iostream>

int main() {
    // Create an automaton that accepts strings ending with 'a'
    fa::Automaton automaton;
    
    // Add states
    automaton.addState(0);
    automaton.addState(1);
    
    // Set initial and final states
    automaton.setStateInitial(0);
    automaton.setStateFinal(1);
    
    // Define the alphabet
    automaton.addSymbol('a');
    automaton.addSymbol('b');
    
    // Add transitions
    automaton.addTransition(0, 'a', 1);
    automaton.addTransition(0, 'b', 0);
    automaton.addTransition(1, 'a', 1);
    automaton.addTransition(1, 'b', 0);
    
    // Test some strings
    std::cout << "Does 'a' match? " << (automaton.match("a") ? "Yes" : "No") << std::endl;
    std::cout << "Does 'ababa' match? " << (automaton.match("ababa") ? "Yes" : "No") << std::endl;
    std::cout << "Does 'abb' match? " << (automaton.match("abb") ? "Yes" : "No") << std::endl;
    
    // Print the automaton
    std::cout << "\nAutomaton structure:\n";
    automaton.prettyPrint(std::cout);
    
    return 0;
}
```
## 📝 Project assignment
For more information about the purpose of this project, you can find the [complete project assignment file](./resources/project-assignment-fr.pdf) (in french) within this repository. This project is part of the third-year Bachelor's degree in Computer Science at the University of Franche-Comté.
