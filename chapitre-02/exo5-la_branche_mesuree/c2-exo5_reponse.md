# Exercice 5 :

## Création de la branche

J'ai créé la branche : choix

Et les trois commits ont été réalisés sur cette branche.

## Taille sur le disque dur

Avant l'ajout des commits, sa taille sur le disque était de 0.04 Mo

Mais après l'ajout des commits, la taille est restée sans modification à savoir 0.04 Mo

## Explication 

La taille affichée avant et après l'ajout des commits reste identique cela signifie que les 03 commits ont bel et bien était créés mais que la différence de stockage peut être très faible et ne pas s'afficher avec un affichage arrondi à deux décimales.

## Commandes

PS C:\Users\dell\Desktop\Vide> git branch choix
PS C:\Users\dell\Desktop\Vide> git switch choix
Switched to branch 'choix'
PS C:\Users\dell\Desktop\Vide> git status
On branch choix
nothing to commit, working tree clean
PS C:\Users\dell\Desktop\Vide> git branch
* choix
  main
PS C:\Users\dell\Desktop\Vide> "{0:N2} Mo" -f ((Get-ChildItem -Recurse -Force | Measure-Object -Property Length -Sum).Sum / 1MB)
0,04 Mo
PS C:\Users\dell\Desktop\Vide> git add Test.cpp                     
PS C:\Users\dell\Desktop\Vide> git commit -m "Modification du fichier Test.cpp"
[choix 131629e] Modification du fichier Test.cpp
 1 file changed, 2 insertions(+), 1 deletion(-)
PS C:\Users\dell\Desktop\Vide>  git push --set-upstream origin choix           
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 346 bytes | 173.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/Akhen2/Vide.git
   d7326a8..131629e  choix -> choix
branch 'choix' set up to track 'origin/choix'.
PS C:\Users\dell\Desktop\Vide> git add Test.cpp                                                                                 
PS C:\Users\dell\Desktop\Vide> git commit -m "3e modification faite sur le fichier Test.cpp"
[choix 010dbab] 3e modification faite sur le fichier Test.cpp
 1 file changed, 2 insertions(+), 1 deletion(-)
PS C:\Users\dell\Desktop\Vide>  git push --set-upstream origin choix                        
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 375 bytes | 187.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/Akhen2/Vide.git
   131629e..010dbab  choix -> choix
branch 'choix' set up to track 'origin/choix'.
PS C:\Users\dell\Desktop\Vide> git log --online -3
fatal: unrecognized argument: --online
PS C:\Users\dell\Desktop\Vide> git log --oneline -3
010dbab (HEAD -> choix, origin/choix) 3e modification faite sur le fichier Test.cpp
131629e Modification du fichier Test.cpp
d7326a8 Premier commit
PS C:\Users\dell\Desktop\Vide> "{0:N2} Mo" -f ((Get-ChildItem -Recurse -Force | Measure-Object -Property Length -Sum).Sum / 1MB)
0,04 Mo