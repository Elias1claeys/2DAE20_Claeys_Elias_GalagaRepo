Digger – Exam Project

Welcome to Digger, my exam project.

Game Initialization

When the game starts, it creates a GameObject containing a Game component. The Game class manages different game states, including the Start state and the Level state.

When the game transitions to the Level state, it begins initializing all required game objects, services, and systems for the level.

Digging System

For the digging mechanic, I implemented a Dig Service Locator. Since there only needs to be one instance of this service, it can be accessed globally throughout the project.

This service allows game objects and systems to easily check whether a specific tile or area has already been dug out.

Collision System

The project includes a Collider Component that handles collision detection between game objects.

When two game objects collide, the collider triggers the appropriate event, allowing objects to react to collisions in a consistent and reusable way.

Bag State Machine

The bag uses a state-based system to control its behavior:

Standard State – The default state when the bag is resting in place.
Wiggle State – Activated when the bag has been dug out but is still supported from above. The bag begins to wobble, indicating that it is about to fall.
Fall State – The bag starts falling once it is no longer supported.
Gold State – If the bag falls from a sufficient height, it transforms into gold. In this state, the player can collect it for points.

This state machine helps create predictable and maintainable behavior for the bag throughout the game.

Github link: https://github.com/Elias1claeys/2DAE20_Claeys_Elias_DiggerRepo