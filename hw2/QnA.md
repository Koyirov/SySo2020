# SystemSoftware hw2

## linux kernel

1. **What does the 2>&1 do in the given command? Why is it needed?**

  Durch diesen Befehl können wir stderror Nachrichten in gleicher Ort umleiten, wo stdout Nachrichten umgeleitet werden.
  Dieser Befehl kann nützlich sein, wenn `-device help` irgendeine Fehlermeldung ausgibt, oder qemu diese Optionen nicht unterstütz.

2. **Which kernel options did you activate in addition to the config from Homework1 and what are they needed for?**

  Unten `Networking Support` Menüpunkt die Konfigurationen, die uns mit Netzwork und Netzwork Protokolle arbeiten und mit andere Hosts Data austauschen ermöglichen. Z.B:
  - `Packet socket`  das Paketprotokoll wird von Anwendungen verwendet, die direkt mit Netzwerkgeräten kommunizieren, ohne dass ein zwischengeschaltetes Netzwerkprotokoll im Kernel implementiert ist.
  - `TCP/IP Networking` dies sind die Protokolle, die im Internet und in den meisten lokalen Ethernets verwendet werden.
  - `DHCP support`  DHCP ist ein Kommunikationsprotokoll. Es ermöglicht die Zuweisung der Netzwerkkonfiguration an Clients durch der Server.
  - `Virtual Socket protocol` ist ein TCP / IP-ähnliches Socket-Protokoll, das die Kommunikation zwischen virtuellen Maschinen und Hypervisor oder Host ermöglicht.
  - und paar ander Optionen.
  Unten `Device Drivers` Menüpunkt nötige Treibers. Z.B:
  - `Netzwork device support`
  - `Network core driver support` für die Vernetzung der Kerntreiber erforderlich.
  - `Virtio network driver` dies ist der virtuelle Netzwerktreiber für virtio. Es kann mit lguest- oder QEMU-basierten VMMs verwendet werden.
  - `Ethernet driver support` dieser Abschnitt enthält alle Ethernet-Gerätetreiber.
  Außerdem:
  - `Multiple users, groups and capalbilities support` Option. Diese Option ermöglicht die Unterstützung für Benutzer, Gruppen und Funktionen, die keine Root-Benutzer sind


## busybox

1. **How is DHSP lease applied to the interface by udhpc?**

  Der udhcp-Client handelt eine Lease mit dem DHCP-Server aus. Sobald der udchpc `lease` erhalten oder verloren hat, wird ein Skript ausgeführt. Dieses Skript konfiguriert `IP Adresse`, `gateway`, `resolv.conf` und usw.  

  Um udhcpc korrekt benutzen zu können, Linux Kernel muss mit `packet socket` Unterstützung konfiguriert sein.

2. **What does the example simple.script do on a new lease?**

  Es stellt neue IP, Netmask und Broadcast Adresse auf Netzwerk Interface. Überprüft ob schon irgendeine Router Einstellungen vorhanden ist, falls ja, löscht die und hinzufügt auf Interface neu Routers Einstellungen. Dementsprechend wird resolv.conf(DNS resolver des Systems) angepasst und neues Prozess ID vergeben.

## dropbear

1. **Which applets does the dropbearmulti binary support and what is their purpose?**

  Sie sind `dropbear`, `dbclient`, `dropbearkey`, `dropbearconvert`, `scp`. Zweck von diese applets ist funktional und sicher genug SSH Server und Klient für den allgemeinen Gebrauch ermöglichen. Möglicherweise im kleinen Speicherumgebung.

  2. **What is shadow, and how can we login to the system if it's not used?**

  Shadow verwendet die Datei `/ etc / shadow`, eine zusätzliche Sicherheitsebene, da nur von root darauf zugegriffen werden kann. Dies bedeutet, dass alle Programme, die sie verwenden, Berechtigungen auf Root-Ebene benötigen, was offensichtlich sicherer ist als` / etc / passwd` -Datei, die von jedem gelesen werden kann.

## kernel

1. **What are the uid and guid numbers in Linux and how are they related the passwd and group files in etc?**

  `uid (user identifier)` ist die Nummer, die von Linux zu neuer Benutzer vergeben wird. Diese Nummer wird um den Benutzer in dem System zu identifieren und seine Zugriffrechte auf Systemresource zu bestimmen benutz. `guid (group IDs)` Nummer ist genauso wie `uid` aber repräsentiert die Benutzer Gruppen.
  `uid`s werden in der Datei `/etc/passwd` und `guid`s in der Datei `/etc/group` gespeichert.

## ssh klient

1. **How can you display the public key portion of the key file?**

  Mit dem Befehl `cat ~/.ssh/Dateiname` fuer ssh public keys.  
  With `dropbearkey -y -f filename` for the dropbearkey generated (private) keys.

2. **Which file within a user's home directory is used by the SSH server to know which public keys are authorized for the respective user?**

  `~/.ssh/authorized_keys` Datei.

## InitRamDisk

1. **What is the difference between dynamic linking at compile time and using dlopen() in the code, and why can't the latter be detected with file and ldd?**

  Dynamische Verknüpfung bezieht sich auf die Verknüpfung, die während des Ladens oder der Laufzeit ausgeführt wird und es löst externe Referenzen auf.
  `dlopen ()`, der als dynamischer Loader bezeichnet wird, lädt die Bibliothek in den Speicher, wenn die Bibliothek nicht bereits geladen ist.
  Der Unterschied ist, dass wir durch dynamisches Verknüpfen einschließen und in der Binärdatei den Namen der Bibliotheken haben. Wenn wir das Programm starten, wird im RAM geprüft, ob die Bibliotheken bereits vorhanden sind. Andernfalls werden sie in den RAM geladen. Ldd kann die Datei finden, da sie bereits fest programmiert ist, welche Bibliotheken sie benötigt. Bei `dlopen()` gibt es keine Includes, keine Angabe, welche Libs benötigt werden. Ldd findet keine Abhängigkeiten. Wenn eine Funktion aus der lib aufgerufen wird, wird die lib in den RAM verschoben.

2. **How does the hostfwd=... help us to access the dropbear instance inside the VM?**

 `hostfwd =` wird verwendet, um eine Verbindung mit der Dropbears-Portnummer herzustellen, die sich in der Datei options.h befindet.
 Die Hostweiterleitung ordnet den localhost-Port 22222 dem Port 22 der virtuellen Maschine zu.

3. **What is the full command that can be executed on your container to log in to the VM via SSH as the root user?**

  `dropbearmulti dbclient root@127.0.0.1 -p 22222 -i ~/.ssh/id_rsa_dropbear`

4. **What is the devpts filesystem mounted at /dev/pts used for when dropbear is configured with --enable-openpty (default)?**

  Dropbear findet ein verfügbares Pseudoterminal und gibt Dateideskriptoren zurück.

5. **If /dev/pts is not set mounted as described above, dropbear falls back to using /dev/(pty?|tty??) devices.**

  Dropbear fällt auf `/dev/tty` zurück.

6 **Which component on the system is responsible for creating these device nodes?**

  The `udev` package creates the device nodes.
