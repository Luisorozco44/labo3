#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3C // Dirección I2C común de pantallas OLED SH1106
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Inicializa la configuración de la pantalla

const int pinLM35 = A0;
const float Vref = 5.0;
const unsigned long intervalo = 1000;//intervalo
unsigned long ultimaMillis = 0;

void setup() {
  Serial.begin(9600); // velocidad del Monitor Serial
  while (!Serial) { }

  delay(250); /// wait for the OLED to power up
  display.begin(i2c_Address, true);   // Address 0x3C default
  display.setContrast(255);          // dim display

  // Clear the buffer.
  display.clearDisplay();
  display.display();  // Save to update screen changes

  Serial.println("Plantilla OLED con lectura LM35");
}

void loop() {
  unsigned long ahora = millis();

  if (ahora - ultimaMillis >= intervalo) {
    ultimaMillis = ahora;

    int lectura = analogRead(pinLM35);
    float voltaje = lectura * (Vref / 1023.0);
    float tempC = voltaje * 100.0;

    display.clearDisplay();// limpiar pantalla

    display.setTextSize(1); //tamanio letra
    display.setTextColor(SH110X_WHITE);// color
    display.setCursor(10, 0);// lugar del cursor
    display.println("Temperatura en °C:  ");

    display.setTextSize(2);                    
    display.setTextColor(SH110X_WHITE);//color
    display.setCursor(20, 25);
    display.print(tempC, 2); // 2 decimales      
    display.println(" C");

    display.display(); // mostart en la pantalla
  }

}