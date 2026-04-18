#include "EcoCampus.h"
#include "temporizador.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QDir>
#include <QPixmap>
#include <QFileInfo>
#include <QDebug>
#include <QSignalBlocker>
#include <QTimer>

EcoCampus::EcoCampus(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    scene_ = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene_);
    ui.graphicsView->setRenderHint(QPainter::Antialiasing, true);

    connect(scene_, &QGraphicsScene::selectionChanged,
        this, &EcoCampus::onSceneSelectionChanged);

    const QString dirDatos = QDir::currentPath();
    if (!controller_.inicializar(dirDatos.toStdString())) {
        qWarning() << "No se pudo inicializar el grafo desde" << dirDatos;
    }

    dibujarGrafo();
}

EcoCampus::~EcoCampus()
{}

void EcoCampus::dibujarGrafo() {
    const QSignalBlocker blocker(scene_);

    scene_->clear();

    const Grafo& g = controller_.getGrafo();

    const QString mapaPath = QDir::currentPath() + "/mapa.png";
    if (QFileInfo::exists(mapaPath)) {
        QPixmap mapa(mapaPath);
        if (!mapa.isNull()) {
            auto* pix = scene_->addPixmap(mapa);
            pix->setZValue(-10);
        }
    }

    QPen penNormal(Qt::black, 2);
    QPen penBloqueado(Qt::red, 2, Qt::DashLine);

    for (const auto& a : g.getaristas()) {
        const Nodo* origen = g.buscarNodo(a.getOrigenId());
        const Nodo* destino = g.buscarNodo(a.getDestinoId());
        if (!origen || !destino) continue;

        QPen pen = a.isBloqueada() ? penBloqueado : penNormal;
        scene_->addLine(origen->getPosX(), origen->getPosY(),
            destino->getPosX(), destino->getPosY(), pen);
    }

    QBrush brushNormal(Qt::blue);
    QBrush brushBloqueado(Qt::red);
    QPen penNodo(Qt::black);

    const int radio = 8;
    for (const auto& n : g.getNodos()) {
        QBrush brush = n.isBloqueado() ? brushBloqueado : brushNormal;
        auto* item = scene_->addEllipse(n.getPosX() - radio, n.getPosY() - radio,
            radio * 2, radio * 2, penNodo, brush);
        item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item->setData(0, n.getId());
        item->setToolTip(QString::fromStdString(n.getNombre()));
    }
}

void EcoCampus::on_btnDFS_clicked() {
    Temporizador t;
    t.iniciar();

    const int inicioId = ui.spnInicio->value();
    auto res = controller_.recorridoDFS(inicioId);

    const long long tiempo = t.microsegundos();
    ui.lblTiempo->setText(QString::number(tiempo) + " µs");
    ui.lblVisitados->setText(QString::number(res.nodosVisitados));
}

void EcoCampus::on_btnBFS_clicked() {
    Temporizador t;
    t.iniciar();

    const int inicioId = ui.spnInicio->value();
    auto res = controller_.recorridoBFS(inicioId);

    const long long tiempo = t.microsegundos();
    ui.lblTiempo->setText(QString::number(tiempo) + " µs");
    ui.lblVisitados->setText(QString::number(res.nodosVisitados));
}

void EcoCampus::on_chkMovilidad_stateChanged(int state) {
    controller_.setPerfil(state == Qt::Checked
        ? PerfilUsuario::MovilidadReducida
        : PerfilUsuario::EstudianteRegular);
    dibujarGrafo();
}

void EcoCampus::onSceneSelectionChanged() {
    const auto selected = scene_->selectedItems();
    if (selected.isEmpty()) return;

    for (auto* item : selected) {
        if (!item) continue;
        const auto data = item->data(0);
        if (!data.isValid()) continue;

        bool ok = false;
        const int id = data.toInt(&ok);
        if (!ok) continue;

        const Nodo* n = controller_.getGrafo().buscarNodo(id);
        if (!n) continue;
        controller_.bloquearNodo(id, !n->isBloqueado());
    }

    if (!updatePending_) {
        updatePending_ = true;
        QTimer::singleShot(0, this, [this]() {
            updatePending_ = false;
            dibujarGrafo();
        });
    }
}

