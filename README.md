# Projet ZZ1 - Labyrinthe

## Consignes
[Lien vers les consignes](https://perso.isima.fr/~yjdaniel/labyrinthe/projet-labyrinthe.html)


## Info Git

git branch  :  affiche toutes les branches en local  
git checkout master :  bascule sur la branche master  
git checkout -b test  :  crée la branche test et bascule dessus  
git merge origin/test  :  fusionne test avel la branche courante -> gestion des conflits  
git branch -d test  :  supprime la branche test en local  
git push origin :test  : supprime la branche test en distant  

## Convention nommage commit

<ul>
<li><code>build</code> : changements qui affectent le système de build ou des dépendances externes (npm, make…)</li>
<li><code>ci</code> : changements concernant les fichiers et scripts d’intégration ou de configuration (Travis, Ansible, BrowserStack…)</li>
<li><code>feat</code> : ajout d’une nouvelle fonctionnalité</li>
<li><code>fix</code> : correction d’un bug</li>
<li><code>perf</code> : amélioration des performances</li>
<li><code>refactor</code> : modification qui n’apporte ni nouvelle fonctionalité ni d’amélioration de performances</li>
<li><code>style</code> : changement qui n’apporte aucune alteration fonctionnelle ou sémantique (indentation, mise en forme, ajout d’espace, renommante d’une variable…)</li>
<li><code>docs</code> : rédaction ou mise à jour de documentation</li>
<li><code>test</code> : ajout ou modification de tests</li>
</ul>

