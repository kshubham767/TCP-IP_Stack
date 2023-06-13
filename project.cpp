#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

class EndDevice {
public:
    string ip;
    string mac;
    int port;
    string data;
    int seq_no;
    string subnet;
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
            subnet = "";
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
    int port1;
    int port2;
    int port3;
    int port4;
    int port5;
    int port6;

    Hub() : port1(0), port2(0), port3(0), port4(0), port5(0), port6(0) {}

    int Hub_vacant() {
         vector<int> plist = {port1, port2, port3, port4, port5, port6};
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

     vector<int> maclist1 = {0, 0, 0, 0, 0};
     vector<int> maclist2 = {0, 0, 0, 0, 0};
};

Switch Switch1;
Switch Switch2;

class Router {
public:
    static vector<string> R_table;
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
    void user_executive_mode() {
        cout << "User Executive mode" << endl;
        string user;
        cin >> user;
        if (user == "en" || user == "enable") {
            privilegde_mode();
        }

        cin >> user;
        if (user == "ex") {
            return;
        }
    }

    void privilegde_mode() {
        cout << "Priviledge mode" << endl;
        while (true) {
            string user;
            cin >> user;
            if (user == "ex" || user == "exit") {
                cout << "User Executive Mode" << endl;
                break;
            } else if (user == "conf t" || user == "configure terminal") {
                global_conf();
            } else if (user == "write memory") {
                cout << "Settings Saved" << endl;
            } else if (user == "showip route") {
                R_table;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    }

    void global_conf() {
        while (true) {
            cout << "Global Configuration Mode" << endl;
            string user;
            cin >> user;
            if (user == "ex" || user == "exit") {
                cout << "Privilege Mode" << endl;
                return;
            } else if (user == "int 1") {
                Interface1();
            } else if (user == "int 2") {
                Interface2();
            } else if (user == "int 3") {
                Interface3();
            } else if (user == "iproute 0.0.0.0 0.0.0.0 ipaddress main router") {
                R_table;
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

    void Interface1() {
        while (true) {
            string user;
            cin >> user;
            if (user == "ip address") {
                cout << "Enter Ip address" << endl;
                string user1;
                cin >> user1;
                interface1.push_back(user1);
                cout << "Enter Network bits" << endl;
                string user2;
                cin >> user2;
                interface1.push_back(user2);
                // Assigning IP
            } else if (user == "noshutdown") {
                cout << "No shutdown" << endl;
            } else if (user == "ex") {
                return;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    }

    void Interface2() {
        while (true) {
            string user;
            cin >> user;
            if (user == "ip address") {
                cout << "Enter Ip address" << endl;
                string user1;
                cin >> user1;
                interface2.push_back(user1);
                cout << "Enter Network bits" << endl;
                string user2;
                cin >> user2;
                interface2.push_back(user2);
                // Assigning IP
            } else if (user == "noshutdown") {
                cout << "No shutdown" << endl;
            } else if (user == "ex") {
                global_conf();
                break;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    }

    void Interface3() {
        while (true) {
            string user;
            cin >> user;
            if (user == "ip address") {
                cout << "Enter Ip address" << endl;
                string user1;
                cin >> user1;
                interface3.push_back(user1);
                cout << "Enter Network bits" << endl;
                string user2;
                cin >> user2;
                interface3.push_back(user2);
                // Assigning IP
            } else if (user == "noshutdown") {
                cout << "No shutdown" << endl;
            } else if (user == "ex") {
                global_conf();
                break;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    }

};

Router Router1;
Router Router2;
Router Router3;


/*-------------------------------------------------SERVER----------------------------------------------------*/
class Server {
public:
    string name;
    int port;
    int seq_no;
    string ip;
    string mac;
    string message;

    Server(string n, int p, int s, string ip)
        : name(n), port(p), seq_no(s), ip(ip) {
        EndDevice endDevice(ip, p, "", s);
        mac = endDevice.Generate_mac_address();
        message = "";
    }
};

Server HTTP("http", 80, 1, "10.0.0.6");
Server SSH("ssh", 22, 2, "20.0.0.6");
Server SMTP("smtp", 25, 3, "30.0.0.6");

vector<Server> s_list = {HTTP, SSH, SMTP};

void messtrf(string message, EndDevice endD, Server& server) {
    server.message = message;
}

/*-----------------------------------------------UDP--------------------------------------------------------*/

void udp(string n, int p, string ip,EndDevice e, string m) {
    for (Server i : s_list) {
        if (n == i.name) {
            if (ip == i.ip && p == i.port) {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> dis(0, 10);
                int x = dis(gen);

                if (x >= 8) {
                    messtrf("Your message", e, i);
                    cout << i.message << endl;
                    return;
                } else {
                    cout << "Packet got dropped because of the unreliability of UDP" << endl;
                    return;
                }
            } else {
                cout << "Port or IP does not match" << endl;
                return;
            }
        }
    }
    cout << "Invalid Server!" << endl;
}

/*-----------------------------------------------TCP--------------------------------------------------------*/

void tcp(string n, int p, string ip, EndDevice e, string m) {
    for (Server server : s_list) {
        if (n == server.name) {
            if (ip == server.ip && p == server.port) {
                string buffer = m;
                messtrf(buffer, e, server);
                cout << server.message << endl;
                return;
            } else {
                cout << "Port or IP does not match." << endl;
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

/*---------------------------------------------PING--------------------------------------------------------*/


int main() {
    e1.display();
    cout<<Router1.max_conf;
    cout<<get_nid("192.168.0.10",25);
    return 0;
}

