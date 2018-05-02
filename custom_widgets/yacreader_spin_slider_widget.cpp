#include "yacreader_spin_slider_widget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

YACReaderSpinSliderWidget::YACReaderSpinSliderWidget(QWidget * parent,bool strechableSlider)
	:QWidget(parent),tracking(true)
{
	QHBoxLayout * layout = new QHBoxLayout;
	layout->addWidget(label = new QLabel(this),1);
	if(!strechableSlider)
	  layout->addStretch();
	spinBox = new QSpinBox(this);
	layout->addWidget(spinBox);
	slider = new QSlider(Qt::Horizontal,this);
	layout->addWidget(slider);
	if(strechableSlider)
	{
		layout->setStretchFactor(slider,0.85);
		layout->setStretchFactor(spinBox,0);
		layout->setStretchFactor(label,0.15);
	}

	connect(spinBox, SIGNAL(valueChanged(int)), slider,  SLOT(setValue(int)));
	connect(slider,  SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(valueWillChange(int)));
	connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(valueWillChangeFromSpinBox(int)));

	connect(slider, SIGNAL(sliderReleased()), this, SLOT(sliderRelease()));

	setLayout(layout);
}
void YACReaderSpinSliderWidget::valueWillChange(int v)
{
	Q_UNUSED(v)
	if(tracking)
		emit valueChanged(spinBox->value());
}

void YACReaderSpinSliderWidget::valueWillChangeFromSpinBox(int v)
{
	Q_UNUSED(v)
	if(!tracking && !slider->isSliderDown())
		emit valueChanged(spinBox->value());
}

void YACReaderSpinSliderWidget::sliderRelease()
{
	if(!tracking)
		emit valueChanged(spinBox->value());
}

void YACReaderSpinSliderWidget::setRange(int lowValue, int topValue, int step)
{
	spinBox->setMinimum(lowValue);
	spinBox->setMaximum(topValue);
	spinBox->setSingleStep(step);

	slider->setMinimum(lowValue);
	slider->setMaximum(topValue);
	slider->setSingleStep(step);
}

void YACReaderSpinSliderWidget::setValue(int value)
{
	disconnect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(valueWillChange(int)));
	spinBox->setValue(value);
	connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(valueWillChange(int)));
}

void YACReaderSpinSliderWidget::setText(const QString & text)
{
	label->setText(text);
}

int YACReaderSpinSliderWidget::getValue()
{
	return spinBox->value();
}

QSize YACReaderSpinSliderWidget::minimumSizeHint() const
{
	return QSize(270, 25);
}

void YACReaderSpinSliderWidget::setTracking(bool b)
{
	tracking = b;
	//slider->setTracking(b);
}
