#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

#define BAIXO 0
#define ALTO 1
#define ESQUERDA 2
#define DIREITA 3

// Declaracao das Portas usadas no acionamento dos motores
const int up = 27;
const int keep = 26;
const int down = 25;

// Led auxiliar para verificar conexao bt
const int bt_on = 14;

void setup() {
  Serial.begin(9600);

  // Inicio e configuracao do Bluetooth
  if (!SerialBT.begin("AquaDrone")) {
    Serial.println("Falha ao iniciar Bluetooth. Verifique a configuracao.");
    while (true); // Trava o programa
  }
  Serial.println("O dispositivo esta disponivel para pareamento.");

  // Setando as portas utilizadas nos motores como saida
  pinMode(up, OUTPUT);
  pinMode(keep, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(bt_on, OUTPUT);

  // Inicializando as saidas
  digitalWrite(up, LOW);
  digitalWrite(keep, LOW);
  digitalWrite(down, LOW);
  digitalWrite(bt_on, LOW);
}

void loop() {
  if (SerialBT.connected()) {
    // Quando conectado, LED indica a conexao
    digitalWrite(bt_on, HIGH);
    if (SerialBT.available()) {
      int valor = SerialBT.read(); // Le o dado recebido
      Serial.print("Recebido: ");
      Serial.println(valor);

      // Controle baseado no valor recebido
      switch (valor) {
        case BAIXO:
          digitalWrite(up, HIGH);
          digitalWrite(keep, LOW);
          digitalWrite(down, LOW);
          break;
        case ALTO:
          digitalWrite(up, LOW);
          digitalWrite(keep, LOW);
          digitalWrite(down, HIGH);
          break;
        default:
          digitalWrite(up, LOW);
          digitalWrite(keep, HIGH);
          digitalWrite(down, LOW);
          break;
      }
    }
  } else {
    // Nao conectado
    digitalWrite(bt_on, LOW);
    Serial.println("Aguardando conexao Bluetooth...");
  }

  delay(500);
}
