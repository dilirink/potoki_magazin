/*   
    ╔══╗─╔══╗╔╗──╔══╗╔═══╗╔══╗╔╗─╔╗╔╗╔══╗
    ║╔╗╚╗╚╗╔╝║║──╚╗╔╝║╔═╗║╚╗╔╝║╚═╝║║║║╔═╝
    ║║╚╗║─║║─║║───║║─║╚═╝║─║║─║╔╗─║║╚╝║
    ║║─║║─║║─║║───║║─║╔╗╔╝─║║─║║╚╗║║╔╗║
    ║╚═╝║╔╝╚╗║╚═╗╔╝╚╗║║║║─╔╝╚╗║║─║║║║║╚═╗
    ╚═══╝╚══╝╚══╝╚══╝╚╝╚╝─╚══╝╚╝─╚╝╚╝╚══╝*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define rand_pok (750+rand()%(1000-750+1)) //генерит для погрузчика  750 до 1000
#define rand_mag (180+rand()%(220-180+1)) //генерит для магазина от 180 до 220
#define rand_gruz (150+rand()%(220-150+1)) //генерит для погрузчика от 150 до 220

// static int pogruz;
static int flag_mag1=0,flag_mag2=0,flag_mag3=0,flag_mag4=0,flag_mag5=0;
void* pokypatel1(void *args);
void* pokypatel2(void *args);

int main(void){
	pthread_t thread1;
    pthread_t thread2;
    srand(time(NULL));
    int  m[5]={500,500,500,500,500};
    
    int  pogruz=rand_gruz;
    int mag[5];
        for(int e=0;e<=5;e++ ){
            mag[e]=m[e];

        }

    printf(" MAGAZIN\n");   
    printf(" ____________________\n");
    printf("|%d||%d|%d|%d|%d|\n",m[0],m[1],m[2],m[3],m[4]);
    printf(" ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
   
   // printf("pogruzchik=%d\n",pogruz);

    pthread_create(&thread1,NULL,pokypatel1,&mag[0]);
         pthread_join(thread1,NULL);
   // pthread_cancel(thread1);
  //  pthread_create(&thread2,NULL,pokypatel2,NULL);
      //   pthread_join(thread2,NULL);
    
}

void* pokypatel1(void *args){ 

    int *i =(int*)args;

    srand(time(NULL));

    int hotelka = rand_pok;
    hotelka-=*i;
    printf("pokypatel1=%d\n",hotelka);
    printf("i=%d\n",*i);
  
        while(hotelka!=0){
            if(flag_mag1==0){
                flag_mag1=1;
                printf("pokypatel 1 v mag 1");
                hotelka-=*i;
            }
            if(flag_mag2==0){
                flag_mag2=1;
                printf("pokypatel 1 v mag 2");
                hotelka-=*(i+1);
            }
            if(flag_mag3==0){
                flag_mag3=1;
                printf("pokypatel 1 v mag 3");
                hotelka-=*(i+2);
            }
            if(flag_mag4==0){
                flag_mag4=1;
                printf("pokypatel 1 v mag 4");
                hotelka-=*(i+3);
            }
            if(flag_mag5==0){
                flag_mag5=1;
                printf("pokypatel 1 v mag 5");
                hotelka-=*(i+4);
            }
            
        }
  
    if(hotelka==0){  printf("zakypilsa"); } 
   // pthread_exit(0);pthread_testcancel();
    
}

// void* pokypatel2(void *args){ 

// }
