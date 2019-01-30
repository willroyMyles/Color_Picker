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
    inputCircle->setInitialColor(QColor(255,255,255));
  //  configureStylesheet();
}

void ColorView::configureView()
{
    auto layout = new QVBoxLayout;
    setLayout(layout);

    auto hlayoutWidget = new QGridLayout;
    auto hlayoutFormat = new QGridLayout;
    auto hlayoutSliders = new QGridLayout;
    auto hsvlayoutSliders = new QGridLayout;
    auto aLayout = new QGridLayout;
    auto hlayoutButton = new QGridLayout;

    auto hWidget = new  QWidget;
    auto hFormat = new  QWidget;
    auto hSliders = new QWidget;
    auto hsvSliders = new QWidget;
    auto hButton = new  QWidget;
    auto aWidget = new  QWidget;

    hWidget->setLayout(hlayoutWidget);
    hFormat->setLayout(hlayoutFormat);
    hSliders->setLayout(hlayoutSliders);
    hsvSliders->setLayout(hsvlayoutSliders);
    hButton->setLayout(hlayoutButton);
    aWidget->setLayout(aLayout);

    stackWidget = new QStackedWidget(this);
    
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
    auto hLabel = new QLabel("H");
    auto sLabel = new QLabel("S");
    auto vLabel = new QLabel("V");
    auto aLabel = new QLabel("A");
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
    layout->addWidget(aWidget, 3, 0);
    layout->addWidget(hButton, 4, 0);
    layout->setSpacing(0);


    
    aLayout->addWidget(aLabel,3,0, 1, 1);
    aLayout->addWidget(aSlider,3,1, 1, 1);
    aLayout->addWidget(aBox,3,2, 1, 1);
    aLayout->setContentsMargins(12, 0, 12, 0);
    
    hlayoutWidget->addWidget(circle, 0, 0);
    hlayoutWidget->addWidget(display, 1, 0);

    hlayoutFormat->addWidget(format, 0, 0);
    hlayoutFormat->addWidget(lineEditor, 1, 0);
    hlayoutFormat->addWidget(comboBox,1,1);

    hlayoutSliders->addWidget(rLabel, 0, 0);
    hlayoutSliders->addWidget(gLabel, 1, 0);
    hlayoutSliders->addWidget(bLabel, 2, 0);
//    hlayoutSliders->addWidget(aLabel, 3, 0);
    hsvlayoutSliders->addWidget(hLabel,0,0);
    hsvlayoutSliders->addWidget(sLabel,1,0);
    hsvlayoutSliders->addWidget(vLabel,2,0);

    hlayoutSliders->addWidget(rSlider, 0, 1);
    hlayoutSliders->addWidget(gSlider, 1, 1);
    hlayoutSliders->addWidget(bSlider, 2, 1);
//    hlayoutSliders->addWidget(aSlider, 3, 1);
    hsvlayoutSliders->addWidget(hSlider,0,1);
    hsvlayoutSliders->addWidget(sSlider,1,1);
    hsvlayoutSliders->addWidget(vSlider,2,1);

    hlayoutSliders->addWidget(rBox, 0, 2);
    hlayoutSliders->addWidget(gBox, 1, 2);
    hlayoutSliders->addWidget(bBox, 2, 2);
//    hlayoutSliders->addWidget(aBox, 3, 2);
    hsvlayoutSliders->addWidget(hBox,0,2);
    hsvlayoutSliders->addWidget(sBox,1,2);
    hsvlayoutSliders->addWidget(vBox,2,2);
    
    stackWidget->addWidget(hSliders);
    stackWidget->addWidget(hsvSliders);
    stackWidget->setContentsMargins(0,0,0,0);


    hlayoutButton->addWidget(confirm, 0, 0);
    hlayoutButton->addWidget(cancel, 0, 1 );



}

void ColorView::configureStylesheet() {

    setStyleSheet(
            "background: rgba(25,25,25,1);;"
            );
}

void ColorView::configureConnections()
{

    connect(display, &ColorDisplay::pick,[=](){
        createOverlay();
    });
    
    
    rBox->setRange(0, 255);
    bBox->setRange(0, 255);
    gBox->setRange(0, 255);
    hBox->setRange(0, 359);
    sBox->setRange(0, 100);
    vBox->setRange(0, 100);
    aBox->setRange(0, 255);
    rSlider->setRange(rBox->minimum(),rBox->maximum());
    gSlider->setRange(gBox->minimum(),gBox->maximum());
    bSlider->setRange(bBox->minimum(),bBox->maximum());
    hSlider->setRange(hBox->minimum(),hBox->maximum());
    sSlider->setRange(sBox->minimum(),sBox->maximum());
    vSlider->setRange(vBox->minimum(),vBox->maximum());
    aSlider->setRange(aBox->minimum(),aBox->maximum());
    aSlider->setValue(255);
    
    
    
    connect(rSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(rBox, value);
        inputCircle->setRed(value);
    });
    connect(gSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(gBox, value);
        inputCircle->setGreen(value);
        
    });
    connect(bSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(bBox, value);
        inputCircle->setBlue(value);
    });
    connect(hSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(hBox, value);
        inputCircle->setHue(value);
    });
    connect(sSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(sBox, value);
        inputCircle->setSaturation(value*factor);
        
    });
    connect(vSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(vBox, value);
        inputCircle->setValue(value*factor);
    });
    connect(aSlider, &QSlider::valueChanged,[=](int value){
        sliderUpdatesSpinboxWithoutSignal(aBox, value);
        inputCircle->setAlpha(value);
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
    connect(hBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(hSlider, value);
    });
    connect(sBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(sSlider, value);
    });
    connect(vBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(vSlider, value);
    });
    connect(aBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        spinboxUpdatesSliderWithoutSignal(aSlider, value);
    });
    
    connect(inputCircle,&InputCircle::positionChanged,[=](QColor col){
        this->colorCircleUpdatesSliderWithoutNotification(rSlider, rBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(gSlider, gBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(bSlider, bBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(hSlider, hBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(sSlider, sBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(vSlider, vBox, col);
        this->colorCircleUpdatesSliderWithoutNotification(aSlider, aBox, col);
    });

    connect(inputCircle, &InputCircle::updateColorText,[=](QColor col){
        display->color = col;
        display->setToolTip(col.name());
        display->repaint();
        this->lineEditor->setText(colorNameFromSpac(col));
    });
    
    connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index){
        if(index == 0) {
            spec = QColor::Rgb;
            stackWidget->setCurrentIndex(index);
        }
        if(index == 1){
             spec = QColor::Hsv;
            stackWidget->setCurrentIndex(index);
        }
        if(index == 2){
             spec = QColor::Cmyk; // subs for hex
            stackWidget->setCurrentIndex(0); // default to rgb
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
    if(slider == hSlider)     inputCircle->setHue(value);
    if(slider == sSlider)     inputCircle->setSaturation(value*factor);
    if(slider == vSlider)     inputCircle->setValue(value*factor);
    if(slider == aSlider)     inputCircle->setAlpha(value);
    slider->blockSignals(false);
}

void ColorView::colorCircleUpdatesSliderWithoutNotification(QSlider *slider, QSpinBox *box, QColor &color) {
    slider->blockSignals(true);
    box->blockSignals(true);
    
    if(slider == rSlider)   slider->setValue(color.red());
    if(slider == gSlider)   slider->setValue(color.green());
    if(slider == bSlider)   slider->setValue(color.blue());
    if(slider == hSlider)   slider->setValue(color.hue());
    if(slider == sSlider)   slider->setValue(color.saturation()/factor);
    if(slider == vSlider)   slider->setValue(color.value()/factor);
    if(slider == aSlider)   slider->setValue(color.alpha());
    if(box == rBox)         box->setValue(color.red());
    if(box == gBox)         box->setValue(color.green());
    if(box == bBox)         box->setValue(color.blue());
    if(box == hBox)         box->setValue(color.hue());
    if(box == sBox)         box->setValue(color.saturation()/factor);
    if(box == vBox)         box->setValue(color.value()/factor);
    if(box == aBox)         box->setValue(color.alpha());
    
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

void ColorView::createOverlay() {
    
    
    
    int num = QApplication::desktop()->screenCount();
    
    for (int i =0 ; i< num; i++){
        auto geo =  QApplication::desktop()->screenGeometry(i);
        auto overlay = new ColorOverlay(geo,this);
        overlay->show();
        
        connect(overlay, &ColorOverlay::closeWindow,[=](){
            for( auto win : this->findChildren<ColorOverlay*>()){
                qDebug() << "found";
                win->close();
                win->deleteLater();
            }
        });
        
        
    }

    


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


   // if(!image)
        image = new QImage(250, 250, QImage::Format_ARGB32_Premultiplied);

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
  //  padding = parent->padding;
    color = parent->color;
    if(parent) this->parent = parent;
  //  move(offset, offset);

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
    qDebug() << pos;
    color = getCurrentColorFromPosition();
    emit positionChanged(color);
    emit updateColorText(color);
}

QColor InputCircle::getCurrentColorFromPosition() {
    int d = qPow(pos.rx() - centerPoint.rx(), 2) + qPow(pos.ry() - centerPoint.ry(), 2);
    auto saturation = (qSqrt(d) / radius)*255.0f;
    qreal theta = qAtan2(pos.ry() - centerPoint.ry(), pos.rx() - centerPoint.rx());
    theta = (180 + 90 + (int)qRadiansToDegrees(theta)) % 360;
    if (saturation >= 255)    saturation = 255;
    if (saturation <= 2)    saturation = 0;
    if (colorValue >= 255)    colorValue = 255;
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
    emit colorChanged(color);
    emit updateColorText(color);
    repaint();
}

void InputCircle::setRed(int red) {
    color.setRed(red);
    checkColorValue();
    drawIndicatorCircle(color);
}

void InputCircle::setGreen(int green) {
    color.setGreen(green);
    checkColorValue();
    drawIndicatorCircle(color);
}

void InputCircle::setBlue(int blue) {
    color.setBlue(blue);
    checkColorValue();
    drawIndicatorCircle(color);
}

void InputCircle::setAlpha(int alpha) {
    this->alpha = alpha;
    color.setAlpha(alpha);
    parent->setAlpha(alpha);
    checkColorValue();
    drawIndicatorCircle(color);
}

void InputCircle::mouseReleaseEvent(QMouseEvent *) {
    drawSmallDot = true;
    this->repaint();
}

void InputCircle::setHue(int hue) {
    color.setHsv(hue, color.saturation(), color.value(), alpha);
    checkColorValue();
    drawIndicatorCircle(color);
}

void InputCircle::setSaturation(int saturation) {
    color.setHsv(color.hue(), saturation, color.value(), alpha);
    checkColorValue();
    drawIndicatorCircle(color);
}

void InputCircle::setValue(int value) {
    color.setHsv(color.hue(), color.saturation(), value, alpha);
    checkColorValue();
    drawIndicatorCircle(color);
}

void InputCircle::setInitialColor(QColor col) {
    this->color = col;
    drawIndicatorCircle(col);
    emit positionChanged(col);
}

void InputCircle::checkColorValue() {
    if(colorValue != color.value()){
        colorValue = color.value();
        parent->colorValue = color.value();
        parent->drawImage();
    }
}




















ColorDisplay::ColorDisplay(QWidget *parent) : QWidget(parent) {
    setMinimumHeight(50);
    auto layout = new QHBoxLayout;
    setLayout(layout);
    
    auto button = new QPushButton(this);
    button->setIcon(QIcon((":/images/dropper.png")));
    button->setIconSize({30,30});
    
    layout->addStretch();
    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);
    
    connect(button, &QPushButton::clicked,[=](){
        emit pick();
    });
}

void ColorDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(QRect(0,0,width(),height()), color);
}



ColorOverlay::ColorOverlay(QRect screenGeometry, QWidget *parent): QWidget() {
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowOpacity(0.9);
    setMouseTracking(true);
    
    move(screenGeometry.x(), screenGeometry.y());
    resize(screenGeometry.width(), screenGeometry.height());
}

void ColorOverlay::mousePressEvent(QMouseEvent *) {
    qDebug() << "closed";
    emit closeWindow();
}

void ColorOverlay::mouseMoveEvent(QMouseEvent *) {

}

void ColorOverlay::mouseReleaseEvent(QMouseEvent *) {
    this->close();
}



