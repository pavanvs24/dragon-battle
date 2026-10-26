# Design: Dragon Battle

Single source of truth for rules, screens and class responsibilities. If the code and this
file disagree, fix one of them in a PR instead of letting them drift.

## 1. The game in one paragraph

One player profile per device. You pick two starter dragons from a read-only catalog, fight
three hard-coded enemy stages, level your dragons up after each win, and breed new dragons
from your stable. Everything runs in the terminal. Progress lives in memory only for the
mid-sem build; `save.dat` arrives in the final.

## 2. Fixed rules (everyone codes to these)

| Rule | Value |
|---|---|
| Stable size | max 6 dragons (array starts at capacity 2 and grows with `new[]`/`delete[]`) |
| Level-1 stats | HP 100, attack 10 to 30, defense 5 to 15 |
| Damage | `max(1, attacker.attack + move.power - target.defense)` |
| Basic move | power +0, no cooldown |
| Special move | power +15, 3-turn cooldown |
| Defend | halves the next hit taken (min 1); ends when that hit lands or the owner's next turn starts |
| Heal | +30 HP (never above max), 3 uses per battle |
| Switch | costs the turn; cannot switch to a fainted dragon |
| Faint | dragon at 0 HP; forced switch is free |
| Level up | level +1, max HP +10, attack +2, defense +1, HP refilled |
| Comparing dragons | `power = attack*2 + defense + maxHp/10`; `==` and `<` compare power |
| Breeding | needs two different dragons, stable not full, parents are kept |
| Child stats | average of parents + 2 each; HP is the average; level 1 |
| Child element | parent 1's element if equal, else `"Fire/Water"` style |
| Child name | first half of parent 1's name + second half of parent 2's |
| After every battle | all dragons fully healed |
| Win a stage | all dragons level up, next stage unlocks |
| Lose a stage | back to menu, no penalty |

## 3. Starter catalog (8 dragons, proposed; Member A may tune within the ranges above)

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
| 3 (boss) | 3 catalog dragons | 3 |

Enemy AI each turn: roll 1 to 100. 1-70 attack, 71-90 defend, 91-100 heal if its dragon is
below half HP (otherwise attack). The enemy also has 3 heals per battle.

## 5. Classes

| Class | Owner | Responsibility |
|---|---|---|
| `Move` | A | name, power, cooldown; used by Dragon (composition) |
| `Dragon` | A | stats, `Move moves[2]`, all operators, friend functions, static counter |
| `Player` | B | name, dynamic `Dragon* stable`, stage progress, breeding; also used for enemy trainers |
| `Battle` | C | takes `Player&` (you) and `Player&` (enemy), runs the turn loop and enemy AI |
| `Game` | D | owns the catalog and your profile, runs menus, builds enemy teams |
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

### Battle turn

```
--- Stage 1 | Turn 3 ---
You:   Ember [#######---] 70/100 (Fire, Lv2)
Enemy: Rocky [####------] 40/100 (Earth, Lv1)

1. Attack  2. Special  3. Defend  4. Heal (2 left)  5. Switch  6. Stats  7. Forfeit
```

After the player acts: print what happened, check faint/win, then the enemy acts and the same checks run.
Invalid input: re-prompt (an exception in the final).

### End of battle

```
 - Stage 1 Cleared !
 - Your Dragons grew stronger !
```

### Breed menu

Show the stable, pick two different dragons by number, print the child with `<<`, add it to the stable.

## 7. Mid-sem vs final

Mid-sem covers only up to operator overloading. Don't build `final` items early.

| Syllabus concept | Where it lives | Owner | Build |
|---|---|---|---|
| Encapsulation | `Dragon` private data and getters | A | midsem |
| Constructors, destructors | Dragon, Player, Game | A, B, D | midsem |
| Composition | Dragon has `Move[2]`, Player has `Dragon[]` | A, B | midsem |
| Friend function | `showStats`, `operator<<`, `operator>>` | A | midsem |
| `this` pointer | chained `heal().defend()`, `healAll()`, `unlockNextStage()` | A, B | midsem |
| Dynamic memory | `Player::stable` (`new[]`, `delete[]`, grow), `Game::catalog` | B, D | midsem |
| Operator overloading | Dragon: `<<`, `>>`, `-=`, `+`, `==`, `<`, `>`, `++` | A | midsem |
| Inheritance, virtual functions | `Dragon` becomes abstract; `FireDragon`, `WaterDragon`... override `specialAttack()` | A | final |
| Templates | `Team<T>` or `Inventory<T>` | B | final |
| STL | `vector` for teams, `map` for the element-effectiveness chart | C, D | final |
| Streams, manipulators | `setw`/`setfill` stat tables, save/load | D | final |
| Exceptions | `InvalidMoveException`, `DeadDragonException`, re-throw | C | final |
| Java unit (applets, GUI, threads, networking, DB) | see open questions | all | final |
