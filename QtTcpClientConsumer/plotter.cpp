#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <algorithm>

Plotter::Plotter(QWidget *parent) : QWidget{parent} {}

void Plotter::setData(const QVector<QPointF> &data){
    points = data;
    update(); // Força o widget a se redesenhar (chama paintEvent)
}

void Plotter::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    // Desenha o fundo branco
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0, 0, width(), height());

    // Configura a caneta para o gráfico
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);

    // Se não houver pontos suficientes para desenhar uma linha, não faz nada
    if (points.size() < 2) {
        return;
    }

    // Encontra os limites dos dados (min/max para tempo e valor)
    double minTime = points.first().x();
    double maxTime = points.first().x();
    double minValue = points.first().y();
    double maxValue = points.first().y();

    for(const QPointF &p : points){
        if(p.x() < minTime) minTime = p.x();
        if(p.x() > maxTime) maxTime = p.x();
        if(p.y() < minValue) minValue = p.y();
        if(p.y() > maxValue) maxValue = p.y();
    }

    // Evita divisão por zero se todos os pontos forem iguais
    double timeRange = (maxTime - minTime == 0) ? 1 : (maxTime - minTime);
    double valueRange = (maxValue - minValue == 0) ? 1 : (maxValue - minValue);

    // Adiciona uma pequena margem para o gráfico não tocar as bordas
    int margin = 10;

    // Desenha as linhas do gráfico, mapeando cada ponto de dados para um pixel na tela
    for(int i = 0; i < points.size() - 1; ++i){
        // Ponto atual (i)
        double x1_data = points.at(i).x();
        double y1_data = points.at(i).y();

        // Ponto seguinte (i+1)
        double x2_data = points.at(i+1).x();
        double y2_data = points.at(i+1).y();

        // Mapeia o valor do dado (tempo, valor) para a coordenada de pixel (x, y)
        // Coordenada X:
        int x1_pixel = margin + ((x1_data - minTime) / timeRange) * (width() - 2 * margin);
        int x2_pixel = margin + ((x2_data - minTime) / timeRange) * (width() - 2 * margin);

        // Coordenada Y: O eixo Y do Qt é invertido (0 é no topo), por isso subtraímos de height()
        int y1_pixel = (height() - margin) - ((y1_data - minValue) / valueRange) * (height() - 2 * margin);
        int y2_pixel = (height() - margin) - ((y2_data - minValue) / valueRange) * (height() - 2 * margin);

        painter.drawLine(x1_pixel, y1_pixel, x2_pixel, y2_pixel);
    }
}
