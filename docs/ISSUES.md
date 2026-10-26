# Task list (one GitHub Issue per line)

Labels: `midsem` or `final`, plus `member-A` to `member-D`. Everything below is `midsem` unless marked.
Mid-sem items are all done; the `final` items are planned.

## Member A: `Move`, `Dragon`
- [x] A1 Finish `Move` (name, power, cooldown, `use`/`tick`)
- [x] A2 `Dragon` constructors, copy constructor, destructor message
- [x] A3 Static counter `totalCreated` and `getTotalCreated()`
- [x] A4 `operator<<` and `operator>>` (friend)
- [x] A5 Friend `showStats()` full stat card
- [x] A6 `operator-=` (damage, honours Defend, clamps at 0)
- [x] A7 `heal`, `defend`, `endTurn`, `levelUp` returning `*this` (chaining)
- [x] A8 `operator+` breeding (rules in `docs/DESIGN.md`)
- [x] A9 `==`, `<`, `>` by power; prefix and postfix `++`
- [ ] A10 `final`: make `Dragon` abstract, add `FireDragon`/`WaterDragon`/`EarthDragon` with `specialAttack()`

## Member B: `Player`
- [x] B1 Constructor, destructor (`delete[]`), `getCount`, getters
- [x] B2 Deep-copy constructor and `operator=` (self-assignment safe)
- [x] B3 `addDragon` with `grow()` (capacity 2 up to 6, `new[]`/`delete[]`)
- [x] B4 Bounds-checked `getDragon`, `hasLivingDragon`, `firstLivingIndex`
- [x] B5 `breed(i, j)` using `Dragon::operator+`
- [x] B6 `healAll()` and `unlockNextStage()` chainable
- [x] B7 `operator<<` for `Player` (stable table with level, HP, attack, defense and element)
- [ ] B8 `final`: `Team<T>` class template; `vector` version of the stable

## Member C: `Battle`
- [x] C1 `showStatus()` using `Utils::hpBar`
- [x] C2 Player menu loop and Attack / Special actions
- [x] C3 Defend, Heal (3 uses), Switch, view Stats, Forfeit
- [x] C4 Faint handling (with a "fainted" message), forced switch, win/lose detection
- [x] C5 Enemy AI (rules in `docs/DESIGN.md`)
- [x] C6 `run()` returns true on player win; turn counter
- [ ] C7 `final`: custom exceptions, throw/catch/re-throw; element effectiveness `map`

## Member D: `Game`, `Utils`, `main`, repo
- [x] D1 Repo, branches and Git workflow (see `CONTRIBUTING.md`)
- [x] D2 `Utils::readInt` / `readLine` safe against bad input
- [x] D3 `Utils::hpBar`, `banner`, `pause`
- [x] D4 Catalog of 8 dragons (dynamic array) and `showCatalog`
- [x] D5 First-run setup (name, pick 2 starters as copies)
- [x] D6 Main menu, My Stable, How to Play
- [x] D7 `buildEnemy(stage)` for stages 1 to 3; win/lose handling and level-ups
- [x] D8 Breed menu
- [x] D9 Integration and bug fixing; the build command in the README compiles cleanly
- [x] D10 Squad selection: `buildSquad` lets the player pick up to 3 dragons, who fight as copies
- [ ] D11 `final`: save/load `save.dat`, `setw`/`setfill` tables

## Carried over to the final
- [ ] Element effectiveness table, also used to decide a bred dragon's element (replaces the plain text joining)
- [ ] Silence switch for the `Dragon` destructor message while the catalog is built
- [ ] Colourised and cleaner battle screens