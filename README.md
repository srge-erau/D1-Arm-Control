# Unitree D1 Arm Control Examples

C++ examples for sending commands to and reading feedback from a Unitree D1 arm through the DDS-based [`unitree_sdk2`](https://github.com/unitreerobotics/unitree_sdk2) API.

> [!CAUTION]
> These programs can command physical robot joints. Keep the workspace clear, use conservative targets, provide an emergency-stop procedure, and test with motors disabled whenever possible. Review each hard-coded command before execution.

## Examples

| Executable | Purpose |
| --- | --- |
| `joint_enable_control` | Send an arm enable/disable mode command |
| `arm_zero_control` | Send the arm zeroing command |
| `joint_angle_control` | Command one hard-coded joint angle |
| `multiple_joint_angle_control` | Command seven hard-coded joint angles |
| `generic_control` | Build a seven-joint command from command-line values |
| `get_arm_joint_angle` | Subscribe to joint-angle and arm-feedback topics |

The publishers use `rt/arm_Command`; the feedback example listens on `current_servo_angle` and `arm_Feedback`.

## Prerequisites

- Linux with CMake 3.5+ and a C++17 compiler
- Unitree `unitree_sdk2` built and installed
- Cyclone DDS C/C++ headers and libraries
- Network access to the arm's DDS domain/interface

The supplied CMake file currently expects DDS headers below `/usr/local/include/ddscxx` and `/usr/local/include/iceoryx/v2.0.2`. Adjust those paths if your SDK is installed elsewhere.

## Build

Install and verify `unitree_sdk2` first, then:

```bash
git clone https://github.com/srge-erau/D1-Arm-Control.git
cd D1-Arm-Control/d1_sdk
cmake -S . -B build
cmake --build build -j
```

Executables are written to `d1_sdk/build/` by the default CMake generator.

## Run

Start with the read-only feedback listener:

```bash
./build/get_arm_joint_angle
```

After completing the robot safety checks, an example command is:

```bash
./build/generic_control unused 0 -30 45 0 20 0 0
```

`generic_control` currently reads seven angles from arguments 2 through 8 and does not validate the argument count. The first value after the executable is therefore unused. Supply all eight arguments to avoid an out-of-range access, and inspect the resulting JSON printed by the program before adapting it for routine use.

## Message sources

The `d1_sdk/src/msg/` directory contains the generated DDS message implementations used by these examples. If Unitree changes its message definitions or wire protocol, regenerate or replace these files with the matching SDK version.

## Maintainer

[Space Robotics and Generative Estimation (SRGE) Lab](https://github.com/srge-erau), Embry-Riddle Aeronautical University.
