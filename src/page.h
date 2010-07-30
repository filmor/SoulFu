#ifndef SOULFU_PAGE_H
#define SOULFU_PAGE_H

// <ZZ> This file contains functions related to pages of books...
// The number of columns in the page animation
#define PAGE_COL (25+2)
// The number of frames in the page animation
#define PAGE_FRAME 32

extern float page_xy[PAGE_FRAME][PAGE_COL*2];

void page_setup(void);

#ifdef DEVTOOL
void page_edit_tool(void);
#endif

#endif
