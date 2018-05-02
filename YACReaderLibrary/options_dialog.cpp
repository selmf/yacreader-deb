#include "options_dialog.h"

#ifndef NO_OPENGL
#include "yacreader_flow_gl.h"
#include "yacreader_gl_flow_config_widget.h"
#endif
#include "yacreader_flow_config_widget.h"
#include "api_key_dialog.h"

#ifndef NO_OPENGL
FlowType flowType = Strip;
#endif

OptionsDialog::OptionsDialog(QWidget * parent)
:YACReaderOptionsDialog(parent)
{
    QTabWidget * tabWidget = new QTabWidget();

    QVBoxLayout * layout = new QVBoxLayout(this);

    QVBoxLayout * flowLayout = new QVBoxLayout;
    QVBoxLayout * gridViewLayout = new QVBoxLayout();
    QVBoxLayout * generalLayout = new QVBoxLayout();

    QHBoxLayout * switchFlowType = new QHBoxLayout();
    switchFlowType->addStretch();
#ifndef NO_OPENGL
    switchFlowType->addWidget(useGL);
#endif
    QHBoxLayout * buttons = new QHBoxLayout();
    buttons->addStretch();
    buttons->addWidget(accept);
    buttons->addWidget(cancel);

    flowLayout->addWidget(sw);
#ifndef NO_OPENGL
    flowLayout->addWidget(gl);
#endif
    flowLayout->addLayout(switchFlowType);

#ifndef NO_OPENGL
    sw->hide();
#endif

    QVBoxLayout * apiKeyLayout = new QVBoxLayout();
    QPushButton * apiKeyButton = new QPushButton(tr("Edit Comic Vine API key"));
    apiKeyLayout->addWidget(apiKeyButton);

    QGroupBox * apiKeyBox = new QGroupBox(tr("Comic Vine API key"));
    apiKeyBox->setLayout(apiKeyLayout);

    connect(apiKeyButton,SIGNAL(clicked()),this,SLOT(editApiKey()));

    //grid view background config
    useBackgroundImageCheck = new QCheckBox(tr("Enable background image"));

    opacityLabel = new QLabel(tr("Opacity level"));

    backgroundImageOpacitySlider = new QSlider(Qt::Horizontal);
    backgroundImageOpacitySlider->setRange(5,100);

    blurLabel = new QLabel(tr("Blur level"));

    backgroundImageBlurRadiusSlider = new QSlider(Qt::Horizontal);
    backgroundImageBlurRadiusSlider->setRange(0,100);

    useCurrentComicCoverCheck = new QCheckBox(tr("Use selected comic cover as background"));

    resetButton = new QPushButton(tr("Restore defautls"));

    QVBoxLayout * gridBackgroundLayout = new QVBoxLayout();
    gridBackgroundLayout->addWidget(useBackgroundImageCheck);
    gridBackgroundLayout->addWidget(opacityLabel);
    gridBackgroundLayout->addWidget(backgroundImageOpacitySlider);
    gridBackgroundLayout->addWidget(blurLabel);
    gridBackgroundLayout->addWidget(backgroundImageBlurRadiusSlider);
    gridBackgroundLayout->addWidget(useCurrentComicCoverCheck);
    gridBackgroundLayout->addWidget(resetButton,0,Qt::AlignRight);

    QGroupBox * gridBackgroundGroup = new QGroupBox(tr("Background"));
    gridBackgroundGroup->setLayout(gridBackgroundLayout);

    gridViewLayout->addWidget(gridBackgroundGroup);
    gridViewLayout->addStretch();

    connect(useBackgroundImageCheck, SIGNAL(clicked(bool)), this, SLOT(useBackgroundImageCheckClicked(bool)));
    connect(backgroundImageOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(backgroundImageOpacitySliderChanged(int)));
    connect(backgroundImageBlurRadiusSlider, SIGNAL(valueChanged(int)), this, SLOT(backgroundImageBlurRadiusSliderChanged(int)));
    connect(useCurrentComicCoverCheck, &QCheckBox::clicked, this, &OptionsDialog::useCurrentComicCoverCheckClicked);
    connect(resetButton, &QPushButton::clicked, this, &OptionsDialog::resetToDefaults);
    //end grid view background config

    QWidget * comicFlowW = new QWidget;
    comicFlowW->setLayout(flowLayout);

    QWidget * gridViewW = new QWidget;
    gridViewW->setLayout(gridViewLayout);

    QWidget * generalW = new QWidget;
    generalW->setLayout(generalLayout);
    generalLayout->addWidget(shortcutsBox);
    generalLayout->addWidget(apiKeyBox);
    generalLayout->addStretch();

    tabWidget->addTab(comicFlowW,tr("Comic Flow"));
#ifndef NO_OPENGL
    tabWidget->addTab(gridViewW,tr("Grid view"));
#endif
    tabWidget->addTab(generalW,tr("General"));

    layout->addWidget(tabWidget);
    layout->addLayout(buttons);
    setLayout(layout);
    //restoreOptions(settings); //load options
    //resize(200,0);
    setModal (true);
    setWindowTitle(tr("Options"));

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void OptionsDialog::editApiKey()
{
    ApiKeyDialog d;
    d.exec();
}

void OptionsDialog::restoreOptions(QSettings * settings)
{
    YACReaderOptionsDialog::restoreOptions(settings);

    bool useBackgroundImage = settings->value(USE_BACKGROUND_IMAGE_IN_GRID_VIEW, true).toBool();

    useBackgroundImageCheck->setChecked(useBackgroundImage);
    backgroundImageOpacitySlider->setValue(settings->value(OPACITY_BACKGROUND_IMAGE_IN_GRID_VIEW, 0.2).toFloat()*100);
    backgroundImageBlurRadiusSlider->setValue(settings->value(BLUR_RADIUS_BACKGROUND_IMAGE_IN_GRID_VIEW, 75).toInt());
    useCurrentComicCoverCheck->setChecked(settings->value(USE_SELECTED_COMIC_COVER_AS_BACKGROUND_IMAGE_IN_GRID_VIEW, false).toBool());

    backgroundImageOpacitySlider->setVisible(useBackgroundImage);
    backgroundImageBlurRadiusSlider->setVisible(useBackgroundImage);
    opacityLabel->setVisible(useBackgroundImage);
    blurLabel->setVisible(useBackgroundImage);
    useCurrentComicCoverCheck->setVisible(useBackgroundImage);
}

void OptionsDialog::useBackgroundImageCheckClicked(bool checked)
{
    settings->setValue(USE_BACKGROUND_IMAGE_IN_GRID_VIEW, checked);

    backgroundImageOpacitySlider->setVisible(checked);
    backgroundImageBlurRadiusSlider->setVisible(checked);
    opacityLabel->setVisible(checked);
    blurLabel->setVisible(checked);
    useCurrentComicCoverCheck->setVisible(checked);

    emit optionsChanged();
}

void OptionsDialog::backgroundImageOpacitySliderChanged(int value)
{
    settings->setValue(OPACITY_BACKGROUND_IMAGE_IN_GRID_VIEW, value/100.0);

    emit optionsChanged();
}

void OptionsDialog::backgroundImageBlurRadiusSliderChanged(int value)
{
    settings->setValue(BLUR_RADIUS_BACKGROUND_IMAGE_IN_GRID_VIEW, value);

    emit optionsChanged();
}

void OptionsDialog::useCurrentComicCoverCheckClicked(bool checked)
{
    settings->setValue(USE_SELECTED_COMIC_COVER_AS_BACKGROUND_IMAGE_IN_GRID_VIEW, checked);

    emit optionsChanged();
}

void OptionsDialog::resetToDefaults()
{
    settings->setValue(OPACITY_BACKGROUND_IMAGE_IN_GRID_VIEW, 0.2);
    settings->setValue(BLUR_RADIUS_BACKGROUND_IMAGE_IN_GRID_VIEW, 75);
    settings->setValue(USE_SELECTED_COMIC_COVER_AS_BACKGROUND_IMAGE_IN_GRID_VIEW, false);

    restoreOptions(settings);

    emit optionsChanged();
}
