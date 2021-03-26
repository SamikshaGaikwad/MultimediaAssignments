#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DATASIZE 375000 			//Total size of image
#define H 500 							//Height of image
#define W 750 							//width og image
FILE *input_file,*IMG33_X, *IMG33_Y, *IMG55_X ,*IMG55_Y;											//define file pointers to input and output images
unsigned char img[H][W],  OUTPUT33_X[H][W], OUTPUT33_Y[H][W], OUTPUT55_X[H][W],OUTPUT55_Y[H][W];	//define 2d array to store the pixels of input and output image
int i, j, k, l, tempY, tempX, tempY1, tempX1; 														//define all the counters and temporary variables 
int FILTER33_X[3][3] = {-1,0,1,-2,0,2,-1,0,1}; 														//Filter for 3*3 image in horizontal direction
int FILTER33_Y[3][3] = {-1,-2,-1,0,0,0,1,2,1}; 														//Filter for 3*3 image in vertical  direction
int FILTER55_X[5][5] = {-1,-2,0,2,1,-2,-4,0,4,2,-4,-8,0,8,4,-2,-4,0,4,2,-1,-2,0,2,1};				//Filter for 5*5 image in horizontal direction
int FILTER55_Y[5][5] = {-1,-2,-4,-2,-1,-2,-4,-8,-4,-2,0,0,0,0,0,2,4,8,4,2,1,2,4,2,1};				//Filter for 5*5 image in vertical direction
//Main function
int main( ) 
{
    input_file = fopen("unesco750-1.raw","rb");			//Open input file
    fread(img, 1, DATASIZE, input_file);				//read file
    fclose(input_file);									//close file
// 3*3 Filtering of the image in horizontal and vertical diection.
    for (i=0; i<H; i++) 
	{
        for (j=0; j<W; j++) 
		{
        	
            if (i==0 || i==H-1 || j==0 || j==W-1)		//condition to fit the image as line 1 is not considered
			{
            	OUTPUT33_X[i][j] = 128;  				//set values to 128
				OUTPUT33_Y[i][j] = 128;       			//set values to 128
			}
			else 
			{				
				tempY=0;		//initialize temporary variable of Y to 0
				tempX=0;		//intialize temporary variable of X to 0
				
				// The loop to rotate the filter by 3*3	
				for (k=0; k<3; k++)
				{										
					for (l=0; l<3; l++)
					{														
						tempX1 = FILTER33_X[k][l]*img[i-1+k][j-1+l]; //Apply filter
						tempX += tempX1;							//Add to the existing value
						tempY1 = FILTER33_Y[k][l]*img[i-1+k][j-1+l];	//Apply filter
						tempY += tempY1;								//Add to the existing value
						
					}					
				}
				OUTPUT33_X[i][j] = tempX/4/2 + 128;			//Output stored by dividing it with a constant
				OUTPUT33_Y[i][j] = tempY/4/2 + 128;			//Output stored by dividing it with a constant		
			}   			     
        }
    }
// 5*5 Filtering of the image in horizontal and vertical diection.
    for (i=0; i<H; i++) 
	{
        for (j=0; j<W; j++) 
		{
            if (i==0 || i==1 || i==H-1 || i== H-2 || j==0 || j==1 || j==W-1 || j==W-2)	//condition to fit the image as line 1 is not considered
			{
            	OUTPUT55_X[i][j] = 128;			//set values to 128
				OUTPUT55_Y[i][j] = 128;			//set values to 128
            	
			}
			else 
			{
				tempY=0;		//initialize temporary variable of Y to 0
				tempX=0;		//initialize temporary variable of Y to 0
				// The loop to rotate the filter by 3*3	
				for (k=0; k<5; k++)
				{										
					for (l=0; l<5; l++)
					{						
						tempX1 = FILTER55_X[k][l]*img[i-2+k][j-2+l];//Apply filter
						tempX += tempX1;						//Add to the existing value
						tempY1 = FILTER55_Y[k][l]*img[i-2+k][j-2+l]; //Apply filter
						tempY += tempY1;						//Add to the existing value
						
					}
				}	
				OUTPUT55_X[i][j] = tempX/30/2 + 128; 		//Output stored by dividing it with a constant
				OUTPUT55_Y[i][j] = tempY/30/2 + 128;		//Output stored by dividing it with a constant
            	
						
			}       
        }
    }
	
	// Store all the output images in raw format
	IMG33_X = fopen("IMG_X33u.raw","wb");
    fwrite(OUTPUT33_X, 1, DATASIZE, IMG33_X);
    fclose(IMG33_X);
    IMG33_Y = fopen("IMG_Y33u.raw","wb");
    fwrite(OUTPUT33_Y, 1, DATASIZE, IMG33_Y);
    fclose(IMG33_Y);
	IMG55_X = fopen("IMG_X55u.raw","wb");
    fwrite(OUTPUT55_X, 1, DATASIZE, IMG55_X);
    fclose(IMG55_X);
    IMG55_Y = fopen("IMG_Y55u.raw","wb");
    fwrite(OUTPUT55_Y, 1, DATASIZE, IMG55_Y);
    fclose(IMG55_Y);

    
   
    return 0;
}