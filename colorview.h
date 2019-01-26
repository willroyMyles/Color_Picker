#ifndef COLORVIEW_H
#define COLORVIEW_H

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>


class ColorCircle : public QWidget
{
    Q_OBJECT
public:
    explicit ColorCircle(QWidget *parent = nullptr);

private:
    QImage *image;

    QColor color;

    QPoint centerPoint;

    int colorValue = 255;
    int radius;
    int offset;
    int padding;
    int squareSize;

    qreal saturation;
    qreal alpha = 255.0;

    QPushButton *pickButton;

    QImage* drawImage();
    void configureLabels();


protected:
    void paintEvent(QPaintEvent *)override;
};



class ColorView : public QWidget
{
    Q_OBJECT
public:
    explicit ColorView(QWidget *parent = nullptr);
    void configureView();



private:
    QSlider *rSlider;
    QSlider *gSlider;
    QSlider *bSlider;
    QSlider *aSlider;

    QSpinBox *rBox;
    QSpinBox *gBox;
    QSpinBox *bBox;
    QSpinBox *aBox;

    QLineEdit *lineEditor;
    QComboBox *comboBox;

    QPushButton *confirm;
    QPushButton *cancel;

    ColorCircle *circle;



    void configureStylesheet();

signals:

public slots:
};

#endif // COLORVIEW_H


