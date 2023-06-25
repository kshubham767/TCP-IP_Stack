#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <bitset>


// EndDevice class
class EndDevice {
public:
    EndDevice(const std::string& macAddress, const std::string& ipAddress, const std::string& gatewayIP) : macAddress(macAddress), ipAddress(ipAddress), gatewayIP(gatewayIP) {}

    std::string getMACAddress() const {
        return macAddress;
    }

    std::string getIPAddress() const {
        return ipAddress;
    }

    std::string getGatewayIP() const {
        return gatewayIP;
    }

private:
    std::string macAddress;
    std::string ipAddress;
    std::string gatewayIP;
};

// Router class
class Router {
public:
    Router(const std::string& macAddress, const std::string& ipAddress) : macAddress(macAddress), ipAddress(ipAddress) {}

    std::string getMACAddress() const {
        return macAddress;
    }

    std::string getIPAddress() const {
        return ipAddress;
    }

    void addARPEntry(const std::string& ipAddress, const std::string& macAddress) {
        arpTable[ipAddress] = macAddress;
    }

    void addRoutingEntry(const std::string& subnet, const std::string& gateway) {
        routingTable[subnet] = gateway;
    }

    std::string getMACAddressForIP(const std::string& ipAddress) const {
        auto it = arpTable.find(ipAddress);
        if (it != arpTable.end()) {
            return it->second;
        }
        return "";
    }

    std::string getNextHop(const std::string& destinationIP) const {
        std::string nextHop;
        int maxMaskLength = -1;

        for (const auto& entry : routingTable) {
            std::string subnet = entry.first;
            std::string gateway = entry.second;

            if (isInSubnet(destinationIP, subnet) && subnet.length() > maxMaskLength) {
                nextHop = gateway;
                maxMaskLength = subnet.length();
            }
        }

        return nextHop;
    }

    void displayARPTable() const {
        std::cout << "ARP Table for Router with IP: " << ipAddress << "\n";
        for (const auto& entry : arpTable) {
            std::cout << "IP: " << entry.first << ", MAC: " << entry.second << "\n";
        }
        std::cout << "\n";
    }

    void displayRoutingTable() const {
        std::cout << "Routing Table for Router with IP: " << ipAddress << "\n";
        for (const auto& entry : routingTable) {
            std::cout << "Subnet: " << entry.first << ", Gateway: " << entry.second << "\n";
        }
        std::cout << "\n";
    }

     void sendPacket(const EndDevice& source, const EndDevice& destination) const {
        std::string sourceIP = source.getIPAddress();
        std::string destinationIP = destination.getIPAddress();

        if (sourceIP == destinationIP) {
            std::cout << "Source and destination devices are the same.\n";
            return;
        }

        std::vector<std::string> route;
        std::string nextHop = getNextHop(destinationIP);
        std::string nextHopMAC = getMACAddressForIP(nextHop);

        if (nextHop.empty()) {
            std::cout << "No route found from source to destination.\n";
            return;
        }

        route.push_back(sourceIP);

        while (nextHop != destinationIP) {
            route.push_back(nextHop);
            nextHop = getNextHop(nextHop);
        }

        route.push_back(destinationIP);

        std::cout << "Sending packet from " << source.getMACAddress() << " to " << destination.getMACAddress() << "\n";
        std::cout << "Route: ";
        for (const auto& ip : route) {
            std::cout << ip << " -> ";
        }
        std::cout << "\n";
        std::cout << "Destination MAC: " << nextHopMAC << "\n";
        std::cout << "Packet successfully delivered to " << destination.getMACAddress() << "\n";
    }

private:
    std::string macAddress;
    std::string ipAddress;
    std::unordered_map<std::string, std::string> arpTable; // IP address to MAC address mapping
    std::unordered_map<std::string, std::string> routingTable; // Subnet to gateway mapping

    bool isInSubnet(const std::string& ipAddress, const std::string& subnet) const {
        // Extract subnet address and mask length from subnet string
        size_t pos = subnet.find('/');
        std::string subnetAddress = subnet.substr(0, pos);
        int maskLength = std::stoi(subnet.substr(pos + 1));

        // Convert subnet address and IP address to binary format
        std::string subnetBinary = ipToBinary(subnetAddress);
        std::string ipBinary = ipToBinary(ipAddress);

        // Compare the first maskLength bits of subnet and IP address
        return subnetBinary.substr(0, maskLength) == ipBinary.substr(0, maskLength);
    }

    std::string ipToBinary(const std::string& ipAddress) const {
        std::string binary;
        size_t start = 0;
        size_t end = ipAddress.find('.');
        while (end != std::string::npos) {
            int octet = std::stoi(ipAddress.substr(start, end - start));
            binary += std::bitset<8>(octet).to_string();
            start = end + 1;
            end = ipAddress.find('.', start);
        }
        int octet = std::stoi(ipAddress.substr(start));
        binary += std::bitset<8>(octet).to_string();
        return binary;
    }
};


// Function to configure a router
void configureRouter(Router& router) {
    std::cout << "Configuring Router with IP: " << router.getIPAddress() << "\n";

    std::string choice;
    do {
        std::cout << "Choose an option:\n";
        std::cout << "1. Add ARP entry\n";
        std::cout << "2. Add routing entry\n";
        std::cout << "3. Exit configuration\n";
        std::cin >> choice;

        if (choice == "1") {
            std::string ipAddress, macAddress;
            std::cout << "Enter IP address: ";
            std::cin >> ipAddress;
            std::cout << "Enter MAC address: ";
            std::cin >> macAddress;
            router.addARPEntry(ipAddress, macAddress);
            std::cout << "ARP entry added.\n";
        } else if (choice == "2") {
            std::string subnet, gateway;
            std::cout << "Enter subnet: ";
            std::cin >> subnet;
            std::cout << "Enter gateway: ";
            std::cin >> gateway;
            router.addRoutingEntry(subnet, gateway);
            std::cout << "Routing entry added.\n";
        } else if (choice == "3") {
            std::cout << "Exiting configuration...\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << "\n";
    } while (choice != "3");

    std::cout << "Router configuration completed.\n";
}

// Function to configure an end device
void configureEndDevice(EndDevice& device) {
    std::cout << "Configuring End Device with IP: " << device.getIPAddress() <<" & MAC: "<<device.getMACAddress() << "\n";

    // Additional configuration logic for end devices can be added here

    std::cout << "End Device configuration completed.\n";
}

// Helper function to display the cost map
void displayCostMap(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& costMap) {
    for (const auto& routerEntry : costMap) {
        std::string routerIP = routerEntry.first;
        const auto& destinationMap = routerEntry.second;

        std::cout << "Router " << routerIP << ":\n";

        for (const auto& destinationEntry : destinationMap) {
            std::string destinationIP = destinationEntry.first;
            int cost = destinationEntry.second;

            std::cout << "Destination: " << destinationIP << ", Cost: " << cost << "\n";
        }

        std::cout << "\n";
    }
}

// Helper function to display the next hop map
void displayNextHopMap(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& nextHopMap) {
    for (const auto& routerEntry : nextHopMap) {
        std::string routerIP = routerEntry.first;
        const auto& destinationMap = routerEntry.second;

        std::cout << "Router " << routerIP << ":\n";

        for (const auto& destinationEntry : destinationMap) {
            std::string destinationIP = destinationEntry.first;
            std::string nextHop = destinationEntry.second;

            std::cout << "Destination: " << destinationIP << ", Next Hop: " << nextHop << "\n";
        }

        std::cout << "\n";
    }
}


// Function to display the network topology
void displayTopology(const std::vector<Router>& routers, const std::vector<EndDevice>& devices) {
    std::cout << "Network Topology:\n";

    // Display routers and their configurations
    std::cout << "Routers:\n";
    for (const auto& router : routers) {
        std::cout << "MAC: " << router.getMACAddress() << ", IP: " << router.getIPAddress() << "\n";
        router.displayARPTable();
        router.displayRoutingTable();
    }

    // Display end devices
    std::cout << "End Devices:\n";
    for (const auto& device : devices) {
        std::cout << "MAC: " << device.getMACAddress() << ", IP: " << device.getIPAddress() << "\n";
    }

    std::cout << "\n";
}

// Function to perform static routing
void staticRouting(const std::vector<Router>& routers, const std::vector<EndDevice>& devices) {
    std::cout << "Performing Static Routing...\n\n";

    for (const auto& router : routers) {
        std::cout << "Router with IP: " << router.getIPAddress() << " is performing static routing.\n";
        for (const auto& device : devices) {
            std::string nextHop = router.getNextHop(device.getIPAddress());
            std::string macAddress = router.getMACAddressForIP(nextHop);
            std::cout << "Router with IP: " << router.getIPAddress() << " can reach Device with IP: " << device.getIPAddress() << " via Next Hop: " << nextHop;
            if (!macAddress.empty()) {
                std::cout << ", MAC: " << macAddress;
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    std::cout << "Static Routing Completed.\n\n";
}

// Function to display the network topology with link weights
void displayTopology(const std::vector<Router>& routers, const std::vector<EndDevice>& devices, const std::unordered_map<std::string, std::unordered_map<std::string, int>>& costMap) {
    std::cout << "Network Topology:\n";

    // Display routers and their configurations
    std::cout << "Routers:\n";
    for (const auto& router : routers) {
        std::cout << "MAC: " << router.getMACAddress() << ", IP: " << router.getIPAddress() << "\n";
        router.displayARPTable();
        router.displayRoutingTable();

        // Display links to devices
        std::cout << "Links to Devices:\n";
        for (const auto& device : devices) {
            std::string nextHop = router.getNextHop(device.getIPAddress());
            std::string macAddress = router.getMACAddressForIP(nextHop);
            int weight = costMap.at(router.getIPAddress()).at(device.getIPAddress());

            std::cout << "Device IP: " << device.getIPAddress() << ", Next Hop: " << nextHop;
            if (!macAddress.empty()) {
                std::cout << ", MAC: " << macAddress;
            }
            std::cout << ", Weight: " << weight << "\n";
        }
        std::cout << "\n";
    }

    // Display end devices
    std::cout << "End Devices:\n";
    for (const auto& device : devices) {
        std::cout << "MAC: " << device.getMACAddress() << ", IP: " << device.getIPAddress() << "\n";
    }

    std::cout << "\n";
}

// Function to perform dynamic routing using Bellman-Ford algorithm with RIP
void dynamicRouting(std::vector<Router>& routers, const std::vector<EndDevice>& devices) {
    std::cout << "Performing Dynamic Routing (Bellman-Ford with RIP)...\n\n";

    std::unordered_map<std::string, std::unordered_map<std::string, int>> costMap; // Cost map for each router to reach other routers
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> nextHopMap; // Next hop map for each router to reach other routers

    const int INF = 16; // Infinite cost value

    // Initialize costMap and nextHopMap
    for (const auto& router : routers) {
        costMap[router.getIPAddress()] = std::unordered_map<std::string, int>();
        nextHopMap[router.getIPAddress()] = std::unordered_map<std::string, std::string>();
    }

    // Initialize costMap with direct costs to connected routers and devices
    for (const auto& router : routers) {
        for(const auto & router_sub: routers) 
        if(router_sub.getIPAddress() == router.getIPAddress()) costMap[router.getIPAddress()][router_sub.getIPAddress()] = 0; // Cost to self is 0
        else costMap[router.getIPAddress()][router_sub.getIPAddress()] = INF;
        for (const auto& device : devices) {
            if (device.getMACAddress() == router.getMACAddressForIP(device.getIPAddress())) costMap[router.getIPAddress()][device.getIPAddress()] = 1;
            else costMap[router.getIPAddress()][device.getIPAddress()] = INF; // Assuming cost to directly connected devices is 1
        }
    }

    // Perform Bellman-Ford algorithm
    bool hasUpdate;
    for (int i = 0; i < routers.size() - 1; ++i) {
        hasUpdate = false;

        for (const auto& router : routers) {
            for (const auto& destinationEntry : costMap[router.getIPAddress()]) {
                std::string destinationIP = destinationEntry.first;
                int currentCost = destinationEntry.second;

                for (const auto& neighbor : routers) {
                    if (neighbor.getIPAddress() != router.getIPAddress()) {
                        std::string neighborIP = neighbor.getIPAddress();
                        int neighborCost = costMap[neighborIP][destinationIP];

                        if (neighborCost != INF && currentCost != INF && (currentCost + neighborCost < costMap[router.getIPAddress()][destinationIP])) {
                            costMap[router.getIPAddress()][destinationIP] = currentCost + neighborCost;
                            nextHopMap[router.getIPAddress()][destinationIP] = neighborIP;
                            hasUpdate = true;
                        }
                    }
                }
            }
        }

        std::cout << "Updated Cost Map:\n";
        displayCostMap(costMap);

        std::cout << "Updated Next Hop Map:\n";
        displayNextHopMap(nextHopMap);

        // If no updates in the last iteration, exit early
        if (!hasUpdate)
            break;
    }

    // Detect negative cycles
    for (const auto& router : routers) {
        for (const auto& destinationEntry : costMap[router.getIPAddress()]) {
            std::string destinationIP = destinationEntry.first;
            int currentCost = destinationEntry.second;

            for (const auto& neighbor : routers) {
                if (neighbor.getIPAddress() != router.getIPAddress()) {
                    std::string neighborIP = neighbor.getIPAddress();
                    int neighborCost = costMap[neighborIP][destinationIP];

                    if (neighborCost != INF && currentCost != INF && (currentCost + neighborCost < costMap[router.getIPAddress()][destinationIP])) {
                        std::cout << "Negative cycle detected in the network.\n";
                        return;
                    }
                }
            }
        }
    }

    // Update costMap using RIP
    for (const auto& router : routers) {
        for (const auto& neighbor : routers) {
            if (neighbor.getIPAddress() != router.getIPAddress()) {
                std::string neighborIP = neighbor.getIPAddress();

                for (const auto& destinationEntry : costMap[neighborIP]) {
                    std::string destinationIP = destinationEntry.first;
                    int neighborCost = destinationEntry.second;

                    if (costMap[router.getIPAddress()].count(destinationIP) == 0 || (neighborCost + 1 < costMap[router.getIPAddress()][destinationIP])) {
                        costMap[router.getIPAddress()][destinationIP] = neighborCost + 1;
                        nextHopMap[router.getIPAddress()][destinationIP] = neighborIP;
                    }
                }
            }
        }
    }

    // Display routing table for each router
    for (const auto& router : routers) {
        std::cout << "Routing table for Router " << router.getIPAddress() << ":\n";
        std::cout << "Destination\t\tNext Hop\t\tCost\n";

        for (const auto& destinationEntry : costMap[router.getIPAddress()]) {
            std::string destinationIP = destinationEntry.first;
            int cost = destinationEntry.second;
            std::string nextHop = nextHopMap[router.getIPAddress()][destinationIP];

            std::cout << destinationIP << "\t\t\t" << nextHop << "\t\t\t" << cost << "\n";
        }

        std::cout << "\n";
    }
}


int main() {
    // int numRouters, numDevices;

    // std::cout << "Enter the number of routers: ";
    // std::cin >> numRouters;

    // std::cout << "Enter the number of end devices: ";
    // std::cin >> numDevices;

    std::vector<Router> routers;
    std::vector<EndDevice> devices;

    // Create routers
    // for (int i = 1; i <= numRouters; ++i) {
    //     std::string macAddress = "AA:BB:CC:DD:FF:" + std::to_string(i);
    //     std::string ipAddress = "192.168." + std::to_string(i) + ".1";
    //     routers.emplace_back(macAddress, ipAddress);
    // }

    // // Create end devices
    // for (int i = 1; i <= numDevices; ++i) {
    //     std::string macAddress = "AA:BB:CC:DD:FF:" + std::to_string(i);
    //     std::string ipAddress = "192.168." + std::to_string(i) + ".2";
    //     devices.emplace_back(macAddress, ipAddress);
    // }

    
    // // Configure end devices
    // for (auto& device : devices) {
    //     configureEndDevice(device);
    //     std::cout << "\n";
    // }

    // // Configure routers
    // for (auto& router : routers) {
    //     configureRouter(router);
    //     std::cout << "\n";
    // }

    routers.emplace_back("AA:BB:CC:DD:EE:01", "192.168.0.1");
    routers.emplace_back("AA:BB:CC:DD:EE:02", "192.168.1.1");
    routers.emplace_back("AA:BB:CC:DD:EE:03", "192.168.2.1");

    // Create end devices
    devices.emplace_back("AA:BB:CC:DD:EE:04", "192.168.0.2", "192.168.0.1");
    devices.emplace_back("AA:BB:CC:DD:EE:05", "192.168.1.2", "192.168.1.1");
    devices.emplace_back("AA:BB:CC:DD:EE:06", "192.168.2.2", "192.168.2.1");

    // Add ARP entries for routers
    routers[0].addARPEntry("192.168.0.2", "AA:BB:CC:DD:EE:04");
    routers[1].addARPEntry("192.168.1.2", "AA:BB:CC:DD:EE:05");
    routers[2].addARPEntry("192.168.2.2", "AA:BB:CC:DD:EE:06");

    // Add routing entries for routers
    routers[0].addRoutingEntry("192.168.0.0/24", "192.168.0.1");
    routers[0].addRoutingEntry("192.168.1.0/24", "192.168.0.2");
    routers[0].addRoutingEntry("192.168.2.0/24", "192.168.0.3");

    routers[1].addRoutingEntry("192.168.0.0/24", "192.168.1.1");
    routers[1].addRoutingEntry("192.168.1.0/24", "192.168.1.2");
    routers[1].addRoutingEntry("192.168.2.0/24", "192.168.1.3");

    routers[2].addRoutingEntry("192.168.0.0/24", "192.168.2.1");
    routers[2].addRoutingEntry("192.168.1.0/24", "192.168.2.3");
    routers[2].addRoutingEntry("192.168.2.0/24", "192.168.2.1");

    // Display the network topology
    displayTopology(routers, devices);

    // Prompt user for routing technique choice
    std::cout << "Choose a routing technique:\n";
    std::cout << "1. Static Routing\n";
    std::cout << "2. Dynamic Routing (Bellman-Ford)\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Perform static routing
        staticRouting(routers, devices);
    } else if (choice == 2) {
        // Perform dynamic routing using Bellman-Ford algorithm
        dynamicRouting(routers, devices);
    } else {
        std::cout << "Invalid choice. Exiting...\n";
        return 0;
    }

    return 0;
}