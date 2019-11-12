# SystemSoftware hw1

## Sysinfo Application

1. **What other information can uname tell about a system**

  - kernel-name
  - nodename
  - kernel-release
  - kernel-version
  - mashine
  - processor
  - hardware-platform
  - operating-system

2. **How can you instruct gcc to produce statically linked binaries?**

    mit dem `-static` Befehl

3. **Which tools are able to display  the dynamic dependencies for binaries on Linux?**

  - file a.aut
  - readelf a.out

4. **What is the practical problem with dynamic linking when you want to install  your program on a different system, e.g Virtual Machine?**

  Es fordert zusätzlicher Installation von Bibliotheken auf Platform, um das Programm ausführen zu können.

## Linux Kernel

1. **How can you get more information about an item in the menuconfig?**

  Auf Menuitem im ncurses Menu kommen und `?` drücken.

2. **What is the relation between the menuconfig and the .config file in the kernel source directory?**

  Alle Einstellungen auf menuconfig, welche wir gewählt haben, werden in `.config` Datei gespeichert.

3. **Which CONFIG_\* options belong to the menu entries that are the provided above?**
```
  - CONFIG_64BIT=y
  - CONFIG_HAVE_KERNEL_GZIP=y
  - CONFIG_CC_OPTIMIZE_FOR_SIZE=y
  - CONFIG_PRINTK=y
  - CONFIG_EMBEDDED=y
  - CONFIG_BINFMT_ELF=y
  - CONFIG_BINFMT_SCRIPT=y
  - CONFIG_DEVTMPFS=y
  - CONFIG_TTY=y
  - CONFIG_VT=y
  - CONFIG_CONSOLE_TRANSLATIONS=y
  - CONFIG_VT_CONSOLE=y
  - CONFIG_HW_CONSOLE=y
  - CONFIG_UNIX98_PTYS=y
  - CONFIG_SERIAL_8250=y
  - CONFIG_SERIAL_8250_CONSOLE=y
  - CONFIG_PROC_FS=y
  - CONFIG_PROC_SYSCTL=y
  - CONFIG_SYSFS=y
  - CONFIG_DEFAULT_HOSTNAME="grp15"
```

4. **What are the different times displayed by time?**

  - real	2m12,084s
  - user	3m5,186s
  - sys	0m25,326s

5. **Where and which are the output binary files produced by the compilation?**

  In alle Ordnern, wo es `C` Dateien gibt. Ausgabedateien sind die Datien mit der Endung `.o` und binary Dateien.

6. **Which is the binary that represents bootable kernel image?**

    bzImage Datei in `$KERNEL_SRC/arch/x86/boot` Ordner.

## Run Linux in a Virtual Machine (with qemu)

1. **Which TTY-device do you need to pass to the kernel for console input/output?**

    `console=/dev/tty0`

2. **Is the system in a usable state, e.g. can you use a shell to execute commands on it?**

  nein, man kann keine Befehle eingeben.

3. **If not, what is missing?**

  Es fehlten `.cpio` archiv, was Filesystemdaten enthält und Anwendungs-Binaries.

## InitRamDisk 1

1. **What could the -L parameter be useful for?**

  `-L` parametr dereferensiert symbolische Links und kopiert die Dateien, auf die wir verweisen, anstatt die Links zu kopieren.
  Dadurch können wir symbolische Link anlegen, anstatt gleiche Datei in mehrere Stelle zu kopieren.

2. **How can you list the contents of a CPIO archive?**

  `cpio -it < archiv.cpio`

3. **What is the path of program that the kernel can execute after unpacking it?**

  `bin/sysinfo`

4. **What needs to be passed to the kernel within append in order to tell it what binary to execute?**

  `init=/bin/sysinfo`

5. **What is the default executable path of the kernel in case nothing is passed to change it?**

  `/init`

6. **What is the complete qemu command line to run your sysinfo application as the init process?**

  `qemu-system-x86_64 -m 64 -nographic -kernel artifacts/bzImage -initrd artifacts/initrd-sysinfo.cpio -append "console=ttyS0 init=bin/sysinfo"`

## Busybox

1. **How do multi-call binaries work?**

Multi-call binaries are called using the name of the wanted functionality as a the first (0th) argument.  
Hard or soft links are used to direct calls to the program, which behaves according to the name called with.

2. **What applets are needed to allow us to interact with the system?**

This depends on what we need to do, but some basic functionalities include `ls`, `chmod`, `chgrp`, `mount`, `cd`, `touch`, `vi` or `sed`, and `file`.

3. **How are symlinks to these binaries interpreted?**

Symlinks to the binary are called by their name and link back to the single binary, which then receives the name called with as an argument.

4. **Does your busybox file have dynamic link dependencies against libraries installed on the build host?**

No, we made sure to link the binary statically.

5. **How can you verify this on the command line?**

Using the `file` utility, we can see that the binary is statically linked

## InitRamDisk 2

1. **What busybox options have you chosen for your new initrd, and why?**

We chose some basic administrative tools, to allow making and removing files and directories as well as editing them.  
We chose some mod utilities because the end goal is to develop a device driver that will require these utilities to be used.
We bound busybox statically to avoid dll dependencies that our embedded linux kernel would not have.  
We exluded /usr because the kernel did not use it, and later instructions excluded it also.

2. **Which additional directories are required to make the system work at runtime?**

`/dev`, `/sys`, `/proc`, `/tmp`, `/sbin`

3. **Which directories need to be created to be compliant with the Linux FHS 3.0?**

`/bin`, `/boot`, `/dev`, `/etc`, `/lib`, `/media`, `/mnt`, `/opt`, `/run`, `/sbin`, `/srv `, `/tmp`, `/usr`, `/var`.

4. **What are all the mounts/filesystems that are active after the system has booted?**

the device fs, system fs, process fs, temporary fs, and bin and sbin which hold the binaries callable by the system.

5. **How does the filetree under / look after the system is booted? (Please don't include all device, sys, and proc entries in your answer)**

```
/
├──bin
│  └── ...
├──dev
│  └── ...
├──init
├──initrd-busybox.cpio
├──linuxrc
├──proc 
│  └── ...
├──root
├──sbin
│  ├── init
│  ├── insmod
│  ├── klogd
│  ├── lsmod
│  ├── poweroff
│  ├── reboot
│  ├── rmmod
│  ├── swapoff
│  └── syslogd
├──sys
│  └── ...
├──tmp
├──usr
```
