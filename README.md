
## Link do video: https://youtu.be/10DZYoq72qs?si=DZnl91zDTSFk_I_7


# 🌍 Arquitetura

![Captura de tela 2024-10-21 153724](https://github.com/user-attachments/assets/2f247bfe-16ce-41e6-be72-0d7970d06ed0)


# 🏗️ Node-red

## Passos

No CMD

npm install -g node-red   

node-red

http://127.0.0.1:1880/

mqtt://test.mosquitto.org:1883

![image](https://github.com/user-attachments/assets/c5d67462-d928-4457-8bcf-1a30be300d63)
![image](https://github.com/user-attachments/assets/18eb32bf-ea08-4a7d-a868-69b84edb953f)


# ⚙️Documentação do Código

# Descrição Geral:

Este código implementa a leitura de um sensor de temperatura e umidade DHT22 conectado a uma placa ESP32. A cada leitura, os dados são enviados via MQTT para um broker público (Mosquitto). O código usa as bibliotecas WiFi.h para conectar à rede Wi-Fi e PubSubClient.h para o protocolo MQTT, além da biblioteca DHT.h para ler os dados do sensor DHT22.

# Componentes:

Placa: ESP32
Sensor: DHT22 para leitura de temperatura e umidade
Protocolo: MQTT para envio dos dados para a nuvem
Broker: Mosquitto (servidor público test.mosquitto.org)
Definições e Variáveis:
DHTPIN (21): Define o pino GPIO da ESP32 onde o sensor DHT22 está conectado.
DHTTYPE: Define o tipo de sensor DHT (DHT22).
ssid: O nome da rede Wi-Fi à qual a ESP32 vai se conectar.
password: A senha da rede Wi-Fi (neste caso, vazia para conectar na rede "Wokwi-GUEST").
mqtt_server: Endereço do broker MQTT público (Mosquitto).
mqtt_topic: Tópico MQTT onde as mensagens do sensor DHT serão publicadas.
Bibliotecas Utilizadas:
WiFi.h: Para a conexão da ESP32 à rede Wi-Fi.
PubSubClient.h: Para o protocolo MQTT, possibilitando a comunicação com o broker.
DHT.h: Para a leitura de dados do sensor de temperatura e umidade.

Funções:
setup():

Inicializa a comunicação serial para monitoramento no console.
Inicializa o sensor DHT.
Configura a conexão Wi-Fi.
Configura o cliente MQTT para se conectar ao broker e assina o tópico definido.
setup_wifi():

Conecta a ESP32 à rede Wi-Fi. Um loop garante que o código continue tentando conectar até obter sucesso. A função também imprime no console o progresso da conexão.
reconnect():

Verifica se a ESP32 está conectada ao broker MQTT. Caso não esteja, tenta se reconectar até obter sucesso, imprimindo mensagens no console para indicar o progresso.
loop():

A função principal que roda continuamente:
Verifica a conexão com o broker MQTT e a restaura, se necessário.
Faz a leitura dos dados de temperatura e umidade do sensor DHT.
Caso as leituras sejam válidas, os dados são enviados ao broker no formato JSON, contendo os valores de temperatura e umidade. A mensagem é publicada no tópico MQTT previamente definido.
Os dados também são exibidos no console para monitoramento.
Uma pausa de 5 segundos é feita entre as leituras e envios subsequentes.
Fluxo de Funcionamento:
Conexão Wi-Fi: A ESP32 conecta-se à rede Wi-Fi.
Conexão MQTT: A ESP32 se conecta ao broker MQTT Mosquitto.
Leitura de Dados: O sensor DHT22 lê a temperatura e a umidade do ambiente.
Publicação de Dados: Os dados de temperatura e umidade são formatados como uma string JSON e enviados ao broker via o protocolo MQTT.
Repetição: O processo se repete continuamente, a cada 5 segundos.

# JSON Enviado:

O formato da mensagem enviada é:

{
  "temperatura": <valor_da_temperatura>,
  "umidade": <valor_da_umidade>
}

# Possíveis Erros:

Se a leitura do sensor falhar (isnan), uma mensagem de erro será exibida no console, mas o código continua rodando normalmente, tentando ler novamente após o próximo intervalo.

Exemplo de Saída Serial:

Conectando-se a Wokwi-GUEST
WiFi conectado!
Tentando conexão MQTT...
Conectado ao broker MQTT
{"temperatura":25.00, "umidade":60.00}

# Modificações Futuras:

Adicionar autenticação ao broker MQTT para maior segurança.
Implementar reconexão automática à rede Wi-Fi em caso de desconexão.
Possibilitar o envio de dados para múltiplos tópicos MQTT se outros sensores forem adicionados.

# Bibliotecas Necessárias:

DHT.h: Para ler dados do sensor DHT22.
PubSubClient.h: Para implementar o protocolo MQTT.
Essas bibliotecas podem ser instaladas diretamente na IDE do Arduino (ou PlatformIO, se for utilizado).
