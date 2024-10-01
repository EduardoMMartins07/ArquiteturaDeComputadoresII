#include <MPU6050_tockn.h>
#include <Wire.h>

#define LeftB 2
#define RightB 3
#define MouseB 6

MPU6050 mpu6050(Wire);
int X, Y, Z;
int OX, OY, OZ;
unsigned long lastMouseMove = 0;    // Para controle do intervalo de movimento do mouse
unsigned long lastButtonPress = 0;  // Para controle de debounce dos botões

const unsigned long mouseMoveInterval = 5;         // Intervalo para o movimento do mouse em milissegundos
const unsigned long buttonDebounceInterval = 100;  // Intervalo para debounce dos botões em milissegundos

// Fator de sensibilidade - reduza este valor para diminuir a sensibilidade do movimento
float sensitivityFactor = 0.25;  // Reduz para 50% do movimento original

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();

  Serial.println("STRTM");        // Start message
  mpu6050.calcGyroOffsets(true);  // Wait for calibration
  mpu6050.update();

  // Capture initial orientation as offset
  OX = mpu6050.getAngleX();
  OY = mpu6050.getAngleY();
  OZ = mpu6050.getAngleZ();

  pinMode(LeftB, INPUT);   // Left button
  pinMode(RightB, INPUT);  // Right button
}

void loop() {
  mpu6050.update();

  // Subtract offsets to get relative motion
  X = (mpu6050.getAngleX() - OX) * sensitivityFactor;
  Y = (mpu6050.getAngleY() - OY) * sensitivityFactor;
  Z = (mpu6050.getAngleZ() - OZ) * sensitivityFactor;

  Serial.println("DATAL," + String(X) + ',' + String(Y) + ',' + String(Z));


  if (digitalRead(LeftB) == HIGH) {
    delay(300);
    Serial.println("DATAB,L");
  }

  if (digitalRead(RightB) == HIGH) {
    delay(300);
    Serial.println("DATAB,R");
  }
}
