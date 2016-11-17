//atualizado em 17/11/2016. 21:26 - Mestrado Neres - TIDD - 2014-2016//

#include <Stepper.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"

#include <IRremote.h>
#include <IRremoteInt.h>
#include <FreqCount.h>
IRsend irsend;

//variaveis de passos para giro do motor//
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);

int stepCount = 0;

//define a saida a ser utilizada para o acionamento do rele
int rele = 7;

//para calculos de comprimento de onda//
float lambdaEntreFaixa;
float lambdaVermelha; // comprimento de onda da comp Vermelha
float lambdaVerde; // comprimento de onda da comp Verde
float lambdaAzul; // comprimento de onda da comp Azul
float d = 0.915 * pow(10, -6); // parametro de rede
//float l = 0.1119; // dist da rede ao anteparo

//Definições Sensor de Proximidade Sharp////
int valSens;
float sharp;
float redPinSharp = 0;

//definições do conversor de frequencia
int period = 1000; // Miliseconds of each light frecuency measurement
int ScalingFactor = 1; // Scaling factor of this sensor
float area = PI * sqrt(0.91);
unsigned long counter = 0; // Counter of measurements during the test
unsigned long currentTime = millis();
unsigned long startTime = currentTime;
volatile long pulses = 0; // Counter of measurements of the TSL235R
unsigned long frequency; // Read the frequency from the digital pin (pulses/second)
float irradiance;

//definições para função de coleta de dados///
boolean ReceberColetaDados;

//sensor de cores//
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_60X);

void setup() {
  //  ReceberColetaDados = true;
  Serial.begin(9600);
  //  Serial.println("Mestrado TIDD - Analise Seus espectro");
  FreqCount.begin(1000);
  myStepper.setSpeed(10);
  pinMode(redPinSharp, OUTPUT);
  valSens = analogRead(redPinSharp);
  sharp = ((6762.0 / (valSens - 9.0)) - 3.7) * 0.010;
  pinMode(rele, OUTPUT); //Define o pino como saida
  delay(100);
  
ReceberColetaDados = false;

}

void loop() {
    ligar_motor();
  delay(200);
}

void DetectaCores() {
  //programação de inicialização do sensor detector de cores TCS34725 https://learn.adafruit.com/adafruit-color-sensors/program-it
  //Serial.println("Detectando cores");
  if (tcs.begin()) {
    //Serial.println("Sensor encontrado:");
  } else {
    //Serial.println("Sem TCS34725! Check conections!");
    while (1);
  }
}

void PulseCount() {
  pulses++;
}

void ColetaFrequencia() {
  //ReceberColetaDados = true;
  if (FreqCount.available()) {
    counter = FreqCount.read();
    attachInterrupt(0, PulseCount, RISING); {
      counter++; // Increase the number of measurement
      noInterrupts();
      frequency = counter / (period / 1000); // Calculate the frequency (pulses/second)
      interrupts(); // Request to measure the frequency
      irradiance = (frequency * 0.01) / area;  // Calculate Irradiance (uW/cm2)
      pulses = 0; // reset the pulses counter
      delay (100); // wait 4 seconds until the next measurement
    }
  }
}

void ColetaCores() {
  //ReceberColetaDados = true;
  //DetectaCores();
  uint16_t clearcol, red, green, blue;
  float average, r, g, b, lux;
  delay(100);
  tcs.getRawData(&red, &green, &blue, &clearcol);

  average = (red + green + blue) / 3;
  r = red / average;
  g = green / average;
  b = blue / average;

  //  Serial.print("\t NADA:"); Serial.print(clearcol);
  //  Serial.print("\t VERMELHO:");

  if ((r > 1.15) && (g < 0.90) && (b < 0.95)) {
    //Serial.print(" VERMELHO ");
  }
  else if ((r < 1.10) && (g > 0.85) && (b < 1.10)) {
    //Serial.print(" VERDE ");
  }
  else if ((r < 0.95) && (g < 0.95) && (b > 1.10)) {
    //Serial.print(" AZUL ");
  }
  else if ((0.60 < r < 1.10) && (0.85 < g < 1.10) && (1.00 < b < 1.50)) {
    //Serial.print(" BRANCO ");
  }
  else if ((r > 1.25) && (g > 0.99) && (b < 0.85)) {
    //Serial.print(" LARANJA ");
  }
  else if ((r < 0.60) && (g > 1.20) && (b > 1.20)) {
    //Serial.print(" VERDE CLARO ");
  }
  else if ((r > 0.45) && (g < 0.71) && (b > 1.85)) {
    //Serial.print(" VIOLETA CLARO ");
  }
  else if ((r > 1.10) && (g > 1.11) && (b < 0.85)) {
    //Serial.print(" LARANJA ESCURO ");
  }
  else if ((r < 0.55) && (g > 1.10) && (b > 1.35)) {
    //Serial.print(" AZUL CLARO ");
  }
  else if ((r > 0.5) && (g < 0.7) && (b > 1.75)) {
    //Serial.print(" MAGENTA ou FÚCSIA ");
  }
  else if ((r > 1.00) && (g > 1.15) && (b < 0.85)) {
    //Serial.print(" AMARELO ESCURO ");
  }
  else if ((r < 0.50) && (g > 1.00) && (b > 1.45)) {
    //Serial.print(" AZUL TURQUESA ");
  }
  else if ((r > 0.55) && (g < 0.70) && (b > 1.77)) {
    //Serial.print(" PINK ");
  }
  else if ((r > 0.95) && (g > 1.20) && (b < 0.85)) {
    //Serial.print(" AMARELO ");
  }
  else if ((r < 0.49) && (g > 1.03) && (b > 1.44)) {
    //Serial.print(" CIANO ou VERDE-AGUA ");
  }
  else if ((r > 0.60) && (g < 0.70) && (b > 1.65)) {
    //Serial.print(" VIOLETA ");
  }
  else {
    //Serial.print(" NENHUMA COR ENCONTRADA ");
  }

  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.print(b);
  Serial.print("\n");
  delay(100);

}

void(*resetFunc)(void) = 0;
void PararCliente() {
  delay(200);
  setup();

}

void lambda_compVermelha() {
  ReceberColetaDados = true;
  float moveVermelho = 0.0985; //é a diferença entre a posição original e o que o motor fez a comp se mover, nesse caso, 9-0 = 9cm
  lambdaVermelha = ((d * (moveVermelho)) / sqrt(pow(sharp, 2) + pow(moveVermelho, 2))) * pow(10, 9);
  delay(100);
}
void lambda_compVerde() {
  ReceberColetaDados = true;
  //float ang_pas_bas = 1.8/2;
  //float passos = 13;
  float moveVerde = 0.0745; //abs(0.0985-(sharp*(tan(passos*(ang_pas_bas))))); //é a diferença entre a posição original e o que o motor fez a comp se mover, nesse caso, 9,85 -    = 7,55cm
  lambdaVerde = ((d * (moveVerde)) / sqrt(pow(sharp, 2) + pow(moveVerde, 2))) * pow(10, 9);
  delay(100);
}
void lambda_compAzul() {
  ReceberColetaDados = true;
  //float ang_pas_bas = 1.8/2;
  //float passos = 19;
  float moveAzul = 0.058; //abs(0.0985-(sharp*(tan(passos*(ang_pas_bas))))); //é a diferença entre a posição original e o que o motor fez a comp se mover, nesse caso, 9,85 -  = 5,85cm
  lambdaAzul = ((d * (moveAzul)) / sqrt(pow(sharp, 2) + pow(moveAzul, 2))) * pow(10, 9);
  delay(100);

  /*OBS: na passagem entre as comps verde e azul a referência passa a ser a comp verde.
    Contudo, frente a distancia ser 6,9, a distância a ser considerada na moveAzul
    será de 6,9-(3,2-2,1) = 5,8cm, igual.*/
}
//
void posiciona_motor_vermelho() {
  ReceberColetaDados = true;
  delay(500);
  myStepper.step(0);
  lambda_compVermelha();
  ColetaFrequencia();
  Serial.print(lambdaVermelha, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);//para leitura da comp vermelha
  myStepper.step(0); //volta à posição original
  //PararCliente();
}
void posiciona_motor_verde() {
  ReceberColetaDados = true;
  delay(500);
  lambda_compVerde();
  ColetaFrequencia();
  myStepper.step(-(13)); // para leitura da comp verde (a partir da cond inicial).
  Serial.print(lambdaVerde, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);
  myStepper.step((13)); // volta à posição original
  //PararCliente();
}
void posiciona_motor_azul() {
  ReceberColetaDados = true;
  delay(500);
  myStepper.step(-(18)); // para leitura da comp azul (a partir da con inicial)
  lambda_compAzul();
  ColetaFrequencia();
  Serial.print(lambdaAzul, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);
  myStepper.step((18)); // volta à posição original
  //PararCliente();
}
void posiciona_motor_branco() {
  ReceberColetaDados = true;
  //branco
  delay(500);
  myStepper.step(-(18));
  lambda_compVermelha();
  ColetaFrequencia();
  Serial.print(lambdaVermelha, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  lambda_compVerde();
  ColetaFrequencia();
  Serial.print(lambdaVerde, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  lambda_compAzul();
  ColetaFrequencia();
  Serial.print(lambdaAzul, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);
  myStepper.step((18)); // volta à posição original
  //PararCliente();
}

void posiciona_motor_comb1() { //comb1 = vermelho + verde
  ReceberColetaDados = true;
  //vermelha e verde
  delay(500);
  myStepper.step(-(13));
  lambda_compVermelha();
  ColetaFrequencia();
  Serial.print(lambdaVermelha, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  lambda_compVerde();
  ColetaFrequencia();
  Serial.print(lambdaVerde, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);
  myStepper.step(13); // para leitura da comp verde - considerando a partir da comp vermelha.
  //PararCliente();
}
void posiciona_motor_comb2() { // comb2 = verde + azul
  ReceberColetaDados = true;
  // verde
  delay(500);
  myStepper.step(-(13)); // para leitura da comp verde - considerando a partir da comp vermelha.
  lambda_compVerde();
  ColetaFrequencia();
  Serial.print(lambdaVerde, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);
  //azul
  delay(500);
  myStepper.step(-(5)); // para leitura da comp azul - considerando a partir da comp verde.
  lambda_compAzul();
  ColetaFrequencia();
  Serial.print(lambdaAzul, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);
  myStepper.step(18); // volta à posição original
  //PararCliente();
}

void posiciona_motor_comb3() { // comb3 = vermelho + azul
  ReceberColetaDados = true;
  //vermelho
  delay(500);
  myStepper.step(0);
  lambda_compVermelha();
  ColetaFrequencia();
  Serial.print(lambdaVermelha, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);//para leitura da comp vermelha
  //AZUL
  delay(500);
  stepCount++;
  lambda_compAzul();
  ColetaFrequencia();
  myStepper.step(-(18)); // para leitura da comp azul - considerando a partir da comp verde.
  Serial.print(lambdaAzul, 2);
  Serial.print(",");
  Serial.print(irradiance, 2);
  Serial.print(",");
  ColetaCores();
  delay(2000);
  myStepper.step((19)); // volta à posição original
  //PararCliente();
  delay(500);
}

void ligar_motor() {
  ReceberColetaDados = true;
  if (Serial.available() > 0) {
    char tecla = Serial.read();

    if (tecla == '1') {
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFFA05F, 32); // Sony TV power code
        delay(200);
      }
      delay(200);
      //Serial.println ("Aumenta Brilho");
    }
    if (tecla == '0') {
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFF20DF, 32); // Sony TV power code
        delay(200);
      }
      delay(200);
      //Serial.println ("Diminui Brilho");
    }
    if (tecla == 'D') {
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFF609F, 32); // Sony TV power code
        delay(400);
        //Serial.println("P");
      }
      delay(200);
      //      digitalWrite(rele, LOW); //Desliga o rele
      //      delay(5000); //Aguarda 3 segundos e reinicia o processo
      PararCliente();
      //      Serial.println ("Ate a proxima!");
    }
    if (tecla == 'L') {
      Serial.println("I");
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFFE01F, 32); // Sony TV power code
        ReceberColetaDados = false;
        //Serial.println ("L");
        delay(400);
      }
      digitalWrite(rele, HIGH); //Aciona o rele
      delay(1000); //Aguarda 5 segundos
      delay(200);
      //Serial.println ("Dispositivo pronto para coletar dados!");
    }
    if (tecla == 'R') {
      Serial.println("I");
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFF906F, 32); // Sony TV power code
        delay(400);
        //Serial.println ("Vermelho");
        posiciona_motor_vermelho();
      }
      delay(30);
    }
    if (tecla == 'G') {
      Serial.println("I");
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFF10EF, 32); // Sony TV power code
        delay(400);
        //        Serial.println ("Verde");
        posiciona_motor_verde();
      }
      delay(30);
    }
    if (tecla == 'B') {
     Serial.println("I");
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFF50AF, 32); // Sony TV power code
        delay(400);
        //        Serial.println ("Azul");
        posiciona_motor_azul();
      }
      delay(30);
    }
    if (tecla == 'W') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFFD02F, 32); // Sony TV power code
        delay(400);
        //      Serial.println ("Branco");
        stepCount++;
        posiciona_motor_branco();
      }
      delay(30);
    }
    if (tecla == 'o') {
      Serial.println("I");
      int i = 0;
      while ((i <= 2)){
        i++;
        //ReceberColetaDados = false;
        irsend.sendNEC(0xFFB04F, 32); // Sony TV power code
        delay(400);
        //    Serial.println ("Laranja");
        posiciona_motor_comb1();
      }
      delay(30);
    }
    if (tecla == 'g') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF30CF, 32); // Sony TV power code
        delay(400);
        //  Serial.println ("Verde Claro");
        posiciona_motor_comb2();
      }
      delay(30);
    }
    if (tecla == 'b') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF708F, 32); // Sony TV power code
        delay(400);
        //Serial.println ("Violeta Claro");
        posiciona_motor_comb3();
      }
      delay(30);
    }
    if (tecla == 'F') {
      Serial.println("I");
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFF00F, 32); // Sony TV power code
        delay(400);
        //Serial.println ("Flash");
      }
    }
    if (tecla == 'O') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFFA857, 32); // Sony TV power code
        delay(400);
        //Serial.println ("Laranja Escuro");
        posiciona_motor_comb1();
      }
      delay(30);
    }
    if (tecla == 'z') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF28D7, 32); // Sony TV power code
        delay(400);
        //        Serial.println ("Azul Claro");
        posiciona_motor_comb2();
      }
      delay(30);
    }
    if (tecla == 'x') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF6897, 32); // Sony TV power code
        delay(400);
        //      Serial.println ("Roxo");
        posiciona_motor_comb3();
      }
      delay(30);
    }
    if (tecla == 'S') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFE817, 32); // Sony TV power code
        delay(400);
        //  Serial.println ("Estrobo");
      }
    }
    if (tecla == 'y') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF9867, 32); // Sony TV power code
        delay(400);
        //        Serial.println ("Amarelo Escuro");
        posiciona_motor_comb1();
      }
      delay(30);
    }
    if (tecla == 'c') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF18E7, 32); // Sony TV power code
        delay(400);
        //      Serial.println ("Azul Turquesa");
        posiciona_motor_comb2();
      }
      delay(30);
    }
    if (tecla == 'K') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF58A7, 32); // Sony TV power code
        delay(400);
        //    Serial.println ("Pink");
        posiciona_motor_comb3();
      }
      delay(30);
    }
    if (tecla == '<') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFD827, 32); // Sony TV power code
        delay(400);
      }
      //Serial.println ("Fade");
    }
    if (tecla == 'Y') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF8877, 32); // Sony TV power code
        delay(400);
        //Serial.println ("Amarelo");
        posiciona_motor_comb1();
      }
      delay(30);
    }
    if (tecla == 'C') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF08F7, 32); // Sony TV power code
        delay(400);
        //      Serial.println ("Verde-Agua");
        posiciona_motor_comb2();
      }
      delay(30);
    }
    if (tecla == 'V') {
      Serial.println("I");
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF48B7, 32); // Sony TV power code
        delay(400);
        //    Serial.println ("Violeta");
        posiciona_motor_comb3();
      }
      delay(30);
    }
    if (tecla == '-') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFC837, 32); // Sony TV power code
        delay(400);
      }
      //Serial.println ("Smooth");
    }
    //Serial.println("F");
  }
}
