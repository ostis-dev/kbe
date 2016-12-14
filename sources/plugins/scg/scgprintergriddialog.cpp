#include "ScgPrinterGridDialog.h"

#include <QPrinter>
#include <QPair>
#include <QVector>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>

typedef QPrinter::PageSize PagePaperSize;
typedef QVector<PagePaperSize>  PagePaperSizeArray;
typedef QPageLayout::Orientation PagePaperOrientation;
typedef QVector<PagePaperOrientation> PagePaperOrientationArray;

Q_DECLARE_METATYPE(PagePaperSize)

static PagePaperSize gSupportedPageSizes[] = 
{
    QPrinter::A0,
    QPrinter::A1,
    QPrinter::A2,
    QPrinter::A3,
    QPrinter::A4,
    QPrinter::A5
};

static PagePaperOrientation gSupportedPageOrientations[] = 
{
    QPageLayout::Portrait,
    QPageLayout::Landscape
};

PagePaperSizeArray supportedPageSizes()
{
    uint nCount = sizeof(gSupportedPageSizes) / sizeof(gSupportedPageSizes[0]);

    PagePaperSizeArray sizes;

    for (uint i = 0; i < nCount; i++)
        sizes.push_back(gSupportedPageSizes[i]);

    return sizes;
}

PagePaperOrientationArray supportedPageOrientations()
{
    uint nCount = sizeof(gSupportedPageOrientations) / sizeof(gSupportedPageOrientations[0]);

    PagePaperOrientationArray orientations;

    for (uint i = 0; i < nCount; i++)
        orientations.push_back(gSupportedPageOrientations[i]);

    return orientations;
}

QString pageSizeToString(PagePaperSize size)
{
    QString str;
    
    switch (size)
    {
    case QPrinter::A0: 
        str = "A0";
    	break;
    case QPrinter::A1: 
        str = "A1";
        break;
    case QPrinter::A2: 
        str = "A2";
        break;
    case QPrinter::A3: 
        str = "A3";
        break;
    case QPrinter::A4: 
        str = "A4";
        break;
    case QPrinter::A5: 
        str = "A5";
        break;
    default:
        str = "undefined size";
    }


    return str;
}

QString pageOrientationToString(PagePaperOrientation orient)
{
    QString str;

    switch(orient)
    {
    case QPageLayout::Landscape:
        str = QObject::tr("Landscape");
        break;
    case QPageLayout::Portrait:
        str = QObject::tr("Portrait");
        break;
    default:
        str = QObject::tr("Undefined orientation");
    }

    return str;
}


SCgPrinterGridDialog::SCgPrinterGridDialog(QWidget *parent)
    : QDialog(parent)
    , mVerticalLayout(0)
    , mEnableCheckbox(0)
    , mGroupBox(0)
    , mFormLayout(0)
    , mSizeLabel(0)
    , mPagePaperSizeComboBox(0)
    , mOrientationLabel(0)
    , mPagePaperOrientationComboBox(0)
    , mButtonBox(0)
    , mIsPrintGridEnabled(0)
    , mPagePaperSizeIndex(0)
    , mPagePaperOrientationIndex(0)
{
    setWindowTitle(tr("Printer grid settings"));

    mVerticalLayout = new QVBoxLayout(this);
    mEnableCheckbox = new QCheckBox(this);
    mEnableCheckbox->setText(tr("Enable printer grid"));

    mVerticalLayout->addWidget(mEnableCheckbox);

    mGroupBox = new QGroupBox(this);
    mFormLayout = new QFormLayout(mGroupBox);


    mSizeLabel = new QLabel(mGroupBox);
    mSizeLabel->setText(tr("Page size"));
    mFormLayout->setWidget(0, QFormLayout::LabelRole, mSizeLabel);

    mPagePaperSizeComboBox = new QComboBox(mGroupBox);
    mFormLayout->setWidget(0, QFormLayout::FieldRole, mPagePaperSizeComboBox);

    mOrientationLabel = new QLabel(mGroupBox);
    mOrientationLabel->setText(tr("Page orientation"));
    mFormLayout->setWidget(1, QFormLayout::LabelRole, mOrientationLabel);

    mPagePaperOrientationComboBox = new QComboBox(mGroupBox);
    mFormLayout->setWidget(1, QFormLayout::FieldRole, mPagePaperOrientationComboBox);


    mVerticalLayout->addWidget(mGroupBox);

    mButtonBox = new QDialogButtonBox(this);
    mButtonBox->setOrientation(Qt::Horizontal);
    mButtonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    mVerticalLayout->addWidget(mButtonBox);

    QObject::connect(mButtonBox, SIGNAL(accepted()), this, SLOT(onPressAccepted()));
    QObject::connect(mButtonBox, SIGNAL(rejected()), this, SLOT(onPressRejected()));

    mGroupBox->setEnabled(false);

    PagePaperSizeArray sizes = supportedPageSizes();
    foreach(const PagePaperSize& pageSize, sizes)
        mPagePaperSizeComboBox->addItem(pageSizeToString(pageSize), qVariantFromValue(pageSize));

    PagePaperOrientationArray orientations = supportedPageOrientations();
    foreach(const PagePaperOrientation& pageOrientation, orientations)
        mPagePaperOrientationComboBox->addItem(pageOrientationToString(pageOrientation), qVariantFromValue(pageOrientation));

    QObject::connect(mEnableCheckbox, SIGNAL(toggled(bool)), SLOT(onEnableCheckboxStateChanged(bool)));
}

SCgPrinterGridDialog::~SCgPrinterGridDialog()
{
}

void SCgPrinterGridDialog::onEnableCheckboxStateChanged(bool toggled)
{
    mGroupBox->setEnabled(toggled);
}

void SCgPrinterGridDialog::onPressAccepted()
{   
    mIsPrintGridEnabled = mEnableCheckbox->isChecked();
    mPagePaperSizeIndex = mPagePaperSizeComboBox->currentIndex();
    mPagePaperOrientationIndex = mPagePaperOrientationComboBox->currentIndex();

    accept();
}
void SCgPrinterGridDialog::onPressRejected()
{
    mEnableCheckbox->setChecked(mIsPrintGridEnabled);
    mPagePaperSizeComboBox->setCurrentIndex(mPagePaperSizeIndex);
    mPagePaperOrientationComboBox->setCurrentIndex(mPagePaperOrientationIndex);

    reject();
}

bool SCgPrinterGridDialog::isPrinterGridEnabled() const
{
    return mEnableCheckbox->isChecked();
}

QSizeF SCgPrinterGridDialog::paperSize() const
{
    QSizeF size;

    if (isPrinterGridEnabled())
    {
        PagePaperSize pagePaperSize = mPagePaperSizeComboBox->currentData().value<PagePaperSize>();
        PagePaperOrientation pagePaperOrientation = mPagePaperOrientationComboBox->currentData().value<PagePaperOrientation>();

        QPrinter printer;
        printer.setPaperSize(pagePaperSize);
        printer.setPageOrientation(pagePaperOrientation);

        size = printer.paperSize(QPrinter::DevicePixel);
    }


    return size;
}
