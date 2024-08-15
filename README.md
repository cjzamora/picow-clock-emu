# Raspberry PI Pico(W) - 6502 microprocessor clock/timer emulator

An interactive clock/timer emulator for the 6502 microprocessor using repeating timer and pulse width modulation. This emulator can generate clock signals from `1Hz` to `125MHz`.

## Requirements
- ARM toolchain
- GCC
- CMake
- Raspberry PI Pico SDK

## GPIO Assignments

- GPIO 16 - Pulse PIN for LEDs
- GPIO 17 - Clock PIN for 6502

## Building and Flashing
```bash
./upload.sh
```

Make sure that the Pico is in BOOTSEL mode before running the script.

## Connecting to the interactive terminal
Connecting to the terminal using `minicom`:

```bash
minicom -b 115200  -D <serial_port>
```

Once connected, you should see the following prompt:

```
Pico Clock/Timer Emulator

Sys Clock:              125000000Hz
Out Clock:              1Hz
Timer:                  RPT
Duty Cycle:             50%

Type '?' for help

>>>
```

Feel free to explore the commands by typing `?` and pressing enter. There are two types of clock generation modes:
- `RPT` - Repeating Timer Mode used to generate clock frequencies from `1Hz` to `9Hz`
- `PWM` - Pulse Width Modulation Mode used to generate clock frequencies from `10Hz` to `125MHz`

## Connecting to 6502
- Connect the CLock PIN to the PHI2 pin of the 6502.