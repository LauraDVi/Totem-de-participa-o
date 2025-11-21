# Totem de monitoramento de participação e engajamento 

Equipe:
  Laura Dantas - 564064;
  Raphael Aaron - 564067;
  Felipe Catto - 562106.

--- 

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
Link para simulação: https://wokwi.com/projects/448010101354763265
#### Arquitetura do ESP32
<img width="547" height="438" alt="image" src="https://github.com/user-attachments/assets/4a9c894f-eedd-43fe-a075-331a56e58749" />


### 4. Validar dados no Fiware
> curl http://localhost:1026/v2/entities/urn:ngsi-ld:Totem:esp32_totem_01

---
## Conclusão
  O desenvolvimento do projeto pôde demonstrar como soluções IoT podem contribuir diretamente para a evolução do ambiente educacional e profissional diante dos desafios da transformação digital. A integração entre ESP32, sensores sísicos, comunicação MQTT e a plataforma Fiware mostrou grande eficiência na coleta, transmissão e contextualização das informações relevantes em tempo real, reforçando o potencial dessas tecnologias na construção de sistemas inteligentes voltados ao aprendizado contínuo, à automação e à melhoria da experiência do usuário.
  Além disso, o projeto ilustra como iniciativas de baixo custo e alta estabilidade podem ser aplicadas para atender a aobjetivos como as ODSs 4, 8 e 9, promovendo inovação, acesso a ferramentas tecnológicas e criação de ambientes mais dinâmicos e inclusivos.
  O trabalho, portanto, evidencia não apenas a importância do uso de tecnologias emergentes, mas a necesidae de preparar indivíduos e organizações para um futuro cada vez mais orientado por dados, conectividade e integração digital.
