// Defining functions to be shared across files

// Initial Module Configuration:
void setupModule();

void powerOn();

void standBy();

void configure();


// Functions to be executed indefinitely in loops:
void userInput();

void listener();

void sendCommand(String at, unsigned int duration);

void showSerialData();


// Functions for Making Calls and Sending Messages:

void makeCall(String pos);

void startTimer(String pos);

void sendMessage(String number, String pos);

// Function to Connect to the Network:

void sendDataToCloud(String pos, String duration);
