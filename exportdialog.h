#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();

    QString getExporter(){return current_exporter; }
    QString getOutputFolder(){return output_folder; }
    QString getNamesFile(){return names_file; }
    int getShuffle(){return do_shuffle; }
    float getValidationSplit(){return static_cast<float>(validation_split_pc)/100; }

private slots:
    void setNamesFile(QString path="");
    void setOutputFolder(QString path="");
    void setValidationSplit(int value);
    void toggleShuffle(bool shuffle);
    void toggleExporter();

private:
    Ui::ExportDialog *ui;
    void checkOK();

    QSettings *settings;

    QString output_folder = "";
    QString names_file = "";
    QString current_exporter = "Darknet";
    bool do_shuffle = false;
    int validation_split_pc = 80;

};

#endif // EXPORTDIALOG_H
