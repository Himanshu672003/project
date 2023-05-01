char t;
 long g=1000;
gvoid setup() {
pinMode(9,OUTPUT);   //left motors forward
pinMode(8,OUTPUT);   //left motors reverse
pinMode(7,OUTPUT);   //right motors forward
pinMode(16,OUTPUT);   //right motors reverse

Serial.begin(9600);
 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(7,HIGH);
  digitalWrite(11,HIGH);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
  
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction,)
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(9,HIGH);



   
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, )
  digitalWrite(7,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);

}

else if(t == 'W'){    //turn led on or off)
  digitalWrite(9,HIGH);
  
}
else if(t == 'w'){
  digitalWrite(9,LOW);

}
else if(t=='w'){
  digitalWrite(8,HIGH); //turn back led on
}
else if(t=='w'){
  digitalWrite(8,LOW);
}
else if(t=='M'){
  digitalWrite(8,HIGH);
  
}
else if(t=='m'){
  digitalWrite(8,LOW);
  
}

else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(7,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  digitalWrite(8,LOW);
}
delay(25);
}
