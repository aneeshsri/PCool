#include <dht.h>

#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;

//Optimal computer temp I want is 25 degrees C:
int OptimCompTemp = 25;

// Fan motor variables:
int en_12 = 9;
int in_1a = 8;
int in_2a = 7;

void setup() {

  // DHT11 Sensor:
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor

  // Set fan motor pins to outputs:
  pinMode(en_12, OUTPUT);
  pinMode(in_1a, OUTPUT);
  pinMode(in_2a, OUTPUT);
  
  // Turn off motor:
  digitalWrite(in_1a, LOW);
  digitalWrite(in_2a, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_apin);

  Serial.print("Temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");

  //If temp <= 20 C:
  if (DHT.temperature <= (OptimCompTemp - 5)){
    digitalWrite(in_1a, LOW);
    digitalWrite(in_2a, LOW);
    
    analogWrite(en_12, 0);
  }
  //Else if temp > 20 C, but <= 25 C:
  else if ( (DHT.temperature > (OptimCompTemp - 5)) && (DHT.temperature <= OptimCompTemp) ){
    digitalWrite(in_1a, LOW);
    digitalWrite(in_2a, HIGH);

    analogWrite(en_12, 85);
  }
  //Else if temp > 25, but < 30 C:
  else if ( (DHT.temperature > OptimCompTemp) && (DHT.temperature < (OptimCompTemp + 5)) ){
    digitalWrite(in_1a, LOW);
    digitalWrite(in_2a, HIGH);

    analogWrite(en_12, 171);
  }
  //Else temp >= 30 C:
  else{
    digitalWrite(in_1a, LOW);
    digitalWrite(in_2a, HIGH);

    analogWrite(en_12, 255);
  }
  
  
  delay(5000);//Wait 5 seconds before repeating.
  
}

//Still in progress - writing a function that will allow for the fan speed to change gradually, as opposed to suddenly
void speedUp(int current, int target){
  for (int i = current; i <= target; i++) {
    analogWrite(en_12, i);
    delay(100);
  }
}

void slowDown(int current, int target){
  for (int i = current; i >= target; i--) {
    analogWrite(en_12, i);
    delay(100);
  }
}
