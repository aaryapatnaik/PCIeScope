
# CXL Overview

Compute Express Link (CXL) is a high-speed interconnect built on PCIe infrastructure. It extends PCIe with memory and cache-coherency capabilities, allowing CPUs, accelerators, and memory devices to share data more efficiently.

## CXL Protocols

### CXL.io
- Handles device discovery, configuration, and I/O transactions
- Uses PCIe-based transaction mechanisms

### CXL.cache
- Lets devices such as accelerators access and cache host memory coherently
- Keeps cached data consistent across participating devices

### CXL.mem
- Allows CPUs to access device-attached memory coherently
- Commonly used for memory expansion and pooling

## PCIe vs. CXL

PCIe provides high-speed communication between a host and devices like GPUs, SSDs, and network cards.

CXL builds on PCIe's physical infrastructure and adds protocols for cache coherence and memory access.

## How This Relates to PCIeScope

PCIeScope explores the underlying PCIe concepts through device enumeration, BAR inspection, link-state simulation, and TLP decoding.

These provide a foundation for understanding how CXL devices are discovered and communicate with their hosts.
