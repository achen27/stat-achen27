#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "stat.h"

int metaSize(){
  struct stat stat_buff;
  stat("makefile", &stat_buff);
  return stat_buff.st_size;
}

int metaMode(){
  struct stat stat_buff;
  stat("makefile", &stat_buff);
  return stat_buff.st_mode;
}

char * metaTime(){
  struct stat stat_buff;
  stat("makefile", &stat_buff);
  return ctime(&stat_buff.st_atime);
}

void metaPermissions(){
  struct stat stat_buff;
  stat("makefile", &stat_buff);
  int perm = stat_buff.st_mode % 01000;
  int user = perm / 0100;
  int group = perm % 0100 / 010;
  int other = perm % 010;

  char * wholePerm[3] = {"", "", ""};
  char * perms[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

  for (int i = 0; i < 3;i++) {
    wholePerm[0] = perms[user];
    wholePerm[1] = perms[group];
    wholePerm[2] = perms[other];
  }

  printf("%s%s%s %o %u %u %s\n", wholePerm[0],wholePerm[1],wholePerm[2], metaSize(), stat_buff.st_uid, stat_buff.st_gid, metaTime());
}


int main(){
  printf("METADATA FOR MAKFILE\n\n");

  printf("Printing file size:\n\t");
  printf("%d", metaSize());
  printf("\n\n");

  printf("Printing mode (permissons):\n\t");
  printf("%o", metaMode());
  printf("\n\n");

  printf("Printing time of last access:\n\t");
  printf("%s", metaTime());
  printf("\n\n");

  printf("Printing in ls -l form:\n");
  metaPermissions();

  return 0;

}
