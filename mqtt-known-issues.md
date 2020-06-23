[<- back](README.md)

# MQTT known issues
These are important issues we have to take into account in Escape Room automation:
1. MQTT message size on Arduino
2. MQTT QoS with Python Paho multi-threading

## 1. MQTT message size on Arduino

Due to **PubSubClient** and **Bridge** implementations on Arduino Yun and Dragino Yun shield, the ***size of MQTT message is limited on Arduino***.
### Publish MQTT message from Arduino


We have run tests to find the message size limitation for the application payload:

#### Arduino Yun
* Arduino Yun can send a message with a total payload of **120 chars including the topic**

#### Dragino Yun + Mega 2560
* Dragino Yun can send a message with a total payload of **120 chars including the topic**

### Receive MQTT message on Arduino
Message size limitation may apply to incoming messages as well, but usually instructions received in the props thru MQTT are short so it is rarely an issue.

Action messages are commands for actuators, so very short messages.

Settings messages, to modify parameters on the Arduino, could be somehow long messages so you may pay attention. It is very easy to test message reception and ensure incoming message size is safe for the Arduino.

## 2. MQTT QoS with Python Paho multi-threading

***Python script completely blocked issues have been reported when `paho-mqtt` is running asynchronously on a network with packet loss (most of Wifi networks).***

It is recommended to use `paho-mqtt` asynchronously, which runs MQTT client loop in its own thread.

If you send messages from the props with **QoS 2**, packet loss may put the MQTT client thread in a stuck situation, the message published is in *not published* state but the MQTT server is connected. Then the script is completely stuck and the props program must be restarted.

This issue has been observed when the props script is using multi-threading somehow intensively, for example to play sounds with Pygame (because each sound is played in its own thread).

***From our experience, this blocking issue occurs after about 24-hour run-time of a Pygame props script using a dozen of audio channels.***

Because Arduino PubSubClient only supports publishing messages with **QoS 0**, it is safe to use **QoS 0** with Python `paho-mqtt` Raspberry props as well. 

From our own experience **QoS 0** works perfectly well, even on Wifi networks with packet loss (MQTT client doesn't get stuck waiting for a *QoS 2 PUBREC* or *PUBCOMP* packet which never arrives).

If you want to ensure the props receive/send message 100% sure, you may implement an acknowledgment and retry mechanism at application level ; for both Arduino and Raspberry props publishing with **QoS 0**.

On our multiple props implementations in Escape Rooms we never faced issues with **QoS 2** on wired networks.


## Author

**Faure Systems** (Oct 9th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://faure.systems/" target="_blank">Faure Systems</a>