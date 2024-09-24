# TP 2 : Signaux

## Q1 : Compilez et exécutez le programme deroutement. Qu’observez vous ? Corrigez le programme.

Le programme affiche "div 0" en boucle.
Il faut décommenter la ligne 17 pour que le handler 
redonne la main au programme au bon endroit.

## Q2 : Observez le comportement du programme signal.

Dans la première version on masque aucun signal.
Puisque le fils est ralenti par un sleep le signal est
envoyé avant e suspend donc il est perdu.

Dans la deuxième version on masque le signal SIGUSR1.
Quand il arrive au fils il est masqué donc il est marqué en attente.
Quand le fils se suspend il met un masque vide donc le signal peut être traité,
ce qui réveille le fils.

## Q3 : Ecrivez un programme qui crée un processus. Après la création du processus fils, le processus père rentre dans une boucle sans fin dans laquelle il écrit le caractère “a”. Le processus fils rentre aussi dans une boucle sans fin et écrit le caractère “b”.

Voir `boucle.c`
On utilise `fork()` et `while(1)`

## Q4 : Modifier votre programme, en utilisant des signaux, pour permettre que le père écrive d’abord 10 caractères “a”, puis attend la mort de son fils. Le fils doit attendre que le père écrive ces 10 caractères “a” avant d’écrire à son tour 10 caractères “b”

On copie les opérations sur masque et le handler de signal.
Le handler est nécessaire pour que le signal ne soit pas ignoré.

## Q5 : On a un programme de calcul dont on prévoit que l’exécution sera très longue. On veut éviter de perdre du temps en affichant à l’écran de façon systématique l’étape du calcul que l’on est en train d’exécuter. Comment faire pour savoir où le programme en est quand on le souhaite ? Illustrer votre solution avec un programme qui incrémente un compteur toutes 10000 itérations

J'ai fait beaucoup trop compliqué dans `update.c` il paraît, en plus le père ne reçoit pas tous les signaux
car il y en a trop.

Dans `update2.c` il y a une version simplifiée où c'est le terminal qui
envoie des signaux (on attrape SIGINT).
Faire Ctrl-C print le compteur. Inconvénient : on ne peut pas quitter simplement.
Solution : `stty quit ^R` avant d'exécuter le programme pour pouvoir
envoyer SIGQUIT avec Ctrl-R depuis le terminal,
sinon on peut toujours ouvrir un autre terminal et `pkill -9 update2`

## Q6 : Ecrire un programme comprenant 2 processus. Le père envoie des signaux SIGUSR1 à son processus fils. Comparez le nombre de signaux emis par le père avec le nombre de signaux reçus par le fils.

Déjà fait dans `update.c` ! Ce n'était pas une mauvaise solution, juste la solution
d'une autre question ! (n fait plutôt fils vers père mais c'est pareil)

La réponse c'est que on reçoit moins de signaux qu'on en envoie.

Voir `sendsignals.c`

## Q7 : Modifiez votre programme pour que le fils ne perde aucun signal.

Il faut masquer le signal tant qu'on est pas prêt à le handle.
