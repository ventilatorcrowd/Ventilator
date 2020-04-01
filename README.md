# Ventilator control software

This is WORK IN PROGRESS.

## Compilation

You can compile by running `make` from the root of the project.

You need a recent version of `arm-none-eabi-g++` compiler (version 7 which comes with Ubuntu 19.10 does not work, version 9 does, version 8 is untested).

If your package manager does not offer a sufficiently new compiler, you can download a toolchain from
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads,
unzip it and change your path to point to the `bin` subdirectory of the unzipped toolchain.
