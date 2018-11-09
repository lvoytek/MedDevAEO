void web_talk_to_clients()
{
	const char* host = "recovery-helper.firebaseio.com";//"firebasestorage.googleapis.com";//"recovery-helper.firebaseio.com";//"firebasestorage.googleapis.com";//"docs-examples.firebaseio.com";//"csb.stanford.edu";
	WiFiClient client;
	const int httpPort = 443;
	client.stop(); 
	client.flush();
	if (!client.connectSSL(host, httpPort)) 
	{
		Serial.println("connection failed");
		delay(1000);
		//return;
	}
	else
	{
		Serial.println("connection successful");
	}

	int flag = 1000;
	Serial.println("Here we go");
	
	//while(client.available()){
	if (client.connectSSL(host, 443)) 
	{ 
		String toSend = "PUT /patients/fGB7g1BNAlU0si9ohBouN03QcGz1.json ";
		toSend += "HTTP/1.1\r\n"; 
		toSend += "Host: "; 
		toSend += host; 
		toSend += "\r\n" ; 
		toSend += "Content-Type: application/json\r\n"; 
		String payload = "{\r\n\"email\": \""; 
		payload += "mario@email.com";
		payload += "\"";
		payload += ","; 
		payload += "\r\n\"exerciseToday\": \""; 
		payload += "true\""; 
		payload += ","; 
		payload += "\r\n\"reps\": \""; 
		payload += String(ExerciseReps); 
		payload += "\"";
		payload += ","; 
		payload += "\r\n\"start\": \""; 
		payload += "false\"";
		payload += ","; 
		payload += "\r\n\"targetExtension\": \""; 
		payload += String(TargetExtend); 
		payload += "\"";
		payload += ","; 
		payload += "\r\n\"targetFlex\": \""; 
		payload += String(TargetFlex); 
		payload += "\"";
		payload += ","; 
		payload += "\r\n\"angleFeedback\": \""; 
		payload += String(FeedbackAngle); 
		payload += "\"\r\n"; 
		payload += "}";
		toSend += "Content-Length: " + String(payload.length()) + "\r\n"; 
		toSend += "\r\n"; 
		toSend += payload; 
		Serial.println(toSend);
		int result = client.println(toSend); 
		Serial.print(result);
		client.println(); 
		client.flush(); 
		client.stop(); 
		Serial.println("Done");
	} 

	//No connection
	else 
	{ 
		Serial.print("client not available");
		client.flush(); 
		client.stop();  
	} 

	client.flush(); 
	client.stop(); 
}

