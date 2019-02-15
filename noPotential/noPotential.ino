const int dirPin = 7; 
const int stepPin = 6; 
const int sleepPin = 18;
const int button1Pin = 2;
const int button2Pin = 3;
const int forward = 4;
const int back = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(stepPin, OUTPUT);   
  pinMode(dirPin, OUTPUT);
  pinMode(forward, OUTPUT);   
  pinMode(back, OUTPUT);
  start();
}

void loop() {
  // put your main code here, to run repeatedly:
  //we should start this loop needing to step backward, so start going backward until you hit button1
  while(digitalRead(button1Pin) == LOW) {
    step_backward();
  }
  //now we need to step forward, go forward until you hit button2
  while(digitalRead(button2Pin) == LOW) {
    step_forward();
  }
}

void start() {
  // Steps forward until button2 is pressed, which would indicate you need to step backward. 
  while(digitalRead(button2Pin) == LOW) {
    step_forward();
  }
}

void step_forward() {
  Serial.println("stepping forward");
  digitalWrite(forward,HIGH);
  digitalWrite(back, LOW);
  /*
  digitalWrite(dirPin, LOW);              
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(500);
  */
}

void step_backward() {
  Serial.println("stepping backward");
  digitalWrite(back, HIGH);
  digitalWrite(forward, LOW);
  /*
  digitalWrite(dirPin, HIGH);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin, LOW);
  */
}
