#include <stdio.h>
#include <stdlib.h> //includes the exit function
#include <string.h>
#include <stdbool.h>

char menuDisplay(char menu){  //menu can take p (for principal menu), o(opérations), a(affichage), f(fidélisation)
    print("******** Bank's Accounts Management System *******\n");
    switch(menu)
    {
        case 'p' :
            printf("\n1. Introduire un compte bancaire\n2.Introduire plusieurs comptes bancaires\n3. Opérations\n4. Affichage\n5. Fidélisation\n6. Quitter");
            scanf(" %c", &choice);
            break;
        case 'o' :
            printf("\n1. Retrait\n2. Dépôt\n3. Retourner au menu principal\n4. Quitter");
            scanf(" %c", &choice);
            break;
        case 'a' :
            printf("\n1. Par Ordre Ascendant\n2. Par Ordre Descendant\n3. Montant > ?\n4. Recherche par CIN\n5. Retourner au menu principal\n6. Quitter"); //Don't forget to add another submenu for ascending and descending
            scanf(" %c", &choice);
            break;
        case 'f' :
            printf("\nVoulez vous ajoutez aux 3 comptes ayant les montants les plus supérieurs 1.3%? Y/N:"); //Try to display the 3 accounts first
            scanf(" %c", &choice);
            break;
    }
}
bool operations(){
    char choice;
    choice = menuDisplay('o');
    if(choice == '1') withdrawal();
    else if (choice == '2') deposit();
    else

    getch();
    system("cls");
    return true;
}
void main(){
    char choice;
    bool repeat = true;
    do {
    choice = menuDiplay();
    switch (choice){
        case '1':
            repeat = createAccount();
            break;
        case '2':
            repeat = createAccounts();
            break;
        case '3':
            repeat = operations();
            break;
        case '4':
            repeat = Affichage();
            break;
        case '5':
            repeat = loyalty();
            break;
        case '6':
            exit(0);
    }
    }while(repeat);
    if (repeat == false) exit(0);

}
