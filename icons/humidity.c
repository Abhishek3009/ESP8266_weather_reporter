
/*******************************************************************************
* image
* filename: D:/projects/weather_station/weather images/humidity.xml
* name: humidity
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Diffuse Dither 128
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



static const uint8_t image_data_humidity[32] = {
    0x00, 0x00, 
    0x01, 0x00, 
    0x01, 0x80, 
    0x03, 0x80, 
    0x03, 0xc0, 
    0x07, 0xc0, 
    0x0f, 0xe0, 
    0x0f, 0xe0, 
    0x19, 0x70, 
    0x19, 0x78, 
    0x3e, 0xf8, 
    0x3d, 0x18, 
    0x1d, 0xb8, 
    0x1f, 0xf0, 
    0x0f, 0xe0, 
    0x03, 0x80
};
const tImage humidity = { image_data_humidity, 14, 16,
    8 };

