
/*******************************************************************************
* image
* filename: D:/projects/weather_station/icons/cloudy.xml
* name: cloudy
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



static const uint8_t image_data_cloudy[200] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xf8, 0x00, 
    0x00, 0x00, 0x01, 0xff, 0x00, 
    0x00, 0x00, 0x03, 0xff, 0xc0, 
    0x00, 0x00, 0x03, 0xff, 0xe0, 
    0x00, 0x0f, 0xc3, 0xff, 0xf0, 
    0x00, 0x3f, 0xf3, 0xff, 0xf8, 
    0x00, 0xff, 0xfc, 0x01, 0xfc, 
    0x01, 0xff, 0xfe, 0xfc, 0xfc, 
    0x01, 0xff, 0xff, 0xff, 0x3c, 
    0x03, 0xff, 0xff, 0xff, 0x98, 
    0x03, 0xff, 0xff, 0xff, 0xd0, 
    0x07, 0xff, 0xff, 0xff, 0xc0, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x1f, 0xff, 0xff, 0xff, 0xf8, 
    0x3f, 0xff, 0xff, 0xff, 0xfc, 
    0x3f, 0xff, 0xff, 0xff, 0xfc, 
    0x7f, 0xff, 0xff, 0xff, 0xfe, 
    0x7f, 0xff, 0xff, 0xff, 0xfe, 
    0x7f, 0x07, 0xff, 0xff, 0xfe, 
    0x7e, 0x78, 0x7f, 0xff, 0xfe, 
    0x7d, 0xff, 0x3f, 0xff, 0xfe, 
    0x79, 0xff, 0xdf, 0xff, 0xfe, 
    0x3b, 0xff, 0xe7, 0xff, 0xfc, 
    0x33, 0xff, 0xf3, 0xff, 0xfc, 
    0x0f, 0xff, 0xf9, 0xff, 0xf8, 
    0x0f, 0xff, 0xfd, 0xff, 0xe0, 
    0x0f, 0xff, 0xfc, 0x00, 0x00, 
    0x0f, 0xff, 0xfc, 0x00, 0x00, 
    0x0f, 0xff, 0xfc, 0x00, 0x00, 
    0x07, 0xff, 0xf8, 0x00, 0x00, 
    0x01, 0xff, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00
};
const tImage cloudy = { image_data_cloudy, 40, 40,
    8 };

