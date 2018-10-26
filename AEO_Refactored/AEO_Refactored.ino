#include <SPI.h>
#include <WiFi101.h>

//Here are the wifi details first WiFi network name and then password 
const PROGMEM char ssid[] = "AndroidAP";
const PROGMEM char pass[] = "Password123";
const PROGMEM int keyIndex = 0; // your network key Index number (needed only for WEP)

//create status flags
int status = WL_IDLE_STATUS;
int status2 = 0; //this flag was for trouble shooting using WiFi.status();
int counter = 0;
int loopCounter = 0;
int loopCounter2 = 0;

//Here are the variables that will be used to parse the lines of the firebase database
//First the strings are set to the lines of interest in the database
//Then later the strings will be manipulated to find the target angles, number of reps, and start flag
String StartString = "true";
String Start = "true";
String ExerciseRepsString = "3";
int ExerciseReps = 3;
String TargetExtendString = "0";
int TargetExtend = 0;
String TargetFlexString = "91";
int TargetFlex = 91;
String ExerciseTodayString = "";

// local port {aka your port to the internet..}
// WiFiServer server(80);
//Set the WiFi port
WiFiServer server(443); //

//function to listen for incoming clients. This function will be called in loop();
void web_listen_for_clients()
{
	Serial.println("Web listen is working");
	delay(15000);
	// listen for incoming clients
	// http://www.shpeua.org/presidents-message.html
	//http://csb.stanford.edu/class/public/pages/sykes_webdesign/05_simple.html
	//recovery-helper.firebaseio.com/recovery-helper/patients/6ljQvxJ5ych3a7Wh1y4IHSWStpK2/email
	//https://recovery-helper.firebaseio.com/
	//https://console.firebase.google.com/project/recovery-helper/database/data/
	//https://firebasestorage.googleapis.com/v0/b/recovery-helper.appspot.com/o/recovery-helper-export.json
	//gs://recovery-helper.appspot.com/recovery-helper-export.json
	//https://recovery-helper.firebaseio.com/.json?print=pretty&format=export&download=recovery-helper-export.json&auth=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE0OTIwNDk2MDksImV4cCI6MTQ5MjA1MzIwOSwiYWRtaW4iOnRydWUsInYiOjB9.96fv9z5Qkva_AghguY6uHbiNcNMrg0632J9Iif0jqgI
	//establish client
	WiFiClient client;
	//set host and http port. The host will be the firebase database with patient info
	const char* host = "recovery-helper.firebaseio.com";//"firebasestorage.googleapis.com";//"recovery-helper.firebaseio.com";//"firebasestorage.googleapis.com";//"docs-examples.firebaseio.com";//"csb.stanford.edu";
	const int httpPort = 443;
	//const int httpPort = 80;
	int num_bytes = 0; // used for troubleshooting
	delay(1000);
	//client.stop();//stop the connection if one is already made
	delay(1000);	 
	client.flush();//wait for the client to stop sending new bytes before proceeding
	
	read_angle();
	delay(1000);	 
 
 	//check to see if client is connected
	if (!client.connectSSL(host, httpPort)) 
	{
		Serial.println("connection failed");//if not, flush and stop, then try to recconnect to wifi
		client.flush();
		client.stop(); 
		status = WiFi.begin(ssid, pass);
		Serial.print("Status is: ");
		Serial.println(status);
		printWifiStatus();
		delay(3000);
		int PingResult = WiFi.ping("www.google.com"); 
		Serial.println(PingResult);
		
		//try to reconnect to wifi if the ping result gives an error code
		if (PingResult < 0) 
		{
			//server.end();
			WiFi.disconnect();
			delay(3000);
			setup_wifi();
		}
		return;
	}
	else
	{
		Serial.println("connection successful");//if client connection is successful, proceed
		delay(5000);
	}

	String url = "/patients/fGB7g1BNAlU0si9ohBouN03QcGz1.json?print=pretty"; //set the url and branch of patient information to read
	client.println(String("GET ") + url + " HTTP/1.1"); //sometimes HTTPS/1.1 // make Get http request
	client.println("Host: " + String(host));
	client.println("Connection: close");
	client.println();
	

	int counter = 0;

	//delay(1000);
	//Serial.println("Response:");
	//String json = "";
	delay(5000);
	
	num_bytes = client.available();
	//Serial.print("Number of bytes	= ");
	//Serial.println(num_bytes);
	
 
	int flag = 1000;
	String line = "";
	
	//collect response from client
	while((num_bytes = client.available()))
	{
		//Serial.print("Number of bytes	= ");
		//Serial.println(num_bytes);
		//String line = client.readStringUntil('\n');
		line = client.readStringUntil('\n'); 
		counter = counter + 1;
		//Serial.println("Line number: ");//These three lines used for parsing testing
		//Serial.println(counter);
		//Serial.println(line);
		if (line.substring(12) == "\"mario@email.com\","){//set user. Used for parsing database. check to see if the line is the correct user
			Serial.println("HERE IT IS!");
			flag = counter + 1;
			//Serial.println(line);
		} else {
			//Serial.println(line);
		}//The next few statements collect the strings that will be manipulated
		if (counter == flag) {
			//Serial.println(line);
			ExerciseTodayString = line;
		}
		if (counter == flag+1) {
			//Serial.println(line);
			ExerciseRepsString = line;
		}
		if (counter == flag+2) {
			//Serial.println(line);
			StartString = line;
		}
		if (counter == flag+3) {
			//Serial.println(line);
			TargetExtendString = line;
		}
		if (counter == flag+4) {
			//Serial.println(line);
			TargetFlexString = line;
		}
		delay(1500);
		Serial.println(line);
		Serial.println("																																																");
		}

	counter = 0;
	delay(1000);
	client.flush();
	delay(1000);
	client.stop();
	delay(1000);
	//stop and flush before starting the motor
	start_motor();
}
	

void setup_wifi(){
	//Initialize serial and wait for port to open:

	//Serial.println(WL_PING_UNKNOWN_HOST);
	// attempt to connect to Wifi network:
	while ( status != WL_CONNECTED) {
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);
		// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
		status = WiFi.begin(ssid, pass);
		//Serial.print("Status is: ");
		//Serial.println(status);
		status2 = WiFi.status();
		Serial.print("Status2 is: ");
		Serial.println(status2);
		if (status2 == WL_CONNECTED) {
			Serial.println("it is connected");
		}
		else if (status2 == WL_IDLE_STATUS){
			Serial.println("Idle");
		}
		else if (status2 == WL_CONNECTION_LOST){
			Serial.println("Connection Lost");
		}
		else if (status2 == WL_CONNECT_FAILED){
			Serial.println("Connection Failed");
		}
		
		else if (status2 == WL_DISCONNECTED){
			Serial.println("Disconnected");
		}
		else{
			Serial.println("I dont know what this is");
		}
		// wait 10 seconds for connection:
		delay(10000);
	}
	server.begin();
	
	// you're connected now, so print out the status:
	printWifiStatus();
}

void printWifiStatus() {
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.print(rssi);
	Serial.println(" dBm");
	int PingResult = WiFi.ping("www.google.com"); 
	Serial.println(PingResult);
	status = WiFi.begin(ssid, pass);
	//Serial.print("Status is: ");
	//Serial.println(status);
	//if (PingResult < 0) {
			//server.end();
		//	WiFi.disconnect();
			//delay(3000);
			//setup_wifi();
		//}
	
}

void setup()
{
	Serial.begin(9600);
	//setup_wifi();
	setup_motor();	
}

void loop() 
{
	for(int deg = 0; deg < 90; deg++){
		for (loopCounter = 0; loopCounter < 500; loopCounter++){
			Serial.println(loopCounter);
			step_backward();
		}
	}
	delay(4000);
	
	for(int deg = 0; deg < 90; deg++){
		for (loopCounter = 0; loopCounter < 500; loopCounter++){
			Serial.println(loopCounter);
			step_forward();
		}
	}
	delay(4000);
}

