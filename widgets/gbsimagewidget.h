#ifndef GBSIMAGEWIDGET_H
#define GBSIMAGEWIDGET_H

#include <QWidget>


namespace Ui {
class GbsImageWidget;
}

class GbsImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GbsImageWidget(QWidget *parent = 0);
    ~GbsImageWidget();
    void setImages(QList<QImage> &list);
    void showEvent(QShowEvent *event);

private slots:
    void on_btnPrevious_clicked();
    void on_btnNext_clicked();

private:
    void setBtnStatus(qint32 currentPage, quint32 totalPage);
    Ui::GbsImageWidget *ui;
    QList<QImage> m_listImage;
    qint32 m_currentPage;
    qint32 m_totalPate;
    bool m_firstShow;
};

#endif // GBSIMAGEWIDGET_H
