# MinigamesInRaylib #
A collection of minigames made in the raylib library with c++.

## Games ##

### Race ###

Race is a game played with two players. The two players race against eachother to get to the red finish line at the end.

### Test ###

Test is not a game, it justs tests the bouncing mechanic used in Sumo and the circle blockers.

### Sumo ###

Sumo is a game where one player trys to knock the other player out of the circle. The circle decreases over time, and at the end of each round the winner's score gets incremented, and the game is reset. When a game resets, the players are not allowed to move for a couple of seconds as to minimize players accidentally moving out of the circle on their own. The top left corner shows when player can move; `Ready` meaning the players cannot move, `Go!` meaning the players can move. The score of both the players is located in the top right of the screen, with colors corresponding to the colors of the players.

### Connect 4 ###

Connect 4 is pretty self explanatory, it is a connect four clone. The players have alternating turns trying to get four of their pieces in a horizontal, vertical, or diagonal line. Whenever a player wins, a message will appear in the top right corner, and players will no longer be able to place their pieces. A preimage of where the piece will go appears when the mouse is in a column of the connect 4 board. A piece will drop where the preimage indicates when the player hits the left mouse button.
