//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// StyleAsCode exporter v2.0 - Style data exported as a values array            //
//                                                                              //
// USAGE: On init call: GuiLoadStyleGenesis();                                   //
//                                                                              //
// more info and bugs-report:  github.com/raysan5/raygui                        //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2025 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define GENESIS_STYLE_PROPS_COUNT  23

// Custom style name: Genesis
static const GuiStyleProp genesisStyleProps[GENESIS_STYLE_PROPS_COUNT] = {
    { 0, 0, (int)0x667384ff },    // DEFAULT_BORDER_COLOR_NORMAL 
    { 0, 1, (int)0x181b1eff },    // DEFAULT_BASE_COLOR_NORMAL 
    { 0, 2, (int)0xc2c8d0ff },    // DEFAULT_TEXT_COLOR_NORMAL 
    { 0, 3, (int)0xd3dbdfff },    // DEFAULT_BORDER_COLOR_FOCUSED 
    { 0, 4, (int)0xa7afb0ff },    // DEFAULT_BASE_COLOR_FOCUSED 
    { 0, 5, (int)0x020202ff },    // DEFAULT_TEXT_COLOR_FOCUSED 
    { 0, 6, (int)0x181b1eff },    // DEFAULT_BORDER_COLOR_PRESSED 
    { 0, 7, (int)0xac3c3cff },    // DEFAULT_BASE_COLOR_PRESSED 
    { 0, 8, (int)0xdededeff },    // DEFAULT_TEXT_COLOR_PRESSED 
    { 0, 9, (int)0x3e4550ff },    // DEFAULT_BORDER_COLOR_DISABLED 
    { 0, 10, (int)0x2e353dff },    // DEFAULT_BASE_COLOR_DISABLED 
    { 0, 11, (int)0x484f57ff },    // DEFAULT_TEXT_COLOR_DISABLED 
    { 0, 16, (int)0x00000010 },    // DEFAULT_TEXT_SIZE 
    { 0, 17, (int)0x00000000 },    // DEFAULT_TEXT_SPACING 
    { 0, 18, (int)0x96a3b4ff },    // DEFAULT_LINE_COLOR 
    { 0, 19, (int)0x292c33ff },    // DEFAULT_BACKGROUND_COLOR 
    { 0, 20, (int)0x00000018 },    // DEFAULT_TEXT_LINE_SPACING 
    { 1, 5, (int)0x97a9aeff },    // LABEL_TEXT_COLOR_FOCUSED 
    { 4, 5, (int)0xa69a9aff },    // SLIDER_TEXT_COLOR_FOCUSED 
    { 4, 6, (int)0xc3ccd5ff },    // SLIDER_BORDER_COLOR_PRESSED 
    { 6, 6, (int)0xa7aeb5ff },    // CHECKBOX_BORDER_COLOR_PRESSED 
    { 9, 5, (int)0xa9a5a5ff },    // TEXTBOX_TEXT_COLOR_FOCUSED 
    { 10, 5, (int)0xc9c7c7ff },    // VALUEBOX_TEXT_COLOR_FOCUSED 
};

// WARNING: This style uses a custom font: "PixelOperator.ttf" (size: 16, spacing: 0)

#define GENESIS_STYLE_FONT_ATLAS_COMP_SIZE 2138

// Font atlas image pixels data: DEFLATE compressed
static unsigned char genesisFontData[GENESIS_STYLE_FONT_ATLAS_COMP_SIZE] = { 0xed,
    0xdd, 0xdb, 0x92, 0xa5, 0xba, 0x0d, 0x00, 0x50, 0xff, 0xff, 0x4f, 0x2b, 0x0f, 0xa9, 0x54, 0x32, 0x95, 0xd3, 0x80, 0x64,
    0xd9, 0x98, 0x9e, 0x35, 0xeb, 0xad, 0x77, 0x4f, 0xc3, 0x36, 0x96, 0x6f, 0x80, 0x1c, 0x03, 0x00, 0x00, 0x00, 0xf8, 0xeb,
    0xc5, 0x3f, 0xfe, 0x24, 0x7e, 0xfc, 0xcd, 0x78, 0xfc, 0x77, 0xae, 0x7f, 0xfe, 0x9f, 0x4f, 0xe3, 0xe2, 0x58, 0xcf, 0xce,
    0x35, 0x7b, 0xdc, 0x48, 0x94, 0xc4, 0x3f, 0x9f, 0x5f, 0x3c, 0xfe, 0xbb, 0x3f, 0x7d, 0xbf, 0xfc, 0xef, 0x5f, 0xfd, 0xa5,
    0xeb, 0xb3, 0x8f, 0x54, 0xb9, 0xe7, 0xff, 0x4f, 0xee, 0x2a, 0xc6, 0x92, 0xb2, 0xbf, 0x3f, 0xbb, 0xfc, 0xb9, 0x77, 0xfe,
    0x9f, 0xb8, 0xf8, 0x3e, 0x95, 0xab, 0xf4, 0x24, 0xb6, 0x4e, 0x88, 0xff, 0x78, 0x14, 0x89, 0xd1, 0x5a, 0x73, 0xfe, 0x7b,
    0xd4, 0x68, 0x6c, 0xa9, 0xaa, 0x25, 0x79, 0x15, 0xe9, 0xf9, 0xf2, 0xb8, 0xaa, 0xfd, 0xf9, 0x16, 0x30, 0x5a, 0xbe, 0xcb,
    0x7c, 0x6d, 0x8c, 0xe9, 0xdf, 0x7e, 0x56, 0x93, 0x7a, 0xbe, 0xd5, 0xcc, 0x27, 0xa3, 0xe5, 0x2a, 0xbd, 0x11, 0xff, 0x51,
    0x6e, 0xa9, 0x22, 0x19, 0xd1, 0x1d, 0x25, 0x58, 0x69, 0x87, 0xc7, 0xc6, 0xf8, 0x8f, 0xd6, 0xb1, 0x4b, 0xb4, 0xd5, 0xb9,
    0x37, 0xe2, 0xff, 0xba, 0xd7, 0x1e, 0x2d, 0xf5, 0x26, 0x6e, 0xca, 0xa8, 0x37, 0x96, 0xd7, 0x8e, 0x53, 0x57, 0xc7, 0xff,
    0xf5, 0x6f, 0x66, 0xfb, 0xdb, 0x48, 0xf6, 0xdd, 0x1d, 0xe5, 0x54, 0xeb, 0xff, 0xfb, 0xcb, 0x31, 0x7e, 0xec, 0x9b, 0xab,
    0xe3, 0x90, 0x4c, 0x09, 0x47, 0x72, 0x76, 0x35, 0xdb, 0xc3, 0xbe, 0xd9, 0xff, 0x3f, 0x1b, 0x0b, 0x8a, 0xff, 0xb5, 0xf1,
    0x5f, 0xf9, 0x26, 0xf1, 0xf0, 0x0c, 0x2a, 0x7d, 0xe2, 0x38, 0x20, 0xfe, 0xb3, 0xed, 0xd0, 0x75, 0x59, 0x75, 0x8d, 0xe5,
    0xb3, 0xeb, 0x12, 0xcf, 0x66, 0xd8, 0xfb, 0x6a, 0x61, 0x7e, 0x6c, 0x94, 0x8f, 0xff, 0x7c, 0xeb, 0x79, 0xf7, 0xd7, 0xb2,
    0xa5, 0xfa, 0xf3, 0xcc, 0x6e, 0xbe, 0xc4, 0xf7, 0xc5, 0x7f, 0x14, 0xfa, 0x94, 0xf7, 0xe3, 0xb9, 0x27, 0xfe, 0xa3, 0xb0,
    0x72, 0x31, 0xda, 0x56, 0xf9, 0x6a, 0xeb, 0x12, 0x7d, 0x6b, 0x06, 0xef, 0x5f, 0x81, 0xfb, 0xf8, 0xbf, 0x9b, 0x0f, 0xbe,
    0xdf, 0xff, 0xc7, 0x11, 0xfd, 0x7f, 0x94, 0xd7, 0x86, 0x47, 0xa1, 0xf5, 0xfd, 0x5a, 0xfc, 0x47, 0x21, 0x66, 0xa2, 0x65,
    0x5e, 0x3e, 0x96, 0xac, 0xe5, 0xf5, 0xae, 0x19, 0xee, 0xb9, 0x5a, 0x77, 0xbd, 0x68, 0xd7, 0xac, 0xe6, 0x77, 0xc5, 0xff,
    0x68, 0xe8, 0xff, 0x9f, 0x8d, 0x01, 0x66, 0xbf, 0x47, 0x7c, 0xac, 0xf7, 0xef, 0x8c, 0xff, 0x5d, 0x2b, 0xf6, 0xeb, 0x6b,
    0x63, 0x1c, 0x71, 0x65, 0xac, 0xff, 0x77, 0x8e, 0xff, 0xeb, 0x6b, 0x00, 0xb9, 0x79, 0x4c, 0x1c, 0x1a, 0xfd, 0x95, 0x39,
    0x73, 0xd7, 0x1d, 0xfb, 0xde, 0xa7, 0x09, 0xa2, 0xf0, 0xac, 0x46, 0xcf, 0x2a, 0xce, 0xea, 0x6b, 0x90, 0xef, 0xff, 0x77,
    0xdd, 0xff, 0xbf, 0x1f, 0x73, 0x9f, 0xd1, 0xff, 0x8f, 0xdb, 0xde, 0xfd, 0x94, 0xf3, 0x01, 0xf6, 0xb6, 0x00, 0x21, 0xfa,
    0xc1, 0x73, 0xc4, 0x80, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x9f, 0xcf,
    0xef, 0xcf, 0x63, 0x90, 0xcf, 0x84, 0xbd, 0x3e, 0x03, 0xfb, 0x4c, 0x4e, 0xe0, 0x6a, 0x09, 0x75, 0xfd, 0xc5, 0xeb, 0xdc,
    0xf1, 0x99, 0x4c, 0x0b, 0xcf, 0x6b, 0x46, 0xa4, 0x77, 0x3f, 0xe8, 0xcc, 0x28, 0x50, 0xc9, 0x69, 0x30, 0x92, 0x75, 0xa2,
    0x37, 0x97, 0x52, 0xee, 0xec, 0xf7, 0xd4, 0xf8, 0x2f, 0xc4, 0xff, 0xfb, 0x9f, 0x8c, 0x42, 0xfe, 0x9e, 0x9d, 0xf1, 0x9f,
    0xad, 0x7b, 0xb5, 0xfc, 0xb8, 0x73, 0x7d, 0xc9, 0xee, 0x8c, 0x62, 0xd1, 0x78, 0x0d, 0xf7, 0xf5, 0xab, 0x7f, 0xe6, 0xd0,
    0xd9, 0x51, 0xaf, 0x67, 0xe2, 0x3f, 0x9b, 0xfb, 0x34, 0x2e, 0x5a, 0xe1, 0x73, 0xe2, 0x7f, 0x6c, 0x89, 0xff, 0xf8, 0x48,
    0xfc, 0x77, 0x67, 0x92, 0xe9, 0xca, 0x42, 0x5e, 0xc9, 0x7c, 0x93, 0xbf, 0x86, 0xf5, 0x0c, 0xbf, 0xd5, 0x1a, 0xf7, 0x9d,
    0xf8, 0xaf, 0xd4, 0xad, 0xeb, 0x3c, 0xab, 0xe2, 0xff, 0xbe, 0x6c, 0x2b, 0xbd, 0xc9, 0xfc, 0xcf, 0x7b, 0x22, 0x7f, 0x4f,
    0x1e, 0xdd, 0xbb, 0x7d, 0xb4, 0xd6, 0xd6, 0x95, 0xd9, 0xbe, 0xf2, 0x2b, 0xf1, 0x1f, 0xc5, 0xbf, 0x12, 0x37, 0x2d, 0x4a,
    0x6f, 0x06, 0xf6, 0x9e, 0xac, 0x6d, 0x7b, 0xe3, 0xbf, 0x7b, 0xdf, 0x9f, 0x33, 0xe2, 0xff, 0xfd, 0x3c, 0xba, 0xab, 0xe6,
    0x70, 0xbd, 0x7d, 0xe5, 0xef, 0xee, 0xff, 0xef, 0x5b, 0xc9, 0x1d, 0xf5, 0x63, 0xa6, 0xa7, 0x7f, 0xb3, 0xff, 0x7f, 0xef,
    0xe7, 0xef, 0xc6, 0x7f, 0x57, 0x6d, 0x8f, 0x8d, 0x23, 0x93, 0x6a, 0x5f, 0xb9, 0x73, 0x95, 0x6c, 0xf7, 0xfc, 0x7f, 0xd5,
    0x37, 0x1b, 0xe9, 0xd1, 0x44, 0x1c, 0x1b, 0xff, 0x33, 0xab, 0x90, 0xeb, 0xc6, 0x0b, 0xef, 0x8c, 0xff, 0x6b, 0xfb, 0xdb,
    0x56, 0x76, 0x05, 0x3c, 0xad, 0xff, 0xdf, 0x75, 0x97, 0x6c, 0x6c, 0x8e, 0xc9, 0xbd, 0xc7, 0xea, 0xdc, 0xa5, 0x2e, 0x9f,
    0xbf, 0x3f, 0x9a, 0x47, 0x78, 0x5f, 0x8f, 0xff, 0xfa, 0x2a, 0xff, 0x68, 0x5a, 0x95, 0x7c, 0x6f, 0xfc, 0xbf, 0x7b, 0xa7,
    0x93, 0xca, 0x51, 0x7a, 0xda, 0xdf, 0x67, 0x77, 0x85, 0x7b, 0x7b, 0x81, 0x9f, 0xef, 0x36, 0x44, 0x53, 0xcf, 0xd1, 0x95,
    0xbf, 0xff, 0xcf, 0x73, 0xcb, 0xef, 0x78, 0x96, 0xbf, 0x13, 0x1f, 0xc9, 0xfd, 0xf4, 0xdf, 0x88, 0xff, 0xca, 0x91, 0x2b,
    0xff, 0x2b, 0x7b, 0x0d, 0x3b, 0xe3, 0xff, 0xbd, 0x16, 0x40, 0xde, 0x4d, 0x38, 0x71, 0x14, 0x03, 0xfc, 0x9e, 0x16, 0xc0,
    0x0e, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xee, 0x37, 0xb1, 0x7f, 0xce,
    0xcd, 0x55, 0xc9, 0x1a, 0x9f, 0x7f, 0x4f, 0x7a, 0x67, 0xc6, 0xfc, 0x71, 0x93, 0x85, 0xec, 0xfa, 0xb7, 0xfe, 0xfc, 0xa4,
    0x23, 0x1f, 0x6f, 0x34, 0xbe, 0xb5, 0x9e, 0xc9, 0xe5, 0x1d, 0x85, 0x6c, 0x03, 0x57, 0x6f, 0xc6, 0xe6, 0xae, 0x41, 0xee,
    0x18, 0xd1, 0x9e, 0xcf, 0x2c, 0xd2, 0xd9, 0x63, 0xfe, 0xf7, 0x9c, 0x9f, 0x67, 0xfa, 0x8d, 0xf2, 0x9b, 0xc6, 0x77, 0xb9,
    0xcc, 0xf2, 0xf9, 0x11, 0x2a, 0x39, 0xf3, 0xf2, 0x79, 0x36, 0x4f, 0xcf, 0x98, 0x3f, 0x9f, 0x79, 0x27, 0x6e, 0xea, 0xe4,
    0xf3, 0x5a, 0xfa, 0x24, 0x73, 0x44, 0x4f, 0x06, 0xa1, 0xda, 0x37, 0x8e, 0xe9, 0xda, 0x5a, 0xb9, 0xde, 0x99, 0x23, 0xc4,
    0xf4, 0xfb, 0xfc, 0x95, 0xfa, 0x1e, 0x93, 0xd7, 0xbd, 0xfe, 0x8d, 0x67, 0xb2, 0x10, 0x44, 0xa9, 0xa7, 0xeb, 0x2c, 0xc1,
    0xeb, 0x4f, 0xf2, 0x19, 0x33, 0xe3, 0x61, 0x7c, 0x75, 0xff, 0x74, 0x24, 0xdb, 0x9b, 0x4a, 0xbe, 0xba, 0x99, 0x5d, 0x33,
    0xe6, 0xc6, 0x88, 0xe3, 0x22, 0xbb, 0x52, 0x3e, 0xfa, 0x7f, 0xee, 0x6f, 0x62, 0x32, 0xfe, 0xa3, 0x98, 0x59, 0xa8, 0x1e,
    0x23, 0xd9, 0xf8, 0x9f, 0xbf, 0x0a, 0xbb, 0xe2, 0xbf, 0x92, 0xf5, 0xe0, 0xfd, 0x8c, 0xd9, 0xb5, 0x9e, 0x70, 0x6f, 0xfc,
    0xc7, 0x83, 0xf6, 0x6b, 0xa4, 0xe7, 0x2f, 0xa3, 0x90, 0xe1, 0xfc, 0xf9, 0xec, 0x22, 0x5a, 0xfb, 0xff, 0x71, 0x59, 0x26,
    0xf1, 0xc2, 0xf8, 0xbf, 0xb6, 0xdf, 0x5b, 0x2e, 0xfe, 0x67, 0x5a, 0xa7, 0xfd, 0xfd, 0x7f, 0xad, 0x5f, 0x3b, 0xb9, 0xff,
    0x7f, 0x27, 0x63, 0x76, 0x14, 0xe6, 0xd9, 0x95, 0xe3, 0xc6, 0xe4, 0xc8, 0xe0, 0xd9, 0x5c, 0x30, 0x1a, 0xe6, 0xab, 0x1d,
    0xf1, 0xdf, 0x3f, 0xc2, 0xae, 0xcc, 0xad, 0x6a, 0xfd, 0x7f, 0xb4, 0xce, 0xff, 0x23, 0xdd, 0xce, 0xcf, 0xc5, 0x7f, 0xe7,
    0x6e, 0x4b, 0x2b, 0x32, 0xe6, 0xe6, 0x77, 0x76, 0x7c, 0xab, 0xff, 0x1f, 0xa5, 0xfe, 0xbf, 0xd6, 0x7b, 0xcd, 0xd4, 0xca,
    0xd8, 0x90, 0xeb, 0x2e, 0x37, 0xfe, 0x5f, 0x3d, 0xca, 0xce, 0xcf, 0x28, 0x63, 0x53, 0xfb, 0xd4, 0x3d, 0xf7, 0xab, 0x45,
    0x4b, 0xa4, 0xc7, 0xd7, 0x3b, 0x33, 0xe6, 0x56, 0xd6, 0x9e, 0xcf, 0x8f, 0xff, 0xce, 0x3d, 0x4c, 0x2a, 0x77, 0x17, 0xa2,
    0xa1, 0x6f, 0x5e, 0xdd, 0xff, 0xcf, 0xce, 0xff, 0x2b, 0xb9, 0xf4, 0xf7, 0xac, 0xff, 0x8d, 0xa5, 0x6b, 0x3f, 0xd1, 0x7a,
    0x3f, 0x71, 0x1c, 0xd0, 0x7e, 0x77, 0x66, 0x89, 0x7f, 0x63, 0xfe, 0xdf, 0x95, 0x81, 0x7d, 0x94, 0xef, 0x09, 0xd5, 0xd7,
    0xff, 0x67, 0x6b, 0x60, 0x1c, 0xd3, 0xf7, 0x8f, 0xc7, 0x7b, 0xe8, 0xc4, 0x4b, 0xd1, 0x7f, 0x5a, 0xfc, 0x9f, 0xf2, 0x44,
    0x43, 0x47, 0xbb, 0x15, 0x2d, 0xad, 0x5b, 0x65, 0xdf, 0x96, 0xce, 0x71, 0xd4, 0xfc, 0xfc, 0x7f, 0xcd, 0xba, 0xfa, 0x1b,
    0xc7, 0x98, 0xb9, 0x23, 0x3b, 0x1f, 0xff, 0xb1, 0xbc, 0xe4, 0xe4, 0x23, 0xfe, 0x4e, 0x2b, 0x75, 0xde, 0xf1, 0xfe, 0xe6,
    0xda, 0x13, 0x1b, 0x9f, 0xb5, 0x13, 0xa1, 0xc4, 0xd1, 0xf3, 0x21, 0xd7, 0x03, 0xfe, 0xe6, 0xf9, 0xd0, 0xdf, 0xfa, 0x1c,
    0xbc, 0x92, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x7d, 0x3b, 0xa4, 0x92, 0x59,
    0x72, 0x34, 0xbf, 0x8b, 0x9e, 0xcf, 0xad, 0x5f, 0x3d, 0xbb, 0xbb, 0xf7, 0xa5, 0x6b, 0xf9, 0x79, 0x6b, 0xe5, 0x34, 0x97,
    0x8f, 0x28, 0x97, 0x53, 0xed, 0x7e, 0xff, 0x83, 0x38, 0xf2, 0x6a, 0xde, 0x65, 0x75, 0x8d, 0x42, 0x3e, 0xd5, 0xce, 0xeb,
    0x35, 0x4a, 0x65, 0xb7, 0xab, 0x96, 0x3d, 0x7f, 0x3b, 0x34, 0x36, 0xbc, 0x4f, 0x59, 0x8b, 0x85, 0x5a, 0x6e, 0xc3, 0xb9,
    0xdc, 0x61, 0xb1, 0xf8, 0x9b, 0xe5, 0xca, 0x6f, 0x7e, 0x3f, 0x89, 0xfb, 0x6c, 0xab, 0xf1, 0xb9, 0xab, 0x59, 0xcd, 0xf8,
    0xde, 0x7d, 0xbd, 0xea, 0xb5, 0xe5, 0x84, 0x5a, 0xb6, 0x7e, 0x67, 0x89, 0x37, 0xde, 0x6e, 0xad, 0x66, 0xc4, 0x8d, 0xcf,
    0xbf, 0x73, 0x1a, 0x1f, 0xcd, 0x05, 0x50, 0xcb, 0x13, 0xb9, 0xeb, 0x5b, 0x55, 0x8e, 0x14, 0xa5, 0x3d, 0x9b, 0xc6, 0xf6,
    0xec, 0x10, 0xf9, 0xec, 0xe7, 0xa3, 0x94, 0xef, 0xb3, 0xfb, 0x93, 0xca, 0x15, 0xa9, 0xc7, 0xff, 0x55, 0x39, 0x55, 0x3e,
    0x99, 0xed, 0xff, 0xc7, 0xf2, 0x7d, 0x18, 0x4e, 0xb9, 0x9a, 0x77, 0xfd, 0x7f, 0xb4, 0xed, 0x98, 0xb4, 0xf7, 0x93, 0x1d,
    0xe5, 0xda, 0x11, 0x0b, 0xbb, 0xf6, 0xfb, 0x8b, 0x74, 0xad, 0x18, 0xe9, 0x1c, 0x7b, 0xf5, 0xd9, 0xd7, 0xae, 0x4f, 0x56,
    0xc4, 0x7f, 0x5c, 0xcc, 0x93, 0xbb, 0x77, 0x1d, 0xeb, 0xbe, 0x9a, 0x4f, 0x5a, 0x86, 0x2f, 0xc6, 0xff, 0x8e, 0xf8, 0x99,
    0x9d, 0xff, 0x47, 0x79, 0x37, 0x9d, 0x33, 0x6b, 0x4c, 0x3c, 0xcc, 0xe8, 0xfc, 0xdb, 0xe2, 0x7f, 0x6f, 0x19, 0x77, 0xb7,
    0xe6, 0xd7, 0x23, 0xec, 0xf1, 0xd1, 0xf8, 0x9f, 0xdd, 0xef, 0x6d, 0x7e, 0xee, 0x7a, 0xbf, 0xfe, 0xdf, 0xb9, 0xb2, 0x71,
    0x46, 0xfc, 0x9f, 0x12, 0xe5, 0xb9, 0x32, 0x5f, 0x1b, 0xff, 0xef, 0xc7, 0x50, 0x57, 0x1f, 0xf6, 0xde, 0xb9, 0x47, 0xdb,
    0xfc, 0xff, 0x7e, 0x97, 0xe4, 0xdc, 0xdd, 0x9d, 0xbd, 0xab, 0x49, 0x3b, 0x4b, 0xbd, 0x73, 0xcf, 0xe1, 0xa7, 0x63, 0x87,
    0xee, 0xf9, 0xee, 0x19, 0xfd, 0x7f, 0x88, 0xff, 0x05, 0x6b, 0xe1, 0x27, 0xf4, 0x92, 0xab, 0xee, 0xe5, 0xe5, 0xb3, 0xd8,
    0xf7, 0x7e, 0x32, 0x5b, 0x52, 0xf9, 0xfb, 0xff, 0x5f, 0x1f, 0xff, 0x3f, 0xd9, 0xe1, 0xe7, 0x5b, 0xf1, 0x1f, 0xc5, 0x15,
    0xc5, 0x33, 0xe2, 0x3f, 0x36, 0x8e, 0x6a, 0x57, 0xdc, 0xcb, 0x3f, 0x79, 0xfc, 0xdf, 0xbf, 0x13, 0xd4, 0xd7, 0xe3, 0xff,
    0x0b, 0x63, 0xe8, 0x35, 0x4f, 0xa1, 0xbc, 0x17, 0xff, 0x73, 0x77, 0x86, 0x4f, 0x1e, 0xff, 0x9f, 0x1e, 0xff, 0xb3, 0x57,
    0x25, 0x36, 0xcd, 0xff, 0x9f, 0x8e, 0x34, 0x7e, 0x7f, 0xfc, 0x8f, 0xad, 0x7b, 0xf7, 0xd7, 0xe7, 0x9b, 0xe3, 0xd0, 0x67,
    0x61, 0xce, 0x79, 0x8a, 0xe3, 0xfd, 0x99, 0xcd, 0xfc, 0xae, 0xa8, 0xeb, 0xef, 0xff, 0x8f, 0x65, 0xfd, 0x7f, 0xef, 0x93,
    0x2d, 0xbb, 0xee, 0xff, 0xef, 0x7d, 0xa2, 0xa8, 0xfb, 0x0c, 0xc5, 0xff, 0x37, 0xda, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xe2, 0x73, 0xf2, 0x2b, 0x72, 0xeb, 0xf7, 0xe7, 0xc3, 0x38, 0x3d, 0xb7, 0xfe,
    0xdd, 0xfb, 0x33, 0xe3, 0xd8, 0xdc, 0xfa, 0xe3, 0x51, 0x8e, 0xa2, 0xef, 0xe5, 0xd6, 0xf7, 0xee, 0xc7, 0xd3, 0xb7, 0x64,
    0xd6, 0xe5, 0xd6, 0xef, 0x7b, 0x87, 0xfa, 0xf4, 0xdc, 0xfa, 0xe3, 0x26, 0x13, 0xd1, 0xc9, 0xb9, 0xf5, 0xeb, 0x6f, 0x51,
    0x9d, 0x9a, 0x5b, 0x9f, 0xb5, 0xef, 0x4e, 0x3e, 0x6d, 0xfb, 0xe3, 0xc5, 0x6b, 0xf6, 0x46, 0x36, 0x84, 0x93, 0x6b, 0x64,
    0x3e, 0x5b, 0xd3, 0x8a, 0x16, 0xa5, 0xf3, 0x7d, 0xcd, 0xb3, 0x73, 0xeb, 0x7f, 0x3d, 0xc6, 0xeb, 0xd9, 0x58, 0xa3, 0x9c,
    0xf3, 0xbe, 0xef, 0x5d, 0xed, 0x48, 0x8d, 0x1b, 0xd7, 0xe6, 0xd6, 0xba, 0x6e, 0x47, 0xcf, 0xdd, 0x29, 0xe1, 0xdb, 0xb9,
    0xb5, 0xc5, 0x7f, 0x4f, 0xab, 0x1b, 0x4d, 0x51, 0xf7, 0xf4, 0x93, 0x7d, 0x59, 0x83, 0xfa, 0xe2, 0x3f, 0xda, 0x3f, 0xdb,
    0x9b, 0x5b, 0xab, 0xba, 0x9e, 0x20, 0xfe, 0x7f, 0x57, 0x3b, 0x90, 0x99, 0xd1, 0x3e, 0x29, 0xf7, 0x37, 0x6b, 0xc0, 0xce,
    0xdc, 0x5a, 0x5f, 0x8f, 0xff, 0x4a, 0xff, 0x20, 0xfe, 0x7f, 0xcf, 0xf8, 0xbf, 0xaf, 0x2f, 0xaf, 0xaf, 0xff, 0x7f, 0x79,
    0x6f, 0xad, 0xdf, 0x19, 0xff, 0x67, 0xe4, 0xd6, 0x15, 0xff, 0xef, 0x8c, 0xff, 0x6b, 0xfb, 0x13, 0xac, 0x58, 0xcd, 0xed,
    0x9d, 0x4d, 0x88, 0xff, 0xd5, 0x75, 0xe7, 0xa4, 0x9d, 0x21, 0xc4, 0x78, 0x7d, 0xfe, 0x5f, 0xdb, 0x13, 0xb4, 0xda, 0x02,
    0xec, 0xcb, 0xd5, 0xfa, 0x46, 0x6e, 0x7d, 0xb9, 0x75, 0x67, 0xae, 0xd7, 0xf5, 0xe8, 0xef, 0x9b, 0xf7, 0x63, 0x4e, 0x1f,
    0xff, 0xf7, 0xde, 0xab, 0xf9, 0xff, 0x35, 0xa5, 0xd5, 0x2b, 0xde, 0xab, 0xc6, 0xff, 0x2b, 0xda, 0xd8, 0x37, 0x4b, 0x63,
    0xcd, 0xbd, 0xa3, 0xfe, 0x33, 0x8c, 0xa6, 0xd1, 0x1f, 0xef, 0xb4, 0x1a, 0xb0, 0x66, 0x9c, 0xf1, 0x7e, 0x4b, 0x08, 0x7c,
    0xed, 0x49, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x93, 0xfc, 0xfb, 0x9f, 0x72, 0x00, 0xf1, 0x0f, 0xfc, 0x75, 0xf1, 0xff, 0x2f };

// Font glyphs rectangles data (on atlas)
static const Rectangle genesisFontRecs[189] = {
    { 4, 4, 4 , 16 },
    { 16, 4, 1 , 9 },
    { 25, 4, 3 , 3 },
    { 36, 4, 6 , 9 },
    { 50, 4, 5 , 13 },
    { 63, 4, 7 , 9 },
    { 78, 4, 5 , 9 },
    { 91, 4, 1 , 3 },
    { 100, 4, 3 , 9 },
    { 111, 4, 3 , 9 },
    { 122, 4, 5 , 5 },
    { 135, 4, 5 , 5 },
    { 148, 4, 2 , 3 },
    { 158, 4, 4 , 1 },
    { 170, 4, 1 , 1 },
    { 179, 4, 3 , 9 },
    { 190, 4, 5 , 9 },
    { 203, 4, 3 , 9 },
    { 214, 4, 5 , 9 },
    { 227, 4, 5 , 9 },
    { 240, 4, 5 , 9 },
    { 253, 4, 5 , 9 },
    { 266, 4, 5 , 9 },
    { 279, 4, 5 , 9 },
    { 292, 4, 5 , 9 },
    { 305, 4, 5 , 9 },
    { 318, 4, 1 , 7 },
    { 327, 4, 2 , 9 },
    { 337, 4, 3 , 5 },
    { 348, 4, 4 , 3 },
    { 360, 4, 3 , 5 },
    { 371, 4, 5 , 9 },
    { 384, 4, 7 , 9 },
    { 399, 4, 5 , 9 },
    { 412, 4, 5 , 9 },
    { 425, 4, 5 , 9 },
    { 438, 4, 5 , 9 },
    { 451, 4, 5 , 9 },
    { 464, 4, 5 , 9 },
    { 477, 4, 5 , 9 },
    { 490, 4, 5 , 9 },
    { 4, 28, 1 , 9 },
    { 13, 28, 5 , 9 },
    { 26, 28, 5 , 9 },
    { 39, 28, 5 , 9 },
    { 52, 28, 7 , 9 },
    { 67, 28, 5 , 9 },
    { 80, 28, 5 , 9 },
    { 93, 28, 5 , 9 },
    { 106, 28, 5 , 9 },
    { 119, 28, 5 , 9 },
    { 132, 28, 5 , 9 },
    { 145, 28, 5 , 9 },
    { 158, 28, 5 , 9 },
    { 171, 28, 5 , 9 },
    { 184, 28, 7 , 9 },
    { 199, 28, 5 , 9 },
    { 212, 28, 5 , 9 },
    { 225, 28, 5 , 9 },
    { 238, 28, 3 , 9 },
    { 249, 28, 3 , 9 },
    { 260, 28, 3 , 9 },
    { 271, 28, 5 , 3 },
    { 284, 28, 5 , 1 },
    { 297, 28, 2 , 2 },
    { 307, 28, 5 , 7 },
    { 320, 28, 5 , 9 },
    { 333, 28, 5 , 7 },
    { 346, 28, 5 , 9 },
    { 359, 28, 5 , 7 },
    { 372, 28, 4 , 9 },
    { 384, 28, 5 , 9 },
    { 397, 28, 5 , 9 },
    { 410, 28, 1 , 9 },
    { 419, 28, 5 , 11 },
    { 432, 28, 5 , 9 },
    { 445, 28, 2 , 9 },
    { 455, 28, 7 , 7 },
    { 470, 28, 5 , 7 },
    { 483, 28, 5 , 7 },
    { 496, 28, 5 , 9 },
    { 4, 52, 5 , 9 },
    { 17, 52, 5 , 7 },
    { 30, 52, 5 , 7 },
    { 43, 52, 4 , 8 },
    { 55, 52, 5 , 7 },
    { 68, 52, 5 , 7 },
    { 81, 52, 7 , 7 },
    { 96, 52, 5 , 7 },
    { 109, 52, 5 , 9 },
    { 122, 52, 5 , 7 },
    { 135, 52, 4 , 9 },
    { 147, 52, 1 , 9 },
    { 156, 52, 4 , 9 },
    { 168, 52, 6 , 2 },
    { 182, 52, 1 , 9 },
    { 191, 52, 5 , 11 },
    { 204, 52, 6 , 9 },
    { 218, 52, 6 , 9 },
    { 232, 52, 5 , 9 },
    { 245, 52, 5 , 12 },
    { 258, 52, 0 , 0 },
    { 266, 52, 5 , 10 },
    { 279, 52, 7 , 9 },
    { 294, 52, 0 , 0 },
    { 302, 52, 6 , 5 },
    { 316, 52, 5 , 3 },
    { 329, 52, 7 , 9 },
    { 344, 52, 0 , 0 },
    { 352, 52, 4 , 4 },
    { 364, 52, 5 , 7 },
    { 377, 52, 0 , 0 },
    { 385, 52, 0 , 0 },
    { 393, 52, 5 , 12 },
    { 406, 52, 5 , 9 },
    { 419, 52, 7 , 9 },
    { 434, 52, 1 , 1 },
    { 443, 52, 5 , 10 },
    { 456, 52, 0 , 0 },
    { 464, 52, 0 , 0 },
    { 472, 52, 6 , 5 },
    { 486, 52, 9 , 9 },
    { 4, 76, 9 , 7 },
    { 21, 76, 5 , 11 },
    { 34, 76, 5 , 9 },
    { 47, 76, 5 , 12 },
    { 60, 76, 5 , 12 },
    { 73, 76, 5 , 12 },
    { 86, 76, 6 , 12 },
    { 100, 76, 5 , 11 },
    { 113, 76, 5 , 13 },
    { 126, 76, 9 , 9 },
    { 143, 76, 5 , 12 },
    { 156, 76, 5 , 12 },
    { 169, 76, 5 , 12 },
    { 182, 76, 5 , 12 },
    { 195, 76, 5 , 11 },
    { 208, 76, 2 , 12 },
    { 218, 76, 2 , 12 },
    { 228, 76, 3 , 12 },
    { 239, 76, 3 , 11 },
    { 250, 76, 6 , 9 },
    { 264, 76, 6 , 12 },
    { 278, 76, 5 , 12 },
    { 291, 76, 5 , 12 },
    { 304, 76, 5 , 12 },
    { 317, 76, 6 , 12 },
    { 331, 76, 5 , 11 },
    { 344, 76, 5 , 5 },
    { 357, 76, 7 , 9 },
    { 372, 76, 5 , 12 },
    { 385, 76, 5 , 12 },
    { 398, 76, 5 , 12 },
    { 411, 76, 5 , 11 },
    { 424, 76, 5 , 12 },
    { 437, 76, 5 , 9 },
    { 450, 76, 5 , 9 },
    { 463, 76, 5 , 10 },
    { 476, 76, 5 , 10 },
    { 489, 76, 5 , 10 },
    { 4, 100, 6 , 10 },
    { 18, 100, 5 , 9 },
    { 31, 100, 5 , 11 },
    { 44, 100, 9 , 7 },
    { 61, 100, 5 , 10 },
    { 74, 100, 5 , 10 },
    { 87, 100, 5 , 10 },
    { 100, 100, 5 , 10 },
    { 113, 100, 5 , 9 },
    { 126, 100, 2 , 10 },
    { 136, 100, 2 , 10 },
    { 146, 100, 3 , 10 },
    { 157, 100, 3 , 9 },
    { 168, 100, 6 , 9 },
    { 182, 100, 6 , 10 },
    { 196, 100, 5 , 10 },
    { 209, 100, 5 , 10 },
    { 222, 100, 5 , 10 },
    { 235, 100, 6 , 10 },
    { 249, 100, 5 , 9 },
    { 262, 100, 5 , 5 },
    { 275, 100, 7 , 7 },
    { 290, 100, 5 , 10 },
    { 303, 100, 5 , 10 },
    { 316, 100, 5 , 10 },
    { 329, 100, 5 , 9 },
    { 342, 100, 5 , 12 },
    { 355, 100, 5 , 11 },
    { 368, 100, 5 , 11 },
};

// Font glyphs info data
// NOTE: No glyphs.image data provided
static const GlyphInfo genesisFontGlyphs[189] = {
    { 32, 0, 0, 4, { 0 }},
    { 33, 2, 4, 5, { 0 }},
    { 34, 2, 4, 7, { 0 }},
    { 35, 1, 4, 8, { 0 }},
    { 36, 1, 2, 7, { 0 }},
    { 37, 1, 4, 9, { 0 }},
    { 38, 1, 4, 7, { 0 }},
    { 39, 2, 4, 5, { 0 }},
    { 40, 3, 4, 7, { 0 }},
    { 41, 1, 4, 7, { 0 }},
    { 42, 1, 4, 7, { 0 }},
    { 43, 1, 6, 7, { 0 }},
    { 44, 1, 12, 5, { 0 }},
    { 45, 1, 8, 6, { 0 }},
    { 46, 2, 12, 5, { 0 }},
    { 47, 1, 4, 5, { 0 }},
    { 48, 1, 4, 7, { 0 }},
    { 49, 2, 4, 7, { 0 }},
    { 50, 1, 4, 7, { 0 }},
    { 51, 1, 4, 7, { 0 }},
    { 52, 1, 4, 7, { 0 }},
    { 53, 1, 4, 7, { 0 }},
    { 54, 1, 4, 7, { 0 }},
    { 55, 1, 4, 7, { 0 }},
    { 56, 1, 4, 7, { 0 }},
    { 57, 1, 4, 7, { 0 }},
    { 58, 2, 6, 5, { 0 }},
    { 59, 1, 6, 5, { 0 }},
    { 60, 1, 6, 5, { 0 }},
    { 61, 1, 7, 6, { 0 }},
    { 62, 1, 6, 5, { 0 }},
    { 63, 1, 4, 7, { 0 }},
    { 64, 1, 4, 9, { 0 }},
    { 65, 1, 4, 7, { 0 }},
    { 66, 1, 4, 7, { 0 }},
    { 67, 1, 4, 7, { 0 }},
    { 68, 1, 4, 7, { 0 }},
    { 69, 1, 4, 7, { 0 }},
    { 70, 1, 4, 7, { 0 }},
    { 71, 1, 4, 7, { 0 }},
    { 72, 1, 4, 7, { 0 }},
    { 73, 2, 4, 5, { 0 }},
    { 74, 1, 4, 7, { 0 }},
    { 75, 1, 4, 7, { 0 }},
    { 76, 1, 4, 7, { 0 }},
    { 77, 1, 4, 9, { 0 }},
    { 78, 1, 4, 7, { 0 }},
    { 79, 1, 4, 7, { 0 }},
    { 80, 1, 4, 7, { 0 }},
    { 81, 1, 4, 7, { 0 }},
    { 82, 1, 4, 7, { 0 }},
    { 83, 1, 4, 7, { 0 }},
    { 84, 1, 4, 7, { 0 }},
    { 85, 1, 4, 7, { 0 }},
    { 86, 1, 4, 7, { 0 }},
    { 87, 1, 4, 9, { 0 }},
    { 88, 1, 4, 7, { 0 }},
    { 89, 1, 4, 7, { 0 }},
    { 90, 1, 4, 7, { 0 }},
    { 91, 3, 4, 7, { 0 }},
    { 92, 1, 4, 5, { 0 }},
    { 93, 1, 4, 7, { 0 }},
    { 94, 1, 4, 7, { 0 }},
    { 95, 0, 14, 5, { 0 }},
    { 96, 1, 4, 5, { 0 }},
    { 97, 1, 6, 7, { 0 }},
    { 98, 1, 4, 7, { 0 }},
    { 99, 1, 6, 7, { 0 }},
    { 100, 1, 4, 7, { 0 }},
    { 101, 1, 6, 7, { 0 }},
    { 102, 1, 4, 6, { 0 }},
    { 103, 1, 6, 7, { 0 }},
    { 104, 1, 4, 7, { 0 }},
    { 105, 2, 4, 5, { 0 }},
    { 106, 1, 4, 7, { 0 }},
    { 107, 1, 4, 7, { 0 }},
    { 108, 2, 4, 5, { 0 }},
    { 109, 1, 6, 9, { 0 }},
    { 110, 1, 6, 7, { 0 }},
    { 111, 1, 6, 7, { 0 }},
    { 112, 1, 6, 7, { 0 }},
    { 113, 1, 6, 7, { 0 }},
    { 114, 1, 6, 7, { 0 }},
    { 115, 1, 6, 7, { 0 }},
    { 116, 1, 5, 6, { 0 }},
    { 117, 1, 6, 7, { 0 }},
    { 118, 1, 6, 7, { 0 }},
    { 119, 1, 6, 9, { 0 }},
    { 120, 1, 6, 7, { 0 }},
    { 121, 1, 6, 7, { 0 }},
    { 122, 1, 6, 7, { 0 }},
    { 123, 2, 4, 7, { 0 }},
    { 124, 2, 4, 5, { 0 }},
    { 125, 1, 4, 7, { 0 }},
    { 126, 1, 4, 8, { 0 }},
    { 161, 2, 6, 5, { 0 }},
    { 162, 1, 4, 7, { 0 }},
    { 163, 1, 4, 8, { 0 }},
    { 8364, 1, 4, 8, { 0 }},
    { 165, 1, 4, 7, { 0 }},
    { 352, 1, 1, 7, { 0 }},
    { 167, 0, 0, 0, { 0 }},
    { 353, 1, 3, 7, { 0 }},
    { 169, 1, 4, 9, { 0 }},
    { 170, 0, 0, 0, { 0 }},
    { 171, 1, 6, 8, { 0 }},
    { 172, 1, 8, 7, { 0 }},
    { 174, 1, 4, 9, { 0 }},
    { 175, 0, 0, 0, { 0 }},
    { 176, 1, 4, 6, { 0 }},
    { 177, 1, 6, 7, { 0 }},
    { 178, 0, 0, 0, { 0 }},
    { 179, 0, 0, 0, { 0 }},
    { 381, 1, 1, 7, { 0 }},
    { 181, 1, 6, 7, { 0 }},
    { 182, 1, 4, 9, { 0 }},
    { 183, 2, 8, 5, { 0 }},
    { 382, 1, 3, 7, { 0 }},
    { 185, 0, 0, 0, { 0 }},
    { 186, 0, 0, 0, { 0 }},
    { 187, 1, 6, 8, { 0 }},
    { 338, 1, 4, 11, { 0 }},
    { 339, 1, 6, 11, { 0 }},
    { 376, 1, 2, 7, { 0 }},
    { 191, 1, 6, 7, { 0 }},
    { 192, 1, 1, 7, { 0 }},
    { 193, 1, 1, 7, { 0 }},
    { 194, 1, 1, 7, { 0 }},
    { 195, 1, 1, 7, { 0 }},
    { 196, 1, 2, 7, { 0 }},
    { 197, 1, 0, 7, { 0 }},
    { 198, 1, 4, 11, { 0 }},
    { 199, 1, 4, 7, { 0 }},
    { 200, 1, 1, 7, { 0 }},
    { 201, 1, 1, 7, { 0 }},
    { 202, 1, 1, 7, { 0 }},
    { 203, 1, 2, 7, { 0 }},
    { 204, 1, 1, 5, { 0 }},
    { 205, 2, 1, 5, { 0 }},
    { 206, 1, 1, 5, { 0 }},
    { 207, 1, 2, 5, { 0 }},
    { 208, 0, 4, 7, { 0 }},
    { 209, 1, 1, 7, { 0 }},
    { 210, 1, 1, 7, { 0 }},
    { 211, 1, 1, 7, { 0 }},
    { 212, 1, 1, 7, { 0 }},
    { 213, 1, 1, 7, { 0 }},
    { 214, 1, 2, 7, { 0 }},
    { 215, 1, 6, 7, { 0 }},
    { 216, 0, 4, 7, { 0 }},
    { 217, 1, 1, 7, { 0 }},
    { 218, 1, 1, 7, { 0 }},
    { 219, 1, 1, 7, { 0 }},
    { 220, 1, 2, 7, { 0 }},
    { 221, 1, 1, 7, { 0 }},
    { 222, 1, 4, 7, { 0 }},
    { 223, 1, 4, 7, { 0 }},
    { 224, 1, 3, 7, { 0 }},
    { 225, 1, 3, 7, { 0 }},
    { 226, 1, 3, 7, { 0 }},
    { 227, 1, 3, 7, { 0 }},
    { 228, 1, 4, 7, { 0 }},
    { 229, 1, 2, 7, { 0 }},
    { 230, 1, 6, 11, { 0 }},
    { 231, 1, 6, 7, { 0 }},
    { 232, 1, 3, 7, { 0 }},
    { 233, 1, 3, 7, { 0 }},
    { 234, 1, 3, 7, { 0 }},
    { 235, 1, 4, 7, { 0 }},
    { 236, 1, 3, 5, { 0 }},
    { 237, 2, 3, 5, { 0 }},
    { 238, 1, 3, 5, { 0 }},
    { 239, 1, 4, 5, { 0 }},
    { 240, 1, 4, 7, { 0 }},
    { 241, 1, 3, 7, { 0 }},
    { 242, 1, 3, 7, { 0 }},
    { 243, 1, 3, 7, { 0 }},
    { 244, 1, 3, 7, { 0 }},
    { 245, 1, 3, 7, { 0 }},
    { 246, 1, 4, 7, { 0 }},
    { 247, 1, 6, 7, { 0 }},
    { 248, 0, 6, 7, { 0 }},
    { 249, 1, 3, 7, { 0 }},
    { 250, 1, 3, 7, { 0 }},
    { 251, 1, 3, 7, { 0 }},
    { 252, 1, 4, 7, { 0 }},
    { 253, 1, 3, 7, { 0 }},
    { 254, 1, 4, 7, { 0 }},
    { 255, 1, 4, 7, { 0 }},
};

// Style loading function: Genesis
static void GuiLoadStyleGenesis(void)
{
    // Load style properties provided
    // NOTE: Default properties are propagated
    for (int i = 0; i < GENESIS_STYLE_PROPS_COUNT; i++)
    {
        GuiSetStyle(genesisStyleProps[i].controlId, genesisStyleProps[i].propertyId, genesisStyleProps[i].propertyValue);
    }

    // Custom font loading
    // NOTE: Compressed font image data (DEFLATE), it requires DecompressData() function
    int genesisFontDataSize = 0;
    unsigned char *data = DecompressData(genesisFontData, GENESIS_STYLE_FONT_ATLAS_COMP_SIZE, &genesisFontDataSize);
    Image imFont = { data, 512, 256, 1, 2 };

    Font font = { 0 };
    font.baseSize = 16;
    font.glyphCount = 189;

    // Load texture from image
    font.texture = LoadTextureFromImage(imFont);
    UnloadImage(imFont);  // Uncompressed image data can be unloaded from memory

    // Copy char recs data from global fontRecs
    // NOTE: Required to avoid issues if trying to free font
    font.recs = (Rectangle *)RAYGUI_MALLOC(font.glyphCount*sizeof(Rectangle));
    memcpy(font.recs, genesisFontRecs, font.glyphCount*sizeof(Rectangle));

    // Copy font char info data from global fontChars
    // NOTE: Required to avoid issues if trying to free font
    font.glyphs = (GlyphInfo *)RAYGUI_MALLOC(font.glyphCount*sizeof(GlyphInfo));
    memcpy(font.glyphs, genesisFontGlyphs, font.glyphCount*sizeof(GlyphInfo));

    GuiSetFont(font);

    // Setup a white rectangle on the font to be used on shapes drawing,
    // it makes possible to draw shapes and text (full UI) in a single draw call
    Rectangle fontWhiteRec = { 510, 254, 1, 1 };
    SetShapesTexture(font.texture, fontWhiteRec);

    //-----------------------------------------------------------------

    // TODO: Custom user style setup: Set specific properties here (if required)
    // i.e. Controls specific BORDER_WIDTH, TEXT_PADDING, TEXT_ALIGNMENT
}