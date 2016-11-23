Pong
_____

author: haze

Game description:
1. Start out with a random player holding the ball (after Arduino reset / init)
2. Logic loop in code calls events once the one or two player button is pressed. 
3. If either player has the ball and presses it within the allotted time window, the ball is sent off in the other direction, moving between leds at a speed of 50ms/ led
4. If either player fails to send the ball back in the opposite direction, the game is over, and the winners side flashes red until the device is reset.
Const values:
1. Ball travel speed = 50ms
2. Allotted time window for sending ball back = 1000ms or 1 second



