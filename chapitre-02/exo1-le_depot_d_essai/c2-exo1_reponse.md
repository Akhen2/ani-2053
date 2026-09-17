# Exercice 1

J'ai créé un dépôt contenant 03 fichiers pour cette exercice et voici le commande utiliser : 

## Commandes :


PS C:\Users\dell\Desktop\Vide> git add Fichier_2.cpp
PS C:\Users\dell\Desktop\Vide> git commit -m "Création du deuxieme fichier"            
[main 3f02127] Création du deuxieme fichier
 1 file changed, 11 insertions(+)
 create mode 100644 Fichier_2.cpp
PS C:\Users\dell\Desktop\Vide> git push
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 282 bytes | 94.00 KiB/s, done.
Total 2 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/Akhen2/Vide.git
   acaaca4..3f02127  main -> main
PS C:\Users\dell\Desktop\Vide> git add Fichier_1.cpp                       
PS C:\Users\dell\Desktop\Vide> git commit -m "Création du premier fichier" 
[main f9dd8b7] Création du premier fichier
 1 file changed, 6 insertions(+)
 create mode 100644 Fichier_1.cpp
PS C:\Users\dell\Desktop\Vide> git push                                   
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 242 bytes | 242.00 KiB/s, done.
Total 2 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/Akhen2/Vide.git
   3f02127..f9dd8b7  main -> main
PS C:\Users\dell\Desktop\Vide> git add Fichier.md                         
PS C:\Users\dell\Desktop\Vide> git commit -m "Création du fichier.md"
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
PS C:\Users\dell\Desktop\Vide> git push
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 290 bytes | 96.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/Akhen2/Vide.git
   f9dd8b7..9843627  main -> main
PS C:\Users\dell\Desktop\Vide> git add Fichier.md                    
PS C:\Users\dell\Desktop\Vide> git commit -m "Création du fichier.md"
[main e5283a3] Création du fichier.md
 1 file changed, 1 insertion(+)
PS C:\Users\dell\Desktop\Vide> git push                              
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 341 bytes | 113.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/Akhen2/Vide.git
   9843627..e5283a3  main -> main
PS C:\Users\dell\Desktop\Vide> git log --oneline --graph --all
* e5283a3 (HEAD -> main, origin/main, origin/HEAD) Création du fichier.md
* 9843627 
* f9dd8b7 Création du premier fichier
* 3f02127 Création du deuxieme fichier
* acaaca4 
* 7b2a96e first commit