#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define SCRIPTS "./fall21-salt-stars/COPYTOSCRIPTS.txt"
#define SCRIPTSCONTENT "\"lint\": \"eslint '**/*.js' --fix\",\n\"lint-watch\": \"nodemon --exec 'npm run lint --silent'\"\n\"test\": \"mocha --exit './{,!(node_modules)/**}/*.spec.js'\"\n\"start\": \"lint-watch\""

void timerFunc(int seconds);
void readAndWriteFile(char *filename, char *content, int length);
void linterSetup();
void npmInstalls();
void branchIt();
void color();

int main() {
  //Git clone
  color();
  char *command;
  char branch[20];
  command = (char *)malloc(sizeof(char) * 200);
  strcpy(command, "git clone --single-branch --branch ");
  puts("Enter branch of day");
  scanf("%s", branch);
  strcat(command, branch);
  strcat(command, " https://github.com/saltsthlm/fall21-salt-stars");
  system(command);
  free(command);

  timerFunc(1);
  color();
  linterSetup();

  timerFunc(1);
  color();
  npmInstalls();

  timerFunc(1);
  color();
  branchIt();


  printf("DONE\n\n\n");

  return 0;
}


void linterSetup() {
  /*
  * Create eslintignore and .eslintrc.json with correct content
  */
  char eslintIgnoreName[] =  "./fall21-salt-stars/.eslintignore";
  char eslintignoreContent[] = "/server/public/javascript/*\nwdio.conf.js\nwebpack.config.js\n/server/config\n**/*.spec.js\n**/*.e2e.js";
  char eslintrcName[] = "./fall21-salt-stars/.eslintrc.json";
  char eslintrcNameContent[] = "{\n\"extends\": \"salt\",\n\"rules\": {\n// Overrides here\n}\n}";
  

  readAndWriteFile(eslintIgnoreName, eslintignoreContent, sizeof(eslintignoreContent));
  readAndWriteFile(eslintrcName, eslintrcNameContent, sizeof(eslintrcNameContent));

  system("cd fall21-salt-stars/; npm install eslint-config-salt --save-dev");

}

void npmInstalls() {
  system("cd fall21-salt-stars/; npm install");
  timerFunc(1);
  system("cd fall21-salt-stars/; npm install mocha --save-dev");
  timerFunc(1);
  readAndWriteFile(SCRIPTS, SCRIPTSCONTENT, sizeof(SCRIPTSCONTENT));
}

void branchIt() {
  char newBranchInput[100];
  char newBranchCommand[200];
  puts("Create and checkout new branch!");
  scanf("%s", newBranchInput);
  strcpy(newBranchCommand, "cd fall21-salt-stars/; git checkout -b ");
  strcat(newBranchCommand, newBranchInput);
  system(newBranchCommand);
}


void readAndWriteFile(char *filename, char *content, int length) {
  FILE *fp = fopen(filename, "w");

  if(!fp) {
      perror("File failed failed");
      EXIT_FAILURE;
    }

  printf("%s: %s\n", filename, "created and filled");

  size_t rp = fwrite(content, sizeof(char), length - 1, fp);
  fclose(fp);

}


void timerFunc(int seconds) {
  seconds = seconds * 400000000;
  clock_t start = clock();
  volatile unsigned sink;

  for(size_t i = 0; i < seconds; i++) {
    sink++;
  }

  printf("%s\n", "wait");

  clock_t end = clock();
}

void color() {
  printf("\033[1;36m");
}