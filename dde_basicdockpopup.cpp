#include "dde_basicdockpopup.h"

#define DATETIME_PLACEHOLDER "这里显示日期时间"

DDE_BasicDockPopup::DDE_BasicDockPopup(QWidget *parent)
    : QWidget(parent),
      m_settings("deepin", "DDEBasicDock")      // 初始化本插件的设置存储
{
    /* 使用纯代码构造界面。
     *
     * 添加到Layout中的部件，可以先在类中声明好，再在这里初始化；
     * 也可以直接在这里创建并初始化（比如QLabel *label = new QLabel）。
     * 两种方法都可以，但值得注意的是，后者的作用域仅限于构造函数，
     * 这就意味着我们不能在后续的程序中改变这些部件的属性了。
     * 所以请慎重，只有在确保部件属性不会变动时，再使用后一种方案。
     */

    setFixedWidth(300);
    layout = new QGridLayout;

    /* 标题标签 */
    lblTitle = new QLabel;
    lblTitle->setText("简单的DDE Dock插件");
    lblTitle->setStyleSheet("color: white; font-size: 20px; padding-bottom: 10px; ");      // Qt支持的CSS仅为一个子集。注意字体设置单位不能用em、rem等。
    lblTitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblTitle, 0, 0, 1, 2);    // 五个参数依次为：部件对象、行、列、行扩展、列扩展。后两者用于合并单元格

    /* 图片标签 */
    lblIcon = new QLabel;
    lblIcon->setPixmap(QPixmap(":/icons/popicon.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    lblIcon->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblIcon, 1, 0);

    /* 图片右侧的说明标签 */
    lblText = new QLabel;
    lblText->setText("开发插件就是爽！\nDDE Dock，给你无限拓展可能！");
    lblText->setStyleSheet("color: white; ");
    lblText->setAlignment(Qt::AlignLeft);
    layout->addWidget(lblText, 1, 1);

    /* 日期时间标签 */
    lblDateTime = new QLabel;
    lblDateTime->setText(DATETIME_PLACEHOLDER);
    lblDateTime->setStyleSheet("color: white; font-size: 15px; padding-top: 10px; ");
    lblDateTime->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblDateTime, 2, 0, 1, 2);

    setLayout(layout);
}

/* 刷新插件弹出窗口UI */
// 本插件将示范：在窗口底部显示实时时钟
void DDE_BasicDockPopup::updatePopupUI()
{
    // 获得当前日期时间。下面的两个静态函数会根据当前的时间/日期来创建对应对象的新实例
    qDate = QDate::currentDate();
    qTime = QTime::currentTime();

    // 按照指定格式获得时间日期文本，并设置到标签中
    lblDateTime->setText(qDate.toString("yyyy-MM-dd  ") + qTime.toString("HH:mm:ss"));
}
