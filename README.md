# Projet de Jeu Vidéo en C++ avec SFML

## Présentation du Projet

Ce projet consiste à développer un jeu vidéo en C++ utilisant la bibliothèque SFML (Simple and Fast Multimedia Library) pour la gestion des graphiques, des sons et des entrées. Le concept du jeu est le suivant :

- Le joueur est dans le noir complet.
- Le seul point de lumière est autour de la souris avec un rayon défini.
- Lorsque la souris s'approche d'un objet "Interactible" (un objet interactif), cet objet apparaît à l'écran (seule la partie éclairée est visible).
- Si l'objet est éclairé pendant plus d'un certain temps, l'effet de cet objet s'active.
- Le but est de trouver un bébé parmi tous les objets interactifs avant la fin du chronomètre.
- Lorsque le bébé est trouvé, le chronomètre se réinitialise, de nouveaux objets interactifs apparaissent aléatoirement, et le jeu recommence.
- À chaque niveau, plus d'objets interactifs apparaissent et le chronomètre devient plus court.

## Diagramme de classes

![Diagramme de Classes]('Babssal - Class Diagram.jpeg')

Le diagramme de classes ci-dessus montre les principales classes et leurs relations dans le projet.
