#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
  key_t key;
  int shmid;
  char * data;

  // set up shared memory
  key = ftok("mykey", 'f');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *) 0, 0);

  if (* data)
  {
    printf("Segment's contents: %s\n", data);
  }
  else
  {
    printf("Empty Segment.\n");
  }

  char intake[200];
  intake[0] = '\0';

  while (strcmp(intake, "y\n") != 0 && strcmp(intake, "n\n") != 0)
  {
    printf("\n");
    printf("Would you like to modify the segment?: ( y or n ) ");

    fgets(intake, 200, stdin);
  }

  if (!strcmp(intake, "y\n"))
  {
    printf("\n");
    printf("What would you like to write?\n");

    fgets(intake, 200, stdin);
    strcpy(data, intake);
  }

  intake[0] = '\0';

  while (strcmp(intake, "y\n") != 0 && strcmp(intake, "n\n") != 0)
  {
    printf("\n");
    printf("Would you like to delete the segment?: ( y or n ) ");

    fgets(intake, 200, stdin);
  }

  if (!strcmp(intake, "y\n"))
  {
    printf("\n");
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("The segment has been deleted.\n");
  }
  else
  {
    printf("Segment present: %s\n", data);
  }

}
