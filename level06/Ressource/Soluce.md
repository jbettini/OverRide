# Level 06

```
    lololol
    6233797
```
## Solution

Dans le code source on peu remarquer que nos input pour login et serial son envoyer a une fonction auth
la fonction auth va comparer serial avec local_14 si les deux sont egale cela va lancer un shell
lors de la comparaison local_14 a ete passer dans un algo de cryptage afin de savoir sa valeur on a qu'a copier le code et le compiler
ajouter un printf a la fin et on aura sa valeur :

```
tem@MacBook-Pro-de-Bettini Ressource % gcc decrypt.c 
xtem@MacBook-Pro-de-Bettini Ressource % ./a.out lololol
Hash =  0x7fffffffdde4 | 6233797 
```

Pour le login lololol local_14 sera egale a 623379 plus qu'a mettre cette valeur dans serial et le level est fini :

### Payload
```
    level06@OverRide:~$ ./level06 
    ***********************************
    *		level06		  *
    ***********************************
    -> Enter Login: lololol
    ***********************************
    ***** NEW ACCOUNT DETECTED ********
    ***********************************
    -> Enter Serial: 6233797
    Authenticated!
    $ 
```