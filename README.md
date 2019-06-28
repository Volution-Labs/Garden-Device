# Garden Minder Devices

Device code for recording sensor data and activating water valves. Automatically water, plan, and provide data for further actions needed for a living, green garden! Requires a server for full functionality.

Built with **C++** on a **esp32** microprocessor with **CoAP** for system communication. Implements soil and air temperature, soil moisture, light and rain sensors. Can be used with latching and non latching water solenoid valves.
Requires a server for full functionality.

For the other half of this project see [Garden-Server](https://github.com/Volution-Labs/garden-server)

**A work in progress.**

## Installation

Open with Arduino and modify config for your setup. Flash with normal settings.

## CLI Tool

A tool to aid in device setup and debugging is available in the garden-server repository.

## To do

- [ ] Add more sensors

- [ ] Checkins

- [ ] Latching valves
