#include "funtions.h"

Convert::Convert()
{

}

void Convert::convertImageToBW(QString way)
{
    Image.load(way);

    for(int i = 0; i < Image.width(); i++){
        for( int j = 0; j < Image.height(); j++){
            pixColor = Image.pixel(i, j);
            pixColorInInt = pixColor;
            if(pixColorInInt > -12000000){ // значение 12 млн. взято приблизительно для отделения светлых оттенков цветов от тёмных
                Image.setPixel(i, j, qRgb( 255,  255,  255));
            }
            else{
                Image.setPixel(i, j, qRgb(0, 0, 0));
            }
        }
    }
}

QImage Convert::giveConvertedImage()
{
    return Image;
}


Matrix::Matrix()
{

}

void Matrix::MatrixConvertedImage(QString way)
{
    tempImage.load(way);

    widthImage = tempImage.width();
    heightImage = tempImage.height();

    matrixImage = new int *[widthImage];
    for (int k = 0; k < widthImage; ++k)
        matrixImage[k] = new int [heightImage];

    for(int i = 0; i < widthImage; i++){
        for( int j = 0; j < heightImage; j++){

            pixColor = tempImage.pixel(i, j);
            pixColorToInt = pixColor;

            if(pixColorToInt == -16777216){
                matrixImage[i][j] = 1;
            }
            else{
                matrixImage[i][j] = 0;

            }
        }
    }
}

void Matrix::MatrixMask(QString way)
{

    QFile mask(way);
    mask.open(QIODevice::ReadOnly | QIODevice::Text);

    sizeMask = mask.readLine();
    positionCentralElementMask = mask.readLine();

    widthMask = sizeMask[0]-48;
    heightMask = sizeMask[2]-48;
    positionToWidthCentralElementMask = positionCentralElementMask[0] - 48;
    positionToHeightCentralElementMask = positionCentralElementMask[2] - 48;

    matrixMask = new int [widthMask*heightMask];
    tempCounter = 0;

    for(int j = 0; j < heightMask; j++){
        oneLineMask = mask.readLine();
        for(int i=0; i < (widthMask-1)*2 +1; i+=2){
            matrixMask[tempCounter] = oneLineMask[i] - 48;
            tempCounter++;
        }
        oneLineMask.clear();
        positionCentralElementMask.clear();
        sizeMask.clear();
    }
    mask.close();
}

int Matrix::giveWidthMask()
{
    return widthMask;
}

int Matrix::giveHeightMask()
{
    return heightMask;
}

int *Matrix::giveMatrixMask()
{
    return matrixMask;
}

int Matrix::givepositionToHeightCentralElementMask()
{
    return positionToHeightCentralElementMask;
}

int Matrix::givepositionToWidthCentralElementMask()
{
    return positionToWidthCentralElementMask;
}

int **Matrix::giveMatrixImage()
{
    return matrixImage;
}



ProcessingImage::ProcessingImage()
{

}

void ProcessingImage::erosionImage(Convert convert, Matrix matrix)
{
    tempImage = convert.giveConvertedImage();
    heightImage = tempImage.height();
    widthImage = tempImage.width();
    tempMatrix = matrix.giveMatrixImage();

    matrixErosion = new int *[widthImage];
    for (int k = 0; k < widthImage; k++)
        matrixErosion[k] = new int [heightImage];


    for(int i = 0; i < widthImage; i++){
        for( int j = 0; j < heightImage; j++){
            matrixErosion[i][j] =  tempMatrix[i][j];
        }
    }

    heightMask = matrix.giveHeightMask();
    widthMask = matrix.giveWidthMask();
    matrixMask = matrix.giveMatrixMask();
    positionToWidhtCentralElementMask = matrix.givepositionToWidthCentralElementMask();
    positionToHeightCentralElementMask = matrix.givepositionToHeightCentralElementMask();

    for(int i = 0; i < widthImage-2; i++){
        for(int j = 0; j < heightImage-2; j++){
            tempCounter = 0;
            for(int k = 0; k < widthMask; k++){
                for(int l = 0; l < heightMask; l ++){
                    if((tempMatrix[i+k][j+l] !=matrixMask[tempCounter]) && (matrixMask[tempCounter]==1)){
                        matrixErosion[i+positionToWidhtCentralElementMask][j+positionToHeightCentralElementMask] = 0;
                    }
                    tempCounter++;
                }
            }
        }
    }

    for(int i = 0; i< widthImage; i++){
        for(int j = 0; j < heightImage; j++){
            if(matrixErosion[i][j] == 1){
                tempImage.setPixel(i, j, qRgb( 0, 0, 0));
            }
            else{
                tempImage.setPixel(i, j, qRgb(255,  255,  255));
            }

        }
    }
}

void ProcessingImage::delatationImage(Convert convert, Matrix matrix)
{
    tempImage = convert.giveConvertedImage();
    heightImage = tempImage.height();
    widthImage = tempImage.width();
    tempMatrix = matrix.giveMatrixImage();

    matrixDelatation = new int *[widthImage];
    for (int k = 0; k < widthImage; k++)
        matrixDelatation[k] = new int [heightImage];

    for(int i = 0; i < widthImage; i++){
        for( int j = 0; j < heightImage; j++){
            matrixDelatation[i][j] =  tempMatrix[i][j];
        }
    }

    heightMask = matrix.giveHeightMask();
    widthMask = matrix.giveWidthMask();
    matrixMask = matrix.giveMatrixMask();
    positionToWidhtCentralElementMask = matrix.givepositionToWidthCentralElementMask();
    positionToHeightCentralElementMask = matrix.givepositionToHeightCentralElementMask();

    for(int i = 0; i < widthImage-2; i++){
        for(int j = 0; j < heightImage-2; j++){
            if(tempMatrix[i+positionToWidhtCentralElementMask][j+positionToHeightCentralElementMask] == matrixMask[positionToWidhtCentralElementMask*widthMask+positionToHeightCentralElementMask]){
                matrixDelatation[i+1][j] = 1;
                matrixDelatation[i][j+1] = 1;
                matrixDelatation[i+2][j+1] = 1; //213124214214
                matrixDelatation[i+1][j+2] = 1; //213124214214
            }
        }

    }

    for(int i = 0; i< widthImage; i++){
        for(int j = 0; j < heightImage; j++){
            if(matrixDelatation[i][j] == 1){
                tempImage.setPixel(i, j, qRgb( 0, 0, 0));
            }
            else{
                tempImage.setPixel(i, j, qRgb(255,  255,  255));
            }

        }
    }
}

void ProcessingImage::outlineImage()
{

    matrixOutline = new int *[widthImage];
    for (int k = 0; k < widthImage; k++)
        matrixOutline[k] = new int [heightImage];

    for( int i = 0; i< widthImage; i ++){
        for(int j = 0; j < heightImage; j++){
            if((matrixDelatation[i][j] == 1) && (matrixErosion[i][j] == 0)){
                matrixOutline[i][j] = 1;
            }
            else{
                matrixOutline[i][j] = 0;
            }
        }
    }

    for(int i = 0; i< widthImage; i++){
        for(int j = 0; j < heightImage; j++){
            if(matrixOutline[i][j] == 1){
                tempImage.setPixel(i, j, qRgb( 0, 0, 0));
            }
            else{
                tempImage.setPixel(i, j, qRgb(255,  255,  255));
            }

        }
    }
}

QImage ProcessingImage::giveTempImage()
{
    return tempImage;
}

SaveImage::SaveImage()
{

}

void SaveImage::saveImage(QString way, Convert conv)
{
    tempImage = conv.giveConvertedImage();
    tempImage.save(way);
}

void SaveImage::saveImage(QString way, ProcessingImage process)
{
    tempImage = process.giveTempImage();
    tempImage.save(way);
}
