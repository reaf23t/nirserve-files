// BASE DO ROBODELTINHATECNIZINHO🫡
// ============================================
// ROBÔ 4 RODAS COM SENSOR ULTRASSÔNICO
// E SEGUIDORES DE LINHA
// ============================================

#include <Servo.h>

// ============================================
// PINOS DOS MOTORES
// ============================================
#define MOTOR1_PIN1 2
#define MOTOR1_PIN2 3
#define MOTOR2_PIN1 4
#define MOTOR2_PIN2 5
#define MOTOR3_PIN1 6
#define MOTOR3_PIN2 7
#define MOTOR4_PIN1 8
#define MOTOR4_PIN2 9

// ============================================
// PINOS DO SENSOR ULTRASSÔNICO
// ============================================
#define TRIG_PIN 10
#define ECHO_PIN 11

// ============================================
// PINOS DOS SEGUIDORES DE LINHA
// ============================================
#define SENSOR_LINHA_ESQUERDA A0
#define SENSOR_LINHA_DIREITA A1

// ============================================
// PINOS DE CONTROLE PWM (velocidade)
// ============================================
#define MOTOR1_PWM 12
#define MOTOR2_PWM A2
#define MOTOR3_PWM A3
#define MOTOR4_PWM A4

// ============================================
// CONSTANTES
// ============================================
#define VELOCIDADE_MAXIMA 255
#define DISTANCIA_MINIMA 20 // em cm
#define LIMIAR_LINHA 500    // ajuste conforme necessário

// ============================================
// VARIÁVEIS GLOBAIS
// ============================================
int velocidadeMotor1 = 0;
int velocidadeMotor2 = 0;
int velocidadeMotor3 = 0;
int velocidadeMotor4 = 0;

// ============================================
// SETUP
// ============================================
void setup() {
  Serial.begin(9600);
  
  // Configurar pinos dos motores como saída
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  pinMode(MOTOR3_PIN1, OUTPUT);
  pinMode(MOTOR3_PIN2, OUTPUT);
  pinMode(MOTOR4_PIN1, OUTPUT);
  pinMode(MOTOR4_PIN2, OUTPUT);
  
  // Configurar pinos PWM como saída
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR2_PWM, OUTPUT);
  pinMode(MOTOR3_PWM, OUTPUT);
  pinMode(MOTOR4_PWM, OUTPUT);
  
  // Configurar sensor ultrassônico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Configurar seguidores de linha
  pinMode(SENSOR_LINHA_ESQUERDA, INPUT);
  pinMode(SENSOR_LINHA_DIREITA, INPUT);
  
  delay(1000);
  Serial.println("Robô iniciado!");
}

// ============================================
// LOOP PRINCIPAL
// ============================================
void loop() {
  // Ler sensores
  float distancia = medirDistancia();
  int sensorEsq = analogRead(SENSOR_LINHA_ESQUERDA);
  int sensorDir = analogRead(SENSOR_LINHA_DIREITA);
  
  // Exibir informações
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.print(" cm | Esq: ");
  Serial.print(sensorEsq);
  Serial.print(" | Dir: ");
  Serial.println(sensorDir);
  
  // Lógica de controle
  if (distancia < DISTANCIA_MINIMA) {
    // Se detectar obstáculo, parar
    pararRobo();
    Serial.println("OBSTÁCULO DETECTADO!");
    delay(500);
    // Fazer curva para evitar
    girarParaDireita(150);
    delay(600);
  } 
  else {
    // Seguir linha
    seguirLinha(sensorEsq, sensorDir);
  }
  
  delay(100);
}

// ============================================
// FUNÇÃO: MEDIR DISTÂNCIA (Sensor Ultrassônico)
// ============================================
float medirDistancia() {
  // Enviar pulso
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Medir tempo de resposta
  long duracao = pulseIn(ECHO_PIN, HIGH, 30000);
  
  // Calcular distância (velocidade do som = 343 m/s)
  float distancia = (duracao * 0.0343) / 2;
  
  return distancia;
}

// ============================================
// FUNÇÃO: CONTROLAR MOTOR INDIVIDUAL
// ============================================
void controlarMotor(int motor, int velocidade, boolean direcao) {
  velocidade = constrain(velocidade, 0, 255);
  
  switch(motor) {
    case 1:
      digitalWrite(MOTOR1_PIN1, direcao ? HIGH : LOW);
      digitalWrite(MOTOR1_PIN2, direcao ? LOW : HIGH);
      analogWrite(MOTOR1_PWM, velocidade);
      break;
    case 2:
      digitalWrite(MOTOR2_PIN1, direcao ? HIGH : LOW);
      digitalWrite(MOTOR2_PIN2, direcao ? LOW : HIGH);
      analogWrite(MOTOR2_PWM, velocidade);
      break;
    case 3:
      digitalWrite(MOTOR3_PIN1, direcao ? HIGH : LOW);
      digitalWrite(MOTOR3_PIN2, direcao ? LOW : HIGH);
      analogWrite(MOTOR3_PWM, velocidade);
      break;
    case 4:
      digitalWrite(MOTOR4_PIN1, direcao ? HIGH : LOW);
      digitalWrite(MOTOR4_PIN2, direcao ? LOW : HIGH);
      analogWrite(MOTOR4_PWM, velocidade);
      break;
  }
}

// ============================================
// FUNÇÃO: ANDAR PARA FRENTE
// ============================================
void andarFrente(int velocidade) {
  controlarMotor(1, velocidade, true);
  controlarMotor(2, velocidade, true);
  controlarMotor(3, velocidade, true);
  controlarMotor(4, velocidade, true);
  Serial.println("➡ Andando para frente");
}

// ============================================
// FUNÇÃO: ANDAR PARA TRÁS
// ============================================
void andarTras(int velocidade) {
  controlarMotor(1, velocidade, false);
  controlarMotor(2, velocidade, false);
  controlarMotor(3, velocidade, false);
  controlarMotor(4, velocidade, false);
  Serial.println("⬅ Andando para trás");
}

// ============================================
// FUNÇÃO: GIRAR PARA DIREITA
// ============================================
void girarParaDireita(int velocidade) {
  controlarMotor(1, velocidade, true);
  controlarMotor(2, velocidade, true);
  controlarMotor(3, velocidade, false);
  controlarMotor(4, velocidade, false);
  Serial.println("↻ Girando para direita");
}

// ============================================
// FUNÇÃO: GIRAR PARA ESQUERDA
// ============================================
void girarParaEsquerda(int velocidade) {
  controlarMotor(1, velocidade, false);
  controlarMotor(2, velocidade, false);
  controlarMotor(3, velocidade, true);
  controlarMotor(4, velocidade, true);
  Serial.println("↺ Girando para esquerda");
}

// ============================================
// FUNÇÃO: MOVIMENTO LATERAL 45°
// (Mover para direita em diagonal)
// ============================================
void moverLateral45Direita(int velocidade) {
  // Roda esquerda frente, roda direita parada
  controlarMotor(1, velocidade, true);    // Frente esquerda
  controlarMotor(2, velocidade, true);    // Frente esquerda
  controlarMotor(3, 0, false);             // Parado direita
  controlarMotor(4, 0, false);             // Parado direita
  Serial.println("↗ Movimento lateral 45° para direita");
}

// ============================================
// FUNÇÃO: MOVIMENTO LATERAL 45°
// (Mover para esquerda em diagonal)
// ============================================
void moverLateral45Esquerda(int velocidade) {
  // Roda direita frente, roda esquerda parada
  controlarMotor(1, 0, false);             // Parado esquerda
  controlarMotor(2, 0, false);             // Parado esquerda
  controlarMotor(3, velocidade, true);    // Frente direita
  controlarMotor(4, velocidade, true);    // Frente direita
  Serial.println("↖ Movimento lateral 45° para esquerda");
}

// ============================================
// FUNÇÃO: PARAR ROBÔ
// ============================================
void pararRobo() {
  controlarMotor(1, 0, false);
  controlarMotor(2, 0, false);
  controlarMotor(3, 0, false);
  controlarMotor(4, 0, false);
  Serial.println("⏹ Robô parado");
}

// ============================================
// FUNÇÃO: SEGUIR LINHA
// ============================================
void seguirLinha(int sensorEsq, int sensorDir) {
  boolean linhaEsq = sensorEsq > LIMIAR_LINHA;
  boolean linhaDir = sensorDir > LIMIAR_LINHA;
  
  if (linhaEsq && linhaDir) {
    // Ambos na linha: ir reto
    andarFrente(180);
  } 
  else if (linhaEsq && !linhaDir) {
    // Linha à esquerda: corrigir para esquerda
    girarParaEsquerda(150);
    Serial.println("Corrigindo para esquerda");
  } 
  else if (!linhaEsq && linhaDir) {
    // Linha à direita: corrigir para direita
    girarParaDireita(150);
    Serial.println("Corrigindo para direita");
  } 
  else {
    // Sem linha: procurar
    girarParaDireita(120);
    Serial.println("Procurando linha...");
  }
}

// ============================================
// FUNÇÃO: CALIBRAR SENSORES
// ============================================
void calibrarSensores() {
  Serial.println("Calibrando sensores de linha...");
  for (int i = 0; i < 10; i++) {
    int esq = analogRead(SENSOR_LINHA_ESQUERDA);
    int dir = analogRead(SENSOR_LINHA_DIREITA);
    Serial.print("Leitura ");
    Serial.print(i + 1);
    Serial.print(" - Esq: ");
    Serial.print(esq);
    Serial.print(" | Dir: ");
    Serial.println(dir);
    delay(500);
  }
  Serial.println("Calibração concluída!");
}

// ============================================
// FUNÇÃO: TESTE DE MOTORES
// ============================================
void testarMotores() {
  Serial.println("\n=== TESTE DE MOTORES ===\n");
  
  Serial.println("Testando Motor 1...");
  controlarMotor(1, 200, true);
  delay(2000);
  controlarMotor(1, 0, false);
  delay(500);
  
  Serial.println("Testando Motor 2...");
  controlarMotor(2, 200, true);
  delay(2000);
  controlarMotor(2, 0, false);
  delay(500);
  
  Serial.println("Testando Motor 3...");
  controlarMotor(3, 200, true);
  delay(2000);
  controlarMotor(3, 0, false);
  delay(500);
  
  Serial.println("Testando Motor 4...");
  controlarMotor(4, 200, true);
  delay(2000);
  controlarMotor(4, 0, false);
  delay(500);
  
  Serial.println("Teste concluído!\n");
}