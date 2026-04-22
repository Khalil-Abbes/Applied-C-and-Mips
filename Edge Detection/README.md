# Prog2 Project2 MinGW Patch

We want to apologize for not initially delivering the project working with MinGW.

Please install this patch to enable local building and testing on your machine.

**If you install this patch, your project won't build on WSL anymore.**
This will cause little struggle if you plan to switch to WSL later, as you will have to reset the files to the original ones before it will work there again.

## Installing this patch

This patch consists of 3 files:

- src/argparser.c
- test/config.py
- Makefile

You'll just need to copy these files into your project and overwrite the existing files there.

## Details

- `argparser.c` contains a fix for missing `<err.h>` in windows.
- `Makefile` was modified to work with Powershell.
- `config.py` was modified to remove colored and formatted output strings from the tester as these won't be displayed properly on (most) Windows terminals.