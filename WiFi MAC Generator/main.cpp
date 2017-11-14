// Kai Brooks
// github.com/kaibrooks
// This program will generate a random MAC Address and initialize it through OSX Terminal

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>

using namespace std;

void help();
string generate_macaddr();
void cycle();

const string currentDateTime() {    // Used to generate date and time for logs
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct); // If date is necessary, "%Y-%m-%d %X" instead of "%X"
    return buf;
}

int main ()
{
    // Declare variables
    string userInput;   // User input in the menu
    string sysCommand;  // The entire command that will be sent to OSX to run
    bool autorun = 0;   // Should the program autorun the MAC generator and refresher
    //char autorunInput;  // The key to break the autorun loop
    
    
    //char macbuf[20];
    //int o[6];
    string pw;
    
    srand(time_t(NULL)); // Generate random seed
    
    // Begin
    cout << endl << "Random MAC Address generator for OSX" << endl;
    cout << "Press [Enter] for a new MAC." << endl;
    cout << "Type CYCLE to turn Airport off and back on again." << endl;
    cout << "Type AUTO to generate a MAC and cycle the airport every hour" << endl;
    cout << "Type HELP for instructions." << endl;
    cout << "--------------------------------------------------------" << endl;
    
    
    // Keep looping until program exit
    while (true) {
        sysCommand = "sudo ifconfig en0 ether "; // Reset the system command to be empty
        sysCommand += generate_macaddr(); // Add the generated MAC address to the end of the system command
        
        // Ask for input, user hits enter for a new MAC
        getline(cin, userInput);
        
        if (userInput=="HELP" or userInput=="help" or userInput=="h") {
            help();
            continue;
        }
        if (userInput=="EXIT" or userInput=="exit" or userInput=="e") {
            return 0;
        }
        if (userInput=="CYCLE" or userInput=="cycle" or userInput=="c") {
            cycle();
            continue;
        }
        if (userInput =="AUTO" or userInput=="auto" or userInput=="a") {
            cout << "[Autorun enabled, script will cycle every 60 minutes. Close program to stop.]" << endl;
            autorun = 1;
            while (autorun == 1) {
                cout << currentDateTime() << " [Autorun] " << sysCommand << endl; // Output the command sent to OSX
                
                //system(sysCommand.c_str()); // Run the system command to overwrite the MAC
                //system("networksetup -setairportpower en0 off; networksetup -setairportpower en0 on"); // Toggle airport
                
                sleep(3600);                // Wait 60 minutes (3600 seconds)
                cout << flush;           // Flush the output buffer
                
                sysCommand = "sudo ifconfig en0 ether "; // Reset the system command to be empty
                sysCommand += generate_macaddr(); // Add the generated MAC address to the end of the system command
            }
            
            
        }
        
        
        //system(sysCommand.c_str()); // Run the system command to overwrite the MAC
        //system("networksetup -setairportpower en0 off; networksetup -setairportpower en0 on"); // Turn the airport off and on
        
        cout << currentDateTime() << " " << sysCommand; // Output the current time and the command that's sent to OSX
        
        
        
    }
}


string generate_macaddr() {
    char macbuf[20];
    int o[6];
    o[0] = 2;           // Locally administered address
    for (int i = 1; i < 6; i++) o[i] = rand()%16;
    sprintf(macbuf, "%02x:%02x:%02x:%02x:%02x:%02x", o[0], o[1], o[2], o[3], o[4], o[5]);
    return macbuf;
} // Generate a random MAC address only

void help() {
    cout << "--------------------------------------------------------" << endl;
    cout << "HELP AND INSTRUCTIONS" << endl;
    cout << "" << endl;
    cout << "1) Copy the entire generated line into a new terminal window. Enter your password if asked." << endl;
    cout << "2) Cycle (turn off and back on) Airport. Type CYCLE to run it for you."<< endl;
    cout << "--------------------------------------------------------" << endl;
}       // Text for the help menu

void cycle() {
    system("networksetup -setairportpower en0 off; networksetup -setairportpower en0 on");
    cout << "[Airport power cycled]";
}       // Run the airport cycling


