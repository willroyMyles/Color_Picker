#include "colorview.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QtMath>
#include <QDebug>
#include <QPainter>
#include <QGraphicsEffect>
#include <QMouseEvent>

ColorView::ColorView(QWidget *parent) : QWidget(parent)
{
    configureView();
    configureConnections();
  //  configureStylesheet();
}

void ColorView::configureView()
{
    auto layout = new QGridLayout;
    setLayout(layout);

    auto hlayoutWidget = new QGridLayout;
    auto hlayoutFormat = new QGridLayout;
    auto hlayoutSliders = new QGridLayout;
    auto hsvlayoutSliders = new QGridLayout;
    auto hlayoutButton = new QGridLayout;
    auto alphaLayout = new QGridLayout;

    auto hWidget = new  QWidget;
    auto hFormat = new  QWidget;
    auto hSliders = new QWidget;
    auto hsvSliders = new QWidget;
    auto alphaWidget = new QWidget;
    auto hButton = new  QWidget;
    
    stackWidget = new QStackedWidget;

    hWidget->setLayout(hlayoutWidget);
    hFormat->setLayout(hlayoutFormat);
    hSliders->setLayout(hlayoutSliders);
    hsvSliders->setLayout(hsvlayoutSliders);
    hButton->setLayout(hlayoutButton);
    alphaWidget->setLayout(alphaLayout);

    rSlider = new QSlider(Qt::Horizontal, this);
    gSlider = new QSlider(Qt::Horizontal, this);
    bSlider = new QSlider(Qt::Horizontal, this);
    hSlider = new QSlider(Qt::Horizontal, this);
    sSlider = new QSlider(Qt::Horizontal, this);
    vSlider = new QSlider(Qt::Horizontal, this);
    aSlider = new QSlider(Qt::Horizontal, this);

    rBox = new QSpinBox(this);
    gBox = new QSpinBox(this);
    bBox = new QSpinBox(this);
    hBox = new QSpinBox(this);
    sBox = new QSpinBox(this);
    vBox = new QSpinBox(this);
    aBox = new QSpinBox(this);

    auto rLabel = new QLabel("R");
    auto gLabel = new QLabel("G");
    auto bLabel = new QLabel("B");
    auto aLabel = new QLabel("A");
    auto hLabel = new QLabel("H");
    auto sLabel = new QLabel("S");
    auto vLabel = new QLabel("V");
    auto format = new QLabel("Format");

    lineEditor = new QLineEdit(this);
    comboBox = new QComboBox(this);

    QStringList stringList;
    stringList << "RGB" << "HSV" << "HEX" ;
    comboBox->addItems(stringList);

    confirm = new QPushButton("confirm", this);
    cancel = new QPushButton("cancel", this);
    
    display = new ColorDisplay;
    circle = new ColorCircle();
    inputCircle = new InputCircle(circle);
    inputCircle->setStyleSheet("QWidget{background: rgba(20,20,20,1);}");
    inputCircle->move(inputCircle->offset,inputCircle->offset);

    layout->addWidget(hWidget, 0, 0);
    layout->addWidget(hFormat, 1, 0);
    layout->addWidget(stackWidget, 2,0);
    //alpha slider
    layout->addWidget(alphaWidget, 3, 0);
    layout->addWidget(hButton, 4, 0);

    hlayoutWidget->addWidget(circle, 0, 0);
    hlayoutWidget->addWidget(display, 1, 0);

    hlayoutFormat->addWidget(format, 0, 0);
    hlayoutFormat->addWidget(lineEditor, 1, 0);
    hlayoutFormat->addWidget(comboBox,1,1);
    
    hsvlayoutSliders->addWidget(hLabel, 0, 0);
    hsvlayoutSliders->addWidget(sLabel, 1, 0);
    hsvlayoutSliders->addWidget(vLabel, 2, 0);
    
    hsvlayoutSliders->addWidget(hSlider, 0, 1);
    hsvlayoutSliders->addWidget(sSlider, 1, 1);
    hsvlayoutSliders->addWidget(vSlider, 2, 1);
    
    hsvlayoutSliders->addWidget(hBox, 0, 2);
    hsvlayoutSliders->addWidget(sBox, 1, 2);
    hsvlayoutSliders->addWidget(vBox, 2, 2);

    hlayoutSliders->addWidget(rLabel, 0, 0);
    hlayoutSliders->addWidget(gLabel, 1, 0);
    hlayoutSliders->addWidget(bLabel, 2, 0);
    alphaLayout->addWidget(aLabel, 3, 0);

    hlayoutSliders->addWidget(rSlider, 0, 1);
    hlayoutSliders->addWidget(gSlider, 1, 1);
    hlayoutSliders->addWidget(bSlider, 2, 1);
    alphaLayout->addWidget(aSlider, 3, 1);

    hlayoutSliders->addWidget(rBox, 0, 2);
    hlayoutSliders->addWidget(gBox, 1, 2);
    hlayoutSliders->addWidget(bBox, 2, 2);
    alphaLayout->addWidget(aBox, 3, 2);

    hlayoutButton->addWidget(confirm, 0, 0);
    hlayoutButton->addWidget(cancel, 0, 1 );
    
    stackWidget->addWidget(hSliders);
    stackWidget->addWidget(hsvSliders);



}

void ColorView::configureStylesheet() {

    setStyleSheet(
            "background: rgba(25,25,25,1);;"
            );
}

void ColorView::configureConnections()
{
    rBox->setRange(0, 255);
    bBox->setRange(0, 255);
    gBox->setRange(0, 255);
    aBox->setRange(0, 255);
    rSlider->setRange(rBox->minimum(),rBox->maximum());
    gSlider->setRange(gBox->minimum(),gBox->maximum());
    bSlider->setRange(bBox->minimum(),bBox->maximum());
    aSlider->setRange(aBox->minimum(),aBox->maximum());
    
    
    
    connect(rSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(rBox, value);
    });
    connect(gSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(gBox, value);
    });
    connect(bSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(bBox, value);
    });
    connect(aSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(aBox, value);
    });
    
    connect(rSlider, SIGNAL(valueChanged(int)),inputCircle, SLOT(setRed(int)));
    connect(gSlider, SIGNAL(valueChanged(int)),inputCircle, SLOT(setGreen(int)));
    connect(bSlider, SIGNAL(valueChanged(int)),inputCircle, SLOT(setBlue(int)));
    //connect(aSlider, SIGNAL(valueChanged(int)),circle, SLOT(setAlpha(int)));
    connect(aSlider, &QSlider::valueChanged, [=](int val){
        circle->setAlpha(val);
        inputCircle->setAlpha(val);
    });
    
    
    connect(rBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(rSlider, value);
    });
    connect(gBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(gSlider, value);
    });
    connect(bBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(bSlider, value);
    });
    connect(aBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(aSlider, value);
    });
    
    connect(inputCircle,&InputCircle::positionChanged,[=](QColor col){
        this->colorCircleUpdatesSliderWithoutNotification(rSlider, rBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(gSlider, gBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(bSlider, bBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(aSlider, aBox, col);
    });

    connect(inputCircle, &InputCircle::updateColorText,[=](QColor col){
        display->color = col;
        display->repaint();
        this->lineEditor->setText(colorNameFromSpac(col));
    });
    
    connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index){
        if(index == 0){
            spec = QColor::Rgb;
            stackWidget->setCurrentIndex(0);
        }
        if(index == 1){
            spec = QColor::Hsv;
            stackWidget->setCurrentIndex(1);
        }
        if(index == 2){
            spec = QColor::Cmyk; // subs for hex
            stackWidget->setCurrentIndex(0);
        }
        this->lineEditor->setText(colorNameFromSpac(inputCircle->color));
    });
    
    
}

void ColorView::spinboxUpdatesSliderWithoutSignal(QSlider *slider, int value) {
    slider->blockSignals(true);
    slider->setValue(value);
    if(slider == rSlider)     inputCircle->setRed(value);
    if(slider == gSlider)     inputCircle->setGreen(value);
    if(slider == bSlider)     inputCircle->setBlue(value);
    if(slider == aSlider)     inputCircle->setAlpha(value);
    slider->blockSignals(false);
}

void ColorView::colorCircleUpdatesSliderWithoutNotification(QSlider *slider, QSpinBox *box, QColor &color) {
    slider->blockSignals(true);
    box->blockSignals(true);
    
    if(slider == rSlider)   rSlider->setValue(color.red());
    if(slider == gSlider)   gSlider->setValue(color.green());
    if(slider == bSlider)   bSlider->setValue(color.blue());
    if(slider == aSlider)   aSlider->setValue(color.alpha());
    if(box == rBox)         rBox->setValue(color.red());
    if(box == gBox)         gBox->setValue(color.green());
    if(box == bBox)         bBox->setValue(color.blue());
    if(box == aBox)         aBox->setValue(color.alpha());
    
    slider->blockSignals(false);
    box->blockSignals(false);

}

QString ColorView::colorNameFromSpac(QColor col) {
    QString name;
    switch (spec)
    {
        case QColor::Rgb:
            name = QString("rgb(%1, %2, %3)").arg(col.red()).arg(col.green()).arg(col.blue());
            break;
        case QColor::Hsv:
            name = QString("hsv(%1, %2%, %3%)").arg(col.hue()).arg((int)(col.saturation()/2.55)).arg((int)(col.value()/2.55));
            break;
        case QColor::Hsl:
            break;
        case QColor::Cmyk:
            name = col.name();
            break;
        default:
            break;
    }
    return name;
}


void ColorView::sliderUpdatesSpinboxWithoutSignal(QSpinBox *box, int value) {
    box->blockSignals(true);
    box->setValue(value);
    box->blockSignals(false);
}






ColorCircle::ColorCircle(QWidget *parent) : QWidget(parent)
{
    squareSize = 250;
    radius = squareSize / 2 ;
    centerPoint.setX(radius );
    centerPoint.setY(radius );
    colorValue = 255;
    offset = 5;
    padding = offset*2;
    
    auto redefinedSize = squareSize + padding;
    setMinimumSize({redefinedSize,redefinedSize});

    drawImage();
}

QImage *ColorCircle::drawImage()
{


    if(!image)  image = new QImage(250, 250, QImage::Format_ARGB32_Premultiplied);

    //draw color circle image
        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {

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
                    color.setRgb(126, 26, 26,0);
                    image->setPixelColor(i, j, color);
                }
            }
        }
    
        return image;
}

void ColorCircle::paintEvent(QPaintEvent *event) {

    QWidget::paintEvent( event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);

    painter.drawImage(offset , offset, *image);

    painter.setPen(QPen(QColor(250,250,250),2));
    painter.drawEllipse( offset, offset, image->width(), image->height());

    qDebug() << "called";
}

void ColorCircle::setAlpha(int alpha) {
    this->alpha = alpha;
    drawImage();
    repaint();
}



InputCircle::InputCircle(ColorCircle *parent) : QWidget(parent) {
    
    squareSize = parent->squareSize;
    radius = parent->radius;
    centerPoint = parent->centerPoint;
    offset = parent->offset;
    padding = parent->padding;
    color = parent->color;
    
    setMinimumSize({squareSize,squareSize});
}

void InputCircle::mousePressEvent(QMouseEvent *event) {
    drawSmallDot = false;
    setCirclePosition(event);
    QWidget::mousePressEvent(event);
    repaint();
}

void InputCircle::mouseMoveEvent(QMouseEvent *event) {
    setCirclePosition(event);
    QWidget::mouseMoveEvent(event);
}

void InputCircle::setCirclePosition(QMouseEvent *event) {
    QVector2D mousePos(event->pos().x(), event->pos().y());
    auto centerPos = QVector2D(centerPoint.x(), centerPoint.y());
    auto diff = mousePos - centerPos;
    if (diff.length() > radius)     diff = diff.normalized() * radius;
    auto position = centerPos + diff;
    pos.setX(position.x());
    pos.setY(position.y());
    color = getCurrentColorFromPosition();
    emit positionChanged(color);
    emit updateColorText(color);
}

QColor InputCircle::getCurrentColorFromPosition() {
    int d = qPow(pos.rx() - centerPoint.rx(), 2) + qPow(pos.ry() - centerPoint.ry(), 2);
    auto saturation = (qSqrt(d) / radius)*255.0f;
    qreal theta = qAtan2(pos.ry() - centerPoint.ry(), pos.rx() - centerPoint.rx());
    theta = (180 + 90 + (int)qRadiansToDegrees(theta)) % 360;
    if (saturation >= 253)    saturation = 255;
    if (saturation <= 2)    saturation = 0;
    if (colorValue >= 253)    colorValue = 255;
    if (colorValue <= 2)    colorValue = 0;
    
    color.setHsv(theta, saturation, colorValue, this->alpha);
    return color;
}

void InputCircle::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    
    if(drawSmallDot){
        painter.setPen(QPen(QColor(20,20,20),2));
        painter.drawEllipse(QPoint(pos.x(), pos.y()), 2, 2);
    }
}

void InputCircle::drawIndicatorCircle(QColor color) {
    drawSmallDot = true;
    
    qreal theta = qDegreesToRadians((qreal)color.hsvHue() + 90);
    auto sat = color.hsvSaturation() / 255.0f * radius;
    qreal x = sat * qCos(theta) + centerPoint.x();
    qreal y = sat * qSin(theta) + centerPoint.y();
    pos = QPoint(x, y);
    this->colorValue = color.value();
    emit colorChanged(color);
    emit updateColorText(color);
//    emit positionChanged(color);
    qDebug() << color;
    repaint();
}

void InputCircle::setRed(int red) {
    color.setRed(red);
    drawIndicatorCircle(color);
}

void InputCircle::setGreen(int green) {
    color.setGreen(green);
    drawIndicatorCircle(color);
}

void InputCircle::setBlue(int blue) {
    color.setBlue(blue);
    drawIndicatorCircle(color);
}

void InputCircle::setAlpha(int alpha) {
    this->alpha = alpha;
    color.setAlpha(alpha);
    drawIndicatorCircle(color);
}

void InputCircle::mouseReleaseEvent(QMouseEvent *) {
    drawSmallDot = true;
    this->repaint();
}

void InputCircle::setHue(int hue) {
    color.setHsv(hue, color.saturation(), color.value());
    drawIndicatorCircle(color);
}

void InputCircle::setSaturation(int saturation) {
    color.setHsv(color.hue(), saturation, color.value());
    drawIndicatorCircle(color);
}

void InputCircle::setValue(int value) {
    color.setHsv(color.hue(), color.saturation(), value);
    drawIndicatorCircle(color);
}


















ColorDisplay::ColorDisplay(QWidget *parent) : QWidget(parent) {
    setMinimumHeight(50);
}

void ColorDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(QRect(0,0,width(),height()), color);
}

