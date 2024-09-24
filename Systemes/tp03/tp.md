# TP 3 : Sémaphores

**Q1 : Ecrivez les 4 fonctions permettant une utilisation simple des sémaphores**

Grâce au fichier fourni c'est plutôt simple, il s'agit surtout de couper le code
au bon moment et mettre dans des fonctions.

**Q2 : Vérifiez le fonctionnement des sémaphores en réalisant une exclusion mutuelle entre un processus fils
et un processus père. Pour cela les processus affiche un message en début de section critique et en fin de
section critique**

voir `q2.c`

**Q3 : Donnez le code du programme qui permet de créer le processus fils et génére la sortie
précédante**

(ABABABABABABABABABABABABABAB)

voir `q3.c`, on utilise 2 sémaphores

IMPORTANT : il faut penser à flush le buffer de sortie après chaque printf pour que les messages
soient bien affichés dans la console !

```c
printf("A");
fflush(stdout);
```

**Q4 : Faire alterner ABACABACABACACACAB avec 3 processus**

(L'ordre des B et C n'importe pas)

voir `q4.c`

B et C se battent pour accéder à P2

**Q5 : ABCABCACBACBABC**

(Again, l'ordre des B et C n'importe pas)

voir `q5.c`

**Q6 : Reprendre la deuxième question du TP mais avec des sémaphores Java**

voir `Q6.java`

**Q7 : Toujours même question mais avec des synchronized**

voir `Q7.java`

**Q8 : En Java, implémentez une classe Sémaphore fournissant les 3 méthodes manipulant les sémaphores**

voir `Q8.java`

**Q9 : Modifier l'implémentation pour que le sémaphore gère de façon FIFO les threads**

voir `Q9.java`
