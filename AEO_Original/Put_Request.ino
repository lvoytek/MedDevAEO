 void web_talk_to_clients() {
  // listen for incoming clients
  // http://www.shpeua.org/presidents-message.html
  //http://csb.stanford.edu/class/public/pages/sykes_webdesign/05_simple.html
  //recovery-helper.firebaseio.com/recovery-helper/patients/6ljQvxJ5ych3a7Wh1y4IHSWStpK2/email
  //https://recovery-helper.firebaseio.com/
  //https://console.firebase.google.com/project/recovery-helper/database/data/
  //https://firebasestorage.googleapis.com/v0/b/recovery-helper.appspot.com/o/recovery-helper-export.json
  //gs://recovery-helper.appspot.com/recovery-helper-export.json
  //https://recovery-helper.firebaseio.com/.json?print=pretty&format=export&download=recovery-helper-export.json&auth=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE0OTIwNDk2MDksImV4cCI6MTQ5MjA1MzIwOSwiYWRtaW4iOnRydWUsInYiOjB9.96fv9z5Qkva_AghguY6uHbiNcNMrg0632J9Iif0jqgI
  const char* host = "recovery-helper.firebaseio.com";//"firebasestorage.googleapis.com";//"recovery-helper.firebaseio.com";//"firebasestorage.googleapis.com";//"docs-examples.firebaseio.com";//"csb.stanford.edu";
  WiFiClient client;
  const int httpPort = 443;
  client.stop(); 
  client.flush();
  if (!client.connectSSL(host, httpPort)) {
    Serial.println("connection failed");
    delay(1000);
    //return;
  }
  else{
    Serial.println("connection successful");
  }

  int flag = 1000;
  Serial.println("Here we go");
  //while(client.available()){
  if (client.connectSSL(host, 443)) { 
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
   //return true; 
 } else { 
   // if you couldn't make a connection: 
   Serial.print("client not available");
   client.flush(); 
   client.stop(); 
   //return false; 
 } 
 
  client.flush(); 
  client.stop(); 
}


