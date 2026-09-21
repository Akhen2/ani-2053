# Exercice 4 :

## Explication :

Dans le fichier "Fichier_2.cpp" il y a eu comme modification : l'ajout d'une variable, la modification d'une autre et la correction d'un texte

## Résultat

``````bash
PS C:\Users\dell\Desktop\Vide> git add -p
diff --git a/Fichier_2.cpp b/Fichier_2.cpp
index b30fd65..2a2bfa6 100644
--- a/Fichier_2.cpp
+++ b/Fichier_2.cpp
@@ -3,10 +3,10 @@
 int main(){
     int a = 3;
     int b = 2;
-    float c = 4.5;
-    float sum = a + b + c;
+    float c = 4.6;
+    float sum = a + b * c;
 
-    std::cout << "La somme de " << a << ", " << b << " et " << c << " est: " << sum << std::endl;
+    std::cout << "Le calcul de " << a << ", " << b << " et " << c << " donne: " << sum << std::endl;
 
     return 0;
 }
(1/1) Stage this hunk [y,n,q,a,d,s,e,p,P,?]? ?
y - stage this hunk
n - do not stage this hunk
q - quit; do not stage this hunk or any of the remaining ones
a - stage this hunk and all later hunks in the file
d - do not stage this hunk or any of the later hunks in the file
s - split the current hunk into smaller hunks
e - manually edit the current hunk
p - print the current hunk
P - print the current hunk using the pager
? - print help
(1/1) Stage this hunk [y,n,q,a,d,s,e,p,P,?]? s
Split into 2 hunks.
@@ -3,6 +3,6 @@
 int main(){
     int a = 3;
     int b = 2;
-    float c = 4.5;
-    float sum = a + b + c;
+    float c = 4.6;
+    float sum = a + b * c;
 
(1/2) Stage this hunk [y,n,q,a,d,k,K,j,J,g,/,e,p,P,?]? y
@@ -8,5 +8,5 @@
 
-    std::cout << "La somme de " << a << ", " << b << " et " << c << " est: " << sum << std::endl;
+    std::cout << "Le calcul de " << a << ", " << b << " et " << c << " donne: " << sum << std::endl;
 
     return 0;
 }
(2/2) Stage this hunk [y,n,q,a,d,K,J,g,/,e,p,P,?]? y

PS C:\Users\dell\Desktop\Vide> git commit -m "Modification de l'exercice 4"
[choix ed33184] Modification de l'exercice 4
 1 file changed, 3 insertions(+), 3 deletions(-)
PS C:\Users\dell\Desktop\Vide> git push
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 344 bytes | 114.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/Akhen2/Vide.git
   4325efd..ed33184  choix -> choix
``````