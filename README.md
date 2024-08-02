# Raspberry PI Pico W 6502 microprocessor clock/timer emulator

This is a simple clock/timer emulator for the 6502 microprocessor using the Raspberry PI Pico W. The emulator can be used to test the 6502 microprocessor with a clock frequency of up to 1Khz. This is useful for testing the 6502 microprocessor without the need for a physical clock/timer chip (e.g. 555 timer).

## Requirements
- ARM toolchain
- GCC
- CMake
- Raspberry PI Pico SDK

## GPIO Assignments

- PIN 14: Mode PIN (Astable/Monostable)
- PIN 15: Step PIN (Clock can be stepped when in Monostable mode)
- PIN 16: Output PIN (Output of the clock/timer)
- PIN 26: Potentiometer (For adjusting the frequency of the clock/timer)

## Building and Flashing
```bash
./upload.sh
```

Make sure that the Pico is in BOOTSEL mode before running the script.

## Connecting to 6502
- Connect the Output PIN (PIN 16) of PI Pico to the PHI2 pin of the 6502 microprocessor.