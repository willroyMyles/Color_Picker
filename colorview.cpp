#include "colorview.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QtMath>
#include <QDebug>

ColorView::ColorView(QWidget *parent) : QWidget(parent)
{
    configureView();
}

void ColorView::configureView()
{
    auto layout = new QGridLayout;
    setLayout(layout);

    auto hlayoutWidget = new QGridLayout;
    auto hlayoutFormat = new QGridLayout;
    auto hlayoutSliders = new QGridLayout;
    auto hlayoutButton = new QGridLayout;

    auto hWidget = new  QWidget;
    auto hFormat = new  QWidget;
    auto hSliders = new QWidget;
    auto hButton = new  QWidget;

    hWidget->setLayout(hlayoutWidget);
    hFormat->setLayout(hlayoutFormat);
    hSliders->setLayout(hlayoutSliders);
    hButton->setLayout(hlayoutButton);

    rSlider = new QSlider(Qt::Horizontal, this);
    gSlider = new QSlider(Qt::Horizontal, this);
    bSlider = new QSlider(Qt::Horizontal, this);
    aSlider = new QSlider(Qt::Horizontal, this);

    rBox = new QSpinBox(this);
    gBox = new QSpinBox(this);
    bBox = new QSpinBox(this);
    aBox = new QSpinBox(this);

    auto rLabel = new QLabel("R");
    auto gLabel = new QLabel("G");
    auto bLabel = new QLabel("B");
    auto aLabel = new QLabel("A");
    auto format = new QLabel("Format");

    lineEditor = new QLineEdit(this);
    comboBox = new QComboBox(this);

    QStringList stringList;
    stringList << "RGB" << "HSV" << "HEX" ;
    comboBox->addItems(stringList);

    confirm = new QPushButton("confirm", this);
    cancel = new QPushButton("cancel", this);

    auto circle = new ColorCircle();

    layout->addWidget(hWidget, 0, 0);
    layout->addWidget(hFormat, 1, 0);
    layout->addWidget(hSliders, 2,0);
    layout->addWidget(hButton, 3, 0);

    hlayoutWidget->addWidget(circle, 0, 0);

    hlayoutFormat->addWidget(format, 0, 0);
    hlayoutFormat->addWidget(lineEditor, 1, 0);
    hlayoutFormat->addWidget(comboBox,1,1);

    hlayoutSliders->addWidget(rLabel, 0, 0);
    hlayoutSliders->addWidget(gLabel, 1, 0);
    hlayoutSliders->addWidget(bLabel, 2, 0);
    hlayoutSliders->addWidget(aLabel, 3, 0);

    hlayoutSliders->addWidget(rSlider, 0, 1);
    hlayoutSliders->addWidget(gSlider, 1, 1);
    hlayoutSliders->addWidget(bSlider, 2, 1);
    hlayoutSliders->addWidget(aSlider, 3, 1);

    hlayoutSliders->addWidget(rBox, 0, 2);
    hlayoutSliders->addWidget(gBox, 1, 2);
    hlayoutSliders->addWidget(bBox, 2, 2);
    hlayoutSliders->addWidget(aBox, 3, 2);

    hlayoutButton->addWidget(confirm, 0, 0);
    hlayoutButton->addWidget(cancel, 0, 1 );



}

ColorCircle::ColorCircle(QWidget *parent) : QWidget(parent)
{

    setGeometry(0, 0, 250 , 250 );
    radius = 250 / 2 ;
    centerPoint.setX(radius );
    centerPoint.setY(radius );
    colorValue = 255;


    drawImage();
    configureLabels();




 //   setStyleSheet("background: rgba(20,20,20,1);");
}

QImage *ColorCircle::drawImage()
{
    image = new QImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
    //draw color circle image
        for (int i = 0; i < width(); i++) {
            for (int j = 0; j < width(); j++) {

                QPoint point(i, j);
                int d = qPow(point.rx() - centerPoint.rx(), 2) + qPow(point.ry() - centerPoint.ry(), 2);
                if (d <= qPow(radius, 2)) {

                    saturation = (qSqrt(d) / radius)*255.0f;
                    qreal theta = qAtan2(point.ry() - centerPoint.ry(), point.rx() - centerPoint.rx());

                    theta = (180 + 90 + static_cast<int>(qRadiansToDegrees(theta))) % 360;
                    color.setHsv(theta, saturation, colorValue, alpha);
                    image->setPixelColor(i, j, color);
                }
                else {
                    color.setRgb(26, 26, 26,0);
                    image->setPixelColor(i, j, color);
                }
            }
        }
        return image;
}

void ColorCircle::configureLabels()
{
    auto layout = new QGridLayout;
    setLayout(layout);

    auto label = new QLabel("hello");
    label->setPixmap(QPixmap::fromImage(*image));

    auto colorLabel = new QLabel;
    colorLabel->setText(color.name());

    auto holder = new QWidget;
    auto holderLayout = new QGridLayout;
    holder->setLayout(holderLayout);

    pickButton = new QPushButton("PICK");

    auto f = label->font();
    f.setWeight(65);
    f.setPixelSize(48);
    colorLabel->setFont(f);

    holderLayout->addWidget(colorLabel, 0, 0, 1, 0, Qt::AlignRight | Qt::AlignBottom);
    holderLayout->addWidget(pickButton, 1, 1);

    layout->addWidget(label, 0, 0);
    layout->addWidget(holder, 0, 1, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);
}

