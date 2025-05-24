#define C_IN_PORT 13
#define D_0_PORT 12
#define D_1_PORT 11
#define D_2_PORT 10
#define D_3_PORT 9

#define C_OUT_PORT 8
#define SUM_0_PORT 7
#define SUM_1_PORT 6
#define SUM_2_PORT 5
#define SUM_3_PORT 4

char buffer[1024];

void SendD(int d) {
  digitalWrite(D_0_PORT, (d >> 0) & 1);
  digitalWrite(D_1_PORT, (d >> 1) & 1);
  digitalWrite(D_2_PORT, (d >> 2) & 1);
  digitalWrite(D_3_PORT, (d >> 3) & 1);
}

void SendCIn(int c_in) {
  digitalWrite(C_IN_PORT, (c_in >> 0) & 1);
}

int ReadSum() {
  return (digitalRead(SUM_0_PORT) << 0) |
         (digitalRead(SUM_1_PORT) << 1) |
         (digitalRead(SUM_2_PORT) << 2) |
         (digitalRead(SUM_3_PORT) << 3) |
         (digitalRead(C_OUT_PORT) << 4);
}

void Test(int d, int c_in) {
  int expected_sum = d + c_in;

  SendD(d);
  SendCIn(c_in);
  int actual_sum = ReadSum();

  sprintf(buffer, "%d + %d = %d? : %d ", d, c_in, expected_sum, actual_sum);
  Serial.print(buffer);
  if (actual_sum != expected_sum) { Serial.print("FAIL"); }
  Serial.println();
}

void TestAll() {
  for (int d = 0; d < 1 << 4; d++) {
    Test(d, 0);
  }
  for (int d = 0; d < 1 << 4; d++) {
    Test(d, 1);
  }
}

void setup() {
  pinMode(C_IN_PORT, OUTPUT);
  pinMode(D_0_PORT, OUTPUT);
  pinMode(D_1_PORT, OUTPUT);
  pinMode(D_2_PORT, OUTPUT);
  pinMode(D_3_PORT, OUTPUT);

  pinMode(C_OUT_PORT, INPUT);
  pinMode(SUM_0_PORT, INPUT);
  pinMode(SUM_1_PORT, INPUT);
  pinMode(SUM_2_PORT, INPUT);
  pinMode(SUM_3_PORT, INPUT);

  Serial.begin(115200);
  Serial.println("=== NEW TEST ===");
  TestAll();
}

void loop() {}
