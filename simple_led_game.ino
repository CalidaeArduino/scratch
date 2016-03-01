#include <Event.h>
#include <Timer.h>

/*
JOC EASY
 */

Timer t;

// Leds
int up[] = {4,12,10,11};
int down[] = {3,8,7,6};

// Player
int player = A0;
boolean playerUp = true;
boolean looser = false;

// Enemies
int enemyUp = 6;
int enemyDown = 4;
int evemyMoveTime = 500;
int enemyTimer = 0;

// speaker
int speaker = 2;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(up[0], OUTPUT);
  pinMode(up[1], OUTPUT);
  pinMode(up[2], OUTPUT);
  pinMode(up[3], OUTPUT);
  pinMode(down[0], OUTPUT);
  pinMode(down[1], OUTPUT);
  pinMode(down[2], OUTPUT);
  pinMode(down[3], OUTPUT);
  Serial.begin(9600);
  
  enemyTimer = t.every(evemyMoveTime, moveEnemy);
  t.every(5000, goHard);
}

void movePlayer(){
  playerUp = analogRead(player) < 512;
  if (playerUp) {
    digitalWrite(down[0], LOW);
    digitalWrite(up[0], HIGH);
  } else {
    digitalWrite(down[0], HIGH);
    digitalWrite(up[0], LOW);
  }
}

void clearEnemies(){
  for(int i=1; i<4; i++){
    digitalWrite(up[i], LOW);
    digitalWrite(down[i], LOW);
  }
}

void goHard(){
  if (evemyMoveTime > 200)
    evemyMoveTime-=100;
    
  t.stop(enemyTimer);
  enemyTimer = t.every(evemyMoveTime, moveEnemy);
}

void regenerateEnemies(){
  if (enemyUp == -1){
    enemyUp = random(4,7);
  }
  if (enemyDown == -1){
    enemyDown = random(4,7);
  }
  if (enemyUp == enemyDown){
    enemyDown++;
  }
}
  
void moveEnemy(){
  // Unset all
  clearEnemies();

  enemyUp--;
  enemyDown--;

  regenerateEnemies();

  if (enemyUp < 4 && enemyUp > 0){
    digitalWrite(up[enemyUp], HIGH);
    tone(speaker, 100, 300);
  }
  if (enemyDown < 4 && enemyDown > 0){
    digitalWrite(down[enemyDown], HIGH);
    tone(speaker, 200, 300);
  }
  
  checkColision();
}

void checkColision(){
  if ((enemyUp == 0 && playerUp) || (enemyDown == 0 && !playerUp)){
    clearEnemies();
    looser = true;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  if (!looser){
    movePlayer();
    t.update();
  } else {
    tone(speaker, 350);
    digitalWrite(down[0], LOW);
    digitalWrite(up[0], HIGH);
    delay(300);
    digitalWrite(down[0], HIGH);
    digitalWrite(up[0], LOW);
    delay(300);
  }
}
