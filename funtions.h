#ifndef CONVERT_H
#define CONVERT_H

#include <QImage>
#include <QString>
#include <QDir>
#include <QColor>
#include <QRgb>
#include <QFile>

class Convert
{
private:

    QDir beginningWay;
    QRgb pixColor;
    QImage Image;
    int pixColorInInt;

public:

    Convert();
    void convertImageToBW(QString way);
    QString giveWayToFile();
    QImage giveConvertedImage();

};



class Matrix
{
private:

    // для изображения
    QString wayToImage;
    int heightImage;
    int widthImage;
    QRgb pixColor;
    QImage tempImage;
    int** matrixImage;
    int pixColorToInt;

    // для маски
    int positionToHeightCentralElementMask;
    int positionToWidthCentralElementMask;
    QString wayToMask;
    QByteArray sizeMask;
    int heightMask;
    int widthMask;
    QByteArray positionCentralElementMask;
    QByteArray oneLineMask;
    int* matrixMask;
    int tempCounter;

public:

    Matrix();
    void MatrixConvertedImage(QString way);
    void MatrixMask(QString way);
    int** giveMatrixImage();
    int* giveMatrixMask();
    int giveHeightMask();
    int giveWidthMask();
    int givepositionToHeightCentralElementMask();
    int givepositionToWidthCentralElementMask();

};



class ProcessingImage
{
private:

    int** matrixErosion;
    int** tempMatrix;
    int* matrixMask;
    int tempCounter;
    QImage tempImage;
    int heightImage;
    int widthImage;
    int heightMask;
    int widthMask;
    int positionToHeightCentralElementMask;
    int positionToWidhtCentralElementMask;
    int** matrixDelatation;
    int** matrixOutline;

public:

    ProcessingImage();
    void erosionImage(Convert convert, Matrix matrix);
    void delatationImage(Convert convert, Matrix matrix);
    void outlineImage();
    QImage giveTempImage();

};


class SaveImage
{
private:

    QString tempWayToFile;
    QImage tempImage;

public:

    SaveImage();
    void saveImage(QString way, Convert conv);
    void saveImage(QString way, ProcessingImage process);

};

#endif // CONVERT_H
