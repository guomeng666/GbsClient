#ifndef GBSTABLEWIDGET_H
#define GBSTABLEWIDGET_H

#include <QWidget>
#include <QMenu>

namespace Ui {
class GbsTableWidget;
}

class GbsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GbsTableWidget(QWidget *parent = 0);
    ~GbsTableWidget();

    //设置表格数据,固定显示20条数据
    void setTableData(quint32 total, quint32 curPage, QList<QStringList> tableData);
    //显示数据
    void showTableData();
    //设置列表头
    void setTableColumnHeader(QStringList &header);

signals:
    //表格首页按钮点击事件
    void evtFristBtnClicked(quint32 page);
    //表格下一页按钮点击事件
    void evtNextBtnClicked(quint32 page);
    //表格上一页按钮点击事件
    void evtPreviousClicked(quint32 page);
    //表格尾页按钮点击事件
    void evtLastBtnClicked(quint32 page);
    //表格修改事件
    void evtAlterRow(const QStringList &row);
    //表格删除事件
    void evtDeleteRow(const QStringList &row);


private slots:
    void on_btnFirst_clicked();
    void on_btnPrevious_clicked();
    void on_btnNext_clicked();
    void on_btnLast_clicked();
    void onRecordSortbyClounm(int column);
    void onEvtTableMenuAction();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

private:
    void initWidget();
    void initMenu();
    void setPageBtnStatus();
    QStringList getSelectedRowData();
    Ui::GbsTableWidget *ui;
    QList<QStringList> m_tableData;
    QMenu *m_tableMenu;
    quint32 m_total;  //一共有多少条数据需要在表格显示,用于计算表格翻页按钮
    quint32 m_curPage;   //表格显示的页是总页数第几页
    quint32 m_perPage; //表格一页显示多少条数据
    quint32 m_totalPage;
    int m_hideCloumn;
};

#endif // GBSTABLEWIDGET_H
