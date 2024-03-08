A project in the introductory course to object-oriented programming and software engineering - "Super-Pacman"
Served by: Daniel Hassin 316558766, Eyal Makdoshi 208879718

General explanation of the game:
In the program the game "Super-Pacman" is realized
On the main screen, the "menu" will open in which the following 3 options will be displayed:
Play - The game will start from the first stage.
You can start the game by pressing the button with the mouse (left button) or by pressing Enter on the keyboard.
How to play - a help window will be displayed to the user that includes a general explanation of the game - how to control the character, what is its purpose.
The window will be displayed by clicking on the button with the mouse (left button).
Exit - the program ends and the game closes.
The game can be closed by pressing the button with the mouse (left button) or by pressing Esc on the keyboard.

The course of the game: the game will have 3 stages where the goal of each stage is to eat all the cookies using Pacman without being 'caught' by the elves, within the time and life allocated to the player (there are stages with a timer). Also the goal of the player is to score the highest total of points.
Eating all of the cookies in a step beyond the next step.
A collision with an elf lowers the player's life count by 1 and returns the Pacman and the elves to their starting position.
The time allocated to the stage ends before all the cookies are eaten, the player's life count is reduced by 1, the Pacman and the gnomes return to their starting place, and also everything that the Pacman ate will return (cookies, opened doors, keys and gifts)
End of the game Success: victory in all stages of the game. Failure: The player's life total is over.

General explanation of the construction of the program:
In the first step, the program will run the "menu" screen. When the user clicks on the "Play" button, the program will read from the input file the size of the game board, the route of the board and the position of the players on the game board.
After that, the program will run in a loop until the end of reading from the input file, that is, until we have successfully completed all the steps or disqualification. In any case, the game window will close and the menu window will be displayed again.
In each action, the program will move the dynamic objects (the Pacman moves according to the user's response, the sprites move both randomly and chase the Pacman randomly), check if there was a collision and handle it if so and also if the stage ends (successfully or unsuccessfully).
Running each step will end when the program detects that there are no more cookies/life/time. If time runs out and a player has life left, the program will rerun the current stage.
Project High School:
Button - inherits all types of buttons - Play, How to play, Exit.
BaseObject – inherits all objects in the game, both static and dynamic.
DynamicObject: Inherited to Pacman, Demon
StaticObject: bequeathed to Gift, Cookie, Wall, Key, Door
Gift: bequeathed to SuperGift, FreezeGift, LifeGift, TimeGift
In addition to realized State - PacmanState: inherited from SuperPacman, NormalPacman

List of the files we created:
Menu - a department that controls the management of the main menu in the game. Contains a background image as well as a Button vector, when clicking the "Start" button the game will start.
Button - an abstract class that creates a button that will be shown to us in the game menu. Holds 2 images, one normal and one highlighted that is intended to highlight the button if the mouse moves over it.
Play - a class which inherits from the Button class which implements a virtual function of its parent class Button, a response to pressing the Play button, which starts the game.
Help - a class which inherits from the Button class which implements a virtual function of its parent class Button, a response to clicking the Help button, which displays a help screen to the user.
Exit - a class that inherits from the Button class that implements a virtual function of its parent class Button, a response to pressing the Exit button, which ends the program.
Controller - responsible for managing the program and running its main loop. Holds an object of type LevelController.
Clock - a class that creates a clock object of type sf::Clock.
  LevelController - the class responsible for managing a level in the game. It contains a Pacman object, a vector of Demon objects. In addition, it will contain variables that update the number of the stage, as well as timers that indicate the movement of the dynamic objects, the freezing of the sprites, and the stage timer.
Board - the whip that is responsible for managing the matrix of the stage. It contains an array of pointers to staticObject objects and its entire functionality.
Resources: The Singleton class which contains all the resources we use in the program, meaning Texture objects for each of the characters (static and dynamic), as well as fonts and sounds that the program has.
BaseObject – abstract class. The base class for all existing objects in stages.
DynamicObject – an abstract class that inherits from the base class BaseObject and is the base class for all mobile objects in the game.
StaticObject - an abstract class that inherits from the base class BaseObject and is the base class for all static objects in the game.
Pacman: A class that inherits from DynamicObject and initializes the game's Pacman for us. It holds the data about the player and updates them accordingly, is responsible for his movement and in addition manages collisions with the various objects using "double dispatch". For each static/dynamic object, a collision is managed accordingly (for example - a collision with a gift - raising the player's score, performing the action according to the type of gift and deleting it from the board).
Demon: a class that inherits from DynamicObject, initializes a random colored demon, is responsible for its movement and also manages conflicts with the various objects using "double dispatch".
Cookie: A class that inherits from the StaticObject class creates a cookie and also increases the cookie counter by one every time it is initialized.
This class has a counter of the number of cookies at each stage at any given time, this is a static int type variable common to all objects of this class - when a cookie is created, the counter increases and when it is eaten, it decreases.
Door: A class that inherits from the StaticObject class creates a static object of type door.
Wall: A class that inherits from the StaticObject class creates a static object of type wall.
Key: A class that inherits from the StaticObject class creates an object of type key.
Gift: an abstract class that inherits from the StaticObject class. Gift types that inherit from her will have to realize a virtual function, each based on its different and specific behavior.
TimeGift: A class that inherits from the Gift class creates a static gift-type object that increments time and realizes the virtual function of its specific operation by incrementing the game timer by 20.
LifeGift: A class that inherits from the Gift class creates a static gift-type object that increases life to the user and realizes the virtual function of its specific action by increasing the user's life by 1.
FreezeGift: A class that inherits from the Gift class creates a static object of the type freezing elves gift and realizes the virtual function of its specific operation by freezing the elves for about 10 seconds.
SuperGift: A class that inherits from the Gift class creates a static gift-type object that turns Pacman into a Super-Pacman and implements the virtual function of its specific action by calling a function of the Pacman class that implements this through State. Pacman will go into Super Pacman mode for about 10 seconds.
PacmanState: a class that represents the state design template in our program. By doing this we allow the Pacman object to change its behavior to Super Pacman at runtime. An abstract class with virtual functions of colliding with an elf and with a door (Pacman in its normal form and Super Pacman behave differently in these cases).
NormalPacman: a class that inherits from the PacmanState class and implements Pacman's behavior in its normal form with an elf (the player's life counter decreases by 1) and with a door (Pacman will pass through it only if he collected a key in the stage).
SuperState: A class that inherits from the PacmanState class and 'realizes' the behavior of the Super Pacman in a collision with an elf (nothing will happen to the player) and with a door (the Pacman will go through it, even if he did not collect a key, and in any case his key counter will not change).
data structures:

A two-dimensional vector of pointers of type unique of StaticObject. An array containing the static objects of the step.
A vector of pointers of type unique of DynamicObject. Contains all the elves in the stage.
A vector of pointers of the unique Button type that stores the menu buttons.
A vector of type string in which we will save the current stage that is being played to repeat it when necessary.
An array of type Texture in which we will store all the textures displayed during the game.
An array of type sf::SoundBuffer and an array of type sf::Sound in which we will store all the sounds played during the game.
Two arrays containing strings of the file names of the images and sounds that are loaded from the disk.

Noteworthy algorithms:

• Conflict management using double dispatch
• Moving the elves:
1) A period of time is drawn during which each elf is in one of two states - chasing the Pacman or moving randomly
2) The situation in which the elf moves is drawn (as explained above)
3) When the movement is random - the direction in which the elf will move is drawn, when the elf is in chase mode - the direction in which it will move is drawn.
• Loading the stage from the file.

Known bugs:
Sometimes, for reasons that are not clear to science, there are situations when the player moves from stage to stage or starts the same stage again (whether the time runs out or whether he is hit by an elf) in which there is no waiting for the first click from the player and the stage starts immediately.

Remarks:
• The gifts are all represented by different textures that represent them clearly to create better gameplay.
• All gifts are represented in the file by the character $, but while reading the stage from the file, the type of gift is randomly drawn.
• When the sprites are frozen and not moving, their color changes to a sort of light blue to emphasize this to the user.
• In every collision with an elf/eating all the cookies/the end of the time allocated to the stage - there is a delay of one second in order to prevent a sharp and fast transition between a stage and a stage/stage itself (due to some disqualification) so that the player has time to understand and react.
• Added the action of the space button on the keyboard which increases the speed of Pacman's movement when it is pressed (consecutively) for large stages where Pacman's movement is quite slow.
• The sprites will not move until the player starts playing and the stage's timer will not start counting down either, even after the player is disqualified.
• When the phase timer ends and it is reloaded, the sprites are reset to their starting position as required but their color can change randomly, as above the gifts - because their type is drawn.
  
Input file format:
The input file is of type txt and is called Board.txt
Adding a stage: If the user wants to add a new stage in the game, the user must open the file "Board.txt" and add a line break (\n), in a new line the size of the game board (ie number of rows and columns), in a new line the number of seconds allotted for the stage This is (if he wants to insert a timer into the phase) so for example: T 40, where 40 is the number of seconds (for an unlimited phase this line should not be inserted). Then go down one line and draw the route of the new stage.

