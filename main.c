#include <Windows.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

void MouseTo(int x, int y) {
    RECT desktop_rect;
    GetClientRect(GetDesktopWindow(), &desktop_rect);
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags =
        MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    input.mi.dx = x * 65536 / desktop_rect.right;
    input.mi.dy = y * 65536 / desktop_rect.bottom;
    SendInput(1, &input, sizeof(input));
}

void MouseLButton(bool tf_down_up) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = tf_down_up ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(input));
}

void MouseLButtonDown() { MouseLButton(true);  }
void MouseLButtonUp()   { MouseLButton(false); }

void click(){
    MouseLButtonDown();
    MouseLButtonUp();
}

void mnc(int x, int y){ // move and click
    MouseTo(x,y);
    click();
    printf("\nclick: x:%d y:%d\n",x,y);
}



int main(int argc, char*argv[]){
    int i;
    int hour,min,sec;
    time_t t;
    struct tm* aTm;

    sscanf(argv[1],"%d",&hour);
    sscanf(argv[2],"%d",&min);
    sscanf(argv[3],"%d",&sec);

    printf("waiting for %d:%d:%d\n",hour,min,sec);
    /*
    while(1){
        if(aTm->tm_hour==hour&&aTm->tm_min==min&&aTm->tm_sec==sec){
            printf("go!");
        }
    }*/
    while(1){
        t = time(NULL);
        aTm = localtime(&t);

        printf("NOW %d:%d:%d\r",aTm->tm_hour,aTm->tm_min,aTm->tm_sec);
        if(aTm->tm_hour==hour && aTm->tm_min==min && aTm->tm_sec==sec){

            FILE *f;
            f=fopen("cords.txt","r");

            int k,i,l[100],cords_pairs[100];

            for(k=0;!feof(f);k++)
                fscanf(f,"%d",&l[k]);

            for(i=0;i<k;i++){
                cords_pairs[i]=l[i];
                printf("%d ",cords_pairs[i]);
            }

            fclose(f);

            i=0;
            while(i<k){
                mnc(cords_pairs[i],cords_pairs[i+1]);
                //Sleep(10);
                //printf("\n%d:%d",cords_pairs[i],cords_pairs[i+1]);
                i+=2;
            }





            break;
        }
    }


    return 0;
}