# Teensy 4.1 Blink Project

This project is a minimal PlatformIO-based Arduino sketch for a Teensy 4.1 board that blinks the built-in LED.

## Hardware

- Teensy 4.1
- USB cable
- Power source as needed for the board

## Software

- PlatformIO
- Visual Studio Code (recommended)

## Build and upload

1. Open the project in VS Code.
2. Install the PlatformIO extension if needed.
3. Build the project:

   ```bash
   pio run
   ```

4. Upload to the board:

   ```bash
   pio run --target upload
   ```

## Project structure

- `src/` — Arduino source files
- `include/` — project headers
- `lib/` — custom libraries
- `test/` — test files
- `platformio.ini` — PlatformIO board and framework configuration

## License

This project is provided as a simple example and is ready to be adapted for your own use.
