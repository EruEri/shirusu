# Shirusu

A simple program that store notes.

All your notes live in your ```$XDG_DATA_HOME/shirusu``` directory which will
probably be ```~/.local/share/shirusu```

## Initialization

To start with ```shirusu```, you first need to initialize it
```
$ shirusu init --help
Usage:
    shirusu init - Initialiaze shirusu

    shirusu init [OPTIONS]...
Description:
    Initialiaze shirusu by creating a directory in the $XDG_DATA_HOME directory
Options:
    -h, --help             Show help
        --version          Show version
``` 

## Take a note

```shirusu``` relies on 2 environment variables:
- SHIRUSU_EDITOR:
    - try to open the note with if define
- EDITOR:
    - try to open the note with if define and SHIRUSU_EDITOR is not define

if any of these variables is defined or well-configured,
```shirusu``` will try to open the note with one of the known editors defined 
in [src/shiru_misc.c](src/shiru_misc.c)

``` 
$ shirusu --help
Usage:
    shirusu - A simple quick thought note taker

    shirusu [COMMAND] [OPTIONS]...
    shirusu [-n <name> | --name <name> | -x <name> ] [-m <message> | --message <message>]
Options:
    -n, --name=NAME        Name of the new note
    -x,       =NAME        Name of the existing note
    -m, --message=MESSAGE  Content of the note
    -h, --help             Show help
        --version          Show version
Commands:
    init                   Initialiaze init
    list                   List notes
    cat                    Print notes
Environments:
    SHIRUSU_EDITOR         Try to open note with if define
    EDITOR                 Try to open note with if SHIRUSU_EDITOR isn't define
```

## Build

You need:
- C compiler compliant c99
- GNU make
- probably an Unix/Unix-lite system (MacOS / Linux / FreeBSD / ...):
    - I don't know if it will work on Windows
    

