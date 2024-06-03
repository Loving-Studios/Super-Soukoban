# Super-Soukoban by Loving Studios

## Link github.com page

https://loving-studios.github.io/Super-Soukoban/

## Link github.com Wiki

https://github.com/Loving-Studios/Super-Soukoban/wiki

## List of team members and GitHub accounts

Pablo Sanjosé

https://github.com/XXPabloS

Víctor González

https://github.com/TheWolfG145

## Short description of the game

Super Soukoban is a captivating puzzle game where players take on the role of a warehouse worker. Their mission? To skillfully maneuver crates through intricate mazes, ensuring they reach their designated storage spots. The challenge lies in avoiding accidental crate entrapment, as once a box is pushed into an unreachable position, it becomes irretrievable.

Developed by Thinking Rabbit, this game follows the blueprint set by the original Sokoban, which debuted on home computers in 1982. In this SNES adaptation, players face an additional twist: each stage imposes a fixed move limit. Thus, not only must they arrange the boxes correctly, but they must do so with maximum efficiency.

While Super Soukoban remains a hidden gem, it unfortunately never ventured beyond the borders of Japan.

## How to play the game, detailing the controls


- Arrow keys: Move player
- Enter: Navigate menus
- Escape: Exit game
- F1: God Mode (No limit steps, can't lose)
- F2: Enable debug mode (shows collision)
- F3: Direct win
- F4: Direct lose
- F5: Move Boxes to red dots

- Win condition triggered upon collision with all boxes and the red ball.
- Lose condition triggered upon reaching the level's step limit.


## List of features implemented

-All the previous points of the previous prototype.
-All music and audio effects have been added as in the original game.
-Levels generated in order, using the original game as reference.
-Fully functional user interface: score, lives, steps.
-Added debug functionalities like God Mode, Show Collisions, Direct -Win, Direct Lose, Move all boxes to red circles.

- Win condition is activated when colliding with all boxes and the red ball.
- Lose when the level step limit is reached.

Levels required for each game:
-Animated intro (short version).
-Full 8 levels.

Premium features:
-Screen to choose between levels and one level.

Additional detailed comments:

- Intuitive Controls: Use the arrow keys to move your character seamlessly through the map.
- Move from Menu to Menu: Press the Enter key to navigate through menus and interact with in-game options.
- Quick Exit: Press the Escape key at any time to exit the game.
- Debug Mode:
	-Enable debug mode by pressing the 'F1' key to obtain god mode,   .
	-Enable debug mode by pressing the 'F2' key to reveal collision information, helping you navigate through complex environments.
	-Enable debug mode by pressing the 'F3' key to win instantly.
	-Enable debug mode by pressing the 'F4' key to lose instantly.
	-Enable debug mode by pressing the 'F5' key to move all the boxes to the red dots.
- Custom team-designed SplashScreen displayed at the start of the game.
- Background music featured in all screens dynamically change according to the current screen.
- Original windows and menus.


-A dynamic mapping system has been implemented in which we pass the information of each level, box positions, wall positions and red dot positions.
-The player's position has been detailed and taken into account in each level.
-System of collisions with the walls.
System of collisions with the boxes.
-It has been avoided that the boxes collide with each other.
-System to detect when a box collides with a red dot.
-Polished character animations.
-Changed animations from box pushing to normal moving implemented.
-MemoryLeak system implemented to download data and avoid memory leaks.
-Audio system to change the song according to the level where you are.
-Frame counter to make correctly the animated intro in short version.


## Additional Comments for the teacher

VERY IMPORTANT!:
-The main problem with our game is that moving the boxes on our map does not prevent us from erasing the information under the box when we start the level. That is to say, when you play the game, level one appears correctly, but when you move the first box you will see that there is a hole in the map and it shows the orange background. This bug does not prevent you to pass level one but as you go through the levels it becomes very complicated because where there was a starting box before the orange background appears. So it ends up booming the game experience. The game loop works correctly, the collisions work correctly, the game is complete in terms of code and the 8 levels as well as the animation are created, but this bug prevents us from completing the game perfectly. So we want to ask for consideration when evaluating the project because there has been a lot of effort on our part, and although we are not happy with the final result we know that we have worked hard to get it done.

Thanks for your consideration, Victor and Pablo

Additional Comments:

-We have tried to implement full screen, but the original game is not intended to be played at a resolution larger than 480 x 320 which is the original resolution of the SNES. 
This has caused us many problems and inconveniences and at the last minute we had to back out because it made the game unplayable and very ugly visually so we preferred to make it work properly before it did not look right.
-We have tried to use the original source but we have been very short of time due to problems that have arisen during the development of the project and we wanted to prioritize.
-We have tried to implement a system so that the assetd of the box changes when it is in the indicated position, but when we put the first box, all the boxes change because we have not been able to do it separately.

## Gameplay Video

https://youtu.be/Fxztxi4CtqY










