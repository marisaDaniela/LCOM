#ifndef __GRAPHICS_H
#define __GRAPHICS_H

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

// user-friendly color names

unsigned long rgb(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

#define BLACK rgb(0,0,0)
#define BLUE rgb(0,0,255)
#define CYAN rgb(0,255,255)
#define DARK_GRAY rgb(169,169,169)
#define GRAY rgb(128,128,128)
#define GREEN rgb(0,255,0)
#define LIGHT_GRAY rgb(211,211,211)
#define NAVY rgb(0,0,128)
#define ORANGE rgb(255,192,0)
#define RED rgb(255,0,0)
#define SILVER rgb(192,192,192)
#define TEAL rgb(0,128,128)
#define WHITE rgb(255,255,255)
#define YELLOW rgb(255,255,0)
/**
 * @brief Initializes the video module in graphics mode
 *
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen,
 *  and the number of colors
 *
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

 /** @} end of video_gr */

int drawSquare(unsigned short x, unsigned short y, unsigned short size, unsigned short color);

void drawLine(unsigned xi, unsigned yi, unsigned xf, unsigned yf, char color);


#endif /* __GRAPHICS_H */
