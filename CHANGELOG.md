# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html)

## [0.1.5] - 2026-07-11

### Added

* Initial keyboard support (scancodes only for now)

## [0.1.4] - 2026-03-27

### Added

* Initial support for IRQs, timer is working
* Custom GDT (replaced GRUB's temporary model)

## [0.1.3] - 2026-01-27

### Added

* Full register dump in C interrupt handler for all ISRs
* Expanded debugging functions to force interrupts for testing
* Initial implementation of `pic.c` and `pic.h`
* Initial implementation of `io.c` and `io.h`

## [0.1.2] - 2025-11-04

### Added

* Initial Functioning IDT with working breakpoint ISR
* `int $0x03` triggers a C handler successfully

## [0.1.1] - 2025-09-14

### Added

* Terminal scrolling support

## [0.1.0] - 2025-09-13

### Added

* Initial GRUB bootloader config
* Basic kernel using VGA text mode (80x25)
* Status-based terminal output with four colours
* Simple VGA driver with terminal row/column tracking