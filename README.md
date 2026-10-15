# Quoridor

A browser-based Quoridor game with an AI opponent, built as a first-year multidisciplinary project (CSE + EE + Civil).

## Features
- 9x9 board, 10 walls per player, pawn jumps
- Modes: AI (hard), AI (easy), 2 players
- Wall validation: a wall is rejected if it fully blocks either player's path
- Live panel showing shortest path length and number of shortest paths
- Catalan number baseline (C(16,8) = 12,870 and C8 = 1,430)
- "Show shortest paths" toggle that highlights every cell on a shortest route

## Algorithms
- BFS for shortest distance and wall validation
- Dynamic programming to count shortest paths
- One-move greedy AI scored on distance difference plus a path-count bonus

## Run
https://maximus733.github.io/Catlan-s-Quoridor/

## Host on GitHub Pages
Repo Settings > Pages > Deploy from branch `main` / root.

## Roadmap
- Minimax with alpha-beta pruning
- Hardware version: Hall-effect sensors, ESP32 and LED indicators
