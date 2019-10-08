[<- back](README.md)

# Build QtMqtt with Visual Studio

1) download and install Strawberry Perl for Windows 64-bit

2) download QtMqtt with GitHub Desktop (clone repository from URL) or:
```csharp
git clone git://code.qt.io/qt/qtmqtt.git
```

3) open Invite: `x64 Native Tools Command Prompt for VS 2017` or `qtenv2.bat`

4) go in `qtmqtt` folder where you find `qtmqtt.pro`

5) build qtmqtt:
```csharp
...\qtmqtt> C:\Qt5\5.12.1\msvc2017_64\bin\qmake.exe
...\qtmqtt> nmake
```

6) copy `Qt5Mqtt.dll` and `Qt5Mqttd.dll` in `C:\Qt5\5.12.1\msvc2017_64\bin` (required for deploy and debug)

7) we're done (in both include and lib folders)

Notes: https://github.com/qt/qtmqtt


## Author

**Marie FAURE** (Oct 1th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://www.live-escape.net/" target="_blank">Live Escape Grenoble</a>