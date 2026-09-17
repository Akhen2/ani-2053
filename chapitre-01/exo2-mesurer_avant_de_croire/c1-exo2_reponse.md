# Exerceci 2

Les nombres de chaque fichiers sources sont :
1609 fichiers .cpp . Elle a obtenu grâce à la commande : (Get-ChildItem -path . -Filter *.cpp -Recurse | Measure-Object).Count

2728 fichiers .h . Elle a obtenu grâce à la commande : (Get-ChildItem -path . -Filter *.h -Recurse | Measure-Object).Count

311 fichiers .c . Elle a obtenu grâce à la commande : (Get-ChildItem -path . -Filter *.c -Recurse | Measure-Object).Count

60 fichiers .hpp  . Elle a obtenu grâce à la commande : (Get-ChildItem -path . -Filter *.hpp -Recurse | Measure-Object).Count

Le nombre de ligne trouvée est de : 1 342 559 lignes grâce à l'extension : codeline counter sur VS code

Donc la somme des fichiers .cpp et .h est de : 4 337 fichiers source

## Comparaison

Dans le chapitre 1, nous avons 1 193 385 lignes mais avec Powershell nous obtenons 1 809 767 grace à la commande : (Get-ChildItem -Path . -Recurse -File | Where-Object { $_.Extension -in ".cpp", ".h", "c", ".hpp" } | Get-Content | Where-Object { $_. Trim() -ne "" -and $_. Trim() -notmatch '^//' -and $_. Trim() -notmatch '^/\*' -and $_. Trim() -notmatch '^\*' -and $_. Trim() -notmatch '^\*/'} | Measure-Object).Count 

ce qui nous fait une différence de 

Dans le chapitre 1, nous avons 2 641 fichiers source mais avec mes commandes j'ai eu 4 337 fichiers source donc avec une différence de 1696
