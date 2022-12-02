//DECLARAÇÃO DAS VARIAVEIS//
// declaração sensor RGB
#define pinS0 12
#define pinS1 13
#define pinS2 11
#define pinS3 10
#define pinOut 9

//declaração dos motores - sentidos
#define MotorDireita_velocidade 6//IN1
#define MotorDireita_SentidoFrente 4//IN2 -DIREITA
#define MotorEsquerda_SentidoFrente 7//IN4- ESQUERDA
#define MotorEsquerda_velocidade 5
// Declaração sensor infravermelho na base do carrinho
#define Sensor_Infravermelho_Direita A0
#define Sensor_Infravermelho_esquerda A1
bool direita = 0;
bool esquerda = 0;
//declaração das velocidade do motor

int velocidade110 = 160;
int velocidade0 = 255;
int velocidade100= 130;

// declaração variaveis cores

unsigned int valorVermelho = 0;
unsigned int valorVerde = 0;
unsigned int valorAzul = 0;
unsigned int valorBranco = 0;

void detectaCor();
void paraCarrinho();
void carrinhoAnda();

void setup() {
  Serial.begin(9600);

  // Motores
  pinMode(MotorDireita_velocidade, OUTPUT);
  pinMode(MotorEsquerda_velocidade, OUTPUT);
  pinMode(MotorDireita_SentidoFrente, OUTPUT);
  pinMode(MotorEsquerda_SentidoFrente, OUTPUT);
  pinMode(Sensor_Infravermelho_Direita, INPUT);
  pinMode(Sensor_Infravermelho_esquerda, INPUT);
  
  // Sensor RGB
  pinMode(pinS0, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  pinMode(pinOut, INPUT);

  digitalWrite(pinS0, HIGH);
  digitalWrite(pinS1, LOW);
  
  //Define o sentido de rotação dos motores
  digitalWrite(MotorDireita_SentidoFrente, HIGH);//MOTOR DIREITA FRENTE -HIGH
  digitalWrite(MotorEsquerda_SentidoFrente, HIGH); //MOTOR ESQUERDO FRENTE - HIGH
}

void loop() {

//Leituras dos Sensores
  direita = digitalRead(Sensor_Infravermelho_Direita);
  esquerda = digitalRead(Sensor_Infravermelho_esquerda);
  
  
//Rodando os motores dependendo das leituras
if(direita == 0 && esquerda == 0){
   analogWrite(MotorDireita_velocidade, velocidade110);
   analogWrite(MotorEsquerda_velocidade, velocidade110);

}else if(direita == 0 && esquerda == 1){
    
  analogWrite(MotorDireita_velocidade, velocidade110);
  analogWrite(MotorEsquerda_velocidade, velocidade0);

}else if(direita == 1 && esquerda == 0){
  analogWrite(MotorDireita_velocidade, velocidade0);
  analogWrite(MotorEsquerda_velocidade, velocidade110);

}else if(direita == 1 && esquerda == 1){
  analogWrite(MotorDireita_velocidade, velocidade0);
  analogWrite(MotorEsquerda_velocidade, velocidade0);
}
  detectaCor();

  //Verifica se a cor vermelha foi detectada
  if ((valorVermelho < valorAzul) &&
      (valorVermelho < valorVerde) &&
      (valorBranco < 100)) {
    Serial.println("Vermelho");
    paraCarrinho();

  } else if ((valorVerde < valorVermelho) &&  //Verifica se a cor verde foi detectada
             (valorVerde < valorAzul) &&
             (valorBranco < 100)) {
    Serial.println("Verde");
    carrinhoAnda();
  }
  Serial.println();
}

void detectaCor() {

 //Vermelho
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);
  valorVermelho = pulseIn(pinOut, LOW);
  //Azul
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, HIGH);
  valorAzul = pulseIn(pinOut, LOW);
  //Verde
  digitalWrite(pinS2,HIGH);
  digitalWrite(pinS3,HIGH);
  valorVerde = pulseIn(pinOut, LOW);
}

void paraCarrinho(){
    analogWrite(MotorDireita_velocidade, velocidade0);
    analogWrite(MotorEsquerda_velocidade, velocidade0);
}

void carrinhoAnda(){
    analogWrite(MotorDireita_velocidade, velocidade110);
    analogWrite(MotorEsquerda_velocidade, velocidade110);
}
