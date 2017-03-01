This is an implementation of Snake using drawLine as the graphics engine.

Uses [pthread-win32](https://github.com/GerHobbelt/pthread-win32) to seperate input and drawing to the screen.
The snake and food are stored as lines drawn between points which are stored and dynamically managed in a linked list

Recent Fixes:
- Switched display thread to print from a buffer instead of printing each character one at a time,  removes a large portion of the flicker from the previous version.

Issues:
- There are still some performance issues that cause frame drops.
- Snake is sometimes spawned in a bad spot.
  - The snake always spawns moving to the right for simplicity, this will be fixed later
  
- Travelling vertically is faster than travelling sidways
  - This is due to the fact that the charactes aren't square, switching the command line to use a square font should fix this. 
