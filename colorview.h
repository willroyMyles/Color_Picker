
#include <QComboBox>
#include <QGraphicsEffect>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QStackedWidget>
#include <QWidget>



class ColorCircle;
class ColorDisplay : public QWidget
{
    Q_OBJECT
public:
    ColorDisplay(QWidget *parent = Q_NULLPTR);
    QColor color;
    
protected:
    void paintEvent(QPaintEvent *) override;
};

class InputCircle : public QWidget
{
    Q_OBJECT
public:
    InputCircle(ColorCircle *parent = Q_NULLPTR);
    int offset;
    QColor color;

private:
    bool drawSmallDot = false;
    
    int squareSize;
    int radius;
    int padding;
    int alpha;
    
    QPoint centerPoint;
    QPoint pos;
    
    QColor currentColor;
    QColor initialColor;
    int colorValue = 255;
    
    void setCirclePosition(QMouseEvent *);
    QColor getCurrentColorFromPosition();
    void drawIndicatorCircle(QColor color);
    
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
    
public slots:
    void setAlpha(int alpha);
private:
    QImage *image;

    qreal saturation;
    qreal alpha = 255.0;

    QImage* drawImage();


protected:
    void paintEvent(QPaintEvent *)override;
};



class ColorView : public QWidget
{
    Q_OBJECT
public:
    explicit ColorView(QWidget *parent = nullptr);


private:
    QSlider *rSlider;
    QSlider *gSlider;
    QSlider *bSlider;
    QSlider *aSlider;
    
    QSpinBox *rBox;
    QSpinBox *gBox;
    QSpinBox *bBox;
    QSpinBox *aBox;

    QSlider *hSlider;
    QSlider *sSlider;
    QSlider *vSlider;
    
    QSpinBox *hBox;
    QSpinBox *sBox;
    QSpinBox *vBox;
    
    QStackedWidget *stackWidget;

    QLineEdit *lineEditor;
    QComboBox *comboBox;

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

signals:

public slots:
};



