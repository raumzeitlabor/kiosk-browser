# RZL-Infoscreen

## what and why?
Modifiziertes Repo um einen RPI mit vanilla raspbian als RZL-Infoscreen zu nutzen. Leider raucht die Distribution aufgrund der dauernden reboots und power-cycles durch die Funksteckdose gerne mal ab.

## how?
Die Infoscreen-URL und die Fenstergröße ist in der sourcefile hardcoded. Also vorher ggf. ändern, inbesondere wenn ein anderes Display verwendet wird, dann neu kompilieren.

    # remove lightdm
    sudo apt-get update
    sudo apt-get -y purge lightdm
    sudo apt-get -y dist-upgrade 
    
    # ...jetzt erst mal ne Mate, das dauert.

    # install packages
    sudo apt-get install nodm libwebkit-dev
    

    # compiling on rpi, like a boss.
    gcc -o browser browser.c $(pkg-config --libs --cflags gtk+-2.0 webkit-1.0)

    sudo cp browser /usr/bin/browser

    
    # Browser mit X-Session laden
    vi ~/.xsession

        #!/bin/bash \n
        /usr/bin/startx -e /usr/bin/browser tty1 </dev/tty1 >/dev/tty1"

    
    # config nodm
    sudoedit /etc/defaults/nodm

        NODM_ENABLED=true
        NODM_USER=pi

    
    # kein screensaver
    
    vi ~/.xinitrc

        #!/bin/bash
        xset s off         # don't activate screensaver
        xset -dpms         # disable DPMS (Energy Star) features.
        xset s noblank     # don't blank the video device


    sudo reboot


-------

This is a minimal WebKit based browser in fullscreen.
It's intended use is to display a single web resource non-interactively,
while being highly portable, especially to the arm11 architecture (used for the Raspberry Pi), and supporting Javascript and HTML5 Websockets for dynamic content updates.
[Peter Schultz](https://github.com/pschultz/kiosk-browser "kiosk-browser on github") wrote the original version. See the changes under changelog.

* [German blog post about a use case with my raspberry pi on repat.de](http://repat.de/2013/03/raspberry-pi-als-kiosk-mit-resourcenschonendem-browser-und-vesa-mount/ "kiosk-browser on repat.de")

## Compiling
    apt-get install libwebkit-dev
    # OR: yum install webkitgtk-devel
    
    gcc -o browser browser.c $(pkg-config --libs --cflags gtk+-2.0 webkit-1.0)

## Installing
No special steps are required for installation. Just execute `browser`.
This program was designed to be started via inittab on boot like this:

    1:2345:respawn:/usr/bin/startx -e /usr/bin/browser http://10.0.0.5/zfs/monitor tty1 </dev/tty1 >/dev/tty1 2>&1

## Usage
    ./browser

This will launch the browser in fullscreen mode and load the resource from`DEFAULT_URL` hardwired in the source.
`DEFAULT_URL` can be anything that WebKit supports, including `file://`-URLs for local webpages and documents.

The following keybinding exists:
  - `F5` for reloading the current page
It's also implemented as a signal handler:
  - `HUP` for reload

## Changelog
* hardwired size(`int HEIGHT` and `int WIDTH`)
* hardwired URL (`gchar* DEFAULT_URL`), no commandline argument
* hardwired position (`GTK_WIN_POS_CENTER_ALWAYS`)
* no toggle fullscreen with F11, thus removed unmaximize() and USR1
* deleted Makefile, only one command(see above)

## Contact
* http://repat.de
* email: repat[at]repat[dot]de
* XMPP: repat@jabber.ccc.de
* Twitter: [repat123](https://twitter.com/repat123 "repat123 on twitter")

[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=repat&url=https://github.com/repat/kiosk-browser&title=kiosk-browser&language=&tags=github&category=software) 
