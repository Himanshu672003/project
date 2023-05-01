const int trigPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4; // Echo Pin of Ultrasonic Sensor

int distance, cm;
int stateStop = 0;


// for motor m1
#define m1Forward A1
#define m1Backward A3

// for motor m2
#define m2Backward A4
#define m2Forward A5

// for motor m3
#define m3Forward 7
#define m3Backward 8

// for motor m4
#define m4Backward 9
#define m4Forward 10


int command; //Int to store app command state.
int Speed = 204; // 0 - 255.                                      


void forward(){
  analogWrite(m1Forward, Speed);
  analogWrite(m2Forward, Speed);
  analogWrite(m3Forward, Speed);
  analogWrite(m4Forward, Speed);
  Serial.println("go forward!");
}
void back(){
  analogWrite(m1Backward, Speed);
  analogWrite(m2Backward, Speed);
  analogWrite(m3Backward, Speed);
  analogWrite(m4Backward, Speed);
  Serial.println("go back!");
}
void left(){
  analogWrite(m1Backward, Speed);
  analogWrite(m2Forward, Speed);
  analogWrite(m3Forward, Speed);
  analogWrite(m4Backward, Speed);
 Serial.println("go left!");
}
void right(){
  analogWrite(m1Forward, Speed);
  analogWrite(m2Backward, Speed);
  analogWrite(m3Backward, Speed);
  analogWrite(m4Forward, Speed);
  Serial.println("go Right!");
}
void forwardleft(){
  Serial.println("forward left");
  analogWrite(m1Backward, Speed);
  analogWrite(m2Forward, Speed);
  analogWrite(m3Forward, Speed);
  analogWrite(m4Backward, Speed);
}
void forwardright() { 
  Serial.println("forward right");
  analogWrite(m1Forward, Speed);
  analogWrite(m2Backward, Speed);
  analogWrite(m3Backward, Speed);
  analogWrite(m4Forward, Speed);
}
void backright(){
  Serial.println("back right");
  analogWrite(m1Forward, Speed);
  analogWrite(m2Backward, Speed);
  analogWrite(m3Backward, Speed);
  analogWrite(m4Forward, Speed);
}
void backleft() {
  Serial.println("backleft");
  analogWrite(m1Backward, Speed);
  analogWrite(m2Forward, Speed);
  analogWrite(m3Forward, Speed);
  analogWrite(m4Backward, Speed);
}
void Stop(){
  Serial.println("stop");
   analogWrite(m1Forward, 0);
   analogWrite(m2Forward, 0);
   analogWrite(m3Forward, 0);
   analogWrite(m4Forward, 0);
   analogWrite(m1Backward, 0);
   analogWrite(m2Backward, 0);
   analogWrite(m3Backward, 0);
   analogWrite(m4Backward, 0);
 // Serial.println("Stop!");  
}

void setup() {
  
   Serial.begin(9600);

  pinMode(m1Forward, OUTPUT);
  pinMode(m2Forward, OUTPUT);
  pinMode(m3Forward, OUTPUT);
  pinMode(m4Forward, OUTPUT);
  pinMode(m1Backward, OUTPUT);
  pinMode(m2Backward, OUTPUT);
  pinMode(m3Backward, OUTPUT);
  pinMode(m4Backward, OUTPUT);

  digitalWrite(m1Forward, LOW);
  digitalWrite(m2Forward, LOW);
  digitalWrite(m3Forward, LOW);
  digitalWrite(m4Forward, LOW);
  digitalWrite(m1Backward, LOW);
  digitalWrite(m2Backward, LOW);
  digitalWrite(m3Backward, LOW);
  digitalWrite(m4Backward, LOW);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH);
  cm = abs(distance / 58);
  //  Serial.print("distance from object(cm)= ");
 // Serial.println(cm);
  if (cm <= 20)
  {
    Stop();
    delay(200);
    back();
    delay(200);
    Stop();
    delay(200);
  }
else {
if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //Initialize with motors stoped.
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
       case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
    }
    
  }
}

}
  
