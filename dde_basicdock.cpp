#include "dde_basicdock.h"
//#include "dde-dock/constants.h"
#include <QApplication>
#include <QPainter>

#define PLUGIN_STATE_KEY "enable"

/* 构造函数 - 在这里初始化插件界面的一些基本数据 */
DDE_BasicDock::DDE_BasicDock(QWidget *parent)
    : QWidget(parent),
      m_settings("deepin", "DDEBasicDock")      // 初始化本插件的设置存储
{
    text = "请稍候...";
}

/* 返回插件可用状态 */
// 这个方法会由Dock接口调用，通过确定这里的值，来决定是否将插件显示在Dock上
bool DDE_BasicDock::enabled()
{
    // 插件的可用状态存储在设置当中，在这里读出
    return m_settings.value(PLUGIN_STATE_KEY, true).toBool();
}

/* 设置插件可用状态 */
void DDE_BasicDock::setEnabled(const bool b)
{
    // 由于可用状态的值保存在设置中，所以在这里也要修改设置
    m_settings.setValue(PLUGIN_STATE_KEY, b);
}

/* 设定插件大小的参考值。 【继承自QWidget】 */
QSize DDE_BasicDock::sizeHint() const
{
    QFont font = qApp->font();
    font.setFamily("Noto Mono");
    QFontMetrics FM(font);
    return FM.boundingRect("000").size();
}

/* 插件大小更改时触发的事件。 【继承自QWidget】 */
void DDE_BasicDock::resizeEvent(QResizeEvent *e)
{
    // 事实上Dock的插件大小都是恒定的（调不了），所以不需做额外处理，调用父类方法就好
    QWidget::resizeEvent(e);
}

/* 绘制插件界面。这是本类的重中之重，插件的外观由此决定。 【继承自QWidget】*/
void DDE_BasicDock::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    /* 这里使用QPainter来绘制界面。
     * 此为手动绘制界面的方法。很多编程环境（如Python的Tkinter、Windows的MFC）都只能用写代码的形式来编写界面，
     * 有别于Qt和VB的可视化窗体设计工具。
     * 另外，QPainter的用法可以类比H5的Canvas编程。
     */
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);      // 设置界面渲染方法。Qt有自己的一套渲染引擎
    painter.setPen(Qt::white);                          // 设置画笔颜色

    // 设置字体
    QFont font = qApp->font();          // 需要获得一个QFont的实例
    font.setFamily("Noto Mono");
    painter.setFont(font);

    // 绘制文字
    painter.drawText(rect().adjusted(2,0,0,0), Qt::AlignLeft | Qt::AlignVCenter, text);
}
