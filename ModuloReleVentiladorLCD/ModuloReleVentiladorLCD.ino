
#include <IRremote.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(56,16,2);

uint8_t duck[8]  = {
  0x0,0xc,0x1d,0xf,0xf,0x6,0x0};

int RECV_PIN = 8;

/*
String rele_1 = "80BF49B6";
String rele_2 = "80BFC936";
String rele_3 = "80BF33CC";
String rele_4 = "80BF718E";
String rele_5 = "80BFF10E";
String rele_6 = "80BF13EC";
String desliga = "80BFD12E";*/


//controle kenwood
String rele_1 = "9D62807F";
String rele_2 = "9D6240BF";
String rele_3 = "9D62C03F";
String rele_4 = "9D6220DF";
String rele_5 = "9D62A05F";
String rele_6 = "9D62609F";
String desliga = "9D6200FF";


String codigo;
String sentido = "desligado";
int velocidade;

IRrecv irrecv(RECV_PIN);

decode_results results;

int led_1 = 12;
int led_2 = 11;
int led_3 = 10;
int led_4 = 9;

void setup() {                

  Serial.begin(9600);
  irrecv.enableIRIn();

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, duck);
  lcd.home();
  visor("VENTILADOR - 00");

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);

  delay(1000);
}

void loop() {
  ventilador();
}

void ventilador(){

  if (irrecv.decode(&results)) {

    codigo = String(results.value, HEX);

    if (codigo.equalsIgnoreCase(rele_1)){
      vent_min();
    } 

    if (codigo.equalsIgnoreCase(rele_2)){
      vent_med();
    } 

    if (codigo.equalsIgnoreCase(rele_3)){
      vent_max();
    } 

    if (codigo.equalsIgnoreCase(rele_4)){
      exa_min();
    } 

    if (codigo.equalsIgnoreCase(rele_5)){
      exa_med();
    } 

    if (codigo.equalsIgnoreCase(rele_6)){
      exa_max();
    } 

    if (codigo.equalsIgnoreCase(desliga)){
      pos_0();
      sentido = "desligado";
      Serial.println(sentido);
      Serial.println("***************************************");
    }
    irrecv.resume();  
  }
}

void pos_0(){
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);
  digitalWrite(led_3, LOW);
  digitalWrite(led_4, LOW);
  visor("VENTILADOR - 00");
}

void vent_min(){
  verifica("ventilador");
  velocidade = 1;
  digitalWrite(led_1, 1);
  digitalWrite(led_2, 0);
  digitalWrite(led_3, 0);
  digitalWrite(led_4, 1);
  visor("VENTILADOR - 01");
}

void vent_med(){
  verifica("ventilador");
  velocidade = 2;
  digitalWrite(led_1, 1);
  digitalWrite(led_2, 0);
  digitalWrite(led_3, 1);
  digitalWrite(led_4, 0);
  visor("VENTILADOR - 02");
}

void vent_max(){
  verifica("ventilador");
  velocidade = 3;
  digitalWrite(led_1, 1);
  digitalWrite(led_2, 0);
  digitalWrite(led_3, 0);
  digitalWrite(led_4, 0);
  visor("VENTILADOR - 03");
}

void exa_min(){
  verifica("exaustor");
  velocidade = 1;
  digitalWrite(led_1, 1);
  digitalWrite(led_2, 1);
  digitalWrite(led_3, 0);
  digitalWrite(led_4, 1);
  visor("EXAUSTOR - 01");
}

void exa_med(){
  verifica("exaustor");
  velocidade = 2;
  digitalWrite(led_1, 1);
  digitalWrite(led_2, 1);
  digitalWrite(led_3, 1);
  digitalWrite(led_4, 0);
  visor("EXAUSTOR - 02");
}

void exa_max(){
  verifica("exaustor");
  velocidade = 3;
  digitalWrite(led_1, 1);
  digitalWrite(led_2, 1);
  digitalWrite(led_3, 0);
  digitalWrite(led_4, 0);
  visor("EXAUSTOR - 03");
}

void verifica(String sent){
  if (sent.equalsIgnoreCase(sentido) || sentido.equalsIgnoreCase("desligado")){
    Serial.println("Dentro if (verdadeiro)");
    Serial.print("sent: ");
    Serial.println(sent);
    Serial.print("sentido: ");
    Serial.println(sentido);
    Serial.println("***************************************");
    sentido = sent;
  }
  else{
    pos_0();
    for (int i=0; i < 25; i++){
      Serial.println(i+1);
      delay(1000);
    }

    Serial.println("Dentro else (falso)");
    Serial.print("sent: ");
    Serial.println(sent);
    Serial.print("sentido: ");
    Serial.println(sentido);
    Serial.println("***************************************");
    sentido = sent;
  }
}

void visor(String veloc){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kiko Previero ");
  lcd.write(0);
  lcd.setCursor(0, 1);
  lcd.print(veloc);
}
