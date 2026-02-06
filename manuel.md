# Manuel d'utilisation

## Construction de la commande
1. charger et extraire le fichier zip
2. exécuter la commande `make build ./LogAnalyzer` //heu la je suis pas sure que ce soit ca

## Affichage des 10 ressources les plus fréquentées

`./LogAnalyzer <nomfichier.log>`
Cette commande ne génère pas de graphe

## Création du graphe simple
 `./LogAnalyzer -g <nomfichier.dot> <nomfichier.log>`
 Va créer un graphe en format GraphWiz dans le fichier <nomfichier.dot>. Si le fichier exite déjà, il sera remplacé
 
 ## Création du graphe avec exclusion de certains fichiers
 `./LogAnalyzer -e <nomfichier.dot>
 Exclut du graphe les fichiers d'extension javascript, css et photos

