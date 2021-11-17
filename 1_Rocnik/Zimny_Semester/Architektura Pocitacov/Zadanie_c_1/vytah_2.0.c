#include <stdio.h>
#include <unistd.h>
#include <string.h>

enum stavy { stojim_pred_dverami, vytah_prichadza, stojim_vo_vytahu, idem_vo_vytahu, zastavujem_vytah, vytah_dorazil_do_ciela } moj_stav = stojim_pred_dverami;
int pozicia_vytahu = 9;
int pozicia_uzivatela = 0;
int target_pozicia; //Stlacene tlacidlo - kam idem

void stav_pred_dverami() {
    printf("\nstojim pred dverami %d\n\n", pozicia_uzivatela);
    printf("=======================\n");
    printf("|       vytah         |\n");
    printf("|                     |\n");
    printf("|        %2d           |\n", pozicia_vytahu);
    printf("|                     |\n");
    printf("| stlac privolanie 1  |\n");
    printf("=======================\n");

    int tlacidlo_holder; //Bude lepsie, ak tuto hodnotu ulozime v temporary premennej
    scanf("%d", &tlacidlo_holder); //Je jedno ake tlacilo stlaci

    return;
}

void stav_vytah_prichadza() {
    printf("=======================\n");
    printf("|                      |\n");
    printf("|   vytah prichadza    |\n");
    printf("|                      |\n");
    printf("=======================\n");

    sleep(2); //Pozastavenie na jednu sekundu, nech je to prirodzenejsie
    pozicia_vytahu = pozicia_uzivatela;

    return;
}

void stav_stojim_vo_vytahu() {
    printf("=======================\n");
    printf("|                      |\n");
    printf("|   Stojis vo vytahu   |\n");
    printf("| Zadaj poschodie kam  |\n");
    printf("|     chcest ist.      |\n");
    printf("|                      |\n");
    printf("=======================\n");

    scanf("%d", &target_pozicia);

    return;
}

void stav_idem_vo_vytahu() {
    printf("=====================================\n");
    printf("|                                   |\n");
    printf("|         Cestujes vytahom          |\n");
    printf("|                                   |\n");
    printf("|  Momentalne sa nachadzas na: %d    |\n", pozicia_vytahu);
    printf("|                                   |\n");
    printf("| Stlac tlacidlo, ak chces zastavit |\n");
    printf("====================================\n");

    while(1) {
        char ch1[30];

        printf( "Chces zastavit, alebo pokracovat zastavit/pokracovat :");
        scanf("%s", ch1);

        int zastavit_value=strcmp(ch1,"zastavit");
        int pokracovat_value=strcmp(ch1,"pokracovat");

        if(zastavit_value==0){
            moj_stav=zastavujem_vytah;
            return;
        }else if(pokracovat_value==0){
            moj_stav=idem_vo_vytahu;
            return;
        }else{
            printf("Nerozumiem, skus znovu \n");
        }
    }

    return;
}

void stav_vytah_dorazil_do_ciela() {
    printf("=====================================\n");
    printf("|                                   |\n");
    printf("|       Vytah dorazil do ciela      |\n");
    printf("|             Zastavuje             |\n");
    printf("|                                   |\n");
    printf("====================================\n");

    sleep(1);

    return;
}

void stav_zastavujem_vytah() {
    printf("=====================================\n");
    printf("|                                   |\n");
    printf("|       Vytah sa zastavuje          |\n");
    printf("|                                   |\n");
    printf("====================================\n");

   sleep(1);

   return;
}

void kontrola_stavov() {

    switch(moj_stav) {
        case stojim_pred_dverami:
            stav_pred_dverami();
            moj_stav = vytah_prichadza; //Zmena stavu
            break;

        case vytah_prichadza:
            stav_vytah_prichadza();
            moj_stav = stojim_vo_vytahu; //Zmena stavu
            break;

        case stojim_vo_vytahu:
            stav_stojim_vo_vytahu();
            moj_stav = idem_vo_vytahu; //Zmena stavu
            break;

        case idem_vo_vytahu:
            if(pozicia_vytahu == target_pozicia){
                moj_stav=vytah_dorazil_do_ciela; //Mozna zmena stavu
            }else if(pozicia_vytahu > target_pozicia) {
                stav_idem_vo_vytahu();
                pozicia_vytahu--;
                pozicia_uzivatela = pozicia_vytahu; //Mozna zmena stavu
            }else {
                stav_idem_vo_vytahu();
                pozicia_vytahu++;
                pozicia_uzivatela = pozicia_vytahu; //Mozna zmena stavu
            }

            break;

        case zastavujem_vytah:
            stav_zastavujem_vytah();
            moj_stav=stojim_vo_vytahu; //Zmena stavu
            break;

        case vytah_dorazil_do_ciela:
            stav_vytah_dorazil_do_ciela();
            moj_stav=stojim_vo_vytahu; //Zmena stavu
            break;
        }
}

int main() {
    while(1){
        kontrola_stavov();
    }

    return 0;
}
