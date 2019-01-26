#include "colorview.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QtMath>
#include <QDebug>
#include <QPainter>
#include <QGraphicsEffect>

ColorView::ColorView(QWidget *parent) : QWidget(parent)
{
    configureView();
    configureStylesheet();
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

    circle = new ColorCircle();

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

void ColorView::configureStylesheet() {

    setStyleSheet(
            "background: rgba(25,25,25,1);;"
            );
}

ColorCircle::ColorCircle(QWidget *parent) : QWidget(parent)
{
    squareSize = 250;
    radius = minimumSize().width() / 2 ;
    centerPoint.setX(radius );
    centerPoint.setY(radius );
    colorValue = 255;
    offset = 5;
    padding = offset*2;
    auto redefinedSize = squareSize + padding;
    setMinimumSize({redefinedSize,redefinedSize});


    drawImage();
  //  configureLabels();

}

QImage *ColorCircle::drawImage()
{
    image = new QImage(squareSize, squareSize, QImage::Format_ARGB32_Premultiplied);
    //draw color circle image
        for (int i = offset; i < squareSize; i++) {
            for (int j = offset; j < squareSize; j++) {

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
    label->setStyleSheet("background: rgba(0,0,0,0);");

    auto effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(35);
    effect->setColor(QColor(0,0,0));
    effect->setOffset(0);
    label->setGraphicsEffect(effect);

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

void ColorCircle::paintEvent(QPaintEvent *event) {


    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);

    painter.drawImage(offset,offset, *image);

    painter.setPen(QPen(QColor(250,250,250),2));
    painter.drawEllipse( offset, offset, image->width(), image->height());
  //  QWidget::paintEvent( event);

    qDebug() << "called";
}

