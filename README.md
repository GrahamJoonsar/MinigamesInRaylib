# MinigamesInRaylib #
A collection of minigames made in the raylib library with c++.

## Games ##

### Race ###

Race is a game played with two players. The two players race against eachother to get to the red finish line at the end.

### Test ###

Test is not a game, it justs tests the bouncing mechanic used in [Sumo](#Sumo) and the circle `Blockers`.

### Sumo ###

Sumo is a game where one player trys to knock the other player out of the circle. The circle decreases over time, and at the end of each round the winner's score gets incremented, and the game is reset. When a game resets, the players are not allowed to move for a couple of seconds as to minimize players accidentally moving out of the circle on their own. The top left corner shows when player can move; `Ready` meaning the players cannot move, `Go!` meaning the players can move. The score of both the players is located in the top right of the screen, with colors corresponding to the colors of the players.

### Connect 4 ###

Connect 4 is pretty self explanatory, it is a connect four clone. The players have alternating turns trying to get four of their pieces in a horizontal, vertical, or diagonal line. Whenever a player wins, a message will appear in the top right corner, and players will no longer be able to place their pieces. A preimage of where the piece will go appears when the mouse is in a column of the connect 4 board. A piece will drop where the preimage indicates when the player hits the left mouse button.

## Documentation ##

### Boundaries.cpp ###

`Boundaries.cpp` defines the `Blocker` class, a rudimentary collider (I probably should change the name of the file). It defines the various methods that a `Blocker` uses to draw to the screen and interact with the player.

#### Dist ####
Dist is a function that returns the distance between two cartesian coordinates. It is used for detecting collision when the `Blocker` is a circle.

#### Blocker::draw ####

This is a function that draws the `Blocker` to the screen. If the `Blocker` is a circle, it draws a circle to the screen using the `Blocker`'s x, y radius, and color. If the `Blocker` is a rectangle, it draws a rectangle to the screen using the `Blocker`'s x, y, width, height, and color.

#### insideOfRect ####

insideOfRect is a complicated function that returns a boolean value based on whether the player will move into the bounds of the `Blocker` based on the player velocities. It does not actually check if the player will move inside of the visible part of the `Blocker`, but a larger rectangle that accounts for the fact that the players position is the center of the visible player circle. This allows the player to realistically collide with rectangle `Blockers`.

#### moveOutsideOfBlocker ####

This is a function that moves the player outside of a `Blocker` if the player is inside of it. Players usually only get stuck inside of Rectangle `Blockers`, and only if the player manages to hit the exact corner of the `Blocker`. This function is not very good, and I will change it later. It only really works on relatively square shaped `Blockers`. To move it to a non-surprising location outside of the `Blocker`, it gets the angle from the center of the `Blocker` to the player, and uses the polar coordinate system converting to cartesian to put the player outside of the `Blocker`.

#### Blocker::collisionWithPlayer ####

This is a function that handles most of the collision logic with the player. It sets the players velocities to zero if the player will move inside the `Blocker` on the next frame. The collision is relatively easy for circle `Blockers`, but the Rectangle `Blockers` have the use the [insideOfRect](#insideOfRect) helper function. The Rectangle `Blockers` also only set the velocity that makes the player enter the `Blocker` to zero, not both velocities. This allows the player to slide along the sides of Rectangle `Blockers` without getting stuck.


### Boundaries.h ###

Just a header file that declares the `Blocker` class, its constructor,  and its methods.
