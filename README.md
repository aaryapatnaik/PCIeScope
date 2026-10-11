
# PCIeScope

A C-based toolkit for exploring PCIe device enumeration, link behavior, and transaction packets on Linux.

## Features

### PCIe Device Inspector
- Enumerates PCI devices through Linux sysfs
- Displays vendor/device IDs, class codes, and BAR resource regions
- Reports available PCIe link speeds and widths

### LTSSM Simulator
- Models PCIe link initialization through Detect, Polling, Configuration, and L0
- Simulates link failure and recovery using a C state machine

### TLP Decoder
- Decodes a sample PCIe Memory Write TLP header
- Extracts packet fields using bitwise operations

### CXL Overview
- Covers CXL.io, CXL.cache, and CXL.mem
- Explains how CXL builds on PCIe

## Build & Run

Compile:
```bash
gcc inspector.c -o inspector
gcc ltssm.c -o ltssm
gcc tlp_decoder.c -o tlp_decoder
```

Run:
```bash
./inspector
./ltssm
./tlp_decoder
```

## Notes

Developed on Linux running in UTM. Device inspection uses virtualized PCI hardware, so certain link properties may be unavailable. Link training and packet decoding are simulated rather than captured from physical hardware.
