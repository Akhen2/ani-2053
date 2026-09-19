# Exercice 4 :

## Explication :

Dans le fichier "Fichier_2.cpp" il y a eu comme modification : l'ajout d'une variable, la modification d'une autre et la correction d'un texte

## Résultat

PS C:\Users\dell\Desktop\Vide> git add -p
diff --git a/Fichier_2.cpp b/Fichier_2.cpp
index c9cd2fd..b30fd65 100644
--- a/Fichier_2.cpp
+++ b/Fichier_2.cpp
@@ -3,9 +3,10 @@
 int main(){
     int a = 3;
     int b = 2;
-    int sum = a + b;    
+    float c = 4.5;
+    float sum = a + b + c;
 
-    std::cout << "La somme de " << a << " et " << b << " est: " << sum << std::endl;
+    std::cout << "La somme de " << a << ", " << b << " et " << c << " est: " << sum << std::endl;
 
     return 0;
 }
(1/1) Stage this hunk [y,n,q,a,d,s,e,p,P,?]? y

PS C:\Users\dell\Desktop\Vide> git commit -m "première utilisation de git add -p"
[main a5c7bf9] première utilisation de git add -p
 1 file changed, 3 insertions(+), 2 deletions(-)
PS C:\Users\dell\Desktop\Vide> git push
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 414 bytes | 207.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/Akhen2/Vide.git
   1cc0fc4..a5c7bf9  main -> main
