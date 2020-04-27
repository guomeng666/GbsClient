#include "gbsimagewidget.h"
#include "ui_gbsimagewidget.h"
#include <QDebug>

GbsImageWidget::GbsImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GbsImageWidget)
{
    ui->setupUi(this);
    m_currentPage = 0;
    m_totalPate = 0;
    m_firstShow = false;
    ui->btnNext->setEnabled(false);
    ui->btnPrevious->setEnabled(false);
}

GbsImageWidget::~GbsImageWidget()
{
    delete ui;
}

void GbsImageWidget::setImages(QList<QImage> &list)
{
    m_listImage = list;
    //显示第一张图片
    m_totalPate = m_listImage.count();
    if(m_firstShow == true){
        if(m_totalPate != 0){
            QImage image = m_listImage.at(m_currentPage).scaled(ui->labImage->size()/1.1,Qt::KeepAspectRatio);
            ui->labImage->setPixmap(QPixmap::fromImage(image));
            m_currentPage++;
            ui->labPage->setText(QString::number(m_currentPage) + "/"+ QString::number(m_totalPate));
        }
        setBtnStatus(m_currentPage,m_totalPate);
    }
}

void GbsImageWidget::showEvent(QShowEvent *event)
{
    if(m_firstShow == false){
        m_firstShow = true;
        if(m_totalPate != 0){
            QImage image = m_listImage.at(m_currentPage).scaled(ui->labImage->size()/1.1,Qt::KeepAspectRatio);
            ui->labImage->setPixmap(QPixmap::fromImage(image));
            m_currentPage++;
            ui->labPage->setText(QString::number(m_currentPage) + "/"+ QString::number(m_totalPate));
        }
        setBtnStatus(m_currentPage,m_totalPate);
    }
}

void GbsImageWidget::on_btnPrevious_clicked()
{
    qDebug()<<ui->labImage->size();
    m_currentPage--;
    QImage image = m_listImage.at(m_currentPage-1).scaled(ui->labImage->size()/1.1,Qt::KeepAspectRatio);
    ui->labImage->setPixmap(QPixmap::fromImage(image));
    ui->labPage->setText(QString::number(m_currentPage) + "/"+ QString::number(m_totalPate));
    setBtnStatus(m_currentPage,m_totalPate);
}

void GbsImageWidget::on_btnNext_clicked()
{
    qDebug()<<ui->labImage->size();
    QImage image = m_listImage.at(m_currentPage).scaled(ui->labImage->size()/1.1,Qt::KeepAspectRatio);
    ui->labImage->setPixmap(QPixmap::fromImage(image));
    m_currentPage++;
    ui->labPage->setText(QString::number(m_currentPage) + "/"+ QString::number(m_totalPate));
    setBtnStatus(m_currentPage,m_totalPate);
}

void GbsImageWidget::setBtnStatus(qint32 currentPage, quint32 totalPage)
{
    if(currentPage < totalPage){
        ui->btnNext->setEnabled(true);
    }else{
        ui->btnNext->setEnabled(false);
    }
    if(currentPage == 1){
        ui->btnPrevious->setEnabled(false);
    }else{
        ui->btnPrevious->setEnabled(true);
    }
}
