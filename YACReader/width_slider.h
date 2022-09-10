#ifndef WIDTH_SLIDER_H
#define WIDTH_SLIDER_H

#include <QWidgetAction>
#include <QWidget>

class QLabel;
class QSlider;

class YACReaderSlider : public QWidget
{
    Q_OBJECT
private:
    QLabel *percentageLabel;
    QSlider *slider;

public:
    YACReaderSlider(QWidget *parent = nullptr);
    void show();

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void paintEvent(QPaintEvent *) override;

public slots:
    void updateText(int value);
    void updateZoomRatio(int value);
    void resetValueToDefault();

signals:
    void zoomRatioChanged(int value);
};

class YACReaderSliderAction : public QWidgetAction
{
    Q_OBJECT
private:
    YACReaderSlider *widget;

public:
    YACReaderSliderAction(QWidget *parent = nullptr);

public slots:
    void updateText(int value);
    void updateZoomRatio(int value);

signals:
    void zoomRatioChanged(int value);
};

#endif
