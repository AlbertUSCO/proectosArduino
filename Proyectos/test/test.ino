
int pinDL1 =  4;// led Dl1
int pinDL2 =  5;// led Dl2
int pinDS1 = 6;//pulsador DS1
int pinDS2 = 7;//pulsador DS2
int pinSensor = 3;//salida PWM
int pinVolBat = A0; // lectura de voltaje de la bateria
unsigned long previousMillis = 0;// variable inicial para calculo de tiempo
const long interval = 3000; // intervalo de 3 segundos segun el reqerimiento

void batStatus(){
    int value;
    float volt;

    value = analogRead(pinVolBat);
    volt = value * 5.0 / 1024;
    Serial.print("voltaje bateria: ");
    Serial.println(volt);
}

void ledLevel(){
    String ledValue = "";
    String led = "";
    int workCycle = 0;

    if (Serial.available() > 0){
    ledValue= Serial.readString();
    Serial.println("valor de iluminacion Para "+ledValue);
    led = ledValue.substring(0,ledValue.indexOf(","));
    Serial.println("led: "+led);
    workCycle = (int)ledValue.substring(ledValue.indexOf(",")+1,ledValue.length()).toInt();
    Serial.print("Ciclos de Trabajo: ");
    Serial.println(workCycle);
    if(led == "l1"){
      analogWrite(pinDL1, workCycle * 255 /100);
      }
    else if(led == "l2"){
      analogWrite(pinDL2, workCycle * 255 /100);
    }
    else{  
      Serial.println("Ups!! Caracter incorrecto");
    }
    }
}

void sensorBt(){
  if (digitalRead(pinDS1) == LOW && digitalRead(pinDS2) == LOW) {
    digitalWrite(pinSensor, HIGH);  
  } 
  else{
    digitalWrite(pinSensor, LOW); 
  }
}

void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000010;    // TIM2 (Pin3 & Pin11) divisor = 8  PWM frecuencia = 3921.16 Hz

  pinMode(pinDL1, OUTPUT);
  pinMode(pinDL2, OUTPUT);
  pinMode(pinSensor, OUTPUT);

  pinMode(pinDS1, INPUT);
  pinMode(pinDS2, INPUT);
  

  Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      batStatus();
  }
  ledLevel();
  sensorBt();
  delay(3000);
}
