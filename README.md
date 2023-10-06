# Computer Networks Lab - Semester Project Submission

This repository contains the code and report for the semester project submission 1 of the Computer Networks Lab (ITL355) course, Spring 2023.

## Network Simulator

We have developed a network simulator that includes all the layers of a network: Physical Layer, Data Link Layer, Network Layer, Transport Layer, and Application Layer. The code for the simulator is written in C++ language.

### IDE Used

We have implemented and compiled this code on CodeBlocks and VS Code as we have used many features that may or may not be supported by other IDEs. It is recommended to run this code on either CodeBlocks or VS Code.

### Libraries Used

- iostream
- string
- bitset
- sstream
- algorithm
- vector
- random
- ctime
- fstream
- map
- functional
- unordered_map
- limits

## Objectives

1. **Physical Layer**
   - Generated end devices and hubs.
   - Established connections between them to form a network topology.
   - Enabled data transmission and reception.
   - Displayed the topology of the network visually.

2. **Data Link Layer**
   - Built Layer 2 devices such as a switch.
   - Implemented address learning when using a switch.
   - Applied at least one Access Control Protocol, Token Passing.
   - Implemented three Flow Control Protocols for noisy channels: Stop & Wait and Selective Repeat.
   - Calculated the number of Broadcast and Collision domains present in the network.

3. **Network Layer**
   - Created and configured a router.
   - Assigned well-formatted classless IPV4 addresses to the devices.
   - Used ARP to find the MAC address of a host within a network.
   - Performed static routing.
   - Implemented RIP protocols for dynamic routing.

4. **Transport Layer and Application Layer**
   - TCP (Transport Layer)
   - UDP (Transport Layer)
   - HTTP (Application Layer)
   - FTP (Application Layer)
   - SSH (Application Layer)
   - DNS (Application Layer)

## Instructions

Please follow these instructions to run the network simulator:

1. Open the project in either CodeBlocks or VS Code.
2. Compile and build the code.
3. Run the executable generated.
4. Follow the on-screen instructions to interact with the simulator.
5. Explore different functionalities and layers of the network simulator.

Feel free to reach out to us if you have any questions or need assistance.

## License

This project is licensed under the [MIT License](LICENSE).
