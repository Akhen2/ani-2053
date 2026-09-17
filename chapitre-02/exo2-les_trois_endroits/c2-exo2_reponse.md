# Exercice 2

En respectant les consignes de l'exercice, voici les différents résultats obtenus

## Résultats

PS C:\Users\dell\Desktop\Vide> git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
PS C:\Users\dell\Desktop\Vide> git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   Fichier_1.cpp

no changes added to commit (use "git add" and/or "git commit -a")
PS C:\Users\dell\Desktop\Vide> git add Fichier_1.cpp
PS C:\Users\dell\Desktop\Vide> git status           
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   Fichier_1.cpp

PS C:\Users\dell\Desktop\Vide> git commit -m "Fichier 1 modifier"
[main 1cc0fc4] Fichier 1 modifier
 1 file changed, 6 insertions(+)
PS C:\Users\dell\Desktop\Vide> git status                        
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
PS C:\Users\dell\Desktop\Vide> git push
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 446 bytes | 111.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/Akhen2/Vide.git
   e5283a3..1cc0fc4  main -> main
PS C:\Users\dell\Desktop\Vide> git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean