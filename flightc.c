#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct flight_list_node {
	int flight_number;          /* !< The flight number */
	char departure_airport[20];          /* !< Departure airport code */
	char destinatio_airport[20];          /* !< Destination airport code */
	char departure_date[20];      /* !< Date departure*/
	char departure_time[20];      /* !< Time departure */
	int nfseats;               /* !< Number of First class rows */
	int *fseats;	       /* !< An array with flags of if a seat is taken or not. 1==occupied, 0==not occupied */
	int nbseats;               /* !< Number of Business class rows */
	int *bseats;               /* !< An array with flags of if a seat is taken or not. 1==occupied, 0==not occupied */
	int neseats;               /* !< Number of Economy class rows */
	int *eseats;               /* !< An array with flags of if a seat is taken or not. 1==occupied, 0==not occupied */
	struct flight_list_node *next; /* !< A pointer to the next flight information */
} FlightListNode;

typedef struct booking_list_node {
	int booking;          /* !< The booking number */
	char departure_date[15];     /* !< The departure date */
	char departure_time[15];     /* !< The departure time */
	char departure_airport[10];         /* !< The departure airport */
	char destinatio_airport[10];         /* !< The destination airport */
	char class[20];       /* !< The seat class */
	char fname[25];       /* !< Firstname */
	char lname[25];       /* !< Lastname */
	struct booking_list_node *next; /* !< a pointer to the next booking */
} BookingListNode;


struct reservation_struct
{
  int flight_number;
  char departure_airport[20];
  char arrival_airport[20];
  char departure_time[20];
  char departure_date[20];
  char destinatio_airport[20];
  int frows;
  int *fseats;
  int brows;
  int *bseats;
  int erows;
  int *eseats;
struct reservation_struct *next;
};

int allocate_seat (FlightListNode * flight, BookingListNode * booking, int *row,int *seat);

/*
        char dep[20],des[20],da[20],ti[20];
        int f,fs,bs,es,ret;
        FILE *fp = fopen("flights.csv","r");
        while( (ret = fscanf(fp,"%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",&f,dep,des,da,ti,&fs,&bs,&es)) > 0 ) {
        fprintf(stdout,"ret=%d\n",ret);
        fprintf(stdout,"%d,%s,%s,%s,%s,%d,%d,%d\n",f,dep,des,da,ti,fs,bs,es);
*/

void
print_ticket (BookingListNode * blnp, FlightListNode * flnp, int seat,
          int row)
{
  char filename[255];
  sprintf (filename, "ticket-%d.txt", blnp->booking);
  FILE *fp = fopen (filename, "w");
  if (fp)
    {
      fprintf (fp, "BOOKING:%d\n", blnp->booking);
      fprintf (fp, "FLIGHT:%d DEPARTURE:%s DESTINATION: %s %s %s\n",
           flnp->flight_number, flnp->departure_airport, flnp->destinatio_airport, flnp->departure_date,
           flnp->departure_time);
      fprintf (fp, "PASSENGER %s %s\n", blnp->fname, blnp->lname);
      fprintf (fp, "CLASS: %s\n", blnp->class);
      fprintf (fp, "ROW %d SEAT %d\n\n", row, seat);
      fclose (fp);
    }
    
}


int main (int argc, char **argv)
{
  char airport1[100];
  char airport2[100];
  struct reservation_struct *head = NULL;



}
/*
FILE *stdmovant = fopen ("flights.csv", "r");
  if (!stdmovant)
    {
      fprintf (stderr, "Could not open file %s\n", argv[1]);

    }
*/

/**
* @brief create the ticket for each booking in the booking list
* To create a ticket we need which row and seat in the booked class that
* the passenger have. Therefore we need to find the flight and search
* for free seat, then mark the seat as booked.
*/
int
create_tickets (BookingListNode * bookings, FlightListNode * flights)
{
  int num_tickets = 0;
  fprintf (stdout, "Writing tickets: ");



 /* Loop through the booking list */



 for (BookingListNode * blnp = bookings; blnp != NULL; blnp = blnp->next)
    {



     /* find the flight for this booking, see hint 6 */




      /* Loop through the flights list ... */
      for (FlightListNode * flnp = flights; flnp != NULL; flnp = flnp->next)
    {



     /* Check if this flight have the same departure, destination,
         date and time as the booking have */
      if (!strcmp (blnp->departure_airport, flnp->departure_airport) &&
          !strcmp (blnp->departure_airport, flnp->departure_airport) &&
          !strcmp (blnp->departure_date, flnp->departure_date) &&
          !strcmp (blnp->departure_time, flnp->departure_time))
        {



         int row = 0, seat = 0;



         /* have booking and flight, now find a seat, mark it booked
             and print the ticket */



         if (allocate_seat (flnp, blnp, &row, &seat))
        {        /* hint 8 */
          fprintf (stdout, "[ticket-%d.txt]", blnp->booking);
          print_ticket (blnp, flnp, seat, row);    /* hint 9 */
          num_tickets++;
        }
        //https:        //www.onlinegdb.com/online_c_compiler#tab-stdin
          /* allocate seat and mark it booked */
          /* see hint 7 */
        }
    }
    }
  fprintf (stdout, "Created  %d tickets\n\n", num_tickets);
  return (num_tickets);
}






int
allocate_seat (FlightListNode * flight, BookingListNode * booking, int *row,
           int *seat)
{
  int sn = 0;
  int rn = 0;
  /* is the booking in first class ? */
  if (strcmp ("first", booking->class) == 0)
    {
      /* Yes, now find a free seat in first class */
      for (int p = 0; p < flight->nfseats * 7; p++)
    {
      if (flight->fseats[p] == 0)
        {            /* seat is free */
          flight->fseats[p] = 1;    /* set it booked */
          sn = p + 1;    /* calculate seat number */
          rn = (int) p / 7 + 1;    /* calculate row number */
          break;        /* no need to look for more */
        }
    }
    }
  /* is the booking in business class ? */
  if (strcmp ("business", booking->class) == 0)
    {
      /* Yes, now find a free seat in business class */
      for (int p = 0; p < flight->nbseats * 7; p++)
    {
      if (flight->bseats[p] == 0)
        {            /* seat is free */
          flight->bseats[p] = 1;    /* set it booked */
          sn = p + flight->nfseats * 7 + 1;    /* calculate seat number */
          rn = flight->nfseats + (int) p / 7 + 1;    /* calculate row number */
          break;        /* no need to look for more */
        }
    }
    }
  /* is the booking in economy class ? */
  if (strcmp ("economy", booking->class) == 0)
    {
      /* Yes, now find a free seat in economy class */
      for (int p = 0; p < flight->neseats * 7; p++)
    {
      if (flight->eseats[p] == 0)
        {            /* seat is free */
          flight->eseats[p] = 1;    /* set it booked */
          sn = p + flight->nfseats * 7 + flight->nbseats * 7 + 1;    /* calculate seat number */
          rn = flight->nfseats + flight->nbseats + (int) p / 7 + 1;    /* calculate row number */
          break;        /* no need to look for more */
        }
    }
    }
  if (rn == 0 || sn == 0)
    {
      fprintf (stdout,
           "did not find class \"%s\" for booking on this plane\n",
           booking->class);
      return (0);
    }
  *row = rn;
  *seat = sn;
  return (1);
}





 //return 0;

//}
   
