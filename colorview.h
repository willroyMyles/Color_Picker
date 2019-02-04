
#include <QApplication>
#include <QDesktopWidget>
#include <QDialog>
#include <QComboBox>
#include <QGraphicsEffect>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QSlider>
#include <QSpinBox>
#include <QStackedWidget>
#include <QWidget>
#include <qwindowdefs_win.h>
#include "ss.h"

class Overlay : public QWidget
{
    Q_OBJECT
public:
    //accepts screen rect and widget as parent
    Overlay(QRect sg, QWidget* parent = Q_NULLPTR);
private:
signals:
    void color(QColor col);
    void closeWindow();
protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    bool eventFilter(QObject*, QEvent*) override;
};

class ColorCircle;
class ColorDisplay : public QWidget
{
    Q_OBJECT
public:
    ColorDisplay(QWidget *parent = Q_NULLPTR);
    QColor color;
protected:
    void paintEvent(QPaintEvent *) override;
signals:
    void pick();
};

class InputCircle : public QWidget
{
    Q_OBJECT
public:
    InputCircle(ColorCircle *parent = Q_NULLPTR);
    int offset;
    QColor color;
    
    void setInitialColor(QColor col);

private:
    bool drawSmallDot = false;
    
    int squareSize;
    int radius;
//    int padding;
    int alpha = 255;
    
    ColorCircle *parent;
    
    QPoint centerPoint;
    QPoint pos;
    
    QColor initialColor;
    int colorValue = 255;
    
    void setCirclePosition(QMouseEvent *);
    QColor getCurrentColorFromPosition();
    void drawIndicatorCircle(QColor color);
    void checkColorValue();
    
public slots:
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    void setAlpha(int alpha);
    void setHue(int hue);
    void setSaturation(int saturation);
    void setValue(int value);

signals:
    void positionChanged(QColor color); //emitted when color circle pressed
    void colorChanged(QColor color); //emitted when sliders change value
    void updateColorText(QColor color); // to update name text
    
protected:
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
};

class ColorCircle : public QWidget
{
    Q_OBJECT
public:
    explicit ColorCircle(QWidget *parent = nullptr);

    QColor color;
    
    QPoint centerPoint;
    
    int colorValue = 255;
    int radius;
    int offset;
    int padding;
    int squareSize;
    QImage* drawImage();

public slots:
    void setAlpha(int alpha);
    void setColor(QColor col);
private:
    QImage *image;
    qreal saturation;
    qreal alpha = 255.0;


protected:
    void paintEvent(QPaintEvent *)override;
};



class ColorView : public QWidget
{
    Q_OBJECT
public:
    explicit ColorView(QWidget *parent = nullptr);


private:
    const qreal factor = 2.55;
    
    QSlider *rSlider;
    QSlider *gSlider;
    QSlider *bSlider;
    QSlider *aSlider;
    QSlider *hSlider;
    QSlider *sSlider;
    QSlider *vSlider;
    
    QStackedWidget *stackWidget;

    QSpinBox *rBox;
    QSpinBox *gBox;
    QSpinBox *bBox;
    QSpinBox *hBox;
    QSpinBox *sBox;
    QSpinBox *vBox;
    QSpinBox *aBox;

    QLineEdit *lineEditor;
    QComboBox *comboBox;
    QList<Overlay*> *list;
    QPushButton *confirm;
    QPushButton *cancel;

    ColorDisplay *display;
    ColorCircle *circle;
    InputCircle *inputCircle;
    
    QColor::Spec spec = QColor::Rgb;
    

    QString colorNameFromSpac(QColor col);
    
    void configureView();
    void configureStylesheet();
    void configureConnections();
    void sliderUpdatesSpinboxWithoutSignal(QSpinBox *, int value);
    void spinboxUpdatesSliderWithoutSignal(QSlider *, int value);
    void colorCircleUpdatesSliderWithoutNotification(QSlider *, QSpinBox *, QColor &);
    
    void createOverlay();

signals:

public slots:
};



