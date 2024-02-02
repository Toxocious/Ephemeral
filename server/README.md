# Ephemeral - Server
This repository contains the source code for the Ephemeral server, which the game client and editor depend on.

We intend to have three individual servers which the game will connect to during runtime:

1. Login server
2. Game Server
3. Battle Server

## Login Server
Will handle the initial login connection for all users.

## Game Server
Handles all game actions, from movement, inventory management, character management, player-to-player trading etc. excluding any battle-related functionality.

## Battle Server
Handles all battle-related functionality.

We intend on using [Smogon's Pokemon Showdown](https://github.com/smogon/pokemon-showdown) battle simulator through the use of - most likely - sockets, as it is the most complete battle simulator available and is extensible provided we need to implement our own features.
