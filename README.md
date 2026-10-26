# Dragon Battle

A turn-based, single-player, terminal dragon battler inspired by Dragon City.
Built in C++ for the Object-Oriented Programming course project.

## Team

| Member | Owns | Branch |
|---|---|---|
| A: Vedula Laxmana Venkata Pranay | `Move`, `Dragon` | `feature/dragon` |
| B: Lokeshwaran K | `Player` | `feature/player` |
| C: Keerthivasan P | `Battle` | `feature/battle` |
| D: Pavan V S | `Game`, `Utils`, `main`, Git/CI | `feature/game` |

## Build and run

With make (Linux, macOS, WSL, MinGW):

```
make
./dragon
```

Without make (plain Windows MinGW):

```
g++ -std=c++11 -Wall -Iinclude src/main.cpp src/Move.cpp src/Dragon.cpp src/Player.cpp src/Battle.cpp src/Game.cpp src/Utils.cpp -o dragon
dragon.exe
```

## Repo layout

```
include/   headers (the shared interface; change only via a group-approved PR)
src/       implementations and main.cpp
docs/      DESIGN.md (rules + screens), ISSUES.md (task list), screenshots/

## Read these first

1. `docs/DESIGN.md`: the rules, screens and which class does what
2. `CONTRIBUTING.md`: the Git workflow everyone follows
3. `docs/ISSUES.md`: the task list, one item per GitHub Issue

## Status

- [ ] Mid-sem build: classes, constructors/destructors, composition, friend, `this`, dynamic memory, operator overloading
- [ ] Final build: inheritance, virtual functions, templates, STL, streams, exceptions, file save/load
