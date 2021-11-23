#include <stdio.h>
#include <stdlib.h> //includes the exit function
#include <string.h>
#include <stdbool.h>
//void selectionSortDouble(char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount); // used by search function so it needs to be declared before
//void swap(struct user *ptrSwap1, struct user *ptrSwap2);

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
            printf("\n1. Retrait\n2. Depot\n3. Retourner au menu principal\n4. Quitter\n");
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
void selectionSortString(char sortBy, char *subChoice, struct user* userAccounts, int currentCount){
    int i, min_idx, j;
    struct user* userAccountsStartingPoint = userAccounts;
    struct user* userAccountToBeSwaped;
    if(subChoice == NULL){
        for (i = 0; i < currentCount; i++){
            min_idx = i;
            for (j = i+1; j < currentCount; j++){
                if (*(userAccounts+min_idx)->CIN > *(userAccounts+j)->CIN){
                        min_idx = j;
                }
            }
            userAccounts += min_idx;
            userAccountToBeSwaped = userAccountsStartingPoint + i;

            swap(userAccountToBeSwaped, userAccounts);
            userAccounts -= min_idx;
        }
        //Affichage to check if CIN selection works
        for (i = 0; i < currentCount; i++){
            printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
            userAccounts++;
        }
    }
    else if (*subChoice == '2'){ // sort by Nom

    }
    else if(*subChoice == '3') {} //sort by Prénom
}

struct user* search(char * searchFor, struct user* userAccounts, int currentCount){
    for(int i = 0; i < currentCount; i++){
        if(!strcmp(searchFor, (userAccounts+i)->CIN)){
            return userAccounts+i;
        }
    }
     printf("\nCIN introuvable");
    return NULL;

}
void withdraw(struct user *userAccounts, int currentCount){
    char *searchFor;
    double sumToWithdraw;
    struct user* accountToWithdrawFrom;
    printf("\nEntrer le CIN du compte :");
    scanf(" %s", searchFor);
    accountToWithdrawFrom = search(searchFor, userAccounts, currentCount);
    if(accountToWithdrawFrom == NULL) return;
    printf("\nMontant actuel : %lf", accountToWithdrawFrom->sum);
    printf("\nEntrer le montant a retirer : \n");
    scanf(" %lf", &sumToWithdraw);
    //printf("\nMontant precedent : %lf", accountToWithdrawFrom->sum);
    accountToWithdrawFrom->sum -= sumToWithdraw;
    printf("\nNouveau Montant : %lf", accountToWithdrawFrom->sum);
}
void deposit(struct user *userAccounts, int currentCount){
    char *searchFor;
    double sumToDeposit;
    struct user* accountToDepositIn;
    printf("\nEntrer le CIN du compte :");
    scanf(" %s", searchFor);
    accountToDepositIn = search(searchFor, userAccounts, currentCount);
    if(accountToDepositIn == NULL) return;
    printf("\nMontant actuel : %lf", accountToDepositIn->sum);
    printf("\nEntrer le montant a deposer :\n");
    scanf(" %lf", &sumToDeposit);
    //printf("\nMontant precedent : %lf", accountToWithdrawFrom->sum);
    accountToDepositIn->sum += sumToDeposit;
    printf("\nNouveau Montant: %lf", accountToDepositIn->sum);
}

bool operations(int currentCount, struct user *userAccounts){ // Withdraw and deposit operations on accounts
    char choice;
    menuDisplay('o', &choice);
    if(choice == '1') withdraw(userAccounts, currentCount);
    else if (choice == '2') deposit(userAccounts, currentCount);
    //else if (choice == '3') return true;
    return true;
}
void swap(struct user *ptrSwap1, struct user *ptrSwap2)
{
    char * strTemp; double sumTemp;
    //swap fName
    strTemp = ptrSwap1->fName;
    ptrSwap1->fName = ptrSwap2->fName;
    ptrSwap2->fName = strTemp;
    //swap lName
    strTemp = ptrSwap1->lName;
    ptrSwap1->lName = ptrSwap2->lName;
    ptrSwap2->lName = strTemp;
    //swap CIN
    strTemp = ptrSwap1->CIN;
    ptrSwap1->CIN = ptrSwap2->CIN;
    ptrSwap2->CIN = strTemp;
    //swamp sum
    sumTemp = ptrSwap1->sum;
    ptrSwap1->sum = ptrSwap2->sum;
    ptrSwap2->sum = sumTemp;
}
void selectionSortDouble(char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount){
    //printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
    //printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", (userAccounts+1)->lName, (userAccounts+1)->fName, (userAccounts+1)->CIN, (userAccounts+1)->sum);
    //printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", (userAccounts+2)->lName, (userAccounts+2)->fName, (userAccounts+2)->CIN, (userAccounts+2)->sum);


    struct user *userAccountToBeSwaped;
    struct user *userAccountsStartingPoint = userAccounts;
    int i, j, min_idx, max_idx;


    //affichage
    printf("\nNom\t|\tPrenom\t|\tCIN\t|\tMontant");
    if(sortBy == 'a') {
        for (i = 0; i < currentCount-1; i++){ // we did sizeArr-1 because it is not necessary for i to get to the last element of the array
            min_idx = i;
            for (j = i+1; j < currentCount; j++){
                if ((userAccounts+min_idx)->sum > (userAccounts+j)->sum){
                    min_idx = j;
                }
            }
            userAccounts += min_idx;
            userAccountToBeSwaped = userAccountsStartingPoint + i;

            swap(userAccountToBeSwaped, userAccounts);
            userAccounts -= min_idx;
        }
        //userAccounts -= min_idx;
        //printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", (userAccounts+3)->lName, (userAccounts+3)->fName, (userAccounts+3)->CIN, (userAccounts+3)->sum);
        //printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
        //test the minimu sum to display if there are any accounts to display
         if(minSumToDisplay > (userAccounts+currentCount)->sum) {system("cls"); printf("\nLe montant introduit depasse les montants disponible."); return;}
        //Display of user accounts in ascending order
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
    }
    else if (sortBy == 'd'){
        for (i = 0; i < currentCount-1; i++){
            max_idx = i;
            for (j = i+1; j < currentCount; j++){
                if ((userAccounts+max_idx)->sum < (userAccounts+j)->sum){
                    max_idx = j;
                }
            }
            userAccounts += max_idx;
            userAccountToBeSwaped = userAccountsStartingPoint + i;
            swap(userAccountToBeSwaped, userAccounts);
            userAccounts -= max_idx;
        }
        //printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", (userAccounts+3)->lName, (userAccounts+3)->fName, (userAccounts+3)->CIN, (userAccounts+3)->sum);
        //printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
        //test the minimu sum introduced to display if there are any accounts to display
         if(minSumToDisplay > (userAccounts)->sum) {system("cls"); printf("\nLe montant introduit depasse les montants disponible."); return;}
        //Display of user accounts in descending order
        for (i = 0; i < currentCount; i++){
            if(userAccounts->sum < minSumToDisplay) break;
                printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
                userAccounts++;
            }
    }
}
void sortFunction(char *subChoice, char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount){
    switch(*subChoice){
        case '1':
            selectionSortDouble(sortBy, minSumToDisplay, userAccounts, currentCount);
            break;
        case '2' : //sort by Nom
            //selectionSortString(sortBy, *subChoice, userAccounts, currentCount);
            break;
        case '3' : //sort by Prénom
            //selectionSortString(sortBy, *subChoice, userAccounts, currentCount);
            break;
    }
}
bool affichage(char choice, struct user *userAccounts, int currentCount){
    char subChoice;
    char *searchFor;
    struct user* accountToSearch;
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
            printf("\nEntrer le CIN a rechercher :\n");
            scanf(" %s", searchFor);
            accountToSearch = search(searchFor, userAccounts, currentCount);
            if(accountToSearch == NULL) break;
            printf("\nNom\t|\tPrenom\t|\tCIN\t|\tMontant");
            printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", accountToSearch->lName, accountToSearch->fName, accountToSearch->CIN, accountToSearch->sum);
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
            if(i > initialStrucSize) userAccounts = realloc(userAccounts, i); //need to realloc also Nom prenom CIN
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
            repeat = operations(i, userAccounts);
            break;
        case '4':
            if(i == 0) {
                    printf("\nLa base de donnees est vide. Essayer d'introduire des nouveaux comptes.");
                    break;
            }
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
