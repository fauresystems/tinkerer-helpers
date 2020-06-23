[<- back](README.md)

# VLC remote how-to

## VLC remote in config file
	# Extra interface modules (Chaîne)
	extraintf=http
	# Password (Chaîne)
	http-password=0000
	# HTTP server port (Entier)
	#http-port=8080
	http-port=8081

## VLC remote in Chrome (or any browser)
* Type the IP address (or URL) of the host in the location field (address bar). You may need to specify the port (VLC defalts to using port 8080)

* If you want to control VLC from a computer that is not the one running VLC then you will need to enable access in the .hosts file (from 0.9.6 onwards)

## VLC HTTP requests

* HTTP requests control:
- https://wiki.videolan.org/VLC_HTTP_requests/
- http://localhost:8081/requests/README.txt

### Request to set volume level to `<val>`
(can be absolute integer, percent or +/- relative value):

`?command=volume&val=<val>`
```code
Allowed values are of the form:
   +<int>, -<int>, <int> or <int>%

examples:
    http://localhost:8081/requests/status.xml?command=volume&val=70
```

### Request to seek to `<val>`

`?command=seek&val=<val>`
```code
Allowed values are of the form:
   [+ or -][<int><H or h>:][<int><M or m or '>:][<int><nothing or S or s or ">]
   or [+ or -]<int>%
   (value between [ ] are optional, value between < > are mandatory)

examples:
   1000 -> seek to the 1000th second
   +1H:2M -> seek 1 hour and 2 minutes forward
   -10% -> seek 10% back
```


## Author

**Faure Systems** (Oct 9th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://faure.systems/" target="_blank">Faure Systems</a>