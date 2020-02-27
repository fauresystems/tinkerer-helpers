[<- back](README.md)

# Mosquitto with websocket on Raspberry Pi
Standard installation of mosquitto MQTT broker on Raspberry Pi does not support websocket (necessary to receive messages for web browsers such as Chrome or Firefox).

## Step by step installation

### Step 1: dependencies installation
```bash
sudo apt-get --assume-yes install \
build-essential \
python \
quilt \
devscripts \
python-setuptools \
python3 \
libssl-dev \
cmake \
libc-ares-dev \
uuid-dev \
daemon \
zlibc \
zlib1g \
zlib1g-dev
```

### Step 2: libwebsockets compilation
```bash
git clone https://github.com/warmcat/libwebsockets.git
cd libwebsockets
mkdir build
cd build
cmake .. && sudo make install && sudo ldconfig
```

### Step 3: download mosquitto
```bash
mkdir ~/mosquitto
cd ~/mosquitto/
MOSQUITTO_VER=mosquitto-1.4.14
wget https://mosquitto.org/files/source/$MOSQUITTO_VER.tar.gz
tar zxvf $MOSQUITTO_VER.tar.gz
cd $MOSQUITTO_VER
```

### Step 4:  change in config WITH_WEBSOCKETS:=yes
Proceed with:
```bash
sudo nano config.mk
```

### Step 5: mosquitto compilation
```bash
make && sudo make install
sudo cp mosquitto.conf /etc/mosquitto
```

### Step 6: add user “mosquitto”
```bash
useradd -r -m -d /var/lib/mosquitto -s /usr/sbin/nologin -g nogroup mosquitto
```

### Step 7: setup mosquitto options
```bash
sudo nano /etc/mosquitto/mosquitto.conf
```
Find:
```bash
port 1883
listener 9001
protocol websockets
pid_file /var/run/mosquitto.pid
```
Optionally add a security layer creating a password file:
```bash
mosquitto_passwd -c /etc/mosquitto/passwd yourloginname
sudo nano /etc/mosquitto/mosquitto.conf
allow_anonymous false
```

### Step 8: create a link
```bash
sudo ln -s /usr/local/sbin/mosquitto /bin/mosquitto
```

### Step 9: reboot
```bash
sudo reboot
```

## Start mosquitto manually
```bash
mosquitto -c /etc/mosquitto/mosquitto.conf
```

## Start mosquitto as a service on Raspberry boot

### 1. Edit “mosquitto.service” file
```bash
sudo nano /etc/systemd/system/mosquitto.service
```
Add:
```bash
[Unit]
Description=Mosquitto MQTT Broker daemon
After=network.target
Requires=network.target

[Service] 
Type=forking 
RemainAfterExit=no 
StartLimitInterval=0 
PIDFile=/var/run/mosquitto.pid 
# Note: The following paths may be different on your system.
ExecStart=/usr/local/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf -d 
ExecReload=/bin/kill -HUP $MAINPID 
Restart=on-failure 
RestartSec=2

[Install] 
WantedBy=multi-user.target
```
See <https://goo.gl/wMCZFv> for more.

### 2. Activate the service
```bash
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

### 3. From now on, mosquitto will start at boot time
```bash
sudo reboot
```

### 4. Check eveything is okay
```bash
pidof mosquitto
mosquitto -v
```


## Credits
This how-to has been written with the help of:
* <a href="https://ouilogique.com/mosquitto-mqtt-raspbery/" target="_blank">Installer Mosquitto MQTT avec WebSocket sur un Raspberry Pi</a>
* <a href="https://xperimentia.com/2015/08/20/installing-mosquitto-mqtt-broker-on-raspberry-pi-with-websockets/" target="_blank">INSTALLING MOSQUITTO MQTT BROKER ON RASPBERRY PI (WITH WEBSOCKETS)</a>


## Author

**Marie FAURE** (Oct 9th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://faure.systems/" target="_blank">Faure Systems</a>