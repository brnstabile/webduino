#include <Stepper.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"

#include <IRremote.h>
#include <IRremoteInt.h>
IRsend irsend;

//variaveis de passos para giro do motor//
const int stepsPerRevolution = 48;
Stepper myStepper(stepsPerRevolution, 22, 23, 24, 25);
int passos; // numero de passos necessarios para mover o motor para a proxima posicao
int posicaoAtual;
int posicaoFutura;

//para calculos de comprimento de onda//
float lambdaVermelha; // comprimento de onda da raia Vermelha
float lambdaVerde; // comprimento de onda da raia Verde
float lambdaAzul; // comprimento de onda da raia Azul
float d = pow(10, -6); // parametro de rede
float l = 0.112; // dist da rede ao anteparo

boolean ReceberColetaDados;

//sensor de cores//
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_60X);

//para acionar ethernet//
//byte ip[] = { 192, 168, 1, 51 };   //setup manual apenas
//// Caso seja necessário mudar o valor do endereço MAC (muito raro)//
//byte mac[] = { 0xAB, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//EthernetServer server(80); //porta '80'
//EthernetClient client = server.available();
////obs:  Pinos 10,11,12 & 13 sáo usados pela ethernet shield



void setup() {
  Serial.begin(9600);
  Serial.println("Mestrado TIDD - Analise Seus espectro");
  myStepper.setSpeed(40);
  delay(100);
  DetectaCores();


//  ///////ETHERNET//////////////
//  Ethernet.begin(mac); //Ethernet.begin(mac, ip, gateway, subnet); //for manual setup
//  server.begin();
//  delay(10);
//  Serial.println(Ethernet.localIP());
//  Serial.println("conectando");
}


void loop() {
  ligar_motor();
  delay(200);
  int client = Serial.available();
  if (client) {
    Serial.println("novo cliente");
    char c = Serial.read();
    if (c == 'i') { // Testamos se os bytes que vieram do Client conectado sao para uma nova coleta
      IniciarColeta();
    }
  }
  if (ReceberColetaDados == true) {
    ColetaDados();
    ColetaCores();
  }
}


void IniciarColeta() {
  ReceberColetaDados = true;
  Serial.println("Coleta de Dados do Experimento");
  //myStepper.step(-(stepsPerRevolution));
  delay(100);
}

void ColetaDados() {
  ReceberColetaDados = true;
  delay(10);
  //myStepper.step(-(stepsPerRevolution));
  delay(100);
  myStepper.step(0);
  int geralPassos = 0;
  delay(1000);
  Serial.println("Pronto Para comecar!");
}

void DetectaCores(){
    //programação de inicialização do sensor detector de cores TCS34725 https://learn.adafruit.com/adafruit-color-sensors/program-it
  Serial.println("Detectando cores");
  if (tcs.begin()) {
    Serial.println("Sensor encontrado:");
  } else {
    Serial.println("Sem TCS34725! Check conections!");
    while (1);
  }
}

void ColetaCores() {
  ReceberColetaDados = true;  
  uint16_t clearcol, red, green, blue;
  float average, r, g, b;
  delay(100);
  tcs.getRawData(&red, &green, &blue, &clearcol);

  average = (red + green + blue) / 3;
  r = red / average;
  g = green / average;
  b = blue / average;
  Serial.print("\t NADA:"); Serial.print(clearcol);
  Serial.print("\t VERMELHO:"); Serial.print(r);
  Serial.print("\t VERDE:"); Serial.print(g);
  Serial.print("\t AZUL:"); Serial.print(b);

  if ((r > 1.7) && (g < 1.0) && (b < 1.0)) {
    Serial.print("\t VERMELHO");
  }
  else if ((r < 0.7) && (g > 1.50) && (b < 1.20)) {
    Serial.print("\t VERDE");
  }
  else if ((r < 0.5) && (g < 1.5) && (b > 1.45)) {
    Serial.print("\t AZUL");
  }
  else {
    Serial.print("\t NENHUMA COR ENCONTRADA");
  }

  Serial.println(" ");
  delay(100);
}


void(*resetFunc)(void) = 0;
void PararCliente() {
  delay(200);
  Serial.println("resetando...");
  resetFunc();
  delay(100);
  Serial.println("OK. Pronto para novo Cliente");
}


void lambda_raiaVermelha() {
  lambdaVermelha = ((d * 0.09) / sqrt(pow(l, 2) + pow(0.09, 2))) * pow(10, 9);
  delay(100);
}
void lambda_raiaVerde() {
  lambdaVerde = (((d * 0.107) / sqrt(pow(l, 2) + pow(0.107, 2))) - sin((((d * 0.107) / sqrt(pow(l, 2) + pow(0.107, 2))) - ((d * 0.07) / sqrt(pow(l, 2) + pow(0.07, 2)))))) * pow(10, 9);
  delay(100);
}
void lambda_raiaAzul() {
  lambdaAzul = (((d * 0.12) / sqrt(pow(l, 2) + pow(0.12, 2))) - sin((((d * 0.12) / sqrt(pow(l, 2) + pow(0.12, 2))) - ((d * 0.059) / sqrt(pow(l, 2) + pow(0.059, 2)))))) * pow(10, 9);
  delay(100);
}

void posiciona_motor_vermelho() {
  delay(500);
  myStepper.step(0);
  lambda_raiaVermelha();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVermelha, DEC);
  delay(2000);//para leitura da raia vermelha
  ColetaCores();
  delay(500);
  myStepper.step(0); //volta à posição original
  PararCliente();
  delay(2000);
  Serial.println("Proximo Cliente...");
}
void posiciona_motor_verde() {
  delay(500);
  myStepper.step(-(3)); // para leitura da raia verde (a partir da cond inicial).
  lambda_raiaVerde();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVerde, DEC);
  delay(2000);
  ColetaCores();
  delay(500);
  myStepper.step((3)); // volta à posição original
  PararCliente();
  delay(2000);
  Serial.println("Proximo Cliente...");
}
void posiciona_motor_azul() {
  delay(500);
  myStepper.step(-(5)); // para leitura da raia azul (a partir da con inicial)
  lambda_raiaAzul();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaAzul, DEC);
  delay(2000);
  ColetaCores();
  delay(500);
  myStepper.step((5)); // volta à posição original
  PararCliente();
  delay(2000);
  Serial.println("Proximo Cliente...");
}
void posiciona_motor_branco() {
  //vermelho
  delay(500);
  myStepper.step(0);
  lambda_raiaVermelha();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVermelha, DEC);
  delay(2000);//para leitura da raia vermelha
  ColetaCores();
  delay(500);
  //verde
  delay(500);
  myStepper.step(-(3)); // para leitura da raia verde - considerando a partir da raia vermelha.
  lambda_raiaVerde();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVerde, DEC);
  ColetaCores();
  delay(2000);
  //azul
  delay(500);
  myStepper.step(-(2)); // para leitura da raia azul - considerando a partir da raia verde.
  lambda_raiaAzul();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaAzul, DEC);
  ColetaCores();
  delay(2000);
  myStepper.step((5)); // volta à posição original
  PararCliente();
  delay(2000);
  Serial.println("Proximo Cliente...");
}

void posiciona_motor_comb1() { //comb1 = vermelho + verde
  //vermelha
  delay(500);
  myStepper.step(0);
  lambda_raiaVermelha();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVermelha, DEC);
  ColetaCores();
  delay(2000);//para leitura da raia vermelha
  //verde
  delay(500);
  myStepper.step(-(3)); // para leitura da raia verde - considerando a partir da raia vermelha.
  lambda_raiaVerde();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVerde, DEC);
  ColetaCores();
  delay(2000);
  myStepper.step((3)); // volta ao inicio.
  PararCliente();
  delay(500);
  Serial.println("Proximo Cliente...");
}
void posiciona_motor_comb2() { // comb2 = verde + azul
  // verde
  delay(500);
  myStepper.step(-(3));// para leitura da raia verde - considerando a partir da raia vermelha.
  lambda_raiaVerde();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVerde, DEC);
  ColetaCores();
  delay(500);//para leitura da raia verde
  //azul
  delay(500);
  myStepper.step(-(2)); // para leitura da raia azul - considerando a partir da raia verde.
  lambda_raiaAzul();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaAzul, DEC);
  ColetaCores();
  delay(2000);
  myStepper.step((5)); // volta ao inicio.
  PararCliente();
  delay(2000);
  Serial.println("Proximo Cliente...");
}
void posiciona_motor_comb3() { // comb3 = vermelho + azul
  //vermelho
  delay(500);
  myStepper.step(0);
  lambda_raiaVermelha();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaVermelha, DEC);
  ColetaCores();
  delay(2000);
  //AZUL
  delay(500);//para leitura da raia vermelha
  myStepper.step(-(5)); // para leitura da raia verde - considerando a partir da raia vermelha.
  lambda_raiaAzul();
  Serial.print("Comprimento de Onda = ");
  Serial.print(" ");
  Serial.println(lambdaAzul, DEC);
  ColetaCores();
  delay(2000);
  myStepper.step((5)); // volta ao inicio.
  PararCliente();
  delay(2000);
  Serial.println("Proximo Cliente...");
}

void ligar_motor() {
  if (Serial.available() > 0) {
    char tecla = Serial.read();
    if (tecla == '1') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFA05F, 32); // Sony TV power code
        delay(200);
      }
      delay(200);
      Serial.println ("Aumenta Brilho");
    }
    if (tecla == '0') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF20DF, 32); // Sony TV power code
        delay(200);
      }
      delay(200);
      Serial.println ("Diminui Brilho");
    }
    if (tecla == 'D') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF609F, 32); // Sony TV power code
        delay(400);
        Serial.println ("DESLIGA");
      }
      myStepper.step(-2*(stepsPerRevolution));
      delay(200);
      PararCliente();
      Serial.println ("Ate a proxima!");
    }
    if (tecla == 'L') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFE01F, 32); // Sony TV power code
        Serial.println ("LIGA");
        delay(400);
      }
      //IniciarColeta();
      ColetaDados();
      Serial.println ("Dispositivo pronto para coletar dados!");
    }
    if (tecla == 'R') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF906F, 32); // Sony TV power code
        delay(400);
      }
      Serial.println ("Vermelho");
      posiciona_motor_vermelho();
      delay(30);
    }
    if (tecla == 'G') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF10EF, 32); // Sony TV power code
        delay(400);
        Serial.println ("Verde");
      }
      posiciona_motor_verde();
      delay(30);
    }
    if (tecla == 'B') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF50AF, 32); // Sony TV power code
        delay(400);
        Serial.println ("Azul");
      }
      posiciona_motor_azul();
      delay(30);
    }
    if (tecla == 'W') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFD02F, 32); // Sony TV power code
        delay(400);
        Serial.println ("Branco");
      }
      posiciona_motor_branco();
      delay(30);
    }
    if (tecla == 'o') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFB04F, 32); // Sony TV power code
        delay(400);
        Serial.println ("Laranja");
      }
      posiciona_motor_comb1();
      delay(30);
    }
    if (tecla == 'g') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF30CF, 32); // Sony TV power code
        delay(400);
        Serial.println ("Verde Claro");
      }
      posiciona_motor_comb2();
      delay(30);
    }
    if (tecla == 'b') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF708F, 32); // Sony TV power code
        delay(400);
        Serial.println ("Azul Esmeralda");
      }
      posiciona_motor_comb3();
      delay(30);
    }
    if (tecla == 'F') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFF00F, 32); // Sony TV power code
        delay(400);
      }
      Serial.println ("Flash");
    }
    if (tecla == 'O') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFA857, 32); // Sony TV power code
        delay(400);
        Serial.println ("Laranja Escuro");
      }
      posiciona_motor_comb1();
      delay(30);
    }
    if (tecla == 'z') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF28D7, 32); // Sony TV power code
        delay(400);
        Serial.println ("Azul Anil");
      }
      posiciona_motor_comb2();
      delay(30);
    }
    if (tecla == 'x') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF6897, 32); // Sony TV power code
        delay(400);
        Serial.println ("Roxo");
      }
      posiciona_motor_comb3();
      delay(30);
    }
    if (tecla == 'S') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFE817, 32); // Sony TV power code
        delay(400);
      }
      Serial.println ("Estrobo");
    }
    if (tecla == 'y') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF9867, 32); // Sony TV power code
        delay(400);
        Serial.println ("Amarelo Claro");
      }
      posiciona_motor_comb1();
      delay(30);
    }
    if (tecla == 'c') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF18E7, 32); // Sony TV power code
        delay(400);
        Serial.println ("Azul Turquesa");
      }
      posiciona_motor_comb2();
      delay(30);
    }
    if (tecla == 'P') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF58A7, 32); // Sony TV power code
        delay(400);
        Serial.println ("Pink");
      }
      posiciona_motor_comb3();
      delay(30);
    }
    if (tecla == '<') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFD827, 32); // Sony TV power code
        delay(400);
      }
      Serial.println ("Fade");
    }
    if (tecla == 'Y') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF8877, 32); // Sony TV power code
        delay(400);
        Serial.println ("Amarelo");
      }
      posiciona_motor_comb1();
      delay(30);
    }
    if (tecla == 'C') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF08F7, 32); // Sony TV power code
        delay(400);
        Serial.println ("Verde-Agua");
      }
      posiciona_motor_comb2();
      delay(30);
    }
    if (tecla == 'V') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFF48B7, 32); // Sony TV power code
        delay(400);
        Serial.println ("Violeta");
      }
      posiciona_motor_comb3();
      delay(30);
    }
    if (tecla == '-') {
      for (int i = 0; i < 1; i++) {
        irsend.sendNEC(0xFFC837, 32); // Sony TV power code
        delay(400);
      }
      Serial.println ("Smooth");
    }
    Serial.println("\n");
  }
}
