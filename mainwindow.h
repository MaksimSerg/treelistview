#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum language
    {
        english,
        russian
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void openSubWindowsAll();
    void changeLanguage(language aLang);

protected:
    void changeEvent(QEvent * event) override;

private:
    Ui::MainWindow *ui;
    QTranslator m_translator;
};

#endif // MAINWINDOW_H
