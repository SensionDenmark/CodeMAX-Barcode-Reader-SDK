///------------------------------------------------------------------------------------------------------------
///------------------------------------------------------------------------------------------------------------
///
///
///                                     CodeMAX Barcode Reader SDK
///                                ====================================
///
///
///                                             SENSION 2018
///                                 Industrial Vision Sensing Solutions
///                                           Aalborg, Denmark
///
///------------------------------------------------------------------------------------------------------------
///------------------------------------------------------------------------------------------------------------
///
///                             READ THIS CAREFULLY BEFORE USING THIS SOFTWARE
///                             ==============================================
///
///
/// THIS SOFTWARE IS LICENSED UNDER THE SENSION CODEMAX BARCODE READER SOFTWARE SDK LICENSE AGREEMENT.
///
/// THIS SOFTWARE CAN ONLY BE USED BY THE RIGHTFUL OWNER. THE SOFTWARE MUST NOT BE COPIED OR RE-DISTRIBUTED
/// WITHOUT SPECIFIC PERMISSIONS FROM SENSION.
///
/// THIS SOFTWARE IS PROVIDED “AS IS”. SENSION DOES NOT WARRANT THE PERFORMANCE OR RESULTS YOU MAY OBTAIN BY
/// USING OUR SOFTWARE AND RELATED TECHNICAL DOCUMENTATION. SENSION MAKE NO WARRANTIES WHEN USING OUR SOFTWARE.
/// BY USING OUR SOFTWARE, SENSION WILL NOT IN ANY WAY BE LIABLE TO YOU FOR ANY CONSEQUENTIAL, INCIDENTAL OR
/// SPECIAL DAMAGES, INCLUDING ANY LOST PROFITS OR LOST SAVINGS.
///
/// WHEN USING THIS SOFTWARE YOU AGREE NOT TO MODIFY, REVERSE ENGINEER, DECOMPILE, DISASSEMBLE,
/// OR IN OTHER WAYS ATTEMPT TO DISCOVER OR RECOVER THE SOURCE CODE OF THE SOFTWARE.
///
/// AS RIGHTFUL OWNER YOU FULLY AGREE THAT THE SOFTWARE WILL NOT BE SHIPPED, TRANSFERRED OR EXPORTED INTO
/// ANY COUNTRY OR USED IN ANY MANNER PROHIBITED BY DANISH OR EUROPEAN EXPORT LAWS.
///
/// COPYRIGHT (c) SENSION , DENMARK
///------------------------------------------------------------------------------------------------------------
///------------------------------------------------------------------------------------------------------------
///
#include "codemax.h"
#include "cmdefines.h"


using namespace cm;
const static enumString boolToYesNo[] = {L"No", L"Yes"};


///---------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------
///
/// \brief This demo program shows how to use the CodeMAX SDK in simple steps :
///
/// 1)  The goal is to create a small command-line program which takes two arguments, namely arg1: filename and
///     path of the source image to be used for analysis, and arg2: the filename and path of the output image
///     that will contain information about the decoding.
///
/// 2)  Retrieve CodeMAX SDK software version info and print it on the console.
///
/// 3)  Open the specified input image
///
/// 4)  Perform setup of the CodeMAX barcode decoder instance by calling setup() once. In this example the decoder
///     is configured to:
///
///     -Use precise processing strategy i.e. 'CM_PROCSTRATEGY_PRECISE'
///     -Use a processing timeout
///     -Enable decoding of five different symbol types, namely: EAN8, EAN13, CODE128, QR and Datamatrix symbols
///
/// 5) Define a processing area 'processingArea' that is equal to the full image, and call the decode function decodeImage().
///
/// 6) Display the decoding result on the console.
///
/// 7) Save the output image at the specified location and with the specified name.
///
///---------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    CodeMAX             decoder;
    cmString            errorMessage;
    cmIoImg             testImage;
    cmIoImg             resultImage;
    cmRoi               processingArea;
    cmDecodeInfo        decodeInfo;
    cmString            className;
    cmString            outputFilename;
    cmString            infoString;
    cmVersionInfo       versionInfo;
    enumCmErrorCodes    status;


    /// 1 Check the argument list
    if (argc != 3)
    {
        std::cout << "------------------------------------------------------------------------------------------------------\n\n";
        std::cout << "         S E N S I O N    C O D E M A X    B A R C O D E    D E C O D E R    SDK    D E M O\n";
        std::cout << "\nThis CodeMAX SDK demo application decodes all barcodes in an input image, shows the result on the\n";
        std::cout << "console output and stores a result image with decode information\n";
        std::cout << "Call the application with the following arguments:\n\n";
        std::cout << "\n";
        std::cout << "./codemax_demo <inputFilename> <outputFilename>\n\n";
        std::cout << "\n";
        std::cout << "<inputFilename>\t The path to the input image.\n";
        std::cout << "<outputFilename>\t The path to the result image.\n";
        std::cout << "------------------------------------------------------------------------------------------------------\n\n";

        return 1;
    }

    /// 2 Retrieve software version information and display it in a header
    decoder.getVersionInfo(versionInfo);
    infoString.format(L"  Software: %ls\n  Version : %d.%d.%d\n  Release : %s\n",
                      enumLicenseTypeName[(int)versionInfo.licenseType], versionInfo.versionMajor, versionInfo.versionMinor,
                      versionInfo.revisionNumber, versionInfo.versionReleaseDate);

    // Some info header
    std::cout << "------------------------------------------------------------------------------------------------------\n\n";
    std::cout << "         S E N S I O N    C O D E M A X    B A R C O D E    D E C O D E R    SDK    D E M O\n\n";
    std::cout << infoString.getStringA() << "\n";
    std::cout << "----Arguments-----------------------------------------------------------------------------------------\n\n";
    std::cout << "  inputFilename : " << argv[1] << "\n";
    std::cout << "  outputFilename: " << argv[2] << "\n";
    std::cout << "----Result--------------------------------------------------------------------------------------------\n\n";


    /// 3 Open an image from the disc
    if (testImage.load(argv[1]) != IO_ERROR_NONE)
    {
        std::cout << "  Error: Input image load error" "\n";
        return 1;
    }

    /// 4 Initialize the decoder. Here we only want to decode 5 different types of symbols
    /// and with a timeout value of 500 ms. We use the precise processing strategy
    ///
    status = decoder.setup(CM_PROCSTRATEGY_PRECISE, 500, CM_EAN_8 | CM_EAN_13 | CM_CODE_128 | CM_DATAMATRIX | CM_QR);

    if (status != CM_ERROR_NONE)
    {
        // Print the error message
        errorMessage = decoder.getErrorMessage(status);
        std::cout << "  ERROR: " << errorMessage.getStringA() << "\n";
        std::cout << "------------------------------------------------------------------------------------------------------\n\n";
        return 1;
    }


    /// 5 Create a user-defined processing area that covers the whole image (alternatively the procROI and pResult arguments could
    /// also have been set to NULL), and finally decode the image
    processingArea.left     = 0;
    processingArea.right    = testImage.getWidth();
    processingArea.top      = 0;
    processingArea.bottom   = testImage.getHeight();

    status = decoder.decodeImage(testImage, decodeInfo, &processingArea, &resultImage);
    if (status != CM_ERROR_NONE)
    {
        // Print the error message
        std::cout << "  ERROR: The decoder failed to execute due to the following error:\n";
        errorMessage = decoder.getErrorMessage(status);
        std::cout << "         " << errorMessage.getStringA() << "\n";
        std::cout << "------------------------------------------------------------------------------------------------------\n\n";
        return 1;
    }


    /// 6 Retrieve the decoding result and print it
    ///
    std::cout << "Number of found symbols:" << decodeInfo.numBarcodes << "\n";

    for (int i = 0; i < decodeInfo.numBarcodes; i++)
    {

        // Print the result
        std::cout << "Symbol " << i << ":" << std::endl;
        className.format(L"%ls", enumSymbolClassName[(int)decodeInfo.barcodeData[i].detectedClass]);
        std::cout << "  Detected class....:" << (char *)className.getStringA() << std::endl;
        std::cout << "  Decoded...........:" << (decodeInfo.barcodeData[i].isDecoded ? "yes" : "no")  << std::endl;
        std::cout << "  Timed out.........:" << (decodeInfo.barcodeData[i].hasTimedOut ? "yes" : "no")  << std::endl;
        std::cout << "  Symbol content....:" << decodeInfo.barcodeData[i].barcodeContent  << std::endl;
        std::cout << "  Symbol type.......:" << decodeInfo.barcodeData[i].barcodeType  << std::endl;
        std::cout << "  Symbol proc.time..:" << decodeInfo.barcodeData[i].decodingTimeMs  << " ms" << std::endl;
        std::cout << "  Symbol region.....:" << "left:" << decodeInfo.barcodeData[i].barcodeRoi.left << " top:" <<
                  decodeInfo.barcodeData[i].barcodeRoi.top << " right:" << decodeInfo.barcodeData[i].barcodeRoi.right << " bottom:" <<
                  decodeInfo.barcodeData[i].barcodeRoi.bottom  << std::endl;
        std::cout << "\n" << std::endl;

    }

    std::cout << "------------------------------------------------------------------------------------------------------\n\n";


    /// 7 Save the result image with overlay information
    outputFilename.copy(argv[2]);
    if (resultImage.save(outputFilename, &infoString) != IO_ERROR_NONE)
    {
        std::cout << "  Error: Output image save error. " << infoString.getStringA() << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------\n\n";
        return 1;
    }

    // Return 0 if barcodes were found, 1 otherwise.
    if (decodeInfo.numBarcodes)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
