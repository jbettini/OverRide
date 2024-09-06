## Solution

```
322424827
```

Le programme prend une entrée utilisateur qui est envoyée à la fonction test en tant que premier argument, avec le second argument fixé à 322424845.

Dans la fonction ```test```, un ```switch``` est effectué sur le résultat de l'opération ```a2 - a1``` (c'est-à-dire la différence entre le second et le premier argument). Le comportement est le suivant :

-   Si le résultat de ```a2 - a1``` est compris entre 1 et 9, ou entre 16 et 21, la fonction ```decrypt``` est appelée avec cette différence comme argument.
-   Pour toutes les autres valeurs, un nombre aléatoire généré par ```rand()``` est passé à la fonction ```decrypt```.

Dans la fonction ```decrypt``` :

-   Une chaîne chiffrée, ```"Q}|usfg~sf{}|a3"```, est stockée dans ```v4```.
-   Une boucle parcourt chaque caractère de ```v4``` et applique un XOR entre ce caractère et la valeur de ```a1``` (l'argument de la fonction ```decrypt```).
-   Une fois la boucle terminée, si le contenu de ```v4``` est égal à ```"Congratulations!"```, un shell est lancé via un appel à ```system("/bin/sh")```.
-   Si ce n'est pas le cas, un message d'erreur est affiché avec ```puts("Invalid Password")```.

Pour obtenir le pass il suffira juste de bruteforce les 21 possibilité donc de 322424824 a 322424845

### Payload

```
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424826

Invalid Password
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ 
```