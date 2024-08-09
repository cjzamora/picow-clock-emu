# Raspberry PI Pico W 6502 microprocessor clock/timer emulator

This is a simple clock/timer emulator for the 6502 microprocessor using the Raspberry PI Pico W. The emulator can be used to test the 6502 microprocessor with a clock frequency of up to `1Khz` (if using the potentiometer ADC pin) and `8Mhz` if setting the clock frequency using the `CLOCK_FREQ` definition in `CMakeLists.txt`. This is useful for testing the 6502 microprocessor without the need for a physical clock/timer chip (e.g. 555 timer/clock oscillator).

## Requirements
- ARM toolchain
- GCC
- CMake
- Raspberry PI Pico SDK

## GPIO Assignments

- PIN 14: Mode PIN (Astable/Monostable)
- PIN 15: Step PIN (Clock can be stepped when in Monostable mode)
- PIN 16: Pulse PIN (Output of the clock/timer, used for LED)
- PIN 28: Clock Output PIN (Output of the clock/timer)
- PIN 26: Potentiometer (For adjusting the frequency of the clock/timer)

## Building and Flashing
```bash
./upload.sh
```

Make sure that the Pico is in BOOTSEL mode before running the script.

## Connecting to 6502
- Connect the Clock Output PIN (PIN 28) of PI Pico to the PHI2 pin of the 6502 microprocessor.

## Frequencies more than 1Khz
If you want to generate clock frequencies more than `1Khz`, you can adjust the `CLOCK_FREQ` in the `CMakeLists.txt` file. Note that the ADC pin for the potentiometer will not work anymore. The clock frequency will be fixed to the value of `CLOCK_FREQ`.

The `CLOCK_FREQ` is defined in `HZ` and can be set to any value up to `8000000` or `8Mhz`.