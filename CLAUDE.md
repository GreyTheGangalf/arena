# Arena — Claude Code instructions

## About the project

A Vampire Survivors-style arena survival game in C++23 with raylib. It is a learning project for CS321 (Programming Paradigms): the same game is reshaped stage by stage with a different paradigm, and every change is judged by measured frame time. The roadmap and the current stage are in `README.md`; read it before starting any task.

## How we work

I am a CS student and I want to learn C++ and paradigms by building this.

- Before writing code, explain in a few sentences what you plan to do and why, then wait for my approval.
- Take one small step at a time. Stay inside the current stage; do not jump ahead to a later paradigm.
- Leave the key, instructive parts to me with `TODO(human)` markers; boilerplate and build configuration you may write yourself.
- When you use a C++ feature I may not know, name the paradigm it belongs to and explain in one sentence why it fits here.
- Never claim a change is faster without a before/after frame time measurement under the same conditions. "The model said so" is not an argument.
- Talk to me in Turkish. Code, identifiers, comments and commit messages are in English.

## Build

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/arena
```

Release measurements: configure a separate `build-release` with `-DCMAKE_BUILD_TYPE=Release`.

Code must compile with zero warnings under `-Wall -Wextra -Wpedantic -Wshadow -Wconversion` and pass `clang-tidy -p build src/*.cpp`.
