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
#include <sys/wait.h>
#include <unistd.h>
#define rand_pok (750+rand()%(1000-750+1)) //генерит для погрузчика  750 до 1000
#define rand_mag (180+rand()%(220-180+1)) //генерит для магазина от 180 до 220
#define rand_gruz (150+rand()%(220-150+1)) //генерит для погрузчика от 150 до 220
#define MAG_NUMBER 5 //колличесвто магаззинов 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct data
{
	pthread_mutex_t	mutex[MAG_NUMBER];
	int	products[MAG_NUMBER];
} shared;
// static int pogruz;
//int flag_mag1=0,flag_mag2=0,flag_mag3=0,flag_mag4=0,flag_mag5=0;
void* pokypatel1(void *args);
void* pokypatel2(void *args);
void* pokypatel3(void *args);
void* pogryz(void *args);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
	pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    srand(time(NULL));
    int  pogruz=rand_gruz;
    for (int i=0; i<MAG_NUMBER; i++)
    {
        shared.products[i]=rand_mag;
    }

   for(int a=0; a<MAG_NUMBER;a++)
   {   
       if(a==0){ printf("starting quantity of goods in the store\n"); } 
       printf("|M%d=%d|",a+1,shared.products[a]);

       if(a==MAG_NUMBER-1) {printf("\nM-magazin and № №\n"); }
    }
   
    pthread_create(&thread1,NULL,pokypatel1,NULL);
    pthread_create(&thread2,NULL,pokypatel2,NULL);
    pthread_create(&thread3,NULL,pokypatel3,NULL);
    pthread_create(&thread4,NULL,pogryz,NULL);
         int a=pthread_join(thread1,NULL);
        // printf("a iz main %d\n",a);
         int b=pthread_join(thread2,NULL);
       //  printf("b iz main %d\n",b);
         int c=pthread_join(thread3,NULL);
      //   printf("c iz main %d\n",b);

    if ((a&&b&&c)==0)  ///завершаем погрузчик
    { 
        pthread_cancel (thread4); 
        printf("pogryzchik ymer\n"); 
    }
    
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// покупаткль 1
void* pokypatel1(void *args){ 
     int hotelka=rand_pok;
     printf("pokypatel 1 start=%d \n",hotelka);
  //  int *i =(int*)args;
    srand(time(NULL));
    
    while(1)
    {
        for (int i=0; i<MAG_NUMBER; i++) 
        {
            if(pthread_mutex_trylock(&shared.mutex[i])==0)
            for(int a=0; a<MAG_NUMBER;a++)
            {   
                if (a==0){printf("pokepatel 1 zabral"); }
                printf("|M%d=%d|",a+1,shared.products[a]);
                
                if(a==MAG_NUMBER-1) {printf("\n"); }
            }
            hotelka-=shared.products[i];
            shared.products[i]=0;
            
            if(hotelka<0) { shared.products[i]=hotelka*-1; hotelka=0; }
            printf("pokypatel 1 =%d \n",hotelka);
            
            pthread_mutex_unlock(&shared.mutex[i]);

            sleep(1);
            if(hotelka==0)
            {
                 printf("potok1 ymer\n"); break; pthread_exit(NULL);
                
            }

        }
        if(hotelka==0) pthread_exit(NULL);
        
        
    }  

}
///////////////////////////////////////////////////////////////////////////////////////////////////////// покупаткль 2
void* pokypatel2(void *args){ 
    // int *i =(int*)args;
     int hotelka=rand_pok;
     printf("pokypatel 2 start=%d \n",hotelka);
     srand(time(NULL));


  
    while(1)
    {
        for (int i=0; i<MAG_NUMBER; i++) 
        {
            if(pthread_mutex_trylock(&shared.mutex[i])==0)
            for(int a=0; a<MAG_NUMBER;a++)
            {   
                if (a==0){printf("pokepatel 2 zabral"); }
                printf("|M%d=%d|",a+1,shared.products[a]);
                
                if(a==MAG_NUMBER-1) {printf("\n"); }
            }
            hotelka-=shared.products[i];
            shared.products[i]=0;
            
            if(hotelka<0) { shared.products[i]=hotelka*-1; hotelka=0; }
            printf("pokypatel 2 =%d \n",hotelka);
            
            pthread_mutex_unlock(&shared.mutex[i]);

            sleep(1);
            if(hotelka==0)
            {
                 printf("potok2 ymer\n"); break; pthread_exit(NULL);
                
            }

        }
        if(hotelka==0) pthread_exit(NULL);
        
        
    }
  
 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// покупатель 3
void* pokypatel3(void *args){ 
    // int *i =(int*)args;
     int hotelka=rand_pok;
     printf("pokypatel 3 start=%d \n",hotelka);
     srand(time(NULL));

    while(1)
    {
        for (int i=0; i<MAG_NUMBER; i++) 
        {
            if(pthread_mutex_trylock(&shared.mutex[i])==0)
            for(int a=0; a<MAG_NUMBER;a++)
            {   
                if (a==0){printf("pokepatel 3 zabral"); }
                printf("|M%d=%d|",a+1,shared.products[a]);
                
                if(a==MAG_NUMBER-1) {printf("\n"); }
            }
            hotelka-=shared.products[i];
            shared.products[i]=0;
            
            if(hotelka<0) { shared.products[i]=hotelka*-1; hotelka=0; }
            printf("pokypatel 3 =%d \n",hotelka);
            
            pthread_mutex_unlock(&shared.mutex[i]);

            sleep(1);
            if(hotelka==0)
            {
             printf("potok3 ymer\n"); break; pthread_exit(NULL);
                
            }

        }
        if(hotelka==0) pthread_exit(NULL);
        
        
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// погрузчик
void* pogryz(void *args){ 
    
    printf("POGRYZCHIK start\n");
   // int *i =(int*)args;
     int zagryzka=rand_gruz;
    srand(time(NULL));


  
        while(1){
            for (int i=0; i<MAG_NUMBER; i++) 
            {
                if(pthread_mutex_trylock(&shared.mutex[i])==0)
                for(int a=0; a<MAG_NUMBER;a++)
                {   
                 if (a==0){printf("POGRYZCHIK zagryzil"); }
                 printf("|M%d=%d|",a+1,shared.products[a]);
                 if(a==MAG_NUMBER-1) {printf("\n"); }
                }
                if (shared.products[i]==0)
                {
                shared.products[i]=zagryzka;
                zagryzka=rand_gruz;
                }
               sleep(1);

            }
          
           
        }
}        
