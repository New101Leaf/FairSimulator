#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Constants
#define MAX_GUESTS 300
#define MAX_TICKETS 5000 
#define ALL_DAY_PASS 200
#define MAX_RIDES 10
#define PRICE_ADMISSION 15.26
#define SINGLE_TICKET 1.13
#define ALL_DAY_PRICE 43.51
#define HALF_TICKET_PRICE .5
#define FIXED_SEED -1
#define DECADE 10
#define BACKUP_TICKETS 40
#define TOO_YOUNG 6
#define PRE_TEEN 12
#define TEEN 13
#define MAX_SINGLE_TICKETS 40
#define RIDE_ATTEMPS 20



//typedef structs
typedef struct {
    unsigned short ticketTracker;
    unsigned short allDayTracker;
    float profits; 
} ticketBoothType;


typedef struct {
    char *rideName;
    unsigned short int rideHeight;
    unsigned short int acceptedRiders;
    unsigned short int rejectedRiders;
    unsigned short int requiredTickets;

} rideType;


typedef struct {
    unsigned short int age;
    unsigned short int guestHeight;
    float guestMoney;
    unsigned short int guestTickets;
    unsigned short int hasAllDayPass;
    unsigned short int numOfRides;

} guestType;


typedef struct {
    ticketBoothType ticketBooth;
    rideType rides[MAX_RIDES];

} fairType;


//Function protoypes
int randomNum(int min, int max);
int admitGuest(fairType *fairptr, guestType *guestptr);
int purchaseRideTickets(fairType *fairPtr, guestType *guestPtr, int requestTick);
int randomTicket(int min, int size, int multiple);
int purschaseDayPass(fairType *fairPtr, guestType *guestPtr);
int forcePurchase(fairType *a, guestType *b, int numOfTick);
int goingOnRide(guestType *guestPtr, rideType *ridePtr);

int main(){
   
    //Variables
    fairType fairRides;
    fairType *ridePtr = &fairRides;  
    guestType* guest = (guestType*)malloc(sizeof(guestType)*MAX_GUESTS);

    //Randomizer variables
    const unsigned int SEED = FIXED_SEED < 0 ? time(NULL) : FIXED_SEED;
    srand(SEED);
   
    //Storing the 10 rides for the fair
    fairRides.rides[0].rideName = "Fun house";
    fairRides.rides[0].requiredTickets = 1;
    fairRides.rides[0].rideHeight = 60;
    fairRides.rides[0].acceptedRiders = 0;
    fairRides.rides[0].rejectedRiders = 0;
    fairRides.rides[1].rideName = "Merry-Go-Rond";
    fairRides.rides[1].requiredTickets = 2;
    fairRides.rides[1].rideHeight = 60;
    fairRides.rides[1].acceptedRiders = 0;
    fairRides.rides[1].rejectedRiders = 0;
    fairRides.rides[2].rideName = "Calm Train";
    fairRides.rides[2].requiredTickets = 3;
    fairRides.rides[2].rideHeight = 105;
    fairRides.rides[2].acceptedRiders = 0;
    fairRides.rides[2].rejectedRiders = 0;
    fairRides.rides[3].rideName = "Tea Cups";
    fairRides.rides[3].requiredTickets = 3;
    fairRides.rides[3].rideHeight = 108;
    fairRides.rides[3].acceptedRiders = 0;
    fairRides.rides[3].rejectedRiders = 0;
    fairRides.rides[4].rideName = "Ferris Wheel";
    fairRides.rides[4].requiredTickets = 4;
    fairRides.rides[4].rideHeight = 110;
    fairRides.rides[4].acceptedRiders = 0;
    fairRides.rides[4].rejectedRiders = 0;
    fairRides.rides[5].rideName = "Back Destroyer";
    fairRides.rides[5].requiredTickets = 4;
    fairRides.rides[5].rideHeight = 150;
    fairRides.rides[5].acceptedRiders = 0;
    fairRides.rides[5].rejectedRiders = 0;
    fairRides.rides[6].rideName = "Pirate Ship";
    fairRides.rides[6].requiredTickets = 4;
    fairRides.rides[6].rideHeight = 152;
    fairRides.rides[6].acceptedRiders = 0;
    fairRides.rides[6].rejectedRiders = 0;
    fairRides.rides[7].rideName = "Drop To Death";
    fairRides.rides[7].requiredTickets = 5;
    fairRides.rides[7].rideHeight = 154;
    fairRides.rides[7].acceptedRiders = 0;
    fairRides.rides[7].rejectedRiders = 0;
    fairRides.rides[8].rideName = "Roller Coaster";
    fairRides.rides[8].requiredTickets = 5;
    fairRides.rides[8].rideHeight = 156;
    fairRides.rides[8].acceptedRiders = 0;
    fairRides.rides[8].rejectedRiders = 0;
    fairRides.rides[9].rideName = "Tummer Tosser";
    fairRides.rides[9].requiredTickets = 5;
    fairRides.rides[9].rideHeight = 160;
    fairRides.rides[9].acceptedRiders = 0;
    fairRides.rides[9].rejectedRiders = 0;
    

    //Initialize ticketbooth
    fairType ticketStand;
    fairType *fairPtr = &ticketStand;
    //Assigning tickets and passes to the ticketbooth
    ticketStand.ticketBooth.ticketTracker = MAX_TICKETS;
    ticketStand.ticketBooth.allDayTracker = ALL_DAY_PASS;
    ticketStand.ticketBooth.profits =0;

    
   
    //Assigning ages to guests
    for(int fillGuest = 0; fillGuest < MAX_GUESTS; fillGuest++){
        //Calucating the ranges 
        //Making sure half of the guests are teenagers
        int randomAge = randomNum(1,5);
        if (randomAge ==1 || randomAge == 2){
            guest[fillGuest].age = randomNum(13,20);
        }else if(randomAge == 3){
            guest[fillGuest].age = randomNum(5,13);
            
        }else{
            guest[fillGuest].age = randomNum(20,66);
            
        }
    }
    int heightSum =0;
    //Assigning heights to guests
    for(int heightFill = 0; heightFill < MAX_GUESTS; heightFill++){
        if(guest[heightFill].age <= PRE_TEEN){
            heightSum = randomNum(72,82);
            guest[heightFill].guestHeight = (guest[heightFill].age * 6) + heightSum;
        }else{
            guest[heightFill].guestHeight = randomNum(149,281);
        }
    }
    

    //Assigning money to the guests
    unsigned short int decade =0;
    unsigned short int minMoney =0;
    float totalWallet =0;
    for(int moneyFill =0; moneyFill < MAX_GUESTS; moneyFill++){
        minMoney = (randomNum(0,5) *2) + 20;
        decade = guest[moneyFill].age / DECADE;
        //assigning money based of decade and randomization
        totalWallet = (decade)*((randomNum(0,6) *5) + 20) + minMoney;
        guest[moneyFill].guestMoney = totalWallet;
        //initilizing values
        guest[moneyFill].guestTickets = 0;
        guest[moneyFill].numOfRides =0;

    }


    //Admitting guests then assigning them single tickets or day passes
    for (int i =0; i< MAX_GUESTS; i++){
         int numOfTickets =0;
         int randomer = randomNum(0,2); // making the all day purschases and single ticket purchases random
        if(admitGuest(fairPtr, &guest[i]) == 1 ){ 
            //Admitting the guest
            numOfTickets = randomTicket(10,6,5); 
              
           if(randomer == 0){
               //if purchasing ride ticket fails use the forepurchase function
               if (purchaseRideTickets(fairPtr,&guest[i],numOfTickets) == 1 ){
                }else{
                    forcePurchase(fairPtr,&guest[i],numOfTickets);
                }
           }else{
               //Buying day pass
               if(purschaseDayPass(fairPtr,&guest[i]) ==1){
               }else{ 
                   forcePurchase(fairPtr,&guest[i],MAX_SINGLE_TICKETS);
               }
           }
        }
    }

    //Riding the rides x amount of times
    for (int j =0; j< RIDE_ATTEMPS; j++ ){
        for (int riding = 0; riding < MAX_GUESTS; riding ++){
             goingOnRide(&guest[riding],&fairRides.rides[0]);
        }
    }
    //printing stats
     printf("\n----------------------- HERE ARE THE GUESTS STATISTICS ------------------ \n"); 
     for (int guester =0; guester <MAX_GUESTS; guester++){
          
         if(guest[guester].hasAllDayPass ==1){
             printf("Guest #%3d, Age: %2d, Height: %2dcm, Money: %6.2f,  Tickets:PASS, ", guester,guest[guester].age,guest[guester].guestHeight,  guest[guester].guestMoney);
         }else{  
          printf("Guest #%3d, Age: %2d, Height: %3dcm, Money: %6.2f,  Tickets: %3d, ", guester,guest[guester].age,guest[guester].guestHeight,  guest[guester].guestMoney, guest[guester].guestTickets);
         }
         printf("Rides: %2d \n",guest[guester].numOfRides);
     }
     printf("\n ---------------- HERE ARE THE RIDE STATISTICS ----------------- ");
     printf("\n");
     for (int printer = 0; printer< MAX_RIDES; printer++){
         printf(" %14s allowed %2d guests on but turned away %2d guests \n", fairRides.rides[printer].rideName, fairRides.rides[printer].acceptedRiders, fairRides.rides[printer].rejectedRiders);
            
     }
    
    printf("\n  ------HERE ARE THE FAIR RESULTS------ \n");
    printf("$ %.2f has been earned. %d passes and %d tickets were not sold \n", fairPtr->ticketBooth.profits, fairPtr->ticketBooth.allDayTracker, fairPtr->ticketBooth.ticketTracker );



   free(guest);
    

}
/*
   Function: This function generates a random number between a specified range
   in: takes a max and min values
   out: returns a random number

*/
int randomNum(int min, int max){ 
    int v = rand() % (min - max) + min;
    return v;
}


/*
   Function: This function admits the guests 
   in: takes in a fair pointer and a guestpointer
   out: returns 1 is successful or 0 if failed

*/
int admitGuest(fairType *fairPtr, guestType *guestPtr){ // free for those who are <6 and half price >=6 and < 13
   float halfPrice = PRICE_ADMISSION *HALF_TICKET_PRICE;
   //half price calulation
   if((guestPtr->guestMoney >= halfPrice) && (guestPtr->age > TOO_YOUNG && guestPtr->age <TEEN)){
       guestPtr->guestMoney -= halfPrice;
       fairPtr->ticketBooth.profits += halfPrice;
       return 1;
   }
   
   if(guestPtr->guestMoney >= PRICE_ADMISSION && guestPtr->age >= TEEN){
         guestPtr->guestMoney -= PRICE_ADMISSION;
         fairPtr->ticketBooth.profits += PRICE_ADMISSION; 
         return 1;
   }
   //Free if age is below or equal to 6
   if (guestPtr->age <= TOO_YOUNG){
       return 1;

   }

   return 0;
}




/*
   Function: assigned tickets to the guests, the tickets are chosen randomly
   in: takes in a fair pointer and a guestpointer and int ticket amoung
   out: returns 1 is successful or 0 if failed

*/
int purchaseRideTickets(fairType *fairPtr, guestType *guestPtr, int requestTick){
    float totalPrice = requestTick * SINGLE_TICKET;
    if(guestPtr->guestMoney >= totalPrice && (requestTick <= fairPtr->ticketBooth.ticketTracker)){
        fairPtr-> ticketBooth.profits += totalPrice;
        fairPtr->ticketBooth.ticketTracker -= requestTick;
        guestPtr -> guestMoney -= totalPrice;
        guestPtr -> guestTickets = requestTick;
        return 1;
    }
    return 0;


}



/*
   Function: assiging all day passes to guests
   in: takes in a fair pointer and a guestpointer  
   out: returns 1 is successful or 0 if failed

*/
int purschaseDayPass(fairType *fairPtr, guestType *guestPtr){
    if(guestPtr->guestMoney >= ALL_DAY_PRICE && fairPtr->ticketBooth.allDayTracker > 0){
        guestPtr->guestMoney -= ALL_DAY_PRICE;
        guestPtr->hasAllDayPass =1;
        fairPtr->ticketBooth.allDayTracker --;
        fairPtr->ticketBooth.profits += ALL_DAY_PRICE;
        return 1;
    }
    return 0;
}


/*
   Function: This functions create a random ticket value between a specified range
   in:  int values 
   out: returns the random value

*/
int randomTicket(int min, int size, int multiple){
    int value =0;
    value = randomNum(0,size) * multiple;
    return value + min;
}

/*
   Function: This function is called when buying a ticket is failed, this is most likly of the cause of my profits being very high 
   //it the ticket value goes down by 1 till the guests can afford the tickets
   in: fairpointer, guestpointer and int ticket value that was requested
   out: returns the random value

*/
int forcePurchase(fairType *a , guestType *b , int numOfTick){
    int ticketAmount = numOfTick;
     for (int i = 0; i < numOfTick; i++){
         if(purchaseRideTickets(a,b,ticketAmount) == 1){
             return 1;
         } 
         ticketAmount--;
     }
     return 0;

}

/*
   Function: This function simulates a guest going on a ride
   in: guestpointer and a ridetype pointer
   out: returns 1 if succesfful or 0 if failed

*/
int goingOnRide(guestType *guestPtr, rideType *ridePtr){
    
    if (guestPtr->age <= 12){
        int randomer = randomNum(0,5);//choosing the appropriate ride range
        ridePtr += randomer; //make the pointer point to the randomized ride
      
        if((guestPtr->hasAllDayPass ==1 || guestPtr->guestTickets >= ridePtr->requiredTickets) && guestPtr->guestHeight >= ridePtr->rideHeight){
          
            if (guestPtr->hasAllDayPass != 1){ //updating structures
                guestPtr->guestTickets -= ridePtr -> requiredTickets;
                ridePtr->acceptedRiders++;
                guestPtr->numOfRides++;
                return 1;
               
            }
            else if(guestPtr->hasAllDayPass == 1){
                guestPtr->numOfRides++;
                ridePtr->acceptedRiders++;
                return 1;
            }

        }else{
            ridePtr->rejectedRiders++;
            return 1;
            
        }

    }else{
        int randomer2 = randomNum(5,10); //choosing the appropriate ride range
        ridePtr += randomer2;
     
        if((guestPtr->hasAllDayPass ==1 || guestPtr->guestTickets >= ridePtr->requiredTickets) && guestPtr->guestHeight >= ridePtr->rideHeight){ 
            if(guestPtr->hasAllDayPass != 1){
                guestPtr->guestTickets -= ridePtr -> requiredTickets;
                ridePtr->acceptedRiders++;
                guestPtr->numOfRides++;
                return 1;
            }
             else if(guestPtr->hasAllDayPass == 1){
                guestPtr->numOfRides++;
                ridePtr->acceptedRiders++;
                return 1;   
            }
        }else{
            ridePtr->rejectedRiders++;
            return 1;
        }
    }
    return 0;  
}

