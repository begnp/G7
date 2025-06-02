// C++ code
//

// Incluindo bibliotecas
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);  // Cria objeto RFID

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


const int pin_btn1 = 5;
const int pin_btn2 = 6;
const int pin_btn3 = 7;

bool btn1State;
bool btn2State;
bool btn3State;

int pergunta_dada = 0;
int resposta = 0;
int questao;

unsigned long marcador;
unsigned long demora;

int pergunta = 1;
int pasta = 1;

void setup()
{
  pinMode(pin_btn1, INPUT_PULLUP);
  pinMode(pin_btn2, INPUT_PULLUP);
  pinMode(pin_btn3, INPUT_PULLUP);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Erro ao iniciar DFPlayer"));
    while (true);
  }
  myDFPlayer.volume(30);
  myDFPlayer.EQ(0);
  Serial.println(F("DFPlayer pronto"));

  SPI.begin();              // Inicia comunicação SPI
  rfid.PCD_Init();          // Inicia o sensor RFID
  Serial.println("Aproxime a tag do leitor...");
  
}

void loop() {
  
  if (pergunta_dada == 0) {
    // Verifica se tem nova tag
    if (!rfid.PICC_IsNewCardPresent()) return;
    if (!rfid.PICC_ReadCardSerial()) return;

   // Para a leitura
    rfid.PICC_HaltA();

    if (rfid.uid.uidByte[0] == 3) {
      Serial.println("É 3!");
      pasta = 3;
      questao = random(1, 21);
      pergunta = questao;

      myDFPlayer.playFolder(pasta, pergunta);
    
      Serial.print(pasta);
      Serial.print(", ");
      Serial.println(questao);
      pergunta_dada = 1;
      //Marcar tempo
      marcador = millis();
      // Serial.println(marcador);
      delay(1000);
    }
    else if (rfid.uid.uidByte[0] == 83) {
      Serial.println("É 83!");
      pasta = 5;
      questao = random(1, 16);
      pergunta = questao;

      myDFPlayer.playFolder(pasta, pergunta);
    
      Serial.print(pasta);
      Serial.print(", ");
      Serial.println(questao);
      pergunta_dada = 1;
      //Marcar tempo
      marcador = millis();
      // Serial.println(marcador);
      delay(1000);
    }
    else if (rfid.uid.uidByte[0] == 195) {
      Serial.println("É 195!");
      pasta = 7;
      questao = random(1, 16);
      pergunta = questao;

      myDFPlayer.playFolder(pasta, pergunta);
    
      Serial.print(pasta);
      Serial.print(", ");
      Serial.println(questao);
      pergunta_dada = 1;
      //Marcar tempo
      marcador = millis();
      // Serial.println(marcador);
      delay(1000);
    }
    else if (rfid.uid.uidByte[0] == 243) {
      Serial.println("É 243!");
      pasta = 9;
      questao = random(1, 16);
      pergunta = questao;

      myDFPlayer.playFolder(pasta, pergunta);
    
      Serial.print(pasta);
      Serial.print(", ");
      Serial.println(pergunta);
      pergunta_dada = 1;
      //Marcar tempo
      marcador = millis();
      // Serial.println(marcador);
      delay(1000);
    }
    /* else if (rfid.uid.uidByte[0] == ) { // inserir uid do tag
      myDFPlayer.playFolder(11, 1);
      delay(15000);
    }*/
  }

  //Ler botão pressionado
  btn1State = digitalRead(pin_btn1);
  btn2State = digitalRead(pin_btn2);
  btn3State = digitalRead(pin_btn3);

  // Se pressionar o botão de repetição
  if (btn3State == LOW && pergunta_dada == 1) {
    myDFPlayer.playFolder(pasta, pergunta);
    delay(2000);
  }
  
  // Se pressionar algum dos botões de resposta
  if (btn1State == LOW && resposta == 0 && pergunta_dada == 1) {
    Serial.println("V");
    resposta = 1;
    delay(1000);
  }
  else if (btn2State == LOW && resposta == 0 && pergunta_dada == 1) {
    Serial.println("F");
    resposta = 2;
    delay(1000);
  }
  
  // Marcar a demora para responder
  demora = millis();
  
  // Indicar se houve resposta e se está correta
  if (pergunta_dada == 1 && resposta != 0) {
    Serial.print(resposta);
    Serial.println(" resposta recebida!");

    int correcao = verificacao(resposta, pasta, pergunta);
    Serial.print(correcao);
    Serial.println(" resposta processada");

    if (correcao == 1) {
      Serial.println("caiu certa");
      certo();
      Serial.println("resposta certa");
    } else if (correcao == 2) {
      Serial.println("caiu errada");
      errado(pasta, pergunta);
      Serial.println("resposta errada");
    }
    pergunta_dada = 0;
    resposta = 0;
    delay(1000);
  }
  // Caso o jogador não responda a tempo
  else if (pergunta_dada == 1 && resposta == 0 && demora > (marcador + 10000)) {
    myDFPlayer.playFolder(2, 1);
    delay(1000);
    myDFPlayer.playFolder(2, 4);
    delay(1000);
    Serial.println("Tempo esgotado!");
    pergunta_dada = 0;
    resposta = 0;
    delay(1000);
  }

}

/*
Verificar se a resposta foi respondida corretamente
Caso a resposta esteja certa retorna 1
Caso a resposta esteja errada retorna 2
*/
int verificacao(int resposta, int pasta, int pergunta) {
  if (resposta == 1) {
    if (pasta == 3) {
      switch (pergunta) {
        case 2:
          return 1;
          break;
        case 5:
          return 1;
          break;
        case 8:
          return 1;
          break;
        case 9:
          return 1;
          break;
        case 11:
          return 1;
          break;
        case 15:
          return 1;
          break;
        case 16:
          return 1;
          break;
        case 19:
          return 1;
          break;
        case 20:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    } else if (pasta == 5) {
      switch (pergunta) {
        case 1:
          return 1;
          break;
        case 3:
          return 1;
          break;
        case 5:
          return 1;
          break;
        case 6:
          return 1;
          break;
        case 7:
          return 1;
          break;
        case 9:
          return 1;
          break;
        case 12:
          return 1;
          break;
        case 15:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    } else if (pasta == 7) {
      switch (pergunta) {
        case 1:
          return 1;
          break;
        case 2:
          return 1;
          break;
        case 3:
          return 1;
          break;
        case 6:
          return 1;
          break;
        case 8:
          return 1;
          break;
        case 11:
          return 1;
          break;
        case 13:
          return 1;
          break;
        case 14:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    } else if (pasta == 9) {
      switch (pergunta) {
        case 1:
          return 1;
          break;
        case 2:
          return 1;
          break;
        case 3:
          return 1;
          break;
        case 4:
          return 1;
          break;
        case 7:
          return 1;
          break;
        case 8:
          return 1;
          break;
        case 9:
          return 1;
          break;
        case 10:
          return 1;
          break;
        case 14:
          return 1;
          break;
        case 15:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    }

  } else if (resposta == 2) {
    if (pasta == 3) {
      switch (pergunta) {
        case 1:
          return 1;
          break;
        case 3:
          return 1;
          break;
        case 4:
          return 1;
          break;
        case 6:
          return 1;
          break;
        case 7:
          return 1;
          break;
        case 10:
          return 1;
          break;
        case 12:
          return 1;
          break;
        case 13:
          return 1;
          break;
        case 14:
          return 1;
          break;
        case 17:
          return 1;
          break;
        case 18:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    } else if (pasta == 5) {
      switch (pergunta) {
        case 2:
          return 1;
          break;
        case 4:
          return 1;
          break;
        case 8:
          return 1;
          break;
        case 10:
          return 1;
          break;
        case 11:
          return 1;
          break;
        case 13:
          return 1;
          break;
        case 14:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    } else if (pasta == 7) {
      switch (pergunta) {
        case 4:
          return 1;
          break;
        case 5:
          return 1;
          break;
        case 7:
          return 1;
          break;
        case 9:
          return 1;
          break;
        case 10:
          return 1;
          break;
        case 12:
          return 1;
          break;
        case 15:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    } else if (pasta == 9) {
      switch (pergunta) {
        case 5:
          return 1;
          break;
        case 6:
          return 1;
          break;
        case 11:
          return 1;
          break;
        case 12:
          return 1;
          break;
        case 13:
          return 1;
          break;
        default:
          return 2;
          break;
      }
    }
    
  }
  // return 2;
}

// Feedback sonoro sobre resposta correta
void certo() {
  myDFPlayer.playFolder(1, 1);
  delay(1500);
  myDFPlayer.playFolder(1, 2);
  delay(2000);
  Serial.println("Entrou na f certo");
}

// Feedback sonoro sobre resposta incorreta
void errado(int pasta, int pergunta) {
  myDFPlayer.playFolder(2, 1);
  delay(1500);
  Serial.println("Entrou na f errado");

  if (pasta == 3) {
    switch (pergunta) {
      case 2:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 5:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 8:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 9:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 11:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 15:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 16:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 19:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      case 20:
        myDFPlayer.playFolder(2, 3);
        delay(2000);
        return;
        break;
      default:
        break;
    }
    myDFPlayer.playFolder(4, pergunta);
    delay(2000);

  } else if (pasta == 5) {
    switch (pergunta) {
      case 1:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 3:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 5:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 6:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 7:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 9:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 12:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 15:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      default:
        break;
    }
    myDFPlayer.playFolder(6, pergunta);
    delay(2000);

  } else if (pasta == 7) {
    switch (pergunta) {
      case 1:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 2:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 3:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 6:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 8:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 11:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 13:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 14:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      default:
        break;
    }
    myDFPlayer.playFolder(8, pergunta);
    delay(2000);

  } else if (pasta == 9) {
    switch (pergunta) {
      case 1:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 2:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 3:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 4:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 7:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 8:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 9:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 10:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 14:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      case 15:
        myDFPlayer.playFolder(2, 2);
        delay(2000);
        return;
        break;
      default:
        break;
    }
    myDFPlayer.playFolder(10, pergunta);
    delay(2000);

  }
  
}
