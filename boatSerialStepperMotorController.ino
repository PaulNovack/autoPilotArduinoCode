const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;
int startSpeed = 600;
bool doneDelay = false;
char input;
String stepsStr;
long center = 0;
  
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  Serial.begin(115200);

}

void loop() {
  if(Serial.available()){
    input = Serial.read();
    if(input == 'L'){
      stepsStr = Serial.readStringUntil('\n');
      move(stepsStr.toInt(),true,center); 
    }
    if(input == 'R'){
      stepsStr = Serial.readStringUntil('\n');
        move(stepsStr.toInt(),false,center); 
    }
    if(input == 'C'){
      if(center > 0){
        move(center,false,center); 
      } else {
        move(-center,true,center); 
      }
    }

  }
}

// Function for move
int move(int steps, bool direction,long& center){
  // set vars
  int InverseRunSpeed = 2000;
  if(direction == true){
    digitalWrite(dirPin,HIGH); //Changes the direction of rotation
  } else {
    digitalWrite(dirPin,LOW); //Changes the direction of rotation
  }

  for(int x = 0; x < steps; x++) {
    if(direction) {
      center++;
    } else {
      center--;
    }
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(InverseRunSpeed);
    if(steps - x < 2000){
      InverseRunSpeed = InverseRunSpeed + 1;
    } else if(InverseRunSpeed > 300){
      InverseRunSpeed = InverseRunSpeed - 1;
    }

  }
}
