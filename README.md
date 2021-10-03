## Vaxman

A modification to the original Pacman game as part of the EA Software Engineering Virtual Experience

Original Pacman from: **Patriciateroltolsa**

Altered game mechanics are as follows:

► Pac-Man is now Vax-Man, as in vaccination man, and can consume the enemy ghosts which are analogous to viruses

► An enemy ghost that hasn't been consumed for 30 seconds will duplicate itself. If there becomes a total of 128 ghosts or greater, you will lose the game. This logic was to be held for every ghost currently in game, and keeping a track of their time "alive" could be done in several ways, with one of them being multithreading

► As for the ability to handle more than 4 ghosts at a time without performance issue. this was done via pre-allocating memory for 128 ghosts, and incrementing the drawing pointer every time the time of 30 seconds was reached for every ghost. Allocating at runtime was extremely draining to performance

► The way to win the game was the same as the original, which is to consume all pellets
