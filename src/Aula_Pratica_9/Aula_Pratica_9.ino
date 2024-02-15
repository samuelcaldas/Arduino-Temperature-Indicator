/**
 * @file Aula_Pratica_9.ino
 * @brief Aula Prática 9 - Indicador de Temperatura °C / °F
 * @version 1.0
 * @date 2023-06-04
 *
 * A. O roteiro envolve o desenvolvimento de um sistema de indicação de temperatura em °C e °F utilizando o Arduino.
 * B. O sistema deve conter um sensor de temperatura (TMP36), um display LCD 16 x 2, dois botões e três LED's (verde, azul e amarelo).
 * C. O sistema só funciona após o botão 1 ser pressionado (pulsado) e o LED verde acenderá.
 * D. Se o botão 1 for pressionado novamente o sistema para de funcionar e o LED verde apaga.
 */

// Inclui a biblioteca do display LCD
#include <LiquidCrystal.h>

// Inicializa o display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define os pinos dos botões e LEDs
#define botao1 6
#define botao2 7
#define ledVerde 10
#define ledAzul 9
#define ledAmarelo 8

// Define o pino do sensor de temperatura
#define sensorTemp A0

// Variáveis para armazenar o estado dos botões e do sistema
bool sistemaLigado = false;
bool tempCelsius = true;

void setup()
{
    // Configura os pinos dos botões como entrada
    pinMode(botao1, INPUT);
    pinMode(botao2, INPUT);

    // Configura os pinos dos LEDs como saída
    pinMode(ledVerde, OUTPUT);
    pinMode(ledAzul, OUTPUT);
    pinMode(ledAmarelo, OUTPUT);

    // Inicializa o display LCD
    lcd.begin(16, 2);
}

void loop()
{
    // Verifica se o botão 1 foi pressionado
    if (digitalRead(botao1) == HIGH)
    {
        // Alterna o estado do sistema (ligado/desligado)
        sistemaLigado = !sistemaLigado;

        // Acende ou apaga o LED verde de acordo com o estado do sistema
        digitalWrite(ledVerde, sistemaLigado ? HIGH : LOW);

        // Aguarda o botão ser solto
        while (digitalRead(botao1) == HIGH);
        delay(50);
    }

    // Verifica se o sistema está ligado
    if (sistemaLigado)
    {
        // Acende ou apaga os LEDs azul e amarelo de acordo com a unidade de temperatura selecionada
        digitalWrite(ledAzul, tempCelsius ? HIGH : LOW);
        digitalWrite(ledAmarelo, tempCelsius ? LOW : HIGH);

        // Verifica se o botão 2 foi pressionado
        if (digitalRead(botao2) == HIGH)
        {
            // Alterna entre Celsius e Fahrenheit
            tempCelsius = !tempCelsius;

            // Limpa o display LCD
            lcd.clear();

            // Aguarda o botão ser solto
            while (digitalRead(botao2) == HIGH);
            delay(50);
        }

        // Lê a temperatura do sensor TMP36
        float tensao = analogRead(sensorTemp) * (5.0 / 1023.0); // Converte o valor lido para tensão
        float tempC = (tensao - 0.5) * 100.0;                   // Converte a tensão para temperatura em graus Celsius
        float tempF = tempC * (9.0 / 5.0) + 32.0;               // Converte a temperatura em graus Celsius para Fahrenheit

        // Exibe a temperatura no display LCD na unidade selecionada
        lcd.setCursor(0, 0);
        lcd.print("Temperatura: ");
        lcd.setCursor(0, 1);
        lcd.print(tempCelsius ? tempC : tempF);
        lcd.print(tempCelsius ? " C" : " F");
    }
    else
    {
        // Limpa o display LCD se o sistema estiver desligado
        lcd.clear();

        // Apaga os LEDs azul e amarelo, caso estejam acesos
        digitalWrite(ledAzul, LOW);
        digitalWrite(ledAmarelo, LOW);
    }
}
