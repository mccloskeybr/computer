#define A_0_PORT 12
#define A_1_PORT 11
#define A_2_PORT 10
#define A_3_PORT 9

#define B_0_PORT 22
#define B_1_PORT 24
#define B_2_PORT 26
#define B_3_PORT 28

#define SUM_0_PORT 6
#define SUM_1_PORT 5
#define SUM_2_PORT 4
#define SUM_3_PORT 3
#define C_OUT_PORT 2

char buffer[1024];

void SendA(int a) {
  digitalWrite(A_0_PORT, (a >> 0) & 1);
  digitalWrite(A_1_PORT, (a >> 1) & 1);
  digitalWrite(A_2_PORT, (a >> 2) & 1);
  digitalWrite(A_3_PORT, (a >> 3) & 1);
}

void SendB(int b) {
  digitalWrite(B_0_PORT, (b >> 0) & 1);
  digitalWrite(B_1_PORT, (b >> 1) & 1);
  digitalWrite(B_2_PORT, (b >> 2) & 1);
  digitalWrite(B_3_PORT, (b >> 3) & 1);
}

int ReadSum() {
  return (digitalRead(SUM_0_PORT) << 0) |
         (digitalRead(SUM_1_PORT) << 1) |
         (digitalRead(SUM_2_PORT) << 2) |
         (digitalRead(SUM_3_PORT) << 3) |
         (digitalRead(C_OUT_PORT) << 4);
}

void Test(int a, int b) {
  int expected_sum = a + b;

  SendA(a);
  SendB(b);
  int actual_sum = ReadSum();

  sprintf(buffer, "%d + %d = %d? : %d ", a, b, expected_sum, actual_sum);
  Serial.print(buffer);
  if (actual_sum != expected_sum) { Serial.print("FAIL"); }
  Serial.println();
}

void TestAll() {
  for (int a = 0; a < 1 << 4; a++) {
    for (int b = 0; b < 1 << 4; b++) {
      Test(a, b);
    }
  }
}

void setup() {
  pinMode(A_0_PORT, OUTPUT);
  pinMode(A_1_PORT, OUTPUT);
  pinMode(A_2_PORT, OUTPUT);
  pinMode(A_3_PORT, OUTPUT);

  pinMode(B_0_PORT, OUTPUT);
  pinMode(B_1_PORT, OUTPUT);
  pinMode(B_2_PORT, OUTPUT);
  pinMode(B_3_PORT, OUTPUT);

  pinMode(SUM_0_PORT, INPUT);
  pinMode(SUM_1_PORT, INPUT);
  pinMode(SUM_2_PORT, INPUT);
  pinMode(SUM_3_PORT, INPUT);
  pinMode(C_OUT_PORT, INPUT);

  // TODO: Also test carry in bit.
  Serial.begin(115200);
  Serial.println("=== NEW TEST ===");
  TestAll();
}

void loop() {}
