#ifndef SOULFU_PAGE_H
#define SOULFU_PAGE_H

// <ZZ> This file contains functions related to pages of books...
#define PAGE_COL (25+2)                     // The number of columns in the page animation
#define PAGE_FRAME 32                       // The number of frames in the page animation

void page_setup(void);

#ifdef DEVTOOL
void page_edit_tool(void);
#endif

#endif
