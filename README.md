This is an implementation of Snake using drawLine as the graphics engine.

Uses [pthread-win32](https://github.com/GerHobbelt/pthread-win32) to seperate input and drawing to the screen.
The snake and food are stored as lines drawn between points which are stored and dynamically managed in a linked list

Issues:
 - Drawing frames involves first clearing the terminal, then printing a completely new frame
  - There is a noticeable flashing between frames
  - This means that higher "resolutions" become unplayable at higher framerates as the screen will be cleared before a whole frame can be drawn.
  - Beyond using a library designed for building command line GUIs like ncurses (which would defeat the purpose of making this with drawLine), I don't know how to improve this unless there's some low level Windows function that works like ncurses.
- Snake is sometimes spawned in a bad spot.
  - The snake always spawns moving to the right for simplicity, this will be fixed later
- Travelling vertically is faster than travelling sidways
  - This is due to the fact that the charactes aren't square, switching the command line to use a square font should fix this. 
