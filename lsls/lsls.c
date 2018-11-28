#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
/**
 * Main
 */
int main(int argc, char **argv)
{
  // Parse command line
  char *path;
  if(argc == 1){
    path = "./";
  }else if ( argc == 2){
    path = argv[1];
  }else{
    fprintf(stderr, "can be only one!\n");
    exit(1);
  }
  DIR *directory = opendir(path);
  // Open directory
  if(directory == NULL){
    fprintf(stderr, "Error opening");
    exit(1);
  }
  struct dirent *ent;
  struct stat buf;
  char fullpath[8192];
  // Repeatly read and print entries
   while((ent = readdir(directory)) != NULL){
    sprintf(fullpath, "%s%s", path, ent->d_name);
    printf("%s\n", fullpath);
    stat(fullpath, &buf);
    // printf("%s %lld\n", ent->d_name, buf.st_size);
    if (S_ISREG(buf.st_mode))
    {
      printf(">%7lld %s\n", buf.st_size, ent->d_name);
    }
    else
    {
      printf(">%7s %s\n", "<DIR>", ent->d_name);
    }
  }
  // Close directory
  closedir(directory);
  return 0;
}