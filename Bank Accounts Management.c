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

struct user* initiliazeUsersArray(int sizeToAllocate, struct user *userAccounts);
struct user* memoryReallocation(struct user *userAccounts, int accountsNum, int currentCount);
void menuDisplay(char menu, char *choice);
struct user* search(char * searchFor, struct user* userAccounts, int currentCount);
void createAccounts(int * currentCount, int accountsNum, struct user *pStruct);
void selectionSortDouble(bool display, char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount); // used by search function so it needs to be declared before
void sortFunction(char *subChoice, char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount);
void swap(struct user *ptrSwap1, struct user *ptrSwap2);
void withdraw(struct user *userAccounts, int currentCount);
void deposit(struct user *userAccounts, int currentCount);
void affichage(char choice, struct user *userAccounts, int currentCount);
bool operations(int currentCount, struct user *userAccounts);
void loyalty(struct user* userAccounts, int currentCount);
//void selectionSortString(char sortBy, char *subChoice, struct user* userAccounts, int currentCount);


void main(){
    char choice = '6';
    int i = 0;
    int accountsNum;
    bool repeat = true;
    int initialStrucSize = 1; //use i value and compare it to initialStrucSize to know if we need to realloc userAccounts struct array
                                //i is used also to follow users order of input
    struct user *userAccounts = initiliazeUsersArray(initialStrucSize, userAccounts);

    do{
    accountsNum = 1;
    if(userAccounts != NULL) menuDisplay('p', &choice);
    //printf("\n choice : %c", choice);
    switch (choice){
        case '1': //Add 1 account
            if(i >= initialStrucSize) {
                //userAccounts = realloc(userAccounts, (i + accountsNum) * sizeof(struct user)); //need to realloc also Nom prenom CIN
                userAccounts = memoryReallocation(userAccounts, accountsNum, i);
            }
            createAccounts(&i, accountsNum, userAccounts);
            //if(repeat == false) break; //if CIN already exists then we should not increment i/currentCount
            //i++;
            break;
        case '2': //Add multiple accounts
            //accountsNum = 1;
            printf("\nCombien de compte comptes voulez-vous creer?");
            scanf(" %d", &accountsNum);
            if(i + accountsNum >= initialStrucSize) {
                //userAccounts = realloc(userAccounts, i + accountsNum);
                userAccounts = memoryReallocation(userAccounts, accountsNum, i);
            }
            createAccounts(&i, accountsNum, userAccounts);
            //printf("\nAccounts num when > 1  : %d", accountsNum);
            //i += accountsNum;
            break;
        case '3': //operations
            repeat = operations(i, userAccounts);
            break;
        case '4': //affichage
            if(i == 0) {
                    printf("\nLa base de donnees est vide. Essayer d'introduire des nouveaux comptes.");
                    break;
            }
            menuDisplay('a', &choice);
            if(choice == '7') {repeat = false; break;}
            if(choice == '6') break;
            affichage(choice, userAccounts, i);
            break;
        case '5': //fidélisation

            loyalty(userAccounts, i);
            break;
        case '6': //Quitter l'appplication
            repeat = false;
            break;
    }
    }while(repeat);

    free(userAccounts);
    free(userAccounts->fName);
    free(userAccounts->lName);
    free(userAccounts->CIN);
    exit(0);
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
}
struct user* memoryReallocation(struct user *userAccounts, int accountsNum, int currentCount){
    int i = 0;
    userAccounts = realloc(userAccounts, (currentCount + accountsNum)* sizeof(struct user));
    //for( i = currentCount;  i < currentCount + accountsNum; i++){
    for(i = 0; i < accountsNum; i++){
        (userAccounts+currentCount+i)->fName = malloc((50 + 1) * sizeof(char)); // we can use the accountsNum here too and it works only it starts from last element
        (userAccounts+currentCount+i)->lName = malloc((50 + 1) * sizeof(char));
        (userAccounts+currentCount+i)->CIN = malloc((50 + 1) * sizeof(char));
        //(userAccounts+i)->fName = malloc((50 + 1) * sizeof(char)); // we can use the accountsNum here too and it works only it starts from last element
        //(userAccounts+i)->lName = malloc((50 + 1) * sizeof(char));
        //(userAccounts+i)->CIN = malloc((50 + 1) * sizeof(char));
    }
    return userAccounts;
}
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
            break;
        case 'f' :
            printf("\nVoulez vous ajoutez aux 3 comptes ayant les montants les plus supérieurs 1.3%? Y/N:  "); //Try to display the 3 accounts first
            scanf(" %c", choice);
            break;
    }
    system("cls");
}

void affichage(char choice, struct user *userAccounts, int currentCount){
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
            break;

    }
    return;
}

void createAccounts(int * currentCount, int accountsNum, struct user *pStruct){
    //printf("\ncurrentCount : %d, and accountsNum to add is : %d ", currentCount, accountsNum);
    int i = accountsNum; //store the actual accountsNum provided by the user
    struct user *ptrStartOfStructArray = pStruct;
    //struct user *ptr;
    pStruct += (*currentCount);

    for(*currentCount ; *currentCount < (*currentCount + i); i--){
        printf("\nEntrer le CIN d'utilisateur :");
        scanf(" %s", pStruct->CIN);
        //search if CIN already exists
        //ptr = search((pStruct->CIN), ptrStartOfStructArray, *currentCount);
        if(search((pStruct->CIN), ptrStartOfStructArray, *currentCount) != NULL) {
                printf("\nCe CIN exist deja. Essayer avec un autre ");
                i++;
                continue;
        }
        printf("\nEntrer le nom d'utilisateur de compte :");
        scanf(" %s", pStruct->lName);
        //printf("\nYou entered  : %s", pStruct->lName);
        printf("\nEntrer le prenom d'utilisateur :");
        scanf(" %s", pStruct->fName);
        printf("\nEntrer le montant :");
        scanf(" %lf", &pStruct->sum); //montant as a double
        system("cls");
        //printf("\nLe montant : %lf\n", pStruct->sum);
        pStruct++;
        (*currentCount)+= 1;
    }
    //printf("\ncurrentCount before : %d", *currentCount);
    //*currentCount += accountsNum - i;
    //printf("\ncurrentCount after : %d", *currentCount);
    return;
}

struct user* search(char * searchFor, struct user* userAccounts, int currentCount){
    int i;
    for(i = 0; i < currentCount; i++){
        if(!strcmp(searchFor, (userAccounts+i)->CIN)){
            return userAccounts+i;
        }
    }
    printf("\nCe CIN ne figure pas dans la base de donnees. Vous pouvez ajouter un compte avec ce CIN.");
    return NULL;

}
void withdraw(struct user *userAccounts, int currentCount){
    char* searchFor;
    double sumToWithdraw;
    struct user* accountToWithdrawFrom;
    printf("\nEntrer le CIN du compte : ");
    scanf(" %s", searchFor);
    accountToWithdrawFrom = search(searchFor, userAccounts, currentCount);
    if(accountToWithdrawFrom == NULL) return;
    printf("\nMontant actuel : %lf", accountToWithdrawFrom->sum);
    printf("\nEntrer le montant a retirer : \n");
    scanf(" %lf", &sumToWithdraw);
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
    else if (choice == '4') return false;
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
void selectionSortDouble(bool display, char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount){
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
        //test the minimu sum to display if there are any accounts to display
         if(minSumToDisplay > (userAccounts+currentCount)->sum) {system("cls"); printf("\nLe montant introduit depasse les montants disponible."); return;}
        //Display of user accounts in ascending order
        if(display){
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
        if(display){
            for (i = 0; i < currentCount; i++){
                if(userAccounts->sum < minSumToDisplay) break;
                    printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", userAccounts->lName, userAccounts->fName, userAccounts->CIN, userAccounts->sum);
                    userAccounts++;
                }
        }
    }
}
void sortFunction(char *subChoice, char sortBy, double minSumToDisplay, struct user *userAccounts, int currentCount){
    switch(*subChoice){
        case '1':
            selectionSortDouble(true, sortBy, minSumToDisplay, userAccounts, currentCount);
            break;
        case '2' : //sort by Nom
            //selectionSortString(sortBy, *subChoice, userAccounts, currentCount);
            break;
        case '3' : //sort by Prénom
            //selectionSortString(sortBy, *subChoice, userAccounts, currentCount);
            break;
    }
}

void loyalty(struct user* userAccounts, int currentCount){ //fidélisation des clients
    char choice;
    int i;
    int numAccounts = 3;// number of top high sum accounts to deposit in 1.3%
    if(currentCount <= 3) numAccounts = currentCount; //This will be helpfun when the database is empty or there are less than 3 accounts
    selectionSortDouble(false, 'd', 0.0, userAccounts, currentCount);
    system("cls"); //to clear the printed provided by the selectionSortDouble function
    if(currentCount == 0) return;
    printf("\nLes 3 comptes ayant le montant le plus superieur : ");
    printf("\nNom\t|\tPrenom\t|\tCIN\t|\tMontant");
    for(i = 0; i < numAccounts; i++){
        printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", (userAccounts+i)->lName, (userAccounts+i)->fName, (userAccounts+i)->CIN, (userAccounts+i)->sum);
    }
    //if(currentCount == 0) return;
    printf("\nVoulez vous ajouter 1.3 pourcent a ces comptes? Y/N");
    scanf(" %c", &choice);
    printf("\nNom\t|\tPrenom\t|\tCIN\t|\tMontant");
    if (choice == 'y' || choice == 'Y'){
        for(i = 0; i < numAccounts; i++){
            (userAccounts+i)->sum += (userAccounts+i)->sum * (1.3/100);
            printf("\n%s\t|\t%s\t|\t%s\t|\t%lf", (userAccounts+i)->lName, (userAccounts+i)->fName, (userAccounts+i)->CIN, (userAccounts+i)->sum);
        }
    }
}


/*
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
*/
