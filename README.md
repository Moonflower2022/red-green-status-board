# Red-Green Status Board

A 5x3 bi-color LED grid controlled by Arduino, using multiplexing to control 15 LEDs with minimal pins.

BOM: [`bom.csv`](bom.csv)

## Hardware Design

### Components
- 15 bi-color (red/green) LEDs arranged in a 5x3 grid
- Arduino board
- Perfboard for mounting
- Resistors for current limiting

### Wiring
The grid uses multiplexing to control all 15 LEDs with 13 Arduino pins:

- **Column pins (3)**: A0, A1, A2 (ground when active)
- **Red row pins (5)**: Digital pins 7, 6, 5, 4, 3
- **Green row pins (5)**: Digital pins 12, 11, 10, 9, 8

Each LED has both red and green elements wired separately, allowing individual color control. The grid is scanned column by column rapidly enough (400-1000μs per column) that persistence of vision creates the illusion of all LEDs being on simultaneously.

### Schematic

```
        COL0   COL1   COL2
         A0     A1     A2
          |      |      |
          v      v      v
ROW0 12G--[LED]--[LED]--[LED]
      3R--[LED]--[LED]--[LED]

ROW1 11G--[LED]--[LED]--[LED]
      4R--[LED]--[LED]--[LED]

ROW2 10G--[LED]--[LED]--[LED]
      5R--[LED]--[LED]--[LED]

ROW3  9G--[LED]--[LED]--[LED]
      6R--[LED]--[LED]--[LED]

ROW4  8G--[LED]--[LED]--[LED]
      7R--[LED]--[LED]--[LED]

Each LED is bi-color (common cathode):
- Red anode connects to row pins 3-7
- Green anode connects to row pins 8-12
- Common cathode connects to column pins A0-A2

To light an LED:
1. Set row pin HIGH (red or green)
2. Set column pin LOW
3. Current flows: Pin → LED → Column → GND
```

### Why Multiplexing?
Direct control of 15 bi-color LEDs would require 30 pins (red + green for each). Multiplexing reduces this to 13 pins by scanning the grid rapidly. The code displays each column for a few hundred microseconds, cycling through all columns fast enough that the human eye perceives continuous illumination.

> Note: This project uses standard multiplexing. [Charlieplexing](https://en.wikipedia.org/wiki/Charlieplexing) could reduce pin count further.

## Project Structure

Each directory contains a complete Arduino sketch with a different pattern or function:

### focus_light/
A simple red/green status indicator controlled by a button.
- Button on pin 13 toggles between red and green states
- Displays solid red or solid green across entire grid
- Useful as a focus indicator or status light

### rain/
Random falling drops animation.
- Drops spawn randomly in each column
- Each drop is randomly colored red or green
- Simulates rain falling down the grid

### snake/
A snake moving around the grid perimeter.
- Red head with green body segments
- Follows a predefined path around the outer edge
- Tail length: 4 segments

### SOCRATICA/
Text display showing "SOCRATICA" letter by letter.
- Each letter defined as a 5x3 pixel pattern
- Alternating red and green letters
- Cycles through all 9 letters continuously

### test/
Test sketch (currently identical to snake)

## How It Works

All sketches share the same basic multiplexing pattern:

1. **Setup**: Configure pins 3-12, A0-A2 as outputs
2. **Display loop**: For each frame (40-50 iterations):
   - Activate one column at a time
   - Set the appropriate red/green row pins HIGH for that column
   - Hold for 300-400 microseconds
   - Turn off all pins and move to next column
3. **Pattern update**: After each frame, update the animation state

The rapid scanning creates smooth animations and mixed colors (orange = red + green on).

## Building Your Own

1. Solder 15 bi-color LEDs to a perfboard in a 5x3 grid
2. Wire columns together (one wire per column)
3. Wire red elements in rows (5 row wires)
4. Wire green elements in rows (5 row wires)
5. Connect to Arduino as specified above
6. Upload any of the sketches
7. Watch the patterns!

## Lessons Learned

- First time using perfboard and multiplexing
- C++ was challenging initially but got easier
- Used the "wrong" side of the perfboard initially
- Some LEDs were soldered backwards and had to be fixed
- Charlieplexing would have been even more efficient

## Future Ideas

- Combine multiple patterns with button switching
- Add brightness control
- Implement more complex animations
- Try charlieplexing for reduced pin usage
