#define CLOCK_PORT 13
#define D_IN_EN_PORT 12
#define D_OUT_EN_PORT 11

#define D_IN_0_PORT 10
#define D_IN_1_PORT 9
#define D_IN_2_PORT 8
#define D_IN_3_PORT 7

#define D_OUT_0_PORT 6
#define D_OUT_1_PORT 5
#define D_OUT_2_PORT 4
#define D_OUT_3_PORT 3

char buffer[1024];

void SendD(int d) {
  digitalWrite(D_IN_0_PORT, (d >> 0) & 1);
  digitalWrite(D_IN_1_PORT, (d >> 1) & 1);
  digitalWrite(D_IN_2_PORT, (d >> 2) & 1);
  digitalWrite(D_IN_3_PORT, (d >> 3) & 1);

  digitalWrite(D_IN_EN_PORT, HIGH);
  digitalWrite(CLOCK_PORT, HIGH);
  digitalWrite(CLOCK_PORT, LOW);
  digitalWrite(D_IN_EN_PORT, LOW);
}

int ReadD() {
  digitalWrite(D_OUT_EN_PORT, HIGH);
  int d = (digitalRead(D_OUT_0_PORT) << 0) |
          (digitalRead(D_OUT_1_PORT) << 1) |
          (digitalRead(D_OUT_2_PORT) << 2) |
          (digitalRead(D_OUT_3_PORT) << 3);
  digitalWrite(D_OUT_EN_PORT, LOW);
  return d;
}

void Test(int d) {
  SendD(d);
  int expected_d = d;
  int actual_d = ReadD();

  sprintf(buffer, "%d = %d? : %d ", d, expected_d, actual_d);
  Serial.print(buffer);
  if (actual_d != expected_d) { Serial.print("FAIL"); }
  Serial.println();
}

void TestAll() {
  for (int d = 0; d < 1 << 4; d++) {
    Test(d);
    delay(500);
  }
}

void setup() {
  pinMode(D_IN_EN_PORT, OUTPUT);
  pinMode(D_OUT_EN_PORT, OUTPUT);
  pinMode(CLOCK_PORT, OUTPUT);

  pinMode(D_IN_0_PORT, OUTPUT);
  pinMode(D_IN_1_PORT, OUTPUT);
  pinMode(D_IN_2_PORT, OUTPUT);
  pinMode(D_IN_3_PORT, OUTPUT);

  pinMode(D_OUT_0_PORT, INPUT);
  pinMode(D_OUT_1_PORT, INPUT);
  pinMode(D_OUT_2_PORT, INPUT);
  pinMode(D_OUT_3_PORT, INPUT);

  digitalWrite(D_IN_EN_PORT, LOW);
  digitalWrite(D_OUT_EN_PORT, LOW);
  digitalWrite(CLOCK_PORT, LOW);
  digitalWrite(D_IN_0_PORT, LOW);
  digitalWrite(D_IN_1_PORT, LOW);
  digitalWrite(D_IN_2_PORT, LOW);
  digitalWrite(D_IN_3_PORT, LOW);

  Serial.begin(115200);
  Serial.println("=== NEW TEST ===");
  TestAll();
}

void loop() {}
