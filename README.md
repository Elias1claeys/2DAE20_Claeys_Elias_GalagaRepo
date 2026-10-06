<h1> Galaga – Exam Project </h1>

For my exam project, I recreated Galaga in C++.

When the game starts, it creates two GameObjects in main. The first one is the background. It contains an image of stars that constantly moves downwards, giving the illusion that the player is flying through space. At least, that was the idea!

The second GameObject is used for the actual game. Attached to this GameObject is the State component, which starts with the Start state. I created a standard GameState inside the engine. It contains OnBegin(), Update(), OnExit() and GoToNextStage(), which can all be overridden by the individual states.

When m_pState->GoToNextStage() is called, the current state's OnExit() is called first. The old state is then replaced by the new state, after which the new state's OnEnter() is called.

In the Start state, the player has three options: singleplayer, multiplayer and versus. Unfortunately, because I realized too late that the deadline was Friday instead of Sunday, all three options currently lead to the singleplayer mode. However, the system is set up so that the different options can lead to different states.

After this, the game goes into the Level state. This state is responsible for creating all the GameObjects needed for the game. It also adds an EnemiesController, which manages all of the enemies. The EnemiesController is responsible for spawning the enemies, selecting which enemies will attack next and moving the enemy formation from left to right.

Because the enemies are very similar, I decided to create one Enemy class instead of three separate classes. The Enemy has an EnemyType, which can be used to determine whether it is a Bee, Flie or Boss. Based on this type, the enemy can then enter the appropriate state.

When an enemy first spawns, it enters the flying state. In this state, I give the enemy a path that it has to follow. These paths are usually made using Bezier curves. I calculated the first paths using GeoGebra, the rest is determined by the game.

The enemies follow these Bezier curves using my BezierPath component. With this component, you can define the path that an enemy should follow. It is also possible to add a loop at a specific point in the path.

The texture of the enemy is determined by the angle at which it is flying, so the sprite changes depending on its movement direction.

Once the enemy reaches the end of its path, it enters the FlyingToFormation state. In this state, the enemy flies in a straight line towards its formation position. I decided to do this instead of using another Bezier curve because it looked strange when using a curve while the formation position was constantly moving from left to right.

Once the enemy reaches its formation position, it enters the formation state, where it stays in position.

When all enemies are in formation, the EnemiesController starts moving the formation from left to right and selects enemies that will attack the player.

There are different attack patterns depending on the enemy type. The Boss can either try to catch the player with its laser or perform a bomb attack before diving towards the player. The Bees also perform a bomb raid followed by a dive, but they try to fly underneath the player before attacking from below. The Flies perform a bomb raid as well, but during their dive they curve from one side to the other.

I also created a Collider component. You can add triggers to this component together with an event. When a GameObject collides with one of these triggers, the corresponding collision event is fired. I use this system for things such as shooting and enemy attacks.

Audio is handled using the Observer pattern. I gave the player an AudioObserver because many of the sounds are triggered by the player's input.

Finally, I created a ScoreObserver. Depending on whether an enemy is in formation or currently attacking, the player receives a different amount of points when destroying it.

Thank you for reading!

Github link: https://github.com/Elias1claeys/2DAE20_Claeys_Elias_DiggerRepo
