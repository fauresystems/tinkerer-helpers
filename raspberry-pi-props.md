[<- back](README.md)

# Raspberry Pi
There are 3 types of applications that **Room** software suits very well and which require none or more or less advanced electronics knowledge (IoT, Raspberry Pi or Arduino):
1. Preparation with NOOBS 3.0
2. Headless HDMi rezolution
3. Static IP address
4. Additional USB wifi adpater
5. MQTT, PyQt5 and Eric6
6. Reboot and relaunch
7. Disable Bluetooth
8. MQTT treading issue when packet loss

## 1. Preparation with NOOBS 3.0

Download NOOBS offline install from https://www.raspberrypi.org/downloads/noobs/ and unzip all files in a clean SD Card (16GB recommended)

1. Boot on NOOBS, choose complete install and proceed
2. Enable VNC and SSH in raspi-config
3. Set passwords:

    ```csharp
    $ passwd
    -> for pi (former is raspberry)
    $ sudo passwd root
    -> for root
    ```
    
4. Update Raspbian:

    ```csharp
    $ sudo apt-get update
    $ sudo apt-get upgrade
    ```
    
5. Add screen 	

    ```csharp
    $ sudo apt-get install screen
    ```
    
## 2. Headless HDMI rezolution

* Order HDMI dummy plug such as <a href="https://www.amazon.com/s?k=hdmi+dummy+plug&ref=nb_sb_noss_2" target="_blank">https://www.amazon.com/s?k=hdmi+dummy+plug&ref=nb_sb_noss_2</a>
* Edit */boot/config.txt*
    ```csharp
    $ sudo nano /boot/config.txt
    ->
    #framebuffer_width=1280
    #framebuffer_height=720
    framebuffer_width=1920
    framebuffer_height=1080
    ```

## 3. Static IP address

Edit */etc/dhcpcd.conf*

```csharp
$ sudo nano /etc/dhcpcd.conf
->
interface eth0

static ip_address=192.168.0.10/24
static routers=192.168.0.1
static domain_name_servers=192.168.0.1

interface wlan0

static ip_address=192.168.0.200/24
static routers=192.168.0.1
static domain_name_servers=192.168.0.1
```

## 4. Additional USB wifi adpater

1. Hotplug a Raspberry comapible Wifi USB apdapter such as https://www.amazon.fr/gp/product/B07D35XB1C/ref=ppx_yo_dt_b_asin_title_o03__o00_s00?ie=UTF8&psc=1

    ```csharp
    $ lsusb
    Bus 001 Device 004: ID 0bda:8178 Realtek Semiconductor Corp. RTL8192CU 802.11n WLAN Adapter
    Bus 001 Device 005: ID 0424:7800 Standard Microsystems Corp. 
    Bus 001 Device 003: ID 0424:2514 Standard Microsystems Corp. USB 2.0 Hub
    Bus 001 Device 002: ID 0424:2514 Standard Microsystems Corp. USB 2.0 Hub
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    ```

2. Connect to wifi network from the desktop

3. Disable onboard wifi then reboot (eventually disable Bluetooth as well):

    ```csharp
    $ cat /etc/modprobe.d/raspi-blacklist.conf 
    
    ## disable onboard wifi
    blacklist brcmfmac
    blacklist brcmutil
    
    ## disable onboard bluetooth
    blacklist btbcm
    blacklist hci_uart
    ```

Wifi network configuration is editable, *order is not relevant if several nerworks are available*:

```csharp
$ cat /etc/wpa_supplicant/wpa_supplicant.conf 
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=FR

#network={
#	ssid="free_escape"
#	psk="toto00"
#	key_mgmt=WPA-PSK
#}

network={
	ssid="Linksys_RDC"
	psk="toto001"
	key_mgmt=WPA-PSK
}
```

## 5. MQTT, PyQt5 and Eric6

```csharp
$ sudo apt-get update
$ sudo apt-get install qt5-default pyqt5-dev pyqt5-dev-tools
$ sudo pip3 install paho-mqtt
$ sudo apt-get install eric
```


## 6. Reboot and relaunch
Start script.py:
```csharp
$ screen -d -m python3 ~/Room/Props/script.py -s %BROKER%
```

Stop script.py:
```csharp
$ ps aux | grep python | grep -v \"grep python\" | grep script.py | awk \'{print $2}\' | xargs kill -9 
```

Relaunch script.py:
```csharp
$ ps aux | grep python | grep -v \"grep python\" | grep script.py | awk \'{print $2}\' | xargs kill -9 ";" sleep 3 && screen -d -m python3 ~/Room/Props/script.py -s %BROKER% 
```

Reboot:
```csharp
$ sudo reboot -f
```

Start script at boot:
```csharp
pi@podium:~ $ cat /etc/rc.local 
#!/bin/sh -e
#
# rc.local
#
# This script is executed at the end of each multiuser runlevel.
# Make sure that the script will "exit 0" on success or any other
# value on error.
#
# In order to enable or disable this script just change the execution
# bits.
#
# By default this script does nothing.

# Print the IP address
_IP=$(hostname -I) || true
if [ "$_IP" ]; then
  printf "My IP address is %s\n" "$_IP"
fi

su pi -c "cd ~/Room/Podium ; python3 podium.py > ~/startup.log 2>&1 &"

exit 0
```

## 8. MQTT threading issue when packet loss

Issues have been reported when using *paho-mqtt* in multithreaded applications:
* with QoS 2
* facing packet loss

*Then code is waiting on a message to be published that is in the state of **mqtt_ms_publish** but we are already connected, so it will never publish.*

It seems to be the issue we have faced with Podium (room Pharao) which get stuck after hours running well.

Solution is to publish messages with QoS 0 or QoS 1. Arduino PubSubClient uses QoS 0 and it works, even with packet loss.


## Author

**Marie FAURE** (Oct 9th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://faure.systems/" target="_blank">Faure Systems</a>