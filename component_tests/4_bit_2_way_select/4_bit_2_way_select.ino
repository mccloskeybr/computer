#define A_EN_PORT 13
#define B_EN_PORT 12

#define A_IN_0_PORT 10
#define A_IN_1_PORT 9
#define A_IN_2_PORT 8
#define A_IN_3_PORT 7

#define B_IN_0_PORT 6
#define B_IN_1_PORT 5
#define B_IN_2_PORT 4
#define B_IN_3_PORT 3

#define OUT_0_PORT 0
#define OUT_1_PORT 0
#define OUT_2_PORT 0
#define OUT_3_PORT 0

char buffer[1024];

void SendAB(int a, int b) {
  digitalWrite(A_IN_0_PORT, (a >> 0) & 1);
  digitalWrite(A_IN_1_PORT, (a >> 1) & 1);
  digitalWrite(A_IN_2_PORT, (a >> 2) & 1);
  digitalWrite(A_IN_3_PORT, (a >> 3) & 1);

  digitalWrite(B_IN_0_PORT, (b >> 0) & 1);
  digitalWrite(B_IN_1_PORT, (b >> 1) & 1);
  digitalWrite(B_IN_2_PORT, (b >> 2) & 1);
  digitalWrite(B_IN_3_PORT, (b >> 3) & 1);
}

void SendEnable(bool enable_a) {
  if (enable_a) {
    digitalWrite(A_EN_PORT, HIGH);
    digitalWrite(B_EN_PORT, LOW);
  } else {
    digitalWrite(A_EN_PORT, LOW);
    digitalWrite(B_EN_PORT, HIGH);
  }
}

int ReadOut() {
  int o = (digitalRead(OUT_0_PORT) << 0) |
          (digitalRead(OUT_1_PORT) << 1) |
          (digitalRead(OUT_2_PORT) << 2) |
          (digitalRead(OUT_3_PORT) << 3);
  return o;
}

void Test(int a, int b, bool enable_a) {
  SendAB(a, b);
  SendEnable(enable_a);

  int expected = enable_a ? a : b;
  int actual = ReadOut();

  sprintf(buffer, "A: %d, B: %d, expected: %d, actual: %d; ", a, b, expected, actual);
  Serial.print(buffer);
  if (actual != expected) { Serial.print("FAIL"); }
  Serial.println();
}

void TestAll() {
  for (int a = 0; a < 1 << 4; a++) {
    for (int b = 0; b < 1 << 4; b++) {
      Test(a, b, true);
    }
  }
  for (int a = 0; a < 1 << 4; a++) {
    for (int b = 0; b < 1 << 4; b++) {
      Test(a, b, false);
    }
  }
}

void setup() {
  pinMode(A_EN_PORT, OUTPUT);
  pinMode(B_EN_PORT, OUTPUT);

  pinMode(A_IN_0_PORT, OUTPUT);
  pinMode(A_IN_1_PORT, OUTPUT);
  pinMode(A_IN_2_PORT, OUTPUT);
  pinMode(A_IN_3_PORT, OUTPUT);

  pinMode(B_IN_0_PORT, OUTPUT);
  pinMode(B_IN_1_PORT, OUTPUT);
  pinMode(B_IN_2_PORT, OUTPUT);
  pinMode(B_IN_3_PORT, OUTPUT);

  pinMode(OUT_0_PORT, INPUT);
  pinMode(OUT_1_PORT, INPUT);
  pinMode(OUT_2_PORT, INPUT);
  pinMode(OUT_3_PORT, INPUT);

  Serial.begin(115200);
  Serial.println("=== NEW TEST ===");
  TestAll();
}

void loop() {}
