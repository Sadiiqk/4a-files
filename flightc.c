#include<stdio.h>
#include<stdlib.h>
#include <string.h>








struct reserv_struct
{
  int flight_no;
  char departure_airport[5];
  char arrival_airport[5];
  char departure_time[17];
  char departure_date[17];
  int frows;
  int *fseats;
  int brows;
  int *bseats;
  int erows;
  int *eseats;

 struct reserv_struct *next;
};


int
main (int argc, char **argv)
{
  char airport1[100];
  char airport2[100];
  struct reserv_struct *head = NULL;

  fprintf (stdout, "Writing text file  (csv)\n");

 FILE *stddon = fopen ("flights.csv", "r");
  if (!stddon)
    {
      fprintf (stderr, "Could not open file %s\n", argv[1]);

     return (-1);
    }

   printf ("Enter airport code: ");
  fgets (airport1, sizeof (airport1), stdin);
  airport1[strlen (airport1) - 1] = '\0';

  printf ("Enter another airport code: ");
  fgets (airport2, sizeof (airport2), stdin);
  airport2[strlen (airport2) - 1] = '\0';

 struct reserv_struct fln;
  while (fscanf
     (stddon, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n", &fln.flight_number,
      fln.departure_airport, fln.arrival_airport, fln.departure_date,
      fln.departure_time, &fln.frows, &fln.brows, &fln.erows) == 8)
    {
      struct reserv_struct *nn =
    malloc (sizeof (struct reserv_struct));
      memcpy (nn, &fln, sizeof (struct reserv_struct));
      nn->fseats = malloc (fln.frows * sizeof (int) * 8);
                              /** 8 is the number of seats in a row */
      memset (nn->fseats, 0, fln.frows * 8);
      nn->bseats = malloc (fln.brows * sizeof (int) * 8);
                        /** 8 is the number of seats in a row */
      memset (nn->bseats, 0, fln.brows *8);
      nn->eseats = malloc (fln.erows * sizeof (int) * 8);
                        /** 8 is the number of seats in a row */
      memset (nn->eseats, 0, fln.erows *8);
      nn->next = head;
      head = nn;
    }


 return 0;

}