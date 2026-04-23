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
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QCoreApplication>
#include <QStringList>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QUrl>
#include <QSizePolicy>

namespace {
QString resolverRutaImagen(const QString& archivo) {
    const QDir appDir(QCoreApplication::applicationDirPath());
    const QDir currentDir(QDir::currentPath());

    QStringList candidatos = {
        appDir.filePath(archivo),
        currentDir.filePath(archivo)
    };

    QDir upDir = appDir;
    for (int i = 0; i < 4; ++i) {
        if (!upDir.cdUp()) break;
        candidatos.append(upDir.filePath(archivo));
    }

    for (const auto& ruta : candidatos) {
        if (QFileInfo::exists(ruta)) return ruta;
    }

    return archivo;
}

}

UiBridge::UiBridge(QObject* parent)
    : QObject(parent)
{
}

void UiBridge::setInicio(int value) {
    if (inicio_ == value) return;
    inicio_ = value;
    emit inicioChanged();
}

void UiBridge::setTiempo(const QString& value) {
    if (tiempo_ == value) return;
    tiempo_ = value;
    emit tiempoChanged();
}

void UiBridge::setVisitados(const QString& value) {
    if (visitados_ == value) return;
    visitados_ = value;
    emit visitadosChanged();
}

void UiBridge::setMovilidadReducida(bool value) {
    if (movilidadReducida_ == value) return;
    movilidadReducida_ = value;
    emit movilidadReducidaChanged(movilidadReducida_);
}

void UiBridge::setOrigen(int value) {
    if (origen_ == value) return;
    origen_ = value;
    emit origenChanged();
}

void UiBridge::setDestino(int value) {
    if (destino_ == value) return;
    destino_ = value;
    emit destinoChanged();
}

void UiBridge::setPerfilRuta(const QString& value) {
    if (perfilRuta_ == value) return;
    perfilRuta_ = value;
    emit perfilRutaChanged();
}

void UiBridge::setPisoActual(const QString& value) {
    if (pisoActual_ == value) return;
    pisoActual_ = value;
    emit pisoActualChanged();
}

void UiBridge::setMostrarBiblioteca(bool value) {
    if (mostrarBiblioteca_ == value) return;
    mostrarBiblioteca_ = value;
    emit mostrarBibliotecaChanged();
}

void UiBridge::setMostrarComedor(bool value) {
    if (mostrarComedor_ == value) return;
    mostrarComedor_ = value;
    emit mostrarComedorChanged();
}

void UiBridge::requestDfs() {
    emit dfsRequested();
}

void UiBridge::requestBfs() {
    emit bfsRequested();
}

void UiBridge::requestBuscarCamino() {
    emit buscarCaminoRequested();
}

void UiBridge::requestRutaPerfil() {
    emit rutaPerfilRequested();
}

EcoCampus::EcoCampus(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    scene_ = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene_);
    ui.graphicsView->setRenderHint(QPainter::Antialiasing, true);
    configurarInteraccionVista();
    ui.centralWidget->setStyleSheet("background: #0f1115;");
    configurarPanelQml();

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

void EcoCampus::configurarInteraccionVista() {
    ui.graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui.graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    ui.graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui.graphicsView->viewport()->installEventFilter(this);
    ui.graphicsView->setStyleSheet("background: #0f1115; border: 1px solid #2a2f3a; border-radius: 12px;");
}

void EcoCampus::configurarPanelQml() {
    uiBridge_ = new UiBridge(this);
    uiBridge_->setInicio(1);
    uiBridge_->setTiempo("0 탎");
    uiBridge_->setVisitados("0");
    uiBridge_->setMovilidadReducida(false);
    uiBridge_->setOrigen(1);
    uiBridge_->setDestino(1);
    uiBridge_->setPerfilRuta("Regular");
    uiBridge_->setPisoActual("Universidad");
    uiBridge_->setMostrarBiblioteca(false);
    uiBridge_->setMostrarComedor(false);

    auto* quickPanel = new QQuickWidget(this);
    quickPanel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    quickPanel->setMinimumWidth(260);
    quickPanel->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickPanel->setClearColor(Qt::transparent);
    quickPanel->rootContext()->setContextProperty("bridge", uiBridge_);
    quickPanel->setSource(QUrl::fromLocalFile(resolverRutaImagen("Panel.qml")));
    connect(quickPanel, &QQuickWidget::statusChanged, this, [quickPanel](QQuickWidget::Status status) {
        if (status == QQuickWidget::Error)
            qWarning() << "QML error:" << quickPanel->errors();
    });

    ui.horizontalLayout->replaceWidget(ui.panelControls, quickPanel);
    ui.panelControls->hide();
    ui.panelControls->deleteLater();

    connect(uiBridge_, &UiBridge::dfsRequested, this, &EcoCampus::on_btnDFS_clicked);
    connect(uiBridge_, &UiBridge::bfsRequested, this, &EcoCampus::on_btnBFS_clicked);
    connect(uiBridge_, &UiBridge::buscarCaminoRequested, this, &EcoCampus::onBuscarCamino_clicked);
    connect(uiBridge_, &UiBridge::rutaPerfilRequested, this, &EcoCampus::onRutaPerfil_clicked);
    connect(uiBridge_, &UiBridge::movilidadReducidaChanged, this, &EcoCampus::onMovilidadChanged);
    connect(uiBridge_, &UiBridge::perfilRutaChanged, this, &EcoCampus::onPerfilRutaChanged);
    connect(uiBridge_, &UiBridge::pisoActualChanged, this, &EcoCampus::actualizarCapasMapa);
    connect(uiBridge_, &UiBridge::mostrarBibliotecaChanged, this, &EcoCampus::actualizarCapasMapa);
    connect(uiBridge_, &UiBridge::mostrarComedorChanged, this, &EcoCampus::actualizarCapasMapa);
}

bool EcoCampus::eventFilter(QObject* watched, QEvent* event) {
    if (watched == ui.graphicsView->viewport()) {
        switch (event->type()) {
        case QEvent::Wheel: {
            auto* wheelEvent = static_cast<QWheelEvent*>(event);
            const double factor = wheelEvent->angleDelta().y() > 0 ? 1.15 : 1.0 / 1.15;
            ui.graphicsView->scale(factor, factor);
            return true;
        }
        case QEvent::MouseButtonPress: {
            auto* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::RightButton) {
                panning_ = true;
                lastPanPos_ = mouseEvent->pos();
                ui.graphicsView->setCursor(Qt::ClosedHandCursor);
                return true;
            }
            break;
        }
        case QEvent::MouseMove: {
            if (panning_) {
                auto* mouseEvent = static_cast<QMouseEvent*>(event);
                const QPoint delta = mouseEvent->pos() - lastPanPos_;
                lastPanPos_ = mouseEvent->pos();

                ui.graphicsView->horizontalScrollBar()->setValue(
                    ui.graphicsView->horizontalScrollBar()->value() - delta.x());
                ui.graphicsView->verticalScrollBar()->setValue(
                    ui.graphicsView->verticalScrollBar()->value() - delta.y());
                return true;
            }
            break;
        }
        case QEvent::MouseButtonRelease: {
            auto* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::RightButton && panning_) {
                panning_ = false;
                ui.graphicsView->setCursor(Qt::ArrowCursor);
                return true;
            }
            break;
        }
        default:
            break;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void EcoCampus::actualizarCapasMapa() {
    if (!uiBridge_) return;

    const QString piso = uiBridge_->pisoActual();
    QString mapaGrafo = piso;
    if (!controller_.setMapaActivo(piso.toStdString()))
        mapaGrafo = mapaActual_;

    if (mapaGrafo != mapaActual_) {
        mapaActual_ = mapaGrafo;
        vistaAjustada_ = false;
        dibujarGrafo();
        return;
    }

    for (auto it = mapLayers_.begin(); it != mapLayers_.end(); ++it)
        it.value()->setVisible(false);

    if (mapLayers_.contains("Universidad"))
        mapLayers_.value("Universidad")->setVisible(true);

    if (piso != "Universidad" && mapLayers_.contains(piso))
        mapLayers_.value(piso)->setVisible(true);

    if (uiBridge_->mostrarBiblioteca() && mapLayers_.contains("Biblioteca"))
        mapLayers_.value("Biblioteca")->setVisible(true);

    if (uiBridge_->mostrarComedor() && mapLayers_.contains("Comedor"))
        mapLayers_.value("Comedor")->setVisible(true);

    if (!vistaAjustada_) {
        ajustarVistaMapa(piso == "Universidad" ? "Universidad" : piso);
        vistaAjustada_ = true;
    }
}

void EcoCampus::ajustarVistaMapa(const QString& mapaId) {
    if (!mapLayers_.contains(mapaId)) return;
    auto* item = mapLayers_.value(mapaId);
    const QRectF rect = item->sceneBoundingRect();
    if (rect.isEmpty()) return;

    ui.graphicsView->resetTransform();
    ui.graphicsView->fitInView(rect, Qt::KeepAspectRatio);
}

void EcoCampus::dibujarGrafo() {
    const QSignalBlocker blocker(scene_);

    scene_->clear();
    mapLayers_.clear();

    const Grafo& g = controller_.getGrafo();

    struct FondoImagen {
        QString id;
        QString ruta;
        QPointF posicion;
        qreal z;
        bool seleccionable;
        bool movible;
    };

    const std::vector<FondoImagen> fondos = {
        { "Universidad", resolverRutaImagen("Universidad.png"), QPointF(0, 0), -30, false, false },
        { "Piso 1", resolverRutaImagen("piso 1.png"), QPointF(0, 0), -25, false, false },
        { "Piso 2", resolverRutaImagen("piso 2.png"), QPointF(0, 0), -25, false, false },
        { "Piso 3", resolverRutaImagen("piso 3.png"), QPointF(0, 0), -25, false, false },
        { "Piso 4", resolverRutaImagen("piso 4.png"), QPointF(0, 0), -25, false, false },
        { "Piso 5", resolverRutaImagen("piso 5.png"), QPointF(0, 0), -25, false, false },
        { "Biblioteca", resolverRutaImagen("biblioteca.png"), QPointF(0, 0), -24, false, false },
        { "Comedor", resolverRutaImagen("comedor.png"), QPointF(0, 0), -24, false, false }
    };

    for (const auto& fondo : fondos) {
        QString ruta = fondo.ruta;
        if (!QFileInfo::exists(ruta)) {
            qWarning() << "No se encontro" << ruta;
            continue;
        }

        QPixmap mapa(ruta);
        if (mapa.isNull()) continue;

        auto* item = scene_->addPixmap(mapa);
        item->setPos(fondo.posicion);
        item->setZValue(fondo.z);
        if (fondo.seleccionable)
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        if (fondo.movible)
            item->setFlag(QGraphicsItem::ItemIsMovable, true);

        mapLayers_.insert(fondo.id, item);
    }

    if (mapLayers_.contains("Piso 4") && mapLayers_.contains("Comedor")) {
        auto* piso4 = mapLayers_.value("Piso 4");
        auto* comedor = mapLayers_.value("Comedor");
        const qreal gap = 4.0;
        const QRectF pisoRect = piso4->boundingRect();
        const QRectF comedorRect = comedor->boundingRect();
        comedor->setPos(piso4->pos().x() - comedorRect.width() - gap, piso4->pos().y());
    }

    actualizarCapasMapa();

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

    if (rutaActual_.size() > 1) {
        QPen penRuta(Qt::green, 3);
        for (size_t i = 1; i < rutaActual_.size(); ++i) {
            const Nodo* origen = g.buscarNodo(rutaActual_[i - 1]);
            const Nodo* destino = g.buscarNodo(rutaActual_[i]);
            if (!origen || !destino) continue;
            scene_->addLine(origen->getPosX(), origen->getPosY(),
                destino->getPosX(), destino->getPosY(), penRuta);
        }
    }

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

    const int inicioId = uiBridge_ ? uiBridge_->inicio() : 1;
    auto res = controller_.recorridoDFS(inicioId);
    const long long tiempo = t.microsegundos();
    if (uiBridge_) {
        uiBridge_->setTiempo(QString::number(tiempo) + " 탎");
        uiBridge_->setVisitados(QString::number(res.nodosVisitados));
    }
    rutaActual_ = res.ordenVisita;
    dibujarGrafo();
}

void EcoCampus::on_btnBFS_clicked() {
    Temporizador t;
    t.iniciar();

    const int inicioId = uiBridge_ ? uiBridge_->inicio() : 1;
    auto res = controller_.recorridoBFS(inicioId);
    const long long tiempo = t.microsegundos();
    if (uiBridge_) {
        uiBridge_->setTiempo(QString::number(tiempo) + " 탎");
        uiBridge_->setVisitados(QString::number(res.nodosVisitados));
    }
    rutaActual_ = res.ordenVisita;
    dibujarGrafo();
}

void EcoCampus::on_chkMovilidad_stateChanged(int state) {
    onMovilidadChanged(state == Qt::Checked);
}

void EcoCampus::onMovilidadChanged(bool enabled) {
    controller_.setPerfil(enabled
        ? PerfilUsuario::MovilidadReducida
        : PerfilUsuario::EstudianteRegular);
    dibujarGrafo();
}

void EcoCampus::onPerfilRutaChanged() {
    if (!uiBridge_) return;

    if (uiBridge_->movilidadReducida()) {
        controller_.setPerfil(PerfilUsuario::MovilidadReducida);
        return;
    }

    if (uiBridge_->perfilRuta() == "Nuevo")
        controller_.setPerfil(PerfilUsuario::EstudianteNuevo);
    else
        controller_.setPerfil(PerfilUsuario::EstudianteRegular);
}

void EcoCampus::onBuscarCamino_clicked() {
    const int origenId = uiBridge_ ? uiBridge_->origen() : 1;
    const int destinoId = uiBridge_ ? uiBridge_->destino() : 1;
    auto res = controller_.buscarCamino(origenId, destinoId);

    if (uiBridge_) {
        uiBridge_->setTiempo(QString::number(res.tiempoMicros) + " 탎");
        uiBridge_->setVisitados(QString::number(res.nodosVisitados));
    }

    rutaActual_ = res.encontrado ? res.camino : std::vector<int>{};
    dibujarGrafo();
}

void EcoCampus::onRutaPerfil_clicked() {
    const int origenId = uiBridge_ ? uiBridge_->origen() : 1;
    const int destinoId = uiBridge_ ? uiBridge_->destino() : 1;
    onPerfilRutaChanged();
    auto res = controller_.calcularRuta(origenId, destinoId);

    if (uiBridge_) {
        uiBridge_->setTiempo(QString::number(res.tiempoMicros) + " 탎");
        uiBridge_->setVisitados(QString::number(res.camino.size()));
    }

    rutaActual_ = res.encontrado ? res.camino : std::vector<int>{};
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

