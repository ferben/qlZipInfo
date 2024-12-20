/*
    GeneratePreviewForURL.h - constants for qlZipInfo

    History:

    v. 0.1.0 (07/22/2021) - initial release
    v. 0.2.0 (11/13/2021) - add binhex support
    v. 0.3.0 (08/01/2022) - add stuffit support
    v. 0.4.0 (10/13/2024) - update color scheme based on PR#2
 
    Copyright (c) 2015-2022, 2024 Sriranga R. Veeraraghavan <ranga@calalum.org>

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software") to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject
    to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef generate_preview_for_url_h
#define generate_preview_for_url_h

/* constants */

/*
    Default error code (MacOS extractErr error code from MacErrors.h) See:
    https://opensource.apple.com/source/CarbonHeaders/CarbonHeaders-18.1/MacErrors.h
 */

enum
{
    zipQLFailed = -3104,
};

/*
    Default values for spacing of the output
 */

enum
{
    gBorder             = 1,
    //gFontSize           = 2,
    gIconHeight         = 16,
    gIconWidth          = 16,
    gColPadding         = 8,
    gColFileSize        = 72,
    gColFileCompress    = 46,
    gColFileModDate     = 58,
    gColFileModTime     = 56,
    gColFileType        = 24,
    gColFileName        = 288,
    gColFileMacType     = 58,
    gColFileMacCreator  = 58,
    gColFileMacFileName = 356,
};

/* table headings */

static const NSString *gTableHeaderName = @"Name";
static const NSString *gTableHeaderSize = @"Size";
static const NSString *gTableHeaderMode = @"Perms.";
static const NSString *gTableHeaderDate = @"Modified";
static const NSString *gTableHeaderType = @"Type";
static const NSString *gTableHeaderCreator = @"Creator";

/* darkmode styles */

static const NSString *gDarkModeBackground = @"#231D2D";
static const NSString *gDarkModeForeground = @"#DDDDDD";
static const NSString *gDarkModeTableRowEvenBackgroundColor
                                           = @"#2F2A39";
static const NSString *gDarkModeTableRowEvenForegroundColor
                                           = @"DEDEDE";
static const NSString *gDarkModeTableBorderColor
                                           = @"#231D2D";
static const NSString *gDarkModeTableHeaderBorderColor
                                           = @"#403B47";
/* light mode styles */

static const NSString *gLightModeBackground = @"white";
static const NSString *gLightModeForeground = @"6e6b6d";
static const NSString *gLightModeTableRowEvenBackgroundColor
                                            = @"#F4F5F5";
static const NSString *gLightModeTableRowEvenForegroundColor
                                            = @"6e6b6d";
static const NSString *gLightModeTableBorderColor
                                            = @"white";
static const NSString *gLightModeTableHeaderBorderColor
                                            = @"#DDDDDD";

/* icons */

static const NSString *gFolderIcon        = @"&#x1F4C1";
static const NSString *gFileIcon          = @"&#x1F4C4";
static const NSString *gFileEncyrptedIcon = @"&#x1F512";
static const NSString *gFileLinkIcon      = @"&#x1F4D1";
static const NSString *gFileSpecialIcon   = @"&#x2699";
static const NSString *gFileUnknownIcon   = @"&#x2753";
static const NSString *gFileAppIcon       = @"&#x270D";
static const NSString *gFilePkgIcon       = @"&#x1F4E6";

/* unknown file name */

static const char *gFileNameUnavilable = "[Unavailable]";
static const NSString *gFileNameUnavilableStr =
                                         @"[Unavailable]";

/*
    font style
    see: https://stackoverflow.com/questions/32660748
 */

static const NSString *gFontFace =
    @"-apple-system, system-ui, 'Helvetica Neue', 'Lucida Grande', sans-serif";
static const NSString *gFontSize = @"small";

/* filesize abbreviations */

static const char *gFileSizeBytes     = "B";
static const char *gFileSizeKiloBytes = "K";
static const char *gFileSizeMegaBytes = "M";
static const char *gFileSizeGigaBytes = "G";
static const char *gFileSizeTeraBytes = "T";

static const char *gMacFileTypeApplication = "APPL";
static const char *gMacFileTypeSIT         = "SITD";
static const char *gMacFileTypeSIT5        = "SIT5";

/* UTIs for files that may require special handling */

static const CFStringRef gUTIGZip   = CFSTR("org.gnu.gnu-zip-archive");
static const CFStringRef gUTIBinHex = CFSTR("com.apple.binhex-archive");
static const CFStringRef gUTISIT1   = CFSTR("com.stuffit.archive.sit");
static const CFStringRef gUTISIT2   = CFSTR("com.allume.stuffit-archive");

/* structs */

typedef struct fileSizeSpec
{
    char spec[3];
    Float64 size;
} fileSizeSpec_t;

/* prototypes */

OSStatus GeneratePreviewForURL(void *thisInterface,
                               QLPreviewRequestRef preview,
                               CFURLRef url,
                               CFStringRef contentTypeUTI,
                               CFDictionaryRef options);
static OSStatus GeneratePreviewForHQX(void *thisInterface,
                                      QLPreviewRequestRef preview,
                                      CFURLRef url,
                                      CFStringRef contentTypeUTI,
                                      CFDictionaryRef options);
static OSStatus GeneratePreviewForSIT(void *thisInterface,
                                      QLPreviewRequestRef preview,
                                      CFURLRef url,
                                      CFStringRef contentTypeUTI,
                                      CFDictionaryRef options);
void CancelPreviewGeneration(void *thisInterface,
                             QLPreviewRequestRef preview);
static off_t getGZExpandedFileSize(const char *zipFileNameStr);
static int getFileSizeSpec(off_t fileSizeInBytes,
                           fileSizeSpec_t *fileSpec);
static float getCompression(off_t uncompressedSize,
                            off_t compressedSize);
static bool formatOutputHeader(NSMutableString *qlHtml);
static bool startOutputBody(NSMutableString *qlHtml);
static bool endOutputBody(NSMutableString *qlHtml);

#endif /* generate_preview_for_url_h */
