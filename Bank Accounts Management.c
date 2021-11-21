#include <stdio.h>
#include <stdlib.h> //includes the exit function
#include <string.h>
#include <stdbool.h>
struct user {
    //char fName[50];
    char *fName;
    char *lName;
    char *CIN;
    double sum;
};

char menuDisplay(char menu, char *choice){  //menu can take p (for principal menu), o(opérations), a(affichage), f(fidélisation)
    //printf("\n choice in menu function %c", *choice);
    printf("******** Bank's Accounts Management System *******\n");
    switch(menu)
    {
        case 'p' :
            printf("\n1. Introduire un compte bancaire\n2. Introduire plusieurs comptes bancaires\n3. Operations\n4. Affichage\n5. Fidelisation\n6. Quitter\n");
            scanf(" %c", choice);
            break;
        case 'o' :
            printf("\n1. Retrait\n2. Dépôt\n3. Retourner au menu principal\n4. Quitter");
            scanf(" %c", choice);
            break;
        case 'a' :
            printf("\n1. Par Ordre Ascendant\n2. Par Ordre Descendant\n3. Montant > ?\n4. Recherche par CIN\n5. Retourner au menu principal\n6. Quitter"); //Don't forget to add another submenu for ascending and descending
            scanf(" %c", choice);
            //if(choice == '6') return '6';
            break;
        case 'f' :
            printf("\nVoulez vous ajoutez aux 3 comptes ayant les montants les plus supérieurs 1.3%? Y/N:"); //Try to display the 3 accounts first
            scanf(" %c", choice);
            break;
    }
    system("cls");
    //return choice;
}

bool createAccounts(int currentCount, int accountsNum, struct user *pStruct){
    //int i = 0;
    for(currentCount ; currentCount < accountsNum; currentCount++){
    printf("\nEntrer le nom d'utilisateur de compte :");
    scanf(" %s", pStruct->lName);
    printf("\nEntrer le prenom d'utilisateur :");
    scanf(" %s", pStruct->fName);
    printf("\nEntrer le CIN d'utilisateur :");
    scanf(" %s", pStruct->CIN);
    printf("\nEntrer le montant :");
    scanf(" %lf", pStruct->sum); //montant as a double
    system("cls");
    }
    return true;
}
void withdrawal(){}
void deposit(){}

bool operations(){ // Withdraw and deposit operations on accounts
    char choice;
    choice = menuDisplay('o', &choice);
    if(choice == '1') withdrawal();
    else if (choice == '2') deposit();
    else if (choice == '3') return true;
    return true;
}
bool affichage(){
}
bool loyalty(){ //fidélisation des clients
}

struct user* initiliazeUsersArray(int sizeToAllocate, struct user *userAccounts){
    userAccounts = malloc(sizeToAllocate * sizeof(struct user)); // de don't need to explicitly cast return type of malloc unless we want to run by C++ compiler
    if(userAccounts == NULL) {printf("\nMemory not allocated for user accounts"); return NULL;}
    userAccounts->fName = malloc((50 + 1) * sizeof(char));  //+1 is consider the terminating character of strings \0
    if(userAccounts->fName == NULL){printf("\nMemory not allocated for fName"); return NULL;}
    userAccounts->lName = malloc((50 + 1) * sizeof(char));
    if(userAccounts->lName == NULL) {("\nMemory not allocated for lName"); return NULL;}
    userAccounts->CIN = malloc((50 + 1)* sizeof(char));
    if(userAccounts->CIN == NULL){printf("\nMemory not allocated for CIN"); return NULL;}
    //we don't need to call malloc again for sum because it is not a pointer to something
    return userAccounts;
};
void main(){
    char choice = '6';
    int accountsNum = 1;
    int i = 0;
    bool repeat = true;
    int initialStrucSize = 20; //use i value and compare it to initialStrucSize to know if we need to realloc userAccounts struct array
                                //i is used also to follow users order of input
    struct user *userAccounts = initiliazeUsersArray(initialStrucSize, userAccounts);
    do{
    if(userAccounts != NULL) menuDisplay('p', &choice);
    printf("\n choice : %c", choice);
    switch (choice){
        case '1':
            if(i > initialStrucSize) userAccounts = realloc(userAccounts, i);
            repeat = createAccounts(i, 1, userAccounts);
            i++;
            break;
        case '2':
            accountsNum = 1;
            printf("\nCombien de compte comptes voulez-vous créer?");
            scanf(" %d", accountsNum);
            if(i + accountsNum > initialStrucSize) userAccounts = realloc(userAccounts, i + accountsNum);
            repeat = createAccounts(i, accountsNum, userAccounts);
            i += accountsNum;
            break;
        case '3':
            repeat = operations();
            break;
        case '4':
            repeat = affichage();
            break;
        case '5':
            repeat = loyalty();
            break;
        case '6': //Quitter l'appplication
            free(userAccounts);
            free(userAccounts->fName);
            free(userAccounts->lName);
            free(userAccounts->CIN);
            exit(0);
    }
    }while(repeat);

    free(userAccounts);
    free(userAccounts->fName);
    free(userAccounts->lName);
    free(userAccounts->CIN);
    exit(0);
}
