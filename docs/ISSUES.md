# Task list (one GitHub Issue per line)

Labels: `midsem` or `final`, plus `member-A` to `member-D`. Everything below is `midsem` unless marked.

## Member A: `Move`, `Dragon`
- [ ] A1 Finish `Move` (name, power, cooldown, `use`/`tick`)
- [ ] A2 `Dragon` constructors, copy constructor, destructor message
- [ ] A3 Static counter `totalCreated` and `getTotalCreated()`
- [ ] A4 `operator<<` and `operator>>` (friend)
- [ ] A5 Friend `showStats()` full stat card
- [ ] A6 `operator-=` (damage, honours Defend, clamps at 0)
- [ ] A7 `heal`, `defend`, `endTurn`, `levelUp` returning `*this` (chaining)
- [ ] A8 `operator+` breeding (rules in `docs/DESIGN.md`)
- [ ] A9 `==`, `<`, `>` by power; prefix and postfix `++`
- [ ] A10 `final`: make `Dragon` abstract, add `FireDragon`/`WaterDragon`/`EarthDragon` with `specialAttack()`

## Member B: `Player`
- [ ] B1 Constructor, destructor (`delete[]`), `getCount`, getters
- [ ] B2 Deep-copy constructor and `operator=` (self-assignment safe)
- [ ] B3 `addDragon` with `grow()` (capacity 2 up to 6, `new[]`/`delete[]`)
- [ ] B4 Bounds-checked `getDragon`, `hasLivingDragon`, `firstLivingIndex`
- [ ] B5 `breed(i, j)` using `Dragon::operator+`
- [ ] B6 `healAll()` and `unlockNextStage()` chainable
- [ ] B7 `operator<<` for `Player` (stable listing)
- [ ] B8 `final`: `Team<T>` class template; `vector` version of the stable

## Member C: `Battle`
- [ ] C1 `showStatus()` using `Utils::hpBar`
- [ ] C2 Player menu loop and Attack / Special actions
- [ ] C3 Defend, Heal (3 uses), Switch, view Stats, Forfeit
- [ ] C4 Faint handling, forced switch, win/lose detection
- [ ] C5 Enemy AI (rules in `docs/DESIGN.md`)
- [ ] C6 `run()` returns true on player win; turn counter
- [ ] C7 `final`: custom exceptions, throw/catch/re-throw; element effectiveness `map`

## Member D: `Game`, `Utils`, `main`, repo
- [ ] D1 Repo settings, labels, Issues, branch rule (see `CONTRIBUTING.md`)
- [ ] D2 `Utils::readInt` / `readLine` safe against bad input
- [ ] D3 `Utils::hpBar`, `banner`, `pause`
- [ ] D4 Catalog of 8 dragons (dynamic array) and `showCatalog`
- [ ] D5 First-run setup (name, pick 2 starters as copies)
- [ ] D6 Main menu, My Stable, How to Play
- [ ] D7 `buildEnemy(stage)` for stages 1 to 3; win/lose handling and level-ups
- [ ] D8 Breed menu
- [ ] D9 Integration and bug fixing (Day 4); keep `make` green
- [ ] D10 `final`: save/load `save.dat`, `setw`/`setfill` tables

## Everyone
- [ ] S1 Run each of your features and save a screenshot to `docs/screenshots/`
- [ ] S2 Write the report section(s) for your own concepts (snippet + screenshot + one line on the game feature)
- [ ] S3 D assembles the report; source code goes in the annexure
