int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)
int count = 0;   //which y pin we are selecting
int v = 1;

void setup(){
  Serial.begin(9600);
  Serial.println("Ready");
  pinMode(2, OUTPUT);    // s0
  pinMode(3, OUTPUT);    // s1
  pinMode(4, OUTPUT);    // s2
}

void loop () {
  
  if(Serial.available()){
    count = Serial.parseInt(); // read the incoming data
    Serial.println(count);
  }
  
  // select the bit  
  r0 = bitRead(count,0);    // use this with arduino 0013 (and newer versions)    
  r1 = bitRead(count,1);    // use this with arduino 0013 (and newer versions)    
  r2 = bitRead(count,2);    // use this with arduino 0013 (and newer versions)    
  
  digitalWrite(2, r0);
  digitalWrite(3, r1);
  digitalWrite(4, r2);
  
  //count = random(0, 8);
  //if (count == 7)
  //{
  //  v = -1;
  //}
  //else if (count == 0)
  //{
  //  v = 1;
  //}
  //count = count + v;

}
