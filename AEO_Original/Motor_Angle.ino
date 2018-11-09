const PROGMEM int SensorPin = A0; 
const PROGMEM int dirPin = 7;	//stepper motor //PIN ASSIGNMENTS! 
const PROGMEM int stepPin = 6; 
const PROGMEM int sleepPin = 18;
int SensorValue = 0;
double SensorVoltage = 0;
double AngleValueFloat = 0;
int AngleValue = 0;
const PROGMEM int AngleCorrectionFactor = 4;
float AdditionalAngleCorrector = 0;
//int MaxExtensionAngle = 999;
//int MaxAngle = 0;
int FeedbackAngle = 0;
int ExtensionHitCounter = 0;
int FlexionHitCounter = 0;
//	AngleValue = (R1 * SensorVoltage) / ((Vin * (Resistance2 - Resistance1) / (Angle2 - Angle1))	- (SensorVoltage * (Resistance2 - Resistance1) / (Angle2 - Angle1)));
const PROGMEM float R1 = 11470;
const PROGMEM float Angle1 = 0;
const PROGMEM float Angle2 = 90;//52
const PROGMEM float Resistance1 = 2280;
const PROGMEM float Resistance2 = 3880;
const PROGMEM float Vin = 3.3;
const PROGMEM float PotSlope = (Resistance2 - Resistance1) / (Angle2 - Angle1);
const PROGMEM float PotIntercept = (Resistance2 + Resistance1 - PotSlope*(Angle1 + Angle2)) / float(2);
int stepCounter = 0;

boolean FWD = LOW;
boolean REV = HIGH;
	

void setup_motor() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	//pinMode(SensorPin, INPUT);
	//pinMode(VoltagePin, OUTPUT);
	//digitalWrite(SensorPin, HIGH);
	//digitalWrite(VoltagePin, HIGH);
	pinMode(stepPin, OUTPUT);	 //Pin settings OUTPUTS
	pinMode(dirPin, OUTPUT);
	Serial.println("hello world");
	Serial.println(ExerciseRepsString);
	Serial.println(StartString);
	Serial.println(TargetExtendString);
	Serial.println(TargetFlexString);
	String temp = ExerciseRepsString.substring(15);
	Serial.print("Here is the whole string: ");
	Serial.println(ExerciseRepsString);
	Serial.print("Here is the substring: ");
	Serial.println(temp);
	//GONNA TRY TO MOVE ALL INDEX OF STRINGS DOWN BY TWO 16->14

}

void start_motor() {

	if (ExerciseRepsString.substring(14) == ",") {
	ExerciseRepsString = ExerciseRepsString.substring(12);
	Serial.println("Exercise Reps");
	ExerciseRepsString.remove(1);
	ExerciseReps = ExerciseRepsString.toInt();
	Serial.println(ExerciseReps);
}


else if (ExerciseRepsString.substring(15) == ",") {
	ExerciseRepsString = ExerciseRepsString.substring(13);
	Serial.println("Exercise Reps");
	ExerciseRepsString.remove(2);
	ExerciseReps = ExerciseRepsString.toInt();
	Serial.println(ExerciseReps);
}
else if (ExerciseRepsString.substring(16) == ",") {
	ExerciseRepsString = ExerciseRepsString.substring(14);
	Serial.println("Exercise reps");
	ExerciseRepsString.remove(3);
	ExerciseReps = ExerciseRepsString.toInt();
	Serial.println(ExerciseReps);
}

if (TargetExtendString.substring(25) == ",") {
	TargetExtendString = TargetExtendString.substring(23);
	Serial.println("TargetExtend 1 ");
	TargetExtendString.remove(1);
	TargetExtend = TargetExtendString.toInt();
	Serial.println(TargetExtend);
}

else if (TargetExtendString.substring(26) == ",") {
	TargetExtendString = TargetExtendString.substring(23);
	Serial.println("TargetExtend 2");
	TargetExtendString.remove(2);
	TargetExtend = TargetExtendString.toInt();
	Serial.println(TargetExtend);
}
else if (TargetExtendString.substring(27) == ",") {
	TargetExtendString = TargetExtendString.substring(23);
	Serial.println("TargetExtend 3");
	TargetExtendString.remove(3);
	TargetExtend = TargetExtendString.toInt();
	Serial.println(TargetExtend);
}

if (true) {
	TargetFlexString = TargetFlexString.substring(18);
	TargetFlexString.remove(3);
	TargetFlex = TargetFlexString.toInt();
	Serial.println("Target flex");
	Serial.println(TargetFlex);
}
if (StartString.substring(19) == ",") {
	//Start = StartString.substring(11);
	Start = "true";
	//Start = Start.remove(5);
	Serial.println("Start false");
	Serial.println(Start);
}

else {
	//Start = StartString.substring(12);
	Start = "true";
	//Start = Start.remove(4);
	Serial.println("Start true");
	Serial.println(Start);
}

	if (Start == "true") {//CHECK THIS!!
		exercise();
	}
	
	
}

void exercise() {
	int RepCounter = 0;
	Serial.println("This is the exercise function");
	while (RepCounter <= ExerciseReps) {
		//FAngle = 999;
		flex();
		FeedbackAngle = AngleValue;
		web_talk_to_clients();
		extend();
		FeedbackAngle = AngleValue;
		web_talk_to_clients();
		RepCounter += 1;
	}
	
}

int calibrate() {
	Serial.println("Set brace to 0 degrees and then press enter");
	Serial.read();
	float zeroDegreeValue = analogRead(SensorPin);
	float zeroDegreeVoltage = float(zeroDegreeValue)*float(3.300/1024);

	Serial.println("Set brace to 110 degrees and then press enter");
	Serial.read();
	float oneTenDegreeValue = analogRead(SensorPin);
	float oneTenDegreeVoltage = float(oneTenDegreeValue)*float(3.300/1024);
	

	
}
float read_angle() {
	
	SensorValue = analogRead(SensorPin);
	SensorVoltage = float(SensorValue)*float(3.300/1024);
	AngleValueFloat = (((SensorVoltage * R1) / (Vin - SensorVoltage)) - PotIntercept) / PotSlope;
	AngleValue = (int) (AngleValueFloat + 0.5) - AngleCorrectionFactor;


 AdditionalAngleCorrector = (.11*AngleValue);
 AdditionalAngleCorrector = (int) (AdditionalAngleCorrector + 0.5);
 AngleValue = AngleValue - AdditionalAngleCorrector;
	
	Serial.println("Sensor Voltage is: ");
	Serial.println(SensorVoltage, 5);
	Serial.println("The AdditionalAngleCorrector is: ");
	Serial.println(AdditionalAngleCorrector);
	Serial.println("Angle is: ");
	Serial.println(AngleValue);
	Serial.println("Target Extend");
	Serial.println(TargetExtend);
	Serial.println("Target Flex");
	Serial.println(TargetFlex);
	Serial.println("ExtensionHitCounter is ");
	Serial.println(ExtensionHitCounter);
	Serial.println("FlexionHitCounter is ");
	Serial.println(FlexionHitCounter);
	delay(1000);
	return AngleValue;
}
void extend() {
	
	AngleValue = read_angle();
	Serial.println("EXTEND!!!");
	counter = 0;
	ExtensionHitCounter = 0;
	while (ExtensionHitCounter < 1){
		while (counter < 1000){
			step_forward();
			counter = counter + 1;
		}
		AngleValue = read_angle();
		if(AngleValue <= TargetExtend){
			ExtensionHitCounter += 1;
		}
	}
}
void flex() {
	
	AngleValue = read_angle();
	Serial.println("FLEX!!!");
	counter = 0;
	FlexionHitCounter = 0;
	while (FlexionHitCounter < 1) {
		while (counter < 1000){
			step_backward();
			counter = counter + 1;
		}
		counter = 0;
		AngleValue = read_angle();
		if (AngleValue >= TargetFlex){
			FlexionHitCounter += 1;
		}
		
	}
	
}
void step_forward() {
	Serial.println("stepping forward");
	digitalWrite(dirPin, FWD);
	digitalWrite(sleepPin, HIGH);							// Set the Sleep mode to AWAKE.
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(500);
	stepCounter--;
	digitalWrite(stepPin, LOW); 
}

void step_backward() {
	Serial.println("stepping backward");
	digitalWrite(dirPin, REV);
	digitalWrite(sleepPin, HIGH);							// Set the Sleep mode to AWAKE.
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(500);
	digitalWrite(stepPin, LOW);
	stepCounter = stepCounter + 1;
	Serial.println(stepCounter);
}



