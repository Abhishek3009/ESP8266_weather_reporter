
/*******************************************************************************
* image
* filename: D:/projects/weather_station/weather images/windspeed.xml
* name: windspeed
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Threshold Dither 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
*/
#include <stdint.h>



static const uint8_t image_data_windspeed[42] = {
    0x00, 0x00, 0x00, 
    0x01, 0xe0, 0x00, 
    0x01, 0x20, 0x00, 
    0x00, 0x26, 0x00, 
    0x00, 0x6d, 0x00, 
    0x3f, 0x81, 0x00, 
    0x00, 0x01, 0x00, 
    0x7f, 0xff, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x0f, 0xfc, 0x00, 
    0x00, 0x04, 0x00, 
    0x00, 0x1c, 0x00, 
    0x00, 0x00, 0x00
};
const tImage windspeed = { image_data_windspeed, 17, 14,
    8 };

