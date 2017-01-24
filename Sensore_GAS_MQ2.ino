#include <LiquidCrystal_I2C.h>

#define LED_ROSSO = 8
#define LED_VERDE = 9

LiquidCrystal_I2C lcd(0x3F, 20, 4);

const int SEGNALE_MQ2 = 1; // Pin analogico A0
const int SOGLIA_MQ2 = 250;

long mq2_val;

int buzzer = 4;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("    Sensore MQ2    ");
  lcd.setCursor(0, 1);
  lcd.print("       Rileva       ");
  lcd.setCursor(0, 2);
  lcd.print("Metano        Butano");
  lcd.setCursor(0, 3);
  lcd.print("GPL           Fumo  ");
  pinMode(SEGNALE_MQ2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  delay(4000);
  lcd.clear();
}

void loop() {

  mq2_val = analogRead(SEGNALE_MQ2);

  if (mq2_val > SOGLIA_MQ2) {
    lcd.setCursor(0, 0);
    lcd.print("    !ATTENZIONE!    ");
    lcd.setCursor(0, 1);
    lcd.print("Presenza di GAS/FUMO");
    lcd.setCursor(0, 2);
    lcd.print("  oltre il limite!  ");
    lcd.setCursor(0, 3);
    lcd.print("    Valore:  ");
    lcd.setCursor(13, 3);
    lcd.print(mq2_val);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    tone(4, 2000);
  }

  else {
    lcd.setCursor(0, 0);
    lcd.print("Assenza  di GAS/FUMO");
    lcd.setCursor(0, 1);
    lcd.print("valore sotto 250 ppm");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("    Valore:    ");
    lcd.setCursor(13, 3);
    lcd.print(mq2_val     );
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
    noTone(4);
  }
  delay(500);
}
