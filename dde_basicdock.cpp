#include "dde_basicdock.h"
#include <QApplication>
#include <QPainter>

#define PLUGIN_STATE_KEY "enable"

DDE_BasicDock::DDE_BasicDock(QWidget *parent)
    : QWidget(parent),
      m_settings("deepin", "DDEBasicDock")
{
    text = "000";
}

bool DDE_BasicDock::enabled()
{
    return m_settings.value(PLUGIN_STATE_KEY, true).toBool();
}

void DDE_BasicDock::setEnabled(const bool b)
{
    m_settings.setValue(PLUGIN_STATE_KEY, b);
}

QSize DDE_BasicDock::sizeHint() const
{
    QFont font = qApp->font();
    font.setFamily("Noto Mono");
    QFontMetrics FM(font);
    return FM.boundingRect("000").size();
}

void DDE_BasicDock::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void DDE_BasicDock::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::white);

    QFont font = qApp->font();
    font.setFamily("Noto Mono");
    painter.setFont(font);

    painter.drawText(rect().adjusted(2,0,0,0), Qt::AlignLeft | Qt::AlignVCenter, text);
}
