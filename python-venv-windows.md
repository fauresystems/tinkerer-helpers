[<- back](README.md)

# Python *venv* (Windows command line)
Create *venv* with Windows command line (you may also consider [Python *venv* (PyCharm)](python-venv-windows.md).

***This is the recommended method to create a virtual environment for Room plugins.***


## Install Python 3 on Windows x64 (for Room plugins)
At this time we recommend Python 3.8.0 release which is stable.

**Room installer will install Python 3.8.0 in `C:\Python38`** so we recommend to let **Room** install Python. Anyway, you can download Python x64 installer from <a href="https://www.python.org/downloads/windows/" target="_blank">python.org</a> and run the installer yourself, please select  `C:\Python38` for the target folder. 

The installation performed by **Room** is somehow minimal:

```bash
$ python-3.8.0-amd64.exe /quiet TargetDir=C:\Python38 Shortcuts=0 PrependPath=1 Include_doc=0 Include_launcher=0 Include_test=0

```

For a manual installation, select **custom installation**:
- **add Python 3.8.0 to PATH** is selected
- unselect all options
- select **pip**
- select **tcl/tk and IDLE**
- select **create shortcuts**
- select **add Pyhton to environment variables**
- install in `C:\Python38`


## To create a new *venv* in your project folder
Please note that **Room** plugins are recommended to run in their own *venv* created with this method.

### 1) Create *venv*
```bash
$ cd «Your Project Directory»
$ python -m pip install --upgrade pip
$ python -m venv --copies --clear .\venv 
```

### 2) Activate *venv*
```bash
$ venv\Scripts\activate.bat
```

### 3) Update *pip* and install project requirements (if any)
```bash
$ python -m pip install --upgrade pip
$ pip install -r requirements.txt
```

You can now run your Python script from the command line.

### 4) Update requirements if you install new packages in this *venv*
```bash
$ pip freeze > requirements.txt
```

### 5) Exit *venv* when you're done
```bash
$ venv\Scripts\deactivate.bat
```


## Author

**Marie FAURE** (Dec 5th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://faure.systems/" target="_blank">Faure Systems</a>