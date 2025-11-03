# termatrix

A minimal Matrix‐style rain animation for the terminal, written in pure C.  
No ncurses, no external dependencies, just ANSI escape codes.

https://github.com/eigenode/termatrix

---

## ✨ Features

- Green falling code rain effect (Matrix‐like)
- Dynamically adapts to terminal size at startup
- Efficient single-buffer rendering (no flicker)
- Each column has randomized:
  - Trail length
  - Fall speed
  - Characters
- Head in bright white, trailing characters in shades of green
- Runs on any POSIX terminal (Linux, macOS, WSL)
- Lightweight — ~100 lines of C
- Graceful exit on `Ctrl+C` with terminal state restored

---

## 🎬 Demo

![Termatrix in action](demo.gif)
---

## 🛠 Build

Make sure you have GCC or Clang installed.

```bash
git clone https://github.com/<yourname>/termatrix.git
cd termatrix
make
```

Run the program:

```bash
make run
```

Clean build artifacts:

```bash
make clean
```

Or compile manually:

```bash
gcc -Wall -Wextra -o tmatrix main.c termatrix.c
./tmatrix
```

---

## ⚙ Implementation

- Uses a `Termatrix` struct to track terminal grid and column states
- `termatrix_update()` moves column heads and updates characters
- `termatrix_render()` draws the frame using ANSI escape codes
- Pre-allocated frame buffer ensures smooth rendering
- Minimal POSIX-only approach: uses `ioctl` for terminal size and `nanosleep` for timing
- No external libraries required

---

## 🚀 Planned Improvements

- **Terminal resizing support:** Currently reads terminal size only at startup
- **Customizable settings:** Allow command-line options for speed, trail length, and colors
- **Performance enhancements:** Optimize buffer handling for large terminals
- **More varied randomization:** Enhance the rain effect with diverse patterns

---
