# Design: Turn-Based Elemental Battle Simulator (Dragon Battle)

Single source of truth for rules, screens and class responsibilities. If the code and this
file disagree, fix one of them in a PR instead of letting them drift.

## 1. The game in one paragraph

One player profile per device. You pick two starter dragons from a read-only catalog. Before each
battle you choose up to three dragons from your stable as a squad, and fight three hard-coded
enemy stages. Winning levels up your squad, and you can breed new dragons from your stable.
Everything runs in the terminal. Progress lives in memory only for the mid-sem build; `save.dat`
arrives in the final.

## 2. Fixed rules (everyone codes to these)

| Rule | Value |
|---|---|
| Stable size | max 6 dragons (array starts at capacity 2 and grows with `new[]`/`delete[]`) |
| Level-1 stats | HP 100, attack 10 to 30, defense 5 to 15 (the catalog values are in section 3) |
| Damage | `max(1, attacker.attack + move.power - target.defense)` |
| Basic move | power +0, no cooldown |
| Special move | power +15, 3-turn cooldown |
| Defend | halves the next hit taken (min 1); ends when that hit lands or the owner's next turn starts |
| Heal | +30 HP (never above max), 3 uses per battle |
| Squad | up to 3 dragons (`Game::SQUAD_MAX`), picked from the stable before each battle; the same dragon cannot be picked twice |
| Switch | costs the turn; cannot switch to a fainted dragon or the one already fighting |
| Faint | dragon at 0 HP; forced switch is free |
| Level up | level +1, max HP +10, attack +2, defense +1, HP refilled |
| Comparing dragons | `power = attack*2 + defense + maxHp/10`; `==` and `<` compare power |
| Breeding | needs two different dragons, stable not full, parents are kept |
| Child stats | average of parents + 2 each; HP is the average; level 1 |
| Child element | parent 1's element if equal, else `"Fire/Water"` style (plain text joining, so it can grow when bred again; an element table is planned for the final) |
| Child name | first half of parent 1's name + second half of parent 2's |
| Battle state | the squad fights as **copies**, so HP, cooldowns and Defend never reach the stable |
| Win a stage | every dragon in the squad levels up in the stable, next stage unlocks |
| Lose a stage | back to menu, no penalty |

## 3. Starter catalog (8 dragons, final values)

| Name | Element | ATK | DEF |
|---|---|---|---|
| Ember | Fire | 26 | 7 |
| Aqua | Water | 20 | 10 |
| Rocky | Earth | 18 | 14 |
| Gale | Air | 24 | 8 |
| Frost | Ice | 22 | 11 |
| Spark | Electric | 28 | 6 |
| Leafy | Nature | 19 | 12 |
| Shade | Dark | 25 | 9 |

All start at HP 100. Picking one creates a **copy** (copy constructor); the catalog is never modified.

## 4. Stages (hard-coded in `Game::buildEnemy`)

| Stage | Enemy team | Dragon level |
|---|---|---|
| 1 | 2 catalog dragons | 1 |
| 2 | 3 catalog dragons | 2 (call `levelUp` once) |
| 3 (boss) | 3 catalog dragons | 3 (call `levelUp` twice) |

Enemy AI each turn: roll 1 to 100. 1-70 attack, 71-90 defend, 91-100 heal if its dragon is
below half HP (otherwise attack). The enemy also has 3 heals per battle.

`Game::startBattle` copies the player's current stage into the squad, so the battle screen shows
the right stage number. On a win it levels up the **original** dragons at the positions the player
picked, then unlocks the next stage.

## 5. Classes

| Class | Owner | Responsibility |
|---|---|---|
| `Move` | A | name, power, cooldown; used by Dragon (composition) |
| `Dragon` | A | stats, `Move moves[2]`, all operators, friend functions, static counter |
| `Player` | B | name, dynamic `Dragon* stable`, stage progress, breeding, stable table (`operator<<`); also used for the enemy team and the battle squad |
| `Battle` | C | takes `Player&` (you) and `Player&` (enemy), runs the turn loop and enemy AI |
| `Game` | D | owns the catalog and your profile, runs menus, builds the squad and the enemy teams |
| `Utils` | D | safe input, HP bar, banner, pause |

Default `Dragon()` is for placeholder array slots and does **not** increment the static counter;
the named and copy constructors do.

## 6. Screens

### First run

```
+-----------------+
|  DRAGON BATTLE  |
+-----------------+

Enter your trainer name: Zap

Welcome Zap !
Now, let's get your Starter Dragons set up !

No. Name        Element     HP      ATK     DEF     
----------------------------------------------------
1   Ember       Fire        100     26      7        
 ...
```

### Main menu

```
1. Battle (next stage)
2. Breed Dragons
3. My Stable
4. How to Play
5. Exit
```

Final-only additions: Save, Load.

### My Stable (also shown before squad and breeding picks)

```
+----------+
|  STABLE  |
+----------+
Player: Zap, Stage: 2, Stable: (3)
No. Name        Lvl  HP        ATK   DEF   Element
------------------------------------------------------------
1   Ember       2    110/110   28    8     Fire
2   Aqua        2    110/110   22    11    Water
3   Emua        1    110/110   27    11    Fire/Water
```

Element is the last column so a long bred element name cannot push the other columns out of line.

### Squad selection

```
Pick Dragon 1: 1
Pick Dragon 2: 1
That dragon is already selected.
Pick Dragon 2: 2
```

A player with fewer than 3 dragons picks only as many as they have.

### Battle turn

```
--- Stage 1 | Turn 3 ---
You:   Ember [#######---] 70/100 (Fire, Lv2)
Enemy: Rocky [####------] 40/100 (Earth, Lv1)

1. Attack  2. Special  3. Defend  4. Heal (2 left)  5. Switch  6. Stats  7. Forfeit
```

After the player acts: print what happened, check faint/win, then the enemy acts and the same checks run.
A fainted dragon prints ` - Name fainted!` and the next living dragon enters for free.
Invalid input: re-prompt (an exception in the final).

### End of battle

```
 - Stage 1 Cleared !
 - Your Dragons grew stronger !
```

### Breed menu

Show the stable table, pick two different dragons by number, add the child to the stable and print its stat card with `showStats`.

## 7. Mid-sem vs final

Mid-sem covers only up to operator overloading and is **done**. Don't build `final` items early.

| Syllabus concept | Where it lives | Owner | Build |
|---|---|---|---|
| Encapsulation | `Dragon` private data and getters | A | midsem |
| Constructors, destructors | Dragon, Player, Game | A, B, D | midsem |
| Composition | Dragon has `Move[2]`, Player has `Dragon[]` | A, B | midsem |
| Friend function | `showStats`, `Dragon` `<<` and `>>`, `Player` `<<` (the stable table) | A, B | midsem |
| `this` pointer | chained `heal().defend()`, `healAll()`, `unlockNextStage()` | A, B | midsem |
| Dynamic memory | `Player::stable` (`new[]`, `delete[]`, grow, deep copy), `Game::catalog` | B, D | midsem |
| Static members | `Dragon::totalCreated`, `Player::MAX_DRAGONS`, `Game::SQUAD_MAX` | A, B, D | midsem |
| Operator overloading | Dragon: `<<`, `>>`, `-=`, `+`, `==`, `<`, `>`, `++` | A | midsem |
| Inheritance, virtual functions | `Dragon` becomes abstract; `FireDragon`, `WaterDragon`... override `specialAttack()` | A | final |
| Templates | `Team<T>` or `Inventory<T>` | B | final |
| STL | `vector` for teams, `map` for the element-effectiveness chart | C, D | final |
| Streams, manipulators | save/load (`setw` tables for the catalog and stable already exist) | D | final |
| Exceptions | `InvalidMoveException`, `DeadDragonException`, re-throw | C | final |
| Java unit (applets, GUI, threads, networking, DB) | to be confirmed with the faculty | all | final |