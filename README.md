# Totem de monitoramento de participação e engajamento 

## Visão geral 
O totem inteligente para monitoramente de participação em empresas ou universidades utiliza: ESP32, sensores IoT e integração via MQTT com o Fiware Irion Context Broker, criando, assim, uma solução inovadora que tem como principais objetivos:
- Monitorar presenças próximas ao totem;
- Estimar fluxo e engajamento de funcionários ou alunos;
- Detectar distâncias e movimentação;
- Enviar dados em tempo real para relatórios.

A solução reforça:
- ODS 4 (Educação de qualidade) - pois fornece dados de engajamento e presença;
- ODS 8 (Trabalho decente e crescimento econômico) - pois prepara ambiente inteligêntes;
- ODS 9 (Indústria, inovação e infraestrutura) - pois utiliza a plataforma digital Fiware.

---

## Arquitetura da solução
<img width="649" height="442" alt="image" src="https://github.com/user-attachments/assets/148f01c3-c973-4ba1-86c0-9351b9b9f275" />


### Componentes utilizados
#### Hardware:
- ESP32
- HC - SR04 (sensor ultrassônico de distância)
- Sensor PIR (presença)
- Botão (contador de integração)

#### Software:
- Wokwi (para simulação)
- MQTT (protocolo)
- Fiware IoT Agent MQTT
- Fiware Orion Context Broker
- Postman para testes

---

## Provisionamento no Fiware
### Via Postman (json):
#### Post - /iot/devices
```
{
  "devices": [
    {
      "device_id": "esp32_totem_01",
      "entity_name": "urn:ngsi-ld:Totem:esp32_totem_01",
      "entity_type": "Totem",
      "protocol": "PDI-IoTA-UltraLight",
      "transport": "MQTT",
      "attributes": [
        { "object_id": "d", "name": "distance", "type": "Number" },
        { "object_id": "n", "name": "student_near", "type": "Boolean" },
        { "object_id": "s", "name": "step_count", "type": "Number" },
        { "object_id": "p", "name": "presence", "type": "Boolean" }
      ]
    }
  ]
}
```

## Funcionamento do ESP32
O ESP32 coleta continuamente dados dos sensores:
- Ultrassônico -> Distância em cm -> d (atributo enviado)
- PIR -> Movimento detectado -> p (atributo enviado)
- Botão -> Contador de interações -> s (atributo enviado)
- Lógica -> Se o indivíduo está próximo (< 80cm) -> n (atributo enviado)

## Exemplo de mensagem recebida no Fiware (json)
### GET - /v2/entities/urn:ngsi-ld:Totem:esp32_totem_01
```
{
  "id": "urn:ngsi-ld:Totem:esp32_totem_01",
  "type": "Totem",
  "distance": { "value": 47, "type": "Number" },
  "presence": { "value": true, "type": "Boolean" },
  "student_near": { "value": true, "type": "Boolean" },
  "step_count": { "value": 12, "type": "Number" }
}
```
---
## Código do ESP32
O código compreto está na pasta /wokwi, mas o fluxo é:
- Conecta no Wifi;
- Conecta no broker MQTT;
- Lê sensores;
- Monta payload UltraLight2;
- Publica em:
```
/ul/esp32_totem_01/attrs
```
- Repete a cada 2 segundos.
---
## Demonstração em vídeo

---

## Como executar o projeto
### 1. Executar o Fiware (docker)
```
docker compose up
```

### 2. Provisionar o Device (Postman)
Importar a collection 'postman_collection.json', incluída no repositório.

### 3. Rodar a simulação Wokwi
Link para simulação: 
#### Arquitetura do ESP32
<img width="515" height="541" alt="image" src="https://github.com/user-attachments/assets/2864cf3e-e8fb-4373-a043-a38e880f151f" />

### 4. Validar dados no Fiware
> curl http://localhost:1026/v2/entities/urn:ngsi-ld:Totem:esp32_totem_01

---

## Conclusão
O Totem demosntra como IoT, Fiware e sensores podem criar um ambiente educacional conectado, com dados reais, insights e melhorias contínuas.




