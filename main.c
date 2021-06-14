#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "subirane.h"



extern int do_capture(const char *device, int grab_flag);

/*******************************************
 * 
 * 
 * ****************************************/
void read_mouse(void * device)
{
    //do_capture("/dev/input/event5", 0);
    do_capture((char *)device, 0);


}
/*******************************************
 * 
 * 
 * ****************************************/
int main(int argc, char **argv) 
{
    printf("Start\n");

    /////////////////////////////// zad 1 - add two numbers //////////////////////////////
    if(argc < 3)printf("Please put arguments\n");

    int sub1 = argv[1][0]-0x30;
    int sub2 = atoi(argv[2]);
    printf("var1 = %d\n", sub1);
    printf("var2 = %d\n", sub2);

    int res;
    subirane sub;
    sub.sub1 = sub1;
    sub.sub2 = sub2;
    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, calc_sum, (void *)&sub);
    void * ressult = NULL;
    pthread_join(thread_id1, &ressult);
    printf("res = %d\n", (int *)ressult);



    // /////////////////////////////// zad 2 - read two HID devices from /dev/input/ folder //////////////////////////////
    // pthread_t thread_id2;
    // pthread_create(&thread_id2, NULL, read_mouse, (void *)"/dev/input/event5");
	// pthread_t thread_id3;
    // pthread_create(&thread_id3, NULL, read_mouse, (void *)"/dev/input/event11");
    // pthread_join(thread_id2, NULL);
	// pthread_join(thread_id3, NULL);



    ///////////////////////////// zad 3 - add two numbers by callign external program (bc) //////////////////////////////
    FILE *pipe_fp;
    char write_buf[100];
    /* Create one way pipe line with call to popen() */
    if (( pipe_fp = popen("bc", "w")) == NULL)
    {
        perror("popen");
        exit(1);
    }
    /* Processing loop */
    strcpy(write_buf, argv[1]);
    strcat(write_buf,"+");
    strcat(write_buf, argv[2]);
    printf("%s\n",write_buf);
    //fputs(write_buf, pipe_fp);
    fprintf(pipe_fp, "%s\n", write_buf);
    fflush(pipe_fp);
    /* Close the pipe */
    pclose(pipe_fp);

                        ///////// second way
    // FILE *pipe_fp;
    // char write_buf[100];
    char read_buf[100];
    strcpy(write_buf,"echo \"");
    strcat(write_buf, argv[1]);
    strcat(write_buf,"+");
    strcat(write_buf, argv[2]);
    strcat(write_buf, "\" | bc");
    printf("%s\n",write_buf);
    /* Create one way pipe line with call to popen() */
    if (( pipe_fp = popen(write_buf, "r")) == NULL)
    {
        perror("popen");
        exit(1);
    }
    /* Processing loop */
    fgets(read_buf, sizeof(read_buf), pipe_fp);
    printf("answ = %s", read_buf);
    /* Close the pipe */
    pclose(pipe_fp);

    ///////////////////////////// zad 4 - call /bin/ls from the C program //////////////////////////////

    char buf[100];
    pid_t child_pid;
    child_pid = fork();
    if(child_pid == -1)
    {
        perror("fork failed");
        exit(1);
    }

    if(child_pid == 0){  
        execlp("ls", "ls", NULL);
        fgets(buf, sizeof(buf), pipe_fp);
        printf("%s", buf);
        }
    else{
        wait(NULL);
        printf("child complete\n");
    }

    int filedescriptor[2];
    pid_t childpid2;
    char buf_read[100];

    if(pipe(filedescriptor) == -1)
    {
        perror("pipe error");
        exit(1);
    }
    if((childpid2 = fork()) == -1)
    {
            perror("fork error");
            exit(1);
    }
    
    if(childpid2==0)//Child
     {
          close(filedescriptor[0]);
          execlp("ls", "ls", NULL);
     }
     else//Parent
     {
        close(filedescriptor[1]);
        read(filedescriptor[0], buf_read, sizeof(buf_read));
        printf("Received string: %s", buf_read);
     }







    char resultat[5];
    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    int resultat_fork = fork();

    if (resultat_fork == -1)
    {
        exit(EXIT_FAILURE);
    }

    if (resultat_fork != 0)
    {
        printf("I am the parent\n");

        close(pipe1[0]);
        close(pipe2[1]);

        strcpy(write_buf, argv[1]);
        strcat(write_buf,"+");
        strcat(write_buf, argv[2]);
        printf("%s\n",write_buf);

        if (write(pipe1[1], write_buf, 3) != 3)
            fprintf(stderr, "write to child failed\n");

        // if (write(pipe1[1], "20*5\n", sizeof("20*5\n") - 1) != sizeof("20*5\n") - 1)
        //     fprintf(stderr, "write to child failed\n");

        int nbytes = read(pipe2[0], resultat, sizeof(resultat));
        if (nbytes <= 0)
            fprintf(stderr, "read from child failed\n");
        else
            printf("resultat: [%.*s]\n", nbytes, resultat);

        close(pipe1[1]);
        close(pipe2[0]);
    }
    else
    {
        printf("I am the child\n");

        close(pipe1[1]);
        close(pipe2[0]);
        dup2(pipe1[0], 0);
        dup2(pipe2[1], 1);
        close(pipe1[0]);    /* More closes! */
        close(pipe2[1]);    /* More closes! */

        execlp("bc", "bc", NULL);
        fprintf(stderr, "Failed to execute bc\n");
        exit(EXIT_FAILURE);
    }



	printf("STOP\n");
    return 0;
}
