#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PROCS 64

int print_procs() {
  struct process_info procs[MAX_PROCS];
  int n, i;

  n = getprocs(procs, MAX_PROCS);
  if (n < 0) {
    printf("getprocs failed\n");
    return -1;
  }

  printf("\nPID\tSTATE\t\tNAME\n");
  for (i = 0; i < n; i++) {
    printf("%d\t", procs[i].pid);

    switch (procs[i].state) {
      case 1: printf("USED\t\t"); break;
      case 2: printf("SLEEPING\t"); break;
      case 3: printf("RUNNABLE\t"); break;
      case 4: printf("RUNNING\t\t"); break;
      case 5: printf("ZOMBIE\t\t"); break;
      default: printf("UNKNOWN\t\t"); break;
    }

    printf("%s\n", procs[i].name);
  }

  return n;
}

int main() {
  char buf[16];

  // Initial display of processes
  printf("Current processes:\n");
  print_procs();

  // Prompt user for PID
  printf("\nEnter PID to kill: ");
  gets(buf, sizeof(buf));
  int pid = atoi(buf);

  // Basic validation
  if (pid <= 0) {
    printf("Invalid PID.\n");
    exit(1);
  }

  // Try to kill the process
  if (kill(pid) < 0)
    printf("Failed to kill PID %d\n", pid);
  else {
    printf("Successfully killed PID %d\n", pid);
    
    // Delay to allow kill to take effect (optional)
    sleep(1);

    // Show remaining processes
    printf("\nRemaining processes after kill:\n");
    print_procs();

    printf("Returning to shell...\n");
  }

  exit(0);
}

