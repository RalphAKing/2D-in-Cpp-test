## This is me testing the SFML liabry in Cpp.


## Prerequisites

- **C++ Compiler**: Ensure that you have a C++ compiler (e.g., GCC, Clang) installed.

---

- main.cpp
---
# SFML Window Example

This is a simple SFML-based C++ program that creates a window and displays a background image.

## Installation

### 1. Compile the Code

Ensure that the SFML library is linked properly. If using `g++`, you can compile with the following command:

```bash
make
```

### 2. Run the Program

Once the program is compiled, run the resulting executable:

```bash
./main
```

### 3. Assets

Make sure you have an image named `test_bg.jpg` in the `assets/` directory of your project to serve as the background. You can replace this with any valid image file.

## Code Explanation

- **SFML Setup**: The code initializes a `sf::RenderWindow` with dimensions 800x600 and a title "SFML Window".
- **Texture Loading**: It loads an image `test_bg.jpg` as a background texture.
- **Event Handling**: It listens for events, specifically the close event, and handles the closing of the window.
- **Rendering**: The program clears the window with a black color, draws the background sprite, and then displays the updated frame.

---

- seedgen.cpp
---
# Random Number Generator Based on Seed

This program generates a random number of a specified length, based on a user-provided seed. The length of the random number is determined by the user, and the seed allows for consistent results when rerun with the same input.

## Features:
- Generates random numbers with a specific number of digits.
- The random number is produced using the `rand()` function, with the seed set by the user for repeatable results.
- The number of digits in the generated random number is defined by the user input.

## Requirements:
- C++ compiler (e.g., g++, clang++)
- Standard C++ library

## Compilation and Execution:
1. Compile the program:
   ```bash
   make
   ```
2. Run the executable:
   ```bash
   ./seedgen
   ```

## Example:

```
Enter a seed value: 123
Enter the length of the random number (number of digits): 5
Random number with 5 digits based on seed 123: 10212
```

## Program Description:
1. **Seed input**: The user is asked to enter a seed value for the random number generation. This ensures the same sequence of numbers will be generated each time the same seed is used.
2. **Length input**: The user specifies the length (in digits) of the random number to be generated.
3. **Random number generation**: The program calculates the minimum and maximum possible values based on the specified length and uses `rand()` to generate a random number within that range.
4. **Output**: The program outputs the generated random number along with the seed value.

## Notes:
- The program uses the `rand()` function, which is generally sufficient for simple use cases but not for cryptographically secure or highly random needs.
- The program will loop indefinitely due to the `return main();` line. To prevent this, replace the recursion with a return statement.

---

- sprite.cpp
--- 
# Basic Sprite Control with SFML

This project demonstrates a basic sprite control system using SFML (Simple and Fast Multimedia Library). The program features a movable sprite, stamina mechanics, FPS tracking, and a grid system. It's an interactive example of 2D game mechanics.

---

## Features
1. **Sprite Movement**:
   - Move the sprite using the `W`, `A`, `S`, `D` keys.
   - Enable sprinting with the `LShift` key, consuming stamina.

2. **Stamina System**:
   - Stamina decreases while sprinting.
   - Gradual stamina regeneration while walking or standing still.
   - Configurable regeneration rates and delay mechanics.

3. **Grid System**:
   - A visible grid dynamically updates based on the view center.
   - Highlights the grid cell where the sprite is located.

4. **FPS Tracking**:
   - Displays the current FPS at the top-left corner.

5. **Responsive Window**:
   - Adjusts the view and grid scaling when the window is resized.

---

## How to Run

### Build Instructions
1. Compile the program using a C++ compiler with SFML. For example:
   ```bash
   make
   ```
2. Run the executable:
   ```bash
   ./sprite
   ```

---

## Controls
- **Movement**: Use `W`, `A`, `S`, `D` to move the sprite.
- **Sprint**: Hold `LShift` while moving.
- **Close Application**: Click the close button on the window.

---

## Customization

### Stamina Settings
Modify the stamina mechanics in the code:
- `float stamina = 100.0f;` - Initial stamina.
- `float staminaDecreaseRate = 10.5f;` - Rate at which stamina decreases while sprinting.
- `float walkRegenRate = 5.5f;` - Stamina regeneration rate while walking.
- `float standRegenRate = 10.5f;` - Stamina regeneration rate while standing still.
- `float staminaRegenDelay = 2.0f;` - Delay before stamina regeneration begins.

### Movement Speed
Adjust movement speed:
- `float speed = 200.0f;` - Walking speed.
- `float runSpeed = 300.0f;` - Sprinting speed.

---

## License

This project is open-source and available for modification and use under the MIT license.

### MIT License

```
MIT License

Copyright (c) 2024-2025 Ralph King

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
