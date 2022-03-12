#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Fichier "IncendieUrgent.dat"
#define Fichier_1 "EquipeProtection.dat"
typedef struct
{int code;
 char nom[20],adr_sg[10];
 int srf,nbr_arb,nbr_incen;
}foret;
/**La liste de foret **/
typedef struct foretList
{foret frt;
 struct foretList *suivant;
}foretList;
/**La fonction qui créer la Liste des N forets en Mode FIFO**/
foretList * creerListeGlobaleForet(int N)
{foretList *P,*tete,*pred;
 int i;
  P=(foretList*)malloc(sizeof(foretList));
  if(P==NULL)
    return NULL;
  printf("\n\t****Les informations de la 1 ere Foret****");
  printf("\n\t\t-Le code:");scanf("%d",&P->frt.code);
  printf("\n\t\t-Le Nom:");scanf("%s",P->frt.nom);
  printf("\n\t\t-L'adresse du siege:");scanf("%s",P->frt.adr_sg);
  printf("\n\t\t-La Surface :");scanf("%d",&P->frt.srf);
  printf("\n\t\t-Le nombre d'arbres total:");scanf("%d",&P->frt.nbr_arb);
  printf("\n\t\t-Le nombre d'arbres en etat d'incendie:");scanf("%d",&P->frt.nbr_incen);
  tete=P;
  pred=P;
  for(i=2;i<=N;i++)
  { P=(foretList*)malloc(sizeof(foretList));
  if(P==NULL)
    return NULL;
  printf("\n****Les informations de la %d ieme Foret****",i);
  printf("\n\t-Le code:");scanf("%d",&P->frt.code);
  printf("\n\t-Le Nom:");scanf("%s",P->frt.nom);
  printf("\n\t-L'adresse du siege:");scanf("%s",P->frt.adr_sg);
  printf("\n\t-La Surface :");scanf("%d",&P->frt.srf);
  printf("\n\t-Le nombre d'arbre total:");scanf("%d",&P->frt.nbr_arb);
  printf("\n\t-Le nombre d'arbre en etat d'incendie:");scanf("%d",&P->frt.nbr_incen);
   pred->suivant=P;
   pred=P;
  }
  P->suivant=NULL;
  return tete;
}
/**crée un fichier contenant seulement les forets qui ont le nombre d'arbres brulés dépasse 20% nbr total**/
int creerFichierForetIncendieEtatUrgent (foretList *tete, char nomFichiers[])
{foretList *P;
 FILE*F;
 F=fopen(nomFichiers,"wb");
 if(F==NULL)
 {printf("ProblEme de crEation du Fichier %s ...",nomFichiers);
  return 0;
 }
  P=tete;
  while(P!=NULL)
  {if(P->frt.nbr_incen>(0.2)*P->frt.nbr_arb)
    {fwrite(&P->frt,sizeof(foret),1,F);
    }
     P=P->suivant;
  }
  fclose(F);
  return 1;
}
/***de plus fonction qui lit les elts d'un fichier bin car on peut pas le visualiser directement**/
int lireFichBin (char nomdefichier[])
{FILE *F;
foret elt;
  F=fopen(nomdefichier,"rb");
  if(F==NULL)
   {printf("Error reading File %s ...........",nomdefichier);
    return 0;
    }
   printf("\n-Les elements du fichier %s sont:\n",nomdefichier);
    while(fread(&elt,sizeof(elt),1,F)!= 0)
     {printf("\n-Le code :%5d",elt.code);
      printf("\n-Le nom: %s",elt.nom);
      printf("\n-L'adrresse du siege:%s", elt.adr_sg);
      printf("\n-La surface:%5d",elt.srf);
      printf("\n-Le nombre d'arbre total :%5d ", elt.nbr_arb);
      printf("\n-Le nombre d'arbre brulEs:%5d ", elt.nbr_incen);
      }
    fclose(F);
   return 1;
}
/**Fonction qui cherche la foret max brulés et retourne la foret qui est de type enregistrement *****/
foret chercherForetMaxIncendie (char nomFichier [ ])
{FILE *F;
 foret elt,eltmax;
 float taux,tauxmax;
     F=fopen(nomFichier,"rb");
  if(F==NULL)
   {printf("Error reading File %s ...........",nomFichier);
    }
    if (fread(&elt,sizeof(elt),1,F)!=0)
    {eltmax=elt;  tauxmax=elt.nbr_incen/elt.nbr_arb;
    while(fread(&elt,sizeof(elt),1,F)!=0)
    {taux=elt.nbr_incen/elt.nbr_arb;
        if(taux>tauxmax)
          {eltmax=elt;
           tauxmax=taux;
          }
    }
    printf("\n\t**la foret ayant le max d’arbres brulés / à son nombre total d’arbres**");
     printf("\n-Le code:%d",eltmax.code);
      printf("\n-Le Nom:%s",eltmax.nom);
      printf("\n-La surface:%d",eltmax.srf);
      printf("\n-Le nombre d'arbre:%d",eltmax.nbr_arb);
      printf("\n-Le nombre d'arbres brulés:%d",eltmax.nbr_incen);
    }
    fclose(F);

    return eltmax;
 }
typedef struct
{int cod,nbr_incen_traites;
 char nm[20],adr_sie[10];
 char ment,dispo;
}epc;
/**La liste protectionCivileList***/
typedef struct protectionCivileList
{epc ptc;
struct  protectionCivileList *svt;
}protectionCivileList;
/*** fonction qui crée la liste des equipes de protections civiles En mode LIFO***/
protectionCivileList * creerListeGlobaleProtectionCivile(int M)
{ protectionCivileList *tete,*p;
 int i;
     tete = NULL;
     for (i=0;i<M;i++)
      {p=(protectionCivileList*)malloc(sizeof(protectionCivileList));
       if(p==NULL)
        return NULL;
        printf("**Entrer les infos de la  %d equipe****\n",i+1);
        printf("\n\t-Le code:");scanf("%d", &p->ptc.cod);
        printf("\n\t-Le nombre d'incendie traités:");scanf("%d",&p->ptc.nbr_incen_traites);
        printf("\n\t-Le Nom:");scanf("%s",p->ptc.nm);
        printf("\n\t-L'adresse de siege:");scanf("%s",p->ptc.adr_sie);
        do
        {printf("\n\t-Entrer La mention A,B,C ou D:");
         scanf("%c",&p->ptc.ment);
        }while(p->ptc.ment!='A'&& p->ptc.ment!='B'&& p->ptc.ment!='C'&& p->ptc.ment!='D');
        do
        {printf("\t-La disponibilite entrer L libre ou N non dispo :");
          scanf("%c",&p->ptc.dispo);
        }while (p->ptc.dispo!='L'&& p->ptc.dispo!='N');
         p->svt= tete;
         tete = p;

        }
        return tete;
}
/** Creer un fichier des equipes qui sont libres et ayant la mm adrr comme la foret max brulés**/
int creerFichierProtectionCivile_Sciege_A_sauver(protectionCivileList *tete, char nomFichiers[])
{FILE *G;
protectionCivileList *p;
epc elt;
  G=fopen(Fichier_1,"wb");
  if(G==NULL)
  {printf("ProBleme de creation du file %s",nomFichiers);
   return 0;
  }
  p=tete;
  while(p!=NULL)
  {if((strcmp(p->ptc.adr_sie,chercherForetMaxIncendie(Fichier).adr_sg)==0)&&(p->ptc.dispo=='L'))
    {fwrite(&p->ptc,sizeof(epc),1,G);
    }
     p=p->svt;
  }
  fclose(G);
  return 1;
}
/**lire un fichier bin ***/
int lireFichBin1 (char nomdefichier[])
{FILE *F;
epc elt;
  F=fopen(nomdefichier,"rb");
  if(F==NULL)
   {printf("Error reading File %s ...........",nomdefichier);
    return 0;
    }
   printf("\n-Les elements du fichier %s sont:\n",nomdefichier);
    while(fread(&elt,sizeof(elt),1,F)!= 0)
     {printf("\n-Le code :%5d",elt.cod);
      printf("\n-Le nom: %s",elt.nm);
      printf("\n-L'adrresse du siege:%s", elt.adr_sie);
      printf("\n-La nbre d'incendie traites :%5d",elt.nbr_incen_traites);
      printf("\n-La mention  :%c ", elt.ment);
      printf("\n-La disponibilite:%c ", elt.dispo);
      }
    fclose(F);
   return 1;
}
/***Fonction qui chercher dans le fichier des equipes ***/
protectionCivileList * chercherEquipeFavorisee (char nomFichier [ ])
{ FILE *G;
int nbr,max;
  epc elt,eltmax;
  protectionCivileList *p;
    G=fopen(nomFichier,"rb");
    if(G==NULL)
    {printf("errreur  de lecture du fichier %s",nomFichier);
    }
    if (fread(&elt,sizeof(elt),1,G)!=0)
    {eltmax=elt;  max=elt.nbr_incen_traites;
    while(fread(&elt,sizeof(elt),1,G)!=0)
    {nbr=elt.nbr_incen_traites;
        if(nbr>max)
          {eltmax=elt;
           max=nbr;
          }
    }
   if(eltmax.ment=='A')
   {printf("\n***Les infos de L'equipe favorisée***");
    printf("\n-Le code:%d",eltmax.cod);
    printf("\n-Le nom:%s",eltmax.nm);
    printf("\n-L'adresse du siege:%s",eltmax.adr_sie);
    printf("\n-Le nombres d'incendie traites:%d",eltmax.nbr_incen_traites);
    printf("\n-La mention:%c",eltmax.ment);
    printf("\n-La disponibilite:%c",eltmax.dispo);
   p->ptc=eltmax;
   p->svt=NULL;
   }
    }
    fclose(G);
    return p;
}
/**cherche dans protectioncivil list l’équipe retournée en (4) et incrémente le nbre incen traités+1**/
/*elle marche mimpas
void nouvelleListe(protectionCivileList*tete)
{protectionCivileList *p;

  p=tete;
  while(p!=NULL)
  {if(p->ptc ==chercherEquipeFavorisee(Fichier_1)->ptc)
    {p->ptc.nbr_incen_traites+1;
    }
     p=p->svt;
  }
  printf("le nmbre apres mise a jour :%d",p->ptc.nbr_incen_traites);
}
*/



int main()
{int N,nb,M,k;
 foretList *tete;
 protectionCivileList *Ptete,*op;
 foret elt;
   do
   {printf("\n**Donner Le nombre De forets:");
     scanf("%d",&N);
   }while(N<=0);
   tete=creerListeGlobaleForet(N);
   system("pause");system("cls");

   nb=creerFichierForetIncendieEtatUrgent(tete,Fichier);
   if(nb!=0)
   {lireFichBin(Fichier);
   }
   elt=chercherForetMaxIncendie(Fichier);
   system("pause");system("cls");

   do
   {printf("\n**Entrer Le nombre Des equipes de protection Civile :");
     scanf("%d",&M);
   }while(M<=0);
    Ptete=creerListeGlobaleProtectionCivile(M);
    k=creerFichierProtectionCivile_Sciege_A_sauver(Ptete,Fichier_1);
    if(k!=0)
    {lireFichBin1(Fichier_1);
    }
    op=chercherEquipeFavorisee(Fichier_1);

    return 0;
}
