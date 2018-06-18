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


// First we import the CodeMAX Barcode Reader SDK library 
// and instantiate objects and variables:
 
#include "codemax.h"
#include "cmdefines.h"
 
using namespace cm;
 
int main(int argc, char *argv[])
{
 CodeMAX decoder;
 cmIoImg inputImage;
 cmIoImg resultImage;
 cmDecodeInfo decodeInfo;
 int numSymbols;
 
 // Then we load the test image:
 inputImage.load("image.jpg");
 
 // Next we initialize the decoder to decode barcodes using 
 // the precise mode allow maximum 100 ms to decode a barcode
 // before time-out and enable all supported symbologies.
 decoder.setup(enumProcStrategy::CM_PROCSTRATEGY_PRECISE, 100, CM_ENABLE_ALL);
 
 // Now we are ready to start decoding, which is done by providing
 // the input image and an optional empty image which will contain 
 // information about the decoded barcodes:
 numSymbols = decoder.decodeImage(inputImage, NULL, &resultImage);
 
 // Finally, we save the result image to the disk, and iterate over
 // all decoded barcodes and print relevant information about the 
 // barcodes to the terminal.
 resultImage.save("resultImage.jpg");
 
 std::cout << "CodeMAX Barcode Reader SDK C++ Example\n" << "\n";
 
 for (int i = 0; i < numSymbols; i++)
 {
  decoder.getBarcodeRegionInfo(i, decodeInfo);
  std::cout << "Barcode type: << decodeInfo.barcodeType << "\n";
  std::cout << "Barcode content: " << decodeInfo.barcodeContent << "\n";
 }
 
 return 0;
}
