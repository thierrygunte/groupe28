#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
           /* PARTIE 1 :STRUCTURE DE DONNEES */
/*definition de la structure PRODUIT*/

struct produit
{
    char code[12];
    char libele[15];
    int prix;
};
typedef struct produit PRODUIT;

/*definition de la structure LISTE_PRODUIT*/
struct liste_produit
{
    PRODUIT*tab;
    int taille;
    int libre;
};
typedef struct liste_produit LISTE_PRODUIT;

/* definition de la fonction PRODUIT* lire produit1()*/

PRODUIT*lire_produit1()
{
    PRODUIT*pr;
    pr=(PRODUIT*)malloc(sizeof(PRODUIT));
    printf("entrer le code du produit :");
    scanf("%s",pr->code);
    printf("entrer le libele du produit :");
    scanf("%s",pr->libele);
    printf("entrer le prix unitaire de ce produit :");
    scanf("%d",&pr->prix);
    free(pr);
    return pr;
}
/*definition de la fonction void lire_produit2 (PRODUIT *P)*/

void lire_produit2(PRODUIT *p)
{
    printf("entrer le code du produit :");
    scanf("%s",p->code);
    printf("entrer le libele du produit :");
    scanf("%s",p->libele);
    printf("entrer le prix unitaire de ce produit :");
    scanf("%d",&p->prix);
    return;
}
/*definition de la fonction void affiche_produit1(PRODUIT *P)*/
void affiche_produit1(PRODUIT *p)
{
    printf("%s",p->code);
    printf("%s",p->libele);
    printf("%d",p->prix);
    return;
}
/*definition de la fonction void affiche_produit2(PRODUIT pro)*/

void affiche_produit2(PRODUIT pro)
{
    printf("%s",pro.code);
    printf("%s",pro.libele);
    printf("%d",pro.prix);
    return;
}

/*  OPERATION SUR LES LISTES DE PRODUIT PARTIE III  */
/*creation LISTE_PRODUIT*/
LISTE_PRODUIT *creation_lp(int n)
{
    LISTE_PRODUIT *lp;
    lp=(LISTE_PRODUIT*)malloc(sizeof(LISTE_PRODUIT));
    lp->tab=(PRODUIT*)malloc(sizeof(PRODUIT)*n);
    lp->taille=n;
    lp->libre=0;
    return lp;
}
/*creation d'une liste vide*/
int vide_lp(LISTE_PRODUIT lp)
{
    if(lp.libre==0)
        return TRUE;
    else
        return FALSE;
}
/*creation d'une liste pleine*/
int plein_lp(LISTE_PRODUIT lp)
{
    if(lp.libre==lp.taille)
        return TRUE;
    else
        return FALSE;
}
/*ajout d'une liste produit*/
int ajout_lp(LISTE_PRODUIT *plp,PRODUIT *p)
{
    if(plp->libre==plp->taille)
        return FALSE;
    else
    {
            strcpy((plp->tab)[plp->libre].code,p->code);
            strcpy((plp->tab)[plp->libre].libele,p->libele);
            (plp->tab)[plp->libre].prix=p->prix;

         plp->libre++;
    }

    printf("Le produit a ete ajouter avec succes\n");
    return TRUE;
}
/*recherche d'un element lp1*/
int search_lp1(LISTE_PRODUIT *lp,char *code)
{
    int i;
    for(i=0;i<lp->taille;i++)
    {
        if(strcmp(lp->tab[i].code,code)==0)
        {
            printf("Info sur le produit \n");
            printf("Code\tnom\tprix_unitaire\n");
            printf("%s\t%s\t%d\n\n",lp->tab[i].code,lp->tab[i].libele,lp->tab[i].prix);
            return i;
        }

    }
    printf("le produit nexiste pas\n\n");
    return -1;
}

void aff_lp(LISTE_PRODUIT *plp)
{
    int i;
    if(plp->libre==0)
    {
        printf("le tableau est vide\n");
        return;
    }
    for(i=0;i<plp->libre;i++)
    {
        printf("code\tnom\tprix_unitaire\n");
        printf("%s\t",plp->tab[i].code);
        printf("%s\t",plp->tab[i].libele);
        printf("%d\t",plp->tab[i].prix);
        printf("\n\n");
    }
    return;
}

int delete_lp(LISTE_PRODUIT *plp,char *code)
{
    int i,s;
    s=search_lp1(plp,code);
    if(s==-1)
    {
        return FALSE;
    }

    else
    {
        for(i=s;i<plp->taille;i++)
        {
            plp->tab[i]=plp->tab[i+1];
        }
    }
    plp->libre=plp->libre-1;
    printf("produit suprimer avec succes\n");
    return TRUE;
}

void delete_2(LISTE_PRODUIT *plp)
{
    int i,j;
    for(i=0;i<plp->libre;i++)
    {
        for(j=0;j<plp->libre;j++)
        {
            plp->tab[j]=plp->tab[j+1];
        }
    }
    plp->libre=0;
}

int trie_selection(LISTE_PRODUIT *plp)
{
    int i,j;
    for(i=0;i<plp->libre-1;i++)
    {
        for(j=i+1;j<plp->libre;j++)
        {
            if(plp->tab[i].prix>plp->tab[j].prix)
            {
                plp->tab[plp->taille-1]=plp->tab[i];
                plp->tab[i]=plp->tab[j];
                plp->tab[j]=plp->tab[plp->taille-1];
            }
        }
    }
    printf("le trie a ete effectuer avec succes\n\n");
    return 0;
}
int menu()
{

    printf("***************************  MENU  *************************\n\n");
    printf("\t1. Ajouter un produit\n");
    printf("\t2. Suprimer un produit\n");
    printf("\t3. Trier les produits par prix croissant\n");
    printf("\t4. Afficher les produits\n");
    printf("\t5. Rechercher un produit\n");
    printf("\t6. Enregistrer les produits dans un fichier\n");
    printf("\t7. Ouvrir le fichier des produits\n");
    printf("\t8. Quiter le programme\n\n");

    return 0;
}

/*    GESTIONN DES FICHIERS */

void to_file(char *nom_fichier,LISTE_PRODUIT *lp)
{
    int i;
    FILE *fichier;
    fichier=fopen(nom_fichier,"a");
    if(fichier==NULL)
    {
        printf("impossible douvrir le fichier %s",nom_fichier);
        return;
    }
    else if(lp->libre==0){
        printf("Le tableau de produit est encore vide\n");
        return;
    }
    else
    {
        for(i=0;i<lp->libre;i++)
        {
            fprintf(fichier,"\n\n%s\t%s\t%d",lp->tab[i].code,lp->tab[i].libele,lp->tab[i].prix);
        }
        delete_2(lp);
        printf("L'ajout a ete effectuer avec succes\n\n");
        fclose(fichier);
    }
    return;
}

void to_liste_produit(LISTE_PRODUIT *plp,char *nom_fichier)
{
    int i=0;
    FILE *fichier;
    fichier=fopen(nom_fichier,"r");
    if(fichier==NULL)
    {
        printf("Le fichier %s n'existe pas dans votre repertoire de travaille\n",nom_fichier);
        return;
    }
    printf("Les element du fichier %s sont :\n\n",nom_fichier);
    while( fscanf(fichier,"%s %s %d",plp->tab[i].code,plp->tab[i].libele,&plp->tab[i].prix)!=EOF)
    {

        printf("%d*\tCode\tNom\tprix_unitaire\n",i+1);
        printf("\t%s\t%s\t%d\n\n",plp->tab[i].code,plp->tab[i].libele,plp->tab[i].prix);
        i++;
    }
    fclose(fichier);
    return;
}


int main()
{   system("color 0f");
    PRODUIT p;
    LISTE_PRODUIT *plp;
    plp=(LISTE_PRODUIT*)malloc(sizeof(LISTE_PRODUIT));
    plp=creation_lp(10);
    int quit,rep;
    char code[5],nom[10];
    start:;
        system("cls");
        menu();
        printf("Veiller entrer votre choix (il doit etre compris entre 1 et 8) :");
        scanf("%d",&rep);
        if(rep<1 || rep>8)
            goto start;
        else if(rep==8)
            return 0;
    system("cls");
    switch(rep)
    {
    case 1:
        lire_produit2(&p);
        ajout_lp(plp,&p);
        break;
    case 2:
        printf("entrer le code du produit a suprimer :");
        scanf("%s",code);
        delete_lp(plp,code);
        break;
    case 3:
        trie_selection(plp);
        break;
    case 4:
        aff_lp(plp);
        break;
    case 5:
        printf("entrer le code :");
        scanf("%s",code);
        search_lp1(plp,code);
        break;
    case 6:
        printf("entrer le nom du fichier :");
        scanf("%s",nom);
        to_file(nom,plp);
        break;
    case 7:
        printf("entrer le nom du fichier :");
        scanf("%s",nom);
        to_liste_produit(plp,nom);
        break;

    }
    printf("\nveiller entrer 0 pour reparti au menu et sur 6 pour quiter le programme :");
    scanf("%d",&quit);
    printf("\n");
    if(quit==0)
        goto start;

    return 0;
}



