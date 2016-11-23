
#define o_btn 0
#define t_btn 13
#define ledStart 2
#define ledEnd 11

static int ballPos = ledStart;
static int lastPos = ballPos;
static unsigned long lastButtonPressedMillis = 0; 

struct Player {
  bool isHolding;
} one{true}, two{false};

void setup() {
  pinMode(o_btn, INPUT);
  pinMode(t_btn, INPUT);
  Serial.begin(9600); 
  for(int i = ledStart; i < ledEnd; i++) {
    Serial.print("toggled to OUTPUT: ");
    Serial.print(i);
    Serial.println();
    pinMode(i, OUTPUT); }
}

int pres(int id) { return digitalRead(id); }
int opr() { return !pres(o_btn); }
int tpr() { return !pres(t_btn); }

void on_opr() {
  if(one.isHolding) {
    send(ledEnd - 1);
    lastButtonPressedMillis = millis();
    one.isHolding = false;  
  }
  if(ballPos == -1) { ballPos = ledStart; }
}

void on_tpr() {
  if(two.isHolding) {
    send(ledStart);
    lastButtonPressedMillis = millis();
    two.isHolding = false;
  }
  if(ballPos == -1) { ballPos = (ledEnd - 1); }
}


void send(int nPos) {
  while(ballPos != nPos) {
    if(ballPos > nPos) {
      ballPos--;
      digitalWrite(ballPos + 1, LOW);
      flash();
    } else if(ballPos < nPos) {
      ballPos++;
      digitalWrite(ballPos - 1, LOW);
      flash();
    }
  }
}

void flash() { flash(ballPos); }

void flash(int id) {
  digitalWrite(id, HIGH);
  delay(50);
}

void on_one_hold() {
  one.isHolding = true;
}

void on_two_hold() {
  two.isHolding = true;
}

void all(bool off) {
  for(int i = 0; i < (ledEnd - 1); i++) {
    digitalWrite(i, LOW);
  }
}

void flashRange(int beg, int end, int time) {
  int timeDiv = time / 2;
  for(int i = beg; i < end; i++) {
    digitalWrite(i, HIGH);
    delay(timeDiv);
    digitalWrite(i, LOW);
    delay(timeDiv);
  }
}
void flashWinner() {
  if(one.isHolding) {
    // flash two's lights.
    Serial.println("one won");
    for(int i = 0; i > 3; i++) {
      flashRange(0, (ledEnd - 1) / 2, 3000);
    }
  } else {
    Serial.println("two won");
    for(int i = 0; i > 3; i++) {
      flashRange((ledEnd - 1) / 2, ledEnd - 1, 3000);
    }
  }
}

void logic() {
  flash();
  if(millis() >= (lastButtonPressedMillis + 1000)) {
    all(false);
    flashRange(0, ledEnd-1, 1000);
    //flashWinner();
    exit(0);
    delay(5000);
    lastButtonPressedMillis = 0;
    ballPos = -1;
  }
  if(ballPos == ledStart) on_one_hold();
  else if(ballPos == (ledEnd - 1)) on_two_hold();
  if(opr()) on_opr();
  if(tpr()) on_tpr();
  Serial.print("ballpos = ");
  Serial.println(ballPos);
  Serial.print("oh: "); Serial.println(one.isHolding ? "true" : "false");
  Serial.print("th: "); Serial.println(two.isHolding ? "true" : "false");
}

void game() {
  logic();
}

void loop() {
  game();
}
