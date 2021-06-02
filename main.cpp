#include <QCoreApplication>
#include "funtions.h"

QString giveWayTo(){
     QDir beginningWay;
     return beginningWay.currentPath();
}

int main()
{
    Convert convert;
    Matrix matrix;
    ProcessingImage process;
    SaveImage save;

    convert.convertImageToBW(giveWayTo()+"/image.png");
    save.saveImage(giveWayTo()+"/ConvertedImage.png", convert);

    matrix.MatrixConvertedImage(giveWayTo()+"/ConvertedImage.png");
    matrix.MatrixMask(giveWayTo()+ "/mask.txt");

    process.delatationImage(convert, matrix);
    save.saveImage(giveWayTo()+"/DilatationImage.png", process);

    process.erosionImage(convert, matrix);
    save.saveImage(giveWayTo()+"/ErosionImage.png", process);

    process.outlineImage();
    save.saveImage(giveWayTo()+"/OutlineImage.png", process);

    return 0;
}
