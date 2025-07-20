# Eris OS

## Current State
Completely broken.

Previously, stage2.asm could successfully enable the A20 line, and print an 'A' to confirm this. Upon attempting to setup the GDT and have it print a 'G' to confirm, the 'G' would be outputted, but the 'A' would not. I can not figure out how I've managed to break this. Additionally, I have no idea why this would even occur, and thus, cannot yet fix it.
