// Function prototypes

// Pins
const int PIN_TEAM_A_PLUS  = A0;
const int PIN_TEAM_A_MINUS = A1;
const int PIN_TEAM_B_PLUS  = A2;
const int PIN_TEAM_B_MINUS = A3;
const int PIN_IR_A = A5;
const int PIN_IR_B = A6;

// Constants
const int IR_THRESHOLD = 32;

// Globals
int golsA = 0;
int golsB = 0;
boolean debounce_ir_a = false;
boolean debounce_ir_b = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TEAM_A_PLUS,  INPUT);
  pinMode(PIN_TEAM_A_MINUS, INPUT);
  pinMode(PIN_TEAM_B_PLUS,  INPUT);
  pinMode(PIN_TEAM_B_MINUS, INPUT);
  pinMode(PIN_IR_A,         INPUT);
  pinMode(PIN_IR_B,         INPUT);
}

void debug() {
  Serial.print("SCORE A: ");
  Serial.print(golsA);
  Serial.print(" | SCORE B: ");
  Serial.print(golsB);
  Serial.println("");
}

void addGoal(int &team){
  team++;
}

void readIRSensors() {
  int ir_a  =   analogRead(PIN_IR_A);
  int ir_b  =   analogRead(PIN_IR_B);

  readIRSensor(ir_a, debounce_ir_a, golsB);
  readIRSensor(ir_b, debounce_ir_b, golsA);
}
void readIRSensor(int &ir, boolean &debounce, int &team) {
  if (!debounce) {
    if (ir > IR_THRESHOLD) {
      addGoal(team);
      debounce = true;
    }
  } else if (ir < IR_THRESHOLD) {
    debounce = false;
  }
}

void loop() {
  int team_a_plus   =   analogRead(PIN_TEAM_A_PLUS);
  int team_a_minus  =   analogRead(PIN_TEAM_A_MINUS);
  int team_b_plus   =   analogRead(PIN_TEAM_B_PLUS);
  int team_b_minus  =   analogRead(PIN_TEAM_B_MINUS);

  readIRSensors();
  debug();
  delay(200);
}

