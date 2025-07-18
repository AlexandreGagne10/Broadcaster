# Broadcaster

This repository outlines an upcoming HDMI simulation. The goal is to broadcast
virtual HDMI frames over a network so that a receiver can analyze timing and
encoding without the need for real hardware.

## Intended HDMI Simulation

- **Server/Client model**: A provider application will act as a server that
  generates HDMI-like video frames and streams them to connected clients. The
  client reads this data, decodes it and can reproduce or inspect the video
  signal.
- **Signal analysis**: By sending well defined frame data, the system will
  allow inspection of pixel timings, sync pulses and other characteristics of
  an HDMI transmission.
- **Custom encoding**: Frames will be transmitted using a lightweight protocol
  devised for the simulator. This makes it possible to experiment with encoding
  schemes without affecting real hardware.

## Build prerequisites

No source code is currently provided, but the planned build will rely on the
following tools:

- A C++17 capable compiler (`g++` 11 or newer is recommended).
- `cmake` version 3.15 or later.
- Standard networking libraries (for example, POSIX sockets or `asio`).

Ensure these dependencies are installed before attempting to build the future
provider and client applications.

## Running the applications

After the code is implemented and compiled, you will be able to start both the
provider and client on the command line:

```bash
# in the build directory
./hdmi-provider --port 5555
```

In a separate terminal, run the client:

```bash
./hdmi-client --host localhost --port 5555
```

The provider will simulate HDMI output while the client connects to the server,
receives the frames and processes or displays them for analysis.
