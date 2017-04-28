#include "imagecontrol.h"
//#include <QDebug>
#include <QImage>
#include <QtWidgets>
#include<math.h>

ImageControl* imageControlInstance;

ImageControl::ImageControl(QObject *parent)
    : QObject(parent)
    , cImgPath(NULL)
    , mNaturalImgWidth(0)
    , mNaturalImgHeight(0)
    , mReviseLevel(0)
    , mlb(NULL)
{
    qDebug() << Q_FUNC_INFO;
}

ImageControl::~ImageControl()
{
    qDebug() << Q_FUNC_INFO;
}

void ImageControl::imageControlInit()
{
    qDebug() << Q_FUNC_INFO;
    cImgPath = NULL;
    mNaturalImgWidth = 0 ;
    mNaturalImgHeight = 0;
    mReviseLevel = 0;
}

ImageControl *ImageControl::instance()
{
    if (imageControlInstance == NULL)
    {
        imageControlInstance = new ImageControl();
    }
    else
    {
        return imageControlInstance;
    }
}

bool ImageControl::setImage(QString imgPath)
{
    qDebug() << Q_FUNC_INFO;

    qDebug() << QString ("file Path [%1]").arg(imgPath);

    QString fileName = imgPath;
    QByteArray byteName = fileName.toLocal8Bit();
    char * cFileName = byteName.data();

    cImgPath = cFileName;

    img.load(cImgPath);


    if ( false == img.isNull() )
    {
        qDebug() << "Image Is Valid";
        QSize imgSiz = img.size();
        setNaturalWidth(imgSiz.width());
        setNaturalHeight(imgSiz.height());
        return true;
    }
    else
    {
        qDebug() << "Image Is NULL";
        return false;
    }
}

void ImageControl::setResizeImage(int imgWidth, int imgHeight)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << QString ("Width [%1],  Height [%2] ").arg(imgWidth).arg(imgHeight);
    img = img.scaled(imgWidth , imgHeight );
    setNaturalHeight(imgHeight);
    setNaturalWidth(imgWidth);
}

void ImageControl::setImageRevise(int reviseLevel)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << QString ("revise Level [%1]").arg(reviseLevel);
}

bool ImageControl::isImageResize()
{
    // need resize??


    bool returnValue = true;

    if ( getNaturalWidth() >= RESIZE_WIDTH)
    {
        //        returnValue = true;
    }
    else
    {
        if ( getNaturalHeight() >= RESIZE_HEIGHT)
        {
            //            returnValue = true;
        }
        else
        {
            returnValue = false;
        }
    }

    qDebug() << QString ("need Image Resize [%1]").arg(returnValue);
    return returnValue;
}

void ImageControl::getDominantColor(QString imgPath)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << QString ("file Path [%1]").arg(imgPath);

    //set image
    //size check
    //revise
    //show

    if ( true == setImage(imgPath) )
    {
        if (true == isImageResize())
        {
            setResizeImage();
        }
        else
        {
        }
        setImageRevise(1);

        imgCalculate();
        //calculate color map

        showImage();
    }
    else
    {
    }


}

void ImageControl::showImage()
{
    qDebug() << Q_FUNC_INFO;
    mlb.setPixmap(QPixmap::fromImage(img));
    mlb.show();

}

//void ImageControl::imgCalculate()
//{
//    mMap.clear();
////    QMap<int, int>::ConstIterator ii;
////    for( ii = mMap.constBegin(); ii != mMap.constEnd(); ++ii )
////      qDebug() << ii.key() << " = " << ii.value();
//    qDebug() << QString("width [%1]").arg(getNaturalWidth() );
//    qDebug() << QString("height [%1]").arg(getNaturalHeight() );
//    for (int x = 0; x < getNaturalWidth() ; x++)
//    {
//        for (int y = 0 ; y < getNaturalHeight(); y++)
//        {
//            if ( true == mMap.contains(img.pixel(x,y)) )
//            {
//                mMap[img.pixel(x,y)] = mMap[img.pixel(x,y)] + 1;
//            }
//            else
//            {
//                mMap[img.pixel(x,y)] = 1;
//            }
//        }
//    }
//    qDebug() << QString("mCount [%1]").arg(mMap.count());
//    foreach( int key, mMap.keys() )
//        qDebug() << key << " = " << mMap[key];

//}

void ImageControl::imgCalculate()
{
    qDebug() << QString("width [%1]").arg(getNaturalWidth() );
    qDebug() << QString("height [%1]").arg(getNaturalHeight() );

    QColor temp;

    for (int x = 0; x < getNaturalWidth() ; x++)
    {
        for (int y = 0 ; y < getNaturalHeight(); y++)
        {
            temp = img.pixelColor(x,y);
            if ((temp.red() + temp.green() + temp.blue()) < 382)
            {
                img.setPixelColor(x,y,qRgb(0,0,0));
            }
            else
            {
                img.setPixelColor(x,y,qRgb(255,255,255));
            }
        }
    }
    qDebug() << QString("mCount [%1]").arg(mMap.count());
    foreach( int key, mMap.keys() )
        qDebug() << key << " = " << mMap[key];
}
