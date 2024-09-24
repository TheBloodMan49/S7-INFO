# Réponse aux questions du TP 1

## Q1 : Compilez puis exécutez le programmme pid.c. Qu’observez vous ?

Le processus crée un fils, et les 2 afichent leur pid.

## Q2 : Modifiez ce programme pour qu’il affiche le numéro du père du processus qui exécute votre programme. Qu’en concluez vous ?

Le terminal est le père du programme.

## Q3 : Compilez, exécutez le programme exec.c. Que fait-il ?

Il lance xterm dans un nouveau processus.

## Q4 : Compilez et exécutez le programme exec2.c pendant son exécution tapez dans un autre terminal la commande ps -a. Qu’observez-vous ?

On observe 2 instance du processus "exec2", malgré que seul le père est censé tourner en boucle.
En réalité, le fils a terminé son exécution, mais le père ne l'a pas encore réalisé.

## Q5 : Compilez et exécutez le programme MonThread.java. Modifiez le programme pour que l’exécution ne soit pas séquentielle

On décommente la ligne avec `mt.start();` pour lancer le thread en parallèle.

## Q6 : Compilez et exécutez le programme entrelace.c, Observez soigneusement ce qui a été affiché sur le terminal (remontez sur les affichages). Qu’en concluez vous ?

Au début on observe uniquement des "je suis le père", ensuite ils sont correctement entrelacés, et à la fin il n'y a plus que des "je suis le fils".
Le fils démarre après le père, puis l'ordonnanceur leur attribue équitablement du temps CPU.

## Q7 : Pour mieux voir l’effet de l’ordonnanceur nous avons ajouté des attentes (sleep()) dans le programme entrelace2.c. Compilez et exécutez le. Que pouvez vous en conclure sur l’ordonnanceur

Parfois les lignes ne sont pas entrelacées correctement. L'ordonnanceur ne garantit pas un ordre d'exécution précis.

## Q8 : Ecrivez cree10 pour creer 10 processus fils

Voir cree10.c

## Q9 : Mêmes questions avec les Threads et les fichiers Entrelace.java et Entrelace2.java

Idem, l'ordonnanceur ne garantit pas un ordre d'exécution précis.

## Q10 : Lors de la création d’un processus par fork(), l’espace d’adressage du processus père est dupliqué. Lisez bien le code du programme variable.c et devinez ce qu’il doit afficher. Compilez puis exécutez ce programme. Qu’observez-vous ?

Le père et le fils ont des adresses mémoires différentes, et les modifications de l'un ne sont pas répercutées sur l'autre.
La variable i est donc initialisée à 1 pour les 2, mais les modifications après le fork ne sont pas partagées.

## Q11 : Lisez, compilez, excécutez le programme Variable.java. Qu’observez-vous ?

En Java, l'objet VarObjet est copié par référence donc les modifications sont partagées entre le père et le fils.

## Q12 : Ecrivez un programme qui crée une hiérarchie de processus. Où chaque processus crée 2 fils qui eux même créerons 2 fils... Votre programme doit générer une hiérarchie à 4 niveaux. Chaque processus doit afficher son identité ainsi que celle de son père

C'est plus compliqué de le faire correctement que ça en a l'air !
Voir hierarchie.c

## Q13 : Modifiez votre programme pour qu’il affiche le nom de ses “ancêtres” jusqu’au premier processus père de votre programme
