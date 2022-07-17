# Filter
Filter is a program that is created for CS50 Problem Set 4. The program is used to filter the input image and it is created by using C. The users have to run the C file with 3 extra command line arguments, in the format of "./filter -x images/yard.bmp out.bmp", where "-x" can be "-g", "-r", "-b" or "-e" that stands for grayscale, reflect, blur, or edges. The original image to be filtered is as shown below. 

![image](https://user-images.githubusercontent.com/95561298/179399686-3f151d31-855b-410d-9f7b-d76d28a70d66.png)

# Information about Filter 
Filter can be used to filter image by 4 different ways:
1) **Grayscale**: The function grayscale should take an image and turn it into a black-and-white version of the same image. Grayscale is represented by "-g". The grayscaled image is as shown below. 
2) **Reflect**: The reflect function should take an image and reflect it horizontally. Reflect is represented by "-r". The reflected image is as shown below. 
3) **Blur**: The blur function should take an image and turn it into a box-blurred version of the same image. Blur is represented by "-b". The blurred image is as shown below.
4) **Edges**: The edges function should take an image and highlight the edges between objects, according to the Sobel operator. Edges is represented by "-e". The edges of the image are detected by using Sobel Edge Detection algorithm and the filtered image is as shown below. 



# How to Run the Project
1) Download all the files.
2) Open the "filter.c" file and run the project.
3) Run the command `./filter -g images/yard.bmp out.bmp` for grayscale, `./filter -r images/yard.bmp out.bmp` for reflect, `./filter -b images/yard.bmp out.bmp` for blur, `./filter -e images/yard.bmp out.bmp` for edges. 

# Some Filtered Images from the Program
**Grayscale**

![image](https://user-images.githubusercontent.com/95561298/179400065-0775ea0b-6506-4191-bdc3-d39047aca9df.png)

**Reflect**

![image](https://user-images.githubusercontent.com/95561298/179400077-00b39fe1-275a-40e1-8dfb-517de5adf266.png)

**Blur**

![image](https://user-images.githubusercontent.com/95561298/179400083-f7f1d4ec-ed9f-45ac-a5cb-cb58b8536a79.png)

**Edges**

![image](https://user-images.githubusercontent.com/95561298/179400094-affb9d61-49cd-4220-b746-a2b66fe14608.png)

# Reference 
https://cs50.harvard.edu/x/2022/psets/4/filter/more/
