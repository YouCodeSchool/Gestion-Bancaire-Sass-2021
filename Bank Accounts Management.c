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

void menuDisplay(char menu, char *choice){  //menu can take p (for principal menu), o(opérations), a(affichage), f(fidélisation)
    //printf("\n choice in menu function %c", *choice);
    printf("\n******** Bank's Accounts Management System *******\n");
    switch(menu)
    {
        case 'p' :
            printf("\n1. Introduire un compte bancaire\n2. Introduire plusieurs comptes bancaires\n3. Operations\n4. Affichage\n5. Fidelisation\n6. Quitter\n");
            scanf(" %c", choice);
            break;
        case 'o' :
            printf("\n1. Retrait\n2. Dépôt\n3. Retourner au menu principal\n4. Quitter\n");
            scanf(" %c", choice);
            break;
        case 'a' :
            printf("\n1. Par Ordre Ascendant\n2. Par Ordre Descendant\n3. Montant > ? Ordre Ascendant\n4. Montant > ? Ordre Descendant\n5. Recherche par CIN\n6. Retourner au menu principal\n7. Quitter\n"); //Don't forget to add another submenu for ascending and descending
            scanf(" %c", choice);
            //if(choice == '6') return '6';
            break;
        case 'f' :
            printf("\nVoulez vous ajoutez aux 3 comptes ayant les montants les plus supérieurs 1.3%? Y/N:  "); //Try to display the 3 accounts first
            scanf(" %c", choice);
            break;
    }
    system("cls");
    //return choice;
}

bool createAccounts(int currentCount, int accountsNum, struct user *pStruct){
    //printf("\ncurrentCount : %d, and accountsNum to add is : %d ", currentCount, accountsNum);
    //int i = 0;
    struct user *ptrStartOfStructArray = pStruct;
    pStruct += currentCount;

    for(currentCount ; currentCount < (currentCount + accountsNum); accountsNum--){
    printf("\nEntrer le nom d'utilisateur de compte :");
    scanf(" %s", pStruct->lName);
    //printf("\nYou entered  : %s", pStruct->lName);
    printf("\nEntrer le prenom d'utilisateur :");
    scanf(" %s", pStruct->fName);
    printf("\nEntrer le CIN d'utilisateur :");
    scanf(" %s", pStruct->CIN);
    printf("\nEntrer le montant :");
    scanf(" %lf", &pStruct->sum); //montant as a double
    system("cls");
    //printf("\nLe montant : %lf\n", pStruct->sum);
    pStruct++;
    }
    /*pStruct--;
    printf("\nfname in first element of array struct fName: %s, lName :  %s,  CIN : %s,  sum : %lf", pStruct->fName, pStruct->lName, pStruct->CIN, pStruct->sum);
    pStruct = ptrStartOfStructArray;
    printf("\nfname in first element of array struct fName: %s, lName :  %s,  CIN : %s,  sum : %lf", pStruct->fName,pStruct->lName, pStruct->CIN, pStruct->sum);
    */
    return true;
}
void withdraw(){}
void deposit(){}

bool operations(){ // Withdraw and deposit operations on accounts
    char choice;
    menuDisplay('o', &choice);
    if(choice == '1') withdraw();
    else if (choice == '2') deposit();
    else if (choice == '3') return true;
    return true;
}
void swap(double *ptrSwap1, double *ptrSwap2)
{
    double temp = *ptrSwap1;
    *ptrSwap1 = *ptrSwap2;
    *ptrSwap2 = temp;
}
void selectionSortDouble(char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount){
    struct user *userAccountToBeSwaped;
    int i, j, min_idx, max_idx;
    if(sortBy == 'a') {
        for (i = 0; i < currentCount-1; i++){ // we did sizeArr-1 because it is not necessary for i to get to the last element of the array
            min_idx = i;
            for (j = i+1; j < currentCount; j++){
                if (userAccounts->sum > (userAccounts++)->sum);
                    min_idx = j;
            }
            userAccounts -= (j - 1);
            userAccountToBeSwaped = userAccounts + i;
            userAccounts += min_idx;
            swap(&userAccountToBeSwaped->sum, &userAccounts->sum);
        }
        userAccounts -= min_idx;
        //printf("%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
    }
    else if (sortBy == 'd'){
        for (i = 0; i < currentCount-1; i++){
            max_idx = i;
            for (j = i+1; j < currentCount; j++){
                if (userAccounts->sum < (userAccounts++)->sum);
                    max_idx = j;
            }
            userAccounts -= (j - 1);
            userAccountToBeSwaped = userAccounts + i;
            userAccounts += max_idx;
            swap(&userAccountToBeSwaped->sum, &userAccounts->sum);
        }
        userAccounts -= max_idx;
        //printf("%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
    }
    //affichage
    printf("\nNom\t|\tPrenom\t|\tCIN\t|\tMontant");
    for (i = 0; i < currentCount; i++){
        if(userAccounts->sum > minSumToDisplay){
            for (i ; i < currentCount; i++){
                printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
                userAccounts++;
            }
            break;
        }
        userAccounts++;
    }
};
void sortFunction(char *subChoice, char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount){
    switch(*subChoice){
        case '1':
            selectionSortDouble(sortBy, minSumToDisplay, userAccounts, currentCount);
            break;
        case '2' :
            //selectionSortString(sortBy, *subChoice, userAccounts, currentCount);
            break;
        case '3' :
            //selectionSortString(sortBy, *subChoice, userAccounts, currentCount);
            break;
    }
}
bool affichage(char choice, struct user *userAccounts, int currentCount){
    char subChoice;
    double minSumToDisplay = 0.0;
    switch(choice){
        case '1': //Trier en ascendant
            printf("\nTrier en ascendant par :\n1. Montant \n2. Nom \n3. Prenom\n");
            scanf(" %c", &subChoice);
            sortFunction(&subChoice, 'a', minSumToDisplay, userAccounts, currentCount); //Pass the sub choice and the operation to perform ascending or descending
            break;
        case '2': //Trier en descendant
            printf("\nTrier en descendant par :\n1. Montant \n2. Nom \n3. Prenom\n");
            scanf(" %c", &subChoice);
            sortFunction(&subChoice, 'd', minSumToDisplay, userAccounts, currentCount); //Pass the sub choice and the operation to perform ascending or descending
            break;
        case '3':  // Montant > ? Ordre Ascendant
            printf("\nEntrer le montant minimum a afficher\n");
            scanf(" %lf", &minSumToDisplay);
            subChoice = '1';
            sortFunction(&subChoice, 'a', minSumToDisplay, userAccounts, currentCount);
            break;
        case '4': // Montant > ? Ordre Descendant
            printf("\nEntrer le montant minimum a afficher\n");
            scanf(" %lf", &minSumToDisplay);
            subChoice = '1';
            sortFunction(&subChoice, 'd', minSumToDisplay, userAccounts, currentCount);
            break;
        case '5': // Recherche par CIN
            //searchCIN();
            break;
        case '6': //Retourn to principal menu
            system("cls");
            return true;

    }
    return true;
}
bool loyalty(){ //fidélisation des clients
}

struct user* initiliazeUsersArray(int sizeToAllocate, struct user *userAccounts){
    int i = 0;
    userAccounts = malloc(sizeToAllocate * sizeof(struct user)); // de don't need to explicitly cast return type of malloc unless we want to run by C++ compiler
    if(userAccounts == NULL) {printf("\nMemory not allocated for user accounts"); return NULL;}
    struct user *startingPoint = userAccounts;
    for(i; i < sizeToAllocate; i++){
        userAccounts->fName = malloc((50 + 1) * sizeof(char));  //+1 is consider the terminating character of strings \0
        if(userAccounts->fName == NULL){printf("\nMemory not allocated for fName"); return NULL;}
        userAccounts->lName = malloc((50 + 1) * sizeof(char));
        if(userAccounts->lName == NULL) {("\nMemory not allocated for lName"); return NULL;}
        userAccounts->CIN = malloc((50 + 1)* sizeof(char));
        if(userAccounts->CIN == NULL){printf("\nMemory not allocated for CIN"); return NULL;}
        //we don't need to call malloc again for sum because it is not a pointer to something
        userAccounts++;
    }

    return startingPoint;
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
    //printf("\n choice : %c", choice);
    switch (choice){
        case '1':
            if(i > initialStrucSize) userAccounts = realloc(userAccounts, i);
            repeat = createAccounts(i, 1, userAccounts);
            i++;
            break;
        case '2':
            accountsNum = 1;
            printf("\nCombien de compte comptes voulez-vous creer?");
            scanf(" %d", &accountsNum);
            if(i + accountsNum > initialStrucSize) userAccounts = realloc(userAccounts, i + accountsNum);
            repeat = createAccounts(i, accountsNum, userAccounts);
            //printf("\nAccounts num when > 1  : %d", accountsNum);
            i += accountsNum;
            break;
        case '3':
            repeat = operations();
            break;
        case '4':
            menuDisplay('a', &choice);
            if(choice == '7') repeat = false;
            repeat = affichage(choice, userAccounts, i);
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
