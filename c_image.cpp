#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <vector>

#include <stdio.h>
#include <sys/select.h>

using namespace cv;
using namespace std;
struct sharemap
{
    char p;
    char picmap[2][120000];
};
static void sleep_ms(unsigned int secs)

{
    struct timeval tval;
    tval.tv_sec=secs/1000;
    tval.tv_usec=(secs*1000)%1000000;
    select(0,NULL,NULL,NULL,&tval);
}
int main(int argc, char** argv)
{
    IplImage *src[6];
    src[0] = cvLoadImage("giraffe.jpg");
    src[1] = cvLoadImage("horses.jpg");
    src[2] = cvLoadImage("scream.jpg");
    src[3] = cvLoadImage("eagle.jpg");
    src[4] = cvLoadImage("dog.jpg");
    src[5] = cvLoadImage("person.jpg");
    int fp = open("dst.bmp",O_CREAT|O_RDWR,00777); 
    if(fp == -1)
    {
        printf("error open\n");
        exit(1);
    }
    printf("success open\n");
    //cout<<sizeof(sharemap)<<endl;
    
    //lseek(fp,sizeof(sharemap),SEEK_SET);
    struct stat file_stat;
    if(fstat(fp,&file_stat)==-1)      
    {
    perror("get file stat fail:");
        close(fp);
        exit(1);
    }
    printf("get file\n");
    int len = file_stat.st_size;
    //int flength = lseek(fp, 1000000, SEEK_SET);
    //int len = lseek(fp,1,SEEK_END);
    cout<<"len"<<len<<endl;
    //write(fp, "0", 1);
    //long int len = sizeof(sharemap);
    //sharemap *ptr = (sharemap*) mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fp,0 );
    uchar *ptr = (uchar*) mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fp,0 );

    if(ptr==MAP_FAILED){
        perror("mmap error");
        close(fp);
        return -1; 
    } 
    close(fp);
    //cout<<"content is "<< ptr[0]<<endl;
    //cout<<"content is "<< ptr[1]<<endl;
    //unsigned int m = 25535;
    //uchar m1 = (uchar)(m%255);
    //uchar m2 = (uchar)(m/255);
    //uchar n = 100;
    //cout <<"m "<< (float)m<<endl;

    //memcpy(ptr, &n, 4);
    //memcpy(ptr+1, &m, 4);
    //cout<<"data len"<<sizeof(src->imageData)<< "  "<<src->imageSize <<endl;
    int srccnt = 3;
    int ptrcnt = 0;
    int ptrcnt2 = ptrcnt+25;
    (*ptr) = 0;
    //*(ptr+1) = srccnt;
    int srcsize = src[0]->imageSize;
    /*memcpy(ptr+54,src[0]->imageData,srcsize);
    memcpy(ptr+54+srcsize,src[1]->imageData,srcsize);
    memcpy(ptr+54+srcsize*2,src[2]->imageData,srcsize);
    memcpy(ptr+54+srcsize*3,src[3]->imageData,srcsize);
    memcpy(ptr+54+srcsize*4,src[4]->imageData,srcsize);
    */
    while(true)
    {
        srccnt = srccnt%6;
        ptrcnt = ptrcnt%50;
        ptrcnt2 = (ptrcnt+25)%50;
        (*ptr) = ptrcnt2;
        *(ptr+1) = srccnt;
        memcpy(ptr+54+srcsize*ptrcnt,src[srccnt]->imageData,srcsize);
        //sleep_ms(100);
        //msync(ptr, len, MS_ASYNC); 
        cout<<"src : "<<srccnt<<endl;  
        cvNamedWindow("Image:",1);
        cvShowImage("Image:",src[srccnt]);
        srccnt++;
        ptrcnt++;     
        if (cv::waitKey(30) == 'q')  
        {             
            break;  
        }        
    }
    cvDestroyWindow("Image:");
    cvReleaseImage(src);
    munmap(ptr,len);
    printf( "umap ok \n" ); 
    //imshow("scream",scream);
    //waitKey(0);
    return 0;
}
