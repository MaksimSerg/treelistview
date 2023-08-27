#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QTranslator>

#include "subwindows/wframe1.h"
#include "subwindows/wframe2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_translator()
{
    ui->setupUi(this);

    // language
    connect(ui->actionEnglish, &QAction::triggered, this, std::bind(&MainWindow::changeLanguage, this, language::english));
    connect(ui->actionRussian, &QAction::triggered, this, std::bind(&MainWindow::changeLanguage, this, language::russian));

    // mdi windows
    QTimer::singleShot(0, this, SLOT(openSubWindowsAll()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeLanguage(language aLang)
{
    QString languageCode = "en";
    if (aLang == language::russian)
    {
        languageCode = "ru";
    }

    QStringList files = {"qtbase", "treelistcontrol"};

    for (QString &fileName: files)
    {
        if (m_translator.load(QString(":/translate/%1_%2.qm").arg(fileName).arg(languageCode))) {
            QCoreApplication::installTranslator(&m_translator);
        }
    }

    QLocale curLocale(QLocale(QString("%1_%2").arg(languageCode).arg(languageCode.toUpper())));
    QLocale::setDefault(curLocale);
}

void MainWindow::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

void MainWindow::openSubWindowsAll()
{
    QSize mSize = ui->mdiArea->size();

    WFrame2 *frame2 = new WFrame2(ui->mdiArea);
    frame2->setWindowTitle("Frame #2");
    frame2->setMinimumSize(0.5*mSize);
    ui->mdiArea->addSubWindow(frame2);

    WFrame1 *frame1 = new WFrame1(ui->mdiArea);
    frame1->setWindowTitle("Frame #1");
    frame1->setMinimumSize(0.5*mSize);
    ui->mdiArea->addSubWindow(frame1);

    frame2->show();
    frame1->show();

//    ui->mdiArea->cascadeSubWindows();
}


