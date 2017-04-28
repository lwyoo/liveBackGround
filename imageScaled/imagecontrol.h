#ifndef IMAGECONTROL_H
#define IMAGECONTROL_H

#include <QObject>
#include <QImage>
#include <QLabel>
#include <QDebug>
#define RESIZE_WIDTH 500
#define RESIZE_HEIGHT 500

class ImageControl : public QObject
{
public:

    enum Image_Control_State{
        /*
         *
         *
         *
         */
    };

    ImageControl(QObject* parent = 0);
    ~ImageControl();
    //init
    void imageControlInit();
    //stop
    void imageControlStop();


    inline void setNaturalWidth(int nWidth)
    {
        qDebug() << QString("set Natural Width [%1]").arg(nWidth);
        mNaturalImgWidth = nWidth;
    }

    inline  int getNaturalWidth(void)
    {
        return mNaturalImgWidth;
    }

    inline void setNaturalHeight(int nHeight)
    {
        qDebug() << QString("set Natural Height [%1]").arg(nHeight);
        mNaturalImgHeight = nHeight;
    }

    inline int getNaturalHeight(void){
        return mNaturalImgHeight;
    }




    static ImageControl* instance();
    bool setImage(QString  imgPath);
    void setResizeImage(int imgWidth = RESIZE_WIDTH , int imgHeight =RESIZE_HEIGHT);
    void setImageRevise(int reviseLevel);

    bool isImageResize(); //resize need?


    void getDominantColor(QString  imgPath); // provide color for QML


    void showImage();

    void imgCalculate();

    void testCode();
private:
    char*         cImgPath;
    int             mNaturalImgWidth;
    int             mNaturalImgHeight;
    int             mReviseLevel;
    QImage img;
    QLabel mlb;
    QMap<QRgb , int> mMap; // rgb , count
    //test Code


};

#endif // IMAGECONTROL_H
