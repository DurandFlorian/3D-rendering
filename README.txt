Projet de lancé de rayon réalisé par Florian Durand

Compilation (fonctionne sur Linux et sur Windows):
1. Avoir la version 17 de C++ 
2. Installer la librairie GLUT
3. Installer CMake 2.9 au minimum et build la target RayTracing

Exécution :
Lancer l'exécutable RayTracing présent dans le dossier "build/".

Fonctionnement :
Une fois lancé le programme affiche une fenêtre appelée Ray tracing.
Les carrés en bas sont des scrollbars :
Les trois carrés rouges correspondent à la rotation de la caméra sur les axes x,y et z.
Le carré blanc correspond au zoom.
Les trois carrés verts correspondent à la rotation de la lumière sur les axes x,y et z.
Le carré jaune correspond à la définition du lancé de rayon en largeur et en longueur.
Le carré bleu correspond au niveau maximum de récursivité qui va de 1 à 5.

Scène : 
La scène est composée de :
5 cercles de couleur visibles et d'un cercle transparent en face du cercle rouge.
1 carré central miroir (activer la récursivité) et un carré gris clair transparent.

Implémentation :
La sphère et le cube ont été implémentés avec tous les niveaux de lumières.

Choix : 
J'ai choisi de re coder la librairie afin de m'améliorer en C++ et afin d'approfondir mes connaissances.