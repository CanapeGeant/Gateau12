//
// Created by 974cc on 09/10/2021.
//

#ifndef GATEAU12_HEADER_H
#define GATEAU12_HEADER_H

#endif //GATEAU12_HEADER_H


typedef struct Element_str{
    char texte[50];
    struct Element_str* next;
}Element_str;

Element_str* l_gouts;


typedef struct File_Commandes{
    Element_str* data;
}File_Commandes;

typedef struct Pile_Gouts{
    Element_str* data;
}Pile_Gouts;


typedef struct Gateau{
    struct Element_str* commande;
    struct Pile_Gouts* p_gouts;
}Gateau;


typedef struct Element_gtx{
    struct Gateau* gateau;
    struct Element_gtx* next;
}Element_gtx;


typedef struct File_Degustation{
    Element_gtx* data;
}File_Degustation;

File_Commandes* f_commandes;
File_Degustation* f_degustation;

