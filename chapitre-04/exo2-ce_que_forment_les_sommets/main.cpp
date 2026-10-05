#include <iostream>
#include <string>

int main(){
    int N;
    std::string type;

    std::cout << "Entrez le nombre de sommet " << std::endl;
    std::ci, >> N;

    std::cout << "Entrez le type de primitive " << std::endl;
    std::cin >> type;

    if(N <= 0){
        std::cout << "Nombre de sommet invalide" << std::endl;
    }

    int forme = 0;
    int reste = 0;

    if(type == "Points"){
        reste = 0;
        forme = N;
    }
    else if(type == "Line_strip"){
        reste = 0;
        forme = (N >= 2) ? N - 2 : 0;
    }
    else if(type == "Lines"){
        reste = N%2;
        forme = N/2;
    }
    else if(type == "Triangle"){
        reste = N%3;
        forme = N/3;
    }
    else if(type == "Triangle_strip"){
        reste = 0;
        forme = (N >=3) ? N - 2 : 0;
    }
    else if(type == "Triangle_fan"){
        reste = 0;
        forme = (N >= 3) ? N - 2 : 0;
    }

    std::cout << forme << " " << type << " " << reste << " " << "Sommet restant " << std::endl; 

    return 0;
}
