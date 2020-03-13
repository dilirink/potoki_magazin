/*   
    ╔══╗─╔══╗╔╗──╔══╗╔═══╗╔══╗╔╗─╔╗╔╗╔══╗
    ║╔╗╚╗╚╗╔╝║║──╚╗╔╝║╔═╗║╚╗╔╝║╚═╝║║║║╔═╝
    ║║╚╗║─║║─║║───║║─║╚═╝║─║║─║╔╗─║║╚╝║
    ║║─║║─║║─║║───║║─║╔╗╔╝─║║─║║╚╗║║╔╗║
    ║╚═╝║╔╝╚╗║╚═╗╔╝╚╗║║║║─╔╝╚╗║║─║║║║║╚═╗
    ╚═══╝╚══╝╚══╝╚══╝╚╝╚╝─╚══╝╚╝─╚╝╚╝╚══╝ magazin v2 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#define rand_pok (750+rand()%(1000-750+1)) //генерит для погрузчика  750 до 1000
#define rand_mag (180+rand()%(220-180+1)) //генерит для магазина от 180 до 220
#define rand_gruz (150+rand()%(220-150+1)) //генерит для погрузчика от 150 до 220
#define MAG_NUMBER 6 //колличесвто магаззинов 
#define POK_NUMBER 3 //колличесвто покупателей 
#define POG_NUMBER 1 //колличесвто погрузчиков 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct data
{
	pthread_mutex_t	mutex[MAG_NUMBER];
	int	products[MAG_NUMBER];
    int pogryzchik[POG_NUMBER];
} shared;

void* pokypatel(void *args);
void* pogryz(void *args);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int arg) /// если при запуске передать 2- то не происзойдёт запуска погрузчика 
{   
    pthread_t thread[POK_NUMBER], thread_pogryz;

    srand(time(NULL));
    int  pogruz=rand_gruz;
    for (int i=0; i<MAG_NUMBER; i++)
    {
        shared.products[i]=rand_mag;
    }

    if(arg==1){
       pthread_create(&thread_pogryz,NULL,pogryz,NULL); //запуск бедолаги погрузчика
    }
    
    if(arg==2)
    {
        printf("pogryzchik off");
    }

   for(int a=0; a<MAG_NUMBER;a++) //генерацая товара в магазчинах 
    {   
       if(a==0){ printf("starting quantity of goods in the store\n"); } 
       printf("|M%d=%d|",a+1,shared.products[a]);

       if(a==MAG_NUMBER-1) {printf("\nM-magazin and № №\n"); }
    }

    for(int z=1;z<POK_NUMBER+1;z++)  // запуск покупателей
    {
        pthread_create(&thread[z],NULL,pokypatel,&z);
    }

    

    for(int z=1;z<POK_NUMBER+1;z++)  //ожидания завершения покупателей
    {
        pthread_join(thread[z],NULL);
    }

    
    
    

    
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////// информация о магазинах
//void* pokypatel(void *args)

///////////////////////////////////////////////////////////////////////////////////////////////////////// покупатели
void* pokypatel(void *args)
{ 
    int hotelka=rand_pok;
    int *i =(int*)args;
    printf("\n START pokypatel%d =%d \n",*i,hotelka);
    srand(time(NULL));
    
    while(1)
    {
        
        for (int i=0; i<MAG_NUMBER; i++) 
        {   
            sleep(1);
            if(pthread_mutex_trylock(&shared.mutex[i])==0)

            for(int a=0; a<MAG_NUMBER;a++)
            {   
                if (a==0){printf("pokypatel %d zabral",i); }
                printf("|M%d=%d|",a+1,shared.products[a]);
                
                if(a==MAG_NUMBER-1) {printf("\n"); }
            }

            hotelka-=shared.products[i];
            shared.products[i]=0;
            
            if(hotelka<0) { shared.products[i]=hotelka*-1; hotelka=0; }
            printf("pokypatel %d =%d \n",i,hotelka);
            
            pthread_mutex_unlock(&shared.mutex[i]);

            if(hotelka==0)
            {
                 printf("pokypatel %d ymer\n",i); break; pthread_exit(NULL);
                
            }

        }
        if(hotelka==0) pthread_exit(NULL);
        
        
    }  

}    


///////////////////////////////////////////////////////////////////////////////////////////////////////// погрузчик
void* pogryz(void *args)
{ 

    int *i =(int*)args;

    printf("POGRYZCHIK start\n");

    int zagryzka=rand_gruz;

    srand(time(NULL));

        while(1){
            
            for (int i=0; i<MAG_NUMBER; i++) 
            {   
                sleep(1);
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
               

            }
          
           
        }
}        
