#include "header.h"
#include "stdlib.h"
#include "stdio.h"

Element_str* creer_list(char ch[50]){
    Element_str* list_g;
    list_g = (Element_str*) malloc(sizeof (Element_str));
    for (int i = 0; i<= 50; i++)
        list_g -> texte[i] = ch[i];
    list_g -> next = NULL;
    return list_g;
}

void ajout_val_fin_rec(Element_str** ad_liste, char txt[50]){
    if (*ad_liste == NULL){
        *ad_liste = creer_list(txt);
    }
    else{
        ajout_val_fin_rec( &((*ad_liste)->next) , txt);
    }
}

void display_list(Element_str* liste){
    if (liste != NULL){
        if (liste -> next != NULL)
            printf("%s -> ", liste-> texte);
        else
            printf("%s", liste-> texte);
        display_list(liste->next);
    }
    else{
        printf("\n");
    }
}

Element_str* initialiser_gouts(){
    l_gouts =NULL;
    ajout_val_fin_rec(&l_gouts, "Chocolat");
    ajout_val_fin_rec(&l_gouts, "Vanille");
    ajout_val_fin_rec(&l_gouts, "Fraise");
    ajout_val_fin_rec(&l_gouts, "Abricot");
    ajout_val_fin_rec(&l_gouts, "Pomme");
    ajout_val_fin_rec(&l_gouts, "Banane");
    ajout_val_fin_rec(&l_gouts, "Myrtille");
    return l_gouts;
}

int nb_el(Element_str* list){
    int cpt = 0;
    while (list != NULL){
        cpt++;
        list = list -> next;
    }
    return cpt;
}

//------------------------------------//
File_Commandes * creer_file_com(){
    File_Commandes * nouv_file = (File_Commandes *)malloc(sizeof(File_Commandes));
    nouv_file->data = NULL;
    return nouv_file;
}

int file_com_est_vide(File_Commandes* f_commandes){
    if(f_commandes->data == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void passer_commande(char commande[50], File_Commandes * f_commandes)
{
    if (nb_el(f_commandes->data) <10)
    {
        Element_str *nouv_el = NULL;
        ajout_val_fin_rec(&nouv_el, commande);
        nouv_el->next = NULL;
        //Ajout à la fin

        if (file_com_est_vide(f_commandes) == 1) {
            f_commandes->data = nouv_el;
        }
        else {
            Element_str *temp = f_commandes ->data;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nouv_el;
        }
    }
    else{
        printf("Tu te calme !\n");
    }
}
//-------------------------------------//

//-------------------------------------//
Element_gtx* creer_El_gat(Gateau* g){
    Element_gtx * nouv_file = (Element_gtx *)malloc(sizeof(Element_gtx));
    nouv_file->gateau = g;
    nouv_file->next = NULL;
    return nouv_file;
}

File_Degustation* creer_file_deg(){
    File_Degustation* nouv_file = (File_Degustation*)malloc(sizeof(File_Degustation));
    nouv_file ->data = NULL;
    return nouv_file;
}

/*
int file_deg_est_vide(File_Degustation * f){
    if(f->data == NULL){
        return 1;
    }
    else{
        return 0;
    }
}
*/

void ajouter_gat_fin(Element_gtx** list, Gateau* gateau){
    Element_gtx** temp = list;
    while ((*temp) != NULL)
    {
        *temp = (*temp) ->next;
    }
    *temp = creer_El_gat(gateau);
}

void livrer(Gateau* gateau, File_Degustation* f_degustation)
{
    if (gateau != NULL)
        ajouter_gat_fin(&(f_degustation->data), gateau);
}

//---------------------------------------//


Element_str* conversion(char com[50]){
    Element_str* list = NULL;
    for (int i =0; i <= 50; i++){
        if (com[i] == 'C'){
            ajout_val_fin_rec(&list, "C");
        }
        if (com[i] == 'V'){
            ajout_val_fin_rec(&list, "V");
        }
        if (com[i] == 'F'){
            ajout_val_fin_rec(&list, "F");
        }
        if (com[i] == 'A'){
            ajout_val_fin_rec(&list, "A");
        }
        if (com[i] == 'P'){
            ajout_val_fin_rec(&list, "P");
        }
        if (com[i] == 'B'){
            ajout_val_fin_rec(&list, "B");
        }
        if (com[i] == 'M'){
            ajout_val_fin_rec(&list, "M");
        }
        if (com[i] == '\0'){
            break;
        }
        display_list(list);
    }
    return list;
}

Element_str* traiter_commande(File_Commandes* f_commandes){
    if (f_commandes != NULL){
        Element_str* cpt = conversion(f_commandes -> data -> texte);
        Element_str* temp = f_commandes -> data -> next;
        free(f_commandes -> data);
        f_commandes ->data =NULL;
        f_commandes -> data = temp;
        return cpt;
    }
    return NULL;
}


Pile_Gouts * creer_pile(){
    Pile_Gouts * nouv_pile = (Pile_Gouts*) malloc(sizeof(Pile_Gouts));
    nouv_pile->data = NULL;
    return nouv_pile;
}

void empiler(Pile_Gouts * p, char a[50]){
    Element_str * nouv_el = creer_list(a);
    //display_list(nouv_el);
    Element_str* temp = p -> data;
    nouv_el-> next = p-> data;
    p->data = nouv_el;
}

Gateau* creer_gateau(Element_str* commande){
    Gateau* miammiam_manger = (Gateau*) malloc(sizeof (Gateau));
    miammiam_manger ->commande = commande;
    miammiam_manger -> p_gouts = creer_pile();
    return miammiam_manger;
}

void construire_gateau(Gateau* gateau, Element_str* l_gouts){
    Element_str* temp = gateau -> commande;
    while (temp != NULL){
        Element_str* cpt = l_gouts;
        while (cpt != NULL){
            if (temp -> texte[0] == cpt ->texte[0]){
                empiler(gateau->p_gouts, cpt-> texte);
                display_list(gateau -> p_gouts->data);
            }
            cpt = cpt ->next;
        }
        temp = temp->next;
    }
}

void degustation(File_Degustation* f_degustation, int nb_parts)
{
    Element_gtx* cpt_gtx = f_degustation -> data;
    Element_gtx* cpt_gtx_next;
    //display_list(cpt_gtx ->next ->gateau->p_gouts->data);
    if (cpt_gtx != NULL){
        Element_str* temp =  cpt_gtx -> gateau -> p_gouts -> data;
        Element_str* cpt_next;

        for(int i = 0; i < nb_parts; i++){
            //printf("test");
            if (temp != NULL){
                if (temp ->next != NULL){
                    cpt_next = temp ->next;
                    free(temp);
                    temp = cpt_next;
                    //printf("a");
                    display_list(temp);

                }
                else if (temp ->next == NULL) {
                    free(temp);
                    if (cpt_gtx->next != NULL) {
                        cpt_gtx_next = cpt_gtx->next;
                        free(cpt_gtx);
                        cpt_gtx = NULL;
                        cpt_gtx = cpt_gtx_next;
                        temp = cpt_gtx -> gateau -> p_gouts -> data;
                    }
                    else {
                        free(cpt_gtx);
                        cpt_gtx = NULL;
                        printf("Il ne re reste plus de  gateau");
                        break;
                    }
                }
            }
        }
    }
}

int main(){
    int working = 1;
    int ref;
    f_commandes = creer_file_com();
    f_degustation = creer_file_deg();
    printf("Bienvenu dans le programme du projet patisserie\n");
    while (working == 1)
    {
        printf("Veuillez entrer la reference\n");
        printf("-------------------------------------------------------------\n");
        printf("|           1) Remplir les gout du patissier                |\n");
        printf("|-----------------------------------------------------------|\n");
        printf("|            2) Passer commande                             |\n");
        printf("|-----------------------------------------------------------|\n");
        printf("|     3) Traiter la commande suivante et creer un gateau    |\n");
        printf("|-----------------------------------------------------------|\n");
        printf("|                  4) Manger                                |\n");
        printf("|-----------------------------------------------------------|\n");
        printf("|                     5) Quitter                            |\n");
        printf("-------------------------------------------------------------\n");
        printf("Reference : ");
        scanf("%d", &ref);
        switch (ref) {
            case 1:{
                l_gouts = initialiser_gouts();
                display_list(l_gouts);
                break;
            }
            case 2:{
                char commande_str[50];
                printf("Pour revenir au menu principal, entrez 1\n");
                printf("Veuillez saisir votre commande :\n");
                scanf("%s", &commande_str);
                if (commande_str[0] == '1'){
                    break;
                }
                passer_commande(commande_str, f_commandes);
                printf("Vous venez de passer la commande suivante : ");
                display_list(f_commandes->data);
                break;

            }
            case 3:{
                Element_str* commande_traitee = traiter_commande(f_commandes);
                Gateau* gat = creer_gateau(commande_traitee);
                construire_gateau(gat, l_gouts);
                display_list(gat->p_gouts->data);
                livrer(gat, f_degustation);

                break;
            }
            case 4:{
                int nb_parts;
                printf("Combien de parts voulez-vous avaler ?");
                scanf("%d", &nb_parts);
                degustation(f_degustation, nb_parts);
                break;
            }
            case 5:{
                printf("Au revoir");
                working = 0;
                break;
            }
        }
    }
}
