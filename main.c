#include <stdio.h>
#include <complex.h>
#define MAX_HEIGHT 2048
#define MAX_WIDTH 2048
#include "pgmimages.h"
#define MAX_PIXELS_PER_LINE 25

int resim_array[2048][MAX_WIDTH];

void write_pgm_file_from_array(char* pgmOutFileName, int imageArray[][MAX_WIDTH], int height, int width, int maxPixel )
{
    int row = 0 ;
    int col = 0 ;
    FILE* fp = fopen ( pgmOutFileName, "w" ) ;
    if ( fp )
    {
        fprintf ( fp, "P2\n" ) ;
        fprintf ( fp, "%u %u\n", width, height ) ;
        fprintf ( fp, "%u\n", maxPixel ) ;

         for ( row = 0 ; row < height ; row ++ )
        {
            for ( col = 0 ; col < width ; col ++ )
            {
                fprintf ( fp, "%u", imageArray[row][col] ) ;
               
                if ( MAX_PIXELS_PER_LINE > 1 )
                {
                    fprintf ( fp, " " ) ;
                }
                if ( ( col % MAX_PIXELS_PER_LINE ) == 0 )
                {
                    fprintf ( fp, "\n" ) ;
                }
            }
           
            if ( col % MAX_PIXELS_PER_LINE )
            {
                fprintf ( fp, "\n" ) ;
            }
        }
        fclose ( fp ) ;
    }
    return ;
}
	
void  array_converter(PGMFormattedImage* pgmFormattedImagePointer,int resim_array[2048][2048]){
	
	float* pixelValues = ( pgmFormattedImagePointer->pixelValues );
	
	for( int i = 0; i < *( pgmFormattedImagePointer->heightOfImage ); i ++ ){
    	float* rowOfPixelValues = ( float* )( ( char* )pixelValues + i* *( pgmFormattedImagePointer->widthOfImage ) * sizeof( float ) );
  		for( int j= 0; j < *( pgmFormattedImagePointer->widthOfImage ); j++ ){
   			resim_array[i][j]=*( rowOfPixelValues + j );
  		}
	}
}

int main(){
	
	for(int temp=1;temp<7;temp++){ //6 adet dosya cýktýsý 
		complex double z, c;
		int temp_a=0; // k  degeri 
		if(temp==1)
			temp_a=2;
		else if(temp==2)
		 	temp_a=5;
	    else if(temp==3)
		 	temp_a=10;	
		else if(temp==4)
			temp_a=25;
		else if(temp==5)
		 	temp_a=50;
		else if(temp==6)
		 	temp_a=75;
	 
	  	 	    
    	int x, y, i;
    
      	write_pgm_file_from_array("bos.pgm",resim_array, 2048, 2048, 255 ); //bos pgm olusturduk. bunu alýp üstüne yazacaðýz 
    
   		PGMFormattedImage* newPGMFormattedImage = ( PGMFormattedImage* )malloc( sizeof( PGMFormattedImage ) );
  		
  		readPGMFormattedImage( newPGMFormattedImage ); 
  
   		array_converter(newPGMFormattedImage,resim_array); 
   		
   		char buf[19];
   
   
	    for (y=0 ; y<2048 ; ++y) {
	        for (x=0 ; x<2048 ; ++x) {
	            c = 0.04 -0.8540*I;
	            z = (-1.5 + x*0.0014) + (-1.5 + y*0.0014)*I;  //goruntuyu scale etmek için  aralýk degerini piksel genisliðine bölün yaklaþýp uzaklasmayý burdan yapýyoruz. Yaklaþma faktörü 0,0014.
	            i = 0;
	            while (cabs(z) < 4 && ++i < temp_a)
					z = z*z + c;
	            	resim_array[y][x]=i;
	        }
	    }    
	    snprintf(buf, 19, "./sonuc/deneme%d.pgm", temp); // dosya adina gore buf size verilecek sonuc dosyasý projede var olmalý.
	    printf("%s\n", buf); 
	    write_pgm_file_from_array(buf,resim_array, 2048, 2048, 255 ); //255 degeri degistirilirse renk skalasý daraltýlabilir.
			
	}
	
    return 0 ;
}
