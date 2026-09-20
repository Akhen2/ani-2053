# Exercice 6 :

Ici, après avoir cloner le dépôt "Vide", il y a eu modification sur la même ligne de chaque de chaque dépôt ce qui a créé un conflit qui a été résolu.

## Résultat

PS C:\Users\dell\Desktop\Vide> git add .                                                   
PS C:\Users\dell\Desktop\Vide> git commit -m "Modification 1"                              
[choix ebc8c90] Modification 1
 1 file changed, 1 insertion(+), 1 deletion(-)
PS C:\Users\dell\Desktop\Vide> git push                                                    
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 290 bytes | 145.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/Akhen2/Vide.git
   4587424..ebc8c90  choix -> choix
PS C:\Users\dell\Desktop\Vide_2> git add .                     
PS C:\Users\dell\Desktop\Vide_2> git commit -m "Modification 2"
[choix ee6cc6f] Modification 2
 1 file changed, 1 insertion(+), 1 deletion(-)
PS C:\Users\dell\Desktop\Vide_2> git push                      
To https://github.com/Akhen2/Vide.git
 ! [rejected]        choix -> choix (non-fast-forward)
error: failed to push some refs to 'https://github.com/Akhen2/Vide.git'
hint: Updates were rejected because the tip of your current branch is behind
hint: its remote counterpart. If you want to integrate the remote changes,
hint: use 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
PS C:\Users\dell\Desktop\Vide_2> git pull
Auto-merging Test.cpp
CONFLICT (content): Merge conflict in Test.cpp
Automatic merge failed; fix conflicts and then commit the result.
PS C:\Users\dell\Desktop\Vide> git add .                     
PS C:\Users\dell\Desktop\Vide> git commit -m "Résolution du conflit"
[choix b80ea2e] Résolution du conflit
 1 file changed, 1 insertion(+), 1 deletion(-)
PS C:\Users\dell\Desktop\Vide> git push                             
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 299 bytes | 149.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/Akhen2/Vide.git
   ebc8c90..b80ea2e  choix -> choix
