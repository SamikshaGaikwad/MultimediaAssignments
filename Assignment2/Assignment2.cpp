#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define W  750 //Width of the image
#define H  500 //Height of the image
unsigned char ip_img[W * H ]; //created an array of the size of the image
unsigned char* input_img = (unsigned char*)&ip_img[0]; //array image saved
unsigned char reverse_img[W*H]; // Array to save image with reverse pixel values
unsigned char add_twenty_img[W*H] ;//Array to save image with adding 20 to pixels
unsigned char add_onetwoeight_img[W*H]; //Array to save image by adding 128 to the pixels
//main function 
int main()
{
    FILE* raw_file = fopen("unesco750-1.raw", "r"); //Open raw image as a file pointer
    fread(input_img, sizeof(input_img[0]), W * H , raw_file); //Read the file
    fclose(raw_file);   //close the file
    //Check if the file is converted into an array
    /*FILE* array_file = fopen("unesco_array.txt", "w");
	
    for (int i = 0; i < (W * H - 1); i++)
	{
		fprintf(array_file, "%3d, ", (int)*input_img++);
		fprintf(array_file, "%3d, ", (int)*input_img++);
		fprintf(array_file, "%3d, ", (int)*input_img++);
	}
    fprintf(array_file, "%3d, ", (int)*input_img++);
	fprintf(array_file, "%3d, ", (int)*input_img++);
	fprintf(array_file, "%3d };", (int)*input_img++);
	
	fclose(array_file);
    */
    printf("Image converted to 2D array\n");

    //FILE* raw_array_file = fopen("unescoArray.raw", "wb");
	
	//fwrite(ip_img, sizeof(ip_img[0]), W * H , array_file);

	//fclose(array_file);

    int n = 9; //Initialize the count
    int i, j, m; //Assign counters
    int temp[(W*H)+8] = {0}; //create a temporary array
	int reverse, addtwenty,addonetwoeight; // variables to store new values

    for(i = 0; i < ((W*H)+8); i++)
    {
        if (i > 3 && i < (W*H)+3)
        {
			temp[i] = input_img[i-4];
		}	
    }
 //------------------------------Reverse Pixels-----------------------------------------   
	for(i = 0; i < (W*H); i++) //loop from o till the number of pixels
	{
	
        reverse= 0;
		for(j = i, m = 0; m < n; j++, m++)  //loop till the counter
        {

            reverse=255-temp[j];        //reverse pixels

        }

		reverse_img[i] = reverse;
		
	}
	/*FILE* array_file = fopen("unesco_array.txt", "w");
	
    for (int i = 0; i < (W * H ); i++)
	{
		fprintf(array_file, "%3d, ", (int)*reverse++);
		fprintf(array_file, "%3d, ", (int)*reverse++);
		fprintf(array_file, "%3d, ", (int)*reverse++);
	}
    fprintf(array_file, "%3d, ", (int)*reverse+);
	fprintf(array_file, "%3d, ", (int)*reverse++);
	fprintf(array_file, "%3d };", (int)*reverse++);
	
	fclose(array_file);
    */
    printf("\nImage Reversed\n");
	
    FILE* rev_img = fopen("reverse.raw","wb"); //Save the pixels in raw format
    fwrite(reverse_img, 1, W*H , rev_img);
    fclose(rev_img);


//------------- ADD 20------------------------------------------------
    for(i = 0; i < W*H; i++)    //loop from o till the number of pixels
	{
	    
        
        addtwenty= 0;
		for(j = i, m = 0; m < n; j++, m++)  //loop till the counter
        {
  
            if(temp[j]<235)     // if addition value goes beyond 255 assign it to 0
                addtwenty=20+temp[j];
            else
                addtwenty=0;
            
        }
    
		
		add_twenty_img[i] = addtwenty;
	
	}
    /*FILE* array_file = fopen("unesco_array.txt", "w");
	
    for (int i = 0; i < (W * H - 1); i++)
	{
		fprintf(array_file, "%3d, ", (int)*addtwenty++);
		fprintf(array_file, "%3d, ", (int)*addtwenty++);
		fprintf(array_file, "%3d, ", (int)*addtwenty++);
	}
    fprintf(array_file, "%3d, ", (int)*addtwenty++);
	fprintf(array_file, "%3d, ", (int)*addtwenty++);
	fprintf(array_file, "%3d };", (int)*addtwent++);
	
	fclose(array_file);
    */
    printf("20 added to pixels");
    FILE* add_twenty= fopen("addtwenty.raw","wb");
    fwrite(add_twenty_img, 1, W*H, add_twenty);
    fclose(add_twenty);


//------------- ADD 128------------------------------------------------
    for(i = 0; i < W*H; i++)     //loop from o till the number of pixels
	{
        
        addonetwoeight= 0;
		for(j = i, m = 0; m < n; j++, m++)  //loop till the counter
        {
            if(temp[j]<128)      // if addition value goes beyond 255 assign it to 0
                addonetwoeight=128+temp[j];
            else
                addonetwoeight=0;
         
        }

		add_onetwoeight_img[i] = addonetwoeight;
	
	}
    /*FILE* array_file = fopen("unesco_array.txt", "w");
	
    for (int i = 0; i < (W * H - 1); i++)
	{
		fprintf(array_file, "%3d, ", (int)*addonetwoeight++);
		fprintf(array_file, "%3d, ", (int)*addonetwoeight++);
		fprintf(array_file, "%3d, ", (int)*addonetwoeight++);
	}
    fprintf(array_file, "%3d, ", (int)*addonetwoeight++);
	fprintf(array_file, "%3d, ", (int)*addonetwoeight++);
	fprintf(array_file, "%3d };", (int)*addonetwoeight++);
	
	fclose(array_file);
    */
    printf("\n128 added to pixels\n");
    FILE* add_onetwoeight = fopen("addonetwoeight.raw","wb"); // Save the changed pixels in raw format
    fwrite(add_onetwoeight_img, 1, W*H, add_onetwoeight);
    fclose(add_onetwoeight);



    return 0;

}