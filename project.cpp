#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include "appLayer.h"

using namespace std;

int case_no = -1;

class EndDevice {
public:
    string ip;
    string mac;
    int port;
    string data;
    int seq_no;
    int subnet;
    string gateway;
    int dynamic;
    string message;

    string Generate_mac_address() {
        stringstream mac;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0x00, 0xFF);

        for (int i = 0; i < 6; i++) {
            mac << hex << dis(gen);
            if (i != 5) {
                mac << ":";
            }
        }

        return mac.str();
    }

    EndDevice(string i, int p, string d, int s)
        : ip(i), port(p), data(d), seq_no(s) {
            mac = Generate_mac_address();
            subnet = 0;
            gateway = "";
            dynamic = 0;
            message = "";
    }

    void display() {
        cout << "ip address is " << ip << endl;
        cout << "mac address is " << Generate_mac_address() << endl;
        cout << "port value = " << port << endl;
    }
};

EndDevice e1("192.168.0.10", 0, "No data", 1);
EndDevice e2("192.168.0.11", 0, "No data", 2);
EndDevice e3("192.168.0.12", 0, "No data", 3);
EndDevice e4("192.168.0.13", 0, "No data", 4);
EndDevice e5("192.168.0.14", 0, "No data", 5);
EndDevice e6("192.168.0.15", 0, "No data", 6);
EndDevice e7("192.168.0.16", 0, "No data", 7);
EndDevice e8("192.168.0.17", 0, "No data", 8);
EndDevice e9("192.168.0.18", 0, "No data", 9);
EndDevice e10("192.168.0.19", 0, "No data", 10);

vector<EndDevice> endDevices = {EndDevice("", 0, "", 0),e1, e2, e3, e4, e5, e6, e7, e8, e9, e10};

bool End_Device_Vacant() {
    int eport[] = {e1.port, e2.port, e3.port, e4.port, e5.port, e6.port, e7.port, e8.port, e9.port, e10.port};
    for (int i = 0; i < 10; i++) {
        if (eport[i] == 0) {
            return false;
        }
    }
    return true;
}

class Hub {
public:
    vector<int> ports;

    Hub() : ports(6,0) {}

    int Hub_vacant() {
        vector<int> plist = ports;
        for (int i = 0; i < 6; i++) {
            if (plist[i] == 0) {
                return 0;
            }
        }
        return 1;
    }
};

Hub Hub1;
Hub Hub2;

class Switch {
public:
    int port1;
    int port2;
    int port3;
    int port4;
    int port5;
    int port6;
    int port7;

    Switch() : port1(0), port2(0), port3(0), port4(0), port5(0), port6(0), port7(0) {}

    int Switch_vacant() {
         vector<int> slist = {port1, port2, port3, port4, port5, port6, port7};
        for (int i = 0; i < 8; i++) {
            if (slist[i] == 0) {
                return 0;
            }
        }
        return 1;
    }

     vector<string> maclist1 = {"0", "0", "0", "0", "0"};
     vector<string> maclist2 = {"0", "0", "0", "0", "0"};
};

Switch Switch1;
Switch Switch2;

class Router {
public:
    vector<vector<string>> R_table;
    vector<string> interface1;
    vector<string> interface2;
    vector<string> interface3;
    int max_ex;
    int max_p;
    int max_conf;
    int max_i1;
    int max_i2;
    int max_i3;
    int flag;
    Router()
    {
        interface1 = {};
        interface2 = {};
        interface3 = {};
        max_ex = 2;
        max_p = 2;
        max_conf = 2;
        max_i1 = 1;
        max_i2 = 1;
        max_i3 = 1;
        flag = 0;
    }
    void user_executive_mode();
    void privilege_mode();
    void global_conf();
    void Interface1();
    void Interface2();
    void Interface3();
};

Router Router1;
Router Router2;
Router Router3;

void Router::user_executive_mode() {
        while (true)
        {
            cout << "User Executive mode" << endl;
            string user;
            cin >> user;
            if (user == "en" || user == "enable") {
                privilege_mode();
            }
            else if (user == "ex") {
                return;
            }
        }
    }

void Router::privilege_mode() {
        while (true) {
            cout << "Priviledge mode" << endl;
            string user;
            cin >> user;
            if (user == "ex" || user == "exit") {
                return;
            } else if (user == "conf_t" || user == "configure_terminal") {
                global_conf();
            } else if (user == "write_memo") {
                cout << "Settings Saved" << endl;
            } else if (user == "showip_route") {
                //cout << Router1.R_table[0][0];
                cout << "showip_route"<<endl;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    }
 void Router :: global_conf() {
        while (true) {
            cout << "Global Configuration Mode" << endl;
            string user;
            cin >> user;
            if (user == "ex" || user == "exit") {
                return;
            } else if (user == "int_1") {
                Interface1();
            } else if (user == "int_2") {
                Interface2();
            } else if (user == "int_3") {
                Interface3();
            } else if (user == "iproute 0.0.0.0 0.0.0.0 ipaddress main router") {
                Router1.R_table;
            } else if (user == "iproute 10.0.0.0 255.255.255.0 20.0.0.3") {
                //routing(Router1);
            } else if (user == "router rip") {
                //RIP();
                cout << "Enter IP of Directly connected neighbours" << endl;
                string user1;
                cin >> user1;
                if (user1 == "network") {
                    cout << "Implementing rip on first one" << endl;
                    cout << "Implementing rip on second one" << endl;
                }
            } else {
                cout << "Invalid command!" << endl;
            }
        }
    }

void Router::Interface1() {
        while (true) {
            string user;
            cin >> user;
            if (user == "ip_address") {
                cout << "Enter Ip address" << endl;
                string user1;
                cin >> user1;
                interface1.push_back(user1);
                cout << "Enter Network bits" << endl;
                string user2;
                cin >> user2;
                interface1.push_back(user2);
                // Assigning IP
            } else if (user == "no_shutdown") {
                cout << "No shutdown" << endl;
            } else if (user == "ex") {
                return;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    }

void Router::Interface2() {
        while (true) {
            string user;
            cin >> user;
            if (user == "ip_address") {
                cout << "Enter Ip address" << endl;
                string user1;
                cin >> user1;
                interface2.push_back(user1);
                cout << "Enter Network bits" << endl;
                string user2;
                cin >> user2;
                interface2.push_back(user2);
                // Assigning IP
            } else if (user == "no_shutdown") {
                cout << "No shutdown" << endl;
            } else if (user == "ex") {
                return;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    }

void Router ::Interface3() {
        while (true) {
            string user;
            cin >> user;
            if (user == "ip_address") {
                cout << "Enter Ip address" << endl;
                string user1;
                cin >> user1;
                interface3.push_back(user1);
                cout << "Enter Network bits" << endl;
                string user2;
                cin >> user2;
                interface3.push_back(user2);
                // Assigning IP
            } else if (user == "no_shutdown") {
                cout << "No shutdown" << endl;
            } else if (user == "ex") {
                return;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
 }


/*-------------------------------------------------SERVER----------------------------------------------------*/

class Server {
public:
    string name;
    int port;
    int seq_no;
    string ip;
    string mac;
    vector<string> segments;  // Stores the segments of the message

    Server(string n, int p, int s, string ip)
        : name(n), port(p), seq_no(s), ip(ip) {
        EndDevice endDevice(ip, p, "", s);
        mac = endDevice.Generate_mac_address();
    }

    string GetMessage() {
        string message;
        for (const string& segment : segments) {
            message += segment;
        }
        return message;
    }
};

Server HTTP("http", 80, 1, "10.0.0.6");
Server SSH("ssh", 22, 2, "20.0.0.6");
Server SMTP("smtp", 25, 3, "30.0.0.6");

vector<Server> s_list = {HTTP, SSH, SMTP};

void messtrf(string message, int e, Server& server) {
    const int segmentSize = 4;  // Number of characters per segment
    int messageLength = message.length();
    int numSegments = (messageLength + segmentSize - 1) / segmentSize;  // Calculate number of segments

    for (int i = 0; i < numSegments; ++i) {
        int startIndex = i * segmentSize;
        int endIndex = min(startIndex + segmentSize, messageLength);
        string segment = message.substr(startIndex, endIndex - startIndex);
        server.segments.push_back(segment);
    }
}

/*-----------------------------------------------UDP--------------------------------------------------------*/

void udp(string n, int p, string ip, int e, string m) {
    for (Server& i : s_list) {
        if (n == i.name) {
            if (ip == i.ip)
            {
                if(p == i.port){
                std::srand(static_cast<unsigned>(std::time(nullptr)));
                int x = rand() % 11;
                if (x >= 5) {
                    messtrf(m, e, i);
                    cout << "Segments received by the server: " << endl;
                    for (const string& segment : i.segments) {
                        cout << segment << endl;
                    }
                    cout << "Complete message received by the server: " << i.GetMessage() << endl;
                    return;
                } else {
                    cout << "Packet got dropped because of the unreliability of UDP" << endl;
                    return;
                }
                }
                else
                {
                    cout<<"Port does not match"<<endl;
                    return;
                }
            }
            else {
                cout << "IP does not match" << endl;
                return;
            }
        }
    }
    cout << "Invalid Server!" << endl;
}

/*-----------------------------------------------TCP--------------------------------------------------------*/

void tcp(string n, int p, string ip, int e, string m) {
    for (Server& server : s_list) {
        if (n == server.name) {
            if (ip == server.ip)
            {
                if(p == server.port){
                string buffer = m;
                messtrf(buffer, e, server);
                cout << "Segments received by the server: " << endl;
                for (const string& segment : server.segments) {
                    cout << segment << endl;
                }
                cout << "Complete message received by the server: " << server.GetMessage() << endl;
                return;
                }
                else
                {
                    cout<<"Port does not match"<<endl;
                    return;
                }
            }
            else
            {
                cout << "IP does not match." << endl;
                return;
            }
        }
    }
    cout << "Invalid Server!" << endl;
}

/*-----------------------------------Conversion of IP and NID------------------------------------------------*/

string get_nid(string ip_address, int subnet) {
    string x = "";
    string binary = "";

    for (int i = 0; i < ip_address.length(); i++) {
        if (ip_address[i] != '.') {
            x += ip_address[i];
        } else {
            binary += bitset<8>(stoi(x)).to_string();
            x = "";
        }

        if (i == ip_address.length() - 1 && ip_address[i] != '.') {
            binary += bitset<8>(stoi(x)).to_string();
        }
    }

    string s = "";
    for (int i = 0; i < subnet; i++) {
        s += binary[i];
    }

    for (int i = 0; i < 32 - subnet; i++) {
        s += '0';
    }
    cout<<"IP in binary : "<<binary<<endl;
    cout<<"NID in binary : "<<s<<endl;
    return s;
}


int subnettingBits(string& subnetMask) {
    string binaryMask;
    for (char c : subnetMask) {
        if (c == '.')
            continue;
        int octet = c - '0';
        binaryMask += bitset<8>(octet).to_string();
    }
    int subnettingBitsCount = 0;
    for (char bit : binaryMask) {
        if (bit == '1')
            subnettingBitsCount++;
        else
            break;
    }
    return subnettingBitsCount;
}

/*---------------------------------------------PING--------------------------------------------------------*/

void ping(int src, int dest) {
    if (Router1.flag == 0 && case_no == 7) {
        cout << "Timeout Occurred" << endl;
    } else if (get_nid(endDevices[src].ip, endDevices[src].subnet) == get_nid(endDevices[dest].ip, endDevices[src].subnet)) {
        cout << "Searching the MAC address of destination in ARP Cache..." << endl;
        cout << "Found the IP address in ARP Cache" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "Reply from: " << endDevices[dest].ip << " bytes=32 time<1ms TTL=128" << endl;
        }
    } else {
        cout << "Searching the MAC address of destination in ARP Cache..." << endl;
        cout << "Couldn't find the MAC address of destination in the ARP Cache" << endl;
        cout << "Default Gateway is " << endDevices[src].gateway << endl;
        for (int i = 0; i < Router1.R_table.size(); i++) {
            if (get_nid(endDevices[dest].ip, endDevices[dest].subnet) == get_nid(Router1.R_table[i][0], subnettingBits(Router1.R_table[i][1]))) {
                cout << "Searching the MAC address of destination in ARP Cache..." << endl;
                cout << "Found the IP address in ARP Cache" << endl;
                for (int i = 0; i < 4; i++) {
                    cout << "Reply from: " << endDevices[dest].ip << " bytes=32 time<1ms TTL=128" << endl;
                }
                return;
            }
        }
        cout << "New Timeout occurred" << endl;
    }
}

/*------------------------------------Routing----------------------------------------------------------------------*/


void routing(Router router) {
        vector<string> entry1 = { get_nid(endDevices[1].ip, endDevices[1].subnet),
                                  to_string(endDevices[1].subnet),
                                  router.interface1[0] };
        router.R_table.push_back(entry1);

        vector<string> entry2 = { get_nid(endDevices[2].ip, endDevices[2].subnet),
                                  to_string(endDevices[2].subnet),
                                  router.interface2[0] };
        router.R_table.push_back(entry2);
    }

/*----------------------------------------------RIP--------------------------------------------------------*/

void RIP() {
    vector<vector<string>> temp1;
    vector<vector<string>> temp2;
    vector<vector<string>> temp3;
    temp1 = Router1.R_table;
    Router1.flag = 1;
    temp2 = Router2.R_table;
    temp3 = Router3.R_table;

    for (int i = 0; i < 5; i++) {
        if (stoi(Router1.R_table[i][4]) > 1 + stoi(temp2[i][4])) {
            Router1.R_table[i][4] = to_string(1 + stoi(temp2[i][4]));
            Router1.R_table[i][3] = "40.0.0.2";
        }

        if (stoi(Router1.R_table[i][4]) > 1 + stoi(temp3[i][4])) {
            Router1.R_table[i][4] = to_string(1 + stoi(temp3[i][4]));
            Router1.R_table[i][3] = "30.0.0.2";
        }

        if (stoi(Router2.R_table[i][4]) > 1 + stoi(temp1[i][4])) {
            Router2.R_table[i][4] = to_string(1 + stoi(temp1[i][4]));
            Router2.R_table[i][3] = "40.0.0.1";
        }

        if (stoi(Router2.R_table[i][4]) > 1 + stoi(temp3[i][4])) {
            Router2.R_table[i][4] = to_string(1 + stoi(temp3[i][4]));
            Router2.R_table[i][3] = "50.0.0.1";
        }

        if (stoi(Router3.R_table[i][4]) > 1 + stoi(temp1[i][4])) {
            Router3.R_table[i][4] = to_string(1 + stoi(temp1[i][4]));
            Router3.R_table[i][3] = "30.0.0.1";
        }

        if (stoi(Router3.R_table[i][4]) > 1 + stoi(temp2[i][4])) {
            Router3.R_table[i][4] = to_string(1 + stoi(temp2[i][4]));
            Router3.R_table[i][3] = "50.0.0.2";
        }
    }

    for (const auto& entry : Router1.R_table) {
        for (const auto& value : entry) {
            cout << value << " ";
        }
        cout << endl;
    }
}

/*----------------------------------------------DHCP--------------------------------------------------------*/


void DHCP(int enddevice) {
    string generatedAddress;
    if (enddevice == 1 || enddevice == 2 || enddevice == 3) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(2, 254);
        int ran = dis(gen);
        string r = to_string(ran);
        string p = "";
        int dots = 0;
        for (char i : Router1.interface1[0]) {
            if (i == '.') {
                dots++;
            }
            if (dots >= 3) {
                p += i;
                break;
            } else {
                p += i;
            }
        }
        p += r;
        generatedAddress = p;
    } else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(2, 254);
        int ran = dis(gen);
        string r = to_string(ran);
        string p = "";
        int dots = 0;
        for (char i : Router1.interface2[0]) {
            if (i == '.') {
                dots++;
            }
            if (dots >= 3) {
                p += i;
                break;
            } else {
                p += i;
            }
        }
        p += r;
        generatedAddress = p;
    }

    cout << "The generated address is " << generatedAddress << endl;
}

/*-----------------------------------------------------HTTP------------------------------------------*/


/*-----------------------------FLOW CONTROL PROTOCOL: STOP AND WAIT ARQ------------------------------------*/

void stop_and_wait_arq_HUb(int a, int b, string c) {
    int sender = 0;
    int receiver = 0;
    int s = 0;
    int ack = 0;
    for (int i = 0; i < c.size(); i++) {
        if (i % 2 == 0) {
            s = 0;
            ack = 1;
        } else {
            s = 1;
            ack = 0;
        }

        int c1 = count(Switch1.maclist1.begin(), Switch1.maclist1.end(), endDevices[b].mac);
        int c2 = count(Switch1.maclist2.begin(), Switch1.maclist2.end(), endDevices[b].mac);
        if (c1 == 0 && c2 == 0) {
            cout << "Mac Address of End Device " << b << " not found in the MAC table\n";
            cout << "Switch will broadcast the message\n";

            if (i != 0 && i % 4 == 0) {
                cout << "Time out occurred, Sending the " << i << "th frame again. Sequence number: " << s << "\n";
            }
            cout << "Sending First packet -----" << c[0] << "-----\n";
            for (int j = 1; j <= 10; j++) {
                if (j != a) {
                    endDevices[j].data = c[i];
                    cout << "Message sent to End Device " << j << "\n";
                }
                if (j == b) {
                    cout << "Ack received by End Device " << b << " ACK NO: " << ack << "\n";
                }
            }
            cout << "\n";
            if (a < 6) {
                Switch1.maclist1[a - 1] = endDevices[a].mac;
            } else {
                Switch1.maclist2[a - 6] = endDevices[a].mac;
            }
            if (b < 6) {
                Switch1.maclist1[b - 1] = endDevices[b].mac;
            } else {
                Switch1.maclist2[b - 6] = endDevices[b].mac;
            }
        } else {
            if (a < 6 && b < 6) {
                cout << "Mac Address found, Both Devices in Hub 1\n";
                cout << "Sending packet -----" << c[i] << "-----\n";
                if (i != 0 && i % 4 == 0) {
                    cout << "Time out occurred, Sending the " << i << "th frame again. Sequence number: " << s << "\n";
                }
                for (int j = 1; j <= 5; j++) {
                    if (j != a) {
                        endDevices[j].data = c[i];
                        cout << "Message sent to End Device " << j << "\n";
                    }
                    if (j == b) {
                        cout << "Ack received by End Device " << b << " ACK NO: " << ack << "\n";
                    }
                }
                cout << "\n";
            } else if (a > 6 && b > 6) {
                cout << "Mac Address found, Both Devices in Hub 2\n";
                cout << "Sending packet -----" << c[i] << "-----\n";
                if (i != 0 && i % 4 == 0) {
                    cout << "Time out occurred, Sending the " << i << "th frame again. Sequence number: " << s << "\n";
                }
                for (int j = 6; j <= 10; j++) {
                    if (j != a) {
                        endDevices[j].data = c[i];
                        cout << "Message sent to End Device " << j << "\n";
                    }
                    if (j == b) {
                        cout << "Ack received by End Device " << b << " ACK NO: " << ack << "\n";
                    }
                }
                cout << "\n";
            } else {
                cout << "Mac Address of End Device " << b << " found in the MAC table\n";
                cout << "Sending packet -----" << c[i] << "-----\n";
                cout << "Sending to other port\n";
                if (i != 0 && i % 4 == 0) {
                    cout << "Time out occurred, Sending the " << i << "th frame again. Sequence number: " << s << "\n";
                }
                for (int j = 1; j <= 10; j++) {
                    if (j != a) {
                        endDevices[j].data = c[i];
                        cout << "Message sent to End Device " << j << "\n";
                    }
                    if (j == b) {
                        cout << "Ack received by End Device " << b << " ACK NO: " << ack << "\n";
                    }
                }
                cout << "\n";
                if (a < 6) {
                    Switch1.maclist1[a - 1] = endDevices[a].mac;
                } else {
                    Switch1.maclist2[a - 6] = endDevices[a].mac;
                }
                if (b < 6) {
                    Switch1.maclist1[b - 1] = endDevices[b].mac;
                } else {
                    Switch1.maclist2[b - 6] = endDevices[b].mac;
                }
            }
        }
    }
}

void stop_and_wait_arq(int a, int b, string c) {
    int sender = 0;
    int receiver = 0;
    int s = 0;
    int ack = 0;
    for (int i = 0; i < c.size(); i++) {
        if (i % 2 == 0) {
            s = 0;
            ack = 1;
        } else {
            s = 1;
            ack = 0;
        }
        int c1 = count(Switch1.maclist1.begin(), Switch1.maclist1.end(), endDevices[b].mac);
        if (c1 == 0) {
            cout << "Mac Address of End Device " << b << " not found in the MAC table" << endl;
            cout << "Switch will broadcast the message" << endl;
            cout << "Sending  packet ----- " << c[i] << " -----" << endl;
            if (i != 0 && i % 4 == 0) {
                cout << "time out occurred, Sending the " << i << "th frame again. Sequence number : " << s << endl;
            }
            for (int j = 1; j <= 5; j++) {
                if (j != a) {
                    endDevices[j].data = c[i];
                    cout << "Message sent to End Device " << j << endl;
                }
                if (j == b) {
                    cout << "Ack received by End Device " << b << " ACK NO : " << ack << endl;
                }
            }
            cout << endl;
            Switch1.maclist1[a - 1] = endDevices[a].mac;
            Switch1.maclist1[b - 1] = endDevices[b].mac;
        } else {
            cout << "Mac Address of End Device " << b << " found in the MAC table" << endl;
            cout << "Sending  packet ----- " << c[i] << " -----" << endl;
            if (i != 0 && i % 4 == 0) {
                cout << "time out occurred, Sending the " << i << "th frame again. Sequence number : " << s << endl;
            }
            cout << "Message sent to End Device " << b << endl;
            cout << "ACK received from End Device " << b << endl;
            cout << endl;
            Switch1.maclist1[a - 1] = endDevices[a].mac;
            Switch1.maclist1[b - 1] = endDevices[b].mac;
        }
    }
}

/*-----------------------------FLOW CONTROL PROTOCOL: SELECTIVE REPEAT------------------------------------*/

void Selective_Repeat_Hub(int a, int b, string c) {
    cout << "Enter the reserved bit size for Seq no" << endl;
    int m;
    cin >> m;

    int sf = 0;
    int sn = 0;
    int x = c.size();
    int Window_Size = pow(2, m - 1);
    int Seq_no = pow(2, m);
    vector<int> array(x, 0);
    vector<int> visited(x, 0);

    while (x != 0) {
        int marker = 0;

        while (sn < sf + Window_Size && sn < c.size()) {
            if (array[sn] == 0) {
                if (sn % 3 == 0 && visited[sn] == 0) {
                    cout << sn << "-th packet lost, Sending next packet" << endl;
                    visited[sn] = 1;
                    if (marker == 0) {
                        sf = sn;
                        marker = marker + 1;
                    }
                } else {
                    array[sn] = 1;

                    int c1 = count(Switch1.maclist1.begin(), Switch1.maclist1.end(), endDevices[b].mac);
                    int c2 = count(Switch1.maclist2.begin(), Switch1.maclist2.end(), endDevices[b].mac);

                    if (c1 == 0 && c2 == 0) {
                        cout << "Mac Address of End Device " << b << " not found in the MAC table" << endl;
                        cout << "Switch will broadcast the message" << endl;
                        cout << "Sending packet -----" << c[sn] << "-----" << endl;

                        for (int j = 1; j < 11; j++) {
                            if (j != a) {
                                endDevices[j].data = c[sn];
                                cout << "Message sent to End Device " << j << endl;
                            }
                            if (j == b) {
                                cout << "Ack received by End Device " << b << " ACK NO :" << sn % Seq_no << endl;
                            }
                        }
                        cout << endl;

                        if (a < 6) {
                            Switch1.maclist1[a - 1] = endDevices[a].mac;
                        } else {
                            Switch1.maclist2[a - 6] = endDevices[a].mac;
                        }

                        if (b < 6) {
                            Switch1.maclist1[b - 1] = endDevices[b].mac;
                        } else {
                            Switch1.maclist2[b - 6] = endDevices[b].mac;
                        }
                    } else {
                        if (a < 6 && b < 6) {
                            cout << "Mac Address found, Both Devices in Hub 1" << endl;
                            cout << "Sending packet -----" << c[sn] << "-----" << endl;

                            for (int j = 1; j < 6; j++) {
                                if (j != a) {
                                    endDevices[j].data = c[sn];
                                    cout << "Message sent to End Device " << j << endl;
                                }
                                if (j == b) {
                                    cout << "Ack received by End Device " << b << " ACK NO :" << sn % Seq_no << endl;
                                }
                            }
                            cout << endl;
                        } else if (a > 6 && b > 6) {
                            cout << "Mac Address found, Both Devices in Hub 2" << endl;
                            cout << "Sending packet -----" << c[sn] << "-----" << endl;

                            for (int j = 6; j < 11; j++) {
                                if (j != a) {
                                    endDevices[j].data = c[sn];
                                    cout << "Message sent to End Device " << j << endl;
                                }
                                if (j == b) {
                                    cout << "Ack received by End Device " << b << " ACK NO :" << sn % Seq_no << endl;
                                }
                            }
                            cout << endl;
                        } else {
                            cout << "Mac Address of End Device " << b << " found in the MAC table" << endl;

                            if (sn != 0 && sn % 4 == 0) {
                                cout << "time out occurred, Sending the " << sn << "th frame again." << endl;
                                cout << "Sequence number: " << sn % Seq_no << endl;
                            }
                            cout << "Sending packet -----" << c[sn] << "-----" << endl;

                            for (int j = 1; j < 11; j++) {
                                if (j != a) {
                                    endDevices[j].data = c[sn];
                                    cout << "Message sent to End Device " << j << endl;
                                }
                                if (j == b) {
                                    cout << "Ack received by End Device " << b << " ACK NO :" << sn % Seq_no << endl;
                                }
                            }
                            cout << endl;

                            if (a > 5) {
                                Switch1.maclist1[a - 6] = endDevices[a].mac;
                            } else {
                                Switch1.maclist1[a - 1] = endDevices[a].mac;
                            }

                            if (b > 5) {
                                Switch1.maclist2[b - 6] = endDevices[b].mac;
                            } else {
                                Switch1.maclist2[b - 1] = endDevices[b].mac;
                            }
                        }
                    }

                    x = x - 1;

                    if (sf == sn) {
                        for (int i = sf; i < c.size(); i++) {
                            if (array[i] == 0) {
                                sf = i;
                                sn = sf - 1;
                                break;
                            }
                        }
                    }
                }

            }
            sn = sn + 1;
        }

        if (sn < c.size()) {
            cout << "Restart the timer, sending the outstanding packets again" << endl;
        }
        sn = sf;
    }
}

void Selective_Repeat(int a, int b, string c) {
    cout << "Enter the reserved bit size for Seq no" << endl;
    int m;
    cin >> m;

    int sf = 0;
    int sn = 0;
    int x = c.size();
    int Window_Size = pow(2, m - 1);
    int Seq_no = pow(2, m);
    vector<int> array(x, 0);
    vector<int> visited(x, 0);

    while (x != 0) {
        int marker = 0;

        while (sn < sf + Window_Size && sn < c.size()) {
            if (array[sn] == 0) {
                if (sn % 2 == 0 && visited[sn] == 0) {
                    cout << sn << "th packet lost, Sending next packet" << endl;
                    visited[sn] = 1;
                    if (marker == 0) {
                        sf = sn;
                        marker = marker + 1;
                    }
                }
                else
                {
                    array[sn] = 1;

                    int c1 = count(Switch1.maclist1.begin(), Switch1.maclist1.end(), endDevices[b].mac);

                    if (c1 == 0) {
                        cout << "Mac Address of End Device " << b << " not found in the MAC table" << endl;
                        cout << "Switch will Broadcast the message" << endl;
                        cout << "Sending packet -----" << c[sn] << "-----" << endl;

                        for (int j = 1; j < 6; j++) {
                            if (j != a) {
                                endDevices[j].data = c[sn];
                                cout << "Message sent to End Device " << j << endl;
                            }
                            if (j == b) {
                                cout << "Ack received by End Device " << b << " ACK NO :" << sn % Seq_no << endl;
                            }
                        }
                        cout << endl;

                        Switch1.maclist1[a - 1] = endDevices[a].mac;
                        Switch1.maclist1[b - 1] = endDevices[b].mac;
                    } else {
                        cout << "Mac Address of End Device " << b << " found in the MAC table" << endl;
                        cout << "Sending packet -----" << c[sn] << "-----" << endl;

                        if (sn != 0 && sn % 4 == 0) {
                            cout << "time out occurred, Sending the " << sn << "th frame again." << endl;
                        }
                        cout << "Message sent to End Device " << b << endl;
                        cout << "ACK received from End Device " << b << endl;
                        cout << endl;

                        Switch1.maclist1[a - 1] = endDevices[a].mac;
                        Switch1.maclist1[b - 1] = endDevices[b].mac;
                    }

                    x = x - 1;

                    if (sf == sn) {
                        for (int i = sf; i < c.size(); i++) {
                            if (array[i] == 0) {
                                sf = i;
                                sn = sf - 1;
                                break;
                            }
                        }
                    }
                }

            }
            sn = sn + 1;
        }

        if (sn < c.size()) {
            cout << "Restart the timer, sending the outstanding packets again" << endl;
        }
        sn = sf;
    }
}

/*----------------------------------------------------ACCESS CONTROL-----------------------------------------*/


vector<int> end_Devices = {e1.seq_no, e2.seq_no, e3.seq_no, e4.seq_no, e5.seq_no, e6.seq_no, e7.seq_no, e8.seq_no, e9.seq_no, e10.seq_no};

void token_passing(int token, int num1) {
    int t = token;
    int s = num1;

    if (t == s) {
        cout << "Sender has the access already!" << endl;
    } else if (t < s) {
        cout << "End Device " << t << " Has access" << endl;
        cout << "------Passing the Token" << endl;
        for (int i = 0; i < endDevices.size(); i++ ) {
            cout << "End Device " << i + t << " Has access now" << endl;

            if (s == i + t) {
                cout << "----------------------------Access granted-----------------------------------" << endl;
                break;
            }
            if (i != s) {
                cout << "------Passing the Token" << endl;
            }
        }
    } else {
        cout << "End Device " << t << " Has access" << endl;
        cout << "------Passing the Token" << endl;
        for (int i = 0; i <  endDevices.size(); i++) {
            end_Devices[i] = t;
            cout << "End Device " << t - i << " Has access now" << endl;

            if (s == t - i) {
                cout << "----------------------------Access granted-----------------------------------" << endl;
                break;
            }
            if (i != s) {
                cout << "------Passing the Token" << endl;
            }
        }
    }
}


void collision_broadcast(int num4) {
    if (1 == num4 || 2 == num4) {
        cout << "Collision Domain: 1" << endl;
        cout << "Broadcast Domain: 1" << endl;
    } else if (3 == num4 || 4 == num4) {
        cout << "Collision Domain: 2" << endl;
        cout << "Broadcast Domain: 1" << endl;
    } else if (5 == num4) {
        cout << "Collision Domain: 5" << endl;
        cout << "Broadcast Domain: 1" << endl;
    } else if (6 == num4) {
        cout << "Collision Domain: 5" << endl;
        cout << "Broadcast Domain: 1" << endl;
    } else if (7 == num4) {
        cout << "Collision Domain: 6" << endl;
        cout << "Broadcast Domain: 1" << endl;
    }
}

/*-------------------------------------------------MENU---------------------------------------------------------*/


void establishDedicatedLink(EndDevice& e1, EndDevice& e2) {
    cout << "Enter Sender Device no: ";
    int num1;
    cin >> num1;
    cout << "Enter Receiver Device no: ";
    int num2;
    cin >> num2;

    cout << "You have selected these two End Devices: " << num1 << " and " << num2 << endl;
    if (e1.port == e2.port) {
        cout << "Enter the message to be transmitted: ";
        string message;
        cin.ignore();
        getline(cin, message);
        cout << "Message: " << message << endl;

        e1.data = message;
        cout << "Connection made between two End devices" << endl;
        e1.port = 1;
        e2.port = 2;
        e2.data = e1.data;
        cout << "Message sent successfully: " << message << endl;

        if (e2.data == e1.data) {
            cout << "                                                     ----ACK RECEIVED FROM END DEVICE " << num2 << "---" << endl;
        } else {
            cout << "---ACK LOST---" << endl;
        }
    } else {
        cout << "No connection possible, already occupied" << endl;
    }
}

void establishHubTopology(EndDevice& e1, Hub & Hub1, EndDevice& e2, EndDevice& e3, EndDevice& e4, EndDevice& e5)
{
    cout<<"Device No. should be between 1 and 5"<<endl;
    cout << "Enter Sender Device number: ";
    int senderDevice;
    cin >> senderDevice;
    cout << "Enter Receiver Device number: ";
    int receiverDevice;
    cin >> receiverDevice;
    if((senderDevice>=1&&senderDevice<=5)&&(receiverDevice >= 1 && receiverDevice <= 5)&&(senderDevice!=receiverDevice)){
    cout << "You have selected these two End Devices within the same HUB: " << senderDevice << " and " << receiverDevice << endl;

    if(End_Device_Vacant()==0&&Hub1.Hub_vacant()==0) {
        endDevices[senderDevice].port = 1;
        Hub1.ports[0]=1;
        cout << "Connection made between Sender-End devices and HUB" << endl;
        for(int i=1;i<4;i++)
        {
            if(Hub1.Hub_vacant()==0)
            {
                Hub1.ports[i]=i+1;
            }
            else
            {
                cout<<"No Port vacant in HUB"<<endl;
                break;
            }
        }
        cout << "Connection made between HUB and other End devices" << endl;
        endDevices[receiverDevice].port=5;
        Hub1.ports[4]=5;
            cout << "Connection made between HUB and Receiver-End device" << endl;
            cout << "Enter the message: ";
            string message;
            cin.ignore();
            getline(cin, message);
            cout << "Message: " << message << endl;

            // Broadcast the message to all end devices
            for (int i = 0; i < 5; i++) {
                if (i + 1 != senderDevice) {
                    endDevices[i].data = message;
                    cout << "Message sent from End Device " << senderDevice << " to End Device " << i + 1 << " successfully." << endl;
                }
            }

            // Receiver acknowledges the message
            if(endDevices[receiverDevice - 1].data==message)
               cout << "Acknowledgement (ACK) received from End Device " << receiverDevice << endl;
            else
                cout<<"Ack lost, no connection"<<endl;

    }
    else {
        cout << "No vacant port available in the HUB." << endl;
    }
    }
    else
    {
        cout<<"Enter the correct Device No."<<endl;
    }

}

void addLearning()
{
   if (Hub1.Hub_vacant() == 0 && Switch1.Switch_vacant() == 0 && Hub2.Hub_vacant() == 0) {
        cout << "Connection made between --Hub1------Switch------Hub2--" << endl;
        Switch1.port1 = 2;
        Hub1.ports[5] = 6;
        Hub2.ports[5] = 4;
        if (End_Device_Vacant() == 0 && Hub1.Hub_vacant() == 0) {
            cout << "......................HUB 1  CONNECTING......................." << endl;
            cout << "Connection made between Hub1 and End Device 1" << endl;
            e1.port = 1;
            Hub1.ports[0] = 9;
            if (Hub1.ports[1] == 0 && Hub1.ports[2] == 0 && Hub1.ports[3] == 0 && Hub1.ports[4] == 0) {
                cout << "Connection made between Hub1 and End Device 2" << endl;
                cout << "Connection made between Hub1 and End Device 3" << endl;
                cout << "Connection made between Hub1 and End Device 4" << endl;
                cout << "Connection made between Hub1 and End Device 5" << endl;
                e2.port = 7;
                e3.port = 2;
                e4.port = 8;
                e5.port = 1;
                Hub1.ports[1] = 5;
                Hub1.ports[2] = 8;
                Hub1.ports[3] = 52;
                Hub1.ports[4] = 80;
            } else {
                cout << "No Port vacant in HUB" << endl;
            }
        } else {
            cout << "---No end device vacant---" << endl;
        }

        if (End_Device_Vacant() == 0 || Hub2.Hub_vacant() == 0) {
            cout << "......................HUB 2  CONNECTING......................." << endl;
            cout << "Connection made between Hub2 and End Device 6" << endl;
            e6.port = 1;
            Hub2.ports[0] = 9;
            if (Hub2.ports[1] == 0 && Hub2.ports[2] == 0 && Hub2.ports[3] == 0 && Hub2.ports[4] == 0) {
                cout << "Connection made between Hub2 and End Device 7" << endl;
                cout << "Connection made between Hub2 and End Device 8" << endl;
                cout << "Connection made between Hub2 and End Device 9" << endl;
                cout << "Connection made between Hub2 and End Device 10" << endl;
                e7.port = 71;
                e8.port = 22;
                e9.port = 71;
                e10.port = 22;
                Hub2.ports[1] = 50;
                Hub2.ports[2] = 801;
                Hub2.ports[3] = 501;
                Hub2.ports[4] = 800;
            } else {
                cout << "No Port vacant in HUB" << endl;
            }
        } else {
            cout << "---No end device vacant---" << endl;
        }

        std::cout << "Enter the message: ";
        std::string num3;
        cin>>num3;
        std::cout << "Message: " << num3 << std::endl;
        e1.data = num3;

        std::cout << "Sender Device is 1" << std::endl;
        std::cout << "Receiver Device is 2" << std::endl;
        std::cout << "Searching for MAC address of End Device 2" << std::endl;
        std::cout << "Mac Address of End Device 2 is = " << e2.mac << std::endl;

        for (int i = 0; i < 5; i++) {
            if (Switch1.maclist1[i] == e2.mac) {
                std::cout << "MAC address found in MAC table within the same port" << std::endl;
                e2.data = e1.data;
                std::cout << "Message sent to End Device 2" << std::endl;
                e3.data = e1.data;
                std::cout << "Message sent to End Device 3" << std::endl;
                e4.data = e1.data;
                std::cout << "Message sent to End Device 4" << std::endl;
                e5.data = e1.data;
                std::cout << "Message sent to End Device 5" << std::endl;
                std::cout << "---ACK RECEIVED from End Device 2---" << std::endl;
                break;
            }
            if (i == 4) {
                std::cout << "Mac Address of End Device 2 not found in the MAC table" << std::endl;
                e2.data = e1.data;
                std::cout << "Message sent to End Device 2" << std::endl;
                e3.data = e1.data;
                std::cout << "Message sent to End Device 3" << std::endl;
                e4.data = e1.data;
                std::cout << "Message sent to End Device 4" << std::endl;
                e5.data = e1.data;
                std::cout << "Message sent to End Device 5" << std::endl;
                e6.data = e1.data;
                std::cout << "Message sent to End Device 6" << std::endl;
                e7.data = e1.data;
                std::cout << "Message sent to End Device 7" << std::endl;
                e8.data = e1.data;
                std::cout << "Message sent to End Device 8" << std::endl;
                e9.data = e1.data;
                std::cout << "Message sent to End Device 9" << std::endl;
                e10.data = e1.data;
                std::cout << "Message sent to End Device 10" << std::endl;
                std::cout << "---ACK RECEIVED from End Device 2---" << std::endl;
            }
        }

        Switch1.maclist1[0] = e1.mac;
        Switch1.maclist1[1] = e2.mac;
        Switch1.maclist1[2] = e3.mac;
        //Switch1.maclist1[3] = e4.mac;
        Switch1.maclist1[4] = e5.mac;
        Switch1.maclist2[0] = e6.mac;
        //Switch1.maclist2[1] = e7.mac;
        Switch1.maclist2[2] = e8.mac;
        //Switch1.maclist2[3] = e9.mac;
        Switch1.maclist2[4] = e10.mac;

        std::cout << "Updated MAC Table in Switch 1" << std::endl;
        std::cout << "MAC Address List 1:" << std::endl;
        for (int i = 0; i < 5; i++) {
            std::cout << Switch1.maclist1[i] << std::endl;
        }
        std::cout << "MAC Address List 2:" << std::endl;
        for (int i = 0; i < 5; i++) {
            std::cout << Switch1.maclist2[i] << std::endl;
        }
    }
    return ;
}

void accessFlow()
{
    if (Hub1.Hub_vacant() == 0 && Switch1.Switch_vacant() == 0 && Hub2.Hub_vacant() == 0) {
        std::cout << "Connection made between --Hub1------Switch------Hub2--" << std::endl;
        Switch1.port1 = 2;
        Hub1.ports[5] = 6;
        Hub2.ports[5] = 4;
    }

    if (End_Device_Vacant() == 0 && Hub1.Hub_vacant() == 0) {
        std::cout << "......................HUB 1  CONNECTING......................." << std::endl;
        std::cout << "Connection made between Hub1 and End Device 1" << std::endl;
        e1.port = 1;
        Hub1.ports[0] = 9;

        if (Hub1.ports[1] == 0 && Hub1.ports[2] == 0 && Hub1.ports[3] == 0 && Hub1.ports[4] == 0) {
            std::cout << "Connection made between Hub1 and End Device 2" << std::endl;
            std::cout << "Connection made between Hub1 and End Device 3" << std::endl;
            std::cout << "Connection made between Hub1 and End Device 4" << std::endl;
            std::cout << "Connection made between Hub1 and End Device 5" << std::endl;
            e2.port = 7;
            e3.port = 2;
            e4.port = 8;
            e5.port = 1;
            Hub1.ports[1] = 5;
            Hub1.ports[2] = 8;
            Hub1.ports[3] = 52;
            Hub1.ports[4] = 80;
        } else {
            std::cout << "No Port vacant in HUB" << std::endl;
        }
    } else {
        std::cout << "---No end device vacant---" << std::endl;
    }

    if (End_Device_Vacant() == 0 || Hub2.Hub_vacant() == 0) {
        std::cout << "......................HUB 2  CONNECTING......................." << std::endl;
        std::cout << "Connection made between Hub2 and End Device 6" << std::endl;
        e6.port = 1;
        Hub2.ports[0] = 9;

        if (Hub2.ports[1] == 0 && Hub2.ports[2] == 0 && Hub2.ports[3] == 0 && Hub2.ports[4] == 0) {
            std::cout << "Connection made between Hub2 and End Device 7" << std::endl;
            std::cout << "Connection made between Hub2 and End Device 8" << std::endl;
            std::cout << "Connection made between Hub2 and End Device 9" << std::endl;
            std::cout << "Connection made between Hub2 and End Device 10" << std::endl;
            e7.port = 71;
            e8.port = 22;
            e9.port = 71;
            e10.port = 22;
            Hub2.ports[1] = 50;
            Hub2.ports[2] = 801;
            Hub2.ports[3] = 501;
            Hub2.ports[4] = 800;
        } else {
            std::cout << "No Port vacant in HUB" << std::endl;
        }
    } else {
        std::cout << "---No end Device vacant---" << std::endl;
    }

    std::cout << "Enter token value: ";
    int token;
    std::cin >> token;

    std::cout << "Enter Sender Device no: ";
    int num1;
    std::cin >> num1;

    token_passing(token, num1);

    std::cout << "Enter receiver Device no: ";
    int num2;
    std::cin >> num2;

    std::cout << "Enter message: ";
    std::string num3;
    std::cin.ignore(); // Ignore the newline character from previous input
    std::getline(std::cin, num3);

    std::cout << "Choose the flow control protocol" << std::endl;
    std::cout << "1. STOP AND WAIT ARQ" << std::endl;
    std::cout << "2. SELECTIVE REPEAT" << std::endl;
    int num5;
    std::cin >> num5;

    if (num5 == 1) {
        stop_and_wait_arq_HUb(num1, num2, num3);
    } else {
        Selective_Repeat_Hub(num1, num2, num3);
    }

    return ;
}

void accessFlowSwitch()
{
    if (Switch1.Switch_vacant() == 0 && End_Device_Vacant() == 0) {
    std::cout << "-----------CONNECTING TO SWITCH------------" << std::endl;
    for (int i = 1; i <= 5; i++) {
        std::cout << "End Device " << i << " Connected to Switch" << std::endl;
    }

    std::cout << "Enter token value: ";
    int token;
    std::cin >> token;

    std::cout << "Enter Sender Device no: ";
    int num1;
    std::cin >> num1;

    token_passing(token, num1);

    std::cout << "Enter receiver Device no: ";
    int num2;
    std::cin >> num2;

    std::cout << "Enter message: ";
    std::string num3;
    std::cin.ignore(); // Ignore the newline character from previous input
    std::getline(std::cin, num3);

    if (num2 != num1) {
        std::cout << "Choose the flow control protocol" << std::endl;
        std::cout << "1. STOP AND WAIT ARQ" << std::endl;
        std::cout << "2. SELECTIVE REPEAT" << std::endl;
        int num5;
        std::cin >> num5;

        if (num5 == 1) {
            stop_and_wait_arq(num1, num2, num3);
        } else {
            Selective_Repeat(num1, num2, num3);
        }
    } else {
        std::cout << "Enter valid number. No communication possible!" << std::endl;
    }
}
    return ;
}

void routerStart()
{
    if (Switch1.Switch_vacant() == 0 && Switch2.Switch_vacant() == 0) {
        std::cout << "Connection made between --Switch1------Router------Switch2--" << std::endl;
        Switch1.port1 = 1;
        Switch2.port1 = 1;
    }

    if (End_Device_Vacant() == 0 || Switch1.Switch_vacant() == 0) {
        std::cout << "......................SWITCH 1  CONNECTING......................." << std::endl;
        std::cout << "Connection made between Switch1 and End Device 1" << std::endl;
        e1.port = 1;
        Switch1.port1 = 9;

        if (Hub1.ports[1] == 0 && Hub1.ports[2] == 0 && Hub1.ports[3] == 0 && Hub1.ports[4] == 0) {
            std::cout << "Connection made between Switch1 and End Device 2" << std::endl;
            e2.port = 7;
        } else {
            std::cout << "No Port vacant in SWITCH" << std::endl;
        }
    } else {
        std::cout << "---No end device vacant---" << std::endl;
    }

    if (End_Device_Vacant() != 0 || Switch2.Switch_vacant() == 0) {
        std::cout << "......................SWITCH 2  CONNECTING......................." << std::endl;
        std::cout << "Connection made between SWITCH 2 and End Device 3" << std::endl;
        e3.port = 1;
        Switch2.port1 = 9;

        if (Hub2.ports[1] == 0 && Hub2.ports[2] == 0 && Hub2.ports[3] == 0 && Hub2.ports[4] == 0) {
            std::cout << "Connection made between SWITCH 2 and End Device 4" << std::endl;
            e4.port = 7;
        } else {
            std::cout << "No Port vacant in SWITCH" << std::endl;
        }
    } else {
        std::cout << "error" << std::endl;
    }

    for (int i = 0; i < 4; i++) {
        std::cout << "Enter IP Address of End Device " << i + 1 << ": ";
        std::string user;
        std::cin >> user;
        endDevices[i + 1].ip = user;

        std::cout << "Enter Network Prefix Length of device " << i + 1 << ": ";
        int prefixLength;
        std::cin >> prefixLength;
        endDevices[i + 1].subnet = prefixLength;

        std::cout << "Enter Default gateway of device " << i + 1 << ": ";
        std::cin >> user;
        endDevices[i + 1].gateway = user;
    }

    if (get_nid(endDevices[1].ip, endDevices[1].subnet) != get_nid(endDevices[2].ip, endDevices[2].subnet) ||
        get_nid(endDevices[3].ip, endDevices[3].subnet) != get_nid(endDevices[4].ip, endDevices[4].subnet)) {
        std::cout << "Enter valid IP addresses" << std::endl;
    }

    Router1.user_executive_mode();
    ping(1, 4);
    return;
}

void rouRIP(){
     if (Switch1.Switch_vacant() == 0 && Switch2.Switch_vacant() == 0) {
        cout << "Connection made between --Switch1------Router1----Router2------Switch2-- " << endl;
        cout << "Connection made between ---Router1----Router3------Router2----- " << endl;
        cout << "   E1                                E3   \n"
                "    |                                |    \n"
                "   S1---------R1 - - - - -R2---------S2   \n"
                "    |           -        -           |    \n"
                "   E2             -    -             E4   \n"
                "                    R3                    \n" << endl;

        Switch1.port1 = 1;
        Switch2.port1 = 1;
    }

    if (End_Device_Vacant() == 0 || Switch1.Switch_vacant() == 0) {
        cout << "......................SWITCH 1  CONNECTING......................." << endl;

        cout << "Connection made between Switch1 and End Device 1" << endl;
        e1.port = 1;
        Switch2.port1 = 9;

        if (Hub1.ports[1]== 0 && Hub1.ports[2] == 0 && Hub1.ports[3] == 0 && Hub1.ports[4] == 0) {
            cout << "Connection made between Switch1 and End Device 2" << endl;
            e2.port = 7;
        } else {
            cout << "No Port vacant in SWITCH" << endl;
        }
    } else {
        cout << "---No end device vacant---" << endl;
    }

    if (End_Device_Vacant() != 0 || Switch2.Switch_vacant() == 0) {
        cout << "......................SWITCH 2  CONNECTING......................." << endl;
        cout << "Connection made between SWITCH 2 and End Device 3" << endl;
        e3.port = 1;
        Switch2.port1 = 9;

        if (Hub2.ports[1] == 0 && Hub2.ports[2] == 0 && Hub2.ports[3] == 0 && Hub2.ports[4] == 0) {
            cout << "Connection made between SWITCH 2 and End Device 4" << endl;
            e4.port = 7;
        } else {
            cout << "No Port vacant in SWITCH" << endl;
        }
    } else {
        cout << "error" << endl;
    }

    for (int i = 0; i < 4; i++) {
        cout << "Enter IP Address of End Device " << i + 1 << ": ";
        string user;
        cin >> user;
        endDevices[i + 1].ip = user;

        cout << "Enter Network Prefix Length of device " << i + 1 << ": ";
        int prefix;
        cin >> prefix;
        endDevices[i + 1].subnet = prefix;

        cout << "Enter Default gateway of device " << i + 1 << ": ";
        cin >> user;
        endDevices[i + 1].gateway = user;
    }

    if (get_nid(endDevices[1].ip, endDevices[1].subnet) != get_nid(endDevices[2].ip, endDevices[2].subnet) ||
        get_nid(endDevices[3].ip, endDevices[3].subnet) != get_nid(endDevices[4].ip, endDevices[4].subnet)) {
        cout << "Enter valid IP addresses" << endl;
    }

    Router1.R_table.clear();
    vector<string> list1 = {"10.0.0.0", "24", "10.0.0.3", "", "1"};
    Router1.R_table.push_back(list1);
    vector<string> list2 = {"20.0.0.0", "24", "20.0.0.2", "", "5"};
    Router1.R_table.push_back(list2);
    vector<string> list3 = {"30.0.0.0", "23", "30.0.0.1", "", "1"};
    Router1.R_table.push_back(list3);
    vector<string> list4 = {"40.0.0.0", "22", "40.0.0.1", "", "1"};
    Router1.R_table.push_back(list4);
    vector<string> list5 = {"50.0.0.0", "22", "30.0.0.1", "", "5"};
    Router1.R_table.push_back(list5);

    Router2.R_table.clear();
    vector<string> list6 = {"10.0.0.0", "24", "30.0.0.2", "", "5"};
    Router2.R_table.push_back(list6);
    vector<string> list7 = {"20.0.0.0", "24", "20.0.0.3", "", "1"};
    Router2.R_table.push_back(list7);
    vector<string> list8 = {"30.0.0.0", "23", "30.0.0.2", "", "1"};
    Router2.R_table.push_back(list8);
    vector<string> list9 = {"50.0.0.0", "22", "50.0.0.1", "", "1"};
    Router2.R_table.push_back(list9);
    vector<string> list12 = {"40.0.0.0", "22", "40.0.0.2", "", "5"};
    Router2.R_table.push_back(list12);

    Router3.R_table.clear();
    vector<string> list10 = {"10.0.0.0", "24", "10.0.0.2", "", "5"};
    Router3.R_table.push_back(list10);
    vector<string> list11 = {"20.0.0.0", "24", "20.0.0.3", "", "1"};
    Router3.R_table.push_back(list11);
    vector<string> list13 = {"30.0.0.0", "23", "30.0.0.2", "", "1"};
    Router3.R_table.push_back(list13);
    vector<string> list14 = {"40.0.0.0", "22", "40.0.0.2", "", "1"};
    Router3.R_table.push_back(list14);
    vector<string> list15 = {"50.0.0.0", "22", "50.0.0.1", "", "5"};
    Router3.R_table.push_back(list15);

    Router1.user_executive_mode();
    Router2.user_executive_mode();
    Router3.user_executive_mode();
    // int e1port = find_port(Router1.R_table, endDevices[1].gateway);
    // int e2port = find_port(Router1.R_table, endDevices[2].gateway);
    // int e3port = find_port(Router2.R_table, endDevices[3].gateway);
    // int e4port = find_port(Router2.R_table, endDevices[4].gateway);

    // Hub1.ports[0] = e1port;
    // Hub1.ports[5] = e2port;
    // Hub2.ports[0] = e3port;
    // Hub2.ports[5] = e4port;

    // cout << "IP address of End Device 1: " << endDevices[1].ip << endl;
    // cout << "NID of End Device 1: " << get_nid(endDevices[1].ip, endDevices[1].subnet) << endl;
    // cout << "Default Gateway of End Device 1: " << endDevices[1].gateway << endl;
    // cout << "Connected Port on Router 1: " << e1port << endl;
    // cout << endl;

    // cout << "IP address of End Device 2: " << endDevices[2].ip << endl;
    // cout << "NID of End Device 2: " << get_nid(endDevices[2].ip, endDevices[2].subnet) << endl;
    // cout << "Default Gateway of End Device 2: " << endDevices[2].gateway << endl;
    // cout << "Connected Port on Router 1: " << e2port << endl;
    // cout << endl;

    // cout << "IP address of End Device 3: " << endDevices[3].ip << endl;
    // cout << "NID of End Device 3: " << get_nid(endDevices[3].ip, endDevices[3].subnet) << endl;
    // cout << "Default Gateway of End Device 3: " << endDevices[3].gateway << endl;
    // cout << "Connected Port on Router 2: " << e3port << endl;
    // cout << endl;

    // cout << "IP address of End Device 4: " << endDevices[4].ip << endl;
    // cout << "NID of End Device 4: " << get_nid(endDevices[4].ip, endDevices[4].subnet) << endl;
    // cout << "Default Gateway of End Device 4: " << endDevices[4].gateway << endl;
    // cout << "Connected Port on Router 2: " << e4port << endl;
    // cout << endl;
    ping(1,4);
    RIP();
    return;
}

void transportLayer() {
        cout << "Enter the respective number for the transport layer protocols" << endl;
        cout << "1. UDP" << endl;
        cout << "2. TCP" << endl;
        int x;
        cin >> x;

        if (x == 1) {
            cout << "Enter the Name of the Server: ";
            string n;
            cin >> n;

            cout << "Enter the port no of the server you want to communicate: ";
            int p;
            cin >> p;

            cout << "Enter the IP address of the server: ";
            string i;
            cin >> i;

            cout << "Enter the Device from which you want to communicate: ";
            int e;
            cin >> e;

            cout << "Enter the Message: ";
            string m;
            cin.ignore(); // Ignore newline character left in the buffer
            getline(cin, m);

            udp(n, p, i, e, m);
        } else if(x==2) {
            cout << "Enter the Name of the Server: ";
            string n;
            cin >> n;

            cout << "Enter the port no of the server you want to communicate: ";
            int p;
            cin >> p;

            cout << "Enter the IP address of the server: ";
            string i;
            cin >> i;

            cout << "Enter the Device from which you want to communicate: ";
            int e;
            cin >> e;

            cout << "Enter the Message: ";
            string m;
            cin.ignore(); // Ignore newline character left in the buffer
            getline(cin, m);

            tcp(n, p, i, e, m);
        }
        else
        {
            cout<<"Enter a valid option"<<endl;
        }
    return;
}

void configureRouter() {
    cout << "Configuring the router" << endl;
    Router1.user_executive_mode();
}


void applicationLayer() {
    cout << "Press the following number for the protocols" << endl;
    cout << "1. DHCP" << endl;
    cout << "2. HTTP, FTP, SSH and DNS "<< endl;

    int x;
    cin >> x;

    if (x == 1) {
        if (End_Device_Vacant() == 0) {
            cout << "-----------CONNECTING TO ROUTER------------" << endl;
            for (int i = 1; i < 4; i++) {
                cout << "End Device " << i << " Connected to Router on Interface 1" << endl;
            }
            for (int i = 4; i < 7; i++) {
                cout << "End Device " << i << " Connected to Router on Interface 2" << endl;
            }

            cout << "            E3                           E4           \n"
                 << "                -                    -                \n"
                 << "      E1- - - - - - S1----R1-----S2 - - - - - -E5     \n"
                 << "                -                    -                \n"
                 << "            E2                           E6           \n"
                 << "                                                      \n"
                 << endl;

            configureRouter();

            for (int i = 1; i < 7; i++) {
                cout << "For End Device " << i << " ";
                DHCP(i);
            }
        } else {
            cout << "Enter a valid number. No communication possible!" << endl;
        }
    } else {
        appLayer();
    }
    return;
}


int main() {
    cout << "Following Simulations can be carried out. Enter the respective number of the simulation:" << endl;
    cout << "1. Dedicated Link" << endl;
    cout << "2. Simulation through Hub (Star Topology)" << endl;
    cout << "3. Simulation through Switch (Address Learning)" << endl;
    cout << "4. Complete Simulation - Implementing Access and Flow Control Protocols" << endl;
    cout << "5. Switch and 5 End Devices" << endl;
    cout << "6. TL" << endl;
    cout << "7. AL" << endl;
    int num;
    cin >> num;
    switch (num) {
        case 1:
            establishDedicatedLink(e1, e2);
            break;
        case 2:
            establishHubTopology(e1, Hub1, e2, e3, e4, e5);
            break;
        case 3:
            addLearning();
            break;
        case 4:
            accessFlow();
            break;
        case 5:
            accessFlowSwitch();
            break;
        case 6:
            transportLayer();
            break;
        case 7:
            applicationLayer();
            break;
        default:
            cout << "Invalid simulation number" << endl;
            break;
    }
    return 0;
}

