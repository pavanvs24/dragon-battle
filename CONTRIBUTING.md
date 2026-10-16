# Git basics for this project


## Make your own branch (once)

Each member works on their own branch so nobody overwrites anyone else.

```
git checkout -b feature/<your-area>      # A: dragon, B: player, C: battle, D: game
```

## Every work session

```
git checkout feature/<your-area>         # make sure you're on YOUR branch
git pull origin main                     # bring in everyone else's merged work
# ... edit your own files, compile, test ...
git add <your files>
git commit -m "Add Dragon copy constructor"
git push origin feature/<your-area>
```

Commit small and often, with a message that says what you did (not "update" or "fixed stuff").

## Merging into main

1. On GitHub, click **Compare & pull request** for your branch, then **Create pull request**.
2. Ask a teammate to look at it and click **Merge pull request**.
3. Everyone then runs `git checkout main` and `git pull` (or `git pull origin main` from their branch).

Merge only when your code compiles.

## Rules

- Edit only your own files. Need a change in someone else's file? Ask them.
- Don't change a function signature in `include/` without telling the group first.
- Never work directly on `main`.
- Never use `git push --force`.

## If something goes wrong

- **Merge conflict:** don't guess. Message the group and fix it together.
- **Push rejected:** run `git pull origin main`, then push again.
- **Not sure what state you're in:** `git status` and `git branch` show your branch and changes.
